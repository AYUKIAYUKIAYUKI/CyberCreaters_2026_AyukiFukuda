//************************************************
//
// ボス処理[boss.cpp]
// Author：葛西敬介
//
//************************************************

/*/ インクルードファイル /*/
#include "boss.h"
#include "boss_bullet.h"
#include "bullet.h"
#include "collision.h"
#include "explosion.h"
#include "object.h"
#include "player.h"
#include "player_count.h"
#include "visible_sph.h"
#include "shadow.h"
// 中枢
#include "game.h"
#include "input.h"
#include "sound.h"

#include <stdlib.h>
#include <time.h>

// 諸処理
#include "enemy.h"
#ifdef _DEBUG
#include "debugproc.h"
#include <assert.h>
#endif	// _DEBUG

// マクロ定義
#define MAX_DATA			(10)		// ランダムで出た数値格納用
#define STAGE_SIZE			(2000.0f)	// フィールドの大きさ

/*/ グローバル変数 /*/
BOSSModel g_BossModel[AMOUNT_BOSS_PARTS];					// ボス用モデル情報のひな形
BossMotion g_BossMotion[NUM_MOTION];						// ボスモーション情報のひな形
BOSS g_aBoss[MAX_BOSS];										// ボス情報
int g_nCntStop = 0;											// 動かなくさせる時間
int g_nCntRot = 0;											// どっち向きに進むかを決める
int g_nCntPattern = 0;										// 行動パターンを変えるためのフレーム数
int g_nBulletType[MAX_DATA] = {};							// ボスの弾の挙動(調整前)
int g_nBulletNum[MAX_DATA] = {};							// ボスの弾の挙動(調整後)
int g_nAdjustTime = 0;										// 弾の挙動を決めるタイミング
int g_nSetBulletTime = 0;									// 移動時に弾を発射させるタイミング
int g_nBulletTime = 0;										// ボスが被弾をしていないときの弾を発射させるタイミング
int g_nMidBossActionChoice = 0;								// 中ボスの挙動を決めるタイミング
int g_nbossActionPatterns = 0;								// 中ボスの行動パターン格納用
int g_nMidBossBullet = 0;									// 中ボスが弾を発射させるタイミング
int g_nCntTeleport = 0;										// テレポートさせるタイミング
int g_nTimeMidBossExplosion = 0;							// 中ボスが死んだあと爆発させるタイミング
int g_nTimeBigBossExplosion = 0;							// 大ボスが死んだあと爆発させるタイミング
int g_nTeleportLate = 0;									// ボスがテレポートした後の時間
int g_nMidBossPhase = 0;									// 中ボスのフェーズ
D3DXVECTOR3 g_MidBossMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 中ボスの移動量
D3DXVECTOR3 g_BigBossMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 大ボスの移動量
D3DXVECTOR3 g_TeleportPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 中ボスのテレポート先の座標

float g_fStartHP = 0;										// ボスの出現時のHP
float g_fRestHP = 0;										// ボスの残りHP

bool g_bStateChange = false;								// 大ボスが状態変化したかどうか
bool g_bBigBossUse = false;									// 大ボスが生きているかどうか

int g_nCntPlayer = 0;										// ゲームの参加人数

/*---【プロトタイプ宣言】---*/
void SetSizePartsRadBoss();			// 各パーツの判定サイズをセット
void UpdatePartsRadBoss(int id);	// 各パーツの判定を更新

//************************************************
// ボス初期
//************************************************
void InitBoss(void)
{

	//グローバル変数の初期化
	g_nCntStop = 0;									// 敵のスタン時間
	g_MidBossMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 中ボスの加算させる移動量
	g_BigBossMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 大ボスの加算させる移動量
	g_nCntRot = 0;									// どっち向きに進むかを決める用の変数
	g_fStartHP = 0.0f;								// ボスの出現時のHP
	g_fRestHP = 0.0f;								// ボスの残りHP	
	g_bStateChange = false;							// ボスが状態変化したかどうか
	g_nCntPattern = 0;								// 行動パターンを変えるためのフレーム数
	g_nAdjustTime = 0;								// ボスの弾の挙動を決めるタイミング
	g_nSetBulletTime = 0;							// ボスの移動時に弾を発射させるタイミング
	g_bBigBossUse = false;							// 大ボスが生きているかどうか
	g_nBulletTime = 0;								// ボスが被弾していないときに弾を発射させるタイミング
	g_nCntPlayer = 0;								// プレイ人数
	g_nMidBossActionChoice = 0;						// 中ボスの挙動を抽選させるタイミング
	g_nbossActionPatterns = 0;						// 中ボスの行動パターン格納用
	g_nMidBossBullet = 0;							// 中ボスが弾を発射させるタイミング
	g_nCntTeleport = 0;								// テレポートさせるタイミング
	g_nTimeMidBossExplosion = 0;					// 中ボスが死んだあと爆発させる時間
	g_nTimeBigBossExplosion = 0;					// 大ボスが死んだあと爆発させる時間
	g_TeleportPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 中ボスのテレポート先の座標
	g_nTeleportLate = 0;							// 中ボスがテレポートした後の時間
	g_nMidBossPhase = 0;							// 中ボスのフェーズ

	// プレイ人数の取得
	g_nCntPlayer = ReturnSelectPlayerCount() + 1;

	for (int i = 0; i < MAX_DATA; i++)
	{
		g_nBulletType[i] = {};								// ボスの弾の挙動(調整前)
		g_nBulletNum[i] = {};								// ボスの弾の挙動(調整後)
	}

	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{ // ボス用モデル情報のひな形のリセット
		BOSSModel* pModel = &g_BossModel[i];

		// スタイル
		pModel->style = 0;

		// モデル
		pModel->pMesh = NULL;
		pModel->pBuffMat = NULL;
		pModel->NumMat = 0;

		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // マテリアル
			pModel->pTex[j] = NULL;
		}

		// モデル座標
		pModel->pos_offset = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 親インデックス
		pModel->IdxParent = -1;
	}

	/*--------------------------------------------*/

	for (int i = 0; i < MAX_BOSS; i++)
	{ // ボス情報のリセット
		BOSS* pBoss = &g_aBoss[i];

		// 使用フラグ
		pBoss->use = false;

		// パラメータ
		pBoss->Param.style = 0;								//番号
		pBoss->Param.state = stateNormal_b;					//状態
		pBoss->Param.dur = 0;								//HPがなくなってから描画されなくなるまでの時間
		pBoss->Param.HP = 0;								//ライフ
		pBoss->Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
		//pBoss->Param.Radius = 0.0f;							//当たり判定の半径
		pBoss->Param.motion_now = 0;						//今再生中のモーション
		pBoss->Param.motion_old = 0;						//1つ前に再生されていたモーション
		//pBoss->Param.bMove = true;							//移動しているかどうか

		// 座標
		pBoss->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 色
		pBoss->col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		for (int j = 0; j < AMOUNT_BOSS_PARTS; j++)
		{ // 各パーツ情報をリセット
			BOSSModel* pModel = &pBoss->parts[j];

			// モデル
			pModel->pMesh = NULL;
			pModel->pBuffMat = NULL;
			pModel->NumMat = 0;

			for (int k = 0; k < AMOUNT_MAT; k++)
			{ // マテリアル
				pModel->pTex[k] = NULL;
			}

			// モデル座標
			pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 親インデックス
			pModel->IdxParent = -1;

			// 判定用情報をリセット
			pBoss->rad[j] = 0.0f;
			pBoss->pos_sph[j] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pBoss->id_sph[j] = -1;
		}

		pBoss->id_shadow = -1;
	}

	/*--------------------------------------------*/

	// ボス用のモデル情報を取得
	ImportModelBoss();

	// ボス用のモーション情報を取得
	ImportMotionBoss();

	// ボス用のパラメータ情報を取得
	ImportParamBoss();

	/*---【モーション情報をコピー(修正予定)】---*/
	for (int i = 0; i < MAX_BOSS; i++)
	{
		for (int j = 0; j < NUM_MOTION; j++)
		{
			if (g_BossMotion[j].amount_key == 0)
			{ // 未使用ならコンティニュー
				continue;
			}

			// モーション情報をコピー
			g_aBoss[i].motion[j] = g_BossMotion[j];
		}


	}

	for (int i = 0; i < MAX_BOSS; i++)
	{
		g_aBoss[i].Param.bMove = true;		// 移動しているかどうか
		g_fStartHP = g_aBoss[i].Param.HP;	// 出現時のHPを保存する
	}

	// 中ボスの挙動の算出
	g_nbossActionPatterns = rand() % NUM_ACT;

	/******************************/

	/*---【試験的に敵を配置(消去予定)】---*/

	//DEBUG_GenerateEnemy();

	/******************************/
}

