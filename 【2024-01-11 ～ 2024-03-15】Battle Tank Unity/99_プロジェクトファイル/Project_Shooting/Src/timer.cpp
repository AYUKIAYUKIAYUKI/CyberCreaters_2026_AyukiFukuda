//************************************************
//
// タイマー表示[timer.cpp]
// Author：福田歩希
//
//************************************************

/*---【インクルードファイル】---*/
#include "timer.h"

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
#define AMOUNT_SCORE 4		// タイマー表示の最大数

/*---【グローバル変数】---*/
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;		// テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;	// 頂点バッファのポインタ
UI g_Timer[AMOUNT_SCORE];						// タイマー表示用情報

int g_CT_startTimer = 0;	// タイマーが登場するまでの遅延時間

/*---【プロトタイプ宣言】---*/
void ImportTexTimer(void);		// テクスチャを取得
void ImportInfoTimer(void);		// 設定情報を取得
void CreateVtxTimer(void);		// 頂点バッファの生成

void AnimationManager_ArrayTime(void);		// 特別な動き
void AnimationManagerTimer(void);			// アニメーション管理
void PlayAnimationTimer(int i, int type);	// アニメーション再生
void StopAnimationTimer(int i, int type);	// アニメーション停止

void VibrationSmallTimer(int i);	// 振動：小
void VibrationBigTimer(int i);		// 振動：大
void ChangeRedTimer(int i);			// 赤く
void FadeAppearTimer(int i);		// 出現
void LikeaGummyTimer(int i);		// ブニョ
void AppealtoFrontTimer(int i);		// チラチラ
void SlideUpTimer(int i);			// 上スライドイン
void SlideDownTimer(int i);			// 下
void SlideLeftTimer(int i);			// 左
void SlideRightTimer(int i);		// 右
void DisSlideUpTimer(int i);		// 上スライドアウト
void DisSlideDownTimer(int i);		// 下
void DisSlideLeftTimer(int i);		// 左
void DisSlideRightTimer(int i);		// 右

void SetVtxTimer(void);		// 展開
void DrawNormalTimer(void);	// 通常描画

