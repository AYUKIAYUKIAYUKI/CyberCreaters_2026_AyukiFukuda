//************************************************
//
// ゲージ表示[bar.cpp]
// Author：福田歩希
//
//************************************************

/*---【インクルードファイル】---*/
#include "bar.h"

// システム
#include "sound.h"

// 諸処理
#include "game.h"
#include "player.h"

// デバッグ用
#ifdef _DEBUG
#include <assert.h>
#endif // _DEBUG

/*---【マクロ定義】---*/
#define AMOUNT_BAR 8	// 武器表示のゲージ

/*---【グローバル変数】---*/
LPDIRECT3DTEXTURE9 g_pTextureBar = NULL;		// テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBar = NULL;	// 頂点バッファのポインタ
UI g_Bar[AMOUNT_BAR];							// ゲージ表示用情報

int g_CT_startBar = 0;					// 武器ゲージが登場するまでの遅延用
int g_Magazine_old[MAX_PLAYER] = {};	// 過去の弾数

/*---【プロトタイプ宣言】---*/
void ImportTexBar(void);		// テクスチャを取得
void ImportInfoBar(int joined);	// 設定情報を取得
void CreateVtxBar(void);		// 頂点バッファの生成

void AnimationManagerBar_First(void);	// アニメーション特別管理
void AnimationManagerBar(void);			// アニメーション管理
void PlayAnimationBar(int i, int type);	// アニメーション再生
void StopAnimationBar(int i, int type);	// アニメーション停止

void VibrationSmallBar(int i);	// 振動：小
void VibrationBigBar(int i);	// 振動：大
void ChangeRedBar(int i);		// 赤く
void FadeAppearBar(int i);		// 出現
void LikeaGummyBar(int i);		// ブニョ
void AppealtoFrontBar(int i);	// チラチラ
void SlideUpBar(int i);			// 上スライドイン
void SlideDownBar(int i);		// 下
void SlideLeftBar(int i);		// 左
void SlideRightBar(int i);		// 右
void DisSlideUpBar(int i);		// 上スライドアウト
void DisSlideDownBar(int i);	// 下
void DisSlideLeftBar(int i);	// 左
void DisSlideRightBar(int i);	// 右

void SetVtxBar(void);		// 展開
void DrawNormalBar(void);	// 通常描画