//************************************************
// モデル情報を読み込む
//************************************************
void ImportModelBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int AmountModel = 0;		// モデルの数を格納
	int id_Model = 0;			// モデルの識別用

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\BOSS\\boss_model.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "ボスモデル情報の展開に失敗");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "AMOUNT_MODEL") == 0)
		{
			// 読み込むモデル数を取得する
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &AmountModel);
		}

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// 読み込むモデル名を取得する
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%s", &FileString[0], 128);

			// 読み込んだ情報をひな形にのみコピーする
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_BossModel[id_Model].pBuffMat,
				NULL,
				&g_BossModel[id_Model].NumMat,
				&g_BossModel[id_Model].pMesh);

			id_Model++; // パーツを進める

			if (id_Model == AmountModel)
			{ // モデル数分読み取り終わると終了
				break;
			}
		}
	}

	// 各モデルのオフセット情報を取得
	ImportOffsetBoss(pFile, AmountModel);

	// 各モデルのテクスチャ情報を取得
	ImportTexBoss(AmountModel);

	// ファイルを閉じる
	fclose(pFile);
}

//************************************************
// モデルオフセット情報を読み込む
//************************************************
void ImportOffsetBoss(FILE* pFile, int AmountModel)
{
	// ファイルデータ読込み用
	char FileString[128] = {};	// 文章を格納
	int Style = -1;				// このパーツのスタイルを格納
	int IdxParent = -1;			// 親のインデックスを格納
	D3DXVECTOR3 pos = {};		// 位置のオフセットを格納
	D3DXVECTOR3 rot = {};		// 向きのオフセットを格納
	int id_Model = 0;			// モデルの識別用

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // このパーツのスタイルを取得	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &Style);
		}

		if (strcmp(&FileString[0], "PARENT") == 0)
		{ // 親のインデックスを取得	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &IdxParent);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // 位置のオフセットを取得	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // 向きのオフセットを取得	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_PARTSSET") == 0)
		{
			// 読み込んだ情報をひな形にのみコピーする
			g_BossModel[id_Model].style = Style;
			g_BossModel[id_Model].IdxParent = IdxParent;
			g_BossModel[id_Model].pos_offset = pos;
			g_BossModel[id_Model].rot_offset = rot;

			id_Model++; // パーツを進める

			if (id_Model == AmountModel)
			{ // モデル数分読み取り終わると終了
				break;
			}
		}
	}
}

//************************************************
// モデルテクスチャ情報を読み込む
//************************************************
void ImportTexBoss(int AmountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int i = 0; i < AmountModel; i++)
	{
		// マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_BossModel[i].pBuffMat->GetBufferPointer();

		// そのパーツの持つマテリアル分回す
		for (int j = 0; j < (int)g_BossModel[i].NumMat; j++)
		{
			// マテリアルにテクスチャが設定されていれば読込み
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_BossModel[i].pTex[j]);
			}
			else
			{
				g_BossModel[i].pTex[j] = NULL;
			}
		}
	}
}

//************************************************
// 敵のパラメータ情報の読込み
//************************************************
void ImportParamBoss(void)
{
	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};		// 文章を格納
	int i = 0;						// 汎用整数
	int appear = 0;					// 出現タイミングを格納
	int style = 0;					// スタイルを格納
	float hp = 0.0f;				// ライフを格納
	//float radius = 0.0f;			// 半径を格納(当たり判定用)
	//float spd = 0;				// 速度を格納
	D3DXVECTOR3 pos, rot, spd;		// 位置と向きを格納

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\BOSS\\boss_param.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "ボスパラメータ情報の展開に失敗");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (i >= MAX_BOSS)
		{ // 敵の最大数を越えると強制終了
			break;
		}

		if (strcmp(&FileString[0], "APPEAR") == 0)
		{ // 出現タイミングを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 64, &appear);
		}

		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // スタイルを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 64, &style);
		}

		if (strcmp(&FileString[0], "HP") == 0)
		{ // ライフを取得
			fscanf_s(pFile, "%s %f", &FileString[0], 64, &hp);
		}

		if (strcmp(&FileString[0], "SPD") == 0)
		{ // 速度を取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 64, &spd.x, &spd.y, &spd.z);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // 位置を取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 64, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // 向きを取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 64, &rot.x, &rot.y, &rot.z);
		}

		//if (strcmp(&FileString[0], "RADIUS") == 0)
		//{ // 当たり判定を取得
		//	fscanf_s(pFile, "%s %f", &FileString[0], 64, &radius);
		//}

		if (strcmp(&FileString[0], "END_PARAMSET") == 0)
		{ // 取得した情報を反映
			g_aBoss[i].Param =
			{
				appear, style, 0, 0, hp,spd,/*radius*/
			};

			g_aBoss[i].pos = pos;
			g_aBoss[i].rot = rot;

			i++;	// 次の番号へ
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{
			break;	// 終了
		}
	}

	// 敵の各パーツの判定サイズを雑に設定
	SetSizePartsRadBoss();
}

//************************************************
// 各パーツの判定サイズを設定
//************************************************
void SetSizePartsRadBoss(void)
{
	// 特に何も用意していないので、無理やり設定
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		g_aBoss[0].rad[i] = 20.0f;
	}

	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		g_aBoss[1].rad[i] = 40.0f;
	}

	g_aBoss[1].rad[15] = 125.0f;
}

