//************************************************
//
// プレイヤー処理[player.cpp]
// Author：福田歩希, kasai keisuke
//
//************************************************

/*---【インクルードファイル】---*/
#include "player.h"

// システム系
#include "input.h"
#include "sound.h"

// 諸処理
#include "bullet.h"
#include "camera.h"
#include "collision.h"
#include "effect_heart.h"
#include "effect_sand.h"
#include "effect_smoke.h"
#include "effect_soul.h"
#include "game.h"
#include "object.h"
#include "player_count.h"
#include "shadow.h"
#include "weapon.h"

// デバッグ時
#ifdef _DEBUG
#include "debugproc.h"
#include "visible_sph.h"
#include <assert.h>
#endif	// _DEBUG

/*---【グローバル変数】---*/
PlayerModel g_PlayerModel[AMOUNT_PLAYER_PARTS];	// プレイヤー用モデル
PlayerMotion g_PlayerMotion[8];					// プレイヤー用モーション
Player g_Player[MAX_PLAYER];					// プレイヤー情報
int g_nNumPlayer = 0;							// プレイ人数格納用
/*---【キーボードでデバッグ操作するプレイヤーを識別】---*/
int g_P_id = -1;

/*---【プロトタイプ宣言】---*/
void ClearInfoPlayerModel(void);	// プレイヤー用モデルのクリア
void ClearInfoPlayerMotion(void);	// プレイヤー用モーションのクリア
void ClearInfoPlayer(void);			// プレイヤー情報のクリア

//************************************************
// プレイヤー初期
//************************************************
void InitPlayer(int joined)
{
	// グローバル変数の初期化
	g_P_id = -1;		// デバッグ操作プレイヤーを変更
	g_nNumPlayer = 0;	// 参加人数格納用

	//プレイ人数の取得
	g_nNumPlayer = ReturnSelectPlayerCount() + 1;

	// プレイヤー用モデルのクリア
	ClearInfoPlayerModel();

	// プレイヤー用モーションのクリア
	ClearInfoPlayerMotion();

	// プレイヤー情報のクリア
	ClearInfoPlayer();

	// プレイヤー用のモデル情報を取得
	ImportModelPlayer();

	// プレイヤー用のモーション情報を取得
	ImportMotionPlayer();
		
	// プレイヤー生成
	CreatePlayer(joined);

	// スポーン地点を設定
	SetSpawnPlayer(joined);
}

//************************************************
// プレイヤー生成
//************************************************
void CreatePlayer(int joined)
{
	for (int i = 0; i < joined; i++)
	{
		// モーション情報をコピー
		for (int j = 0; j < 8; j++)
		{
			if (g_PlayerMotion[j].amount_key == 0)
			{ // 未使用ならコンティニュー
				continue;
			}

			g_Player[i].motion[j] = g_PlayerMotion[j];
		}

		g_Player[i].use = true;						// 使用
		g_Player[i].param.style = i;				// スタイル番号
		g_Player[i].param.state = stateNormal_p;	// 状態
		g_Player[i].param.HP = 3;					// 体力
		g_Player[i].param.SPD = 10.0f;				// 速度
		g_Player[i].param.rad = 30.0f;				// 判定サイズ
		g_Player[i].param.motion_now = styleGun;	// 武器
		g_Player[i].param.motion_now = 0;
		g_Player[i].param.motion_old = 0;
		g_Player[i].param.weapon = styleGun;		// 武器
		g_Player[i].PFW.magazine = 20;				// 弾数


		// スタイル番号を照合
		VerifyStylePlayer(i);

		/*---【影を生成】---*/
		g_Player[i].id_shadow = CreateShadow(40.0f);

#ifdef _DEBUG

		// 当たり判定を可視化
		CreateVisibleSph(g_Player[i].param.rad, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), &g_Player[i].pos);

#endif
	}
}

//************************************************
// スポーン地点設定
//************************************************
void SetSpawnPlayer(int joined)
{
	switch (joined)
	{
	case 1:

		g_Player[0].pos = { 0.0f, 0.0f, 0.0f };

		break;

	case 2:

		g_Player[0].pos = { -100.0f, 0.0f, 0.0f };
		g_Player[1].pos = { 100.0f, 0.0f, 0.0f };

		break;

	case 3:

		g_Player[0].pos = { -100.0f, 0.0f, 100.0f };
		g_Player[1].pos = { 100.0f, 0.0f, 100.0f };
		g_Player[2].pos = { -100.0f, 0.0f, -100.0f };

		break;

	case 4:

		g_Player[0].pos = { -100.0f, 0.0f, 100.0f };
		g_Player[1].pos = { 100.0f, 0.0f, 100.0f };
		g_Player[2].pos = { -100.0f, 0.0f, -100.0f };
		g_Player[3].pos = { 100.0f, 0.0f, -100.0f };

		break;
	}
}

//************************************************
// モデル情報を読み込む
//************************************************
void ImportModelPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int AmountModel = 0;		// モデルの数を格納
	int id_Model = 0;			// モデルの識別用

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\PLAYER\\player_model.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "プレイヤーモデル情報の展開に失敗");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "AMOUNT_MODEL") == 0)
		{
			// 読み込むモデル数を取得する
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &AmountModel);
		}

#ifdef _DEBUG

		// エラー
		assert(AmountModel < AMOUNT_PLAYER_PARTS && "プレイヤーモデルモデル情報が最大量を越えました");

#endif	// _DEBUG

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// 読み込むモデル名を取得する
			fscanf_s(pFile, "%s %s", &FileString[0], 2, &FileString[0], 128);

			// 読み込んだ情報をひな形にのみコピーする
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_PlayerModel[id_Model].pBuffMat,
				NULL,
				&g_PlayerModel[id_Model].NumMat,
				&g_PlayerModel[id_Model].pMesh);

			id_Model++; // パーツを進める

			if (id_Model == AmountModel)
			{ // モデル数分読み取り終わると終了
				break;
			}
		}
	}

	// 各モデルのオフセット情報を取得
	ImportOffsetPlayer(pFile, AmountModel);

	// 各モデルのテクスチャ情報を取得
	ImportTexPlayer(AmountModel);

	// ファイルを閉じる
	fclose(pFile);
}

