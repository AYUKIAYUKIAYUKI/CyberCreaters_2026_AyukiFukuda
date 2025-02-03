//************************************************
//
//リザルトデザイン[resultdesign.cpp]
//Author：福田歩希
//
//************************************************
#include "resultdesign.h"

#include "fade.h"
#include "input.h"

typedef enum
{
	TexLogo = 0,
	TexMax
}TexType;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResultDesign[TexMax] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultDesign = NULL;	//頂点バッファのポインタ
ResultDesign g_aResultDesign[TexMax];	//情報

//************************************************
//リザルトデザイン初期
//************************************************
void InitResultDesign(void)
{
	//構造体の情報の初期化群
	for (int i = 0; i < TexMax; i++)
	{
		g_aResultDesign[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResultDesign[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResultDesign[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResultDesign[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aResultDesign[i].sizeX = 0.0f;
		g_aResultDesign[i].sizeY = 0.0f;
		g_aResultDesign[i].F = 1.0f;	//汎用
	}

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	const char* pFileName[TexMax] =
	{
		"data\\texture\\roachrank.png",
	};

	for (int i = 0; i < TexMax; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureResultDesign[i]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * TexMax,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultDesign,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffResultDesign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++)
	{
		//頂点座標の初期設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffResultDesign->Unlock();

	//情報を付与
	SetInfoResultDesign();

	//展開
	SetSizeResultDesign();
}

//************************************************
//リザルトデザイン終了処理関数
//************************************************
void UninitResultDesign(void)
{
	//テクスチャの破棄
	for (int i = 0; i < TexMax; i++)
	{
		if (g_pTextureResultDesign[i] != NULL)
		{
			g_pTextureResultDesign[i]->Release();
			g_pTextureResultDesign[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResultDesign != NULL)
	{
		g_pVtxBuffResultDesign->Release();
		g_pVtxBuffResultDesign = NULL;
	}
}

//************************************************
//リザルトデザイン更新
//************************************************
void UpdateResultDesign(void)
{
	//展開
	SetSizeResultDesign();
}

//************************************************
//リザルトデザイン展開
//************************************************
void SetSizeResultDesign(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffResultDesign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		//頂点座標の初期設定
		pVtx[0].pos =
		{
			g_aResultDesign[i].pos.x - g_aResultDesign[i].sizeX,
			g_aResultDesign[i].pos.y - g_aResultDesign[i].sizeY,
			0.0f
		};

		pVtx[1].pos =
		{
			g_aResultDesign[i].pos.x + g_aResultDesign[i].sizeX,
			g_aResultDesign[i].pos.y - g_aResultDesign[i].sizeY,
			0.0f
		};

		pVtx[2].pos =
		{
			g_aResultDesign[i].pos.x - g_aResultDesign[i].sizeX,
			g_aResultDesign[i].pos.y + g_aResultDesign[i].sizeY,
			0.0f
		};

		pVtx[3].pos =
		{
			g_aResultDesign[i].pos.x + g_aResultDesign[i].sizeX,
			g_aResultDesign[i].pos.y + g_aResultDesign[i].sizeY,
			0.0f
		};
	}

	//頂点バッファをアンロックする
	g_pVtxBuffResultDesign->Unlock();
}

//************************************************
//リザルトデザイン描画
//************************************************
void DrawResultDesign(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultDesign, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TexMax; i++)
	{
		pDevice->SetTexture(0, g_pTextureResultDesign[i]);

		//リザルトデザインの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//構造体の情報を設定する関数
//************************************************
void SetInfoResultDesign(void)
{
	for (int i = 0; i < TexMax; i++)
	{
		if (i == TexLogo)
		{
			g_aResultDesign[i].pos = D3DXVECTOR3((float)SCREEN_HALFWIDTH, (float)SCREEN_HALFHEIGHT, 0.0f);
			g_aResultDesign[i].sizeX = (float)SCREEN_HALFWIDTH;
			g_aResultDesign[i].sizeY = (float)SCREEN_HALFHEIGHT;
		}
		g_aResultDesign[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResultDesign[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResultDesign[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aResultDesign[i].F = 1.0f;	//汎用
	}
}