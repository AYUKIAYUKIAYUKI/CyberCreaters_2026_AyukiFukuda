//************************************************
//
// フェーズ表示[phase.cpp]
// Author：福田歩希
//
//************************************************

/*---【インクルードファイル】---*/
#include "phase.h"

// システム
#include "sound.h"

// 諸処理
#include "enemy.h"
#include "game.h"

// デバッグ用
#ifdef _DEBUG
#include <assert.h>
#endif // _DEBUG

/*---【マクロ定義】---*/
#define AMOUNT_PHASE 16		// フェーズ表示の最大数
#define AMOUNT_PHASENUM 4	// 数字の最大数

/*---【テクスチャ分類】---*/
typedef enum
{
	TEXTURE_TYPE_PHASE_ENEMYWOOD = 0,	// 敵の総数の表示枠
	TEXTURE_TYPE_PHASE_ENEMYMAX,		// 「敵の総数」
	TEXTURE_TYPE_PHASE_WOOD,			// フェーズの表示枠
	TEXTURE_TYPE_PHASE_NOW,				// 「現在のフェーズ」
	TEXTURE_TYPE_PHASE_STONE,			// でかい石板
	TEXTURE_TYPE_PHASE_NEXT,			// NEXTのお知らせ
	TEXTURE_TYPE_PHASE_MIDBOSS,			// 中ボス襲来
	TEXTURE_TYPE_PHASE_BIGBOSS,			// 大ボス襲来
	TEXTURE_TYPE_PHASE_SCOREWOOD,		// スコアの表示枠
	TEXTURE_TYPE_PHASE_TIMEWOOD,		// タイマーの表示枠
	TEXTURE_TYPE_PHASE_LIMIT,			// 「残り時間」
	TEXTURE_TYPE_PHASE_COLON,			// 「：」
	TEXTURE_TYPE_PHASE_MAX
} TEXTURE_TYPE_PHASE;

/*---【グローバル変数】---*/
LPDIRECT3DTEXTURE9 g_pTexturePhase[TEXTURE_TYPE_PHASE_MAX] = {};	// テクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePhaseNum = NULL;						// 数字用テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPhase = NULL;						// 頂点バッファのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPhaseNum = NULL;					// 数字用頂点バッファのポインタ
UI g_Phase[AMOUNT_PHASE];											// フェーズ表示用情報
UI g_PhaseNum[AMOUNT_PHASE];										// 数字表示用情報

int g_CT_startPhase_Enemy = 0;	// 敵の総数表示が登場するまでの遅延用
int g_CT_startPhase_Now = 0;	// フェーズ表示が登場するまでの遅延用
bool g_change_phase = false;	// フェーズの変動を検知
int * g_pPhase = nullptr;		// フェーズ情報同期用
bool g_change_enemy = false;	// 出現数が変わった事を検出
bool g_change_score = false;	// スコアが変わった事を検出

/*---【プロトタイプ宣言】---*/
void ImportTexPhase(void);		// テクスチャを取得
void ImportInfoPhase(void);		// 設定情報を取得
void CreateVtxPhase(void);		// 頂点バッファの生成
void SetInfoPhase_Enemy(void);	// 敵総数用情報を設定

void AnimationManagerPhase_Enemy(void);		// 敵の総数用アニメーション特別管理
void AnimationManagerPhase_Now(void);		// フェーズ用アニメーション特別管理
void AnimationManagerPhase(void);			// アニメーション管理
void PlayAnimationPhase(UI* p, int type);	// アニメーション再生
void StopAnimationPhase(UI* p, int type);	// アニメーション停止

void VibrationSmallPhase(UI* p);	// 振動：小
void VibrationBigPhase(UI* p);		// 振動：大
void ChangeRedPhase(UI* p);			// 赤く
void FadeAppearPhase(UI* p);		// 出現
void LikeaGummyPhase(UI* p);		// ブニョ
void AppealtoFrontPhase(UI* p);		// チラチラ
void SlideUpPhase(UI* p);			// 上スライドイン
void SlideDownPhase(UI* p);			// 下
void SlideLeftPhase(UI* p);			// 左
void SlideRightPhase(UI* p);		// 右
void DisSlideUpPhase(UI* p);		// 上スライドアウト
void DisSlideDownPhase(UI* p);		// 下
void DisSlideLeftPhase(UI* p);		// 左
void DisSlideRightPhase(UI* p);		// 右

void SetVtxPhase(void);		// 展開
void DrawNormalPhase(void);	// 通常描画

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ImportTexPhaseNum(void);	// テクスチャを取得
void ImportInfoPhaseNum(void);	// 設定情報を取得
void CreateVtxPhaseNum(void);	// 頂点バッファの生成

void AnimationManagerPhaseNum(void);	// アニメーション管理

void SetVtxPhaseNum(void);		// 展開
void DrawNormalPhaseNum(void);	// 通常描画