//************************************************
// モデルオフセット情報を読み込む
//************************************************
void ImportOffsetPlayer(FILE* pFile, int AmountModel)
{
	// ファイルデータ読込み用
	char FileString[128] = {};	// 文章を格納
	int style = -1;				// このパーツのスタイルを格納
	int weapon = -1;			// このパーツの武器スタイルを格納
	int IdxParent = -1;			// 親のインデックスを格納
	D3DXVECTOR3 pos = {};		// 位置のオフセットを格納
	D3DXVECTOR3 rot = {};		// 向きのオフセットを格納
	int id_Model = 0;			// モデルの識別用

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // このパーツのスタイルを取得	
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &style);
		}

		if (strcmp(&FileString[0], "WEAPON") == 0)
		{ // このパーツのスタイルを取得	
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &weapon);
		}

		if (strcmp(&FileString[0], "PARENT") == 0)
		{ // 親パーツとなるものの番を取得	
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &IdxParent);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // 位置のオフセットを取得	
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // 向きのオフセットを取得	
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_PARTSSET") == 0)
		{
			// 読み込んだ情報をひな形にのみコピーする
			g_PlayerModel[id_Model].style = style;
			g_PlayerModel[id_Model].weapon = weapon;
			g_PlayerModel[id_Model].IdxParent = IdxParent;
			g_PlayerModel[id_Model].pos_offset = pos;
			g_PlayerModel[id_Model].rot_offset = rot;

			weapon = -1;	// 武器スタイルをリセット
			id_Model++;		// パーツを進める

			if (id_Model == AmountModel)
			{ // モデル数分読み取り終わると終了
				break;
			}
		}
	}

	// 攻撃位置のオフセット情報を取得
	ImportOffsetAtkPlayer(pFile);
}

//************************************************
// (強引に) 攻撃位置のオフセット情報を読み込む
//************************************************
void ImportOffsetAtkPlayer(FILE* pFile)
{
	// ファイルデータ読込み用
	char FileString[128] = {};	// 文章を格納
	int i = 0;					// 汎用整数
	D3DXVECTOR3 pos = {};		// 位置のオフセットを格納

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{ 
		if (strcmp(&FileString[0], "POS") == 0)
		{ // 位置のオフセットを反映

			// 位置を取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
			
			for (int j = 0; j < MAX_PLAYER; j++)
			{ // (無理やり) 全てのプレイヤーに反映
				g_Player[j].offset_atk[i].pos = pos;
			}

			i++;	// 次の番へ
		}

		if (i >= Max_itemstyle)
		{ // 武器の最大数に到達すると終了
			break;
		}
	}
}

//************************************************
// モデルテクスチャ情報を読み込む
//************************************************
void ImportTexPlayer(int AmountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int i = 0; i < AmountModel; i++)
	{
		// マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_PlayerModel[i].pBuffMat->GetBufferPointer();

		// そのパーツの持つマテリアル分回す
		for (int j = 0; j < (int)g_PlayerModel[i].NumMat; j++)
		{
			// マテリアルにテクスチャが設定されていれば読込み
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_PlayerModel[i].pTex[j]);
			}
			else
			{
				g_PlayerModel[i].pTex[j] = NULL;
			}
		}
	};
}

//************************************************
// スタイル番号の照合
//************************************************
void VerifyStylePlayer(int id)
{
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		// 各プレイヤーのスタイル番号と各パーツのスタイル番号を照合
		if (g_PlayerModel[i].style == g_Player[id].param.style || g_PlayerModel[i].style == 99)
		{ // スタイル番号の一致しているパーツ及びユニパーツを有効化する
			g_Player[id].parts[i] = g_PlayerModel[i];
		}
	}
}

//************************************************
// モーション情報を読み込む
//************************************************
void ImportMotionPlayer(void)
{
	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int i = 0, j = 0, k = 0;	// 汎用整数
	int loop = 0;				// ループフラグを格納
	int amountKey = 0;			// 総キー数を取得
	int amountFrame = 0;		// 総フレーム数を取得
	D3DXVECTOR3 pos, rot;		// 位置と向きを格納

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\PLAYER\\player_motion.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "プレイヤーモーション情報の展開に失敗");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "LOOP") == 0)
		{ // ループフラグを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &loop);
		}

		if (strcmp(&FileString[0], "NUM_KEY") == 0)
		{ // 総キー数を取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &amountKey);
		}

		if (strcmp(&FileString[0], "FRAME") == 0)
		{ // フレーム数を取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &amountFrame);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // 動作位置を取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // 動作向きを取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_KEY") == 0)
		{ // パーツ動作情報を保存
			g_PlayerMotion[i].key[j].dest[k].pos = pos;
			g_PlayerMotion[i].key[j].dest[k].rot = rot;

			k++;	// パーツ番号を進める
		}

		if (strcmp(&FileString[0], "END_KEYSET") == 0)
		{ // キー情報を保存
			g_PlayerMotion[i].key[j].amount_frame = amountFrame;

			k = 0;	// パーツ番号をリセット
			j++;	// キー番号を進める
		}

		if (strcmp(&FileString[0], "END_MOTIONSET") == 0)
		{ // モーション情報を保存
			g_PlayerMotion[i].loop = loop;
			g_PlayerMotion[i].amount_key = amountKey;

			j = 0;	// キー番号をリセット
			i++;	// モーション番号を進める
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{ // 終了
			break;
		}
	}
}

