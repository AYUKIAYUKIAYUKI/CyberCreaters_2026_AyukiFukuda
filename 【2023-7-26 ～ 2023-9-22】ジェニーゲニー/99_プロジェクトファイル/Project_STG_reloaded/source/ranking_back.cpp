//************************************************
//
//もどる[ranking_back.cpp]
//Author：福田歩希
//
//************************************************
#include "ranking_back.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Ranking_Back[AMOUNT_TEXTURE_RANKING_BACK] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Ranking_Back = NULL;	//頂点バッファのポインタ
RANKING_BACK g_aRanking_Back[AMOUNT_POLYGON_RANKING_BACK];	//カーソル用ポリゴンの情報を格納
int g_nCnt = 0;

//************************************************
//初期化処理関数
//************************************************
void Init_Ranking_Back(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_BACK,
		&g_pTexture_Ranking_Back[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_RANKING_BACK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Ranking_Back,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Ranking_Back;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Ranking_Back->Lock(0, 0, (void**)&pVtx_Ranking_Back, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BACK; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Ranking_Back[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Back[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Back[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Back[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Ranking_Back[0].rhw = 1.0f;
		pVtx_Ranking_Back[1].rhw = 1.0f;
		pVtx_Ranking_Back[2].rhw = 1.0f;
		pVtx_Ranking_Back[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Ranking_Back[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Back[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Back[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Back[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Ranking_Back[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Ranking_Back[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Ranking_Back[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Ranking_Back[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Ranking_Back += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Ranking_Back->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BACK; nCnt++)
	{
		g_aRanking_Back[nCnt].nStyle = 0;
		g_aRanking_Back[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Back[nCnt].fSpanX = 0.0f;
		g_aRanking_Back[nCnt].fSpanY = 0.0f;
		g_aRanking_Back[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Back[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Back[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aRanking_Back[nCnt].fLength = 0.0f;
		g_aRanking_Back[nCnt].fAngle = 0.0f;
		g_aRanking_Back[nCnt].fSPD_X = 0.0f;
		g_aRanking_Back[nCnt].colA = 0.0f;
	}

	g_nCnt = 0;

	//初回のみ頂点を展開
	Setinfo_Ranking_Back();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Ranking_Back(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_RANKING_BACK; nCnt++)
	{
		if (g_pTexture_Ranking_Back[nCnt] != NULL)
		{
			g_pTexture_Ranking_Back[nCnt]->Release();
			g_pTexture_Ranking_Back[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Ranking_Back != NULL)
	{
		g_pVtxBuff_Ranking_Back->Release();
		g_pVtxBuff_Ranking_Back = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Ranking_Back(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Ranking_Back;

	bool* pStart_R;
	pStart_R = Getinfo_Ranking();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Ranking_Back->Lock(0, 0, (void**)&pVtx_Ranking_Back, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BACK; nCnt++)
	{
		//移動など反映
		pVtx_Ranking_Back[0].pos.x = g_aRanking_Back[nCnt].pos.x + sinf(g_aRanking_Back[nCnt].rot.z - (D3DX_PI - g_aRanking_Back[nCnt].fAngle)) * g_aRanking_Back[nCnt].fLength;
		pVtx_Ranking_Back[0].pos.y = g_aRanking_Back[nCnt].pos.y + cosf(g_aRanking_Back[nCnt].rot.z - (D3DX_PI - g_aRanking_Back[nCnt].fAngle)) * g_aRanking_Back[nCnt].fLength;
		pVtx_Ranking_Back[1].pos.x = g_aRanking_Back[nCnt].pos.x + sinf(g_aRanking_Back[nCnt].rot.z + (D3DX_PI - g_aRanking_Back[nCnt].fAngle)) * g_aRanking_Back[nCnt].fLength;
		pVtx_Ranking_Back[1].pos.y = g_aRanking_Back[nCnt].pos.y + cosf(g_aRanking_Back[nCnt].rot.z + (D3DX_PI - g_aRanking_Back[nCnt].fAngle)) * g_aRanking_Back[nCnt].fLength;
		pVtx_Ranking_Back[2].pos.x = g_aRanking_Back[nCnt].pos.x + sinf(g_aRanking_Back[nCnt].rot.z - g_aRanking_Back[nCnt].fAngle) * g_aRanking_Back[nCnt].fLength;
		pVtx_Ranking_Back[2].pos.y = g_aRanking_Back[nCnt].pos.y + cosf(g_aRanking_Back[nCnt].rot.z - g_aRanking_Back[nCnt].fAngle) * g_aRanking_Back[nCnt].fLength;
		pVtx_Ranking_Back[3].pos.x = g_aRanking_Back[nCnt].pos.x + sinf(g_aRanking_Back[nCnt].rot.z + g_aRanking_Back[nCnt].fAngle) * g_aRanking_Back[nCnt].fLength;
		pVtx_Ranking_Back[3].pos.y = g_aRanking_Back[nCnt].pos.y + cosf(g_aRanking_Back[nCnt].rot.z + g_aRanking_Back[nCnt].fAngle) * g_aRanking_Back[nCnt].fLength;

		if (*pStart_R == true && g_nCnt < 5)
		{
			g_nCnt++;

			g_aRanking_Back[nCnt].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		}
		else
		{
			g_aRanking_Back[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		pVtx_Ranking_Back[0].col = g_aRanking_Back[nCnt].col;
		pVtx_Ranking_Back[1].col = g_aRanking_Back[nCnt].col;
		pVtx_Ranking_Back[2].col = g_aRanking_Back[nCnt].col;
		pVtx_Ranking_Back[3].col = g_aRanking_Back[nCnt].col;

		pVtx_Ranking_Back += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Ranking_Back->Unlock();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Ranking_Back(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Ranking_Back, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BACK; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Ranking_Back[0]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Ranking_Back(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BACK; nCnt++)
	{
		g_aRanking_Back[nCnt].nStyle = nCnt;
		g_aRanking_Back[nCnt].pos = D3DXVECTOR3(1650.0f, 1000.0f, 0.0f);
		g_aRanking_Back[nCnt].fSpanX = 300.0f;
		g_aRanking_Back[nCnt].fSpanY = 50.0f;
		g_aRanking_Back[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Back[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Back[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRanking_Back[nCnt].fLength = sqrtf((g_aRanking_Back[nCnt].fSpanX * g_aRanking_Back[nCnt].fSpanX) + (g_aRanking_Back[nCnt].fSpanY * g_aRanking_Back[nCnt].fSpanY));
		g_aRanking_Back[nCnt].fAngle = atan2f(g_aRanking_Back[nCnt].fSpanX * 2.0f, g_aRanking_Back[nCnt].fSpanY * 2.0f);
		g_aRanking_Back[nCnt].fSPD_X = 1.0f;
		g_aRanking_Back[nCnt].colA = 0.01f;
	}
}