//************************************************
// 初期処理
//************************************************
void InitPhase(int joined)
{
	g_CT_startPhase_Enemy = 0;	// 敵の総数表示が登場するまでの遅延用
	g_CT_startPhase_Now = 0;	// フェーズ表示が登場するまでの遅延用
	g_change_phase = false;		// フェーズの変動を検知
	g_pPhase = GetInfoPhase();	// フェーズ情報を同期用
	g_change_enemy = false;		// 出現数が変わった事を検出
	g_change_score = false;		// スコアが変わった事を検出

#ifdef _DEBUG	// フェーズ情報のポインタにアドレス入ってるか確認 (初期化前後したらバグる)

	assert(g_pPhase != nullptr && "フェーズ同期用の情報を取得できませんでした");

#endif

	for (int i = 0; i < AMOUNT_PHASE; i++)
	{ // Phase表示リセット
		g_Phase[i].use = false;
		g_Phase[i].textype = -1;
		g_Phase[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Phase[i].move = { 0.0f, 0.0f, 0.0f };
		g_Phase[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Phase[i].span = { 0.0f, 0.0f };
		g_Phase[i].angle = 0;
		g_Phase[i].length = 0;
		g_Phase[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // アニメーション情報リセット
			g_Phase[i].play[j].use = false;
			g_Phase[i].play[j].dur = 0;
			g_Phase[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_Phase[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_Phase[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_Phase[i].play[j].span = { 0.0f, 0.0f };
			g_Phase[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	// テクスチャを読み込む
	ImportTexPhase();

	// 情報を取得する
	ImportInfoPhase();

	// 通常頂点バッファの生成
	CreateVtxPhase();

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_PHASENUM; i++)
	{ // 数字用情報リセット
		g_PhaseNum[i].use = false;
		g_PhaseNum[i].textype = -1;
		g_PhaseNum[i].pos = { 0.0f, 0.0f, 0.0f };
		g_PhaseNum[i].move = { 0.0f, 0.0f, 0.0f };
		g_PhaseNum[i].rot = { 0.0f, 0.0f, 0.0f };
		g_PhaseNum[i].span = { 0.0f, 0.0f };
		g_PhaseNum[i].angle = 0;
		g_PhaseNum[i].length = 0;
		g_PhaseNum[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // アニメーション情報リセット
			g_PhaseNum[i].play[j].use = false;
			g_PhaseNum[i].play[j].dur = 0;
			g_PhaseNum[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_PhaseNum[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_PhaseNum[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_PhaseNum[i].play[j].span = { 0.0f, 0.0f };
			g_PhaseNum[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	// テクスチャを読み込む
	ImportTexPhaseNum();

	// 情報を取得する
	ImportInfoPhaseNum();

	// 通常頂点バッファの生成
	CreateVtxPhaseNum();

	/*************************************/

	// 情報を設定
	g_CT_startPhase_Enemy = 100 + (10 * joined);	// 敵の総数表示が出るまでの遅延期間
	g_CT_startPhase_Now = 150 + (10 * joined);		// フェーズ表示が出るまでの遅延期間
	
	/*************************************/
}

//************************************************
// 終了処理
//************************************************
void UninitPhase(void)
{
	for (int i = 0; i < TEXTURE_TYPE_PHASE_MAX; i++)
	{ // テクスチャの破棄
		if (g_pTexturePhase[i] != NULL)
		{
			g_pTexturePhase[i]->Release();
			g_pTexturePhase[i] = NULL;
		}
	}

	if (g_pTexturePhaseNum != NULL)
	{ // 数字テクスチャの破棄
		g_pTexturePhaseNum->Release();
		g_pTexturePhaseNum = NULL;
	}

	if (g_pVtxBuffPhase != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffPhase->Release();
		g_pVtxBuffPhase = NULL;
	}

	if (g_pVtxBuffPhaseNum != NULL)
	{ // 数字頂点バッファの破棄
		g_pVtxBuffPhaseNum->Release();
		g_pVtxBuffPhaseNum = NULL;
	}
}

//************************************************
// 更新処理
//************************************************
void UpdatePhase(void)
{
	// 敵総数表示用アニメーション特別管理
	AnimationManagerPhase_Enemy();

	// フェーズ表示用アニメーション特別管理
	AnimationManagerPhase_Now();

	if (g_change_score)
	{ // スコア変更に合わせてアニメーション
		g_Phase[TEXTURE_TYPE_PHASE_SCOREWOOD].play[ANIMATION_TYPE_VIBSMALL].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_SCOREWOOD].play[ANIMATION_TYPE_VIBSMALL].dur = 30;

		g_change_score = false;
	}

	// アニメーション管理
	AnimationManagerPhase();

	// 数字アニメーション管理
	AnimationManagerPhaseNum();

	// 通常展開
	SetVtxPhase();

	// 数字通常展開
	SetVtxPhaseNum();
}

//************************************************
// 描画処理
//************************************************
void DrawPhase(void)
{
	// 通常描画
	DrawNormalPhase();

	// 数字通常描画
	DrawNormalPhaseNum();
}

//************************************************
// フェーズ表示の情報を取得
//************************************************
UI* GetInfoPhaseUI(void)
{
	return &g_Phase[0];
}

//************************************************
// フェーズの変更検知
//************************************************
bool* ChangePhasePlay(void)
{
	return &g_change_phase;
}

//************************************************
// 出現数の変更検知
//************************************************
bool* ChangeEnemyPlay(void)
{
	return &g_change_enemy;
}

//************************************************
// スコアの変更検知
//************************************************
bool* ChangeScorePlay(void)
{
	return &g_change_score;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// テクスチャを読み込む
//************************************************
void ImportTexPhase(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// テクスチャ画像の読込み用
	const char* pFileName[TEXTURE_TYPE_PHASE_MAX] =
	{
		"data\\TEXTURE\\woody.png",
		"data\\TEXTURE\\amount_enemy.png",
		"data\\TEXTURE\\fewoody.png",
		"data\\TEXTURE\\phase_now.png",
		"data\\TEXTURE\\bigstone.png",
		"data\\TEXTURE\\NEXT.png",
		"data\\TEXTURE\\mid_phase.png",
		"data\\TEXTURE\\big_phase.png",
		"data\\TEXTURE\\woody.png",
		"data\\TEXTURE\\fewoody.png",
		"data\\TEXTURE\\timelimit.png",
		"data\\TEXTURE\\colon.png",
	};

	for (int i = 0; i < TEXTURE_TYPE_PHASE_MAX; i++)
	{ // テクスチャの生成

		if (pFileName[i] == NULL)
		{
			break;	// 画像が無くなっても終了
		}

		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTexturePhase[i]);
	}
}

//************************************************
// 設定情報を読み込む
//************************************************
void ImportInfoPhase(void)
{
	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char str[128] = {};		// 文章を格納
	int i = 0;				// 汎用整数
	int textype = 0;		// テクスチャ情報を取得
	D3DXVECTOR3 pos = {};	// 位置を格納
	D3DXVECTOR3 rot = {};	// 向きを格納
	D3DXVECTOR2 span = {};	// 大きさを格納
	D3DXCOLOR col = {};		// 色を格納

	// Phase情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\UI\\phase.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "フェーズ用情報の展開に失敗");

#endif	// _DEBUG：ファイル展開の合否
	}

	while (fscanf_s(pFile, "%s", &str[0], 128) != EOF)
	{
		if (strcmp(&str[0], "TEXTYPE") == 0)
		{ // テクスチャタイプを取得
			fscanf_s(pFile, "%s %d", &str[0], 2, &textype);
		}

		if (strcmp(&str[0], "POS") == 0)
		{ // 位置を取得
			fscanf_s(pFile, "%s %f %f %f", &str[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&str[0], "ROT") == 0)
		{ // 向きを取得
			fscanf_s(pFile, "%s %f %f %f", &str[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&str[0], "SPAN") == 0)
		{ // 大きさを取得
			fscanf_s(pFile, "%s %f %f", &str[0], 2, &span.x, &span.y);
		}

		if (strcmp(&str[0], "COL") == 0)
		{ // 色を取得
			fscanf_s(pFile, "%s %f %f %f %f", &str[0], 2, &col.r, &col.g, &col.b, &col.a);
		}

		if (strcmp(&str[0], "END_PARAMSET") == 0)
		{ // 取得した情報を反映

			g_Phase[i].use = true;
			g_Phase[i].textype = textype;
			g_Phase[i].pos = pos;
			g_Phase[i].rot = rot;
			g_Phase[i].span = span;
			g_Phase[i].col = col;

			i++;	// 次の番号へ
		}

		if (strcmp(&str[0], "END_SCRIPT") == 0)
		{
			break;	// 終了
		}
	}

	// ファイルを閉じる
	fclose(pFile);
}

//************************************************
// 頂点バッファの生成
//************************************************
void CreateVtxPhase(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_PHASE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPhase,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffPhase->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_PHASE; i++, pVtx += AMOUNT_VTX)
	{
		// 頂点座標の初期設定
		pVtx[0].pos = { 0.0f, 0.0f, 0.0f };
		pVtx[1].pos = { 0.0f, 0.0f, 0.0f };
		pVtx[2].pos = { 0.0f, 0.0f, 0.0f };
		pVtx[3].pos = { 0.0f, 0.0f, 0.0f };

		// 除算数の初期設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の初期設定
		pVtx[0].tex = { 0.0f, 0.0f };
		pVtx[1].tex = { 1.0f, 0.0f };
		pVtx[2].tex = { 0.0f, 1.0f };
		pVtx[3].tex = { 1.0f, 1.0f };
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPhase->Unlock();
}

////************************************************
//// アニメーション選択
////************************************************
//void SelectAnimationPhase(void)
//{
//	int i = g_select;	// 識別簡略化
//
//	// 再生するアニメーションを変更する
//	if (GetKeyboardTrigger(DIK_1))
//	{
//		g_animaType > 0 ? g_animaType-- : g_animaType = ANIMATION_TYPE_MAX - 1;
//	}
//	else if (GetKeyboardTrigger(DIK_2))
//	{
//		g_animaType < ANIMATION_TYPE_MAX - 1 ? g_animaType++ : g_animaType = 0;
//	}
//
//	// 対応するアニメーションを再生
//	if (GetKeyboardTrigger(DIK_3))
//	{
//		switch (g_animaType)
//		{
//		case ANIMATION_TYPE_VIBSMALL:
//
//			g_Phase[i].play[ANIMATION_TYPE_VIBSMALL].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_VIBSMALL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_VIBBIG:
//
//			g_Phase[i].play[ANIMATION_TYPE_VIBBIG].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_VIBBIG].dur = 15;
//
//			break;
//
//		case ANIMATION_TYPE_RED:
//
//			g_Phase[i].play[ANIMATION_TYPE_RED].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_RED].dur = 20;
//
//			break;
//
//		case ANIMATION_TYPE_FADE:
//
//			g_Phase[i].play[ANIMATION_TYPE_FADE].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_FADE].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_GUMMY:
//
//			g_Phase[i].play[ANIMATION_TYPE_GUMMY].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_APPEAL:
//
//			g_Phase[i].play[ANIMATION_TYPE_APPEAL].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_APPEAL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEUP:
//
//			g_Phase[i].play[ANIMATION_TYPE_SLIDEUP].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_SLIDEUP].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEDOWN:
//
//			g_Phase[i].play[ANIMATION_TYPE_SLIDEDOWN].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_SLIDEDOWN].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDELEFT:
//
//			g_Phase[i].play[ANIMATION_TYPE_SLIDELEFT].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDERIGHT:
//
//			g_Phase[i].play[ANIMATION_TYPE_SLIDERIGHT].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_SLIDERIGHT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_DISUP:
//
//			g_Phase[i].play[ANIMATION_TYPE_DISUP].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_DISUP].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISDOWN:
//
//			g_Phase[i].play[ANIMATION_TYPE_DISDOWN].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_DISDOWN].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISLEFT:
//
//			g_Phase[i].play[ANIMATION_TYPE_DISLEFT].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_DISLEFT].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISRIGHT:
//
//			g_Phase[i].play[ANIMATION_TYPE_DISRIGHT].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_DISRIGHT].dur = 40;
//
//			break;
//		}
//	}
//}

//************************************************
// 敵総数用情報を設定
//************************************************
void SetInfoPhase_Enemy(void)
{
	g_Phase[TEXTURE_TYPE_PHASE_ENEMYWOOD].play[ANIMATION_TYPE_SLIDERIGHT].use = true;
	g_Phase[TEXTURE_TYPE_PHASE_ENEMYWOOD].play[ANIMATION_TYPE_SLIDERIGHT].dur = 60;

	g_Phase[TEXTURE_TYPE_PHASE_ENEMYWOOD].col = { 1.0f, 1.0f, 1.0f, 1.0f };
}

//************************************************
// 敵総数表示用アニメーション特別管理
//************************************************
void AnimationManagerPhase_Enemy(void)
{
	// カウント減少
	g_CT_startPhase_Enemy > 0 ? g_CT_startPhase_Enemy--: g_CT_startPhase_Enemy = 0;

	if (g_CT_startPhase_Enemy == 1)	// 0にすると無限に再生
	{ // 遅延経過後に木枠が登場
		SetInfoPhase_Enemy();

		g_Phase[TEXTURE_TYPE_PHASE_SCOREWOOD].play[ANIMATION_TYPE_SLIDELEFT].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_SCOREWOOD].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;

		g_Phase[TEXTURE_TYPE_PHASE_SCOREWOOD].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	if (g_Phase[TEXTURE_TYPE_PHASE_ENEMYWOOD].play[ANIMATION_TYPE_SLIDERIGHT].dur == 35)
	{ // 木枠が登場後それっぽいタイミングで登場

		g_Phase[TEXTURE_TYPE_PHASE_ENEMYMAX].play[ANIMATION_TYPE_FADE].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_ENEMYMAX].play[ANIMATION_TYPE_FADE].dur = 60;

		g_PhaseNum[1].play[ANIMATION_TYPE_FADE].use = true;
		g_PhaseNum[1].play[ANIMATION_TYPE_FADE].dur = 60;

		g_PhaseNum[2].play[ANIMATION_TYPE_FADE].use = true;
		g_PhaseNum[2].play[ANIMATION_TYPE_FADE].dur = 60;

		g_Phase[TEXTURE_TYPE_PHASE_ENEMYMAX].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_PhaseNum[1].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_PhaseNum[2].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	if (g_change_enemy)
	{ // 出現数の変更に合わせてアニメーション

		g_Phase[TEXTURE_TYPE_PHASE_WOOD].play[ANIMATION_TYPE_VIBSMALL].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_WOOD].play[ANIMATION_TYPE_VIBSMALL].dur = 30;

		g_PhaseNum[1].play[ANIMATION_TYPE_GUMMY].use = true;
		g_PhaseNum[1].play[ANIMATION_TYPE_GUMMY].dur = 30;

		g_PhaseNum[2].play[ANIMATION_TYPE_GUMMY].use = true;
		g_PhaseNum[2].play[ANIMATION_TYPE_GUMMY].dur = 30;

		g_change_enemy = false;
	}
}

//************************************************
// フェーズ表示アニメーション特別管理
//************************************************
void AnimationManagerPhase_Now(void)
{
	// カウント減少
	g_CT_startPhase_Now > 0 ? g_CT_startPhase_Now-- : g_CT_startPhase_Now = 0;

	if (g_CT_startPhase_Now == 1)	// 0にすると無限に再生
	{ // 遅延経過後に枠が登場

		g_Phase[TEXTURE_TYPE_PHASE_WOOD].play[ANIMATION_TYPE_SLIDEDOWN].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_WOOD].play[ANIMATION_TYPE_SLIDEDOWN].dur = 60;

		g_Phase[TEXTURE_TYPE_PHASE_TIMEWOOD].play[ANIMATION_TYPE_SLIDEDOWN].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_TIMEWOOD].play[ANIMATION_TYPE_SLIDEDOWN].dur = 60;

		g_Phase[TEXTURE_TYPE_PHASE_WOOD].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_Phase[TEXTURE_TYPE_PHASE_TIMEWOOD].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	if (g_Phase[TEXTURE_TYPE_PHASE_WOOD].play[ANIMATION_TYPE_SLIDEDOWN].dur == 35)
	{ // 枠が登場後それっぽいタイミングで登場

		g_Phase[TEXTURE_TYPE_PHASE_NOW].play[ANIMATION_TYPE_FADE].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_NOW].play[ANIMATION_TYPE_FADE].dur = 60;
		g_Phase[TEXTURE_TYPE_PHASE_LIMIT].play[ANIMATION_TYPE_FADE].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_LIMIT].play[ANIMATION_TYPE_FADE].dur = 60;
		g_Phase[TEXTURE_TYPE_PHASE_COLON].play[ANIMATION_TYPE_FADE].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_COLON].play[ANIMATION_TYPE_FADE].dur = 60;
		g_PhaseNum[0].play[ANIMATION_TYPE_FADE].use = true;
		g_PhaseNum[0].play[ANIMATION_TYPE_FADE].dur = 60;

		g_Phase[TEXTURE_TYPE_PHASE_NOW].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_Phase[TEXTURE_TYPE_PHASE_LIMIT].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_Phase[TEXTURE_TYPE_PHASE_COLON].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_PhaseNum[0].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	/*--------------------------------------------*/
	
	if (g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_SLIDELEFT].dur == 1)
	{ // 特大表示が動く
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBBIG].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBBIG].dur = 60;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	if (g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBBIG].dur == 1)
	{
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBSMALL].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_DISRIGHT].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_DISRIGHT].dur = 60;
	}

	if (g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_DISRIGHT].dur == 1)
	{
		g_Phase[TEXTURE_TYPE_PHASE_STONE].col = { 0.0f, 0.0f, 0.0f, 0.0f };

		// 敵の出現数の数字もこのタイミングで動かしとく
		g_PhaseNum[1].play[ANIMATION_TYPE_GUMMY].use = true;
		g_PhaseNum[1].play[ANIMATION_TYPE_GUMMY].dur = 30;
		g_PhaseNum[2].play[ANIMATION_TYPE_GUMMY].use = true;
		g_PhaseNum[2].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	/*--------------------------------------------*/
	
	// 特大文字が動く
	if (*g_pPhase == 2)
	{
		if (g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_SLIDELEFT].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_GUMMY].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_GUMMY].dur = 30;
		}

		if (g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBBIG].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_DISRIGHT].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_DISRIGHT].dur = 60;
		}

		if (g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_DISRIGHT].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}
	else if (*g_pPhase == 4)
	{
		if (g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_SLIDELEFT].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_GUMMY].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_GUMMY].dur = 30;
		}

		if (g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBBIG].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_DISRIGHT].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_DISRIGHT].dur = 60;
		}

		if (g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_DISRIGHT].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}
	else
	{
		if (g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_SLIDELEFT].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_GUMMY].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_GUMMY].dur = 30;
		}

		if (g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBBIG].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_DISRIGHT].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_DISRIGHT].dur = 60;
		}

		if (g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_DISRIGHT].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	/*--------------------------------------------*/

	if (g_change_phase)
	{ // フェーズの変更に合わせてアニメーション

		// 通常表示
		g_Phase[TEXTURE_TYPE_PHASE_ENEMYWOOD].play[ANIMATION_TYPE_VIBSMALL].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_ENEMYWOOD].play[ANIMATION_TYPE_VIBSMALL].dur = 30;

		g_PhaseNum[0].play[ANIMATION_TYPE_GUMMY].use = true;
		g_PhaseNum[0].play[ANIMATION_TYPE_GUMMY].dur = 30;

		// 特大表示
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBSMALL].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_SLIDELEFT].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;

		g_Phase[TEXTURE_TYPE_PHASE_STONE].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		// 特大文字
		if (*g_pPhase == 2)
		{
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_SLIDELEFT].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;

			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
		else if (*g_pPhase == 4)
		{
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_SLIDELEFT].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;

			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
		else
		{
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_SLIDELEFT].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;

			g_Phase[TEXTURE_TYPE_PHASE_NEXT].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}

		g_change_phase = false;
	}
}

