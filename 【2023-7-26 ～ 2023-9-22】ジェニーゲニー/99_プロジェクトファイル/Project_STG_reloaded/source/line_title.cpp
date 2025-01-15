//************************************************
//
//タイトルの線処理[line_title.cpp]
//Author：福田歩希
//
//************************************************
#include "line_titleh.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Line_title = NULL;	//頂点バッファのポインタ
LINE_TITLE g_aLine_title[AMOUNT_POLYGON_LINE_TITLE];	//カーソル用ポリゴンの情報を格納

//************************************************
//初期化処理関数
//************************************************
void Init_Line_title(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_LINE_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Line_title,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Line_title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Line_title->Lock(0, 0, (void**)&pVtx_Line_title, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LINE_TITLE; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Line_title[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Line_title[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Line_title[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Line_title[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Line_title[0].rhw = 1.0f;
		pVtx_Line_title[1].rhw = 1.0f;
		pVtx_Line_title[2].rhw = 1.0f;
		pVtx_Line_title[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Line_title[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Line_title[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Line_title[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Line_title[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Line_title[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Line_title[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Line_title[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Line_title[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Line_title += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Line_title->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LINE_TITLE; nCnt++)
	{
		g_aLine_title[nCnt].nStyle = 0;
		g_aLine_title[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine_title[nCnt].fSpanX = 0.0f;
		g_aLine_title[nCnt].fSpanY = 0.0f;
		g_aLine_title[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine_title[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine_title[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aLine_title[nCnt].fLength = 0.0f;
		g_aLine_title[nCnt].fAngle = 0.0f;
	}

	//初回のみ頂点を展開
	Setinfo_Line_title();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Line_title(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuff_Line_title != NULL)
	{
		g_pVtxBuff_Line_title->Release();
		g_pVtxBuff_Line_title = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Line_title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Line_title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Line_title->Lock(0, 0, (void**)&pVtx_Line_title, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LINE_TITLE; nCnt++)
	{
		//移動など反映
		pVtx_Line_title[0].pos.x = g_aLine_title[nCnt].pos.x + sinf(g_aLine_title[nCnt].rot.z - (D3DX_PI - g_aLine_title[nCnt].fAngle)) * g_aLine_title[nCnt].fLength;
		pVtx_Line_title[0].pos.y = g_aLine_title[nCnt].pos.y + cosf(g_aLine_title[nCnt].rot.z - (D3DX_PI - g_aLine_title[nCnt].fAngle)) * g_aLine_title[nCnt].fLength;
		pVtx_Line_title[1].pos.x = g_aLine_title[nCnt].pos.x + sinf(g_aLine_title[nCnt].rot.z + (D3DX_PI - g_aLine_title[nCnt].fAngle)) * g_aLine_title[nCnt].fLength;
		pVtx_Line_title[1].pos.y = g_aLine_title[nCnt].pos.y + cosf(g_aLine_title[nCnt].rot.z + (D3DX_PI - g_aLine_title[nCnt].fAngle)) * g_aLine_title[nCnt].fLength;
		pVtx_Line_title[2].pos.x = g_aLine_title[nCnt].pos.x + sinf(g_aLine_title[nCnt].rot.z - g_aLine_title[nCnt].fAngle) * g_aLine_title[nCnt].fLength;
		pVtx_Line_title[2].pos.y = g_aLine_title[nCnt].pos.y + cosf(g_aLine_title[nCnt].rot.z - g_aLine_title[nCnt].fAngle) * g_aLine_title[nCnt].fLength;
		pVtx_Line_title[3].pos.x = g_aLine_title[nCnt].pos.x + sinf(g_aLine_title[nCnt].rot.z + g_aLine_title[nCnt].fAngle) * g_aLine_title[nCnt].fLength;
		pVtx_Line_title[3].pos.y = g_aLine_title[nCnt].pos.y + cosf(g_aLine_title[nCnt].rot.z + g_aLine_title[nCnt].fAngle) * g_aLine_title[nCnt].fLength;

		pVtx_Line_title += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Line_title->Unlock();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Line_title(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Line_title, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LINE_TITLE; nCnt++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Line_title(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LINE_TITLE; nCnt++)
	{
		g_aLine_title[nCnt].nStyle = nCnt;
		g_aLine_title[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
		g_aLine_title[nCnt].fSpanX = 60.0f;
		g_aLine_title[nCnt].fSpanY = 60.0f;
		g_aLine_title[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine_title[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine_title[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aLine_title[nCnt].fLength = sqrtf((g_aLine_title[nCnt].fSpanX * g_aLine_title[nCnt].fSpanX) + (g_aLine_title[nCnt].fSpanY * g_aLine_title[nCnt].fSpanY));
		g_aLine_title[nCnt].fAngle = atan2f(g_aLine_title[nCnt].fSpanX * 2.0f, g_aLine_title[nCnt].fSpanX * 2.0f);
	}
}