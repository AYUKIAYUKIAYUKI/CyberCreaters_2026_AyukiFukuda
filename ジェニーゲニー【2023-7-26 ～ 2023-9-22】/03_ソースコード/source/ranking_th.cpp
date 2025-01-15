//************************************************
//
//順位のやつ[ranking_th.cpp]
//Author：福田歩希
//
//************************************************
#include "ranking_th.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Ranking_TH[AMOUNT_TEXTURE_RANKING_TH] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Ranking_TH = NULL;	//頂点バッファのポインタ
RANKING_TH g_aRanking_TH[AMOUNT_POLYGON_RANKING_TH];	//カーソル用ポリゴンの情報を格納

//************************************************
//初期化処理関数
//************************************************
void Init_Ranking_TH(int nMode)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_1ST,
		&g_pTexture_Ranking_TH[0]);

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_2ND,
		&g_pTexture_Ranking_TH[1]);

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_3RD,
		&g_pTexture_Ranking_TH[2]);

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_4TH,
		&g_pTexture_Ranking_TH[3]);

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_5TH,
		&g_pTexture_Ranking_TH[4]);

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_YOURS,
		&g_pTexture_Ranking_TH[5]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_RANKING_TH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Ranking_TH,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Ranking_TH;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Ranking_TH->Lock(0, 0, (void**)&pVtx_Ranking_TH, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_TH; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Ranking_TH[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_TH[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_TH[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_TH[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Ranking_TH[0].rhw = 1.0f;
		pVtx_Ranking_TH[1].rhw = 1.0f;
		pVtx_Ranking_TH[2].rhw = 1.0f;
		pVtx_Ranking_TH[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Ranking_TH[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_TH[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_TH[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_TH[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Ranking_TH[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Ranking_TH[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Ranking_TH[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Ranking_TH[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Ranking_TH += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Ranking_TH->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_TH; nCnt++)
	{
		g_aRanking_TH[nCnt].nStyle = 0;
		g_aRanking_TH[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_TH[nCnt].fSpanX = 0.0f;
		g_aRanking_TH[nCnt].fSpanY = 0.0f;
		g_aRanking_TH[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_TH[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_TH[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aRanking_TH[nCnt].fLength = 0.0f;
		g_aRanking_TH[nCnt].fAngle = 0.0f;
		g_aRanking_TH[nCnt].fSPD_X = 0.0f;
		g_aRanking_TH[nCnt].colA = 0.0f;
	}

	//初回のみ頂点を展開
	Setinfo_Ranking_TH(nMode);
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Ranking_TH(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_RANKING_TH; nCnt++)
	{
		if (g_pTexture_Ranking_TH[nCnt] != NULL)
		{
			g_pTexture_Ranking_TH[nCnt]->Release();
			g_pTexture_Ranking_TH[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Ranking_TH != NULL)
	{
		g_pVtxBuff_Ranking_TH->Release();
		g_pVtxBuff_Ranking_TH = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Ranking_TH(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Ranking_TH;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Ranking_TH->Lock(0, 0, (void**)&pVtx_Ranking_TH, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_TH; nCnt++)
	{
		//移動など反映
		pVtx_Ranking_TH[0].pos.x = g_aRanking_TH[nCnt].pos.x + sinf(g_aRanking_TH[nCnt].rot.z - (D3DX_PI - g_aRanking_TH[nCnt].fAngle)) * g_aRanking_TH[nCnt].fLength;
		pVtx_Ranking_TH[0].pos.y = g_aRanking_TH[nCnt].pos.y + cosf(g_aRanking_TH[nCnt].rot.z - (D3DX_PI - g_aRanking_TH[nCnt].fAngle)) * g_aRanking_TH[nCnt].fLength;
		pVtx_Ranking_TH[1].pos.x = g_aRanking_TH[nCnt].pos.x + sinf(g_aRanking_TH[nCnt].rot.z + (D3DX_PI - g_aRanking_TH[nCnt].fAngle)) * g_aRanking_TH[nCnt].fLength;
		pVtx_Ranking_TH[1].pos.y = g_aRanking_TH[nCnt].pos.y + cosf(g_aRanking_TH[nCnt].rot.z + (D3DX_PI - g_aRanking_TH[nCnt].fAngle)) * g_aRanking_TH[nCnt].fLength;
		pVtx_Ranking_TH[2].pos.x = g_aRanking_TH[nCnt].pos.x + sinf(g_aRanking_TH[nCnt].rot.z - g_aRanking_TH[nCnt].fAngle) * g_aRanking_TH[nCnt].fLength;
		pVtx_Ranking_TH[2].pos.y = g_aRanking_TH[nCnt].pos.y + cosf(g_aRanking_TH[nCnt].rot.z - g_aRanking_TH[nCnt].fAngle) * g_aRanking_TH[nCnt].fLength;
		pVtx_Ranking_TH[3].pos.x = g_aRanking_TH[nCnt].pos.x + sinf(g_aRanking_TH[nCnt].rot.z + g_aRanking_TH[nCnt].fAngle) * g_aRanking_TH[nCnt].fLength;
		pVtx_Ranking_TH[3].pos.y = g_aRanking_TH[nCnt].pos.y + cosf(g_aRanking_TH[nCnt].rot.z + g_aRanking_TH[nCnt].fAngle) * g_aRanking_TH[nCnt].fLength;

		pVtx_Ranking_TH[0].col = g_aRanking_TH[nCnt].col;
		pVtx_Ranking_TH[1].col = g_aRanking_TH[nCnt].col;
		pVtx_Ranking_TH[2].col = g_aRanking_TH[nCnt].col;
		pVtx_Ranking_TH[3].col = g_aRanking_TH[nCnt].col;

		pVtx_Ranking_TH += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Ranking_TH->Unlock();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Ranking_TH(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Ranking_TH, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_TH; nCnt++)
	{
		switch (g_aRanking_TH[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Ranking_TH[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_Ranking_TH[1]);

			break;

		case 2:

			pDevice->SetTexture(0, g_pTexture_Ranking_TH[2]);

			break;

		case 3:

			pDevice->SetTexture(0, g_pTexture_Ranking_TH[3]);

			break;

		case 4:

			pDevice->SetTexture(0, g_pTexture_Ranking_TH[4]);

			break;
		
		case 5:

			pDevice->SetTexture(0, g_pTexture_Ranking_TH[5]);

			break;
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Ranking_TH(int nMode)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_TH; nCnt++)
	{
		g_aRanking_TH[nCnt].nStyle = nCnt;

		switch (nCnt)
		{
		case 0:

			g_aRanking_TH[nCnt].pos = D3DXVECTOR3(570.0f, 200.0f, 0.0f);
			g_aRanking_TH[nCnt].fSpanX = 187.5f;
			g_aRanking_TH[nCnt].fSpanY = 112.5f;

			break;

		case 1:

			g_aRanking_TH[nCnt].pos = D3DXVECTOR3(230.0f, 500.0f, 0.0f);
			g_aRanking_TH[nCnt].fSpanX = 125.0f;
			g_aRanking_TH[nCnt].fSpanY = 75.0f;

			break;

		case 2:

			g_aRanking_TH[nCnt].pos = D3DXVECTOR3(1230.0f, 500.0f, 0.0f);
			g_aRanking_TH[nCnt].fSpanX = 125.0f;
			g_aRanking_TH[nCnt].fSpanY = 75.0f;

			break;

		case 3:

			g_aRanking_TH[nCnt].pos = D3DXVECTOR3(230.0f, 720.0f, 0.0f);
			g_aRanking_TH[nCnt].fSpanX = 100.0f;
			g_aRanking_TH[nCnt].fSpanY = 50.0f;

			break;

		case 4:

			g_aRanking_TH[nCnt].pos = D3DXVECTOR3(1230.0f, 720.0f, 0.0f);
			g_aRanking_TH[nCnt].fSpanX = 100.0f;
			g_aRanking_TH[nCnt].fSpanY = 50.0f;

			break;

		case 5:

			if (nMode == 1)
			{
				g_aRanking_TH[nCnt].pos = D3DXVECTOR3(350.0f, 925.0f, 0.0f);
				g_aRanking_TH[nCnt].fSpanX = 250.0f;
				g_aRanking_TH[nCnt].fSpanY = 50.0f;
			}

			break;
		}

		g_aRanking_TH[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_TH[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_TH[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRanking_TH[nCnt].fLength = sqrtf((g_aRanking_TH[nCnt].fSpanX * g_aRanking_TH[nCnt].fSpanX) + (g_aRanking_TH[nCnt].fSpanY * g_aRanking_TH[nCnt].fSpanY));
		g_aRanking_TH[nCnt].fAngle = atan2f(g_aRanking_TH[nCnt].fSpanX * 2.0f, g_aRanking_TH[nCnt].fSpanY * 2.0f);
		g_aRanking_TH[nCnt].fSPD_X = 1.0f;
		g_aRanking_TH[nCnt].colA = 0.01f;
	}
}