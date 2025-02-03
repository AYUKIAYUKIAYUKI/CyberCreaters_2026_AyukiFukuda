//************************************************
//
// スコア表示[score.cpp]
// Author：福田歩希
//
//************************************************

/*---【インクルードファイル】---*/
#include "score.h"

// システム
#include "sound.h"

// 諸処理
#include "game.h"

// デバッグ用
#ifdef _DEBUG
#include <assert.h>
#endif // _DEBUG

/*---【マクロ定義】---*/
#define AMOUNT_SCORE 8		// スコア表示の最大数

/*---【グローバル変数】---*/
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;		// テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;	// 頂点バッファのポインタ
UI g_Score[AMOUNT_SCORE];						// スコア表示用情報

int g_Score_old = 0;		// 過去のスコア
int g_CT_startScore = 0;	// スコア表示が登場するまでの遅延用

/*---【プロトタイプ宣言】---*/
void ImportTexScore(void);		// テクスチャを取得
void ImportInfoScore(void);		// 設定情報を取得
void CreateVtxScore(void);		// 頂点バッファの生成

void AnimationManager_Array(void);			// 特別な動き
void AnimationManagerScore(void);			// アニメーション管理
void PlayAnimationScore(int i, int type);	// アニメーション再生
void StopAnimationScore(int i, int type);	// アニメーション停止

void VibrationSmallScore(int i);	// 振動：小
void VibrationBigScore(int i);		// 振動：大
void ChangeRedScore(int i);			// 赤く
void FadeAppearScore(int i);		// 出現
void LikeaGummyScore(int i);		// ブニョ
void AppealtoFrontScore(int i);		// チラチラ
void SlideUpScore(int i);			// 上スライドイン
void SlideDownScore(int i);			// 下
void SlideLeftScore(int i);			// 左
void SlideRightScore(int i);		// 右
void DisSlideUpScore(int i);		// 上スライドアウト
void DisSlideDownScore(int i);		// 下
void DisSlideLeftScore(int i);		// 左
void DisSlideRightScore(int i);		// 右

void SetVtxScore(void);		// 展開
void DrawNormalScore(void);	// 通常描画

