//************************************************
//
//フェード処理[fade.cpp]
//Author：福田歩希
//
//************************************************
#include "fade.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Fade = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Fade = NULL;	//頂点バッファのポインタ
FADE g_aFade;	//フェード情報

//************************************************
//ポリゴン初期化処理関数
//************************************************
void InitFade()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_FADE,
		&g_pTexture_Fade);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Fade,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Fade;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Fade->Lock(0, 0, (void**)&pVtx_Fade, 0);

	//頂点座標の初期設定
	pVtx_Fade[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Fade[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Fade[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Fade[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Fade[0].rhw = 1.0f;
	pVtx_Fade[1].rhw = 1.0f;
	pVtx_Fade[2].rhw = 1.0f;
	pVtx_Fade[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Fade[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Fade[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Fade[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Fade[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の初期設定
	pVtx_Fade[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Fade[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Fade[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Fade[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Fade->Unlock();

	//フェード構造体の情報の初期化群
	g_aFade.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aFade.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aFade.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aFade.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aFade.fRadius[nCnt] = 0.0f;
	}
	g_aFade.fLength = 0.0f;
	g_aFade.fAngle = 0.0f;
	g_aFade.bFadeIn = false;
	g_aFade.bFadeOut = false;

	//フェード構造体に情報を付与
	SetInfoFade();

	//位置に基づきポリゴンを展開
	UpdatePosFade();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void UninitFade(void)
{
	//テクスチャの破棄
	if (g_pTexture_Fade != NULL)
	{
		g_pTexture_Fade->Release();
		g_pTexture_Fade = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Fade != NULL)
	{
		g_pVtxBuff_Fade->Release();
		g_pVtxBuff_Fade = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void UpdateFade(void)
{
	if (g_aFade.bFadeIn)
	{
		if (g_aFade.col.a > -0.1f)
		{
			UpdateColFade();
		}
	}
	else if (g_aFade.bFadeOut)
	{
		if (g_aFade.col.a < 1.1f)
		{
			UpdateColFade();
		}
	}
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void DrawFade(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Fade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Fade);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//フェード構造体の情報を設定する関数
//************************************************
void SetInfoFade(void)
{
	g_aFade.pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
	g_aFade.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aFade.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aFade.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aFade.fRadius[0] = RADIUS_FADE_X;	//フェード横半幅
	g_aFade.fRadius[1] = RADIUS_FADE_Y;	//フェード縦半幅
	g_aFade.fLength = sqrtf((g_aFade.fRadius[0] * g_aFade.fRadius[0]) + (g_aFade.fRadius[1] * g_aFade.fRadius[1]));
	g_aFade.fAngle = atan2f(g_aFade.fRadius[0] * 2.0f, g_aFade.fRadius[1] * 2.0f);
}

//************************************************
//フェードの位置を設定する関数
//************************************************
void UpdatePosFade(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Fade;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Fade->Lock(0, 0, (void**)&pVtx_Fade, 0);

	pVtx_Fade[0].pos.x = g_aFade.pos.x + sinf(g_aFade.rot.z - (D3DX_PI - g_aFade.fAngle)) * g_aFade.fLength;
	pVtx_Fade[0].pos.y = g_aFade.pos.y + cosf(g_aFade.rot.z - (D3DX_PI - g_aFade.fAngle)) * g_aFade.fLength;
	pVtx_Fade[1].pos.x = g_aFade.pos.x + sinf(g_aFade.rot.z + (D3DX_PI - g_aFade.fAngle)) * g_aFade.fLength;
	pVtx_Fade[1].pos.y = g_aFade.pos.y + cosf(g_aFade.rot.z + (D3DX_PI - g_aFade.fAngle)) * g_aFade.fLength;
	pVtx_Fade[2].pos.x = g_aFade.pos.x + sinf(g_aFade.rot.z - g_aFade.fAngle) * g_aFade.fLength;
	pVtx_Fade[2].pos.y = g_aFade.pos.y + cosf(g_aFade.rot.z - g_aFade.fAngle) * g_aFade.fLength;
	pVtx_Fade[3].pos.x = g_aFade.pos.x + sinf(g_aFade.rot.z + g_aFade.fAngle) * g_aFade.fLength;
	pVtx_Fade[3].pos.y = g_aFade.pos.y + cosf(g_aFade.rot.z + g_aFade.fAngle) * g_aFade.fLength;

	//頂点バッファをアンロックする
	g_pVtxBuff_Fade->Unlock();
}

//************************************************
//フェードの色を設定する関数
//************************************************
void UpdateColFade(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Fade;

	if (g_aFade.bFadeIn)
	{
		g_aFade.col.a -= SPD_CHANGE_COL_FADE;
	}
	else if (g_aFade.bFadeOut)
	{
		g_aFade.col.a += SPD_CHANGE_COL_FADE;
	}

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Fade->Lock(0, 0, (void**)&pVtx_Fade, 0);

	//色を反映
	pVtx_Fade[0].col = g_aFade.col;
	pVtx_Fade[1].col = g_aFade.col;
	pVtx_Fade[2].col = g_aFade.col;
	pVtx_Fade[3].col = g_aFade.col;

	//頂点バッファをアンロックする
	g_pVtxBuff_Fade->Unlock();
}

//************************************************
//フェード構造体のアドレスを渡す
//************************************************
FADE* GetInfoFade(void)
{
	return &g_aFade;
}