//************************************************
//
// テスト[TEST.cpp]
// Author：福田歩希
//
//************************************************

/*/ インクルードファイル /*/
#include "TEST.h"
// 中枢
#include "input.h"
#include "sound.h"
// デバッグ時
#ifdef _DEBUG
#include "debugproc.h"
#endif

/*/ マクロ定義 /*/
#define AMOUNT_TEST 4	// テスト表示の数
#define SIZE_VERIFY	1

// テスト用テクスチャ
typedef enum
{
	Tex00 = 0,
	TexMax
}TexType;

/*/ グローバル変数 /*/
LPDIRECT3DTEXTURE9 g_pTextureTEST[TexMax] = {};	// テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTEST = NULL;	// 頂点バッファのポインタ
TEST g_TEST[AMOUNT_TEST];						// テスト構造体

//************************************************
// テスト初期
//************************************************
void InitTEST(int joined)
{
	for (int i = 0; i < AMOUNT_TEST; i++)
	{ // 構造体の情報の初期化
		g_TEST[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TEST[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TEST[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TEST[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_TEST[i].size = { 0.0f,0.0f };
		g_TEST[i].angle = 0.0f;
		g_TEST[i].length = 0.0f;
		g_TEST[i].F = 1.0f;	// 汎用
	}

	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスへの取得
	pDevice = GetDevice();

	// テクスチャ画像の読込み用
	const char* pFileName[TexMax] =
	{
		"data\\TEXTURE\\test.png",
	};

	for (int i = 0; i < TexMax; i++)
	{ // テクスチャの生成
		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureTEST[i]);
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_TEST,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTEST,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffTEST->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_TEST; i++)
	{
		// 頂点座標の初期設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 視錐台の拡大率(?)の初期設定
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTEST->Unlock();

	// テスト情報を付与
	SetInfoTEST(joined);
}

//************************************************
// 構造体の情報を設定する関数
//************************************************
void SetInfoTEST(int joined)
{
	int adjust = 0;	// 人数調整用

	for (int i = 0; i < AMOUNT_TEST; i++)
	{ // 構造体の情報の初期化
		g_TEST[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TEST[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TEST[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TEST[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_TEST[i].size = { 0.0f,0.0f };
		g_TEST[i].angle = 0.0f;
		g_TEST[i].length = 0.0f;
		g_TEST[i].F = 1.0f;	// 汎用
	}

	if (joined >= 3)
	{
		adjust++;	//<! 参加人数が3人以上で調整用にカウントします。
	}	

	for (int i = 0, j = 0; i < joined; i++)
	{ //テスト表示に情報を付与

		if (i == 2) j++;	//!< 2ループ時点で必ず1カウントします。

		if (joined == 1)
		{ // 参加人数が1人の時のみ特別に位置、サイズを固定
			g_TEST[i].pos =
			{
				SCREEN_HALFWIDTH,
				100.0f,
				0.0f,
			};

			g_TEST[i].size = { 160.0f, 100.0f };
		}
		else
		{ // 参加人数が複数いる場合、自動的に位置、サイズを設定
			g_TEST[i].pos =
			{
				(SCREEN_HALFWIDTH * 0.5f) + (i * SCREEN_HALFWIDTH) - (j * SCREEN_WIDTH),
				TEST_POS_Y + (j * SCREEN_HALFHEIGHT) - (adjust * 10.0f),
				0.0f,
			};

			g_TEST[i].size = { 130.0f - (adjust * 30.0f), 80.0f - (adjust * 15.0f) };
		}

		g_TEST[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

//************************************************
// テスト終了処理関数
//************************************************
void UninitTEST(void)
{
	for (int i = 0; i < TexMax; i++)
	{ // テクスチャの破棄
		if (g_pTextureTEST[i] != NULL)
		{
			g_pTextureTEST[i]->Release();
			g_pTextureTEST[i] = NULL;
		}
	}

	if (g_pVtxBuffTEST != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffTEST->Release();
		g_pVtxBuffTEST = NULL;
	}
}

//************************************************
// テスト更新
//************************************************
void UpdateTEST(int joined)
{
	/*---【情報を再付与】---*/
	SetInfoTEST(joined);

	// 展開
	SetSizeTEST();

	// 色変更
	SetColTEST();
}

//************************************************
// テスト展開
//************************************************
void SetSizeTEST(void)
{
	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffTEST->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_TEST; i++, pVtx += AMOUNT_VTX)
	{ // 頂点座標の設定
#if SIZE_VERIFY
		pVtx[0].pos =
		{
			g_TEST[i].pos.x - g_TEST[i].size.x,
			g_TEST[i].pos.y - g_TEST[i].size.y,
			0.0f
		};

		pVtx[1].pos =
		{
			g_TEST[i].pos.x + g_TEST[i].size.x,
			g_TEST[i].pos.y - g_TEST[i].size.y,
			0.0f
		};

		pVtx[2].pos =
		{
			g_TEST[i].pos.x - g_TEST[i].size.x,
			g_TEST[i].pos.y + g_TEST[i].size.y,
			0.0f
		};

		pVtx[3].pos =
		{
			g_TEST[i].pos.x + g_TEST[i].size.x,
			g_TEST[i].pos.y + g_TEST[i].size.y,
			0.0f
		};
#else
		PrintDebugProc("length x : %f\n", g_TEST[0].length);
		PrintDebugProc("length y : %f\n", g_TEST[0].length);

		pVtx[0].pos =
		{
			g_TEST[i].pos.x + sinf(g_TEST[i].rot.z - (D3DX_PI - g_TEST[i].angle)) * g_TEST[i].length,
			g_TEST[i].pos.y + cosf(g_TEST[i].rot.z - (D3DX_PI - g_TEST[i].angle)) * g_TEST[i].length,
			0.0f
		};

		PrintDebugProc("0x : %f\n", pVtx[0].pos.x);
		PrintDebugProc("0y : %f\n", pVtx[0].pos.y);

		pVtx[1].pos =
		{
			g_TEST[i].pos.x + sinf(g_TEST[i].rot.z + (D3DX_PI - g_TEST[i].angle)) * g_TEST[i].length,
			g_TEST[i].pos.y + cosf(g_TEST[i].rot.z + (D3DX_PI - g_TEST[i].angle)) * g_TEST[i].length,
			0.0f
		};

		PrintDebugProc("1x : %f\n", pVtx[1].pos.x);
		PrintDebugProc("1y : %f\n", pVtx[1].pos.y);

		pVtx[2].pos =
		{
			g_TEST[i].pos.x + sinf(g_TEST[i].rot.z - g_TEST[i].angle) * g_TEST[i].length,
			g_TEST[i].pos.y + cosf(g_TEST[i].rot.z - g_TEST[i].angle) * g_TEST[i].length,
			0.0f
		};

		PrintDebugProc("2x : %f\n", pVtx[2].pos.x);
		PrintDebugProc("2y : %f\n", pVtx[2].pos.y);

		pVtx[3].pos =
		{
			g_TEST[i].pos.x + sinf(g_TEST[i].rot.z + g_TEST[i].angle) * g_TEST[i].length,
			g_TEST[i].pos.y + cosf(g_TEST[i].rot.z + g_TEST[i].angle) * g_TEST[i].length,
			0.0f
		};

		PrintDebugProc("3x : %f\n", pVtx[3].pos.x);
		PrintDebugProc("3y : %f\n", pVtx[3].pos.y);
#endif
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTEST->Unlock();
}

//************************************************
// テスト色変更
//************************************************
void SetColTEST(void)
{
	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffTEST->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_TEST; i++, pVtx += AMOUNT_VTX)
	{
		pVtx[0].col = g_TEST[i].col;
		pVtx[1].col = g_TEST[i].col;
		pVtx[2].col = g_TEST[i].col;
		pVtx[3].col = g_TEST[i].col;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTEST->Unlock();
}

//************************************************
// テスト描画
//************************************************
void DrawTEST(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTEST, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_TEST; i++)
	{
		pDevice->SetTexture(0, g_pTextureTEST[Tex00]);

		// テストの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}