//************************************************
// プレイヤー破棄
//************************************************
void UninitPlayer(void)
{
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_PlayerModel[i].pTex[j] != NULL)
			{ // テクスチャの破棄

				g_PlayerModel[i].pTex[j]->Release();
				g_PlayerModel[i].pTex[j] = NULL;
			}
		}

		if (g_PlayerModel[i].pMesh != NULL)
		{ // メッシュの破棄

			g_PlayerModel[i].pMesh->Release();
			g_PlayerModel[i].pMesh = NULL;
		}

		if (g_PlayerModel[i].pBuffMat != NULL)
		{ // マテリアルの破棄

			g_PlayerModel[i].pBuffMat->Release();
			g_PlayerModel[i].pBuffMat = NULL;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// プレイヤー更新
//************************************************
void UpdatePlayer(int joined)
{
	for (int i = 0; i < joined; i++)
	{
		// 過去の位置を記録
		g_Player[i].pos_old = g_Player[i].pos;

		// 回転
		RotatePlayer(i);

		// 砲塔調整
		AdjustTurret(i);

		// 移動
		MovePlayer(i);

		// 移動反映
		TranslatePlayer(i);

		/*---【新しい影の追従】---*/
		TrackShadow(g_Player[i].id_shadow,
			g_Player[i].pos);

		// 攻撃
		AtkPlayer(i);

		// 攻撃の反動
		//RecoilPlayer(i);

		// 負傷
		DamagePlayer(i);

		// 死亡判定
		DeadPlayer(i);

		// 復活判定
		ResurrectPlayer(i);

		// モーション
		MotionPlayer(i);
	}

	// 最後に行列計算
	CalcMtxPlayer();

#ifdef _DEBUG

	// デバッグ表示
	//PrintDebugPlayer();

#endif	// _DEBUG
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// プレイヤー回転
//************************************************
void RotatePlayer(int id)
{
	// ブレーキ力
	float StopEnergy = 0.1f;

	if (!g_Player[id].use)
	{ // 未使用ならリターン
		return;
	}

	// 回転ブレーキ
	if (g_Player[id].rot_goal.y - g_Player[id].rot.y > D3DX_PI)
	{
		g_Player[id].rot.y += ((g_Player[id].rot_goal.y - g_Player[id].rot.y) * StopEnergy + (D3DX_PI * 1.8f));
	}
	else if (g_Player[id].rot_goal.y - g_Player[id].rot.y < -D3DX_PI)
	{
		g_Player[id].rot.y += ((g_Player[id].rot_goal.y - g_Player[id].rot.y) * StopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		g_Player[id].rot.y += ((g_Player[id].rot_goal.y - g_Player[id].rot.y) * StopEnergy);
	}
}

//************************************************
// 砲塔を視点方向へ向ける
//************************************************
void AdjustTurret(int id)
{
	// カメラ情報を取得
	Camera* pCamera = GetInfoCamera();

	if (!g_Player[id].use)
	{ // 未使用ならリターン
		return;
	}

	for (int j = 0; j < AMOUNT_PLAYER_PARTS; j++)
	{ // 装備の変更を考慮し、描画のないパーツにも情報を与える

		// この番パーツの「親パーツ」のインデックスを保存
		int IdxParent = g_Player[id].parts[j].IdxParent;

#if OFFSET_VERIFY

		if (g_Player[id].parts[j].IdxParent == -1)
		{ // この番のパーツが土台パーツであるならスキップ
			continue;
		}

#else

		if (IdxParent != 0)
		{ // この番のパーツの親のモデル種類が土台パーツでないならスキップ
			continue;
		}

#endif	// OFFSET_VERIFY

		// 向きを視点正面方向へ
		g_Player[id].parts[j].rot_moved.y = pCamera[id].rot.y;
	}
}

//************************************************
// プレイヤー移動
//************************************************
void MovePlayer(int id)
{
#ifdef _DEBUG

	if (id == g_P_id)
	{ // デバッグ選択しているプレイヤーの番を飛ばす
		DEBUG_MovePlayer();
		return;
	}

#endif	// _DEBUG

	if (!g_Player[id].use)
	{ // 未使用ならリターン
		return;
	}

	if (g_Player[id].param.state != stateDead_p &&
		g_Player[id].param.motion_now != 3)
	{ // 被弾モーション中：死亡状態でないとき

		// カメラ情報を取得
		const Camera* pCamera = GetInfoCamera();

		if (GetJoyStickL(id))
		{ // 左スティックで移動
			const XINPUT_GAMEPAD GamePad = GetGamePad(id);

			// 移動量と目的の向きを付与
			g_Player[id].move.x += sinf(atan2f((float)(GamePad.sThumbLX * 0.00001), (float)(GamePad.sThumbLY * 0.00001)) + pCamera[id].rot.y);
			g_Player[id].move.z += cosf(atan2f((float)(GamePad.sThumbLX * 0.00001), (float)(GamePad.sThumbLY * 0.00001)) + pCamera[id].rot.y);
			g_Player[id].rot_goal.y = atan2f((float)(GamePad.sThumbLX * -0.000001), (float)(GamePad.sThumbLY * -0.000001)) + pCamera[id].rot.y;

			if (g_Player[id].param.state != stateDamage_p &&
				g_Player[id].param.state != stateDead_p)
			{ // 負傷：死亡状態でなければ

				// 移動状態に
				g_Player[id].param.state = stateMove_p;

				// 移動モーションを再生
				g_Player[id].param.motion_now = 1;
			}

			// 砂エフェクト
			SetEffectSand(g_Player[id].pos, 0, 30.0f, id);
			SetEffectSand(g_Player[id].pos, 1, 30.0f, id);
		}
		else
		{ // 移動していないとき

			if (g_Player[id].param.state != stateDamage_p)
			{ // 負傷状態でなければ

				// 通常状態に
				g_Player[id].param.state = stateNormal_p;

				// 通常モーションを再生
				g_Player[id].param.motion_now = 0;
			}
		}
	}

	g_Player[id].move *= SPD_STOPMOVE_PLAYER;	// ブレーキ

	// ある程度移動量が少ないと0を入れておく
	if (g_Player[id].move.x < EPSILON && g_Player[id].move.x > -EPSILON)
	{
		g_Player[id].move.x = 0.0f;
	}

	if (g_Player[id].move.z < EPSILON && g_Player[id].move.z > -EPSILON)
	{
		g_Player[id].move.z = 0.0f;
	}
}

//************************************************
// デバッグ移動
//************************************************
void DEBUG_MovePlayer(void)
{
	if (g_Player[g_P_id].param.state != stateDead_p &&
		g_Player[g_P_id].param.motion_now != 3)
	{ // 被弾モーション中：死亡状態でないとき

		// カメラ情報を取得
		const Camera* pCamera = GetInfoCamera();

		// デバッグ時はキーボード入力で移動可能
		float X = 0.0f;
		float Z = 0.0f;
		bool move = false;

		if (GetKeyboardTrigger(DIK_1))
		{
			g_P_id = 0;
		}
		else if (GetKeyboardTrigger(DIK_2))
		{
			g_P_id = 1;
		}
		else if (GetKeyboardTrigger(DIK_3))
		{
			g_P_id = 2;
		}
		else if (GetKeyboardTrigger(DIK_4))
		{
			g_P_id = 3;
		}

		if (GetKeyboardPress(DIK_A))
		{
			X = -1.0f;
		}
		else if (GetKeyboardPress(DIK_D))
		{
			X = 1.0f;
		}

		if (GetKeyboardPress(DIK_W))
		{
			Z = 1.0f;
		}
		else if (GetKeyboardPress(DIK_S))
		{
			Z = -1.0f;
		}

		if (X != 0.0f || Z != 0.0f)
		{ // 何かを入力していれば移動している判定
			move = true;
		}

		if (move)
		{
			// 移動量と目標向きを設定
			g_Player[g_P_id].move.x += sinf(atan2f(X, Z) + pCamera[g_P_id].rot.y);
			g_Player[g_P_id].move.z += cosf(atan2f(X, Z) + pCamera[g_P_id].rot.y);
			g_Player[g_P_id].rot_goal.y = atan2f(-X, -Z) + pCamera[g_P_id].rot.y;

			if (g_Player[g_P_id].param.state != stateDamage_p &&
				g_Player[g_P_id].param.state != stateDead_p)
			{ // 負傷：死亡状態でなければ

				// 移動状態に
				g_Player[g_P_id].param.state = stateMove_p;

				// 移動モーションを再生
				g_Player[g_P_id].param.motion_now = 1;
			}

			// 砂エフェクト
			SetEffectSand(g_Player[g_P_id].pos, 0, 30.0f, g_P_id);
			SetEffectSand(g_Player[g_P_id].pos, 1, 30.0f, g_P_id);
		}
		else
		{ // 移動していないとき

			if (g_Player[g_P_id].param.state != stateDamage_p)
			{ // 負傷状態でなければ

				// 通常状態に
				g_Player[g_P_id].param.state = stateNormal_p;

				// 通常モーションを再生
				g_Player[g_P_id].param.motion_now = 0;
			}
		}
	}

	g_Player[g_P_id].move *= SPD_STOPMOVE_PLAYER;	// ブレーキ
}

//************************************************
// 移動を反映
//************************************************
void TranslatePlayer(int id)
{
	g_Player[id].pos += g_Player[id].move * SPD_MOVE_PLAYER;	// 移動

	if (g_Player[id].param.state == stateDamage_p)
	{ // 負傷状態のみ特別に加速
		g_Player[id].pos += g_Player[id].move * SPD_MOVE_PLAYER;
	}

	// オブジェクトとの当たり判定を実行し、移動を補正
	HitObjectPlayer(id);

	// ステージの端を越えていたら補正
	if (g_Player[id].pos.x + g_Player[id].param.rad >= 2000.0f)
	{
		g_Player[id].pos.x = 2000.0f - g_Player[id].param.rad;
	}
	else if (g_Player[id].pos.x - g_Player[id].param.rad <= -2000.0f)
	{
		g_Player[id].pos.x = -2000.0f + g_Player[id].param.rad;
	}

	if (g_Player[id].pos.z + g_Player[id].param.rad >= 2000.0f)
	{
		g_Player[id].pos.z = 2000.0f - g_Player[id].param.rad;
	}
	else if (g_Player[id].pos.z - g_Player[id].param.rad <= -2000.0f)
	{
		g_Player[id].pos.z = -2000.0f + g_Player[id].param.rad;
	}
}

//************************************************
// 壁との当たり判定
//************************************************
void HitObjectPlayer(int id)
{
	Object* pObject = GetInfoObject();

	for (int i = 0; i < AMOUNT_OBJECT; i++, pObject++)
	{
		if (pObject->param.HP <= 0)
		{ // 破壊されていればコンティニュー
			continue;
		}

		if (pObject->type == 9 ||
			pObject->type == 10)
		{ // このモデルが道路の場合はコンティニュー
			continue;
		}

		// 当たり判定を実行、移動を補正
		CollisionVecSphAABB(id, g_Player[id].pos, g_Player[id].param.rad, pObject->model.aabb);
	}
}

//************************************************
// プレイヤーの攻撃
//************************************************
void AtkPlayer(int id)
{
	if (!g_Player[id].use)
	{ // 未使用ならリターン
		return;
	}

	if (g_Player[id].param.state == stateDead_p ||
		g_Player[id].param.HP <= 0)
	{ // 死亡状態ならリターン
		return;
	}	

	// 武器ごとの動作を行う
	switch (g_Player[id].param.weapon)
	{
	case styleGun:

		if (!g_Player[id].PFW.empty)
		{ // 残弾があれば

			// 攻撃ボタン押下で発射準備
			if (GetPressTriggerButtonR(id))
			{
				g_Player[id].PFW.CT_input++;	// キャスト
			}
			else
			{
				// 押下でなければ、即射出されるようにする
				g_Player[id].PFW.CT_input = 14;
			}

			if (g_Player[id].PFW.CT_input >= 15)
			{ // 発射キャスト完了で

				CreateBullet(bulletPlayer, id);	// 弾を生成
				
				RotatePFW3(id, -0.1f);	// 歯車回転

				g_Player[id].PFW.magazine--;	// 弾を消費

				if (g_Player[id].PFW.magazine <= 0)
				{ // 残弾が無くなると

					g_Player[id].PFW.empty = true;	// リロードに入る
				}

				g_Player[id].PFW.CT_input = 0;	// キャストをリセット
			}
		}
		else
		{ // 残弾が無ければ

			g_Player[id].PFW.CT_reload++;	// リロード開始

			RotatePFW3(id, 0.1f);	// 歯車回転

			if (g_Player[id].PFW.CT_reload >= 80)
			{ // リロード完了で

				g_Player[id].PFW.magazine = 20;	// 装填 
				g_Player[id].PFW.CT_reload = 0;	// リロードリセット
				g_Player[id].PFW.empty = false;	// 空っぽ判定取り消し
				PlaySound(SOUND_LABEL_PICK_WEAPON);
			}
		}

		break;

	case styleRPG:

		if (!g_Player[id].PFW.empty)
		{ // 残弾があれば

				if (g_Player[id].PFW.CT_recoil > 0)
			{ // 反動の期間があれば

				g_Player[id].PFW.CT_recoil--;	// 反動期間を減少
			}
			else
			{ // 反動期間がなければ

				// 攻撃ボタン押下で発射準備
				if (GetTriggerTriggerButtonR(id))
				{
					CreateBullet(bulletPlayer, id);	// 弾を生成

					RotatePFW3(id, -0.4f);	// 歯車回転

					g_Player[id].PFW.magazine--;	// 残弾消費

					if (g_Player[id].PFW.magazine <= 0)
					{
						g_Player[id].PFW.empty = true;
					}

					g_Player[id].PFW.CT_recoil = 80;	// 反動期間
				}
			}
		}
		else
		{ // 残弾が無ければ

			g_Player[id].PFW.CT_reload++;	// リロード開始

			RotatePFW3(id, 0.01f);	// 歯車回転

			if (g_Player[id].PFW.CT_reload >= 100)
			{ // リロード完了で

				g_Player[id].PFW.magazine = 3;	// 装填 
				g_Player[id].PFW.CT_reload = 0;	// リロードリセット
				g_Player[id].PFW.CT_recoil = 0;	// 反動リセット
				g_Player[id].PFW.empty = false;	// 空っぽ判定取り消し
				PlaySound(SOUND_LABEL_PICK_WEAPON);
			}
		}

		break;

	case styleGut:

		if (!g_Player[id].PFW.empty)
		{ // 残弾があれば

			// 攻撃ボタン押下で発射準備
			if (GetPressTriggerButtonR(id))
			{
				g_Player[id].PFW.CT_input++;	// キャスト
			}
			else
			{
				// 押下でなければ、即射出されるようにする
				g_Player[id].PFW.CT_input = 7;
			}

			if (g_Player[id].PFW.CT_input >= 8)
			{ // 発射キャスト完了で

				CreateBullet(bulletPlayer, id);	// 弾を生成

				RotatePFW3(id, -0.15f);	// 歯車回転

				g_Player[id].PFW.magazine--;	// 弾を消費

				if (g_Player[id].PFW.magazine <= 0)
				{ // 残弾が無くなると

					g_Player[id].PFW.empty = true;	// リロードに入る
				}

				g_Player[id].PFW.CT_input = 0;	// キャストをリセット
			}
		}
		else
		{ // 残弾が無ければ

			g_Player[id].PFW.CT_reload++;	// リロード開始

			RotatePFW3(id, 0.01f);	// 歯車回転

			if (g_Player[id].PFW.CT_reload >= GUTRELOAD)
			{ // リロード完了で

				g_Player[id].PFW.magazine = 40;	// 装填 
				g_Player[id].PFW.CT_reload = 0;	// リロードリセット
				g_Player[id].PFW.CT_recoil = 0;	// 反動リセット
				g_Player[id].PFW.empty = false;	// 空っぽ判定取り消し
				PlaySound(SOUND_LABEL_PICK_WEAPON);
			}
		}

		break;

	case styleShot:

		if (!g_Player[id].PFW.empty)
		{ // 残弾があれば

			if (g_Player[id].PFW.CT_recoil > 0)
			{ // 反動の期間があれば

				g_Player[id].PFW.CT_recoil--;	// 反動期間を減少
			}
			else
			{ // 反動期間がなければ

				// 攻撃ボタン押下で発射準備
				if (GetTriggerTriggerButtonR(id))
				{
					CreateBullet(bulletPlayer, id);	// 弾を生成

					RotatePFW3(id, -0.4f);	// 歯車回転

					g_Player[id].PFW.magazine--;	// 残弾消費

					if (g_Player[id].PFW.magazine <= 0)
					{
						g_Player[id].PFW.empty = true;
					}

					g_Player[id].PFW.CT_recoil = 20;	// 反動期間
				}
			}
		}
		else
		{ // 残弾が無ければ

			g_Player[id].PFW.CT_reload++;	// リロード開始

			RotatePFW3(id, 0.01f);	// 歯車回転

			if (g_Player[id].PFW.CT_reload >= 100)
			{ // リロード完了で

				g_Player[id].PFW.magazine = 7;	// 装填 
				g_Player[id].PFW.CT_reload = 0;	// リロードリセット
				g_Player[id].PFW.empty = false;	// 空っぽ判定取り消し
				PlaySound(SOUND_LABEL_PICK_WEAPON);
			}
		}

		break;
	}

#ifdef _DEBUG

	/*---【デバッグ表示】---*/
	PrintDebugProc("\n━━━━━━━━━━━━━━\n");
	PrintDebugProc("残弾数：%d\n", g_Player[id].PFW.magazine);
	PrintDebugProc("押下CT：%d\n", g_Player[id].PFW.CT_input);
	PrintDebugProc("リロードCT：%d\n", g_Player[id].PFW.CT_reload);
	const char* unko = nullptr;
	g_Player[id].PFW.empty ? unko = "[ empty ]" : unko = "オウケイ";
	PrintDebugProc("空判定：%s\n", unko);
	PrintDebugProc("━━━━━━━━━━━━━━\n\n");

	if (GetKeyboardPress(DIK_SPACE))
	{
		CreateBullet(bulletPlayer, id);
	}

#endif	// _DEBUG
}

//************************************************
// プレイヤーの被弾時
//************************************************
void HitPlayer(int id)
{
	// 被弾状態でなければ被弾
	g_Player[id].param.state = stateDamage_p;	// 負傷状態に
	g_Player[id].param.motion_now = 3;			// 被弾モーション
	g_Player[id].motion[3].id_frame = 0;		// フレームをリセット
	g_Player[id].motion[3].id_key = 0;			// キーをリセット
	g_Player[id].param.dur = 100;				// 継続時間
	g_Player[id].param.HP--;

	// 画面の振動
	VibCamera(id);

	// 被弾エフェクト
	if (g_Player[id].param.HP > 0)
	{
		PlaySound(SOUND_LABEL_PLAYERHIT);
		CreateEffect_Heart(&g_Player[id].pos);
	}
	else
	{
		PlaySound(SOUND_LABEL_PLAYERDEAD);
		CreateEffect_Soul(&g_Player[id].pos);
	}
}

//************************************************
// プレイヤー負傷
//************************************************
void DamagePlayer(int id)
{
	if (g_Player[id].param.state != stateDamage_p)
	{ // 負傷状態でなければ終了
		return;
	}

	/*---【以下負傷状態時のみ】---*/

	// 点滅
	//g_Player[id].col.a *= -1.0f;

	if(CntDuration(&g_Player[id].param.dur))
	{
		//g_Player[id].col.a = 1.0f;					// 通常色に
		g_Player[id].param.state = stateNormal_p;	// 通常状態に
	}
}

//************************************************
// プレイヤー死亡判定
//************************************************
void DeadPlayer(int id)
{
	if (g_Player[id].param.HP <= 0 &&
		g_Player[id].param.state != stateDead_p)
	{ // ライフが無くなり、死亡状態で無い場合
		int* score = GetInfoScore();
		*score -= 100;
		/*---【せっかくなので復活時もモーション】---*/
		g_Player[id].motion[3].id_frame = 0;	// フレームをリセット
		g_Player[id].motion[3].id_key = 0;		// キーをリセット

		g_Player[id].param.state = stateDead_p;	// 死亡状態に
		g_Player[id].param.dur = 360;			// 適当にクールタイム
	}

	if (g_Player[id].param.state == stateDead_p)
	{
		g_Player[id].param.dur--;	// 適当に減少

		// 黒煙を出す
		if (g_Player[id].param.dur % 5 == 0)
		{
			CreateEffect_Smoke(0, &g_Player[id].pos);
		}
	}
}

//************************************************
// プレイヤー復活判定
//************************************************
void ResurrectPlayer(int id)
{
	if (g_Player[id].param.state == stateDead_p &&
		g_Player[id].param.dur <= 0)
	{ // 死亡状態で、その継続時間が無くなると

		g_Player[id].param.state = stateNormal_p;
		g_Player[id].param.HP = 3;
	}
}

//************************************************
// プレイヤーのモーション管理
//************************************************
void MotionPlayer(int id)
{
	if (!g_Player[id].use)
	{ // 未使用ならリターン
		return;
	}

	if (g_Player[id].param.state == stateDead_p)
	{ // 死亡状態ならリターン
		return;
	}

	// 再生情報格納用
	int* pNow = &g_Player[id].param.motion_now;				// 現在のモーション種類
	int* pOld = &g_Player[id].param.motion_old;				// 過去のモーション種類
	PlayerMotion* pMotion = &g_Player[id].motion[*pNow];	// 各プレイヤーのモーション情報

	// 変更を検知
	ChangeMotionPlayer(id, pNow, pOld);

	// パーツの動作
	MoveMotionPlayer(id, pMotion);

	// フレームカウント
	CntMotionPlayer(id, pMotion);
}

//************************************************
// プレイヤーのモーション変更検知
//************************************************
void ChangeMotionPlayer(int id, int* pNow, int* pOld)
{
	if (*pOld == *pNow)
	{ // 過去と現在の再生モーションが同じならリターン
		return;
	}

	// 過去のモーションのキーとフレームをリセット
	g_Player[id].motion[*pOld].id_key = 0;
	g_Player[id].motion[*pOld].id_frame = 0;

	// 新しいモーションへ移ったことを保存
	*pOld = *pNow;
}

//************************************************
// プレイヤーのモーション動作用
//************************************************
void MoveMotionPlayer(int id, PlayerMotion* pMotion)
{
	// 再生中のキーの総フレーム数から現在のフレーム番号を差し引く
	float dest = (float)(pMotion->key[pMotion->id_key].amount_frame - pMotion->id_frame);

	/*---【動作が必要な土台パーツのみモーションを反映】---*/
	g_Player[id].parts[0].pos_moved += (pMotion->key[pMotion->id_key].dest[0].pos - g_Player[id].parts[0].pos_moved) / dest;
	g_Player[id].parts[0].rot_moved += (pMotion->key[pMotion->id_key].dest[0].rot - g_Player[id].parts[0].rot_moved) / dest;
}

//************************************************
// プレイヤーのモーションカウント用
//************************************************
void CntMotionPlayer(int id, PlayerMotion* pMotion)
{		
	// フレームカウント
	pMotion->id_frame++;

	if (pMotion->id_frame >= pMotion->key[pMotion->id_key].amount_frame)
	{ // 再生中のキーの総フレーム分経過で

		// フレーム番号をリセットし
		pMotion->id_frame = 0;
		
		// キーカウント
		pMotion->id_key++;

		if (pMotion->id_key >= pMotion->amount_key)
		{ // 再生中のモーションの総キー数経過で

			if (pMotion->loop == 1)
			{ // ループフラグが有るなら

				// キー番号リセットしリターン
				pMotion->id_key = 0;
				return;
			}

			/*---【未定、試験的に待機モーション戻す】---*/
			g_Player[id].param.motion_now = 0;
		}
	}
}

//************************************************
// プレイヤー用のワールドマトリックスを計算
//************************************************
void CalcMtxPlayer(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	
	// 下のfor文の最大数を参加人数に変更しています(葛西)
	for (int P_id = 0; P_id < g_nNumPlayer; P_id++)
	{
		if (!g_Player[P_id].use)
		{ // この番使用フラグ無しでコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player[P_id].mtxWorld);

		// 向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Player[P_id].rot.y,
			g_Player[P_id].rot.x,
			g_Player[P_id].rot.z);

		// 向きを反映2
		D3DXMatrixMultiply(&g_Player[P_id].mtxWorld,
			&g_Player[P_id].mtxWorld,
			&mtxRot);

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_Player[P_id].pos.x,
			g_Player[P_id].pos.y,
			g_Player[P_id].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_Player[P_id].mtxWorld,
			&g_Player[P_id].mtxWorld,
			&mtxTrans);

		for (int Ps_id = 0; Ps_id < AMOUNT_PLAYER_PARTS; Ps_id++)
		{
			if (g_Player[P_id].parts[Ps_id].pMesh == NULL)
			{ // 未使用ならコンティニュー
				continue;
			}

			// この番パーツの「親パーツ」のインデックスを保存
			int IdxParent = g_Player[P_id].parts[Ps_id].IdxParent;

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Player[P_id].parts[Ps_id].mtxWorld);

			// モーション向きの反映
			D3DXVECTOR3 PartsRot =
			{
				g_Player[P_id].parts[Ps_id].rot_offset.x + g_Player[P_id].parts[Ps_id].rot_moved.x,
				g_Player[P_id].parts[Ps_id].rot_offset.y + g_Player[P_id].parts[Ps_id].rot_moved.y,
				g_Player[P_id].parts[Ps_id].rot_offset.z + g_Player[P_id].parts[Ps_id].rot_moved.z
			};

			if (IdxParent == 0)
			{ // この番の親パーツが「土台パーツ」であれば、移動方向への回転を打ち消す(砲塔が常に視点方向を向くため)
				PartsRot -= g_Player[P_id].rot;
			}

			// 向きを反映1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				PartsRot.y,
				PartsRot.x,
				PartsRot.z);

			// 向きを反映2
			D3DXMatrixMultiply(&g_Player[P_id].parts[Ps_id].mtxWorld,
				&g_Player[P_id].parts[Ps_id].mtxWorld,
				&mtxRot);

			// モーション位置の反映
			D3DXVECTOR3 PartsPos =
			{
				g_Player[P_id].parts[Ps_id].pos_offset.x + g_Player[P_id].parts[Ps_id].pos_moved.x,
				g_Player[P_id].parts[Ps_id].pos_offset.y + g_Player[P_id].parts[Ps_id].pos_moved.y,
				g_Player[P_id].parts[Ps_id].pos_offset.z + g_Player[P_id].parts[Ps_id].pos_moved.z
			};

			// 位置を反映1
			D3DXMatrixTranslation(&mtxTrans,
				PartsPos.x,
				PartsPos.y,
				PartsPos.z);

			// 位置を反映
			D3DXMatrixMultiply(&g_Player[P_id].parts[Ps_id].mtxWorld,
				&g_Player[P_id].parts[Ps_id].mtxWorld,
				&mtxTrans);

			D3DXMATRIX mtxParent = {};

			// 親のワールドマトリックスを取得
			if (IdxParent == -1)
			{ // 土台パーツのみワールド座標に直結
				mtxParent = g_Player[P_id].mtxWorld;
			}
			else if (IdxParent == 99)
			{ // ユニパーツは各プレイヤーの体のパーツに付随
				mtxParent = g_Player[P_id].parts[P_id + 1].mtxWorld;
			}
			else
			{ // 体のパーツは土台に付随
				mtxParent = g_Player[P_id].parts[IdxParent].mtxWorld;
			}

			// パーツごとのワールドマトリックスを算出
			D3DXMatrixMultiply(&g_Player[P_id].parts[Ps_id].mtxWorld,
				&g_Player[P_id].parts[Ps_id].mtxWorld,
				&mtxParent);
		}

		// (かなり無理のある) 攻撃位置の設定 (仮)
		for (int weapon_id = 0; weapon_id < Max_itemstyle; weapon_id++)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Player[P_id].offset_atk[weapon_id].mtx);

			// 位置を反映1
			D3DXMatrixTranslation(&mtxTrans,
				g_Player[P_id].offset_atk[weapon_id].pos.x,
				g_Player[P_id].offset_atk[weapon_id].pos.y,
				g_Player[P_id].offset_atk[weapon_id].pos.z);

			// 位置を反映
			D3DXMatrixMultiply(&g_Player[P_id].offset_atk[weapon_id].mtx,
				&g_Player[P_id].offset_atk[weapon_id].mtx,
				&mtxTrans);

			// 付随するであろう武器のマトリックスと強引にかけ合わせる…
			D3DXMatrixMultiply(&g_Player[P_id].offset_atk[weapon_id].mtx,
				&g_Player[P_id].offset_atk[weapon_id].mtx,
				&g_Player[P_id].parts[weapon_id + 5].mtxWorld);
		}
	}
}