//************************************************
// 初期処理
//************************************************
void InitTimer(int joined)
{
	for (int i = 0; i < AMOUNT_SCORE; i++)
	{ // Timer表示リセット
		g_Timer[i].use = false;
		g_Timer[i].textype = -1;
		g_Timer[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Timer[i].move = { 0.0f, 0.0f, 0.0f };
		g_Timer[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Timer[i].span = { 0.0f, 0.0f };
		g_Timer[i].angle = 0;
		g_Timer[i].length = 0;
		g_Timer[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // アニメーション情報リセット
			g_Timer[i].play[j].use = false;
			g_Timer[i].play[j].dur = 0;
			g_Timer[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_Timer[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_Timer[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_Timer[i].play[j].span = { 0.0f, 0.0f };
			g_Timer[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	// テクスチャを読み込む
	ImportTexTimer();

	// 情報を取得する
	ImportInfoTimer();

	// 通常頂点バッファの生成
	CreateVtxTimer();

	/**********************************/

	g_CT_startTimer = 160 + (10 * joined);	// タイマー表示が登場するまでの遅延用

	/**********************************/
}

//************************************************
// 終了処理
//************************************************
void UninitTimer(void)
{
	if (g_pTextureTimer != NULL)
	{ // テクスチャの破棄
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}

	if (g_pVtxBuffTimer != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//************************************************
// 更新処理
//************************************************
void UpdateTimer(void)
{
	// 特別なやつ
	AnimationManager_ArrayTime();

	// アニメーション管理
	AnimationManagerTimer();

	// 通常展開
	SetVtxTimer();
}

//************************************************
// 描画処理
//************************************************
void DrawTimer(void)
{
	// 通常描画
	DrawNormalTimer();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// テクスチャを読み込む
//************************************************
void ImportTexTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// テクスチャ画像の読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\num.png",
		&g_pTextureTimer);
}

//************************************************
// 設定情報を読み込む
//************************************************
void ImportInfoTimer(void)
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

	// Timer情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\UI\\timer.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "タイマー用配置情報の展開に失敗");

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

			g_Timer[i].use = true;
			g_Timer[i].textype = textype;
			g_Timer[i].pos = pos;
			g_Timer[i].rot = rot;
			g_Timer[i].span = span;
			g_Timer[i].col = col;

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
void CreateVtxTimer(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTimer->Unlock();
}

////************************************************
//// アニメーション選択
////************************************************
//void SelectAnimationTimer(void)
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
//			g_Timer[i].play[ANIMATION_TYPE_VIBSMALL].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_VIBSMALL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_VIBBIG:
//
//			g_Timer[i].play[ANIMATION_TYPE_VIBBIG].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_VIBBIG].dur = 15;
//
//			break;
//
//		case ANIMATION_TYPE_RED:
//
//			g_Timer[i].play[ANIMATION_TYPE_RED].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_RED].dur = 20;
//
//			break;
//
//		case ANIMATION_TYPE_FADE:
//
//			g_Timer[i].play[ANIMATION_TYPE_FADE].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_FADE].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_GUMMY:
//
//			g_Timer[i].play[ANIMATION_TYPE_GUMMY].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_APPEAL:
//
//			g_Timer[i].play[ANIMATION_TYPE_APPEAL].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_APPEAL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEUP:
//
//			g_Timer[i].play[ANIMATION_TYPE_SLIDEUP].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_SLIDEUP].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEDOWN:
//
//			g_Timer[i].play[ANIMATION_TYPE_SLIDEDOWN].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_SLIDEDOWN].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDELEFT:
//
//			g_Timer[i].play[ANIMATION_TYPE_SLIDELEFT].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDERIGHT:
//
//			g_Timer[i].play[ANIMATION_TYPE_SLIDERIGHT].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_SLIDERIGHT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_DISUP:
//
//			g_Timer[i].play[ANIMATION_TYPE_DISUP].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_DISUP].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISDOWN:
//
//			g_Timer[i].play[ANIMATION_TYPE_DISDOWN].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_DISDOWN].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISLEFT:
//
//			g_Timer[i].play[ANIMATION_TYPE_DISLEFT].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_DISLEFT].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISRIGHT:
//
//			g_Timer[i].play[ANIMATION_TYPE_DISRIGHT].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_DISRIGHT].dur = 40;
//
//			break;
//		}
//	}
//}

//************************************************
// 特別なやつ
//************************************************
void AnimationManager_ArrayTime(void)
{
	g_CT_startTimer > 0 ? g_CT_startTimer-- : g_CT_startTimer = 0;

	if (g_CT_startTimer == 1)
	{
		g_Timer[0].play[ANIMATION_TYPE_FADE].use = true;
		g_Timer[0].play[ANIMATION_TYPE_FADE].dur = 60;

		g_Timer[0].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	for (int i = 0; i < AMOUNT_SCORE - 1; i++)
	{
		if (g_Timer[i].play[ANIMATION_TYPE_FADE].dur == 50)
		{
			g_Timer[i + 1].play[ANIMATION_TYPE_FADE].use = true;
			g_Timer[i + 1].play[ANIMATION_TYPE_FADE].dur = 60;

			g_Timer[i + 1].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
	}
}

//************************************************
// アニメーション管理
//************************************************
void AnimationManagerTimer(void)
{
	for (int i = 0; i < AMOUNT_SCORE; i++)
	{
		if (!g_Timer[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// どのアニメーションを再生するのか選別
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_Timer[i].play[j].use)
			{
				// 対応するアニメーションを再生する
				PlayAnimationTimer(i, j);
			}
		}
	}
}

//************************************************
// 種類に対応したアニメーション再生
//************************************************
void PlayAnimationTimer(int id, int type)
{
	switch (type)
	{
	case ANIMATION_TYPE_VIBSMALL:

		VibrationSmallTimer(id);	// 振動：小

		break;

	case ANIMATION_TYPE_VIBBIG:

		VibrationBigTimer(id);	// 振動：大

		break;

	case ANIMATION_TYPE_RED:

		ChangeRedTimer(id);	// 赤くなる

		break;

	case ANIMATION_TYPE_FADE:

		FadeAppearTimer(id);	// フェード

		break;

	case ANIMATION_TYPE_GUMMY:

		LikeaGummyTimer(id);	// ブニョ

		break;

	case ANIMATION_TYPE_APPEAL:

		AppealtoFrontTimer(id);	// バンっ

		break;

	case ANIMATION_TYPE_SLIDEUP:

		SlideUpTimer(id);	// 上スライドイン

		break;

	case ANIMATION_TYPE_SLIDEDOWN:

		SlideDownTimer(id);	// 下スライドイン

		break;

	case ANIMATION_TYPE_SLIDELEFT:

		SlideLeftTimer(id);	// 左スライドイン

		break;

	case ANIMATION_TYPE_SLIDERIGHT:

		SlideRightTimer(id);	// 右スライドイン

		break;

	case ANIMATION_TYPE_DISUP:

		DisSlideUpTimer(id);	// 上スライドアウト

		break;

	case ANIMATION_TYPE_DISDOWN:

		DisSlideDownTimer(id);	// 下スライドアウト

		break;

	case ANIMATION_TYPE_DISLEFT:

		DisSlideLeftTimer(id);	// 左スライドアウト

		break;

	case ANIMATION_TYPE_DISRIGHT:

		DisSlideRightTimer(id);	// 右スライドアウト

		break;
	}
}

//************************************************
// アニメーション停止
//************************************************
void StopAnimationTimer(int id, int type)
{
	g_Timer[id].play[type] =
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
void VibrationSmallTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_VIBSMALL].pos =
	{
		(float)(rand() % 10),
		(float)(rand() % 10),
		0.0f
	};

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_VIBSMALL].dur))
	{
		// アニメーションを停止
		StopAnimationTimer(id, ANIMATION_TYPE_VIBSMALL);
	}
}

//************************************************
// 振動：大
//************************************************
void VibrationBigTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_VIBBIG].pos =
	{
		(float)(rand() % 30),
		(float)(rand() % 30),
		0.0f
	};

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_VIBBIG].dur))
	{
		// アニメーションを停止
		StopAnimationTimer(id, ANIMATION_TYPE_VIBBIG);
	}
}

//************************************************
// 赤くなる
//************************************************
void ChangeRedTimer(int id)
{
	if (g_Timer[id].play[ANIMATION_TYPE_RED].dur > 10)
	{
		g_Timer[id].play[ANIMATION_TYPE_RED].col.g += -0.1f;
		g_Timer[id].play[ANIMATION_TYPE_RED].col.b += -0.1f;
	}
	else
	{
		g_Timer[id].play[ANIMATION_TYPE_RED].col.g += 0.1f;
		g_Timer[id].play[ANIMATION_TYPE_RED].col.b += 0.1f;
	}

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_RED].dur))
	{
		// アニメーションを停止
		StopAnimationTimer(id, ANIMATION_TYPE_RED);
	}
}

