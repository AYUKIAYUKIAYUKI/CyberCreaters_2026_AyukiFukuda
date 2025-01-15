//************************************************
//
//ポーズフェード処理[pause_fade.cpp]
//Author：福田歩希
//
//************************************************
#include "pause.h"
#include "pause_fade.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Pause_Fade[AMOUNT_TEXTURE_PAUSE_FADE] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Pause_Fade = NULL;	//頂点バッファのポインタ
PAUSE_FADE g_aPause_Fade[AMOUNT_POLYGON_PAUSE_FADE];	//ポリゴンの情報を格納

//************************************************
//初期化処理関数
//************************************************
void Init_Pause_Fade(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLACK_PAUSE_FADE,
		&g_pTexture_Pause_Fade[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_PAUSE_FADE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Pause_Fade,
		NULL);

	////頂点情報へのポインタ
	//VERTEX_2D* pVtx_Pause_Fade;

	////頂点バッファをロックして頂点情報のポインタを取得
	//g_pVtxBuff_Pause_Fade->Lock(0, 0, (void**)&pVtx_Pause_Fade, 0);

	////初期設定
	//for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_FADE; nCnt++)
	//{
	//	//頂点座標の初期設定
	//	pVtx_Pause_Fade[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	pVtx_Pause_Fade[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	pVtx_Pause_Fade[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	pVtx_Pause_Fade[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	//視錐台の拡大率(?)の初期設定
	//	pVtx_Pause_Fade[0].rhw = 1.0f;
	//	pVtx_Pause_Fade[1].rhw = 1.0f;
	//	pVtx_Pause_Fade[2].rhw = 1.0f;
	//	pVtx_Pause_Fade[3].rhw = 1.0f;

	//	//頂点カラーの初期設定
	//	pVtx_Pause_Fade[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	pVtx_Pause_Fade[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	pVtx_Pause_Fade[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	pVtx_Pause_Fade[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//	//テクスチャ座標の初期設定
	//	pVtx_Pause_Fade[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx_Pause_Fade[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx_Pause_Fade[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx_Pause_Fade[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//	pVtx_Pause_Fade += AMOUNT_VTX;
	//}

	////頂点バッファをアンロックする
	//g_pVtxBuff_Pause_Fade->Unlock();

	////初期設定
	//for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_FADE; nCnt++)
	//{
	//	g_aPause_Fade[nCnt].nStyle = 0;
	//	g_aPause_Fade[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_aPause_Fade[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_aPause_Fade[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_aPause_Fade[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	//	g_aPause_Fade[nCnt].fLength = 0.0f;
	//	g_aPause_Fade[nCnt].fAngle = 0.0f;
	//}

	//初回のみ頂点を展開
	Setinfo_Pause_Fade();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Pause_Fade(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_PAUSE_FADE; nCnt++)
	{
		if (g_pTexture_Pause_Fade[nCnt] != NULL)
		{
			g_pTexture_Pause_Fade[nCnt]->Release();
			g_pTexture_Pause_Fade[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Pause_Fade != NULL)
	{
		g_pVtxBuff_Pause_Fade->Release();
		g_pVtxBuff_Pause_Fade = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Pause_Fade(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Pause_Fade;

	bool* pStart_M;
	pStart_M = Getinfo_Return_Pause();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Pause_Fade->Lock(0, 0, (void**)&pVtx_Pause_Fade, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_FADE; nCnt++)
	{
		//移動、回転を反映
		pVtx_Pause_Fade[0].pos.x = g_aPause_Fade[nCnt].pos.x + sinf(g_aPause_Fade[nCnt].rot.z - (D3DX_PI - g_aPause_Fade[nCnt].fAngle)) * g_aPause_Fade[nCnt].fLength;
		pVtx_Pause_Fade[0].pos.y = g_aPause_Fade[nCnt].pos.y + cosf(g_aPause_Fade[nCnt].rot.z - (D3DX_PI - g_aPause_Fade[nCnt].fAngle)) * g_aPause_Fade[nCnt].fLength;
		pVtx_Pause_Fade[1].pos.x = g_aPause_Fade[nCnt].pos.x + sinf(g_aPause_Fade[nCnt].rot.z + (D3DX_PI - g_aPause_Fade[nCnt].fAngle)) * g_aPause_Fade[nCnt].fLength;
		pVtx_Pause_Fade[1].pos.y = g_aPause_Fade[nCnt].pos.y + cosf(g_aPause_Fade[nCnt].rot.z + (D3DX_PI - g_aPause_Fade[nCnt].fAngle)) * g_aPause_Fade[nCnt].fLength;
		pVtx_Pause_Fade[2].pos.x = g_aPause_Fade[nCnt].pos.x + sinf(g_aPause_Fade[nCnt].rot.z - g_aPause_Fade[nCnt].fAngle) * g_aPause_Fade[nCnt].fLength;
		pVtx_Pause_Fade[2].pos.y = g_aPause_Fade[nCnt].pos.y + cosf(g_aPause_Fade[nCnt].rot.z - g_aPause_Fade[nCnt].fAngle) * g_aPause_Fade[nCnt].fLength;
		pVtx_Pause_Fade[3].pos.x = g_aPause_Fade[nCnt].pos.x + sinf(g_aPause_Fade[nCnt].rot.z + g_aPause_Fade[nCnt].fAngle) * g_aPause_Fade[nCnt].fLength;
		pVtx_Pause_Fade[3].pos.y = g_aPause_Fade[nCnt].pos.y + cosf(g_aPause_Fade[nCnt].rot.z + g_aPause_Fade[nCnt].fAngle) * g_aPause_Fade[nCnt].fLength;

		if (*pStart_M == false)
		{
			g_aPause_Fade[nCnt].col.a -= 0.05f;

			if (g_aPause_Fade[nCnt].col.a < 0.0f)
			{
				g_aPause_Fade[nCnt].col.a = 0.0f;
			}
		}
		else
		{
			g_aPause_Fade[nCnt].col.a += 0.1f;
		}

		pVtx_Pause_Fade[0].col = g_aPause_Fade[nCnt].col;
		pVtx_Pause_Fade[1].col = g_aPause_Fade[nCnt].col;
		pVtx_Pause_Fade[2].col = g_aPause_Fade[nCnt].col;
		pVtx_Pause_Fade[3].col = g_aPause_Fade[nCnt].col;

		pVtx_Pause_Fade += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Pause_Fade->Unlock();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Pause_Fade(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Pause_Fade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_PAUSE_FADE; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Pause_Fade[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Pause_Fade(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_FADE; nCnt++)
	{
		g_aPause_Fade[nCnt].nStyle = 0;
		g_aPause_Fade[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
		g_aPause_Fade[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Fade[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Fade[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPause_Fade[nCnt].fLength = sqrtf((990.0f * 990.0f) + (540.0f * 540.0f));
		g_aPause_Fade[nCnt].fAngle = atan2f(990.0f * 2.0f, 540.0f * 2.0f);
	}
}

//************************************************
//ポリゴン情報を送る関数
//************************************************
float* Getinfo_Pause_Fade(void)
{
	return &g_aPause_Fade[0].col.a;
}