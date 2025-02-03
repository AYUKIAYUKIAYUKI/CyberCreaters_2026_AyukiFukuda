//************************************************
//
//敵生成[enemy.cpp]
//Author：福田歩希
//
//************************************************
#include "enemy.h"

#include <assert.h>
#include "debugproc.h"
#include "sound.h"

#include "bullet.h"
#include "collision.h"
#include "model.h"
#include "particle.h"
#include "player.h"
#include "score.h"
#include "shadow.h"
#include "tutorialdesign.h"
#include "visible_sphere.h"

//グローバル宣言
LPD3DXMESH g_pMeshEnemy[AMOUNT_ENEMY_PARTS];	//メッシュのポインタ
LPD3DXBUFFER g_pBuffMatEnemy[AMOUNT_ENEMY_PARTS];	//マテリアルのポインタ
DWORD g_dwNumMatEnemy[AMOUNT_ENEMY_PARTS];	//マテリアルの数
Enemy g_aEnemy[AMOUNT_ENEMY] = {};
int g_nCastSpawn = 0;	//敵スポーン間隔管理

//************************************************
//敵初期
//************************************************
void InitEnemy(void)
{
	//モデル用情報を初期化
	for (int i = 0; i < AMOUNT_ENEMY_PARTS; i++)
	{
		g_pMeshEnemy[i] = NULL;	//メッシュ情報のポインタををクリア
		g_pBuffMatEnemy[i] = NULL;	//マテリアル情報のポインタをクリア
		g_dwNumMatEnemy[i] = 0;	//マテリアルの数をクリア
	}

	//敵用の情報を初期化
	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		g_aEnemy[i].bUse = false;
		g_aEnemy[i].nState = EnemyStateNormal;
		g_aEnemy[i].bATK = false;
		g_aEnemy[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEnemy[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].fRadius = 0.0f;
		g_aEnemy[i].nLife = 0;
		g_aEnemy[i].nCntState = 0;
		/* パーツ情報クリア */
		for (int j = 0; j < AMOUNT_ENEMY_PARTS; j++)
		{
			g_aEnemy[i].aParts[j].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[i].aParts[j].posM = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[i].aParts[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[i].aParts[j].rotM = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[i].aParts[j].nIdxParent = 0;
		}
		/* モーション情報クリア */
		for (int j = 0; j < AMOUNT_ENEMY_MOTION; j++)
		{
			g_aEnemy[i].motion[j].nIdxKey = 0;
			g_aEnemy[i].motion[j].nLoop = 0;
			g_aEnemy[i].motion[j].nNumKey = 0;
			g_aEnemy[i].motion[j].nFrameCnt = 0;

			for (int k = 0; k < AMOUNT_ENEMY_KEY; k++)
			{
				g_aEnemy[i].motion[j].key[k].nFrame = 0;

				for (int l = 0; l < AMOUNT_ENEMY_PARTS; l++)
				{
					g_aEnemy[i].motion[j].key[j].parts[l].posGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					g_aEnemy[i].motion[j].key[j].parts[l].rotGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
		}
		g_aEnemy[i].nNowMotion = EnemyMotionStateNormal;
		g_aEnemy[i].nOldMotion = EnemyMotionStateNormal;
	}

	//敵スポーン間隔クリア
	g_nCastSpawn = 0;

	//モデルパーツの設定
	SetInfoPartsEnemy();

	//モーションの設定
	SetInfoMotionEnemy();
}

//************************************************
//モデルパーツ情報を設定
//************************************************
void SetInfoPartsEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//パーツ用情報を設定
	FILE* pFile = NULL;
	char sEnemyModel[64] = {};

	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		//パーツ間オフセットの読込み
		if (fopen_s(&pFile, "data\\txt\\enemymodelset.txt", "r") != 0) return;

		/* モデルパーツの総数以上ループで終了 */
		for (int j = 0; j < AMOUNT_ENEMY_PARTS; j++)
		{
			fscanf_s(pFile, "%d", &g_aEnemy[i].aParts[j].nIdxParent);
			fscanf_s(pFile, "%f %f %f", &g_aEnemy[i].aParts[j].pos.x, &g_aEnemy[i].aParts[j].pos.y, &g_aEnemy[i].aParts[j].pos.z);
			fscanf_s(pFile, "%f %f %f", &g_aEnemy[i].aParts[j].rot.x, &g_aEnemy[i].aParts[j].rot.y, &g_aEnemy[i].aParts[j].rot.z);
		}

		fclose(pFile);

		/**********************************************************/

		//Xファイルの読み込み
		if (fopen_s(&pFile, "data\\txt\\enemymodel.txt", "r") != 0) return;

		int j = 0;

		/* ファイルの終端に着くか、モデルパーツの総数以上ループで終了 */
		while (fscanf_s(pFile, "%s", &sEnemyModel[0], 64) != EOF || j < AMOUNT_ENEMY_PARTS)
		{
			D3DXLoadMeshFromX(&sEnemyModel[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pBuffMatEnemy[j],
				NULL,
				&g_dwNumMatEnemy[j],
				&g_pMeshEnemy[j]);

			j++;
		}

		fclose(pFile);
	}
}

//************************************************
//モーション情報を設定(要改善)
//************************************************
void SetInfoMotionEnemy(void)
{
	//モーション用情報を設定
	FILE* pFile = NULL;
	char sEnemyMotion[128] = {};

	for (int nCntEnemy = 0; nCntEnemy < AMOUNT_ENEMY; nCntEnemy++)
	{
		Enemy* thisEnemy = &g_aEnemy[nCntEnemy];

		if (fopen_s(&pFile, "data\\txt\\enemykeyset.txt", "r") == 0)
		{
			int i = 0;	/* nStyle管理 */

			/* ファイルの終端に着くまでループ */
			while (fscanf_s(pFile, "%s", &sEnemyMotion[0], 128) != EOF)
			{
				if (strcmp(&sEnemyMotion[0], "LOOP") == 0)
				{
					fscanf_s(pFile, "%s %d", &sEnemyMotion[0], 64, &thisEnemy->motion[i].nLoop);
				}
				if (strcmp(&sEnemyMotion[0], "NUM_KEY") == 0)
				{
					fscanf_s(pFile, "%s %d", &sEnemyMotion[0], 64, &thisEnemy->motion[i].nNumKey);

					/* キー数を取得したので、キー数分のフレームも取得 */
					for (int j = 0; j < thisEnemy->motion[i].nNumKey; fscanf_s(pFile, "%s", &sEnemyMotion[0], 128))
					{
						if (strcmp(&sEnemyMotion[0], "FRAME") == 0)
						{
							fscanf_s(pFile, "%s %d", &sEnemyMotion[0], 64, &thisEnemy->motion[i].key[j].nFrame);

							/* フレーム数を取得したので、パーツ数分の目的地も取得 */
							for (int k = 0; k < AMOUNT_ENEMY_PARTS; fscanf_s(pFile, "%s", &sEnemyMotion[0], 128))
							{
								if (strcmp(&sEnemyMotion[0], "POS") == 0)
								{
									fscanf_s(pFile, "%s %f %f %f", &sEnemyMotion[0], 64, &thisEnemy->motion[i].key[j].parts[k].posGoal.x, &thisEnemy->motion[i].key[j].parts[k].posGoal.y, &thisEnemy->motion[i].key[j].parts[k].posGoal.z);
									fscanf_s(pFile, "%s", &sEnemyMotion[0], 64);
									fscanf_s(pFile, "%s %f %f %f", &sEnemyMotion[0], 64, &thisEnemy->motion[i].key[j].parts[k].rotGoal.x, &thisEnemy->motion[i].key[j].parts[k].rotGoal.y, &thisEnemy->motion[i].key[j].parts[k].rotGoal.z);

									k++;
								}
							}

							j++;

							/* 全てのキーを読み込むと、次のモーションを読み込む */
							if (j >= thisEnemy->motion[i].nNumKey)
							{
								i++;
							}
						}
					}
				}
			}

			fclose(pFile);
		}
	}
}

//************************************************
//敵破棄
//************************************************
void UninitEnemy(void)
{
	//マテリアルの破棄
	for (int i = 0; i < AMOUNT_ENEMY_PARTS; i++)
	{
		if (g_pBuffMatEnemy[i] != NULL)
		{
			g_pBuffMatEnemy[i]->Release();
			g_pBuffMatEnemy[i] = NULL;
		}
	}

	//メッシュの破棄
	for (int i = 0; i < AMOUNT_ENEMY_PARTS; i++)
	{
		if (g_pMeshEnemy[i] != NULL)
		{
			g_pMeshEnemy[i]->Release();
			g_pMeshEnemy[i] = NULL;
		}
	}
}

//************************************************
//敵セット
//************************************************
void SetInfoEnemy(void)
{
	//スポーン地点ランダム設定
	Model* pModel = GetInfoModel();
	D3DXVECTOR3 Spawn = {};
	int nIdx = 0;
	
	nIdx = rand() % 4;
	Spawn = pModel[nIdx].pos;

	//敵の情報を設定
	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		if (g_aEnemy[i].bUse) continue;

		g_aEnemy[i].bUse = true;
		g_aEnemy[i].nState = EnemyStateNormal;
		g_aEnemy[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEnemy[i].pos = D3DXVECTOR3(Spawn.x, 0.0f, Spawn.z);
		g_aEnemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].fRadius = 10.0f;
		g_aEnemy[i].nLife = 2;
		g_aEnemy[i].nCntState = 0;

		//影をセット
		SetInfoShadow(10.0f, &g_aEnemy[i].pos);

		//当たり判定を可視化
		//SetSizeVisible_Sphere(g_aEnemy[i].fRadius, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), &g_aEnemy[i].pos);

		for (int j = 0; j < 10; j++)
		{
			SetInfoParticle(g_aEnemy[i].pos, D3DXCOLOR(0.5f, 0.5f, 0.0f, 0.9f), 3.0f);
		}

		break;
	}
}

//************************************************
//敵更新
//************************************************
void UpdateEnemy(int mode)
{
	//出現処理
	if (mode == MODE_TUTORIAL)
	{
		bool* pSpawn = GetInfoSpawnEnemy();

		if (*pSpawn)
		{
			for (int i = 0; i < AMOUNT_ENEMY; i++)
			{
				if (g_aEnemy[i].bUse)
				{
					break;
				}

				//1匹も出ていないときのみ
				SpawnEnemy();
			}
		}
	}
	else
	{
		SpawnEnemy();
	}

	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		if (g_aEnemy[i].bUse)
		{
			//弾との当たり判定
			if (g_aEnemy[i].nState != EnemyStateEscape)
			{
				CollisionBullet(CollisionModeEnemy, i);
			}

			//ステータスに応じて行動
			StateEnemy(i, mode);

			//モーション再生
			MotionEnemy(i);

			//攻撃判定が出て入れば判定生成
			if (g_aEnemy[i].bATK)
			{
				SetInfoATK(i);
			}
		}
	}
}