//************************************************
// アニメーション管理
//************************************************
void AnimationManagerPhase(void)
{
	for (int i = 0; i < AMOUNT_PHASE; i++)
	{
		if (!g_Phase[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// どのアニメーションを再生するのか選別
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_Phase[i].play[j].use)
			{
				// 対応するアニメーションを再生する
				PlayAnimationPhase(&g_Phase[i], j);
			}
		}
	}
}

//************************************************
// 種類に対応したアニメーション再生
//************************************************
void PlayAnimationPhase(UI* p, int type)
{
	switch (type)
	{
	case ANIMATION_TYPE_VIBSMALL:

		VibrationSmallPhase(p);	// 振動：小

		break;

	case ANIMATION_TYPE_VIBBIG:

		VibrationBigPhase(p);	// 振動：大

		break;

	case ANIMATION_TYPE_RED:

		ChangeRedPhase(p);	// 赤くなる

		break;

	case ANIMATION_TYPE_FADE:

		FadeAppearPhase(p);	// フェード

		break;

	case ANIMATION_TYPE_GUMMY:

		LikeaGummyPhase(p);	// ブニョ

		break;

	case ANIMATION_TYPE_APPEAL:

		AppealtoFrontPhase(p);	// バンっ

		break;

	case ANIMATION_TYPE_SLIDEUP:

		SlideUpPhase(p);	// 上スライドイン

		break;

	case ANIMATION_TYPE_SLIDEDOWN:

		SlideDownPhase(p);	// 下スライドイン

		break;

	case ANIMATION_TYPE_SLIDELEFT:

		SlideLeftPhase(p);	// 左スライドイン

		break;

	case ANIMATION_TYPE_SLIDERIGHT:

		SlideRightPhase(p);	// 右スライドイン

		break;

	case ANIMATION_TYPE_DISUP:

		DisSlideUpPhase(p);	// 上スライドアウト

		break;

	case ANIMATION_TYPE_DISDOWN:

		DisSlideDownPhase(p);	// 下スライドアウト

		break;

	case ANIMATION_TYPE_DISLEFT:

		DisSlideLeftPhase(p);	// 左スライドアウト

		break;

	case ANIMATION_TYPE_DISRIGHT:

		DisSlideRightPhase(p);	// 右スライドアウト

		break;
	}
}