//************************************************
// 出現
//************************************************
void FadeAppearTimer(int id)
{
	if (g_Timer[id].play[ANIMATION_TYPE_FADE].dur >= 40)
	{
		g_Timer[id].play[ANIMATION_TYPE_FADE].col.a = -1.0f;
	}
	else
	{
		g_Timer[id].play[ANIMATION_TYPE_FADE].col.a = (-1.0f / (40 - g_Timer[id].play[ANIMATION_TYPE_FADE].dur));
	}

	if (g_Timer[id].play[ANIMATION_TYPE_FADE].dur == 40)
	{
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_FADE].dur))
	{
		// アニメーションを停止
		StopAnimationTimer(id, ANIMATION_TYPE_FADE);
	}
}

//************************************************
// ブニョ
//************************************************
void LikeaGummyTimer(int id)
{
	if (g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur > 25)
	{
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur > 20 &&
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur <= 25)
	{
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Timer[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur > 15 &&
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur <= 20)
	{
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Timer[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur > 10 &&
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur <= 15)
	{
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur > 5 &&
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur <= 10)
	{
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Timer[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur <= 5)
	{
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Timer[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur))
	{
		// アニメーションを停止
		StopAnimationTimer(id, ANIMATION_TYPE_GUMMY);
	}
}

//************************************************
// チラチラ
//************************************************
void AppealtoFrontTimer(int id)
{
	if (g_Timer[id].play[ANIMATION_TYPE_APPEAL].dur == 30)
	{
		g_Timer[id].play[ANIMATION_TYPE_APPEAL].col.a = -1.0f;
	}

	g_Timer[id].play[ANIMATION_TYPE_APPEAL].col.a *= -1.0f;

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_APPEAL].dur))
	{
		g_Timer[id].play[ANIMATION_TYPE_APPEAL].col.a = 0.0f;

		// アニメーションを停止
		StopAnimationTimer(id, ANIMATION_TYPE_APPEAL);
	}
}