////************************************************
//// 敵の出現設定
////************************************************
//void DEBUG_GenerateEnemy(void)
//{
//	/*---【現在、試験的に敵の情報設定(修正予定)】---*/
//	for (int i = 0; i < MAX_BOSS; i++)
//	{
//		// パラメータ
//		g_aBoss[i].Param.style = 0;
//		g_aBoss[i].Param.SPD = 0.1f + i * 0.1f;
//
//		g_aBoss[i].use = true;
//		g_aBoss[i].pos = D3DXVECTOR3(5.0f, 0.0f, 0.0f);
//
//		// スタイル番号を照合
//		VerifyStyleBOSS(i);
//
//		break;	// 1体のみ
//	}
//}

//************************************************
// スタイル番号の照合
//************************************************
void VerifyStyleBoss(int id)
{
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		if (g_aBoss[id].Param.style == g_BossModel[i].style)
		{ // 各ボスのスタイルと全パーツのスタイルを照合
			g_aBoss[id].parts[i] = g_BossModel[i];	//!< 番号の一致しているパーツのみ有効化
		}
	}
}

//************************************************
// モーション情報を読み込む
//************************************************
void ImportMotionBoss(void)
{
	//ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int i = 0, j = 0, k = 0;	// 汎用整数
	int Loop = 0;				// ループフラグを格納
	int AmountKey = 0;			// 総キー数を取得
	int AmountFrame = 0;		// 総フレーム数を取得
	D3DXVECTOR3 pos, rot;		// 位置と向きを格納

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\BOSS\\boss_motion.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "ボスモーション情報の展開に失敗");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "LOOP") == 0)
		{ // ループフラグを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &Loop);
		}

		if (strcmp(&FileString[0], "NUM_KEY") == 0)
		{ // 総キー数を取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &AmountKey);
		}

		if (strcmp(&FileString[0], "FRAME") == 0)
		{ // フレーム数を取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &AmountFrame);
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
			g_BossMotion[i].key[j].dest[k].pos = pos;
			g_BossMotion[i].key[j].dest[k].rot = rot;

			k++;	// パーツ番号を進める
		}

		if (strcmp(&FileString[0], "END_KEYSET") == 0)
		{ // キー情報を保存
			g_BossMotion[i].key[j].amount_frame = AmountFrame;

			k = 0;	// パーツ番号をリセット
			j++;	// キー番号を進める
		}

		if (strcmp(&FileString[0], "END_MOTIONSET") == 0)
		{ // モーション情報を保存
			g_BossMotion[i].loop = Loop;
			g_BossMotion[i].amount_key = AmountKey;

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
// ボス破棄
//************************************************
void UninitBoss(void)
{
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_BossModel[i].pTex[j] != NULL)
			{ // テクスチャの破棄
				g_BossModel[i].pTex[j]->Release();
				g_BossModel[i].pTex[j] = NULL;
			}
		}

		if (g_BossModel[i].pMesh != NULL)
		{ // メッシュの破棄
			g_BossModel[i].pMesh->Release();
			g_BossModel[i].pMesh = NULL;
		}

		if (g_BossModel[i].pBuffMat != NULL)
		{ // マテリアルの破棄
			g_BossModel[i].pBuffMat->Release();
			g_BossModel[i].pBuffMat = NULL;
		}
	}
}

//************************************************
// ボス更新
//************************************************
void UpdateBoss(void)
{
	for (int i = 0; i < MAX_BOSS; i++)
	{
		// 出現
		AppearBoss(i);

		if (!g_aBoss[i].use)
		{// ボスが使用されていないならコンティニュー
			continue;
		}

		if (g_aBoss[i].Param.style == BOSSTYPE_BIG && g_aBoss[i].use)
		{// ボスタイプが大ボスで使われていたらカウントを増やす
		}


		// 過去の位置を記録
		g_aBoss[i].pos_old = g_aBoss[i].pos;

		// 回転
		RotateBoss(i);

		//移動
		MoveBoss();

		/*---【新しい影の追従】---*/
		TrackShadow(g_aBoss[i].id_shadow,
			g_aBoss[i].pos);

		// 各パーツの判定を更新
		UpdatePartsRadBoss(i);

		//被弾
		DamageBoss(i);

		// ボスと建物の当たり判定
		CollisionBoss(i);

		// ボスとプレイヤーの当たり判定
		CollisionPlayer(i);

		//残りHPを算出する
		g_fRestHP = g_aBoss[i].Param.HP;

		//死亡
		DeadBoss(i);

		// フェーズ終了後にボスを消す
		DeleteOldBoss(i);

		// モーション
		MotionBoss(i);

	}

	// 最後に行列計算
	CalcMtxBoss();
#ifdef _DEBUG

	PrintDebugProc("中ボスの座標 : %f %f %f\n", g_aBoss[0].pos.x, g_aBoss[0].pos.y, g_aBoss[0].pos.z);
	PrintDebugProc("中ボスの向き : %f %f %f\n", g_aBoss[0].rot.x, g_aBoss[0].rot.y, g_aBoss[0].rot.z);
	PrintDebugProc("中ボスの向きを変えるタイミング : %d\n", g_nCntRot);
	PrintDebugProc("大ボスの座標 : %f %f %f\n", g_aBoss[1].pos.x, g_aBoss[1].pos.y, g_aBoss[1].pos.z);
	PrintDebugProc("大ボスの向き : %f %f %f\n", g_aBoss[1].rot.x, g_aBoss[1].rot.y, g_aBoss[1].rot.z);
	PrintDebugProc("大ボスの行動パターンを変えるフレーム数 : %d\n", g_nCntPattern);
	PrintDebugProc("中ボスの行動パターンを抽選させるためのフレーム数 : %d\n", g_nMidBossActionChoice);
	PrintDebugProc("中ボスの行動パターン : %d\n", g_nbossActionPatterns);
	PrintDebugProc("テレポートさせるタイミング : %d\n", g_nCntTeleport);
#endif

#ifdef _DEBUG

	for (int i = 0; i < 2; i++)
	{
		BOSS* pBoss = &g_aBoss[i];
		char pStr[8];

		switch (pBoss->Param.state)
		{
		case stateNormal_b:
			snprintf(&pStr[0], 8, "通常");
			break;

		case stateMove_b:
			snprintf(&pStr[0], 8, "移動");
			break;

		case stateAtk_b:
			snprintf(&pStr[0], 8, "攻撃");
			break;

		case stateDamage_b:
			snprintf(&pStr[0], 8, "被弾");
			break;

		case stateDead_b:
			snprintf(&pStr[0], 8, "死亡");
			break;

		default:

			// エラー
			assert(false && "いずれかのエネミー状態にエラー");

			break;
		}

		PrintDebugProc("【%dB】\nstate : %s\n", i + 1, &pStr[0]);	// ステータス
		PrintDebugProc("HP : %f\n", pBoss->Param.HP);				// ライフ
		PrintDebugProc("SPD : %f\n", pBoss->Param.SPD);				// 速度
	}
#endif
}