//************************************************
// アニメーション停止
//************************************************
void StopAnimationPhase(UI* p, int type)
{
	p->play[type] =
	{
		false,
		0,
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
	};
}

//************************************************
// 振動：小
//************************************************
void VibrationSmallPhase(UI* p)
{
	p->play[ANIMATION_TYPE_VIBSMALL].pos =
	{
		(float)(rand() % 10),
		(float)(rand() % 10),
		0.0f
	};

	if (CntDuration(&p->play[ANIMATION_TYPE_VIBSMALL].dur))
	{
		// アニメーションを停止
		StopAnimationPhase(p, ANIMATION_TYPE_VIBSMALL);
	}
}

//************************************************
// 振動：大
//************************************************
void VibrationBigPhase(UI* p)
{
	p->play[ANIMATION_TYPE_VIBBIG].pos =
	{
		(float)(rand() % 30),
		(float)(rand() % 30),
		0.0f
	};

	if (CntDuration(&p->play[ANIMATION_TYPE_VIBBIG].dur))
	{
		// アニメーションを停止
		StopAnimationPhase(p, ANIMATION_TYPE_VIBBIG);
	}
}

//************************************************
// 赤くなる
//************************************************
void ChangeRedPhase(UI* p)
{
	if (p->play[ANIMATION_TYPE_RED].dur > 10)
	{
		p->play[ANIMATION_TYPE_RED].col.g += -0.1f;
		p->play[ANIMATION_TYPE_RED].col.b += -0.1f;
	}
	else
	{
		p->play[ANIMATION_TYPE_RED].col.g += 0.1f;
		p->play[ANIMATION_TYPE_RED].col.b += 0.1f;
	}

	if (CntDuration(&p->play[ANIMATION_TYPE_RED].dur))
	{
		// アニメーションを停止
		StopAnimationPhase(p, ANIMATION_TYPE_RED);
	}
}