//************************************************
// プレイヤー描画
//************************************************
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;							// マテリアルデータへのポインタ

	// 下のfor文の最大数を参加人数に変更しています(葛西)
	for (int id_P = 0; id_P < g_nNumPlayer; id_P++)
	{
		if (!g_Player[id_P].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player[id_P].mtxWorld);

		for (int id_Ps = 0; id_Ps < AMOUNT_PLAYER_PARTS; id_Ps++)
		{
			if (g_Player[id_P].parts[id_Ps].pMesh == NULL)
			{ // 空っぽならコンティニュー
				continue;
			}

			if (g_Player[id_P].param.state == stateDead_p)
			{ // 死亡状態のとき

				if (id_Ps != 9)
				{ // 墓以外のパーツを描画しない
					continue;
				}
			}
			else
			{ // 生存状態の時

				if (id_Ps == 9)
				{ // 墓を描画しない
					continue;
				}
			}

			if (g_Player[id_P].parts[id_Ps].style == 99 &&
				g_Player[id_P].parts[id_Ps].IdxParent == 99 &&
				g_Player[id_P].param.weapon != g_PlayerModel[id_Ps].weapon)
			{ // ユニパーツの場合、武器の識別をスタイルが異なるとコンティニュー
				continue;
			}

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Player[id_P].parts[id_Ps].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Player[id_P].parts[id_Ps].pBuffMat->GetBufferPointer();

			for (int id_mat = 0; id_mat < (int)g_Player[id_P].parts[id_Ps].NumMat; id_mat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[id_mat].MatD3D);

				// テクスチャの設定
				if (g_Player[id_P].parts[id_Ps].pTex[id_mat] != NULL)
				{
					pDevice->SetTexture(0, g_Player[id_P].parts[id_Ps].pTex[id_mat]);
				}
				else
				{
					pDevice->SetTexture(0, NULL);
				}

				// モデルパーツの描画
				g_Player[id_P].parts[id_Ps].pMesh->DrawSubset(id_mat);
			}

			// 保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//************************************************
// 拡散光を変更
//************************************************
void ChangeDiffuseColPlayer(int player_id, int parts_id, int mat_id, D3DXMATERIAL * pMat)
{
	if (parts_id == 0)
	{ // プレイヤー本体のキャタピラパーツの色を変える…？
		switch (player_id)
		{
			// 緑
		case 0:
			pMat[mat_id].MatD3D.Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			break;

			// 赤
		case 1:
			pMat[mat_id].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			break;

			// 青
		case 2:
			pMat[mat_id].MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			break
				;
			// 黄
		case 3:
			pMat[mat_id].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			break;
		}
	}
}

//************************************************
// プレイヤー情報を取得
//************************************************
Player* GetInfoPlayer(void)
{
	return &g_Player[0];
}

//************************************************
// デバッグ表示
//************************************************
void PrintDebugPlayer(void)
{
#ifdef _DEBUG

	Player* pPlayer;
	char pStr[8];

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		pPlayer = &g_Player[i];

		switch (pPlayer->param.state)
		{
		case stateNormal_p:
			snprintf(&pStr[0], 8, "通常");
			break;

		case stateMove_p:
			snprintf(&pStr[0], 8, "移動");
			break;

		case stateAtk_p:
			snprintf(&pStr[0], 8, "攻撃");
			break;

		case stateDamage_p:
			snprintf(&pStr[0], 8, "被弾");
			break;

		case stateDead_p:
			snprintf(&pStr[0], 8, "死亡");
			break;

		default:

			// エラー
			assert(false && "いずれかのプレイヤー状態にエラー");

			break;
		}

		PrintDebugProc("【%dP】\nstate : %s\n", i, &pStr[0]);	// ステータス
		PrintDebugProc("HP : %d\n", pPlayer->param.HP);			// 体力
		PrintDebugProc("SPD : %f\n", pPlayer->param.SPD);		// 速度
	}

#endif	// _DEBUG
}