//************************************************
// ボス出現
//************************************************
void AppearBoss(int id)
{
	int* pPhase = GetInfoPhase();    // フェーズ情報を取得

	if (id == 0)
	{
		if (*pPhase != 2)
		{ // 中ボスフェーズ以外はリターン
			return;
		}
	}
	else if (id == 1)
	{
		if (*pPhase != 4)
		{ // 大ボスフェーズ以外はリターン
			return;
		}
	}

	if (g_aBoss[id].Param.appear > 0)
	{ // 出現タイミングが設定されていれば
		g_aBoss[id].Param.appear--;

		if (g_aBoss[id].Param.appear <= 0)
		{ // 出現タイミング時間に到達で
			g_aBoss[id].use = true;

			// スタイル番号を照合
			VerifyStyleBoss(id);

			/*---【影を生成】---*/
			g_aBoss[id].id_shadow = CreateShadow(40.0f);

#ifdef _DEBUG

			// このとき当たり判定を可視化
			for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
			{
				switch (id)
				{
				case 0:

					if (i > 14)
					{
						continue;
					}

					break;

				case 1:

					if (i <= 14)
					{
						continue;
					}

					break;
				}

				g_aBoss[id].id_sph[i] = CreateVisibleSph(g_aBoss[id].rad[i], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), &g_aBoss[id].pos_sph[i]);
			}

#endif
		}
	}
}

//************************************************
// ボス回転
//************************************************
void RotateBoss(int id)
{
	// ブレーキ力
	float StopEnergy = 0.1f;

	// 回転ブレーキ
	if (g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y > D3DX_PI)
	{
		g_aBoss[id].rot.y += ((g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y) * StopEnergy + (D3DX_PI * 1.8f));
	}
	else if (g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y < -D3DX_PI)
	{
		g_aBoss[id].rot.y += ((g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y) * StopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		g_aBoss[id].rot.y += ((g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y) * StopEnergy);
	}
}

//************************************************
// ボス移動
//************************************************
void MoveBoss(void)
{
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{

		switch (g_aBoss[nCntBoss].Param.style)
		{
		case 0:
			MidBossBehavior(nCntBoss);	//中ボスの挙動
			break;
		case 1:
			BigBossBehavior(nCntBoss);	//大ボスの挙動
			break;
		default:
			break;
		}
	}
}

//************************************************
// 中ボスの挙動
//************************************************
void MidBossBehavior(int id)
{
	g_nTeleportLate = 0;

	if (g_aBoss[id].use && g_aBoss[id].Param.state != stateDamage_b && g_aBoss[id].Param.state != stateDead_b)
	{
		g_nMidBossActionChoice++;	// カウントを増やす

		g_aBoss[id].Param.state = stateMove_b;		// 移動状態

		//向きを決める
		g_aBoss[id].rot_goal.y = atan2f(-g_aBoss[id].Param.SPD.x - g_MidBossMove.x, -g_aBoss[id].Param.SPD.z - g_MidBossMove.z);

		if (g_nMidBossActionChoice >= MAX_CHANGEFRAME)
		{
			// 行動パターンの再抽選
			g_nbossActionPatterns = rand() % NUM_ACT + 1;

			// カウントを0に戻す
			g_nMidBossActionChoice = 0;

		}

		for (int nCntParts = 0; nCntParts < AMOUNT_BOSS_PARTS; nCntParts++)
		{
			// ステージ外の判定
			if (g_aBoss[id].pos.x + g_aBoss[id].rad[nCntParts] >= STAGE_SIZE)
			{// ステージの右端
				// 行動パターンの再抽選
				g_nbossActionPatterns = 7;

				// カウントを0に戻す
				g_nMidBossActionChoice = 0;

				g_aBoss[id].pos.x = STAGE_SIZE - g_aBoss[id].rad[nCntParts];

			}
			else if (g_aBoss[id].pos.x - g_aBoss[id].rad[nCntParts] <= -STAGE_SIZE)
			{// ステージの左端
				// 行動パターンの再抽選
				g_nbossActionPatterns = 8;

				// カウントを0に戻す
				g_nMidBossActionChoice = 0;
			}

			if (g_aBoss[id].pos.z + g_aBoss[id].rad[nCntParts] >= STAGE_SIZE)
			{// ステージの奥端
				// 行動パターンの再抽選
				g_nbossActionPatterns = 9;

				// カウントを0に戻す
				g_nMidBossActionChoice = 0;

			}
			else if (g_aBoss[id].pos.z - g_aBoss[id].rad[nCntParts] <= -STAGE_SIZE)
			{// ステージの手前端
				// 行動パターンの再抽選
				g_nbossActionPatterns = 10;

				// カウントを0に戻す
				g_nMidBossActionChoice = 0;
			}

		}

		// 行動パターン
		switch (g_nbossActionPatterns)
		{
		case 1:
			//********************************************************************
			// 速度を決める
			//********************************************************************
			g_MidBossMove = D3DXVECTOR3(MIDBOSSMOVE, 0.0f, 0.0f);
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;
		case 2:
			//********************************************************************
			// 速度を決める
			//********************************************************************
			g_MidBossMove = D3DXVECTOR3(-MIDBOSSMOVE, 0.0f, MIDBOSSMOVE);
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;
		case 3:
			//********************************************************************
			// 速度を決める
			//********************************************************************
			g_MidBossMove = D3DXVECTOR3(0.0f, 0.0f, -MIDBOSSMOVE);
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;
		case 4:
			//********************************************************************
			// 速度を決める
			//********************************************************************
			g_MidBossMove = D3DXVECTOR3(-MIDBOSSMOVE, 0.0f, -MIDBOSSMOVE);
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;
		case 5:
			g_aBoss[id].pos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);	// ステージの真ん中
			g_nCntTeleport++;
			if (g_nCntTeleport >= 30)
			{
				g_aBoss[id].Param.state = stateNormal_b;	// 通常状態にする

				//********************************************************************
				// 速度を決める
				//********************************************************************
				g_nMidBossBullet++;
				if (g_nMidBossBullet % 20 == 0)
				{// 20フレームに1回弾を発射させる
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, -BULLETMOVEY, 5.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(5.0f, -BULLETMOVEY, 0.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-5.0f, -BULLETMOVEY, 0.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, -BULLETMOVEY, -5.0f), 100.0f);

					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(3.0f, -BULLETMOVEY, 3.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(3.0f, -BULLETMOVEY, -3.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-3.0f, -BULLETMOVEY, 3.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-3.0f, -BULLETMOVEY, -3.0f), 100.0f);
				}
				else if (g_nMidBossBullet % 35 == 0)
				{// 35フレームに1回弾を発射させる
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(3.0f, -3.2f, 3.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(3.0f, -3.2f, -3.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-3.0f, -3.2f, 3.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-3.0f, -3.2f, -3.0f), 100.0f);

				}

				g_MidBossMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//g_nCntTeleport = 0;	// テレポートしてからの時間をリセットする

			}
			break;
		case 6:
			// テレポートパターン
			g_TeleportPos.x = rand() % DATA_RANGE - (float)DATA_ADJUST;
			g_TeleportPos.z = rand() % DATA_RANGE - (float)DATA_ADJUST;
			PlaySound(SOUND_LABEL_TELEPORT);

			g_aBoss[id].pos = D3DXVECTOR3(g_TeleportPos.x, 5.0f, g_TeleportPos.z);

			// 行動パターンの再抽選
			g_nbossActionPatterns = rand() % NUM_ACT + 1;
			break;
		case 7:
			// ステージの右端用
			g_MidBossMove = D3DXVECTOR3(-MIDBOSSMOVE, 0.0f, 0.0f);			// 左方向に移動する
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case 8:
			// ステージの左端用
			g_MidBossMove = D3DXVECTOR3(MIDBOSSMOVE, 0.0f, 0.0f);			// 右方向に移動する
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case 9:
			// ステージの奥端用
			g_MidBossMove = D3DXVECTOR3(0.0f, 0.0f, -MIDBOSSMOVE);			// 手前方向に移動する
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case 10:
			// ステージの手前端用
			g_MidBossMove = D3DXVECTOR3(0.0f, 0.0f, MIDBOSSMOVE);			// 奥方向に移動する
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		}

		if (g_aBoss[id].Param.bMove)
		{
			//位置を動かす
			g_aBoss[id].pos += g_MidBossMove * 1 + g_aBoss[id].Param.SPD;
		}
	}
}

