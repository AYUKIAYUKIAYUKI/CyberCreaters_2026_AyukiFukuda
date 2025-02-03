//************************************************
//
//リース表示処理[wreath.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "wreath.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Wreath[AMOUNT_TEXTURE_WREATH] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Wreath = NULL;	//頂点バッファのポインタ

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Wreath()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WREATH,
		&g_pTexture_Wreath[0]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WOOD,
		&g_pTexture_Wreath[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_WREATH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Wreath,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Wreath;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Wreath->Lock(0, 0, (void**)&pVtx_Wreath, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_WREATH; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Wreath[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Wreath[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Wreath[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Wreath[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Wreath[0].rhw = 1.0f;
		pVtx_Wreath[1].rhw = 1.0f;
		pVtx_Wreath[2].rhw = 1.0f;
		pVtx_Wreath[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Wreath[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Wreath[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Wreath[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Wreath[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Wreath[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Wreath[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Wreath[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Wreath[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Wreath += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Wreath->Unlock();

	//初回に一度ポリゴンを展開する
	SetPos_Vtx_Wreath();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Wreath(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_WREATH; nCnt++)
	{
		if (g_pTexture_Wreath[nCnt] != NULL)
		{
			g_pTexture_Wreath[nCnt]->Release();
			g_pTexture_Wreath[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Wreath != NULL)
	{
		g_pVtxBuff_Wreath->Release();
		g_pVtxBuff_Wreath = NULL;
	}
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Wreath(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Wreath, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_WREATH; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Wreath[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//頂点を展開する関数
//************************************************
void SetPos_Vtx_Wreath(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Wreath;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Wreath->Lock(0, 0, (void**)&pVtx_Wreath, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_WREATH; nCnt++)
	{
		pVtx_Wreath[0].pos = D3DXVECTOR3(POS_X_LEFT_WREATH + (POS_WOOD * nCnt), POS_Y_UP_WREATH + (POS_WOOD * nCnt), 0.0f);
		pVtx_Wreath[1].pos = D3DXVECTOR3(POS_X_RIGHT_WREATH - (POS_WOOD * nCnt), POS_Y_UP_WREATH + (POS_WOOD * nCnt), 0.0f);
		pVtx_Wreath[2].pos = D3DXVECTOR3(POS_X_LEFT_WREATH + (POS_WOOD * nCnt), POS_Y_DOWN_WREATH - (POS_WOOD * nCnt), 0.0f);
		pVtx_Wreath[3].pos = D3DXVECTOR3(POS_X_RIGHT_WREATH - (POS_WOOD * nCnt), POS_Y_DOWN_WREATH - (POS_WOOD * nCnt), 0.0f);

		pVtx_Wreath += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Wreath->Unlock();
}