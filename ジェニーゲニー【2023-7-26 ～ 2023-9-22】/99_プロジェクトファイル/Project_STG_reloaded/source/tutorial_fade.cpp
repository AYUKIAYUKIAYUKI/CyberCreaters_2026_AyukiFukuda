//************************************************
//
//チュートリアルフェード処理[tutorial_fade.cpp]
//Author：福田歩希
//
//************************************************
#include "tutorial_fade.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Tutorial_Fade[AMOUNT_TEXTURE_TUTORIAL_FADE] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Tutorial_Fade = NULL;	//頂点バッファのポインタ
TUTORIAL_FADE g_aTutorial_Fade[AMOUNT_POLYGON_TUTORIAL_FADE];	//メニュー用ポリゴンの情報を格納

//************************************************
//初期化処理関数
//************************************************
void Init_Tutorial_Fade(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLACK_TUTORIAL_FADE,
		&g_pTexture_Tutorial_Fade[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TUTORIAL_FADE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Tutorial_Fade,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Tutorial_Fade;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Tutorial_Fade->Lock(0, 0, (void**)&pVtx_Tutorial_Fade, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_FADE; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Tutorial_Fade[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Fade[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Fade[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Fade[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Tutorial_Fade[0].rhw = 1.0f;
		pVtx_Tutorial_Fade[1].rhw = 1.0f;
		pVtx_Tutorial_Fade[2].rhw = 1.0f;
		pVtx_Tutorial_Fade[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Tutorial_Fade[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Fade[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Fade[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Fade[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Tutorial_Fade[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Tutorial_Fade[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Tutorial_Fade[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Tutorial_Fade[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Tutorial_Fade += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Tutorial_Fade->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_FADE; nCnt++)
	{
		g_aTutorial_Fade[nCnt].nStyle = 0;
		g_aTutorial_Fade[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Fade[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Fade[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Fade[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aTutorial_Fade[nCnt].fLength = 0.0f;
		g_aTutorial_Fade[nCnt].fAngle = 0.0f;
	}

	//初回のみ頂点を展開
	Setinfo_Tutorial_Fade();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Tutorial_Fade(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_TUTORIAL_FADE; nCnt++)
	{
		if (g_pTexture_Tutorial_Fade[nCnt] != NULL)
		{
			g_pTexture_Tutorial_Fade[nCnt]->Release();
			g_pTexture_Tutorial_Fade[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Tutorial_Fade != NULL)
	{
		g_pVtxBuff_Tutorial_Fade->Release();
		g_pVtxBuff_Tutorial_Fade = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Tutorial_Fade(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Tutorial_Fade;

	bool* pStart_T;
	pStart_T = Getinfo_Tutorial();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Tutorial_Fade->Lock(0, 0, (void**)&pVtx_Tutorial_Fade, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_FADE; nCnt++)
	{
		//移動、回転を反映
		pVtx_Tutorial_Fade[0].pos.x = g_aTutorial_Fade[nCnt].pos.x + sinf(g_aTutorial_Fade[nCnt].rot.z - (D3DX_PI - g_aTutorial_Fade[nCnt].fAngle)) * g_aTutorial_Fade[nCnt].fLength;
		pVtx_Tutorial_Fade[0].pos.y = g_aTutorial_Fade[nCnt].pos.y + cosf(g_aTutorial_Fade[nCnt].rot.z - (D3DX_PI - g_aTutorial_Fade[nCnt].fAngle)) * g_aTutorial_Fade[nCnt].fLength;
		pVtx_Tutorial_Fade[1].pos.x = g_aTutorial_Fade[nCnt].pos.x + sinf(g_aTutorial_Fade[nCnt].rot.z + (D3DX_PI - g_aTutorial_Fade[nCnt].fAngle)) * g_aTutorial_Fade[nCnt].fLength;
		pVtx_Tutorial_Fade[1].pos.y = g_aTutorial_Fade[nCnt].pos.y + cosf(g_aTutorial_Fade[nCnt].rot.z + (D3DX_PI - g_aTutorial_Fade[nCnt].fAngle)) * g_aTutorial_Fade[nCnt].fLength;
		pVtx_Tutorial_Fade[2].pos.x = g_aTutorial_Fade[nCnt].pos.x + sinf(g_aTutorial_Fade[nCnt].rot.z - g_aTutorial_Fade[nCnt].fAngle) * g_aTutorial_Fade[nCnt].fLength;
		pVtx_Tutorial_Fade[2].pos.y = g_aTutorial_Fade[nCnt].pos.y + cosf(g_aTutorial_Fade[nCnt].rot.z - g_aTutorial_Fade[nCnt].fAngle) * g_aTutorial_Fade[nCnt].fLength;
		pVtx_Tutorial_Fade[3].pos.x = g_aTutorial_Fade[nCnt].pos.x + sinf(g_aTutorial_Fade[nCnt].rot.z + g_aTutorial_Fade[nCnt].fAngle) * g_aTutorial_Fade[nCnt].fLength;
		pVtx_Tutorial_Fade[3].pos.y = g_aTutorial_Fade[nCnt].pos.y + cosf(g_aTutorial_Fade[nCnt].rot.z + g_aTutorial_Fade[nCnt].fAngle) * g_aTutorial_Fade[nCnt].fLength;

		if (*pStart_T == false)
		{
			g_aTutorial_Fade[nCnt].col.a -= 0.05f;

			if (g_aTutorial_Fade[nCnt].col.a < 0.0f)
			{
				g_aTutorial_Fade[nCnt].col.a = 0.0f;
			}
		}
		else
		{
			g_aTutorial_Fade[nCnt].col.a += 0.1f;
		}

		pVtx_Tutorial_Fade[0].col = g_aTutorial_Fade[nCnt].col;
		pVtx_Tutorial_Fade[1].col = g_aTutorial_Fade[nCnt].col;
		pVtx_Tutorial_Fade[2].col = g_aTutorial_Fade[nCnt].col;
		pVtx_Tutorial_Fade[3].col = g_aTutorial_Fade[nCnt].col;

		pVtx_Tutorial_Fade += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Tutorial_Fade->Unlock();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Tutorial_Fade(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Tutorial_Fade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_TUTORIAL_FADE; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Tutorial_Fade[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Tutorial_Fade(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_FADE; nCnt++)
	{
		g_aTutorial_Fade[nCnt].nStyle = 0;
		g_aTutorial_Fade[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
		g_aTutorial_Fade[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Fade[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Fade[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTutorial_Fade[nCnt].fLength = sqrtf((990.0f * 990.0f) + (540.0f * 540.0f));
		g_aTutorial_Fade[nCnt].fAngle = atan2f(990.0f * 2.0f, 540.0f * 2.0f);
	}
}

//************************************************
//ポリゴン情報を送る関数
//************************************************
float* Getinfo_Tutorial_Fade(void)
{
	return &g_aTutorial_Fade[0].col.a;
}