//************************************************
// 上スライドイン
//************************************************
void SlideUpTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_SLIDEUP].pos.y = (2000.0f / (60 - g_Timer[id].play[ANIMATION_TYPE_SLIDEUP].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_SLIDEUP].dur))
	{
		// アニメーションを停止
		StopAnimationTimer(id, ANIMATION_TYPE_SLIDEUP);
	}
}

//************************************************
// 下スライドイン
//************************************************
void SlideDownTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_SLIDEDOWN].pos.y = (-2000.0f / (60 - g_Timer[id].play[ANIMATION_TYPE_SLIDEDOWN].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_SLIDEDOWN].dur))
	{
		// アニメーションを停止
		StopAnimationTimer(id, ANIMATION_TYPE_SLIDEDOWN);
	}
}

//************************************************
// 左スライドイン
//************************************************
void SlideLeftTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_SLIDELEFT].pos.x = (-2000.0f / (60 - g_Timer[id].play[ANIMATION_TYPE_SLIDELEFT].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_SLIDELEFT].dur))
	{
		// アニメーションを停止
		StopAnimationTimer(id, ANIMATION_TYPE_SLIDELEFT);
	}
}

//************************************************
// 右スライドイン
//************************************************
void SlideRightTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_SLIDERIGHT].pos.x = (2000.0f / (60 - g_Timer[id].play[ANIMATION_TYPE_SLIDERIGHT].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_SLIDERIGHT].dur))
	{
		// アニメーションを停止
		StopAnimationTimer(id, ANIMATION_TYPE_SLIDERIGHT);
	}
}

//************************************************
// 上スライドアウト
//************************************************
void DisSlideUpTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_DISUP].pos.y = (-2000.0f / g_Timer[id].play[ANIMATION_TYPE_DISUP].dur) + (2000.0f / 40);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_DISUP].dur))
	{
		// アニメーションを停止
		StopAnimationTimer(id, ANIMATION_TYPE_DISUP);
	}
}

//************************************************
// 下スライドアウト
//************************************************
void DisSlideDownTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_DISDOWN].pos.y = (2000.0f / g_Timer[id].play[ANIMATION_TYPE_DISDOWN].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_DISDOWN].dur))
	{
		// アニメーションを停止
		StopAnimationTimer(id, ANIMATION_TYPE_DISDOWN);
	}
}

//************************************************
// 左スライドアウト
//************************************************
void DisSlideLeftTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_DISLEFT].pos.x = (-2000.0f / g_Timer[id].play[ANIMATION_TYPE_DISLEFT].dur) + (2000.0f / 40);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_DISLEFT].dur))
	{
		// アニメーションを停止
		StopAnimationTimer(id, ANIMATION_TYPE_DISLEFT);
	}
}

