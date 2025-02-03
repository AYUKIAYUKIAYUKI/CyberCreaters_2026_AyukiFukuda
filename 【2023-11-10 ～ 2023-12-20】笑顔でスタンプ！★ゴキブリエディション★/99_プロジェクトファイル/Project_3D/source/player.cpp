//************************************************
//
//プレイヤー[player.cpp]
//Author：福田歩希
//
//************************************************
#include "player.h"

#include "debugproc.h"
#include "input.h"
#include "sound.h"

#include "bullet.h"
#include "camera.h"
#include "model.h"
#include "shadow.h"
#include "visible_rect.h"
#include "wall.h"

//マクロ定義
#define SPD_STOPMOVE_PLAYER	(0.9f)	//ブレーキ力
#define SPD_MOVE_PLAYER	(0.2f)	//移動速度
#define EPSILON	(0.1f)	//閾値

//グローバル変数
Player g_Player;	//プレイヤー情報
int g_nMUKIMUKI_Colorful_CT = 0;	//ムキムキカラフルキャスト
bool g_bOnceRosalia = false;
int g_nDecrease = 0;
//D3DXCOLOR coldef[AMOUNT_PLAYER_PARTS][8];
//bool g_bDef = false;

//パーツセット
static const char* g_sFileNameParts[2] =
{
	"data\\txt\\danceP.txt",
	"data\\txt\\playermodelset.txt"
};

//モーションセット
static const char* g_sFileNameMotion[2] =
{
	"data\\txt\\dance.txt",
	"data\\txt\\playerkeyset.txt"
};

