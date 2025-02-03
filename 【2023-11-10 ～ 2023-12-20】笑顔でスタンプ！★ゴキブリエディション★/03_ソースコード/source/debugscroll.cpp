//************************************************
//
//デバッグ表示用スクロールバー[debugscroll.cpp]
//Author：福田歩希
//
//************************************************
#include "debugscroll.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_DebugScroll = NULL;	//頂点バッファのポインタ
DebugScroll g_aDebugScroll[AMOUNT_DEBUGSCROLL];	//スクロールバー情報

//************************************************
//初期
//************************************************
void InitDebugScroll(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < AMOUNT_DEBUGSCROLL; i++)
	{
		g_aDebugScroll[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDebugScroll[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_DEBUGSCROLL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_DebugScroll,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_DebugScroll->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_DEBUGSCROLL; i++)
	{
		//頂点座標の初期設定
		switch (i)
		{
		case 0:
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, (float)SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(25.0f, (float)SCREEN_HEIGHT, 0.0f);
			break;
		case 1:
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(25.0f, 50.0f, 0.0f);
			break;
		}

		//視錐台の拡大率(?)の初期設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの初期設定
		switch (i)
		{
		case 0:
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			break;
		case 1:
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		//テクスチャ座標の初期設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_DebugScroll->Unlock();
}

//************************************************
//破棄
//************************************************
void UninitDebugScroll(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuff_DebugScroll != NULL)
	{
		g_pVtxBuff_DebugScroll->Release();
		g_pVtxBuff_DebugScroll = NULL;
	}
}

//************************************************
//更新
//************************************************
void UpdateDebugScroll(void)
{
	LONG* pRectUP = GetInfoRectUP();

	g_aDebugScroll[1].pos.y = -(float)*pRectUP * 1.03f;

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_DebugScroll->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX;

	pVtx[0].pos = D3DXVECTOR3(0.0f, g_aDebugScroll[1].pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(25.0f, g_aDebugScroll[1].pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, g_aDebugScroll[1].pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(25.0f, g_aDebugScroll[1].pos.y + 50.0f, 0.0f);
	
	//頂点バッファをアンロックする
	g_pVtxBuff_DebugScroll->Unlock();
}

//************************************************
//描画
//************************************************
void DrawDebugScroll(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_DebugScroll, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_DEBUGSCROLL; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}