//************************************************
// 出現
//************************************************
void FadeAppearPhase(UI* p)
{
	if (p->play[ANIMATION_TYPE_FADE].dur >= 40)
	{
		p->play[ANIMATION_TYPE_FADE].col.a = -1.0f;
	}
	else
	{
		p->play[ANIMATION_TYPE_FADE].col.a = (-1.0f / (40 - p->play[ANIMATION_TYPE_FADE].dur));
	}

	if (p->play[ANIMATION_TYPE_FADE].dur == 40)
	{
		p->play[ANIMATION_TYPE_GUMMY].use = true;
		p->play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	if (CntDuration(&p->play[ANIMATION_TYPE_FADE].dur))
	{
		// アニメーションを停止
		StopAnimationPhase(p, ANIMATION_TYPE_FADE);
	}
}

//************************************************
// ブニョ
//************************************************
void LikeaGummyPhase(UI* p)
{
	if (p->play[ANIMATION_TYPE_GUMMY].dur > 25)
	{
		p->play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		p->play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (p->play[ANIMATION_TYPE_GUMMY].dur > 20 &&
		p->play[ANIMATION_TYPE_GUMMY].dur <= 25)
	{
		p->play[ANIMATION_TYPE_GUMMY].span.x += 2;

		p->play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		p->play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (p->play[ANIMATION_TYPE_GUMMY].dur > 15 &&
		p->play[ANIMATION_TYPE_GUMMY].dur <= 20)
	{
		p->play[ANIMATION_TYPE_GUMMY].span.x += 2;

		p->play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		p->play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (p->play[ANIMATION_TYPE_GUMMY].dur > 10 &&
		p->play[ANIMATION_TYPE_GUMMY].dur <= 15)
	{
		p->play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		p->play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (p->play[ANIMATION_TYPE_GUMMY].dur > 5 &&
		p->play[ANIMATION_TYPE_GUMMY].dur <= 10)
	{
		p->play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		p->play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		p->play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (p->play[ANIMATION_TYPE_GUMMY].dur <= 5)
	{
		p->play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		p->play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		p->play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}

	if (CntDuration(&p->play[ANIMATION_TYPE_GUMMY].dur))
	{
		// アニメーションを停止
		StopAnimationPhase(p, ANIMATION_TYPE_GUMMY);
	}
}

//************************************************
// チラチラ
//************************************************
void AppealtoFrontPhase(UI* p)
{
	if (p->play[ANIMATION_TYPE_APPEAL].dur == 30)
	{
		p->play[ANIMATION_TYPE_APPEAL].col.a = -1.0f;
	}

	p->play[ANIMATION_TYPE_APPEAL].col.a *= -1.0f;

	if (CntDuration(&p->play[ANIMATION_TYPE_APPEAL].dur))
	{
		p->play[ANIMATION_TYPE_APPEAL].col.a = 0.0f;

		// アニメーションを停止
		StopAnimationPhase(p, ANIMATION_TYPE_APPEAL);
	}
}

//************************************************
// 上スライドイン
//************************************************
void SlideUpPhase(UI* p)
{
	p->play[ANIMATION_TYPE_SLIDEUP].pos.y = (2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDEUP].dur)) + (-2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDEUP].dur))
	{
		// アニメーションを停止
		StopAnimationPhase(p, ANIMATION_TYPE_SLIDEUP);
	}
}

//************************************************
// 下スライドイン
//************************************************
void SlideDownPhase(UI* p)
{
	p->play[ANIMATION_TYPE_SLIDEDOWN].pos.y = (-2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDEDOWN].dur)) + (2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDEDOWN].dur))
	{
		// アニメーションを停止
		StopAnimationPhase(p, ANIMATION_TYPE_SLIDEDOWN);
	}
}