//************************************************
//プレイヤー初期
//************************************************
void InitPlayer(int mode)
{
	g_nMUKIMUKI_Colorful_CT = 0;
	g_bOnceRosalia = false;
	g_nDecrease = 0;
	//g_bDef = false;

	//for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		coldef[i][j] = { 0.0f, 0.0f, 0.0f, 0.0f };
	//	}
	//}

	//プレイヤーの初期セット
	g_Player.nState = PlayerStateNormal;
	g_Player.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_Player.bATK = false;
	g_Player.bMUKIMUKI = false;
	g_Player.nCapacity = AMOUNT_CAPACITY;
	g_Player.nEnegy = 0;
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rotGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nCntState = 0;
	/* パーツ情報クリア */
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		g_Player.aParts[i].pMeshPlayer = NULL;	//メッシュ情報のポインタををクリア
		g_Player.aParts[i].pBuffMatPlayer = NULL;	//マテリアル情報のポインタをクリア
		g_Player.aParts[i].dwNumMatPlayer = 0;	//マテリアルの数をクリア
		g_Player.aParts[i].pTexture = NULL;	//テクスチャ情報のポインタをクリア
		g_Player.aParts[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.aParts[i].posM = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.aParts[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.aParts[i].rotM = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.aParts[i].nIdxParent = 0;
	}
	/* モーション情報クリア */
	for (int i = 0; i < PlayerStateMax; i++)
	{
		g_Player.motion[i].nIdxKey = 0;
		g_Player.motion[i].nLoop = 0;
		g_Player.motion[i].nNumKey = 0;
		g_Player.motion[i].nFrameCnt = 0;

		for (int j = 0; j < AMOUNT_PLAYER_KEY; j++)
		{
			g_Player.motion[i].key[j].nFrame = 0;

			for (int k = 0; k < AMOUNT_PLAYER_PARTS; k++)
			{
				g_Player.motion[i].key[j].parts[k].posGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Player.motion[i].key[j].parts[k].rotGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}
	g_Player.nNowMotion = PlayerMotionStateNormal;
	g_Player.nOldMotion = PlayerMotionStateNormal;
	/* AABB情報クリア */
	g_Player.aabb.min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aabb.max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//影を設定
	SetInfoShadow(20.0f, &g_Player.pos);

	//モデルパーツの設定
	SetInfoParts(mode);

	//モーションの設定
	SetInfoMotion(mode);

	//当たり判定を可視化
	if (mode != MODE_TITLE)
	{
		UpdatePlayerAABB(g_Player.pos);
		//SetSizeVisible_Rect(g_Player.aabb, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), &g_Player.pos);
	}
}

//************************************************
//モデルパーツ情報を設定
//************************************************
void SetInfoParts(int mode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//パーツ用情報を設定
	FILE* pFile = NULL;
	char sPlayerModel[64] = {};
	int ReadMode = 0;

	if (mode == MODE_TITLE)
	{
		ReadMode = 0;
	}
	else
	{
		ReadMode = 1;
	}

	//パーツ間オフセットの読込み
	if (fopen_s(&pFile, g_sFileNameParts[ReadMode], "r") != 0) return;

	/* モデルパーツの総数以上ループで終了 */
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		fscanf_s(pFile, "%f %f %f", &g_Player.aParts[i].pos.x, &g_Player.aParts[i].pos.y, &g_Player.aParts[i].pos.z);
		fscanf_s(pFile, "%f %f %f", &g_Player.aParts[i].rot.x, &g_Player.aParts[i].rot.y, &g_Player.aParts[i].rot.z);
		fscanf_s(pFile, "%d", &g_Player.aParts[i].nIdxParent);

		//g_Player.aParts[i].pos.y *= 50.0f;
	}

	fclose(pFile);

	/**********************************************************/

	//Xファイルの読み込み
	if (fopen_s(&pFile, "data\\txt\\playermodel.txt", "r") != 0) return;

	int i = 0;

	/* ファイルの終端に着くか、モデルパーツの総数以上ループで終了 */
	while (fscanf_s(pFile, "%s", &sPlayerModel[0], 64) != EOF || i < AMOUNT_PLAYER_PARTS)
	{
		D3DXLoadMeshFromX(&sPlayerModel[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.aParts[i].pBuffMatPlayer,
			NULL,
			&g_Player.aParts[i].dwNumMatPlayer,
			&g_Player.aParts[i].pMeshPlayer);

		i++;
	}

	fclose(pFile);

	/**********************************************************/

	for (int j = 0; j < AMOUNT_PLAYER_PARTS; j++)
	{
		//マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_Player.aParts[j].pBuffMatPlayer->GetBufferPointer();

		//そのパーツの持つマテリアル分回す
		for (int k = 0; k < (int)g_Player.aParts[j].dwNumMatPlayer; k++)
		{
			//coldef[j][k] = pMat[k].MatD3D.Diffuse;

			//マテリアルにテクスチャが設定されていれば読込み
			if (pMat[k].pTextureFilename != NULL)
			{
				char* sFileName = pMat[k].pTextureFilename;

				D3DXCreateTextureFromFileA(pDevice,
					sFileName,
					&g_Player.aParts[j].pTexture);
			}
			else
			{
				g_Player.aParts[j].pTexture = NULL;
			}
		}
	}
}

//************************************************
//モーション情報を設定(要改善)
//************************************************
void SetInfoMotion(int mode)
{
	//モーション用情報を設定
	FILE* pFile = NULL;
	char sPlayerMotion[128] = {};
	int ReadMode = 0;

	if (mode == MODE_TITLE)
	{
		ReadMode = 0;
	}
	else
	{
		ReadMode = 1;
	}

	if (fopen_s(&pFile, g_sFileNameMotion[ReadMode], "r") == 0)
	{
		int i = 0;	/* nStyle管理 */

		/* ファイルの終端に着くまでループ */
		while (fscanf_s(pFile, "%s", &sPlayerMotion[0], 128) != EOF)
		{
			if (strcmp(&sPlayerMotion[0], "LOOP") == 0)
			{
				fscanf_s(pFile, "%s %d", &sPlayerMotion[0], 64, &g_Player.motion[i].nLoop);
			}
			if (strcmp(&sPlayerMotion[0], "NUM_KEY") == 0)
			{
				fscanf_s(pFile, "%s %d", &sPlayerMotion[0], 64, &g_Player.motion[i].nNumKey);

				/* キー数を取得したので、キー数分のフレームも取得 */
  				for (int j = 0; j < g_Player.motion[i].nNumKey; fscanf_s(pFile, "%s", &sPlayerMotion[0], 128))
				{
					if (strcmp(&sPlayerMotion[0], "FRAME") == 0)
					{
						fscanf_s(pFile, "%s %d", &sPlayerMotion[0], 64, &g_Player.motion[i].key[j].nFrame);

						/* フレーム数を取得したので、パーツ数分の目的地も取得 */
						for (int k = 0; k < AMOUNT_PLAYER_PARTS; fscanf_s(pFile, "%s", &sPlayerMotion[0], 128))
						{
							if (strcmp(&sPlayerMotion[0], "POS") == 0)
							{
								fscanf_s(pFile, "%s %f %f %f", &sPlayerMotion[0], 64, &g_Player.motion[i].key[j].parts[k].posGoal.x, &g_Player.motion[i].key[j].parts[k].posGoal.y, &g_Player.motion[i].key[j].parts[k].posGoal.z);
								fscanf_s(pFile, "%s", &sPlayerMotion[0], 64);
								fscanf_s(pFile, "%s %f %f %f", &sPlayerMotion[0], 64, &g_Player.motion[i].key[j].parts[k].rotGoal.x, &g_Player.motion[i].key[j].parts[k].rotGoal.y, &g_Player.motion[i].key[j].parts[k].rotGoal.z);

								k++;
							}
						}

						j++;

						/* 全てのキーを読み込むと、次のモーションを読み込む */
						if (j >= g_Player.motion[i].nNumKey)
						{
							i++;

							if(ReadMode == 0)
							{
								if (i > 1) break;
							}
							else if (ReadMode == 1)
							{
								if (i > PlayerMotionStateMax) break;
							}
						}
					}
				}
			}
		}
	}

	if (pFile != NULL)
	{
		fclose(pFile);
	}
}

//************************************************
//プレイヤー破棄
//************************************************
void UninitPlayer(void)
{
	//テクスチャの破棄
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		if (g_Player.aParts[i].pTexture != NULL)
		{
			g_Player.aParts[i].pTexture->Release();
			g_Player.aParts[i].pTexture = NULL;
		}
	}

	//マテリアルの破棄
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		if (g_Player.aParts[i].pBuffMatPlayer != NULL)
		{
			g_Player.aParts[i].pBuffMatPlayer->Release();
			g_Player.aParts[i].pBuffMatPlayer = NULL;
		}
	}

	//メッシュの破棄
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		if (g_Player.aParts[i].pMeshPlayer != NULL)
		{
			g_Player.aParts[i].pMeshPlayer->Release();
			g_Player.aParts[i].pMeshPlayer = NULL;
		}
	}
}