//************************************************
// 攻撃時の反動
//************************************************
//void RecoilPlayer(int id)
//{
//
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// プレイヤー用モデルのクリア
//************************************************
void ClearInfoPlayerModel(void)
{
	PlayerModel* pModel = &g_PlayerModel[0];
	
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++, pModel++)
	{
		pModel->style = 0;
		pModel->weapon = 0;
		pModel->pMesh = NULL;
		pModel->pBuffMat = NULL;
		pModel->NumMat = 0;
		pModel->pos_offset = { 0.0f, 0.0f, 0.0f };
		pModel->pos_moved = { 0.0f, 0.0f, 0.0f };
		pModel->rot_offset = { 0.0f, 0.0f, 0.0f };
		pModel->rot_moved = { 0.0f, 0.0f, 0.0f };

		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			pModel->pTex[j] = NULL;
		}

		pModel->IdxParent = 0;
	}
}

//************************************************
// プレイヤー用モーションのクリア
//************************************************
void ClearInfoPlayerMotion(void)
{
	PlayerMotion* pMotion = &g_PlayerMotion[0];

	for (int i = 0; i < 8; i++, pMotion++)
	{
		pMotion->loop = 0;
		pMotion->amount_key = 0;
		pMotion->id_key = 0;
		pMotion->id_frame = 0;

		for (int j = 0; j < 16; j++)
		{
			pMotion->key[j].amount_frame = 0;

			for (int k = 0; k < AMOUNT_PLAYER_PARTS; k++)
			{
				pMotion->key[j].dest[k].pos = { 0.0f, 0.0f, 0.0f };
				pMotion->key[j].dest[k].rot = { 0.0f, 0.0f, 0.0f };
			}
		}
	}
}

