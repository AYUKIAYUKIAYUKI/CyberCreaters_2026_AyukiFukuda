//************************************************
//
//メニューのテキスト表示処理[text_mode.cpp]
//Author：福田歩希
//
//************************************************
#include "text_mode.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Text_Mode[AMOUNT_TEXTURE_TEXT_MODE] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Text_Mode = NULL;	//頂点バッファのポインタ
TEXT_MODE g_aText_Mode[AMOUNT_POLYGON_TEXT_MODE];	//カーソル用ポリゴンの情報を格納

//************************************************
//初期化処理関数
//************************************************
void Init_Text_Mode(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WINDOW_MODE,
		&g_pTexture_Text_Mode[0]);

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHOOSE_MODE,
		&g_pTexture_Text_Mode[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TEXT_MODE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Text_Mode,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Text_Mode;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Text_Mode->Lock(0, 0, (void**)&pVtx_Text_Mode, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TEXT_MODE; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Text_Mode[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Mode[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Mode[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Mode[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Text_Mode[0].rhw = 1.0f;
		pVtx_Text_Mode[1].rhw = 1.0f;
		pVtx_Text_Mode[2].rhw = 1.0f;
		pVtx_Text_Mode[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Text_Mode[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Text_Mode[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Text_Mode[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Text_Mode[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Text_Mode[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Text_Mode[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Text_Mode[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Text_Mode[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Text_Mode += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Text_Mode->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TEXT_MODE; nCnt++)
	{
		g_aText_Mode[nCnt].nStyle = 0;
		g_aText_Mode[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Mode[nCnt].fSpanX = 0.0f;
		g_aText_Mode[nCnt].fSpanY = 0.0f;
		g_aText_Mode[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Mode[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Mode[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aText_Mode[nCnt].fLength = 0.0f;
		g_aText_Mode[nCnt].fAngle = 0.0f;
		g_aText_Mode[nCnt].fSPD_X = 0.0f;
	}

	//初回のみ頂点を展開
	Setinfo_Text_Mode();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Text_Mode(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_TEXT_MODE; nCnt++)
	{
		if (g_pTexture_Text_Mode[nCnt] != NULL)
		{
			g_pTexture_Text_Mode[nCnt]->Release();
			g_pTexture_Text_Mode[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Text_Mode != NULL)
	{
		g_pVtxBuff_Text_Mode->Release();
		g_pVtxBuff_Text_Mode = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Text_Mode(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Text_Mode;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Text_Mode->Lock(0, 0, (void**)&pVtx_Text_Mode, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TEXT_MODE; nCnt++)
	{
		switch (g_aText_Mode[nCnt].nStyle)
		{
		case 0:

			if (g_aText_Mode[nCnt].fSpanX < 500.0f)
			{
				g_aText_Mode[nCnt].fSPD_X *= 1.15f;
				g_aText_Mode[nCnt].fSpanX += g_aText_Mode[nCnt].fSPD_X;
			}
			else if (g_aText_Mode[nCnt].fSpanX > 500.0f && g_aText_Mode[nCnt].fSpanX < 850.0f)
			{
				g_aText_Mode[nCnt].fSPD_X *= 0.8f;
				g_aText_Mode[nCnt].fSpanX += g_aText_Mode[nCnt].fSPD_X;
			}

			g_aText_Mode[nCnt].fSpanY = 250.0f;

			break;

		case 1:

			if (g_aText_Mode[0].fSpanX > 700.0f)
			{
				if (g_aText_Mode[nCnt].fSpanX < 400.0f)
				{
					g_aText_Mode[nCnt].fSPD_X *= 1.15f;
					g_aText_Mode[nCnt].fSpanX += g_aText_Mode[nCnt].fSPD_X;
				}
				else if (g_aText_Mode[nCnt].fSpanX > 400.0f && g_aText_Mode[nCnt].fSpanX < 700.0f)
				{
					g_aText_Mode[nCnt].fSPD_X *= 0.8f;
					g_aText_Mode[nCnt].fSpanX += g_aText_Mode[nCnt].fSPD_X;
				}

			}

			g_aText_Mode[nCnt].fSpanY = 100.0f;

			break;
		}

		//サイズ変更
		g_aText_Mode[nCnt].fLength = sqrtf((g_aText_Mode[nCnt].fSpanX * g_aText_Mode[nCnt].fSpanX) + (g_aText_Mode[nCnt].fSpanY * g_aText_Mode[nCnt].fSpanY)) * 0.5f;
		g_aText_Mode[nCnt].fAngle = atan2f(g_aText_Mode[nCnt].fSpanX * 2.0f, g_aText_Mode[nCnt].fSpanY * 2.0f);

		//移動を反映
		pVtx_Text_Mode[0].pos.x = g_aText_Mode[nCnt].pos.x + sinf(g_aText_Mode[nCnt].rot.z - (D3DX_PI - g_aText_Mode[nCnt].fAngle)) * g_aText_Mode[nCnt].fLength;
		pVtx_Text_Mode[0].pos.y = g_aText_Mode[nCnt].pos.y + cosf(g_aText_Mode[nCnt].rot.z - (D3DX_PI - g_aText_Mode[nCnt].fAngle)) * g_aText_Mode[nCnt].fLength;
		pVtx_Text_Mode[1].pos.x = g_aText_Mode[nCnt].pos.x + sinf(g_aText_Mode[nCnt].rot.z + (D3DX_PI - g_aText_Mode[nCnt].fAngle)) * g_aText_Mode[nCnt].fLength;
		pVtx_Text_Mode[1].pos.y = g_aText_Mode[nCnt].pos.y + cosf(g_aText_Mode[nCnt].rot.z + (D3DX_PI - g_aText_Mode[nCnt].fAngle)) * g_aText_Mode[nCnt].fLength;
		pVtx_Text_Mode[2].pos.x = g_aText_Mode[nCnt].pos.x + sinf(g_aText_Mode[nCnt].rot.z - g_aText_Mode[nCnt].fAngle) * g_aText_Mode[nCnt].fLength;
		pVtx_Text_Mode[2].pos.y = g_aText_Mode[nCnt].pos.y + cosf(g_aText_Mode[nCnt].rot.z - g_aText_Mode[nCnt].fAngle) * g_aText_Mode[nCnt].fLength;
		pVtx_Text_Mode[3].pos.x = g_aText_Mode[nCnt].pos.x + sinf(g_aText_Mode[nCnt].rot.z + g_aText_Mode[nCnt].fAngle) * g_aText_Mode[nCnt].fLength;
		pVtx_Text_Mode[3].pos.y = g_aText_Mode[nCnt].pos.y + cosf(g_aText_Mode[nCnt].rot.z + g_aText_Mode[nCnt].fAngle) * g_aText_Mode[nCnt].fLength;

		pVtx_Text_Mode[0].col = g_aText_Mode[nCnt].col;
		pVtx_Text_Mode[1].col = g_aText_Mode[nCnt].col;
		pVtx_Text_Mode[2].col = g_aText_Mode[nCnt].col;
		pVtx_Text_Mode[3].col = g_aText_Mode[nCnt].col;

		pVtx_Text_Mode += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Text_Mode->Unlock();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Text_Mode(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Text_Mode, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TEXT_MODE; nCnt++)
	{
		switch (g_aText_Mode[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Text_Mode[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_Text_Mode[1]);

			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Text_Mode(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TEXT_MODE; nCnt++)
	{
		g_aText_Mode[nCnt].nStyle = nCnt;
		g_aText_Mode[nCnt].pos = D3DXVECTOR3(990.0f, 200.0f + (20 * nCnt), 0.0f);
		g_aText_Mode[nCnt].fSpanX = 0.0f;
		g_aText_Mode[nCnt].fSpanY = 0.0f;
		g_aText_Mode[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Mode[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		switch (g_aText_Mode[nCnt].nStyle)
		{
		case 0:

			g_aText_Mode[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aText_Mode[nCnt].fSPD_X = 1.0f;

			break;

		case 1:

			g_aText_Mode[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aText_Mode[nCnt].fSPD_X = 1.0f;

			break;
		}

		g_aText_Mode[nCnt].fLength = 0.0f;
		g_aText_Mode[nCnt].fAngle = 0.0f;
	}

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Text_Mode;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Text_Mode->Lock(0, 0, (void**)&pVtx_Text_Mode, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TEXT_MODE; nCnt++)
	{
		//移動を反映
		pVtx_Text_Mode[0].pos.x = g_aText_Mode[0].pos.x + sinf(g_aText_Mode[0].rot.z - (D3DX_PI - g_aText_Mode[0].fAngle)) * g_aText_Mode[0].fLength;
		pVtx_Text_Mode[0].pos.y = g_aText_Mode[0].pos.y + cosf(g_aText_Mode[0].rot.z - (D3DX_PI - g_aText_Mode[0].fAngle)) * g_aText_Mode[0].fLength;
		pVtx_Text_Mode[1].pos.x = g_aText_Mode[0].pos.x + sinf(g_aText_Mode[0].rot.z + (D3DX_PI - g_aText_Mode[0].fAngle)) * g_aText_Mode[0].fLength;
		pVtx_Text_Mode[1].pos.y = g_aText_Mode[0].pos.y + cosf(g_aText_Mode[0].rot.z + (D3DX_PI - g_aText_Mode[0].fAngle)) * g_aText_Mode[0].fLength;
		pVtx_Text_Mode[2].pos.x = g_aText_Mode[0].pos.x + sinf(g_aText_Mode[0].rot.z - g_aText_Mode[0].fAngle) * g_aText_Mode[0].fLength;
		pVtx_Text_Mode[2].pos.y = g_aText_Mode[0].pos.y + cosf(g_aText_Mode[0].rot.z - g_aText_Mode[0].fAngle) * g_aText_Mode[0].fLength;
		pVtx_Text_Mode[3].pos.x = g_aText_Mode[0].pos.x + sinf(g_aText_Mode[0].rot.z + g_aText_Mode[0].fAngle) * g_aText_Mode[0].fLength;
		pVtx_Text_Mode[3].pos.y = g_aText_Mode[0].pos.y + cosf(g_aText_Mode[0].rot.z + g_aText_Mode[0].fAngle) * g_aText_Mode[0].fLength;

		pVtx_Text_Mode[0].col = g_aText_Mode[0].col;
		pVtx_Text_Mode[1].col = g_aText_Mode[0].col;
		pVtx_Text_Mode[2].col = g_aText_Mode[0].col;
		pVtx_Text_Mode[3].col = g_aText_Mode[0].col;

		pVtx_Text_Mode += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Text_Mode->Unlock();
}