//************************************************
// 大ボスの挙動
//************************************************
void BigBossBehavior(int id)
{
	//ローカル変数宣言
	D3DXVECTOR3 BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 弾の移動量
	int nLife = 0;	// 弾の寿命


	BulletMove.x = rand() % 5 + (float)1;	// 弾の移動量を算出(X座標)
	BulletMove.z = rand() % 5 + (float)1;	// 弾の移動量を算出(Z座標)
	nLife = rand() % 50 + 100;		// 弾の寿命を算出

	if (g_aBoss[id].use)
	{ // フレーム数の加算
		g_nCntPattern++;
	}

	if (g_fRestHP < g_fStartHP * 0.4f)
	{// 大ボスのHPが40%を下回ったら
		g_bStateChange = true;
	}

	if (g_nCntPattern <= PATTERN_ZERO)
	{// カウントを増やしてから500フレームまで
		g_BigBossMove.x = 1.5f;			// X方向の移動量を調整する
		g_BigBossMove.z = 0.0f;			// Z方向の移動量を0にする
		g_aBoss[id].Param.SPD.z = 0.0f;	// パラメーターのZ方向のスピードをなくす
	}
	else if (g_nCntPattern <= PATTERN_ONE)
	{// カウントを増やしてから1000フレームまで
		g_BigBossMove.z = 1.0f;			// Z方向の移動量を調整する
		g_BigBossMove.x = 0.0f;			// X方向の移動量を0にする
		g_aBoss[id].Param.SPD.x = 0.0f;	// パラメーターのX方向のスピードをなくす
	}
	else if (g_nCntPattern <= PATTERN_TWO)
	{// カウントを増やしてから1500フレームまで
		g_BigBossMove.x = -1.0f;
		g_BigBossMove.z = 0.0f;
		g_aBoss[id].Param.SPD.z = 0.0f;
	}
	else if (g_nCntPattern <= PATTERN_THREE)
	{
		g_BigBossMove.x = -0.8f;
		g_BigBossMove.z = 0.8f;

	}
	else if (g_nCntPattern <= PATTERN_FOUR)
	{
		g_BigBossMove.x = -1.0f;
		g_BigBossMove.z = -0.5f;
	}
	else if (g_nCntPattern <= PATTERN_FIVE)
	{
		g_nBulletTime++;	//フレームを加算させる

		if (g_nBulletTime % 50 == 0)
		{
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 8.0f), 100.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, -8.0f), 100.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(8.0f, 0.0f, 0.0f), 100.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-8.0f, 0.0f, 0.0f), 150.0f);
		}

		g_BigBossMove.x = 0.0f;
		g_BigBossMove.z = 0.0f;
		g_aBoss[id].Param.SPD.x = 0.0f;
		g_aBoss[id].Param.SPD.z = 0.0f;

	}
	else if (g_nCntPattern <= PATTERN_SIX)
	{
		g_BigBossMove.x = -1.0f;
		g_BigBossMove.z = -1.0f;
	}
	else if (g_nCntPattern <= PATTERN_SEVEN)
	{
		g_BigBossMove.x = 1.0f;
		g_BigBossMove.z = 0.0f;
		g_aBoss[id].Param.SPD.z = 0.0f;

	}
	else if (g_nCntPattern <= PATTERN_EIGHT)
	{
		g_nBulletTime++;	//フレームを加算させる

		if (g_nBulletTime % 20 == 0)
		{
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(8.0f, 0.0f, 8.0f), 100.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(8.0f, 0.0f, -8.0f), 100.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(8.0f, 0.0f, -8.0f), 100.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-8.0f, 0.0f, -8.0f), 150.0f);
		}

		g_BigBossMove.x = 0.0f;
		g_BigBossMove.z = 0.0f;
		g_aBoss[id].Param.SPD.x = 0.0f;
		g_aBoss[id].Param.SPD.z = 0.0f;

	}
	else if (g_nCntPattern <= PATTERN_NINE)
	{
		g_BigBossMove.z = -1.5f;
	}
	if (g_nCntPattern > PATTERN_NINE)
	{// 1500フレームを超えたらカウントを0に戻す
		g_nCntPattern = 0;
	}



	if (g_aBoss[id].use && g_aBoss[id].Param.state != stateDamage_b && g_aBoss[id].Param.state != stateDead_b)
	{
		g_nSetBulletTime++;

		if (g_nSetBulletTime % 100 == 0)
		{
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(BulletMove.x, 0.0f, BulletMove.z), (float)nLife);
		}
		g_aBoss[id].Param.state = stateMove_b;		// 移動状態

		//向きを決める
		g_aBoss[id].rot_goal.y = atan2f(-g_aBoss[id].Param.SPD.x - g_BigBossMove.x, -g_aBoss[id].Param.SPD.z - g_BigBossMove.z);

		//if (!g_bStateChange)
		//{//HPが40%以上あるとき
		if (g_aBoss[id].Param.bMove)
		{
			g_aBoss[id].pos += g_aBoss[id].Param.SPD + g_BigBossMove;
		}
		//}
		//else
		//{//HPが40%以下を下回ったら
			//if (g_aBoss[id].Param.bMove)
			//{//移動速度を少し上げる
			//	//位置を動かす
			//	g_aBoss[id].pos += g_aBoss[id].Param.SPD * 2.0f;

			//}

		//}


		//if (g_aBoss[id].Param.style == BOSSTYPE_BIG)
		//{

		//}

	}


}

