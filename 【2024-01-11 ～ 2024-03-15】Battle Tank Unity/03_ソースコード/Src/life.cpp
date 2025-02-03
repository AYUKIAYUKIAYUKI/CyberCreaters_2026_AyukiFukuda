//************************************************
//
// ライフ表示[life.cpp]
// Author：福田歩希
//
//************************************************

/*---【インクルードファイル】---*/
#include "life.h"

// システム
#include "sound.h"

// 諸処理
#include "player.h"
#include "game.h"

// デバッグ用
#ifdef _DEBUG
#include <assert.h>
#endif // _DEBUG

/*---【マクロ定義】---*/
#define AMOUNT_LIFE 8		// ライフ表示の最大数
#define AMOUNT_LIFENUM	4	// 数字の最大数

/*---【テクスチャ分類】---*/
typedef enum
{
	TEXTURE_TYPE_LIFE_SIRCLE = 0,	// 表示枠
	TEXTURE_TYPE_LIFE_HEART,		// ハート
	TEXTURE_TYPE_LIFE_MAX
} TEXTURE_TYPE_LIFE;

/*---【グローバル変数】---*/
LPDIRECT3DTEXTURE9 g_pTextureLife[TEXTURE_TYPE_LIFE_MAX] = {};	// テクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTextureLifeNum = NULL;					// 数字テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;					// 頂点バッファのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLifeNum = NULL;				// 数字頂点バッファのポインタ
UI g_Life[AMOUNT_LIFE];											// ライフ表示用情報
UI g_LifeNum[AMOUNT_LIFENUM];									// 数字表示用情報

int g_CT_startLife = 0;				// ライフ表示が登場するまでの遅延用
int g_CT_vibHeart = 0;				// ハートがキモく動く時間を管理
int g_Life_old[MAX_PLAYER] = {};	// 過去のライフ

/*---【プロトタイプ宣言】---*/
void ImportTexLife(void);			// テクスチャを取得
void ImportInfoLife(int joined);	// 設定情報を取得
void CreateVtxLife(void);			// 頂点バッファの生成

void AnimationManagerLife_Second(void);		// ライフ表示用アニメーション特別管理
void AnimationManagerLife(void);			// アニメーション管理
void PlayAnimationLife(UI* p, int type);	// アニメーション再生
void StopAnimationLife(UI* p, int type);	// アニメーション停止

void VibrationSmallLife(UI* p);	// 振動：小
void VibrationBigLife(UI* p);	// 振動：大
void ChangeRedLife(UI* p);		// 赤く
void FadeAppearLife(UI* p);		// 出現
void LikeaGummyLife(UI* p);		// ブニョ
void AppealtoFrontLife(UI* p);	// チラチラ
void SlideUpLife(UI* p);		// 上スライドイン
void SlideDownLife(UI* p);		// 下
void SlideLeftLife(UI* p);		// 左
void SlideRightLife(UI* p);		// 右
void DisSlideUpLife(UI* p);		// 上スライドアウト
void DisSlideDownLife(UI* p);	// 下
void DisSlideLeftLife(UI* p);	// 左
void DisSlideRightLife(UI* p);	// 右

void SetVtxLife(void);		// 展開
void DrawNormalLife(void);	// 通常描画

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ImportTexLifeNum(void);		// テクスチャを取得
void ImportInfoLifeNum(int joined);	// 設定情報を取得
void CreateVtxLifeNum(void);		// 頂点バッファの生成

void AnimationManagerLifeNum_EX(void);	// 数字用アニメーション特別管理
void AnimationManagerLifeNum(void);		// 数字アニメーション管理

void SetVtxLifeNum(void);		// 展開
void DrawNormalLifeNum(void);	// 通常描画