//************************************************
//プレイヤー更新
//************************************************
void UpdatePlayer(int mode)
{
	if (mode != MODE_TITLE)
	{
		g_Player.bATK = false;

		if (g_Player.bMUKIMUKI)
		{
			//g_bDef = false;

			//ムキムキカラフル
			MUKIMUKI_Colorful();

			if (!g_bOnceRosalia)
			{
				g_bOnceRosalia = true;
				PlaySound(SOUND_LABEL_ROSALIA);
			}

			SetVibration(1, 65535);

			g_nDecrease++;

			if (g_nDecrease >= 2)
			{
				g_nDecrease = 0;
				g_Player.nEnegy--;
			}

			if (g_Player.nEnegy <= 0)
			{
				g_Player.bMUKIMUKI = false;
			}
		}
		else
		{
			if (g_Player.nState != PlayerStateDamage)
			{
				//デフォルトカラーに
				//g_bDef = true;
			}

			if (g_bOnceRosalia)
			{
				g_bOnceRosalia = false;
				StopSound(SOUND_LABEL_ROSALIA);
			}
		}

		//被弾確認の処理
		if (g_Player.nState == PlayerStateDamage) TakesDamagePlayer();

		//過去の位置を記録
		g_Player.posOld = g_Player.pos;

		//キャパ回復
		if (g_Player.nCapacity < AMOUNT_CAPACITY)
		{
			if (!g_Player.bMUKIMUKI)
			{
				g_Player.nCapacity++;
				g_Player.nCapacity *= 1.075f;
			}
			else
			{
				g_Player.nCapacity++;
				g_Player.nCapacity *= 1.15f;
			}
		}

		if (g_Player.nEnegy >= AMOUNT_ENEGY)
		{
			g_Player.bMUKIMUKI = true;
		}

		//弾発射
		if (GetKeyboardPress(DIK_SPACE) || GetPressTriggerButtonR())
		{
			if (g_Player.nCapacity >= AMOUNT_USING_CAPACITY)
			{
				/* 1,プレイヤーの向きをカメラ正面方向へ */
				//const Camera* pCamera = GetInfoCamera();
				//g_Player.rotGoal.y = pCamera->rot.y;

				/* 2.弾丸を発射 */
				SetInfoBullet();

				if (mode == MODE_GAME)
				{
					if (!g_Player.bMUKIMUKI)
					{
						g_Player.nCapacity -= AMOUNT_USING_CAPACITY;
					}
					else
					{
						g_Player.nCapacity -= AMOUNT_USING_CAPACITY * 0.8;
					}
				}

				PlaySound(SOUND_LABEL_ATK);
			}

			//攻撃判定を出す
			g_Player.bATK = true;
		}

		//攻撃していて、被弾していなければここで攻撃モーション
		if (g_Player.bATK && g_Player.nState != PlayerStateDamage)
		{
			g_Player.nState = PlayerStateAtk;
			g_Player.nNowMotion = PlayerMotionStateAtk;
		}
		//攻撃していなくて、被弾していなければここで通常モーションに
		else if (!g_Player.bATK && g_Player.nState != PlayerStateDamage)
		{
			g_Player.nState = PlayerStateNormal;
			g_Player.nNowMotion = PlayerMotionStateNormal;
		}

		//移動
		if (MovePlayer() && g_Player.nState != PlayerStateAtk)
		{
			//被弾していなければこここで移動モーション
			if (g_Player.nState != PlayerStateDamage)
			{
				g_Player.nNowMotion = PlayerMotionStateMove;
			}
		}

		//回転
		MoveRotatePlayer();

		////ジャンプ
		//if (g_Player.nState != PlayerStateJump && JumpPlayer())
		//{
		//	g_Player.nState = PlayerStateJump;
		//	g_Player.nNowMotion = PlayerStateJump;
		//}

		////着地
		//if (g_Player.nState == PlayerStateJump && LandPlayer())
		//{
		//	g_Player.nState = PlayerStateNormal;
		//	g_Player.nNowMotion = PlayerStateLand;
		//}

		//AABB更新
		UpdatePlayerAABB(g_Player.pos);

		//当たり判定
		CollisionWall();
		//CollisionModel();

		/* 攻撃モーション再生 */
		if (GetKeyboardTrigger(DIK_M))
		{
			if (g_Player.nNowMotion != PlayerStateAtk)
			{
				g_Player.nState = PlayerStateAtk;
				g_Player.nNowMotion = PlayerMotionStateAtk;
			}
		}

		PrintDebugProc("プレイヤーの座標：( %f, %f, %f, )\n", g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);	
		PrintDebugProc("プレイヤーの移動量：( %f, %f, %f, )\n", g_Player.move.x, g_Player.move.y, g_Player.move.z);
	}

	//モーション再生
	MotionPlayer();
}