//************************************************
// ボスの当たり判定
//************************************************
void HitBoss(int id)
{
	g_aBoss[id].Param.state = stateDamage_b;	// 負傷状態に
	g_aBoss[id].Param.dur = STANTIME;			// 継続時間を付与
	g_aBoss[id].Param.HP--;						// HPを減らす

}

//************************************************
// ボスの負傷判定
//************************************************
void DamageBoss(int id)
{

	if (g_aBoss[id].Param.state != stateDamage_b)
	{ // 負傷状態でなければ終了
		return;
	}

	/*---【以下負傷状態時のみ】---*/

	// 点滅
	g_aBoss[id].col.a *= -1.0f;

	if (g_aBoss[id].Param.style == BOSSTYPE_BIG)
	{
		AdjustBullet(id);
	}

	switch (g_aBoss[id].Param.style)
	{
	case 0:
		if (CntDuration(&g_aBoss[id].Param.dur))
		{//スタン時間を過ぎたら
			g_aBoss[id].Param.state = stateNormal_b;	// 通常状態に
			g_aBoss[id].col.a = 1.0f;					// 通常色に
			g_nCntRot++;

		}
		break;
	case 1:
		if (CntDuration(&g_aBoss[id].Param.dur))
		{//スタン時間を過ぎたら
			g_aBoss[id].Param.state = stateMove_b;	// 移動状態に

		}
		break;
	}

}

//************************************************
// ボスの死亡判定
//************************************************
void DeadBoss(int id)
{
	if (g_aBoss[id].Param.state == stateDamage_b && g_aBoss[id].Param.HP <= 0.0f)
	{ // 負傷状態で体力が無いときのみ
		g_aBoss[id].Param.state = stateDead_b;	// 死亡状態に
		g_aBoss[id].Param.dur = 180;			// 継続時間付与
		g_aBoss[id].col.a = 0.5f;				// 半透明に
	}


	if (g_aBoss[id].Param.state != stateDead_b)
	{ // 死亡状態でなければ終了
		return;
	}

	if (g_aBoss[id].Param.state == stateDead_b && g_aBoss[id].use)
	{
		switch (g_aBoss[id].Param.style)
		{
		case BOSSTYPE_MID:
			g_nTimeMidBossExplosion++;
			if (g_nTimeMidBossExplosion == MIDBOSS_LATE)
			{
				SetExplosion(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + 50.0f, g_aBoss[id].pos.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f), 100.0f, 100.0f);
			}
			break;
		case BOSSTYPE_BIG:
			g_nTimeBigBossExplosion++;
			if (g_nTimeBigBossExplosion == BIGBOSS_LATE)
			{
				SetExplosion(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + 50.0f, g_aBoss[id].pos.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f), 100.0f, 100.0f);
			}
			break;
		}
	}
	/*---【以下死亡状態時のみ】---*/

	if (CntDuration(&g_aBoss[id].Param.dur))
	{
		/*---【無限に現れず、かつ復活の予定もあるためこれで】---*/
		g_aBoss[id].use = false;	// 使用フラグ

		/*---【影を消去】---*/
		DeleteShadow(g_aBoss[id].id_shadow);

		g_aBoss[id].id_shadow = -1;	// 役目を終えた数値もリセット

#ifdef _DEBUG

		// 判定可視化のみ邪魔なので消去
		for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
		{
			DeleteVisibleSph(g_aBoss[id].id_sph[i]);

			g_aBoss[id].id_sph[i] = -1;	// 役目を終えた数値もリセット
		}

#endif	// _DEBUG
	}

	if (g_aBoss[id].Param.style == BOSSTYPE_BIG && g_aBoss[id].Param.state == stateDead_b)
	{
		g_bBigBossUse = true;
	}
}



//************************************************
// ボスの復活判定
//************************************************
void ResurrectBoss(int id)
{
	if (g_aBoss[id].Param.state == stateDead_b)
	{ // 死亡状態であれば
		g_aBoss[id].Param.state = stateNormal_b;
		g_aBoss[id].Param.HP = 3;	//!< 現段階では適当に設定
	}

}

//************************************************
// モーション管理処理
//************************************************
void MotionBoss(int id)
{
	if (!g_aBoss[id].use)
	{ // 未使用ならリターン
		return;
	}

	// 再生情報格納用
	int* pNow = &g_aBoss[id].Param.motion_now;			// 現在のモーション種類
	int* pOld = &g_aBoss[id].Param.motion_old;			// 過去のモーション種類
	BossMotion* pMotion = &g_aBoss[id].motion[*pNow];	// 各エネミーのモーション情報

	switch (g_aBoss[id].Param.state)
	{
	case stateNormal_b: // ニュートラルモーション
		if (g_aBoss[id].Param.style == BOSSTYPE_MID)
		{// 中ボス
			g_aBoss[id].Param.motion_now = motion_neutralMid;
		}
		else
		{// 大ボス
			g_aBoss[id].Param.motion_now = motion_neutralBig;
		}
		break;
	case stateMove_b:	// 移動モーション
		if (g_aBoss[id].Param.style == BOSSTYPE_MID)
		{// 中ボス
			g_aBoss[id].Param.motion_now = motion_moveMid;
		}
		else
		{// 大ボス
			g_aBoss[id].Param.motion_now = motion_moveBig;
		}
		break;
	case stateAtk_b:	// 攻撃モーション
		if (g_aBoss[id].Param.style == BOSSTYPE_MID)
		{// 中ボス
			g_aBoss[id].Param.motion_now = motion_actionMid;
		}
		else
		{// 大ボス
			g_aBoss[id].Param.motion_now = motion_actionBig;
		}
		break;
	case stateDamage_b:	// 被弾モーション
		if (g_aBoss[id].Param.style == BOSSTYPE_MID)
		{// 中ボス
			g_aBoss[id].Param.motion_now = motion_damageMid;
		}
		else
		{// 大ボス
			g_aBoss[id].Param.motion_now = motion_damageBig;
		}
		break;
	case stateDead_b:	// 死亡モーション
		if (g_aBoss[id].Param.style == BOSSTYPE_MID)
		{// 中ボス
			g_aBoss[id].Param.motion_now = motion_deadMid;
		}
		else
		{// 大ボス
			g_aBoss[id].Param.motion_now = motion_deadBig;
		}
		break;
	case steteResurrect_b:	// 復活モーション
		break;

	}

	// 変更を検知
	ChangeMotionBoss(id, pNow, pOld);

	// パーツの動作
	MoveMotionBoss(id, pMotion);

	// フレームカウント
	CntMotionBoss(id, pMotion);

}

