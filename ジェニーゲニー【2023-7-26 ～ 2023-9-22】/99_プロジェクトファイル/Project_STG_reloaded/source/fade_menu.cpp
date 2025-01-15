//************************************************
//
//メニューフェード処理[menu_fade.cpp]
//Author：福田歩希
//
//************************************************
#include "fade.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Fade_Menu[AMOUNT_TEXTURE_FADE_MENU] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Fade_Menu = NULL;	//頂点バッファのポインタ
FADE_MENU_OBJECT g_aFade_Menu[AMOUNT_POLYGON_FADE_MENU];	//メニュー用ポリゴンの情報を格納

//************************************************
//初期化処理関数
//************************************************
void Init_Fade_Menu(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLACK_FADE_MENU,
		&g_pTexture_Fade_Menu[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_FADE_MENU,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Fade_Menu,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Fade_Menu;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Fade_Menu->Lock(0, 0, (void**)&pVtx_Fade_Menu, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FADE_MENU; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Fade_Menu[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Fade_Menu[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Fade_Menu[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Fade_Menu[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Fade_Menu[0].rhw = 1.0f;
		pVtx_Fade_Menu[1].rhw = 1.0f;
		pVtx_Fade_Menu[2].rhw = 1.0f;
		pVtx_Fade_Menu[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Fade_Menu[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Fade_Menu[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Fade_Menu[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Fade_Menu[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Fade_Menu[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Fade_Menu[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Fade_Menu[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Fade_Menu[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Fade_Menu += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Fade_Menu->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FADE_MENU; nCnt++)
	{
		g_aFade_Menu[nCnt].nStyle = 0;
		g_aFade_Menu[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFade_Menu[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFade_Menu[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFade_Menu[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aFade_Menu[nCnt].fLength = 0.0f;
		g_aFade_Menu[nCnt].fAngle = 0.0f;
	}

	//初回のみ頂点を展開
	Setinfo_Fade_Menu();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Fade_Menu(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_FADE_MENU; nCnt++)
	{
		if (g_pTexture_Fade_Menu[nCnt] != NULL)
		{
			g_pTexture_Fade_Menu[nCnt]->Release();
			g_pTexture_Fade_Menu[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Fade_Menu != NULL)
	{
		g_pVtxBuff_Fade_Menu->Release();
		g_pVtxBuff_Fade_Menu = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Fade_Menu(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Fade_Menu;

	bool* pStart;
	pStart = Getinfo_Menu();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Fade_Menu->Lock(0, 0, (void**)&pVtx_Fade_Menu, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FADE_MENU; nCnt++)
	{
		//移動、回転を反映
		pVtx_Fade_Menu[0].pos.x = g_aFade_Menu[nCnt].pos.x + sinf(g_aFade_Menu[nCnt].rot.z - (D3DX_PI - g_aFade_Menu[nCnt].fAngle)) * g_aFade_Menu[nCnt].fLength;
		pVtx_Fade_Menu[0].pos.y = g_aFade_Menu[nCnt].pos.y + cosf(g_aFade_Menu[nCnt].rot.z - (D3DX_PI - g_aFade_Menu[nCnt].fAngle)) * g_aFade_Menu[nCnt].fLength;
		pVtx_Fade_Menu[1].pos.x = g_aFade_Menu[nCnt].pos.x + sinf(g_aFade_Menu[nCnt].rot.z + (D3DX_PI - g_aFade_Menu[nCnt].fAngle)) * g_aFade_Menu[nCnt].fLength;
		pVtx_Fade_Menu[1].pos.y = g_aFade_Menu[nCnt].pos.y + cosf(g_aFade_Menu[nCnt].rot.z + (D3DX_PI - g_aFade_Menu[nCnt].fAngle)) * g_aFade_Menu[nCnt].fLength;
		pVtx_Fade_Menu[2].pos.x = g_aFade_Menu[nCnt].pos.x + sinf(g_aFade_Menu[nCnt].rot.z - g_aFade_Menu[nCnt].fAngle) * g_aFade_Menu[nCnt].fLength;
		pVtx_Fade_Menu[2].pos.y = g_aFade_Menu[nCnt].pos.y + cosf(g_aFade_Menu[nCnt].rot.z - g_aFade_Menu[nCnt].fAngle) * g_aFade_Menu[nCnt].fLength;
		pVtx_Fade_Menu[3].pos.x = g_aFade_Menu[nCnt].pos.x + sinf(g_aFade_Menu[nCnt].rot.z + g_aFade_Menu[nCnt].fAngle) * g_aFade_Menu[nCnt].fLength;
		pVtx_Fade_Menu[3].pos.y = g_aFade_Menu[nCnt].pos.y + cosf(g_aFade_Menu[nCnt].rot.z + g_aFade_Menu[nCnt].fAngle) * g_aFade_Menu[nCnt].fLength;

		if (*pStart == false)
		{
			g_aFade_Menu[nCnt].col.a -= 0.05f;

			if (g_aFade_Menu[nCnt].col.a < 0.0f)
			{
				g_aFade_Menu[nCnt].col.a = 0.0f;
			}
		}
		else
		{
			g_aFade_Menu[nCnt].col.a += 0.1f;
		}

		pVtx_Fade_Menu[0].col = g_aFade_Menu[nCnt].col;
		pVtx_Fade_Menu[1].col = g_aFade_Menu[nCnt].col;
		pVtx_Fade_Menu[2].col = g_aFade_Menu[nCnt].col;
		pVtx_Fade_Menu[3].col = g_aFade_Menu[nCnt].col;

		pVtx_Fade_Menu += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Fade_Menu->Unlock();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Fade_Menu(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Fade_Menu, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_FADE_MENU; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Fade_Menu[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Fade_Menu(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FADE_MENU; nCnt++)
	{
		g_aFade_Menu[nCnt].nStyle = 0;
		g_aFade_Menu[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
		g_aFade_Menu[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFade_Menu[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFade_Menu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aFade_Menu[nCnt].fLength = sqrtf((990.0f * 990.0f) + (540.0f * 540.0f));
		g_aFade_Menu[nCnt].fAngle = atan2f(990.0f * 2.0f, 540.0f * 2.0f);
	}
}

//************************************************
//ポリゴン情報を送る関数
//************************************************
float* Getinfo_Fade_Menu(void)
{
	return &g_aFade_Menu[0].col.a;
}