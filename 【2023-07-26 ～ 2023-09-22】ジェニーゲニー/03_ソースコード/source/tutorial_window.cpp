//************************************************
//
//チュートリアル催促ウィンドウ処理[tutorial_window.cpp]
//Author：福田歩希
//
//************************************************
#include "tutorial_window.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Tutorial_Window[AMOUNT_TEXTURE_TUTORIAL_WINDOW] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Tutorial_Window = NULL;	//頂点バッファのポインタ
TUTORIAL_WINDOW g_aTutorial_Window[AMOUNT_POLYGON_TUTORIAL_WINDOW];	//カーソル用ポリゴンの情報を格納

//************************************************
//初期化処理関数
//************************************************
void Init_Tutorial_Window(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLACK_EX,
		&g_pTexture_Tutorial_Window[0]);

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TUTORIAL_WINDOW,
		&g_pTexture_Tutorial_Window[1]);

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TUTORIAL_TEXT,
		&g_pTexture_Tutorial_Window[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TUTORIAL_WINDOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Tutorial_Window,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Tutorial_Window;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Tutorial_Window->Lock(0, 0, (void**)&pVtx_Tutorial_Window, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_WINDOW; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Tutorial_Window[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Window[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Window[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Window[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Tutorial_Window[0].rhw = 1.0f;
		pVtx_Tutorial_Window[1].rhw = 1.0f;
		pVtx_Tutorial_Window[2].rhw = 1.0f;
		pVtx_Tutorial_Window[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Tutorial_Window[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Window[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Window[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Window[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Tutorial_Window[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Tutorial_Window[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Tutorial_Window[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Tutorial_Window[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Tutorial_Window += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Tutorial_Window->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_WINDOW; nCnt++)
	{
		g_aTutorial_Window[nCnt].nStyle = 0;
		g_aTutorial_Window[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Window[nCnt].fSpanX = 0.0f;
		g_aTutorial_Window[nCnt].fSpanY = 0.0f;
		g_aTutorial_Window[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Window[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Window[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aTutorial_Window[nCnt].fLength = 0.0f;
		g_aTutorial_Window[nCnt].fAngle = 0.0f;
		g_aTutorial_Window[nCnt].fSPD_X = 0.0f;
		g_aTutorial_Window[nCnt].colA = 0.0f;
	}

	//初回のみ頂点を展開
	Setinfo_Tutorial_Window();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Tutorial_Window(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_TUTORIAL_WINDOW; nCnt++)
	{
		if (g_pTexture_Tutorial_Window[nCnt] != NULL)
		{
			g_pTexture_Tutorial_Window[nCnt]->Release();
			g_pTexture_Tutorial_Window[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Tutorial_Window != NULL)
	{
		g_pVtxBuff_Tutorial_Window->Release();
		g_pVtxBuff_Tutorial_Window = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Tutorial_Window(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Tutorial_Window;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Tutorial_Window->Lock(0, 0, (void**)&pVtx_Tutorial_Window, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_WINDOW; nCnt++)
	{
		switch (g_aTutorial_Window[nCnt].nStyle)
		{
		case 0:

			g_aTutorial_Window[nCnt].fSpanX = 1980.0f;
			g_aTutorial_Window[nCnt].fSpanY = 1080.0f;

			break;

		case 1:

			if (g_aTutorial_Window[nCnt].colA < 0.7f)
			{
				g_aTutorial_Window[nCnt].colA *= 1.5f;
			}
			else
			{
				g_aTutorial_Window[nCnt].colA = 0.7f;
			}

			g_aTutorial_Window[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTutorial_Window[nCnt].colA);

			if (g_aTutorial_Window[nCnt].fSpanX < 800.0f)
			{
				g_aTutorial_Window[nCnt].fSPD_X *= 1.3f;
				g_aTutorial_Window[nCnt].fSpanX += g_aTutorial_Window[nCnt].fSPD_X;
			}
			else if (g_aTutorial_Window[nCnt].fSpanX > 800.0f && g_aTutorial_Window[nCnt].fSpanX < 1200.0f)
			{
				g_aTutorial_Window[nCnt].fSPD_X *= 0.8f;
				g_aTutorial_Window[nCnt].fSpanX += g_aTutorial_Window[nCnt].fSPD_X;
			}

			g_aTutorial_Window[nCnt].fSpanY = 800.0f;

			break;

		case 2:

			if (g_aTutorial_Window[nCnt].colA < 1.0f)
			{
				g_aTutorial_Window[nCnt].colA *= 1.095f;
			}
			else
			{
				g_aTutorial_Window[nCnt].colA = 1.0f;
			}

			g_aTutorial_Window[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTutorial_Window[nCnt].colA);

			if (g_aTutorial_Window[nCnt].fSpanX < 800.0f)
			{
				g_aTutorial_Window[nCnt].fSPD_X *= 1.3f;
				g_aTutorial_Window[nCnt].fSpanX += g_aTutorial_Window[nCnt].fSPD_X;
			}
			else if (g_aTutorial_Window[nCnt].fSpanX > 800.0f && g_aTutorial_Window[nCnt].fSpanX < 950.0f)
			{
				g_aTutorial_Window[nCnt].fSPD_X *= 0.8f;
				g_aTutorial_Window[nCnt].fSpanX += g_aTutorial_Window[nCnt].fSPD_X;
			}

			g_aTutorial_Window[nCnt].fSpanY = 100.0f;

			break;
		}

		//サイズ変更
		if (g_aTutorial_Window[nCnt].nStyle != 0)
		{
			g_aTutorial_Window[nCnt].fLength = sqrtf((g_aTutorial_Window[nCnt].fSpanX * g_aTutorial_Window[nCnt].fSpanX) + (g_aTutorial_Window[nCnt].fSpanY * g_aTutorial_Window[nCnt].fSpanY)) * 0.5f;
		}
		else
		{
			g_aTutorial_Window[nCnt].fLength = sqrtf((g_aTutorial_Window[nCnt].fSpanX * g_aTutorial_Window[nCnt].fSpanX) + (g_aTutorial_Window[nCnt].fSpanY * g_aTutorial_Window[nCnt].fSpanY));
		}

		g_aTutorial_Window[nCnt].fAngle = atan2f(g_aTutorial_Window[nCnt].fSpanX * 2.0f, g_aTutorial_Window[nCnt].fSpanY * 2.0f);

		//移動など反映
		pVtx_Tutorial_Window[0].pos.x = g_aTutorial_Window[nCnt].pos.x + sinf(g_aTutorial_Window[nCnt].rot.z - (D3DX_PI - g_aTutorial_Window[nCnt].fAngle)) * g_aTutorial_Window[nCnt].fLength;
		pVtx_Tutorial_Window[0].pos.y = g_aTutorial_Window[nCnt].pos.y + cosf(g_aTutorial_Window[nCnt].rot.z - (D3DX_PI - g_aTutorial_Window[nCnt].fAngle)) * g_aTutorial_Window[nCnt].fLength;
		pVtx_Tutorial_Window[1].pos.x = g_aTutorial_Window[nCnt].pos.x + sinf(g_aTutorial_Window[nCnt].rot.z + (D3DX_PI - g_aTutorial_Window[nCnt].fAngle)) * g_aTutorial_Window[nCnt].fLength;
		pVtx_Tutorial_Window[1].pos.y = g_aTutorial_Window[nCnt].pos.y + cosf(g_aTutorial_Window[nCnt].rot.z + (D3DX_PI - g_aTutorial_Window[nCnt].fAngle)) * g_aTutorial_Window[nCnt].fLength;
		pVtx_Tutorial_Window[2].pos.x = g_aTutorial_Window[nCnt].pos.x + sinf(g_aTutorial_Window[nCnt].rot.z - g_aTutorial_Window[nCnt].fAngle) * g_aTutorial_Window[nCnt].fLength;
		pVtx_Tutorial_Window[2].pos.y = g_aTutorial_Window[nCnt].pos.y + cosf(g_aTutorial_Window[nCnt].rot.z - g_aTutorial_Window[nCnt].fAngle) * g_aTutorial_Window[nCnt].fLength;
		pVtx_Tutorial_Window[3].pos.x = g_aTutorial_Window[nCnt].pos.x + sinf(g_aTutorial_Window[nCnt].rot.z + g_aTutorial_Window[nCnt].fAngle) * g_aTutorial_Window[nCnt].fLength;
		pVtx_Tutorial_Window[3].pos.y = g_aTutorial_Window[nCnt].pos.y + cosf(g_aTutorial_Window[nCnt].rot.z + g_aTutorial_Window[nCnt].fAngle) * g_aTutorial_Window[nCnt].fLength;

		pVtx_Tutorial_Window[0].col = g_aTutorial_Window[nCnt].col;
		pVtx_Tutorial_Window[1].col = g_aTutorial_Window[nCnt].col;
		pVtx_Tutorial_Window[2].col = g_aTutorial_Window[nCnt].col;
		pVtx_Tutorial_Window[3].col = g_aTutorial_Window[nCnt].col;

		pVtx_Tutorial_Window += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Tutorial_Window->Unlock();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Tutorial_Window(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Tutorial_Window, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_TUTORIAL_WINDOW; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Tutorial_Window[nCnt]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Tutorial_Window(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_WINDOW; nCnt++)
	{
		g_aTutorial_Window[nCnt].nStyle = nCnt;

		switch (g_aTutorial_Window[nCnt].nStyle)
		{
		case 0:

			g_aTutorial_Window[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);

			g_aTutorial_Window[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.85f);

			break;

		case 1:

			g_aTutorial_Window[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);

			g_aTutorial_Window[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTutorial_Window[nCnt].colA);

			break;

		case 2:

			g_aTutorial_Window[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f - 150.0f, 0.0f);

			g_aTutorial_Window[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTutorial_Window[nCnt].colA);

			break;
		}

		g_aTutorial_Window[nCnt].fSpanX = 0.0f;
		g_aTutorial_Window[nCnt].fSpanY = 0.0f;
		g_aTutorial_Window[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Window[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Window[nCnt].fLength = 0.0f;
		g_aTutorial_Window[nCnt].fAngle = 0.0f;
		g_aTutorial_Window[nCnt].fSPD_X = 1.0f;
		g_aTutorial_Window[nCnt].colA = 0.01f;
	}
}