//************************************************
// モーション変更処理
//************************************************
void ChangeMotionBoss(int id, int* pNow, int* pOld)
{
	if (*pOld == *pNow)
	{ // 過去と現在の再生モーションが同じならリターン
		return;
	}

	// 過去のモーションのキーとフレームをリセット
	g_aBoss[id].motion[*pOld].id_key = 0;
	g_aBoss[id].motion[*pOld].id_frame = 0;

	// 新しいモーションへ移ったことを保存
	*pOld = *pNow;

}

//************************************************
// モーション動作処理
//************************************************
void MoveMotionBoss(int id, BossMotion* pMotion)
{
	int adjust = 0;	// 補正用整数

	// モデルとモーションパーツ間の不整合を補正する
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		if (g_aBoss[id].Param.style != g_BossModel[i].style)
		{ /*---【モーション情報はモデルの取得順に関わらず該当スタイルを構成するモデル群の
					大元の親パーツを先頭とした連番であるため、配列の不整合を補正する必要がある】---*/
			adjust++;
		}
		else
		{
			break;	// 該当スタイルに到達した時点で終了
		}
	}

	/*--------------------------------------------*/

	// 再生中のキーの総フレーム数から現在のフレーム番号を差し引く
	float dest = (float)(pMotion->key[pMotion->id_key].amount_frame - pMotion->id_frame);

	/*---【ひな形に用意されている全パーツ数分】---*/
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		if (g_aBoss[id].parts[i].pMesh == NULL)
		{ // パーツが未使用ならコンティニュー
			continue;
		}

#ifdef _DEBUG

		assert((i - adjust) >= 0 && "モーション順補正の配列外アクセス");

#endif // _DEBUG：

		g_aBoss[id].parts[i].pos_moved += (pMotion->key[pMotion->id_key].dest[i - adjust].pos - g_aBoss[id].parts[i].pos_moved) / dest;
		g_aBoss[id].parts[i].rot_moved += (pMotion->key[pMotion->id_key].dest[i - adjust].rot - g_aBoss[id].parts[i].rot_moved) / dest;
	}
}

//************************************************
// モーションカウント用
//************************************************
void CntMotionBoss(int id, BossMotion* pMotion)
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
			g_aBoss[id].Param.motion_now = 0;
		}
	}

}

//************************************************
// ボスの弾の挙動を決める
//************************************************
void AdjustBullet(int id)
{
	g_nAdjustTime++;	// フレーム数の加算
	for (int nCntData = 0; nCntData < MAX_DATA; nCntData++)
	{
		if (g_nAdjustTime % 100 == 0)
		{
			g_nBulletType[nCntData] = rand() % 100 + 1;	//0～10までの自然数をランダムで生成

			if (g_nBulletType[nCntData] >= 0 && g_nBulletType[nCntData] < 10)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_ONE;
			}
			else if (g_nBulletType[nCntData] >= 10 && g_nBulletType[nCntData] < 20)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_TWO;
			}
			if (g_nBulletType[nCntData] >= 20 && g_nBulletType[nCntData] < 30)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_THREE;
			}
			if (g_nBulletType[nCntData] >= 30 && g_nBulletType[nCntData] < 40)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_FOUR;
			}
			if (g_nBulletType[nCntData] >= 40 && g_nBulletType[nCntData] < 50)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_FIVE;
			}
			if (g_nBulletType[nCntData] >= 50 && g_nBulletType[nCntData] < 60)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_SIX;
			}
			if (g_nBulletType[nCntData] >= 60 && g_nBulletType[nCntData] < 70)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_SEVEN;
			}
			if (g_nBulletType[nCntData] >= 70 && g_nBulletType[nCntData] < 80)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_EIGHT;
			}
			if (g_nBulletType[nCntData] >= 80 && g_nBulletType[nCntData] < 90)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_NINE;
			}
			if (g_nBulletType[nCntData] >= 90 && g_nBulletType[nCntData] < 100)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_TEN;
			}
		}

		switch (g_nBulletNum[nCntData])
		{
		case BULLETPATTERN_ONE:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 8.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 10.0f), 40.0f);
			break;
		case BULLETPATTERN_TWO:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(8.0f, 0.0f, 0.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 40.0f);
			break;
		case BULLETPATTERN_THREE:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 5.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 40.0f);
			break;
		case BULLETPATTERN_FOUR:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 5.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 10.0f), 40.0f);
			break;
		case BULLETPATTERN_FIVE:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(5.0f, 0.0f, 0.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 40.0f);
			break;
		case BULLETPATTERN_SIX:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 60.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 10.0f), 60.0f);
			break;
		case BULLETPATTERN_SEVEN:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(5.0f, 0.0f, 5.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(10.0f, 0.0f, 10.0f), 40.0f);
			break;
		case BULLETPATTERN_EIGHT:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, -10.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 10.0f), 40.0f);
			break;
		case BULLETPATTERN_NINE:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-10.0f, 0.0f, -10.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(10.0f, 0.0f, -10.0f), 40.0f);
			break;
		case BULLETPATTERN_TEN:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-15.0f, 0.0f, -20.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-15.0f, 0.0f, 20.0f), 40.0f);
			break;
		}

	}


}

//************************************************
// ボス用のワールドマトリックスを計算
//************************************************
void CalcMtxBoss(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	for (int enemy_id = 0; enemy_id < MAX_BOSS; enemy_id++)
	{
		if (!g_aBoss[enemy_id].use)
		{ // この番の使用フラグが無しでコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aBoss[enemy_id].mtxWorld);

		// 向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aBoss[enemy_id].rot.y,
			g_aBoss[enemy_id].rot.x,
			g_aBoss[enemy_id].rot.z);

		// 向きを反映2
		D3DXMatrixMultiply(&g_aBoss[enemy_id].mtxWorld,
			&g_aBoss[enemy_id].mtxWorld,
			&mtxRot);

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_aBoss[enemy_id].pos.x,
			g_aBoss[enemy_id].pos.y,
			g_aBoss[enemy_id].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_aBoss[enemy_id].mtxWorld,
			&g_aBoss[enemy_id].mtxWorld,
			&mtxTrans);

		for (int Ps_id = 0; Ps_id < AMOUNT_BOSS_PARTS; Ps_id++)
		{
			if (g_aBoss[enemy_id].parts[Ps_id].pMesh == NULL)
			{ // 空っぽならコンティニュー
				continue;
			}

			// この番パーツの「親パーツ」のインデックスを保存
			int IdxParent = g_aBoss[enemy_id].parts[Ps_id].IdxParent;

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld);

			// モーション向きの反映
			D3DXVECTOR3 PartsRot =
			{
				g_aBoss[enemy_id].parts[Ps_id].rot_offset.x + g_aBoss[enemy_id].parts[Ps_id].rot_moved.x,
				g_aBoss[enemy_id].parts[Ps_id].rot_offset.y + g_aBoss[enemy_id].parts[Ps_id].rot_moved.y,
				g_aBoss[enemy_id].parts[Ps_id].rot_offset.z + g_aBoss[enemy_id].parts[Ps_id].rot_moved.z
			};

			// 向きを反映1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				PartsRot.y,
				PartsRot.x,
				PartsRot.z);

			// 向きを反映2
			D3DXMatrixMultiply(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&mtxRot);

			// モーション位置の反映
			D3DXVECTOR3 PartsPos =
			{
				g_aBoss[enemy_id].parts[Ps_id].pos_offset.x + g_aBoss[enemy_id].parts[Ps_id].pos_moved.x,
				g_aBoss[enemy_id].parts[Ps_id].pos_offset.y + g_aBoss[enemy_id].parts[Ps_id].pos_moved.y,
				g_aBoss[enemy_id].parts[Ps_id].pos_offset.z + g_aBoss[enemy_id].parts[Ps_id].pos_moved.z
			};

			// 位置を反映1
			D3DXMatrixTranslation(&mtxTrans,
				PartsPos.x,
				PartsPos.y,
				PartsPos.z);

			// 位置を反映
			D3DXMatrixMultiply(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&mtxTrans);

			D3DXMATRIX mtxParent = {};

			// 親のワールドマトリックスを取得
			if (IdxParent == -1)
			{ //メインパーツのみワールド座標に直結
				mtxParent = g_aBoss[enemy_id].mtxWorld;
			}
			else
			{ //その他パーツはそれぞれの親パーツへ付随
				mtxParent = g_aBoss[enemy_id].parts[IdxParent].mtxWorld;
			}

			// パーツごとのワールドマトリックスを算出
			D3DXMatrixMultiply(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&mtxParent);
		}
	}
}