//************************************************
//プレイヤー移動
//************************************************
bool MovePlayer(void)
{
	bool bMove = false;

	//カメラの向きに対して進行方向を十字に変える
	Camera* pCamera = GetInfoCamera();

	float X = 0.0f;
	float Z = 0.0f;

	if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_LEFT))
	{
		X = -1.0f;
	}
	if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_RIGHT))
	{
		X = 1.0f;
	}
	if (GetKeyboardPress(DIK_W) || GetJoypadPress(JOYKEY_UP))
	{
		Z = 1.0f;
	}
	if (GetKeyboardPress(DIK_S) || GetJoypadPress(JOYKEY_DOWN))
	{
		Z = -1.0f;
	}

	//何かを入力していれば移動している判定
	if (X != 0.0f || Z != 0.0f)
	{
		bMove = true;
	}

	if (bMove)
	{
		//移動量と目標方角を設定
		if (!g_Player.bATK)
		{
			g_Player.move.x += sinf(atan2f(X, Z) + pCamera->rot.y);
			g_Player.move.z += cosf(atan2f(X, Z) + pCamera->rot.y);
		}

		if (g_Player.bMUKIMUKI)
		{
			g_Player.move.x += sinf(atan2f(X, Z) + pCamera->rot.y);
			g_Player.move.z += cosf(atan2f(X, Z) + pCamera->rot.y);
		}

		if (g_Player.nState != PlayerStateDamage)
		{
			g_Player.rotGoal.y = atan2f(X, Z) + pCamera->rot.y;
		}
	}

	g_Player.move *= SPD_STOPMOVE_PLAYER;	//ブレーキ

	//ある程度移動量が少ないと0を入れておく
	if (g_Player.move.x < EPSILON && g_Player.move.x > -EPSILON) g_Player.move.x = 0.0f;
	if (g_Player.move.y < EPSILON && g_Player.move.y > -EPSILON) g_Player.move.y = 0.0f;
	if (g_Player.move.z < EPSILON && g_Player.move.z > -EPSILON) g_Player.move.z = 0.0f;

	g_Player.pos += g_Player.move * SPD_MOVE_PLAYER;	//移動

	//ジャンプしてるなら重力
	//if (g_Player.nState == PlayerStateJump) g_Player.move.y = g_Player.move.y - 3.0f;

	return bMove;
}

