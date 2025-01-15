//************************************************
//
//ポーズ画面ウィンドウ処理[pause_window.cpp]
//Author：福田歩希
//
//************************************************
#include "pause_window.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Pause_Window[AMOUNT_TEXTURE_PAUSE_WINDOW] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Pause_Window = NULL;	//頂点バッファのポインタ
PAUSE_WINDOW g_aPause_Window[AMOUNT_POLYGON_PAUSE_WINDOW];	//カーソル用ポリゴンの情報を格納

//************************************************
//初期化処理関数
//************************************************
void Init_Pause_Window(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PAUSE_WINDOW,
		&g_pTexture_Pause_Window[0]);

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PAUSE_TEXT,
		&g_pTexture_Pause_Window[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_PAUSE_WINDOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Pause_Window,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Pause_Window;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Pause_Window->Lock(0, 0, (void**)&pVtx_Pause_Window, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_WINDOW; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Pause_Window[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Pause_Window[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Pause_Window[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Pause_Window[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Pause_Window[0].rhw = 1.0f;
		pVtx_Pause_Window[1].rhw = 1.0f;
		pVtx_Pause_Window[2].rhw = 1.0f;
		pVtx_Pause_Window[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Pause_Window[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Pause_Window[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Pause_Window[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Pause_Window[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Pause_Window[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Pause_Window[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Pause_Window[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Pause_Window[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Pause_Window += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Pause_Window->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_WINDOW; nCnt++)
	{
		g_aPause_Window[nCnt].nStyle = 0;
		g_aPause_Window[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Window[nCnt].fSpanX = 0.0f;
		g_aPause_Window[nCnt].fSpanY = 0.0f;
		g_aPause_Window[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Window[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Window[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aPause_Window[nCnt].fLength = 0.0f;
		g_aPause_Window[nCnt].fAngle = 0.0f;
		g_aPause_Window[nCnt].fSPD_X = 0.0f;
		g_aPause_Window[nCnt].colA = 0.0f;
	}

	//初回のみ頂点を展開
	Setinfo_Pause_Window();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Pause_Window(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_PAUSE_WINDOW; nCnt++)
	{
		if (g_pTexture_Pause_Window[nCnt] != NULL)
		{
			g_pTexture_Pause_Window[nCnt]->Release();
			g_pTexture_Pause_Window[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Pause_Window != NULL)
	{
		g_pVtxBuff_Pause_Window->Release();
		g_pVtxBuff_Pause_Window = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Pause_Window(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Pause_Window;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Pause_Window->Lock(0, 0, (void**)&pVtx_Pause_Window, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_WINDOW; nCnt++)
	{
		switch (g_aPause_Window[nCnt].nStyle)
		{
		case 0:

			if (g_aPause_Window[nCnt].colA < 0.9f)
			{
				g_aPause_Window[nCnt].colA *= 1.5f;
			}
			else
			{
				g_aPause_Window[nCnt].colA = 0.9f;
			}

			g_aPause_Window[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aPause_Window[nCnt].colA);

			if (g_aPause_Window[nCnt].fSpanX < 530.0f)
			{
				g_aPause_Window[nCnt].fSPD_X *= 1.5f;
				g_aPause_Window[nCnt].fSpanX += g_aPause_Window[nCnt].fSPD_X;
			}
			else if (g_aPause_Window[nCnt].fSpanX > 530.0f && g_aPause_Window[nCnt].fSpanX < 630.0f)
			{
				g_aPause_Window[nCnt].fSPD_X *= 0.5f;
				g_aPause_Window[nCnt].fSpanX += g_aPause_Window[nCnt].fSPD_X;
			}

			g_aPause_Window[nCnt].fSpanY = 400.0f;

			break;

		case 1:

			if (g_aPause_Window[nCnt].colA < 1.0f)
			{
				g_aPause_Window[nCnt].colA *= 1.2f;
			}
			else
			{
				g_aPause_Window[nCnt].colA = 1.0f;
			}

			g_aPause_Window[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aPause_Window[nCnt].colA);
			
			g_aPause_Window[nCnt].fSpanX = 130.0f;
			g_aPause_Window[nCnt].fSpanY = 50.0f;

			break;
		}

		//サイズ変更
		g_aPause_Window[nCnt].fLength = sqrtf((g_aPause_Window[nCnt].fSpanX * g_aPause_Window[nCnt].fSpanX) + (g_aPause_Window[nCnt].fSpanY * g_aPause_Window[nCnt].fSpanY));

		g_aPause_Window[nCnt].fAngle = atan2f(g_aPause_Window[nCnt].fSpanX * 2.0f, g_aPause_Window[nCnt].fSpanY * 2.0f);

		//移動など反映
		pVtx_Pause_Window[0].pos.x = g_aPause_Window[nCnt].pos.x + sinf(g_aPause_Window[nCnt].rot.z - (D3DX_PI - g_aPause_Window[nCnt].fAngle)) * g_aPause_Window[nCnt].fLength;
		pVtx_Pause_Window[0].pos.y = g_aPause_Window[nCnt].pos.y + cosf(g_aPause_Window[nCnt].rot.z - (D3DX_PI - g_aPause_Window[nCnt].fAngle)) * g_aPause_Window[nCnt].fLength;
		pVtx_Pause_Window[1].pos.x = g_aPause_Window[nCnt].pos.x + sinf(g_aPause_Window[nCnt].rot.z + (D3DX_PI - g_aPause_Window[nCnt].fAngle)) * g_aPause_Window[nCnt].fLength;
		pVtx_Pause_Window[1].pos.y = g_aPause_Window[nCnt].pos.y + cosf(g_aPause_Window[nCnt].rot.z + (D3DX_PI - g_aPause_Window[nCnt].fAngle)) * g_aPause_Window[nCnt].fLength;
		pVtx_Pause_Window[2].pos.x = g_aPause_Window[nCnt].pos.x + sinf(g_aPause_Window[nCnt].rot.z - g_aPause_Window[nCnt].fAngle) * g_aPause_Window[nCnt].fLength;
		pVtx_Pause_Window[2].pos.y = g_aPause_Window[nCnt].pos.y + cosf(g_aPause_Window[nCnt].rot.z - g_aPause_Window[nCnt].fAngle) * g_aPause_Window[nCnt].fLength;
		pVtx_Pause_Window[3].pos.x = g_aPause_Window[nCnt].pos.x + sinf(g_aPause_Window[nCnt].rot.z + g_aPause_Window[nCnt].fAngle) * g_aPause_Window[nCnt].fLength;
		pVtx_Pause_Window[3].pos.y = g_aPause_Window[nCnt].pos.y + cosf(g_aPause_Window[nCnt].rot.z + g_aPause_Window[nCnt].fAngle) * g_aPause_Window[nCnt].fLength;

		pVtx_Pause_Window[0].col = g_aPause_Window[nCnt].col;
		pVtx_Pause_Window[1].col = g_aPause_Window[nCnt].col;
		pVtx_Pause_Window[2].col = g_aPause_Window[nCnt].col;
		pVtx_Pause_Window[3].col = g_aPause_Window[nCnt].col;

		pVtx_Pause_Window += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Pause_Window->Unlock();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Pause_Window(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Pause_Window, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_PAUSE_WINDOW; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Pause_Window[nCnt]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Pause_Window(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_WINDOW; nCnt++)
	{
		g_aPause_Window[nCnt].nStyle = nCnt;

		switch (g_aPause_Window[nCnt].nStyle)
		{
		case 0:

			g_aPause_Window[nCnt].pos = D3DXVECTOR3(990.0f, 530.0f, 0.0f);

			g_aPause_Window[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aPause_Window[nCnt].colA);

			break;

		case 1:

			g_aPause_Window[nCnt].pos = D3DXVECTOR3(990.0f, 250.0f, 0.0f);

			g_aPause_Window[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aPause_Window[nCnt].colA);

			break;
		}

		g_aPause_Window[nCnt].fSpanX = 0.0f;
		g_aPause_Window[nCnt].fSpanY = 0.0f;
		g_aPause_Window[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Window[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Window[nCnt].fLength = 0.0f;
		g_aPause_Window[nCnt].fAngle = 0.0f;
		g_aPause_Window[nCnt].fSPD_X = 1.0f;
		g_aPause_Window[nCnt].colA = 0.01f;
	}
}