//************************************************
// 左スライドイン
//************************************************
void SlideLeftPhase(UI* p)
{
	p->play[ANIMATION_TYPE_SLIDELEFT].pos.x = (-2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDELEFT].dur)) + (2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDELEFT].dur))
	{
		// アニメーションを停止
		StopAnimationPhase(p, ANIMATION_TYPE_SLIDELEFT);
	}
}

//************************************************
// 右スライドイン
//************************************************
void SlideRightPhase(UI* p)
{
	p->play[ANIMATION_TYPE_SLIDERIGHT].pos.x = (2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDERIGHT].dur)) + (-2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDERIGHT].dur))
	{
		// アニメーションを停止
		StopAnimationPhase(p, ANIMATION_TYPE_SLIDERIGHT);
	}
}

//************************************************
// 上スライドアウト
//************************************************
void DisSlideUpPhase(UI* p)
{
	p->play[ANIMATION_TYPE_DISUP].pos.y = (-2000.0f / p->play[ANIMATION_TYPE_DISUP].dur) + (2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISUP].dur))
	{
		// アニメーションを停止
		StopAnimationPhase(p, ANIMATION_TYPE_DISUP);
	}
}

//************************************************
// 下スライドアウト
//************************************************
void DisSlideDownPhase(UI* p)
{
	p->play[ANIMATION_TYPE_DISDOWN].pos.y = (2000.0f / p->play[ANIMATION_TYPE_DISDOWN].dur) + (-2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISDOWN].dur))
	{
		// アニメーションを停止
		StopAnimationPhase(p, ANIMATION_TYPE_DISDOWN);
	}
}

//************************************************
// 左スライドアウト
//************************************************
void DisSlideLeftPhase(UI* p)
{
	p->play[ANIMATION_TYPE_DISLEFT].pos.x = (-2000.0f / p->play[ANIMATION_TYPE_DISLEFT].dur) + (2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISLEFT].dur))
	{
		// アニメーションを停止
		StopAnimationPhase(p, ANIMATION_TYPE_DISLEFT);
	}
}