//************************************************
//プレイヤー回転
//************************************************
void MoveRotatePlayer(void)
{
	////プレイヤーが回転
	//if (GetKeyboardPress(DIK_Z))
	//{
	//	g_Player.rotGoal.y -= 0.1f;

	//	if (g_Player.rotGoal.y <= -D3DX_PI) g_Player.rotGoal.y = D3DX_PI;
	//}
	//else if (GetKeyboardPress(DIK_C))
	//{
	//	g_Player.rotGoal.y += 0.1f;

	//	if (g_Player.rotGoal.y >= D3DX_PI) g_Player.rotGoal.y = -D3DX_PI;
	//}

	//ブレーキ力
	float StopEnergy = 0.1f;

	//謎の抑止力
	//float fStop = 1.0f;
	//if (g_Player.bATK)
	//{
	//	fStop = 0.2f;
	//}

	//回転ブレーキ
	if (g_Player.rotGoal.y - g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y += ((g_Player.rotGoal.y - g_Player.rot.y) * StopEnergy + (D3DX_PI * 1.8f));
	}
	else if (g_Player.rotGoal.y - g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += ((g_Player.rotGoal.y - g_Player.rot.y) * StopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		g_Player.rot.y += ((g_Player.rotGoal.y - g_Player.rot.y) * StopEnergy);
	}
}

//************************************************
//プレイヤージャンプ
//************************************************
bool JumpPlayer(void)
{
	bool bJump = false;

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		g_Player.move.y += 200.0f;

		bJump = true;
	}

	return bJump;
}

//************************************************
//プレイヤー着地
//************************************************
bool LandPlayer(void)
{
	bool bLand = false;

	if (g_Player.pos.y < 0.0f)
	{
		g_Player.pos.y = 0.0f;
		g_Player.move.y = 0.0f;

		bLand = true;
	}

	return bLand;
}