//************************************************
// 初期処理
//************************************************
void InitScore(int joined)
{
	g_Score_old = 0;		// 過去のスコア
	g_CT_startScore = 0;	// スコア表示が登場するまでの遅延用

	for (int i = 0; i < AMOUNT_SCORE; i++)
	{ // Score表示リセット
		g_Score[i].use = false;
		g_Score[i].textype = -1;
		g_Score[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Score[i].move = { 0.0f, 0.0f, 0.0f };
		g_Score[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Score[i].span = { 0.0f, 0.0f };
		g_Score[i].angle = 0;
		g_Score[i].length = 0;
		g_Score[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // アニメーション情報リセット
			g_Score[i].play[j].use = false;
			g_Score[i].play[j].dur = 0;
			g_Score[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_Score[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_Score[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_Score[i].play[j].span = { 0.0f, 0.0f };
			g_Score[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	// テクスチャを読み込む
	ImportTexScore();

	// 情報を取得する
	ImportInfoScore();

	// 通常頂点バッファの生成
	CreateVtxScore();

	/**********************************/

	g_CT_startScore = 120 + (10 * joined);	// スコア表示が登場するまでの遅延用

	/**********************************/
}

//************************************************
// 終了処理
//************************************************
void UninitScore(void)
{
	if (g_pTextureScore != NULL)
	{ // テクスチャの破棄
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	if (g_pVtxBuffScore != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//************************************************
// 更新処理
//************************************************
void UpdateScore(void)
{
	// 特別なやつ
	AnimationManager_Array();

	// アニメーション管理
	AnimationManagerScore();

	// 通常展開
	SetVtxScore();
}

//************************************************
// 描画処理
//************************************************
void DrawScore(void)
{
	// 通常描画
	DrawNormalScore();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// テクスチャを読み込む
//************************************************
void ImportTexScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// テクスチャ画像の読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\num.png",
		&g_pTextureScore);
}

//************************************************
// 設定情報を読み込む
//************************************************
void ImportInfoScore(void)
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

	// Score情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\UI\\score.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "スコア用配置情報の展開に失敗");

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

			g_Score[i].use = true;
			g_Score[i].textype = textype;
			g_Score[i].pos = pos;
			g_Score[i].rot = rot;
			g_Score[i].span = span;
			g_Score[i].col = col;

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
void CreateVtxScore(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SCORE; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffScore->Unlock();
}

////************************************************
//// アニメーション選択
////************************************************
//void SelectAnimationScore(void)
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
//			g_Score[i].play[ANIMATION_TYPE_VIBSMALL].use = true;
//			g_Score[i].play[ANIMATION_TYPE_VIBSMALL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_VIBBIG:
//
//			g_Score[i].play[ANIMATION_TYPE_VIBBIG].use = true;
//			g_Score[i].play[ANIMATION_TYPE_VIBBIG].dur = 15;
//
//			break;
//
//		case ANIMATION_TYPE_RED:
//
//			g_Score[i].play[ANIMATION_TYPE_RED].use = true;
//			g_Score[i].play[ANIMATION_TYPE_RED].dur = 20;
//
//			break;
//
//		case ANIMATION_TYPE_FADE:
//
//			g_Score[i].play[ANIMATION_TYPE_FADE].use = true;
//			g_Score[i].play[ANIMATION_TYPE_FADE].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_GUMMY:
//
//			g_Score[i].play[ANIMATION_TYPE_GUMMY].use = true;
//			g_Score[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_APPEAL:
//
//			g_Score[i].play[ANIMATION_TYPE_APPEAL].use = true;
//			g_Score[i].play[ANIMATION_TYPE_APPEAL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEUP:
//
//			g_Score[i].play[ANIMATION_TYPE_SLIDEUP].use = true;
//			g_Score[i].play[ANIMATION_TYPE_SLIDEUP].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEDOWN:
//
//			g_Score[i].play[ANIMATION_TYPE_SLIDEDOWN].use = true;
//			g_Score[i].play[ANIMATION_TYPE_SLIDEDOWN].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDELEFT:
//
//			g_Score[i].play[ANIMATION_TYPE_SLIDELEFT].use = true;
//			g_Score[i].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDERIGHT:
//
//			g_Score[i].play[ANIMATION_TYPE_SLIDERIGHT].use = true;
//			g_Score[i].play[ANIMATION_TYPE_SLIDERIGHT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_DISUP:
//
//			g_Score[i].play[ANIMATION_TYPE_DISUP].use = true;
//			g_Score[i].play[ANIMATION_TYPE_DISUP].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISDOWN:
//
//			g_Score[i].play[ANIMATION_TYPE_DISDOWN].use = true;
//			g_Score[i].play[ANIMATION_TYPE_DISDOWN].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISLEFT:
//
//			g_Score[i].play[ANIMATION_TYPE_DISLEFT].use = true;
//			g_Score[i].play[ANIMATION_TYPE_DISLEFT].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISRIGHT:
//
//			g_Score[i].play[ANIMATION_TYPE_DISRIGHT].use = true;
//			g_Score[i].play[ANIMATION_TYPE_DISRIGHT].dur = 40;
//
//			break;
//		}
//	}
//}

//************************************************
// 特別なやつ
//************************************************
void AnimationManager_Array(void)
{
	g_CT_startScore > 0 ? g_CT_startScore-- : g_CT_startScore = 0;

	if (g_CT_startScore == 1)
	{
		g_Score[0].play[ANIMATION_TYPE_FADE].use = true;
		g_Score[0].play[ANIMATION_TYPE_FADE].dur = 60;

		g_Score[0].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	for (int i = 0; i < AMOUNT_SCORE - 1; i++)
	{
		if (g_Score[i].play[ANIMATION_TYPE_FADE].dur == 50)
		{
			g_Score[i + 1].play[ANIMATION_TYPE_FADE].use = true;
			g_Score[i + 1].play[ANIMATION_TYPE_FADE].dur = 60;

			g_Score[i + 1].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
	}
}

//************************************************
// アニメーション管理
//************************************************
void AnimationManagerScore(void)
{
	for (int i = 0; i < AMOUNT_SCORE; i++)
	{
		if (!g_Score[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// どのアニメーションを再生するのか選別
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_Score[i].play[j].use)
			{
				// 対応するアニメーションを再生する
				PlayAnimationScore(i, j);
			}
		}
	}
}

//************************************************
// 種類に対応したアニメーション再生
//************************************************
void PlayAnimationScore(int id, int type)
{
	switch (type)
	{
	case ANIMATION_TYPE_VIBSMALL:

		VibrationSmallScore(id);	// 振動：小

		break;

	case ANIMATION_TYPE_VIBBIG:

		VibrationBigScore(id);	// 振動：大

		break;

	case ANIMATION_TYPE_RED:

		ChangeRedScore(id);	// 赤くなる

		break;

	case ANIMATION_TYPE_FADE:

		FadeAppearScore(id);	// フェード

		break;

	case ANIMATION_TYPE_GUMMY:

		LikeaGummyScore(id);	// ブニョ

		break;

	case ANIMATION_TYPE_APPEAL:

		AppealtoFrontScore(id);	// バンっ

		break;

	case ANIMATION_TYPE_SLIDEUP:

		SlideUpScore(id);	// 上スライドイン

		break;

	case ANIMATION_TYPE_SLIDEDOWN:

		SlideDownScore(id);	// 下スライドイン

		break;

	case ANIMATION_TYPE_SLIDELEFT:

		SlideLeftScore(id);	// 左スライドイン

		break;

	case ANIMATION_TYPE_SLIDERIGHT:

		SlideRightScore(id);	// 右スライドイン

		break;

	case ANIMATION_TYPE_DISUP:

		DisSlideUpScore(id);	// 上スライドアウト

		break;

	case ANIMATION_TYPE_DISDOWN:

		DisSlideDownScore(id);	// 下スライドアウト

		break;

	case ANIMATION_TYPE_DISLEFT:

		DisSlideLeftScore(id);	// 左スライドアウト

		break;

	case ANIMATION_TYPE_DISRIGHT:

		DisSlideRightScore(id);	// 右スライドアウト

		break;
	}
}

//************************************************
// アニメーション停止
//************************************************
void StopAnimationScore(int id, int type)
{
	g_Score[id].play[type] =
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
void VibrationSmallScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_VIBSMALL].pos =
	{
		(float)(rand() % 10),
		(float)(rand() % 10),
		0.0f
	};

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_VIBSMALL].dur))
	{
		// アニメーションを停止
		StopAnimationScore(id, ANIMATION_TYPE_VIBSMALL);
	}
}

//************************************************
// 振動：大
//************************************************
void VibrationBigScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_VIBBIG].pos =
	{
		(float)(rand() % 30),
		(float)(rand() % 30),
		0.0f
	};

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_VIBBIG].dur))
	{
		// アニメーションを停止
		StopAnimationScore(id, ANIMATION_TYPE_VIBBIG);
	}
}

//************************************************
// 赤くなる
//************************************************
void ChangeRedScore(int id)
{
	if (g_Score[id].play[ANIMATION_TYPE_RED].dur > 10)
	{
		g_Score[id].play[ANIMATION_TYPE_RED].col.g += -0.1f;
		g_Score[id].play[ANIMATION_TYPE_RED].col.b += -0.1f;
	}
	else
	{
		g_Score[id].play[ANIMATION_TYPE_RED].col.g += 0.1f;
		g_Score[id].play[ANIMATION_TYPE_RED].col.b += 0.1f;
	}

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_RED].dur))
	{
		// アニメーションを停止
		StopAnimationScore(id, ANIMATION_TYPE_RED);
	}
}