//************************************************
// 初期処理
//************************************************
void InitLife(int joined)
{
	g_CT_startLife = 0;	// ライフ表示が登場するまでの遅延用
	g_CT_vibHeart = 0;	// ハートがキモく動く時間を管理

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_Life_old[i] = 0;	// ライフの情報をリセット
	}

	for (int i = 0; i < AMOUNT_LIFE; i++)
	{ // Life表示リセット
		g_Life[i].use = false;
		g_Life[i].textype = -1;
		g_Life[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Life[i].move = { 0.0f, 0.0f, 0.0f };
		g_Life[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Life[i].span = { 0.0f, 0.0f };
		g_Life[i].angle = 0;
		g_Life[i].length = 0;
		g_Life[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // アニメーション情報リセット
			g_Life[i].play[j].use = false;
			g_Life[i].play[j].dur = 0;
			g_Life[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_Life[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_Life[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_Life[i].play[j].span = { 0.0f, 0.0f };
			g_Life[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	// テクスチャを読み込む
	ImportTexLife();

	// 情報を取得する
	ImportInfoLife(joined);

	// 通常頂点バッファの生成
	CreateVtxLife();

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_LIFENUM; i++)
	{ // 数字用情報リセット
		g_LifeNum[i].use = false;
		g_LifeNum[i].textype = -1;
		g_LifeNum[i].pos = { 0.0f, 0.0f, 0.0f };
		g_LifeNum[i].move = { 0.0f, 0.0f, 0.0f };
		g_LifeNum[i].rot = { 0.0f, 0.0f, 0.0f };
		g_LifeNum[i].span = { 0.0f, 0.0f };
		g_LifeNum[i].angle = 0;
		g_LifeNum[i].length = 0;
		g_LifeNum[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // アニメーション情報リセット
			g_LifeNum[i].play[j].use = false;
			g_LifeNum[i].play[j].dur = 0;
			g_LifeNum[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_LifeNum[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_LifeNum[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_LifeNum[i].play[j].span = { 0.0f, 0.0f };
			g_LifeNum[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	// テクスチャを読み込む
	ImportTexLifeNum();

	// 情報を取得する
	ImportInfoLifeNum(joined);

	// 通常頂点バッファの生成
	CreateVtxLifeNum();

	/**********************************/

	g_CT_startLife = 40;	// ライフ表示が登場するまでの遅延用
	g_CT_vibHeart = 180;	// ハートがキモく動く時間

	/**********************************/
}

//************************************************
// 終了処理
//************************************************
void UninitLife(void)
{
	for (int i = 0; i < TEXTURE_TYPE_LIFE_MAX; i++)
	{
		if (g_pTextureLife[i] != NULL)
		{ // テクスチャの破棄
			g_pTextureLife[i]->Release();
			g_pTextureLife[i] = NULL;
		}
	}

	if (g_pVtxBuffLife != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//************************************************
// 更新処理
//************************************************
void UpdateLife(void)
{
	// ライフ用特別アニメーション
	AnimationManagerLife_Second();

	// アニメーション管理
	AnimationManagerLife();

	// 数字用特別アニメーション
	AnimationManagerLifeNum_EX();

	// 数字アニメーション管理
	AnimationManagerLifeNum();

	// 通常展開
	SetVtxLife();

	// 数字通常展開
	SetVtxLifeNum();
}

//************************************************
// 描画処理
//************************************************
void DrawLife(void)
{
	// 通常描画
	DrawNormalLife();

	// 数字通常描画
	DrawNormalLifeNum();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// テクスチャを読み込む
//************************************************
void ImportTexLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// テクスチャ画像の読込み用
	const char* pFileName[TEXTURE_TYPE_LIFE_MAX] =
	{
		"data\\TEXTURE\\lifecircle.png",
		"data\\TEXTURE\\heart.png",
	};

	for (int i = 0; i < TEXTURE_TYPE_LIFE_MAX; i++)
	{ // テクスチャの生成

		if (pFileName[i] == NULL)
		{
			break;	// 画像が無くなっても終了
		}

		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureLife[i]);
	}
}

//************************************************
// 設定情報を読み込む
//************************************************
void ImportInfoLife(int joined)
{
	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char str[128] = {};		// 文章を格納
	int set = 0;			// 何人用か
	int i = 0;				// 汎用整数
	int textype = 0;		// テクスチャ情報を取得
	D3DXVECTOR3 pos = {};	// 位置を格納
	D3DXVECTOR3 rot = {};	// 向きを格納
	D3DXVECTOR2 span = {};	// 大きさを格納
	D3DXCOLOR col = {};		// 色を格納

	// Life情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\UI\\life.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "ライフ用配置情報の展開に失敗");

#endif	// _DEBUG：ファイル展開の合否
	}

	while (fscanf_s(pFile, "%s", &str[0], 128) != EOF)
	{
		if (strcmp(&str[0], "SET") == 0)
		{ // 参加人数を取得
			fscanf_s(pFile, "%s %d", &str[0], 2, &set);
		}

		if (set != joined)
		{ // 対応するセットのみを取得
			continue;
		}

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

			g_Life[i].use = true;
			g_Life[i].textype = textype;
			g_Life[i].pos = pos;
			g_Life[i].rot = rot;
			g_Life[i].span = span;
			g_Life[i].col = col;

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
void CreateVtxLife(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_LIFE; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffLife->Unlock();
}

////************************************************
//// アニメーション選択
////************************************************
//void SelectAnimationLife(void)
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
//			g_Life[i].play[ANIMATION_TYPE_VIBSMALL].use = true;
//			g_Life[i].play[ANIMATION_TYPE_VIBSMALL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_VIBBIG:
//
//			g_Life[i].play[ANIMATION_TYPE_VIBBIG].use = true;
//			g_Life[i].play[ANIMATION_TYPE_VIBBIG].dur = 15;
//
//			break;
//
//		case ANIMATION_TYPE_RED:
//
//			g_Life[i].play[ANIMATION_TYPE_RED].use = true;
//			g_Life[i].play[ANIMATION_TYPE_RED].dur = 20;
//
//			break;
//
//		case ANIMATION_TYPE_FADE:
//
//			g_Life[i].play[ANIMATION_TYPE_FADE].use = true;
//			g_Life[i].play[ANIMATION_TYPE_FADE].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_GUMMY:
//
//			g_Life[i].play[ANIMATION_TYPE_GUMMY].use = true;
//			g_Life[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_APPEAL:
//
//			g_Life[i].play[ANIMATION_TYPE_APPEAL].use = true;
//			g_Life[i].play[ANIMATION_TYPE_APPEAL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEUP:
//
//			g_Life[i].play[ANIMATION_TYPE_SLIDEUP].use = true;
//			g_Life[i].play[ANIMATION_TYPE_SLIDEUP].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEDOWN:
//
//			g_Life[i].play[ANIMATION_TYPE_SLIDEDOWN].use = true;
//			g_Life[i].play[ANIMATION_TYPE_SLIDEDOWN].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDELEFT:
//
//			g_Life[i].play[ANIMATION_TYPE_SLIDELEFT].use = true;
//			g_Life[i].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDERIGHT:
//
//			g_Life[i].play[ANIMATION_TYPE_SLIDERIGHT].use = true;
//			g_Life[i].play[ANIMATION_TYPE_SLIDERIGHT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_DISUP:
//
//			g_Life[i].play[ANIMATION_TYPE_DISUP].use = true;
//			g_Life[i].play[ANIMATION_TYPE_DISUP].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISDOWN:
//
//			g_Life[i].play[ANIMATION_TYPE_DISDOWN].use = true;
//			g_Life[i].play[ANIMATION_TYPE_DISDOWN].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISLEFT:
//
//			g_Life[i].play[ANIMATION_TYPE_DISLEFT].use = true;
//			g_Life[i].play[ANIMATION_TYPE_DISLEFT].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISRIGHT:
//
//			g_Life[i].play[ANIMATION_TYPE_DISRIGHT].use = true;
//			g_Life[i].play[ANIMATION_TYPE_DISRIGHT].dur = 40;
//
//			break;
//		}
//	}
//}

//************************************************
// アニメーション特別管理
//************************************************
void AnimationManagerLife_Second(void)
{
	g_CT_startLife > 0 ? g_CT_startLife-- : g_CT_startLife = 0;

	if (g_CT_startLife == 1)
	{
		g_Life[0].play[ANIMATION_TYPE_FADE].use = true;
		g_Life[0].play[ANIMATION_TYPE_FADE].dur = 60;

		g_Life[0].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	for (int i = 0; i < AMOUNT_LIFE - 1; i++)
	{
		if (!g_Life[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		if (g_Life[i].play[ANIMATION_TYPE_FADE].dur == 50)
		{
			g_Life[i + 1].play[ANIMATION_TYPE_FADE].use = true;
			g_Life[i + 1].play[ANIMATION_TYPE_FADE].dur = 60;

			g_Life[i + 1].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
	}

	/*--------------------------------------------*/

#if 0	// 定期的にキモく動く

	g_CT_vibHeart > 0 ? g_CT_vibHeart-- : g_CT_vibHeart = 0;

	if (g_CT_vibHeart == 1)
	{ // 定期的にキモく動く

		g_Life[TEXTURE_TYPE_LIFE_HEART].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Life[TEXTURE_TYPE_LIFE_HEART].play[ANIMATION_TYPE_GUMMY].dur = 30;

		g_CT_vibHeart = 180;
	}

#endif
}

//************************************************
// アニメーション管理
//************************************************
void AnimationManagerLife(void)
{
	for (int i = 0; i < AMOUNT_LIFE; i++)
	{
		if (!g_Life[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// どのアニメーションを再生するのか選別
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_Life[i].play[j].use)
			{
				// 対応するアニメーションを再生する
				PlayAnimationLife(&g_Life[i], j);
			}
		}
	}
}

//************************************************
// 種類に対応したアニメーション再生
//************************************************
void PlayAnimationLife(UI *p, int type)
{
	switch (type)
	{
	case ANIMATION_TYPE_VIBSMALL:

		VibrationSmallLife(p);	// 振動：小

		break;

	case ANIMATION_TYPE_VIBBIG:

		VibrationBigLife(p);	// 振動：大

		break;

	case ANIMATION_TYPE_RED:

		ChangeRedLife(p);	// 赤くなる

		break;

	case ANIMATION_TYPE_FADE:

		FadeAppearLife(p);	// フェード

		break;

	case ANIMATION_TYPE_GUMMY:

		LikeaGummyLife(p);	// ブニョ

		break;

	case ANIMATION_TYPE_APPEAL:

		AppealtoFrontLife(p);	// バンっ

		break;

	case ANIMATION_TYPE_SLIDEUP:

		SlideUpLife(p);	// 上スライドイン

		break;

	case ANIMATION_TYPE_SLIDEDOWN:

		SlideDownLife(p);	// 下スライドイン

		break;

	case ANIMATION_TYPE_SLIDELEFT:

		SlideLeftLife(p);	// 左スライドイン

		break;

	case ANIMATION_TYPE_SLIDERIGHT:

		SlideRightLife(p);	// 右スライドイン

		break;

	case ANIMATION_TYPE_DISUP:

		DisSlideUpLife(p);	// 上スライドアウト

		break;

	case ANIMATION_TYPE_DISDOWN:

		DisSlideDownLife(p);	// 下スライドアウト

		break;

	case ANIMATION_TYPE_DISLEFT:

		DisSlideLeftLife(p);	// 左スライドアウト

		break;

	case ANIMATION_TYPE_DISRIGHT:

		DisSlideRightLife(p);	// 右スライドアウト

		break;
	}
}

//************************************************
// アニメーション停止
//************************************************
void StopAnimationLife(UI *p, int type)
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
void VibrationSmallLife(UI *p)
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
		StopAnimationLife(p, ANIMATION_TYPE_VIBSMALL);
	}
}

//************************************************
// 振動：大
//************************************************
void VibrationBigLife(UI *p)
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
		StopAnimationLife(p, ANIMATION_TYPE_VIBBIG);
	}
}

//************************************************
// 赤くなる
//************************************************
void ChangeRedLife(UI *p)
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
		StopAnimationLife(p, ANIMATION_TYPE_RED);
	}
}

//************************************************
// 出現
//************************************************
void FadeAppearLife(UI *p)
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
		StopAnimationLife(p, ANIMATION_TYPE_FADE);
	}
}

//************************************************
// ブニョ
//************************************************
void LikeaGummyLife(UI *p)
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
		StopAnimationLife(p, ANIMATION_TYPE_GUMMY);
	}
}

//************************************************
// チラチラ
//************************************************
void AppealtoFrontLife(UI *p)
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
		StopAnimationLife(p, ANIMATION_TYPE_APPEAL);
	}
}

//************************************************
// 上スライドイン
//************************************************
void SlideUpLife(UI *p)
{
	p->play[ANIMATION_TYPE_SLIDEUP].pos.y = (2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDEUP].dur)) + (-2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDEUP].dur))
	{
		// アニメーションを停止
		StopAnimationLife(p, ANIMATION_TYPE_SLIDEUP);
	}
}

//************************************************
// 下スライドイン
//************************************************
void SlideDownLife(UI *p)
{
	p->play[ANIMATION_TYPE_SLIDEDOWN].pos.y = (-2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDEDOWN].dur)) + (2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDEDOWN].dur))
	{
		// アニメーションを停止
		StopAnimationLife(p, ANIMATION_TYPE_SLIDEDOWN);
	}
}