//************************************************
// ボス描画
//************************************************
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;							// マテリアルデータへのポインタ

	for (int enemy_id = 0; enemy_id < MAX_BOSS; enemy_id++)
	{
		if (!g_aBoss[enemy_id].use)
		{ // この番の使用フラグが無しでコンティニュー
			continue;
		}

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aBoss[enemy_id].mtxWorld);

		for (int Ps_id = 0; Ps_id < AMOUNT_BOSS_PARTS; Ps_id++)
		{
			if (g_aBoss[enemy_id].parts[Ps_id].pMesh == NULL)
			{ // 空っぽならコンティニュー
				continue;
			}

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBoss[enemy_id].parts[Ps_id].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aBoss[enemy_id].parts[Ps_id].pBuffMat->GetBufferPointer();

			for (int mat_id = 0; mat_id < (int)g_aBoss[enemy_id].parts[Ps_id].NumMat; mat_id++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[mat_id].MatD3D);

				// テクスチャの設定
				if (g_aBoss[enemy_id].parts[Ps_id].pTex[mat_id] != NULL)
				{
					pDevice->SetTexture(0, g_aBoss[enemy_id].parts[Ps_id].pTex[mat_id]);
				}
				else
				{
					pDevice->SetTexture(0, NULL);
				}

				// モデルパーツの描画
				g_aBoss[enemy_id].parts[Ps_id].pMesh->DrawSubset(mat_id);
			}

			// 保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}

	}
}

//************************************************
// ボス情報を取得
//************************************************
BOSS* GetInfoBoss(void)
{
	return g_aBoss;
}

//************************************************
// ボスが生きているかどうか
//************************************************
bool CheckBossUse(void)
{
	if (g_bBigBossUse)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//************************************************
// ボスと建物の当たり判定
//************************************************
void CollisionBoss(int id)
{
	// ボスのタイプに限らずオブジェクトとの衝突判定を行う
	Object* pObject = GetInfoObject();

	for (int nCntObject = 0; nCntObject < AMOUNT_OBJECT; nCntObject++, pObject++)
	{
		if (!pObject->use)
		{ // 未使用ならコンティニュー
			continue;
		}

		for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
		{
			if (CollisionSphAABB(g_aBoss[id].pos_sph[i], g_aBoss[id].rad[i], pObject->model.aabb))
			{
				HitObject(nCntObject);	// 建物に衝突判定
			}
		}
	}
}

//************************************************
// ボスとプレイヤーの当たり判定
//************************************************
void CollisionPlayer(int id)
{
	Player* pPlayer = GetInfoPlayer();

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (!g_aBoss[id].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		if (pPlayer[nCntPlayer].param.state == stateDamage_p ||
			pPlayer[nCntPlayer].param.state == stateDead_p)
		{ // 負傷：死亡状態ならコンティニュー
			continue;
		}

		for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
		{
			// 全てのモデル分判定するので、スタイル不一致のものはコンティニュー
			switch (id)
			{
			case 0:

				if (i > 14)
				{
					continue;
				}

				break;

			case 1:

				if (i <= 14)
				{
					continue;
				}

				break;
			}

			if (CollisionSph(g_aBoss[id].pos_sph[i], g_aBoss[id].rad[i], pPlayer[nCntPlayer].pos, pPlayer[nCntPlayer].param.rad))
			{
				// 被弾の処理
				HitPlayer(nCntPlayer);
			}
		}
	}
}
//************************************************
// フェーズが終わったボスの消去
//************************************************
void DeleteOldBoss(int id)
{
	g_nMidBossPhase = *GetInfoPhase();

	if (g_nMidBossPhase != 3)
	{
		return;
	}

	if (g_aBoss[id].Param.style == BOSSTYPE_MID)
	{
#ifdef _DEBUG

		// 判定可視化のみ邪魔なので消去
		for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
		{
			DeleteVisibleSph(g_aBoss[id].id_sph[i]);

			g_aBoss[id].id_sph[i] = -1;	// 役目を終えた数値もリセット
		}

#endif	// _DEBUG

		/*---【影を消去】---*/
		DeleteShadow(g_aBoss[id].id_shadow);

		// ボスの消去
		g_aBoss[id].use = false;
	}

}

////////////////////////////////////////////////////////////////

//************************************************
// 体力による生存判定 - 中ボス
//************************************************
bool GetInfoHP_MidBoss(void)
{
	bool tf = false;

	if (g_aBoss[0].Param.HP <= 0)
	{
		tf = true;
	}

	return tf;
}

//************************************************
// 体力による生存判定 - 大ボス
//************************************************
bool GetInfoHP_BigBoss(void)
{
	bool tf = false;

	if (g_aBoss[1].Param.HP <= 0)
	{
		tf = true;
	}

	return tf;
}

////////////////////////////////////////////////////////////////

//************************************************
// 各パーツの判定を更新
//************************************************
void UpdatePartsRadBoss(int id)
{
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		switch (id)
		{
		case 0:

			if (i > 14)
			{
				continue;
			}

			break;

		case 1:

			if (i <= 14)
			{
				continue;
			}

			break;
		}

		g_aBoss[id].pos_sph[i] =
		{
			g_aBoss[id].parts[i].mtxWorld._41,
			g_aBoss[id].parts[i].mtxWorld._42,
			g_aBoss[id].parts[i].mtxWorld._43
		};

		if (g_aBoss[id].pos_sph[i].x == 0.0f &&
			g_aBoss[id].pos_sph[i].z == 0.0f)
		{
			g_aBoss[id].pos_sph[i].y = -1000.0f;
		}

	}
}