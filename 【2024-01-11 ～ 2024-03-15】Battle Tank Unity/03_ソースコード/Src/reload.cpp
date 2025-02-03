//************************************************
//
// リロード表示[reload.cpp]
// Author：福田歩希
//
//************************************************

/*---【インクルードファイル】---*/
#include "reload.h"

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
#define AMOUNT_RELOAD 4	// リロード表示の最大数

/*---【グローバル変数】---*/
LPDIRECT3DTEXTURE9 g_pTextureReload = {};			// テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffReload = NULL;	// 頂点バッファのポインタ
UI g_Reload[AMOUNT_RELOAD];							// リロード表示用情報

int g_CT_startReload = 0;	// リロード表示が登場するまでの遅延用

/*---【プロトタイプ宣言】---*/
void ImportTexReload(void);			// テクスチャを取得
void ImportInfoReload(int joined);	// 設定情報を取得
void CreateVtxReload(void);			// 頂点バッファの生成

void AnimationManagerReload_EX(void);		// アニメーション特別管理
void AnimationManagerReload(void);			// アニメーション管理
void PlayAnimationReload(int i, int type);	// アニメーション再生
void StopAnimationReload(int i, int type);	// アニメーション停止

void VibrationSmallReload(int i);	// 振動：小
void VibrationBigReload(int i);		// 振動：大
void ChangeRedReload(int i);		// 赤く
void FadeAppearReload(int i);		// 出現
void LikeaGummyReload(int i);		// ブニョ
void AppealtoFrontReload(int i);	// チラチラ
void SlideUpReload(int i);			// 上スライドイン
void SlideDownReload(int i);		// 下
void SlideLeftReload(int i);		// 左
void SlideRightReload(int i);		// 右
void DisSlideUpReload(int i);		// 上スライドアウト
void DisSlideDownReload(int i);		// 下
void DisSlideLeftReload(int i);		// 左
void DisSlideRightReload(int i);	// 右

void SetVtxReload(void);		// 展開
void DrawNormalReload(void);	// 通常描画