//************************************************
//敵出現
//************************************************
void SpawnEnemy(void)
{
	//スポーンキャスト
	g_nCastSpawn++;

	//キャスト完了で
	if (g_nCastSpawn >= 60)
	{
		g_nCastSpawn = 0;

		//敵セット
		SetInfoEnemy();
	}
}

//************************************************
//敵状態
//************************************************
void StateEnemy(int nCnt, int mode)
{
	bool* pStamp = GetInfoStampEnemy();

	Enemy* Enemy = &g_aEnemy[nCnt];
	Player* pPlayer = GetInfoPlayer();

	float fVecPlayer = atan2f(pPlayer->pos.x - Enemy->pos.x, pPlayer->pos.z - Enemy->pos.z);
	float fAntiVecPlayer = atan2f(-(pPlayer->pos.x - Enemy->pos.x), -(pPlayer->pos.z - Enemy->pos.z));

	switch (Enemy->nState)
	{
		//通常
	case EnemyStateNormal:

		if (Enemy->col.a != 1.0f)
		{
			Enemy->col.a = 1.0f;
		}

		switch (Enemy->nLife)
		{
		case 2:
			Enemy->nState = EnemyStateDash;
			Enemy->nNowMotion = EnemyMotionStateDash;
			break;
		case 1:
			Enemy->nState = EnemyStateEscape;
			Enemy->nNowMotion = EnemyMotionStateDash;
			break;
		default:
			Enemy->nState = EnemyStateDeath;
			break;
		}

		break;

		//ダッシュ
	case EnemyStateDash:

		//どれぐらい近づいてきたのか計算
		if(CollisionSphere(Enemy->pos, Enemy->fRadius, pPlayer->pos, 20.0f))
		{
			Enemy->nState = EnemyStateATK;
			Enemy->nNowMotion = EnemyMotionStateATK;
		}
		else
		{
			//プレイヤーの方向によってくる
			Enemy->move =
			{
				sinf(fVecPlayer),
				0.0f,
				cosf(fVecPlayer)
			};

			if (mode == MODE_TUTORIAL)
			{
				Enemy->move *= 1.0f;
			}
			else
			{
				Enemy->move *= 3.0f;
			}
		}
		Enemy->rot.y = fAntiVecPlayer;

		//どれぐらい近づかれたか計算
		if (pPlayer->bMUKIMUKI)
		{
			if (CollisionSphere(pPlayer->pos, 100.0f, Enemy->pos, Enemy->fRadius))
			{
				Enemy->nState = EnemyStateNormal;
				Enemy->nLife -= 1;
			}
		}

		break;

		//攻撃
	case EnemyStateATK:

		//どれぐらい近づいてきたのか計算
		if (!CollisionSphere(Enemy->pos, Enemy->fRadius, pPlayer->pos, 30.0f))
		{
			//プレイヤーに少し寄ってくる
			Enemy->move =
			{
				sinf(fVecPlayer),
				0.0f,
				cosf(fVecPlayer)
			};

			if (mode == MODE_TUTORIAL)
			{
				Enemy->move *= 0.5;
			}
			else
			{
				Enemy->move *= 1.5f;
			}
		}
		Enemy->rot.y = fAntiVecPlayer;

		//どれぐらい近づかれたか計算
		if (pPlayer->bMUKIMUKI)
		{
			if (CollisionSphere(pPlayer->pos, 15.0f, Enemy->pos, Enemy->fRadius))
			{
				Enemy->nState = EnemyStateNormal;
				Enemy->nLife -= 2;

				for (int i = 0; i < 30; i++)
				{
					SetInfoParticle(Enemy->pos, D3DXCOLOR(0.5f, 0.5f, 0.0f, 0.9f), 7.0f);
				}
			}
		}

		break;

		//逃走
	case EnemyStateEscape:

		//プレイヤーから逃げる
		Enemy->move =
		{
			sinf(fAntiVecPlayer),
			0.0f,
			cosf(fAntiVecPlayer)
		};

		if (mode == MODE_TUTORIAL)
		{
			Enemy->move *= 0.5f;
		}
		else
		{
			Enemy->move *= 1.8f;
		}

		Enemy->rot.y = fVecPlayer;

		//どれぐらい近づかれたか計算
		if (CollisionSphere(pPlayer->pos, 15.0f, Enemy->pos, Enemy->fRadius))
		{
			Enemy->nState = EnemyStateNormal;
			Enemy->nLife--;

			for (int i = 0; i < 30; i++)
			{
				SetInfoParticle(Enemy->pos, D3DXCOLOR(0.5f, 0.5f, 0.0f, 0.9f), 7.0f);
			}

			if (pPlayer->bMUKIMUKI)
			{
				pPlayer->nEnegy += 35;
			}
		}

		break;

		//被弾
	case EnemyStateDamage:

		//無敵時間
		if (Enemy->nCntState >= 0)
		{
			Enemy->nCntState--;
		}
		else
		{
			Enemy->nState = EnemyStateNormal;
		}

		Enemy->col.a *= -1.0f;

		break;

		//死亡
	case EnemyStateDeath:

		//消滅
		DisappearEnemy(nCnt);
		Add_Score(666);

		if (mode == MODE_TUTORIAL)
		{
			*pStamp = true;
		}

		PlaySound(SOUND_LABEL_STAMP);

		break;

		//アクセスエラー
	default:
		assert(false);
		break;
	}

	g_aEnemy[nCnt].move *= 0.8f;	//ブレーキ
	g_aEnemy[nCnt].pos += g_aEnemy[nCnt].move;	//移動速度
}