//************************************************
// 右スライドアウト
//************************************************
void DisSlideRightPhase(UI* p)
{
	p->play[ANIMATION_TYPE_DISRIGHT].pos.x = (2000.0f / p->play[ANIMATION_TYPE_DISRIGHT].dur) + (-2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISRIGHT].dur))
	{
		// アニメーションを停止
		StopAnimationPhase(p, ANIMATION_TYPE_DISRIGHT);
	}
}

//************************************************
// 頂点を展開
//************************************************
void SetVtxPhase(void)
{
	AnimationParam general[AMOUNT_PHASE] = {};	// 再生用情報をまとめる

	for (int i = 0; i < AMOUNT_PHASE; i++)
	{ // 頂点位置用の情報を算出

		if (!g_Phase[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// 再生用の疑似情報をまとめる
			general[i].move += g_Phase[i].play[j].move;
			general[i].pos += g_Phase[i].play[j].pos;
			general[i].rot += g_Phase[i].play[j].rot;
			general[i].span += g_Phase[i].play[j].span;
			general[i].col += g_Phase[i].play[j].col;
		}

		// 角度を算出
		g_Phase[i].angle = atan2f(g_Phase[i].span.x + general[i].span.x, g_Phase[i].span.y + general[i].span.y);

		// 対角線を算出
		g_Phase[i].length = sqrtf((g_Phase[i].span.x + general[i].span.x) * (g_Phase[i].span.x + general[i].span.x) +
			(g_Phase[i].span.y + general[i].span.y) * (g_Phase[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffPhase->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_PHASE; i++, pVtx += AMOUNT_VTX)
	{ // 頂点座標の設定

		pVtx[0].pos =
		{
			g_Phase[i].pos.x + general[i].pos.x + sinf((g_Phase[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Phase[i].angle)) * g_Phase[i].length,
			g_Phase[i].pos.y + general[i].pos.y + cosf((g_Phase[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Phase[i].angle)) * g_Phase[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Phase[i].pos.x + general[i].pos.x + sinf((g_Phase[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Phase[i].angle)) * g_Phase[i].length,
			g_Phase[i].pos.y + general[i].pos.y + cosf((g_Phase[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Phase[i].angle)) * g_Phase[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Phase[i].pos.x + general[i].pos.x + sinf((g_Phase[i].rot.z + general[i].rot.z) - (g_Phase[i].angle)) * g_Phase[i].length,
			g_Phase[i].pos.y + general[i].pos.y + cosf((g_Phase[i].rot.z + general[i].rot.z) - (g_Phase[i].angle)) * g_Phase[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Phase[i].pos.x + general[i].pos.x + sinf((g_Phase[i].rot.z + general[i].rot.z) + (g_Phase[i].angle)) * g_Phase[i].length,
			g_Phase[i].pos.y + general[i].pos.y + cosf((g_Phase[i].rot.z + general[i].rot.z) + (g_Phase[i].angle)) * g_Phase[i].length,
			0.0f
		};

		// 色の反映
		pVtx[0].col = g_Phase[i].col + general[i].col;
		pVtx[1].col = g_Phase[i].col + general[i].col;
		pVtx[2].col = g_Phase[i].col + general[i].col;
		pVtx[3].col = g_Phase[i].col + general[i].col;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPhase->Unlock();
}

//************************************************
// 通常描画処理
//************************************************
void DrawNormalPhase(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int textype = 0;

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPhase, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_PHASE; i++)
	{
		if (!g_Phase[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		textype = g_Phase[i].textype;

		pDevice->SetTexture(0, g_pTexturePhase[textype]);

		// テストの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// テクスチャを読み込む
//************************************************
void ImportTexPhaseNum(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// テクスチャ画像の読込み用
	const char* pFileName = "data\\TEXTURE\\num.png";

	D3DXCreateTextureFromFile(pDevice,
		pFileName,
		&g_pTexturePhaseNum);
}

//************************************************
// 設定情報を読み込む
//************************************************
void ImportInfoPhaseNum(void)
{
	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char str[128] = {};		// 文章を格納
	int i = 0;				// 汎用整数
	int textype = 0;		// テクスチャ情報を取得
	D3DXVECTOR3 pos = {};	// 位置を格納
	D3DXVECTOR3 rot = {};	// 向きを格納
	D3DXVECTOR2 span = {};	// 大きさを格納
	D3DXCOLOR col = {};		// 色を格納

	// Phase情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\UI\\phase_num.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "フェーズ用数字情報の展開に失敗");

#endif	// _DEBUG：ファイル展開の合否
	}

	while (fscanf_s(pFile, "%s", &str[0], 128) != EOF)
	{
		if (strcmp(&str[0], "TEXTYPE") == 0)
		{ // テクスチャタイプを取得
			fscanf_s(pFile, "%s %d", &str[0], 2, &textype);
		}

		if (strcmp(&str[0], "POS") == 0)
		{ // 位置を取得
			fscanf_s(pFile, "%s %f %f %f", &str[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&str[0], "ROT") == 0)
		{ // 向きを取得
			fscanf_s(pFile, "%s %f %f %f", &str[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&str[0], "SPAN") == 0)
		{ // 大きさを取得
			fscanf_s(pFile, "%s %f %f", &str[0], 2, &span.x, &span.y);
		}

		if (strcmp(&str[0], "COL") == 0)
		{ // 色を取得
			fscanf_s(pFile, "%s %f %f %f %f", &str[0], 2, &col.r, &col.g, &col.b, &col.a);
		}

		if (strcmp(&str[0], "END_PARAMSET") == 0)
		{ // 取得した情報を反映

			g_PhaseNum[i].use = true;
			g_PhaseNum[i].textype = textype;
			g_PhaseNum[i].pos = pos;
			g_PhaseNum[i].rot = rot;
			g_PhaseNum[i].span = span;
			g_PhaseNum[i].col = col;

			i++;	// 次の番号へ
		}

		if (strcmp(&str[0], "END_SCRIPT") == 0)
		{
			break;	// 終了
		}
	}

	// ファイルを閉じる
	fclose(pFile);
}

//************************************************
// 頂点バッファの生成
//************************************************
void CreateVtxPhaseNum(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_PHASENUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPhaseNum,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffPhaseNum->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_PHASENUM; i++, pVtx += AMOUNT_VTX)
	{
		// 頂点座標の初期設定
		pVtx[0].pos = { 0.0f, 0.0f, 0.0f };
		pVtx[1].pos = { 0.0f, 0.0f, 0.0f };
		pVtx[2].pos = { 0.0f, 0.0f, 0.0f };
		pVtx[3].pos = { 0.0f, 0.0f, 0.0f };

		// 除算数の初期設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の初期設定
		pVtx[0].tex = { 0.0f, 0.0f };
		pVtx[1].tex = { 1.0f, 0.0f };
		pVtx[2].tex = { 0.0f, 1.0f };
		pVtx[3].tex = { 1.0f, 1.0f };
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPhaseNum->Unlock();
}

//************************************************
// アニメーション管理
//************************************************
void AnimationManagerPhaseNum(void)
{
	for (int i = 0; i < AMOUNT_PHASENUM; i++)
	{
		if (!g_PhaseNum[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// どのアニメーションを再生するのか選別
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_PhaseNum[i].play[j].use)
			{
				// 対応するアニメーションを再生する
				PlayAnimationPhase(&g_PhaseNum[i], j);
			}
		}
	}
}

//************************************************
// 頂点を展開
//************************************************
void SetVtxPhaseNum(void)
{
	AnimationParam general[AMOUNT_PHASENUM] = {};	// 再生用情報をまとめる

	for (int i = 0; i < AMOUNT_PHASENUM; i++)
	{ // 頂点位置用の情報を算出

		if (!g_PhaseNum[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// 再生用の疑似情報をまとめる
			general[i].move += g_PhaseNum[i].play[j].move;
			general[i].pos += g_PhaseNum[i].play[j].pos;
			general[i].rot += g_PhaseNum[i].play[j].rot;
			general[i].span += g_PhaseNum[i].play[j].span;
			general[i].col += g_PhaseNum[i].play[j].col;
		}

		// 角度を算出
		g_PhaseNum[i].angle = atan2f(g_PhaseNum[i].span.x + general[i].span.x, g_PhaseNum[i].span.y + general[i].span.y);

		// 対角線を算出
		g_PhaseNum[i].length = sqrtf((g_PhaseNum[i].span.x + general[i].span.x) * (g_PhaseNum[i].span.x + general[i].span.x) +
			(g_PhaseNum[i].span.y + general[i].span.y) * (g_PhaseNum[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffPhaseNum->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_PHASENUM; i++, pVtx += AMOUNT_VTX)
	{ // 頂点座標の設定

		/*---【かなり無理のある数値の設定】---*/
		int value = 0;	// テクスチャ用の数値を格納

		if (i == 0)
		{
			value = *g_pPhase + 1;	// フェーズ情報を取得
		}
		else if (i == 1)
		{
			value = GetInfoMaxEnemy();	// 敵の出現情報を取得
			value /= 10;
		}
		else if (i == 2)
		{
			value = GetInfoMaxEnemy();	// 敵の出現情報を取得
		}

		pVtx[0].pos =
		{
			g_PhaseNum[i].pos.x + general[i].pos.x + sinf((g_PhaseNum[i].rot.z + general[i].rot.z) - (D3DX_PI - g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			g_PhaseNum[i].pos.y + general[i].pos.y + cosf((g_PhaseNum[i].rot.z + general[i].rot.z) - (D3DX_PI - g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_PhaseNum[i].pos.x + general[i].pos.x + sinf((g_PhaseNum[i].rot.z + general[i].rot.z) + (D3DX_PI - g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			g_PhaseNum[i].pos.y + general[i].pos.y + cosf((g_PhaseNum[i].rot.z + general[i].rot.z) + (D3DX_PI - g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_PhaseNum[i].pos.x + general[i].pos.x + sinf((g_PhaseNum[i].rot.z + general[i].rot.z) - (g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			g_PhaseNum[i].pos.y + general[i].pos.y + cosf((g_PhaseNum[i].rot.z + general[i].rot.z) - (g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_PhaseNum[i].pos.x + general[i].pos.x + sinf((g_PhaseNum[i].rot.z + general[i].rot.z) + (g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			g_PhaseNum[i].pos.y + general[i].pos.y + cosf((g_PhaseNum[i].rot.z + general[i].rot.z) + (g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			0.0f
		};

		// 色の反映
		pVtx[0].col = g_PhaseNum[i].col + general[i].col;
		pVtx[1].col = g_PhaseNum[i].col + general[i].col;
		pVtx[2].col = g_PhaseNum[i].col + general[i].col;
		pVtx[3].col = g_PhaseNum[i].col + general[i].col;

		// 数値を切り替え
		pVtx[0].tex = { value * 0.1f, 0.0f };
		pVtx[1].tex = { (value + 1) * 0.1f, 0.0f };
		pVtx[2].tex = { value * 0.1f, 1.0f };
		pVtx[3].tex = { (value + 1) * 0.1f, 1.0f };
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffPhaseNum->Unlock();
}

//************************************************
// 通常描画処理
//************************************************
void DrawNormalPhaseNum(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPhaseNum, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_PHASENUM; i++)
	{
		if (!g_Phase[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		pDevice->SetTexture(0, g_pTexturePhaseNum);

		// テストの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}