//************************************************
// 左スライドイン
//************************************************
void SlideLeftLife(UI *p)
{
	p->play[ANIMATION_TYPE_SLIDELEFT].pos.x = (-2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDELEFT].dur)) + (2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDELEFT].dur))
	{
		// アニメーションを停止
		StopAnimationLife(p, ANIMATION_TYPE_SLIDELEFT);
	}
}

//************************************************
// 右スライドイン
//************************************************
void SlideRightLife(UI *p)
{
	p->play[ANIMATION_TYPE_SLIDERIGHT].pos.x = (2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDERIGHT].dur)) + (-2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDERIGHT].dur))
	{
		// アニメーションを停止
		StopAnimationLife(p, ANIMATION_TYPE_SLIDERIGHT);
	}
}

//************************************************
// 上スライドアウト
//************************************************
void DisSlideUpLife(UI *p)
{
	p->play[ANIMATION_TYPE_DISUP].pos.y = (-2000.0f / p->play[ANIMATION_TYPE_DISUP].dur) + (2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISUP].dur))
	{
		// アニメーションを停止
		StopAnimationLife(p, ANIMATION_TYPE_DISUP);
	}
}

//************************************************
// 下スライドアウト
//************************************************
void DisSlideDownLife(UI *p)
{
	p->play[ANIMATION_TYPE_DISDOWN].pos.y = (2000.0f / p->play[ANIMATION_TYPE_DISDOWN].dur) + (-2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISDOWN].dur))
	{
		// アニメーションを停止
		StopAnimationLife(p, ANIMATION_TYPE_DISDOWN);
	}
}

