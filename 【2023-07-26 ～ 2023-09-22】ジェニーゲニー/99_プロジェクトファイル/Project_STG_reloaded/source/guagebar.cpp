//************************************************
//
//ゲージバー表示処理[guagebar.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "guagebar.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_GuageBar = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_GuageBar = NULL;	//頂点バッファのポインタ

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_GuageBar()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GUAGEBAR,
		&g_pTexture_GuageBar);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_GuageBar,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_GuageBar;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_GuageBar->Lock(0, 0, (void**)&pVtx_GuageBar, 0);

	//頂点座標の初期設定
	pVtx_GuageBar[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_GuageBar[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_GuageBar[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_GuageBar[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_GuageBar[0].rhw = 1.0f;
	pVtx_GuageBar[1].rhw = 1.0f;
	pVtx_GuageBar[2].rhw = 1.0f;
	pVtx_GuageBar[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_GuageBar[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_GuageBar[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_GuageBar[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_GuageBar[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の初期設定
	pVtx_GuageBar[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_GuageBar[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_GuageBar[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_GuageBar[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_GuageBar->Unlock();

	//初回に一度ポリゴンを展開する
	SetPos_Vtx_GuageBar();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_GuageBar(void)
{
	//テクスチャの破棄
	if (g_pTexture_GuageBar != NULL)
	{
		g_pTexture_GuageBar->Release();
		g_pTexture_GuageBar = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_GuageBar != NULL)
	{
		g_pVtxBuff_GuageBar->Release();
		g_pVtxBuff_GuageBar = NULL;
	}
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_GuageBar(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_GuageBar, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_GuageBar);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//頂点を展開する関数
//************************************************
void SetPos_Vtx_GuageBar(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_GuageBar;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_GuageBar->Lock(0, 0, (void**)&pVtx_GuageBar, 0);

	pVtx_GuageBar[0].pos = D3DXVECTOR3(POS_X_LEFT_GUAGEBAR, POS_Y_UP_GUAGEBAR, 0.0f);
	pVtx_GuageBar[1].pos = D3DXVECTOR3(POS_X_RIGHT_GUAGEBAR, POS_Y_UP_GUAGEBAR, 0.0f);
	pVtx_GuageBar[2].pos = D3DXVECTOR3(POS_X_LEFT_GUAGEBAR, POS_Y_DOWN_GUAGEBAR, 0.0f);
	pVtx_GuageBar[3].pos = D3DXVECTOR3(POS_X_RIGHT_GUAGEBAR, POS_Y_DOWN_GUAGEBAR, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_GuageBar->Unlock();
}