//************************************************
// 右スライドアウト
//************************************************
void DisSlideRightTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_DISRIGHT].pos.x = (2000.0f / g_Timer[id].play[ANIMATION_TYPE_DISRIGHT].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_DISRIGHT].dur))
	{
		// アニメーションを停止
		StopAnimationTimer(id, ANIMATION_TYPE_DISRIGHT);
	}
}

//************************************************
// 頂点を展開
//************************************************
void SetVtxTimer(void)
{
	AnimationParam general[AMOUNT_SCORE] = {};	// 再生用情報をまとめる

	for (int i = 0; i < AMOUNT_SCORE; i++)
	{ // 頂点位置用の情報を算出

		if (!g_Timer[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// 再生用の疑似情報をまとめる
			general[i].move += g_Timer[i].play[j].move;
			general[i].pos += g_Timer[i].play[j].pos;
			general[i].rot += g_Timer[i].play[j].rot;
			general[i].span += g_Timer[i].play[j].span;
			general[i].col += g_Timer[i].play[j].col;
		}

		// 角度を算出
		g_Timer[i].angle = atan2f(g_Timer[i].span.x + general[i].span.x, g_Timer[i].span.y + general[i].span.y);

		// 対角線を算出
		g_Timer[i].length = sqrtf((g_Timer[i].span.x + general[i].span.x) * (g_Timer[i].span.x + general[i].span.x) +
			(g_Timer[i].span.y + general[i].span.y) * (g_Timer[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;						// 頂点情報へのポインタ
	int phaseTimer = GetInfoPhaseTimer();	// フェーズタイマーを取得

	// 60進数に換算
	int dev = phaseTimer / 60;
	phaseTimer += (40 * dev);

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SCORE; i++, pVtx += AMOUNT_VTX)
	{ // 頂点座標の設定

		int value = phaseTimer % 10;
		phaseTimer /= 10;

		pVtx[0].pos =
		{
			g_Timer[i].pos.x + general[i].pos.x + sinf((g_Timer[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Timer[i].angle)) * g_Timer[i].length,
			g_Timer[i].pos.y + general[i].pos.y + cosf((g_Timer[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Timer[i].angle)) * g_Timer[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Timer[i].pos.x + general[i].pos.x + sinf((g_Timer[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Timer[i].angle)) * g_Timer[i].length,
			g_Timer[i].pos.y + general[i].pos.y + cosf((g_Timer[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Timer[i].angle)) * g_Timer[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Timer[i].pos.x + general[i].pos.x + sinf((g_Timer[i].rot.z + general[i].rot.z) - (g_Timer[i].angle)) * g_Timer[i].length,
			g_Timer[i].pos.y + general[i].pos.y + cosf((g_Timer[i].rot.z + general[i].rot.z) - (g_Timer[i].angle)) * g_Timer[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Timer[i].pos.x + general[i].pos.x + sinf((g_Timer[i].rot.z + general[i].rot.z) + (g_Timer[i].angle)) * g_Timer[i].length,
			g_Timer[i].pos.y + general[i].pos.y + cosf((g_Timer[i].rot.z + general[i].rot.z) + (g_Timer[i].angle)) * g_Timer[i].length,
			0.0f
		};

		// 色の反映
		pVtx[0].col = g_Timer[i].col + general[i].col;
		pVtx[1].col = g_Timer[i].col + general[i].col;
		pVtx[2].col = g_Timer[i].col + general[i].col;
		pVtx[3].col = g_Timer[i].col + general[i].col;

		// テクスチャの反映
		pVtx[0].tex = { value * 0.1f, 0.0f };
		pVtx[1].tex = { (value + 1) * 0.1f, 0.0f };
		pVtx[2].tex = { value * 0.1f, 1.0f };
		pVtx[3].tex = { (value + 1) * 0.1f, 1.0f };
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTimer->Unlock();
}

//************************************************
// 通常描画処理
//************************************************
void DrawNormalTimer(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_SCORE; i++)
	{
		if (!g_Timer[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		pDevice->SetTexture(0, g_pTextureTimer);

		// テストの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}