//************************************************
// 左スライドアウト
//************************************************
void DisSlideLeftLife(UI *p)
{
	p->play[ANIMATION_TYPE_DISLEFT].pos.x = (-2000.0f / p->play[ANIMATION_TYPE_DISLEFT].dur) + (2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISLEFT].dur))
	{
		// アニメーションを停止
		StopAnimationLife(p, ANIMATION_TYPE_DISLEFT);
	}
}

//************************************************
// 右スライドアウト
//************************************************
void DisSlideRightLife(UI *p)
{
	p->play[ANIMATION_TYPE_DISRIGHT].pos.x = (2000.0f / p->play[ANIMATION_TYPE_DISRIGHT].dur) + (-2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISRIGHT].dur))
	{
		// アニメーションを停止
		StopAnimationLife(p, ANIMATION_TYPE_DISRIGHT);
	}
}

//************************************************
// 頂点を展開
//************************************************
void SetVtxLife(void)
{
	AnimationParam general[AMOUNT_LIFE] = {};	// 再生用情報をまとめる

	for (int i = 0; i < AMOUNT_LIFE; i++)
	{ // 頂点位置用の情報を算出

		if (!g_Life[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// 再生用の疑似情報をまとめる
			general[i].move += g_Life[i].play[j].move;
			general[i].pos += g_Life[i].play[j].pos;
			general[i].rot += g_Life[i].play[j].rot;
			general[i].span += g_Life[i].play[j].span;
			general[i].col += g_Life[i].play[j].col;
		}

		// 角度を算出
		g_Life[i].angle = atan2f(g_Life[i].span.x + general[i].span.x, g_Life[i].span.y + general[i].span.y);

		// 対角線を算出
		g_Life[i].length = sqrtf((g_Life[i].span.x + general[i].span.x) * (g_Life[i].span.x + general[i].span.x) +
			(g_Life[i].span.y + general[i].span.y) * (g_Life[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_LIFE; i++, pVtx += AMOUNT_VTX)
	{ // 頂点座標の設定
		pVtx[0].pos =
		{
			g_Life[i].pos.x + general[i].pos.x + sinf((g_Life[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Life[i].angle)) * g_Life[i].length,
			g_Life[i].pos.y + general[i].pos.y + cosf((g_Life[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Life[i].angle)) * g_Life[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Life[i].pos.x + general[i].pos.x + sinf((g_Life[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Life[i].angle)) * g_Life[i].length,
			g_Life[i].pos.y + general[i].pos.y + cosf((g_Life[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Life[i].angle)) * g_Life[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Life[i].pos.x + general[i].pos.x + sinf((g_Life[i].rot.z + general[i].rot.z) - (g_Life[i].angle)) * g_Life[i].length,
			g_Life[i].pos.y + general[i].pos.y + cosf((g_Life[i].rot.z + general[i].rot.z) - (g_Life[i].angle)) * g_Life[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Life[i].pos.x + general[i].pos.x + sinf((g_Life[i].rot.z + general[i].rot.z) + (g_Life[i].angle)) * g_Life[i].length,
			g_Life[i].pos.y + general[i].pos.y + cosf((g_Life[i].rot.z + general[i].rot.z) + (g_Life[i].angle)) * g_Life[i].length,
			0.0f
		};

		// 色の反映
		pVtx[0].col = g_Life[i].col + general[i].col;
		pVtx[1].col = g_Life[i].col + general[i].col;
		pVtx[2].col = g_Life[i].col + general[i].col;
		pVtx[3].col = g_Life[i].col + general[i].col;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();
}

//************************************************
// 通常描画処理
//************************************************
void DrawNormalLife(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int textype = 0;

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_LIFE; i++)
	{
		if (!g_Life[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		textype = g_Life[i].textype;

		pDevice->SetTexture(0, g_pTextureLife[textype]);

		// テストの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// テクスチャを読み込む
//************************************************
void ImportTexLifeNum(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// テクスチャ画像の読込み用
	const char* pFileName = "data\\TEXTURE\\num.png";

	D3DXCreateTextureFromFile(pDevice,
		pFileName,
		&g_pTextureLifeNum);
}

//************************************************
// 設定情報を読み込む
//************************************************
void ImportInfoLifeNum(int joined)
{
	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char str[128] = {};		// 文章を格納
	int set = 0;			// 何人用か
	int i = 0;				// 汎用整数
	int textype = 0;		// テクスチャ情報を取得
	D3DXVECTOR3 pos = {};	// 位置を格納
	D3DXVECTOR3 rot = {};	// 向きを格納
	D3DXVECTOR2 span = {};	// 大きさを格納
	D3DXCOLOR col = {};		// 色を格納

	// Life情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\UI\\life_num.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "ライフ用数字情報の展開に失敗");

#endif	// _DEBUG：ファイル展開の合否
	}

	while (fscanf_s(pFile, "%s", &str[0], 128) != EOF)
	{
		if (strcmp(&str[0], "SET") == 0)
		{ // 参加人数を取得
			fscanf_s(pFile, "%s %d", &str[0], 2, &set);
		}

		if (set != joined)
		{ // 対応するセットのみを取得
			continue;
		}

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

			g_LifeNum[i].use = true;
			g_LifeNum[i].textype = textype;
			g_LifeNum[i].pos = pos;
			g_LifeNum[i].rot = rot;
			g_LifeNum[i].span = span;
			g_LifeNum[i].col = col;

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
void CreateVtxLifeNum(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_LIFENUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLifeNum,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffLifeNum->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_LIFENUM; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffLifeNum->Unlock();
}

//************************************************
// アニメーション特別管理
//************************************************
void AnimationManagerLifeNum_EX(void)
{
	if (g_CT_startLife == 1)
	{
		g_LifeNum[0].play[ANIMATION_TYPE_FADE].use = true;
		g_LifeNum[0].play[ANIMATION_TYPE_FADE].dur = 70;

		g_LifeNum[0].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	for (int i = 0; i < AMOUNT_LIFENUM - 1; i++)
	{
		if (!g_LifeNum[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		if (g_LifeNum[i].play[ANIMATION_TYPE_FADE].dur == 50)
		{
			g_LifeNum[i + 1].play[ANIMATION_TYPE_FADE].use = true;
			g_LifeNum[i + 1].play[ANIMATION_TYPE_FADE].dur = 70;

			g_LifeNum[i + 1].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
	}
}

//************************************************
// アニメーション管理
//************************************************
void AnimationManagerLifeNum(void)
{
	for (int i = 0; i < AMOUNT_LIFENUM; i++)
	{
		if (!g_LifeNum[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// どのアニメーションを再生するのか選別
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_LifeNum[i].play[j].use)
			{
				// 対応するアニメーションを再生する
				PlayAnimationLife(&g_LifeNum[i], j);
			}
		}
	}
}

//************************************************
// 頂点を展開
//************************************************
void SetVtxLifeNum(void)
{
	AnimationParam general[AMOUNT_LIFENUM] = {};	// 再生用情報をまとめる

	for (int i = 0; i < AMOUNT_LIFENUM; i++)
	{ // 頂点位置用の情報を算出

		if (!g_LifeNum[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// 再生用の疑似情報をまとめる
			general[i].move += g_LifeNum[i].play[j].move;
			general[i].pos += g_LifeNum[i].play[j].pos;
			general[i].rot += g_LifeNum[i].play[j].rot;
			general[i].span += g_LifeNum[i].play[j].span;
			general[i].col += g_LifeNum[i].play[j].col;
		}

		// 角度を算出
		g_LifeNum[i].angle = atan2f(g_LifeNum[i].span.x + general[i].span.x, g_LifeNum[i].span.y + general[i].span.y);

		// 対角線を算出
		g_LifeNum[i].length = sqrtf((g_LifeNum[i].span.x + general[i].span.x) * (g_LifeNum[i].span.x + general[i].span.x) +
			(g_LifeNum[i].span.y + general[i].span.y) * (g_LifeNum[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;	// 頂点情報へのポインタ
	Player* pPlayer = GetInfoPlayer();

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffLifeNum->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_LIFENUM; i++, pVtx += AMOUNT_VTX)
	{ // 頂点座標の設定

		/*---【かなり無理のある数値の設定】---*/
		int value = pPlayer[i].param.HP;	// テクスチャ用の数値を格納

		pVtx[0].pos =
		{
			g_LifeNum[i].pos.x + general[i].pos.x + sinf((g_LifeNum[i].rot.z + general[i].rot.z) - (D3DX_PI - g_LifeNum[i].angle)) * g_LifeNum[i].length,
			g_LifeNum[i].pos.y + general[i].pos.y + cosf((g_LifeNum[i].rot.z + general[i].rot.z) - (D3DX_PI - g_LifeNum[i].angle)) * g_LifeNum[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_LifeNum[i].pos.x + general[i].pos.x + sinf((g_LifeNum[i].rot.z + general[i].rot.z) + (D3DX_PI - g_LifeNum[i].angle)) * g_LifeNum[i].length,
			g_LifeNum[i].pos.y + general[i].pos.y + cosf((g_LifeNum[i].rot.z + general[i].rot.z) + (D3DX_PI - g_LifeNum[i].angle)) * g_LifeNum[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_LifeNum[i].pos.x + general[i].pos.x + sinf((g_LifeNum[i].rot.z + general[i].rot.z) - (g_LifeNum[i].angle)) * g_LifeNum[i].length,
			g_LifeNum[i].pos.y + general[i].pos.y + cosf((g_LifeNum[i].rot.z + general[i].rot.z) - (g_LifeNum[i].angle)) * g_LifeNum[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_LifeNum[i].pos.x + general[i].pos.x + sinf((g_LifeNum[i].rot.z + general[i].rot.z) + (g_LifeNum[i].angle)) * g_LifeNum[i].length,
			g_LifeNum[i].pos.y + general[i].pos.y + cosf((g_LifeNum[i].rot.z + general[i].rot.z) + (g_LifeNum[i].angle)) * g_LifeNum[i].length,
			0.0f
		};

		// 色の反映
		pVtx[0].col = g_LifeNum[i].col + general[i].col;
		pVtx[1].col = g_LifeNum[i].col + general[i].col;
		pVtx[2].col = g_LifeNum[i].col + general[i].col;
		pVtx[3].col = g_LifeNum[i].col + general[i].col;

		// 数値を切り替え
		pVtx[0].tex = { value * 0.1f, 0.0f };
		pVtx[1].tex = { (value + 1) * 0.1f, 0.0f };
		pVtx[2].tex = { value * 0.1f, 1.0f };
		pVtx[3].tex = { (value + 1) * 0.1f, 1.0f };
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffLifeNum->Unlock();

	for (int i = 0; i < MAX_PLAYER; i++)
	{ // 過去のライフを記録

		if (!pPlayer[i].use)
		{ // 未使用ならコンティニュー

			continue;
		}

		// 過去のライフと現在のライフが異なればアニメーション
		if (g_Life_old[i] != pPlayer[i].param.HP)
		{
			if (g_Life_old[i] > pPlayer[i].param.HP)
			{ // 低い場合

				// 枠
				g_Life[i * 2].play[ANIMATION_TYPE_VIBSMALL].use = true;
				g_Life[i * 2].play[ANIMATION_TYPE_RED].use = true;
				g_Life[i * 2].play[ANIMATION_TYPE_VIBSMALL].dur = 20;
				g_Life[i * 2].play[ANIMATION_TYPE_RED].dur = 20;
				
				// ハート
				g_Life[i * 2 + 1].play[ANIMATION_TYPE_VIBSMALL].use = true;
				g_Life[i * 2 + 1].play[ANIMATION_TYPE_VIBSMALL].dur = 30;

				// 数字
				g_LifeNum[i].play[ANIMATION_TYPE_GUMMY].use = true;
				g_LifeNum[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
			}
			else
			{ // 高い場合

				// ハート
				g_Life[i * 2 + 1].play[ANIMATION_TYPE_GUMMY].use = true;
				g_Life[i * 2 + 1].play[ANIMATION_TYPE_GUMMY].dur = 30;
			
				// 数字
				g_LifeNum[i].play[ANIMATION_TYPE_GUMMY].use = true;
				g_LifeNum[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
			}
		}

		g_Life_old[i] = pPlayer[i].param.HP;
	}
}

//************************************************
// 通常描画処理
//************************************************
void DrawNormalLifeNum(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLifeNum, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_LIFENUM; i++)
	{
		if (!g_Life[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		pDevice->SetTexture(0, g_pTextureLifeNum);

		// テストの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}