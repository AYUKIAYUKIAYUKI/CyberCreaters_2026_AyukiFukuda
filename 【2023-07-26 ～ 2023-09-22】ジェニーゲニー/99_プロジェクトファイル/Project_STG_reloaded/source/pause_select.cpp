//************************************************
//
//ポーズ画面モード選択[pause_select.cpp]
//Author：福田歩希
//
//************************************************
#include "pause_cursor.h"
#include "pause_select.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Pause_Select[AMOUNT_TEXTURE_PAUSE_SELECT] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Pause_Select = NULL;	//頂点バッファのポインタ
PAUSE_SELECT g_aPause_Select[AMOUNT_POLYGON_PAUSE_SELECT];	//ポリゴンの情報を格納

//************************************************
//初期化処理関数
//************************************************
void Init_Pause_Select(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PAUSE_CONTINUE,
		&g_pTexture_Pause_Select[0]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PAUSE_RETRY,
		&g_pTexture_Pause_Select[1]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PAUSE_MENU,
		&g_pTexture_Pause_Select[2]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PAUSE_TITLE,
		&g_pTexture_Pause_Select[3]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_PAUSE_SELECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Pause_Select,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Pause_Select;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Pause_Select->Lock(0, 0, (void**)&pVtx_Pause_Select, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_SELECT; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Pause_Select[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Pause_Select[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Pause_Select[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Pause_Select[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Pause_Select[0].rhw = 1.0f;
		pVtx_Pause_Select[1].rhw = 1.0f;
		pVtx_Pause_Select[2].rhw = 1.0f;
		pVtx_Pause_Select[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Pause_Select[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Pause_Select[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Pause_Select[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Pause_Select[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Pause_Select[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Pause_Select[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Pause_Select[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Pause_Select[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Pause_Select += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Pause_Select->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_SELECT; nCnt++)
	{
		g_aPause_Select[nCnt].nStyle = 0;
		g_aPause_Select[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Select[nCnt].fSpanX = 0.0f;
		g_aPause_Select[nCnt].fSpanY = 0.0f;
		g_aPause_Select[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Select[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Select[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aPause_Select[nCnt].colA = 0.0f;
	}

	//初回のみ頂点を展開
	Setinfo_Pause_Select();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Pause_Select(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_PAUSE_SELECT; nCnt++)
	{
		if (g_pTexture_Pause_Select[nCnt] != NULL)
		{
			g_pTexture_Pause_Select[nCnt]->Release();
			g_pTexture_Pause_Select[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Pause_Select != NULL)
	{
		g_pVtxBuff_Pause_Select->Release();
		g_pVtxBuff_Pause_Select = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Pause_Select(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Pause_Select;

	//選んでるものへのポインタ
	int* pChoose_Pause;
	pChoose_Pause = Getinfo_Choose_Pause();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Pause_Select->Lock(0, 0, (void**)&pVtx_Pause_Select, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_SELECT; nCnt++)
	{
		if (g_aPause_Select[nCnt].col.a < 1.0f)
		{
			g_aPause_Select[nCnt].colA *= 1.2f;
		}
		else
		{
			g_aPause_Select[nCnt].colA = 1.0f;
		}

		//選んでるものに応じて色変更
		switch(*pChoose_Pause)
		{
		case 0:

			g_aPause_Select[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aPause_Select[0].colA);
			g_aPause_Select[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[1].colA);
			g_aPause_Select[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[2].colA);
			g_aPause_Select[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[3].colA);

			break;

		case 1:

			g_aPause_Select[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[0].colA);
			g_aPause_Select[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aPause_Select[1].colA);
			g_aPause_Select[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[2].colA);
			g_aPause_Select[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[3].colA);

			break;

		case 2:

			g_aPause_Select[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[0].colA);
			g_aPause_Select[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[1].colA);
			g_aPause_Select[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aPause_Select[2].colA);
			g_aPause_Select[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[3].colA);

			break;

		case 3:

			g_aPause_Select[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[0].colA);
			g_aPause_Select[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[1].colA);
			g_aPause_Select[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[2].colA);
			g_aPause_Select[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aPause_Select[3].colA);

			break;
		}

		//移動、回転を反映
		pVtx_Pause_Select[0].pos.x = g_aPause_Select[nCnt].pos.x - g_aPause_Select[nCnt].fSpanX;
		pVtx_Pause_Select[0].pos.y = g_aPause_Select[nCnt].pos.y - g_aPause_Select[nCnt].fSpanY;
		pVtx_Pause_Select[1].pos.x = g_aPause_Select[nCnt].pos.x + g_aPause_Select[nCnt].fSpanX;
		pVtx_Pause_Select[1].pos.y = g_aPause_Select[nCnt].pos.y - g_aPause_Select[nCnt].fSpanY;
		pVtx_Pause_Select[2].pos.x = g_aPause_Select[nCnt].pos.x - g_aPause_Select[nCnt].fSpanX;
		pVtx_Pause_Select[2].pos.y = g_aPause_Select[nCnt].pos.y + g_aPause_Select[nCnt].fSpanY;
		pVtx_Pause_Select[3].pos.x = g_aPause_Select[nCnt].pos.x + g_aPause_Select[nCnt].fSpanX;
		pVtx_Pause_Select[3].pos.y = g_aPause_Select[nCnt].pos.y + g_aPause_Select[nCnt].fSpanY;

		pVtx_Pause_Select[0].col = g_aPause_Select[nCnt].col;
		pVtx_Pause_Select[1].col = g_aPause_Select[nCnt].col;
		pVtx_Pause_Select[2].col = g_aPause_Select[nCnt].col;
		pVtx_Pause_Select[3].col = g_aPause_Select[nCnt].col;

		pVtx_Pause_Select += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Pause_Select->Unlock();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Pause_Select(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Pause_Select, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_SELECT; nCnt++)
	{
		switch (g_aPause_Select[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Pause_Select[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_Pause_Select[1]);

			break;

		case 2:

			pDevice->SetTexture(0, g_pTexture_Pause_Select[2]);

			break;

		case 3:

			pDevice->SetTexture(0, g_pTexture_Pause_Select[3]);

			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Pause_Select(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_SELECT; nCnt++)
	{
		g_aPause_Select[nCnt].nStyle = nCnt;

		switch (g_aPause_Select[nCnt].nStyle)
		{
		case 0:

			g_aPause_Select[nCnt].pos = D3DXVECTOR3(700.0f, 450.0f, 0.0f);
			g_aPause_Select[nCnt].fSpanX = 300.0f;
			g_aPause_Select[nCnt].fSpanY = 50.0f;

			break;

		case 1:

			g_aPause_Select[nCnt].pos = D3DXVECTOR3(1280.0f, 450.0f, 0.0f);
			g_aPause_Select[nCnt].fSpanX = 150.0f;
			g_aPause_Select[nCnt].fSpanY = 50.0f;

			break;

		case 2:

			g_aPause_Select[nCnt].pos = D3DXVECTOR3(700.0f, 650.0f, 0.0f);
			g_aPause_Select[nCnt].fSpanX = 200.0f;
			g_aPause_Select[nCnt].fSpanY = 50.0f;

			break;

		case 3:

			g_aPause_Select[nCnt].pos = D3DXVECTOR3(1280.0f, 650.0f, 0.0f);
			g_aPause_Select[nCnt].fSpanX = 200.0f;
			g_aPause_Select[nCnt].fSpanY = 50.0f;

			break;
		}

		g_aPause_Select[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Select[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Select[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		g_aPause_Select[nCnt].colA = 0.01f;
	}
}