//************************************************
//敵攻撃判定
//************************************************
void SetInfoATK(int nCnt)
{
	Player* pPlayer = GetInfoPlayer();

	//手元に攻撃
	if (!pPlayer->bMUKIMUKI)
	{
		if (CollisionSphere(pPlayer->pos, 25.0f, g_aEnemy[nCnt].pos, g_aEnemy[nCnt].fRadius))
		{
			pPlayer->move =
			{
				sinf(g_aEnemy[nCnt].rot.y),
				0.0f,
				cosf(g_aEnemy[nCnt].rot.y),
			};

			pPlayer->move *= -30.0f;

			pPlayer->nState = PlayerStateDamage;
			pPlayer->nCntState = 20;

			pPlayer->nEnegy += 15;

			PlaySound(SOUND_LABEL_DAMAGE);
		}
	}

	g_aEnemy[nCnt].bATK = false;
}

//************************************************
//敵消滅
//************************************************
void DisappearEnemy(int nCnt)
{
	//敵用の情報を初期化
	g_aEnemy[nCnt].bUse = false;
	g_aEnemy[nCnt].nState = EnemyStateNormal;
	g_aEnemy[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEnemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEnemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEnemy[nCnt].fRadius = 0.0f;
	g_aEnemy[nCnt].nLife = 0;
	g_aEnemy[nCnt].nCntState = 0;
	g_aEnemy[nCnt].nNowMotion = EnemyMotionStateNormal;
	g_aEnemy[nCnt].nOldMotion = EnemyMotionStateNormal;

	//影にも消滅処理を行う
	DisappearShadow(&g_aEnemy[nCnt].pos);

	//当たり判定可視化にも消滅処理を行う
	//DisappearVisible_Sphere(&g_aEnemy[nCnt].pos);
}

//************************************************
//敵モーション管理
//************************************************
void MotionEnemy(int nCnt)
{
	EnemyMotionSet* Motion = &g_aEnemy[nCnt].motion[g_aEnemy[nCnt].nNowMotion];

	//モーションに変更があるか検知
	MotionChangeEnemy(nCnt);

	//パーツの移動や回転
	MotionMoveEnemy(nCnt, Motion);

	//モーション用の経過カウント
	MotionCountEnemy(nCnt, Motion);
}

//************************************************
//モーション変更
//************************************************
void MotionChangeEnemy(int nCnt)
{
	/* モーションが変更されていれば */
	if (g_aEnemy[nCnt].nOldMotion != g_aEnemy[nCnt].nNowMotion)
		{
		//キーとフレームカウントリセット
		g_aEnemy[nCnt].motion[g_aEnemy[nCnt].nOldMotion].nFrameCnt = 0;
		g_aEnemy[nCnt].motion[g_aEnemy[nCnt].nOldMotion].nIdxKey = 0;

		//新しいモーションを再生したことを保存
		g_aEnemy[nCnt].nOldMotion = g_aEnemy[nCnt].nNowMotion;
	}
}

//************************************************
//モーション用移動
//************************************************
void MotionMoveEnemy(int nCnt, const EnemyMotionSet* Motion)
{
	/* …？(用研究) */
	//float fFrame = (float)(Motion->key[Motion->nIdxKey].nFrame);
	float fFrame = (float)(Motion->key[Motion->nIdxKey].nFrame - Motion->nFrameCnt);

	//目標と現在の差を埋めていく
	for (int j = 0; j < AMOUNT_ENEMY_PARTS; j++)
	{
		g_aEnemy[nCnt].aParts[j].posM += (Motion->key[Motion->nIdxKey].parts[j].posGoal - g_aEnemy[nCnt].aParts[j].posM) / fFrame;
		g_aEnemy[nCnt].aParts[j].rotM += (Motion->key[Motion->nIdxKey].parts[j].rotGoal - g_aEnemy[nCnt].aParts[j].rotM) / fFrame;
	}
}

//************************************************
//モーション用カウント
//************************************************
void MotionCountEnemy(int nCnt, EnemyMotionSet* Motion)
{
	Motion->nFrameCnt++;	/* フレームを進める */

	if (Motion->nFrameCnt >= Motion->key[Motion->nIdxKey].nFrame)	/* 所要フレーム数を経過で */
	{
		Motion->nFrameCnt = 0;
		Motion->nIdxKey++;		/* キーを進める */

		//攻撃モーション中のちょうどいいキーのタイミングで攻撃判定を生成
		if (g_aEnemy[nCnt].nState == EnemyStateATK && Motion->nIdxKey == 10 && !g_aEnemy[nCnt].bATK)
		{
			g_aEnemy[nCnt].bATK = true;
		}

		if (Motion->nIdxKey >= Motion->nNumKey)	/* 所要キーを経過で */
		{
			if (g_aEnemy[nCnt].nState == EnemyStateATK)
			{
				g_aEnemy[nCnt].nState = EnemyStateNormal;
				return;
			}

			if (Motion->nLoop == 1)
			{
				Motion->nIdxKey = 0;
				return;
			}

			g_aEnemy[nCnt].nNowMotion = EnemyMotionStateNormal;
		}
	}
}

//************************************************
//敵描画
//************************************************
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	D3DMATERIAL9 matDef;	//現在のマテリアル保存用

	D3DXMATERIAL* pMat;	//マテリアルデータへのポインタ

	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		if (g_aEnemy[i].bUse)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEnemy[i].mtxWorld);

			//向きを反映1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aEnemy[i].rot.y,
				g_aEnemy[i].rot.x,
				g_aEnemy[i].rot.z);

			//向きを反映2
			D3DXMatrixMultiply(&g_aEnemy[i].mtxWorld,
				&g_aEnemy[i].mtxWorld,
				&mtxRot);

			//位置を反映1
			D3DXMatrixTranslation(&mtxTrans,
				g_aEnemy[i].pos.x,
				g_aEnemy[i].pos.y,
				g_aEnemy[i].pos.z);

			//位置を反映2
			D3DXMatrixMultiply(&g_aEnemy[i].mtxWorld,
				&g_aEnemy[i].mtxWorld,
				&mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[i].mtxWorld);

			for (int j = 0; j < AMOUNT_ENEMY_PARTS; j++)
			{
				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_aEnemy[i].aParts[j].mtxWorld);

				//モーション向きの反映
				D3DXVECTOR3 PartsRot =
				{
					g_aEnemy[i].aParts[j].rot.x + g_aEnemy[i].aParts[j].rotM.x,
					g_aEnemy[i].aParts[j].rot.y + g_aEnemy[i].aParts[j].rotM.y,
					g_aEnemy[i].aParts[j].rot.z + g_aEnemy[i].aParts[j].rotM.z
				};

				//向きを反映1
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					PartsRot.y,
					PartsRot.x,
					PartsRot.z);

				//向きを反映2
				D3DXMatrixMultiply(&g_aEnemy[i].aParts[j].mtxWorld,
					&g_aEnemy[i].aParts[j].mtxWorld,
					&mtxRot);

				//モーション位置の反映
				D3DXVECTOR3 PartsPos =
				{
					g_aEnemy[i].aParts[j].pos.x + g_aEnemy[i].aParts[j].posM.x,
					g_aEnemy[i].aParts[j].pos.y + g_aEnemy[i].aParts[j].posM.y,
					g_aEnemy[i].aParts[j].pos.z + g_aEnemy[i].aParts[j].posM.z
				};

				//位置を反映1
				D3DXMatrixTranslation(&mtxTrans,
					PartsPos.x,
					PartsPos.y,
					PartsPos.z);

				//位置を反映
				D3DXMatrixMultiply(&g_aEnemy[i].aParts[j].mtxWorld,
					&g_aEnemy[i].aParts[j].mtxWorld,
					&mtxTrans);

				D3DXMATRIX mtxParent = {};

				//親のワールドマトリックスを取得
				if (g_aEnemy[i].aParts[j].nIdxParent == -1)
				{
					mtxParent = g_aEnemy[i].mtxWorld;
				}
				else
				{
					mtxParent = g_aEnemy[i].aParts[g_aEnemy[i].aParts[j].nIdxParent].mtxWorld;
				}

				//パーツごとのワールドマトリックスを算出
				D3DXMatrixMultiply(&g_aEnemy[i].aParts[j].mtxWorld,
					&g_aEnemy[i].aParts[j].mtxWorld,
					&mtxParent);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[i].aParts[j].mtxWorld);

				//現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[j]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEnemy[j]; nCntMat++)
				{
					//色を設定
					pMat[nCntMat].MatD3D.Diffuse.a = g_aEnemy[i].col.a;

					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//テクスチャの設定
					pDevice->SetTexture(0, NULL);

					//モデルパーツの描画
					g_pMeshEnemy[j]->DrawSubset(nCntMat);
				}

				//保存していたマテリアルを戻す
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//************************************************
//敵情報を取得
//************************************************
Enemy* GetInfoEnemy(void)
{
	return &g_aEnemy[0];
}