//************************************************
//
//背景処理[bg.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "bg.h"
#include "timer.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_BG[AMOUNT_TEXTURE_BG] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_BG = NULL;	//頂点バッファのポインタ
BG g_aBG[AMOUNT_POLYGON_BG];	//背景用構造体

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_BG(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_DEMO_BG,
		&g_pTexture_BG[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_BG,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_BG;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_BG->Lock(0, 0, (void**)&pVtx_BG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_BG[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_BG[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_BG[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_BG[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_BG[0].rhw = 1.0f;
		pVtx_BG[1].rhw = 1.0f;
		pVtx_BG[2].rhw = 1.0f;
		pVtx_BG[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_BG[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_BG[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_BG[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_BG[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_BG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_BG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_BG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_BG[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_BG += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_BG->Unlock();

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		g_aBG[nCnt].texL = 0.0f;
		g_aBG[nCnt].texR = 1.0f;
		g_aBG[nCnt].moveSPD = 0.002f;
	}

	//初回に一度ポリゴンを展開する
	SetPos_Vtx_BG();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_BG(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_BG; nCnt++)
	{
		if (g_pTexture_BG[nCnt] != NULL)
		{
			g_pTexture_BG[nCnt]->Release();
			g_pTexture_BG[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_BG != NULL)
	{
		g_pVtxBuff_BG->Release();
		g_pVtxBuff_BG = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_BG(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_BG;

	//タイマー情報のポインタ
	bool* pInversion;
	bool* pReInversion;

	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_BG->Lock(0, 0, (void**)&pVtx_BG, 0);

	//テクスチャをいい感じの速さで流す
	g_aBG[0].texL += g_aBG[0].moveSPD;
	g_aBG[0].texR += g_aBG[0].moveSPD;

	if (*pInversion == true &&
		g_aBG[0].moveSPD >= -0.0025f &&
		*pReInversion == false)
	{
		g_aBG[0].moveSPD -= 0.00005f;
	}
	if (*pInversion == true &&
		g_aBG[0].moveSPD <= 0.0035f &&
		*pReInversion == true)
	{
		g_aBG[0].moveSPD += 0.000025f;
	}

	//反映
	pVtx_BG[0].tex = D3DXVECTOR2(g_aBG[0].texL, 0.0f);
	pVtx_BG[1].tex = D3DXVECTOR2(g_aBG[0].texR, 0.0f);
	pVtx_BG[2].tex = D3DXVECTOR2(g_aBG[0].texL, 1.0f);
	pVtx_BG[3].tex = D3DXVECTOR2(g_aBG[0].texR, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_BG->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_BG(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_BG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_BG; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_BG[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//頂点を展開する関数
//************************************************
void SetPos_Vtx_BG(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_BG;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_BG->Lock(0, 0, (void**)&pVtx_BG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		pVtx_BG[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_BG[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx_BG[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx_BG[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		pVtx_BG += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_BG->Unlock();
}