//************************************************
// 出現
//************************************************
void FadeAppearScore(int id)
{
	if (g_Score[id].play[ANIMATION_TYPE_FADE].dur >= 40)
	{
		g_Score[id].play[ANIMATION_TYPE_FADE].col.a = -1.0f;
	}
	else
	{
		g_Score[id].play[ANIMATION_TYPE_FADE].col.a = (-1.0f / (40 - g_Score[id].play[ANIMATION_TYPE_FADE].dur));
	}

	if (g_Score[id].play[ANIMATION_TYPE_FADE].dur == 40)
	{
		g_Score[id].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Score[id].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_FADE].dur))
	{
		// アニメーションを停止
		StopAnimationScore(id, ANIMATION_TYPE_FADE);
	}
}

//************************************************
// ブニョ
//************************************************
void LikeaGummyScore(int id)
{
	if (g_Score[id].play[ANIMATION_TYPE_GUMMY].dur > 25)
	{
		g_Score[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Score[id].play[ANIMATION_TYPE_GUMMY].dur > 20 &&
		g_Score[id].play[ANIMATION_TYPE_GUMMY].dur <= 25)
	{
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Score[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Score[id].play[ANIMATION_TYPE_GUMMY].dur > 15 &&
		g_Score[id].play[ANIMATION_TYPE_GUMMY].dur <= 20)
	{
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Score[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Score[id].play[ANIMATION_TYPE_GUMMY].dur > 10 &&
		g_Score[id].play[ANIMATION_TYPE_GUMMY].dur <= 15)
	{
		g_Score[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Score[id].play[ANIMATION_TYPE_GUMMY].dur > 5 &&
		g_Score[id].play[ANIMATION_TYPE_GUMMY].dur <= 10)
	{
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Score[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Score[id].play[ANIMATION_TYPE_GUMMY].dur <= 5)
	{
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Score[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_GUMMY].dur))
	{
		// アニメーションを停止
		StopAnimationScore(id, ANIMATION_TYPE_GUMMY);
	}
}

//************************************************
// チラチラ
//************************************************
void AppealtoFrontScore(int id)
{
	if (g_Score[id].play[ANIMATION_TYPE_APPEAL].dur == 30)
	{
		g_Score[id].play[ANIMATION_TYPE_APPEAL].col.a = -1.0f;
	}

	g_Score[id].play[ANIMATION_TYPE_APPEAL].col.a *= -1.0f;

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_APPEAL].dur))
	{
		g_Score[id].play[ANIMATION_TYPE_APPEAL].col.a = 0.0f;

		// アニメーションを停止
		StopAnimationScore(id, ANIMATION_TYPE_APPEAL);
	}
}

//************************************************
// 上スライドイン
//************************************************
void SlideUpScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_SLIDEUP].pos.y = (2000.0f / (60 - g_Score[id].play[ANIMATION_TYPE_SLIDEUP].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_SLIDEUP].dur))
	{
		// アニメーションを停止
		StopAnimationScore(id, ANIMATION_TYPE_SLIDEUP);
	}
}