//************************************************
// 初期処理
//************************************************
void InitReload(int joined)
{
	g_CT_startReload = 0;	// リロード表示が登場するまでの遅延用

	for (int i = 0; i < AMOUNT_RELOAD; i++)
	{ // Reload表示リセット
		g_Reload[i].use = false;
		g_Reload[i].textype = -1;
		g_Reload[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Reload[i].move = { 0.0f, 0.0f, 0.0f };
		g_Reload[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Reload[i].span = { 0.0f, 0.0f };
		g_Reload[i].angle = 0;
		g_Reload[i].length = 0;
		g_Reload[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // アニメーション情報リセット
			g_Reload[i].play[j].use = false;
			g_Reload[i].play[j].dur = 0;
			g_Reload[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_Reload[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_Reload[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_Reload[i].play[j].span = { 0.0f, 0.0f };
			g_Reload[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	// テクスチャを読み込む
	ImportTexReload();

	// 情報を取得する
	ImportInfoReload(joined);

	// 通常頂点バッファの生成
	CreateVtxReload();

	/**********************************/

	g_CT_startReload = 30;	// リロード表示が登場するまでの遅延用

	/**********************************/
}

//************************************************
// 終了処理
//************************************************
void UninitReload(void)
{
	if (g_pTextureReload != NULL)
	{ // テクスチャの破棄
		g_pTextureReload->Release();
		g_pTextureReload = NULL;
	}

	if (g_pVtxBuffReload != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffReload->Release();
		g_pVtxBuffReload = NULL;
	}
}

//************************************************
// 更新処理
//************************************************
void UpdateReload(void)
{
	// アニメーション特別管理
	AnimationManagerReload_EX();

	// アニメーション管理
	AnimationManagerReload();

	// 通常展開
	SetVtxReload();
}

//************************************************
// 描画処理
//************************************************
void DrawReload(void)
{
	// 通常描画
	DrawNormalReload();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// テクスチャを読み込む
//************************************************
void ImportTexReload(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// テクスチャ画像の読込み用
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\rere.png",
		&g_pTextureReload);
}

//************************************************
// 設定情報を読み込む
//************************************************
void ImportInfoReload(int joined)
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

	// Reload情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\UI\\reload.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "リロード用配置情報の展開に失敗");

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

			g_Reload[i].use = true;
			g_Reload[i].textype = textype;
			g_Reload[i].pos = pos;
			g_Reload[i].rot = rot;
			g_Reload[i].span = span;
			g_Reload[i].col = col;

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
void CreateVtxReload(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_RELOAD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffReload,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffReload->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_RELOAD; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffReload->Unlock();
}

//************************************************
// アニメーション特別管理
//************************************************
void AnimationManagerReload_EX(void)
{
	Player* pPlayer = GetInfoPlayer();

	for (int i = 0; i < AMOUNT_RELOAD; i++)
	{
		if (!g_Reload[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		if (pPlayer[i].PFW.empty)
		{
			g_Reload[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
		else
		{
			g_Reload[i].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}
}

//************************************************
// アニメーション管理
//************************************************
void AnimationManagerReload(void)
{
	for (int i = 0; i < AMOUNT_RELOAD; i++)
	{
		if (!g_Reload[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// どのアニメーションを再生するのか選別
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_Reload[i].play[j].use)
			{
				// 対応するアニメーションを再生する
				PlayAnimationReload(i, j);
			}
		}
	}
}

//************************************************
// 種類に対応したアニメーション再生
//************************************************
void PlayAnimationReload(int id, int type)
{
	switch (type)
	{
	case ANIMATION_TYPE_VIBSMALL:

		VibrationSmallReload(id);	// 振動：小

		break;

	case ANIMATION_TYPE_VIBBIG:

		VibrationBigReload(id);	// 振動：大

		break;

	case ANIMATION_TYPE_RED:

		ChangeRedReload(id);	// 赤くなる

		break;

	case ANIMATION_TYPE_FADE:

		FadeAppearReload(id);	// フェード

		break;

	case ANIMATION_TYPE_GUMMY:

		LikeaGummyReload(id);	// ブニョ

		break;

	case ANIMATION_TYPE_APPEAL:

		AppealtoFrontReload(id);	// バンっ

		break;

	case ANIMATION_TYPE_SLIDEUP:

		SlideUpReload(id);	// 上スライドイン

		break;

	case ANIMATION_TYPE_SLIDEDOWN:

		SlideDownReload(id);	// 下スライドイン

		break;

	case ANIMATION_TYPE_SLIDELEFT:

		SlideLeftReload(id);	// 左スライドイン

		break;

	case ANIMATION_TYPE_SLIDERIGHT:

		SlideRightReload(id);	// 右スライドイン

		break;

	case ANIMATION_TYPE_DISUP:

		DisSlideUpReload(id);	// 上スライドアウト

		break;

	case ANIMATION_TYPE_DISDOWN:

		DisSlideDownReload(id);	// 下スライドアウト

		break;

	case ANIMATION_TYPE_DISLEFT:

		DisSlideLeftReload(id);	// 左スライドアウト

		break;

	case ANIMATION_TYPE_DISRIGHT:

		DisSlideRightReload(id);	// 右スライドアウト

		break;
	}
}

//************************************************
// アニメーション停止
//************************************************
void StopAnimationReload(int id, int type)
{
	g_Reload[id].play[type] =
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
void VibrationSmallReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_VIBSMALL].pos =
	{
		(float)(rand() % 10),
		(float)(rand() % 10),
		0.0f
	};

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_VIBSMALL].dur))
	{
		// アニメーションを停止
		StopAnimationReload(id, ANIMATION_TYPE_VIBSMALL);
	}
}

//************************************************
// 振動：大
//************************************************
void VibrationBigReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_VIBBIG].pos =
	{
		(float)(rand() % 30),
		(float)(rand() % 30),
		0.0f
	};

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_VIBBIG].dur))
	{
		// アニメーションを停止
		StopAnimationReload(id, ANIMATION_TYPE_VIBBIG);
	}
}

//************************************************
// 赤くなる
//************************************************
void ChangeRedReload(int id)
{
	if (g_Reload[id].play[ANIMATION_TYPE_RED].dur > 10)
	{
		g_Reload[id].play[ANIMATION_TYPE_RED].col.g += -0.1f;
		g_Reload[id].play[ANIMATION_TYPE_RED].col.b += -0.1f;
	}
	else
	{
		g_Reload[id].play[ANIMATION_TYPE_RED].col.g += 0.1f;
		g_Reload[id].play[ANIMATION_TYPE_RED].col.b += 0.1f;
	}

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_RED].dur))
	{
		// アニメーションを停止
		StopAnimationReload(id, ANIMATION_TYPE_RED);
	}
}

//************************************************
// 出現
//************************************************
void FadeAppearReload(int id)
{
	if (g_Reload[id].play[ANIMATION_TYPE_FADE].dur >= 40)
	{
		g_Reload[id].play[ANIMATION_TYPE_FADE].col.a = -1.0f;
	}
	else
	{
		g_Reload[id].play[ANIMATION_TYPE_FADE].col.a = (-1.0f / (40 - g_Reload[id].play[ANIMATION_TYPE_FADE].dur));
	}

	if (g_Reload[id].play[ANIMATION_TYPE_FADE].dur == 40)
	{
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_FADE].dur))
	{
		// アニメーションを停止
		StopAnimationReload(id, ANIMATION_TYPE_FADE);
	}
}