//************************************************
// プレイヤー情報のクリア
//************************************************
void ClearInfoPlayer(void)
{
	Player* pPlayer = &g_Player[0];

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		pPlayer->use = false;
		pPlayer->param = { 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 0 };	// メンバー情報はヘッダファイルを確認して下さい
		pPlayer->PFW = { 0, 0, 0, 0, true };	// メンバー(ry
		pPlayer->pos = { 0.0f, 0.0f, 0.0f };
		pPlayer->pos_old = { 0.0f, 0.0f, 0.0f };
		pPlayer->move = { 0.0f, 0.0f, 0.0f };
		pPlayer->rot = { 0.0f, 0.0f, 0.0f };
		pPlayer->rot_goal = { 0.0f, 0.0f, 0.0f };
		pPlayer->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		for (int j = 0; j < Max_itemstyle; j++)
		{
			pPlayer->offset_atk[j].pos = { 0.0f, 0.0f, 0.0f };
		}

		for (int j = 0; j < AMOUNT_PLAYER_PARTS; j++)
		{
			pPlayer->parts[j].style = 0;
			pPlayer->parts[j].weapon = 0;
			pPlayer->parts[j].pMesh = NULL;
			pPlayer->parts[j].pBuffMat = NULL;
			pPlayer->parts[j].NumMat = 0;
			pPlayer->parts[j].pos_offset = { 0.0f, 0.0f, 0.0f };
			pPlayer->parts[j].pos_moved = { 0.0f, 0.0f, 0.0f };
			pPlayer->parts[j].rot_offset = { 0.0f, 0.0f, 0.0f };
			pPlayer->parts[j].rot_moved = { 0.0f, 0.0f, 0.0f };

			for (int k = 0; k < AMOUNT_MAT; k++)
			{
				pPlayer->parts[j].pTex[k] = NULL;
			}

			pPlayer->parts[j].IdxParent = 0;
		}

		pPlayer->id_shadow = 0;
		pPlayer->id_sph = 0;
	}
}