//************************************************
// 下スライドイン
//************************************************
void SlideDownScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_SLIDEDOWN].pos.y = (-2000.0f / (60 - g_Score[id].play[ANIMATION_TYPE_SLIDEDOWN].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_SLIDEDOWN].dur))
	{
		// アニメーションを停止
		StopAnimationScore(id, ANIMATION_TYPE_SLIDEDOWN);
	}
}

//************************************************
// 左スライドイン
//************************************************
void SlideLeftScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_SLIDELEFT].pos.x = (-2000.0f / (60 - g_Score[id].play[ANIMATION_TYPE_SLIDELEFT].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_SLIDELEFT].dur))
	{
		// アニメーションを停止
		StopAnimationScore(id, ANIMATION_TYPE_SLIDELEFT);
	}
}

//************************************************
// 右スライドイン
//************************************************
void SlideRightScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_SLIDERIGHT].pos.x = (2000.0f / (60 - g_Score[id].play[ANIMATION_TYPE_SLIDERIGHT].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_SLIDERIGHT].dur))
	{
		// アニメーションを停止
		StopAnimationScore(id, ANIMATION_TYPE_SLIDERIGHT);
	}
}

//************************************************
// 上スライドアウト
//************************************************
void DisSlideUpScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_DISUP].pos.y = (-2000.0f / g_Score[id].play[ANIMATION_TYPE_DISUP].dur) + (2000.0f / 40);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_DISUP].dur))
	{
		// アニメーションを停止
		StopAnimationScore(id, ANIMATION_TYPE_DISUP);
	}
}

//************************************************
// 下スライドアウト
//************************************************
void DisSlideDownScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_DISDOWN].pos.y = (2000.0f / g_Score[id].play[ANIMATION_TYPE_DISDOWN].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_DISDOWN].dur))
	{
		// アニメーションを停止
		StopAnimationScore(id, ANIMATION_TYPE_DISDOWN);
	}
}

//************************************************
// 左スライドアウト
//************************************************
void DisSlideLeftScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_DISLEFT].pos.x = (-2000.0f / g_Score[id].play[ANIMATION_TYPE_DISLEFT].dur) + (2000.0f / 40);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_DISLEFT].dur))
	{
		// アニメーションを停止
		StopAnimationScore(id, ANIMATION_TYPE_DISLEFT);
	}
}