//************************************************
//プレイヤー被弾
//************************************************
void TakesDamagePlayer(void)
{
	//無敵時間
	if (g_Player.nCntState > 0)
	{
		g_Player.nCntState--;
		g_Player.nCapacity = 0;
		g_Player.col.a *= -1.0f;
		g_Player.rot.y++;
		g_Player.nNowMotion = PlayerMotionStateJump;
	}
	//解除するとき
	else
	{
		g_Player.nState = PlayerStateNormal;
		g_Player.col.a = 1.0f;
	}
}

//************************************************
//プレイヤーAABB更新
//************************************************
void UpdatePlayerAABB(D3DXVECTOR3 pos)
{
	g_Player.aabb.min =
	{
		pos.x - 15.0f,
		pos.y,
		pos.z - 15.0f
	};

	g_Player.aabb.max =
	{
		pos.x + 15.0f,
		pos.y + 70.0f,
		pos.z + 15.0f
	};
}

//************************************************
//プレイヤーモーション管理
//************************************************
void MotionPlayer(void)
{
	PlayerMotionSet* Motion = &g_Player.motion[g_Player.nNowMotion];

	//モーションに変更があるか検知
	MotionChangePlayer();

	//パーツの移動や回転
	MotionMovePlayer(Motion);

	//モーション用の経過カウント
	MotionCountPlayer(Motion);
}

//************************************************
//モーション変更
//************************************************
void MotionChangePlayer(void)
{
	/* モーションが変更されていれば */
	if (g_Player.nOldMotion != g_Player.nNowMotion)
	{
		//キーとフレームカウントリセット
		g_Player.motion[g_Player.nOldMotion].nFrameCnt = 0;
		g_Player.motion[g_Player.nOldMotion].nIdxKey = 0;

		//新しいモーションを再生したことを保存
		g_Player.nOldMotion = g_Player.nNowMotion;
	}
}

//************************************************
//モーション用移動
//************************************************
void MotionMovePlayer(const PlayerMotionSet* Motion)
{
	/* …？(用研究) */
	//float fFrame = (float)(Motion->key[Motion->nIdxKey].nFrame);
	float fFrame = (float)(Motion->key[Motion->nIdxKey].nFrame - Motion->nFrameCnt);

	//目標と現在の差を埋めていく
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		g_Player.aParts[i].posM += (Motion->key[Motion->nIdxKey].parts[i].posGoal - g_Player.aParts[i].posM) / fFrame;
		g_Player.aParts[i].rotM += (Motion->key[Motion->nIdxKey].parts[i].rotGoal - g_Player.aParts[i].rotM) / fFrame;
	}
}

//************************************************
//モーション用カウント
//************************************************
void MotionCountPlayer(PlayerMotionSet* Motion)
{
	Motion->nFrameCnt++;	/* フレームを進める */

	if (Motion->nFrameCnt >= Motion->key[Motion->nIdxKey].nFrame)	/* 所要フレーム数を経過で */
	{
		if (g_Player.nNowMotion == PlayerMotionStateAtk && Motion->nIdxKey > 5)
		{
			Motion->nFrameCnt = 0;
			Motion->nIdxKey = 4;
		}

		Motion->nFrameCnt = 0;
		Motion->nIdxKey++;		/* キーを進める */

		if (Motion->nIdxKey >= Motion->nNumKey)	/* 所要キーを経過で */
		{
			if (Motion->nLoop == 1)
			{
				Motion->nIdxKey = 0;
				return;
			}

			g_Player.nNowMotion = PlayerMotionStateNormal;
		}
	}
}