//************************************************
// 初期処理
//************************************************
void InitBar(int joined)
{
	g_CT_startBar = 0;	// 武器表示が登場するまでの遅延用

	for (int i = 0; i < AMOUNT_BAR; i++)
	{ // ゲージ表示リセット
		g_Bar[i].use = false;
		g_Bar[i].textype = -1;
		g_Bar[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Bar[i].move = { 0.0f, 0.0f, 0.0f };
		g_Bar[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Bar[i].span = { 0.0f, 0.0f };
		g_Bar[i].angle = 0;
		g_Bar[i].length = 0;
		g_Bar[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // アニメーション情報リセット
			g_Bar[i].play[j].use = false;
			g_Bar[i].play[j].dur = 0;
			g_Bar[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_Bar[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_Bar[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_Bar[i].play[j].span = { 0.0f, 0.0f };
			g_Bar[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_Magazine_old[i] = 0;
	}

	// テクスチャを読み込む
	ImportTexBar();

	// 情報を取得する
	ImportInfoBar(joined);

	// 通常頂点バッファの生成
	CreateVtxBar();

	/**********************************/

	g_CT_startBar = 30;	// ゲージが登場するまでの遅延用

	/**********************************/
}

//************************************************
// 終了処理
//************************************************
void UninitBar(void)
{
	if (g_pTextureBar != NULL)
	{ // テクスチャの破棄
		g_pTextureBar->Release();
		g_pTextureBar = NULL;
	}

	if (g_pVtxBuffBar != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffBar->Release();
		g_pVtxBuffBar = NULL;
	}
}

//************************************************
// 更新処理
//************************************************
void UpdateBar(void)
{
	// アニメーション特別管理
	AnimationManagerBar_First();

	// アニメーション管理
	AnimationManagerBar();

	// 通常展開
	SetVtxBar();
}

//************************************************
// 描画処理
//************************************************
void DrawBar(void)
{
	// 通常描画
	DrawNormalBar();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// テクスチャを読み込む
//************************************************
void ImportTexBar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// テクスチャ画像の読込み用
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\num.png",
		&g_pTextureBar);
}

//************************************************
// 設定情報を読み込む
//************************************************
void ImportInfoBar(int joined)
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

	// Bar情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\UI\\bar.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "武器用配置情報の展開に失敗");

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

			g_Bar[i].use = true;
			g_Bar[i].textype = textype;
			g_Bar[i].pos = pos;
			g_Bar[i].rot = rot;
			g_Bar[i].span = span;
			g_Bar[i].col = col;

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
void CreateVtxBar(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_BAR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBar,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffBar->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_BAR; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffBar->Unlock();
}

//************************************************
// アニメーション特別管理
//************************************************
void AnimationManagerBar_First(void)
{
	//g_CT_startBar > 0 ? g_CT_startBar-- : g_CT_startBar = 0;

	//if (g_CT_startBar == 1)
	//{
	//	g_Bar[0].play[ANIMATION_TYPE_FADE].use = true;
	//	g_Bar[0].play[ANIMATION_TYPE_FADE].dur = 60;

	//	g_Bar[0].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	//}
}

//************************************************
// アニメーション管理
//************************************************
void AnimationManagerBar(void)
{
	for (int i = 0; i < AMOUNT_BAR; i++)
	{
		if (!g_Bar[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// どのアニメーションを再生するのか選別
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_Bar[i].play[j].use)
			{
				// 対応するアニメーションを再生する
				PlayAnimationBar(i, j);
			}
		}
	}
}
//************************************************
// 種類に対応したアニメーション再生
//************************************************
void PlayAnimationBar(int id, int type)
{
	switch (type)
	{
	case ANIMATION_TYPE_VIBSMALL:

		VibrationSmallBar(id);	// 振動：小

		break;

	case ANIMATION_TYPE_VIBBIG:

		VibrationBigBar(id);	// 振動：大

		break;

	case ANIMATION_TYPE_RED:

		ChangeRedBar(id);	// 赤くなる

		break;

	case ANIMATION_TYPE_FADE:

		FadeAppearBar(id);	// フェード

		break;

	case ANIMATION_TYPE_GUMMY:

		LikeaGummyBar(id);	// ブニョ

		break;

	case ANIMATION_TYPE_APPEAL:

		AppealtoFrontBar(id);	// バンっ

		break;

	case ANIMATION_TYPE_SLIDEUP:

		SlideUpBar(id);	// 上スライドイン

		break;

	case ANIMATION_TYPE_SLIDEDOWN:

		SlideDownBar(id);	// 下スライドイン

		break;

	case ANIMATION_TYPE_SLIDELEFT:

		SlideLeftBar(id);	// 左スライドイン

		break;

	case ANIMATION_TYPE_SLIDERIGHT:

		SlideRightBar(id);	// 右スライドイン

		break;

	case ANIMATION_TYPE_DISUP:

		DisSlideUpBar(id);	// 上スライドアウト

		break;

	case ANIMATION_TYPE_DISDOWN:

		DisSlideDownBar(id);	// 下スライドアウト

		break;

	case ANIMATION_TYPE_DISLEFT:

		DisSlideLeftBar(id);	// 左スライドアウト

		break;

	case ANIMATION_TYPE_DISRIGHT:

		DisSlideRightBar(id);	// 右スライドアウト

		break;
	}
}

//************************************************
// アニメーション停止
//************************************************
void StopAnimationBar(int id, int type)
{
	g_Bar[id].play[type] =
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
void VibrationSmallBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_VIBSMALL].pos =
	{
		(float)(rand() % 10),
		(float)(rand() % 10),
		0.0f
	};

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_VIBSMALL].dur))
	{
		// アニメーションを停止
		StopAnimationBar(id, ANIMATION_TYPE_VIBSMALL);
	}
}

//************************************************
// 振動：大
//************************************************
void VibrationBigBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_VIBBIG].pos =
	{
		(float)(rand() % 30),
		(float)(rand() % 30),
		0.0f
	};

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_VIBBIG].dur))
	{
		// アニメーションを停止
		StopAnimationBar(id, ANIMATION_TYPE_VIBBIG);
	}
}

//************************************************
// 赤くなる
//************************************************
void ChangeRedBar(int id)
{
	if (g_Bar[id].play[ANIMATION_TYPE_RED].dur > 10)
	{
		g_Bar[id].play[ANIMATION_TYPE_RED].col.g += -0.1f;
		g_Bar[id].play[ANIMATION_TYPE_RED].col.b += -0.1f;
	}
	else
	{
		g_Bar[id].play[ANIMATION_TYPE_RED].col.g += 0.1f;
		g_Bar[id].play[ANIMATION_TYPE_RED].col.b += 0.1f;
	}

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_RED].dur))
	{
		// アニメーションを停止
		StopAnimationBar(id, ANIMATION_TYPE_RED);
	}
}

//************************************************
// 出現
//************************************************
void FadeAppearBar(int id)
{
	if (g_Bar[id].play[ANIMATION_TYPE_FADE].dur >= 40)
	{
		g_Bar[id].play[ANIMATION_TYPE_FADE].col.a = -1.0f;
	}
	else
	{
		g_Bar[id].play[ANIMATION_TYPE_FADE].col.a = (-1.0f / (40 - g_Bar[id].play[ANIMATION_TYPE_FADE].dur));
	}

	if (g_Bar[id].play[ANIMATION_TYPE_FADE].dur == 40)
	{
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_FADE].dur))
	{
		// アニメーションを停止
		StopAnimationBar(id, ANIMATION_TYPE_FADE);
	}
}