//************************************************
// 右スライドアウト
//************************************************
void DisSlideRightScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_DISRIGHT].pos.x = (2000.0f / g_Score[id].play[ANIMATION_TYPE_DISRIGHT].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_DISRIGHT].dur))
	{
		// アニメーションを停止
		StopAnimationScore(id, ANIMATION_TYPE_DISRIGHT);
	}
}

//************************************************
// 頂点を展開
//************************************************
void SetVtxScore(void)
{
	AnimationParam general[AMOUNT_SCORE] = {};	// 再生用情報をまとめる

	for (int i = 0; i < AMOUNT_SCORE; i++)
	{ // 頂点位置用の情報を算出

		if (!g_Score[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// 再生用の疑似情報をまとめる
			general[i].move += g_Score[i].play[j].move;
			general[i].pos += g_Score[i].play[j].pos;
			general[i].rot += g_Score[i].play[j].rot;
			general[i].span += g_Score[i].play[j].span;
			general[i].col += g_Score[i].play[j].col;
		}

		// 角度を算出
		g_Score[i].angle = atan2f(g_Score[i].span.x + general[i].span.x, g_Score[i].span.y + general[i].span.y);

		// 対角線を算出
		g_Score[i].length = sqrtf((g_Score[i].span.x + general[i].span.x) * (g_Score[i].span.x + general[i].span.x) +
			(g_Score[i].span.y + general[i].span.y) * (g_Score[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;				// 頂点情報へのポインタ
	int* score = GetInfoScore();	// スコア取得
	int copy = *score;				// スコアコピー

	if (g_Score_old != *score)
	{ // スコアに変動があれば
		
		for (int i = 0; i < AMOUNT_SCORE; i++)
		{
			g_Score[i].play[ANIMATION_TYPE_GUMMY].use = true;
			g_Score[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
		}
	}

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SCORE; i++, pVtx += AMOUNT_VTX)
	{ // 頂点座標の設定

		int value = copy % 10;
		copy /= 10;

		pVtx[0].pos =
		{
			g_Score[i].pos.x + general[i].pos.x + sinf((g_Score[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Score[i].angle)) * g_Score[i].length,
			g_Score[i].pos.y + general[i].pos.y + cosf((g_Score[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Score[i].angle)) * g_Score[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Score[i].pos.x + general[i].pos.x + sinf((g_Score[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Score[i].angle)) * g_Score[i].length,
			g_Score[i].pos.y + general[i].pos.y + cosf((g_Score[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Score[i].angle)) * g_Score[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Score[i].pos.x + general[i].pos.x + sinf((g_Score[i].rot.z + general[i].rot.z) - (g_Score[i].angle)) * g_Score[i].length,
			g_Score[i].pos.y + general[i].pos.y + cosf((g_Score[i].rot.z + general[i].rot.z) - (g_Score[i].angle)) * g_Score[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Score[i].pos.x + general[i].pos.x + sinf((g_Score[i].rot.z + general[i].rot.z) + (g_Score[i].angle)) * g_Score[i].length,
			g_Score[i].pos.y + general[i].pos.y + cosf((g_Score[i].rot.z + general[i].rot.z) + (g_Score[i].angle)) * g_Score[i].length,
			0.0f
		};

		// 色の反映
		pVtx[0].col = g_Score[i].col + general[i].col;
		pVtx[1].col = g_Score[i].col + general[i].col;
		pVtx[2].col = g_Score[i].col + general[i].col;
		pVtx[3].col = g_Score[i].col + general[i].col;

		// テクスチャの反映
		pVtx[0].tex = { value * 0.1f, 0.0f };
		pVtx[1].tex = { (value + 1) * 0.1f, 0.0f };
		pVtx[2].tex = { value * 0.1f, 1.0f };
		pVtx[3].tex = { (value + 1) * 0.1f, 1.0f };
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();

	g_Score_old = *score;
}

//************************************************
// 通常描画処理
//************************************************
void DrawNormalScore(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_SCORE; i++)
	{
		if (!g_Score[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		pDevice->SetTexture(0, g_pTextureScore);

		// テストの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}