//************************************************
//プレイヤー描画
//************************************************
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	D3DMATERIAL9 matDef;	//現在のマテリアル保存用

	D3DXMATERIAL* pMat;	//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//向きを反映1
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_Player.rot.y,
		g_Player.rot.x,
		g_Player.rot.z);

	//向きを反映2
	D3DXMatrixMultiply(&g_Player.mtxWorld,
		&g_Player.mtxWorld,
		&mtxRot);

	//位置を反映1
	D3DXMatrixTranslation(&mtxTrans,
		g_Player.pos.x,
		g_Player.pos.y,
		g_Player.pos.z);

	//位置を反映2
	D3DXMatrixMultiply(&g_Player.mtxWorld,
		&g_Player.mtxWorld,
		&mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.aParts[i].mtxWorld);

		//モーション向きの反映
		D3DXVECTOR3 PartsRot =
		{
			g_Player.aParts[i].rot.x + g_Player.aParts[i].rotM.x,
			g_Player.aParts[i].rot.y + g_Player.aParts[i].rotM.y,
			g_Player.aParts[i].rot.z + g_Player.aParts[i].rotM.z
		};

		//向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			PartsRot.y,
			PartsRot.x,
			PartsRot.z);

		//向きを反映2
		D3DXMatrixMultiply(&g_Player.aParts[i].mtxWorld,
			&g_Player.aParts[i].mtxWorld,
			&mtxRot);

		//モーション位置の反映
		D3DXVECTOR3 PartsPos =
		{
			g_Player.aParts[i].pos.x + g_Player.aParts[i].posM.x,
			g_Player.aParts[i].pos.y + g_Player.aParts[i].posM.y,
			g_Player.aParts[i].pos.z + g_Player.aParts[i].posM.z
		};

		//位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			PartsPos.x,
			PartsPos.y,
			PartsPos.z);

		//位置を反映
		D3DXMatrixMultiply(&g_Player.aParts[i].mtxWorld,
			&g_Player.aParts[i].mtxWorld,
			&mtxTrans);

		D3DXMATRIX mtxParent = {};

		//親のワールドマトリックスを取得
		if (g_Player.aParts[i].nIdxParent == -1)
		{
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			mtxParent = g_Player.aParts[g_Player.aParts[i].nIdxParent].mtxWorld;
		}

		//パーツごとのワールドマトリックスを算出
		D3DXMatrixMultiply(&g_Player.aParts[i].mtxWorld,
			&g_Player.aParts[i].mtxWorld,
			&mtxParent);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aParts[i].mtxWorld);

		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aParts[i].pBuffMatPlayer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aParts[i].dwNumMatPlayer; nCntMat++)
		{
			//カラチェン
			if (g_Player.bMUKIMUKI)
			{
				pMat[nCntMat].MatD3D.Diffuse = g_Player.col;
			}

			//if (g_bDef)
			//{
			//	pMat[nCntMat].MatD3D.Diffuse = coldef[i][nCntMat];
			//}

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			if (g_Player.aParts[i].pTexture != NULL)
			{
				pDevice->SetTexture(0, g_Player.aParts[i].pTexture);
			}
			else
			{
				pDevice->SetTexture(0, NULL);
			}

			//モデルパーツの描画
			g_Player.aParts[i].pMeshPlayer->DrawSubset(nCntMat);
		}

		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//************************************************
//プレイヤー情報を取得
//************************************************
Player* GetInfoPlayer(void)
{
	return &g_Player;
}

//************************************************
//ムキムキカラフルモード
//************************************************
void MUKIMUKI_Colorful(void)
{
	g_nMUKIMUKI_Colorful_CT++;

	switch (g_nMUKIMUKI_Colorful_CT)
	{
	case 0:
		g_Player.col = { 1.0f, 0.0f, 0.0f, 1.0f };
		break;

	case 1:
		g_Player.col = { 0.0f, 1.0f, 0.0f, 1.0f };
		break;

	case 2:
		g_Player.col = { 0.0f, 0.0f, 1.0f, 1.0f };
		break;

	case 3:
		g_Player.col = { 1.0f, 1.0f, 0.0f, 1.0f };
		break;

	case 4:
		g_Player.col = { 1.0f, 0.0f, 1.0f, 1.0f };
		break;

	case 5:
		g_Player.col = { 0.0f, 1.0f, 1.0f, 1.0f };
		g_nMUKIMUKI_Colorful_CT = -1;
		break;
	}
}