//************************************************
// ブニョ
//************************************************
void LikeaGummyReload(int id)
{
	if (g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur > 25)
	{
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur > 20 &&
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur <= 25)
	{
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Reload[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur > 15 &&
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur <= 20)
	{
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Reload[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur > 10 &&
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur <= 15)
	{
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur > 5 &&
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur <= 10)
	{
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Reload[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur <= 5)
	{
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Reload[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur))
	{
		// アニメーションを停止
		StopAnimationReload(id, ANIMATION_TYPE_GUMMY);
	}
}

//************************************************
// チラチラ
//************************************************
void AppealtoFrontReload(int id)
{
	if (g_Reload[id].play[ANIMATION_TYPE_APPEAL].dur == 30)
	{
		g_Reload[id].play[ANIMATION_TYPE_APPEAL].col.a = -1.0f;
	}

	g_Reload[id].play[ANIMATION_TYPE_APPEAL].col.a *= -1.0f;

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_APPEAL].dur))
	{
		g_Reload[id].play[ANIMATION_TYPE_APPEAL].col.a = 0.0f;

		// アニメーションを停止
		StopAnimationReload(id, ANIMATION_TYPE_APPEAL);
	}
}

//************************************************
// 上スライドイン
//************************************************
void SlideUpReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_SLIDEUP].pos.y = (2000.0f / (60 - g_Reload[id].play[ANIMATION_TYPE_SLIDEUP].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_SLIDEUP].dur))
	{
		// アニメーションを停止
		StopAnimationReload(id, ANIMATION_TYPE_SLIDEUP);
	}
}

//************************************************
// 下スライドイン
//************************************************
void SlideDownReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_SLIDEDOWN].pos.y = (-2000.0f / (60 - g_Reload[id].play[ANIMATION_TYPE_SLIDEDOWN].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_SLIDEDOWN].dur))
	{
		// アニメーションを停止
		StopAnimationReload(id, ANIMATION_TYPE_SLIDEDOWN);
	}
}

//************************************************
// 左スライドイン
//************************************************
void SlideLeftReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_SLIDELEFT].pos.x = (-2000.0f / (60 - g_Reload[id].play[ANIMATION_TYPE_SLIDELEFT].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_SLIDELEFT].dur))
	{
		// アニメーションを停止
		StopAnimationReload(id, ANIMATION_TYPE_SLIDELEFT);
	}
}

//************************************************
// 右スライドイン
//************************************************
void SlideRightReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_SLIDERIGHT].pos.x = (2000.0f / (60 - g_Reload[id].play[ANIMATION_TYPE_SLIDERIGHT].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_SLIDERIGHT].dur))
	{
		// アニメーションを停止
		StopAnimationReload(id, ANIMATION_TYPE_SLIDERIGHT);
	}
}

//************************************************
// 上スライドアウト
//************************************************
void DisSlideUpReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_DISUP].pos.y = (-2000.0f / g_Reload[id].play[ANIMATION_TYPE_DISUP].dur) + (2000.0f / 40);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_DISUP].dur))
	{
		// アニメーションを停止
		StopAnimationReload(id, ANIMATION_TYPE_DISUP);
	}
}