//************************************************
// ブニョ
//************************************************
void LikeaGummyBar(int id)
{
	if (g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur > 25)
	{
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur > 20 &&
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur <= 25)
	{
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Bar[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur > 15 &&
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur <= 20)
	{
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Bar[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur > 10 &&
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur <= 15)
	{
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur > 5 &&
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur <= 10)
	{
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Bar[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur <= 5)
	{
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Bar[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur))
	{
		// アニメーションを停止
		StopAnimationBar(id, ANIMATION_TYPE_GUMMY);
	}
}

//************************************************
// チラチラ
//************************************************
void AppealtoFrontBar(int id)
{
	if (g_Bar[id].play[ANIMATION_TYPE_APPEAL].dur == 30)
	{
		g_Bar[id].play[ANIMATION_TYPE_APPEAL].col.a = -1.0f;
	}

	g_Bar[id].play[ANIMATION_TYPE_APPEAL].col.a *= -1.0f;

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_APPEAL].dur))
	{
		g_Bar[id].play[ANIMATION_TYPE_APPEAL].col.a = 0.0f;

		// アニメーションを停止
		StopAnimationBar(id, ANIMATION_TYPE_APPEAL);
	}
}

//************************************************
// 上スライドイン
//************************************************
void SlideUpBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_SLIDEUP].pos.y = (2000.0f / (60 - g_Bar[id].play[ANIMATION_TYPE_SLIDEUP].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_SLIDEUP].dur))
	{
		// アニメーションを停止
		StopAnimationBar(id, ANIMATION_TYPE_SLIDEUP);
	}
}

//************************************************
// 下スライドイン
//************************************************
void SlideDownBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_SLIDEDOWN].pos.y = (-2000.0f / (60 - g_Bar[id].play[ANIMATION_TYPE_SLIDEDOWN].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_SLIDEDOWN].dur))
	{
		// アニメーションを停止
		StopAnimationBar(id, ANIMATION_TYPE_SLIDEDOWN);
	}
}

//************************************************
// 左スライドイン
//************************************************
void SlideLeftBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_SLIDELEFT].pos.x = (-2000.0f / (60 - g_Bar[id].play[ANIMATION_TYPE_SLIDELEFT].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_SLIDELEFT].dur))
	{
		// アニメーションを停止
		StopAnimationBar(id, ANIMATION_TYPE_SLIDELEFT);
	}
}

//************************************************
// 右スライドイン
//************************************************
void SlideRightBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_SLIDERIGHT].pos.x = (2000.0f / (60 - g_Bar[id].play[ANIMATION_TYPE_SLIDERIGHT].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_SLIDERIGHT].dur))
	{
		// アニメーションを停止
		StopAnimationBar(id, ANIMATION_TYPE_SLIDERIGHT);
	}
}

//************************************************
// 上スライドアウト
//************************************************
void DisSlideUpBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_DISUP].pos.y = (-2000.0f / g_Bar[id].play[ANIMATION_TYPE_DISUP].dur) + (2000.0f / 40);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_DISUP].dur))
	{
		// アニメーションを停止
		StopAnimationBar(id, ANIMATION_TYPE_DISUP);
	}
}

//************************************************
// 下スライドアウト
//************************************************
void DisSlideDownBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_DISDOWN].pos.y = (2000.0f / g_Bar[id].play[ANIMATION_TYPE_DISDOWN].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_DISDOWN].dur))
	{
		// アニメーションを停止
		StopAnimationBar(id, ANIMATION_TYPE_DISDOWN);
	}
}

//************************************************
// 左スライドアウト
//************************************************
void DisSlideLeftBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_DISLEFT].pos.x = (-2000.0f / g_Bar[id].play[ANIMATION_TYPE_DISLEFT].dur) + (2000.0f / 40);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_DISLEFT].dur))
	{
		// アニメーションを停止
		StopAnimationBar(id, ANIMATION_TYPE_DISLEFT);
	}
}

//************************************************
// 右スライドアウト
//************************************************
void DisSlideRightBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_DISRIGHT].pos.x = (2000.0f / g_Bar[id].play[ANIMATION_TYPE_DISRIGHT].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_DISRIGHT].dur))
	{
		// アニメーションを停止
		StopAnimationBar(id, ANIMATION_TYPE_DISRIGHT);
	}
}

