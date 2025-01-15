//************************************************
//
//メニューのモード選択処理[select_mode.cpp]
//Author：福田歩希
//
//************************************************
#include "cursorh.h"
#include "select_mode.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Select_Mode[AMOUNT_TEXTURE_SELECT_MODE] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Select_Mode = NULL;	//頂点バッファのポインタ
SELECT_MODE g_aSelect_Mode[AMOUNT_POLYGON_SELECT_MODE];	//メニュー用ポリゴンの情報を格納

//************************************************
//初期化処理関数
//************************************************
void Init_Select_Mode(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MODE_GAME,
		&g_pTexture_Select_Mode[0]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MODE_RANK,
		&g_pTexture_Select_Mode[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_SELECT_MODE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Select_Mode,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Select_Mode;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Select_Mode->Lock(0, 0, (void**)&pVtx_Select_Mode, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SELECT_MODE; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Select_Mode[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Select_Mode[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Select_Mode[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Select_Mode[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Select_Mode[0].rhw = 1.0f;
		pVtx_Select_Mode[1].rhw = 1.0f;
		pVtx_Select_Mode[2].rhw = 1.0f;
		pVtx_Select_Mode[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Select_Mode[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Select_Mode[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Select_Mode[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Select_Mode[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Select_Mode[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Select_Mode[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Select_Mode[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Select_Mode[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Select_Mode += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Select_Mode->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SELECT_MODE; nCnt++)
	{
		g_aSelect_Mode[nCnt].nStyle = 0;
		g_aSelect_Mode[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSelect_Mode[nCnt].fSpanX = 0.0f;
		g_aSelect_Mode[nCnt].fSpanY = 0.0f;
		g_aSelect_Mode[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSelect_Mode[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSelect_Mode[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//初回のみ頂点を展開
	Setinfo_Select_Mode();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Select_Mode(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_SELECT_MODE; nCnt++)
	{
		if (g_pTexture_Select_Mode[nCnt] != NULL)
		{
			g_pTexture_Select_Mode[nCnt]->Release();
			g_pTexture_Select_Mode[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Select_Mode != NULL)
	{
		g_pVtxBuff_Select_Mode->Release();
		g_pVtxBuff_Select_Mode = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Select_Mode(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Select_Mode;

	//選んでるものへのポインタ
	int* pChoose;

	pChoose = Getinfo_Choose();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Select_Mode->Lock(0, 0, (void**)&pVtx_Select_Mode, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SELECT_MODE; nCnt++)
	{
		//選んでるものに応じて色変更
		if (*pChoose == 0)
		{
			g_aSelect_Mode[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_aSelect_Mode[1].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		}
		else
		{
			g_aSelect_Mode[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			g_aSelect_Mode[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//移動、回転を反映
		pVtx_Select_Mode[0].pos.x = g_aSelect_Mode[nCnt].pos.x - g_aSelect_Mode[nCnt].fSpanX;
		pVtx_Select_Mode[0].pos.y = g_aSelect_Mode[nCnt].pos.y - g_aSelect_Mode[nCnt].fSpanY;
		pVtx_Select_Mode[1].pos.x = g_aSelect_Mode[nCnt].pos.x + g_aSelect_Mode[nCnt].fSpanX;
		pVtx_Select_Mode[1].pos.y = g_aSelect_Mode[nCnt].pos.y - g_aSelect_Mode[nCnt].fSpanY;
		pVtx_Select_Mode[2].pos.x = g_aSelect_Mode[nCnt].pos.x - g_aSelect_Mode[nCnt].fSpanX;
		pVtx_Select_Mode[2].pos.y = g_aSelect_Mode[nCnt].pos.y + g_aSelect_Mode[nCnt].fSpanY;
		pVtx_Select_Mode[3].pos.x = g_aSelect_Mode[nCnt].pos.x + g_aSelect_Mode[nCnt].fSpanX;
		pVtx_Select_Mode[3].pos.y = g_aSelect_Mode[nCnt].pos.y + g_aSelect_Mode[nCnt].fSpanY;

		pVtx_Select_Mode[0].col = g_aSelect_Mode[nCnt].col;
		pVtx_Select_Mode[1].col = g_aSelect_Mode[nCnt].col;
		pVtx_Select_Mode[2].col = g_aSelect_Mode[nCnt].col;
		pVtx_Select_Mode[3].col = g_aSelect_Mode[nCnt].col;

		pVtx_Select_Mode += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Select_Mode->Unlock();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Select_Mode(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Select_Mode, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SELECT_MODE; nCnt++)
	{
		switch (g_aSelect_Mode[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Select_Mode[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_Select_Mode[1]);

			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Select_Mode(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SELECT_MODE; nCnt++)
	{
		g_aSelect_Mode[nCnt].nStyle = nCnt;

		switch (g_aSelect_Mode[nCnt].nStyle)
		{
		case 0:

			g_aSelect_Mode[nCnt].pos = D3DXVECTOR3(570.0f, 650.0f, 0.0f);
			g_aSelect_Mode[nCnt].fSpanX = 350.0f;
			g_aSelect_Mode[nCnt].fSpanY = 250.0f;
			g_aSelect_Mode[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aSelect_Mode[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aSelect_Mode[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;

		case 1:

			g_aSelect_Mode[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH - 570.0f, 650.0f, 0.0f);
			g_aSelect_Mode[nCnt].fSpanX = 350.0f;
			g_aSelect_Mode[nCnt].fSpanY = 250.0f;
			g_aSelect_Mode[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aSelect_Mode[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aSelect_Mode[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;
		}
	}
}