//************************************************
// 下スライドアウト
//************************************************
void DisSlideDownReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_DISDOWN].pos.y = (2000.0f / g_Reload[id].play[ANIMATION_TYPE_DISDOWN].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_DISDOWN].dur))
	{
		// アニメーションを停止
		StopAnimationReload(id, ANIMATION_TYPE_DISDOWN);
	}
}

//************************************************
// 左スライドアウト
//************************************************
void DisSlideLeftReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_DISLEFT].pos.x = (-2000.0f / g_Reload[id].play[ANIMATION_TYPE_DISLEFT].dur) + (2000.0f / 40);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_DISLEFT].dur))
	{
		// アニメーションを停止
		StopAnimationReload(id, ANIMATION_TYPE_DISLEFT);
	}
}

//************************************************
// 右スライドアウト
//************************************************
void DisSlideRightReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_DISRIGHT].pos.x = (2000.0f / g_Reload[id].play[ANIMATION_TYPE_DISRIGHT].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_DISRIGHT].dur))
	{
		// アニメーションを停止
		StopAnimationReload(id, ANIMATION_TYPE_DISRIGHT);
	}
}

//************************************************
// 頂点を展開
//************************************************
void SetVtxReload(void)
{
	AnimationParam general[AMOUNT_RELOAD] = {};	// 再生用情報をまとめる

	for (int i = 0; i < AMOUNT_RELOAD; i++)
	{ // 頂点位置用の情報を算出

		if (!g_Reload[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// 再生用の疑似情報をまとめる
			general[i].move += g_Reload[i].play[j].move;
			general[i].pos += g_Reload[i].play[j].pos;
			general[i].rot += g_Reload[i].play[j].rot;
			general[i].span += g_Reload[i].play[j].span;
			general[i].col += g_Reload[i].play[j].col;
		}

		// 角度を算出
		g_Reload[i].angle = atan2f(g_Reload[i].span.x + general[i].span.x, g_Reload[i].span.y + general[i].span.y);

		// 対角線を算出
		g_Reload[i].length = sqrtf((g_Reload[i].span.x + general[i].span.x) * (g_Reload[i].span.x + general[i].span.x) +
			(g_Reload[i].span.y + general[i].span.y) * (g_Reload[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffReload->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_RELOAD; i++, pVtx += AMOUNT_VTX)
	{ // 頂点座標の設定

		pVtx[0].pos =
		{
			g_Reload[i].pos.x + general[i].pos.x + sinf((g_Reload[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Reload[i].angle)) * g_Reload[i].length,
			g_Reload[i].pos.y + general[i].pos.y + cosf((g_Reload[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Reload[i].angle)) * g_Reload[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Reload[i].pos.x + general[i].pos.x + sinf((g_Reload[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Reload[i].angle)) * g_Reload[i].length,
			g_Reload[i].pos.y + general[i].pos.y + cosf((g_Reload[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Reload[i].angle)) * g_Reload[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Reload[i].pos.x + general[i].pos.x + sinf((g_Reload[i].rot.z + general[i].rot.z) - (g_Reload[i].angle)) * g_Reload[i].length,
			g_Reload[i].pos.y + general[i].pos.y + cosf((g_Reload[i].rot.z + general[i].rot.z) - (g_Reload[i].angle)) * g_Reload[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Reload[i].pos.x + general[i].pos.x + sinf((g_Reload[i].rot.z + general[i].rot.z) + (g_Reload[i].angle)) * g_Reload[i].length,
			g_Reload[i].pos.y + general[i].pos.y + cosf((g_Reload[i].rot.z + general[i].rot.z) + (g_Reload[i].angle)) * g_Reload[i].length,
			0.0f
		};

		// 色の反映
		pVtx[0].col = g_Reload[i].col + general[i].col;
		pVtx[1].col = g_Reload[i].col + general[i].col;
		pVtx[2].col = g_Reload[i].col + general[i].col;
		pVtx[3].col = g_Reload[i].col + general[i].col;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffReload->Unlock();
}

//************************************************
// 通常描画処理
//************************************************
void DrawNormalReload(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffReload, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_RELOAD; i++)
	{
		if (!g_Reload[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		pDevice->SetTexture(0, g_pTextureReload);

		// テストの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}