//************************************************
// 頂点を展開
//************************************************
void SetVtxBar(void)
{
	AnimationParam general[AMOUNT_BAR] = {};	// 再生用情報をまとめる

	for (int i = 0; i < AMOUNT_BAR; i++)
	{ // 頂点位置用の情報を算出

		if (!g_Bar[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// 再生用の疑似情報をまとめる
			general[i].move += g_Bar[i].play[j].move;
			general[i].pos += g_Bar[i].play[j].pos;
			general[i].rot += g_Bar[i].play[j].rot;
			general[i].span += g_Bar[i].play[j].span;
			general[i].col += g_Bar[i].play[j].col;
		}

		// 角度を算出
		g_Bar[i].angle = atan2f(g_Bar[i].span.x + general[i].span.x, g_Bar[i].span.y + general[i].span.y);

		// 対角線を算出
		g_Bar[i].length = sqrtf((g_Bar[i].span.x + general[i].span.x) * (g_Bar[i].span.x + general[i].span.x) +
			(g_Bar[i].span.y + general[i].span.y) * (g_Bar[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	Player* pPlayer = GetInfoPlayer();

	/*---【かなり無理のある数値の設定】---*/
	int value[AMOUNT_BAR] = {};
	int P_id = 0;

	for (int i = 0; i < AMOUNT_BAR; i++)
	{
		if (i % 2 == 0 && i != 0)
		{ // 2回に一度プレイヤー用数値を上昇 

			P_id++;
		}

		value[i] = pPlayer[P_id].PFW.magazine;	// テクスチャ用の数値を格納

		//PrintDebugProc("元 %d P_id %d\n", value[i], P_id);
	}

	for (int i = 0; i < AMOUNT_BAR / 2; i++)
	{
		// 桁数を整合する
		value[(i * 2)] /= 10;
	}

	for (int i = 0; i < AMOUNT_BAR; i++)
	{
		//PrintDebugProc("桁 %d\n", value[i]);
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffBar->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_BAR; i++, pVtx += AMOUNT_VTX)
	{ // 頂点座標の設定

		pVtx[0].pos =
		{
			g_Bar[i].pos.x + general[i].pos.x + sinf((g_Bar[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Bar[i].angle)) * g_Bar[i].length,
			g_Bar[i].pos.y + general[i].pos.y + cosf((g_Bar[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Bar[i].angle)) * g_Bar[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Bar[i].pos.x + general[i].pos.x + sinf((g_Bar[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Bar[i].angle)) * g_Bar[i].length,
			g_Bar[i].pos.y + general[i].pos.y + cosf((g_Bar[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Bar[i].angle)) * g_Bar[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Bar[i].pos.x + general[i].pos.x + sinf((g_Bar[i].rot.z + general[i].rot.z) - (g_Bar[i].angle)) * g_Bar[i].length,
			g_Bar[i].pos.y + general[i].pos.y + cosf((g_Bar[i].rot.z + general[i].rot.z) - (g_Bar[i].angle)) * g_Bar[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Bar[i].pos.x + general[i].pos.x + sinf((g_Bar[i].rot.z + general[i].rot.z) + (g_Bar[i].angle)) * g_Bar[i].length,
			g_Bar[i].pos.y + general[i].pos.y + cosf((g_Bar[i].rot.z + general[i].rot.z) + (g_Bar[i].angle)) * g_Bar[i].length,
			0.0f
		};

		// 色の反映
		pVtx[0].col = g_Bar[i].col + general[i].col;
		pVtx[1].col = g_Bar[i].col + general[i].col;
		pVtx[2].col = g_Bar[i].col + general[i].col;
		pVtx[3].col = g_Bar[i].col + general[i].col;

		// 数値を切り替え
		pVtx[0].tex = { value[i] * 0.1f, 0.0f };
		pVtx[1].tex = { (value[i] + 1) * 0.1f, 0.0f };
		pVtx[2].tex = { value[i] * 0.1f, 1.0f };
		pVtx[3].tex = { (value[i] + 1) * 0.1f, 1.0f };
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffBar->Unlock();

#if 0

	for (int i = 0; i < MAX_PLAYER; i++)
	{ // 過去のライフを記録

		if (!pPlayer[i].use)
		{ // 未使用ならコンティニュー

			continue;
		}

		// 過去のライフと現在のライフが異なればアニメーション
		if (g_Magazine_old[i] != pPlayer[i].PFW.magazine)
		{
			g_Bar[i].play[ANIMATION_TYPE_GUMMY].use = true;
			g_Bar[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
		}

		// 弾の数を記録
		g_Magazine_old[i] = pPlayer[i].PFW.magazine;
	}

#endif
}

//************************************************
// 通常描画処理
//************************************************
void DrawNormalBar(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBar, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_BAR; i++)
	{
		if (!g_Bar[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		pDevice->SetTexture(0, g_pTextureBar);

		// テストの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}