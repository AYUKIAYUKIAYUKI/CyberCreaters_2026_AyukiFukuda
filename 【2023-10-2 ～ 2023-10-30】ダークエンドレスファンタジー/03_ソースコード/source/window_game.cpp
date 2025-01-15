//************************************************
//
//ポーズウィンドウ処理[window_game.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "window_game.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Window_Game[AMOUNT_TEX_WINDOW_GAME] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Window_Game = NULL;	//頂点バッファのポインタ
WINDOW_GAME g_aWindow_Game[AMOUNT_POLYGON_WINDOW_GAME];	//ポーズウィンドウ情報

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Window_Game(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WHTITE_PAUSE,
		&g_pTexture_Window_Game[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WINDOW_GAME,
		&g_pTexture_Window_Game[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_PAUSE,
		&g_pTexture_Window_Game[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_WINDOW_GAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Window_Game,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Window_Game;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Window_Game->Lock(0, 0, (void**)&pVtx_Window_Game, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_WINDOW_GAME; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Window_Game[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Window_Game[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Window_Game[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Window_Game[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Window_Game[0].rhw = 1.0f;
		pVtx_Window_Game[1].rhw = 1.0f;
		pVtx_Window_Game[2].rhw = 1.0f;
		pVtx_Window_Game[3].rhw = 1.0f;

		switch (nCnt)
		{
		case 0:
			pVtx_Window_Game[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			pVtx_Window_Game[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			pVtx_Window_Game[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			pVtx_Window_Game[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			break;
		default:
			pVtx_Window_Game[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx_Window_Game[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx_Window_Game[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx_Window_Game[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		//テクスチャ座標の初期設定
		pVtx_Window_Game[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Window_Game[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Window_Game[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Window_Game[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Window_Game += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Window_Game->Unlock();

	//ポーズウィンドウ構造体の情報の初期化群
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_WINDOW_GAME; nCnt++)
	{
		g_aWindow_Game[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWindow_Game[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWindow_Game[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWindow_Game[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aWindow_Game[nCnt].fRadius[nCnt2] = 0.0f;
		}
		g_aWindow_Game[nCnt].fLength = 0.0f;
		g_aWindow_Game[nCnt].fAngle = 0.0f;
	}

	//ポーズウィンドウ構造体に情報を付与
	SetInfo_Window_Game();

	//位置に基づきポリゴンを展開
	Update_Pos_Window_Game();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Window_Game(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEX_WINDOW_GAME; nCnt++)
	{
		if (g_pTexture_Window_Game[nCnt] != NULL)
		{
			g_pTexture_Window_Game[nCnt]->Release();
			g_pTexture_Window_Game[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Window_Game != NULL)
	{
		g_pVtxBuff_Window_Game->Release();
		g_pVtxBuff_Window_Game = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Window_Game(void)
{

}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Window_Game(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Window_Game, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_WINDOW_GAME; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Window_Game[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポーズウィンドウ構造体の情報を設定する関数
//************************************************
void SetInfo_Window_Game(void)
{
	int nCntLayer = 0;
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_WINDOW_GAME; nCnt++)
	{
		g_aWindow_Game[nCnt].pos = D3DXVECTOR3(SCREEN_HALFWIDTH, SCREEN_HALFHEIGHT, 0.0f);
		switch (nCnt)
		{
		case 0:
			g_aWindow_Game[nCnt].fRadius[0] = SCREEN_HALFWIDTH;	//ポーズウィンドウ横半幅
			g_aWindow_Game[nCnt].fRadius[1] = SCREEN_HALFHEIGHT;	//ポーズウィンドウ縦半幅
			break;
		case 1:
			g_aWindow_Game[nCnt].fRadius[0] = 600.0f;
			g_aWindow_Game[nCnt].fRadius[1] = 500.0f;
			break;
		case 2:
			g_aWindow_Game[nCnt].pos = D3DXVECTOR3(SCREEN_HALFWIDTH, 250.0f, 0.0f);
			g_aWindow_Game[nCnt].fRadius[0] = RADIUS_TEXT_PAUSE_X;
			g_aWindow_Game[nCnt].fRadius[1] = RADIUS_TEXT_PAUSE_Y;
			break;
		}
		g_aWindow_Game[nCnt].fLength = sqrtf((g_aWindow_Game[nCnt].fRadius[0] * g_aWindow_Game[nCnt].fRadius[0]) + (g_aWindow_Game[nCnt].fRadius[1] * g_aWindow_Game[nCnt].fRadius[1]));
		g_aWindow_Game[nCnt].fAngle = atan2f(g_aWindow_Game[nCnt].fRadius[0] * 2.0f, g_aWindow_Game[nCnt].fRadius[1] * 2.0f);
	}
}

//************************************************
//ポーズウィンドウの位置を設定する関数
//************************************************
void Update_Pos_Window_Game(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Window_Game;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Window_Game->Lock(0, 0, (void**)&pVtx_Window_Game, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_WINDOW_GAME; nCnt++)
	{
		//クモは動く
		g_aWindow_Game[nCnt].pos += g_aWindow_Game[nCnt].move;

		pVtx_Window_Game[0].pos.x = g_aWindow_Game[nCnt].pos.x + sinf(g_aWindow_Game[nCnt].rot.z - (D3DX_PI - g_aWindow_Game[nCnt].fAngle)) * g_aWindow_Game[nCnt].fLength;
		pVtx_Window_Game[0].pos.y = g_aWindow_Game[nCnt].pos.y + cosf(g_aWindow_Game[nCnt].rot.z - (D3DX_PI - g_aWindow_Game[nCnt].fAngle)) * g_aWindow_Game[nCnt].fLength;
		pVtx_Window_Game[1].pos.x = g_aWindow_Game[nCnt].pos.x + sinf(g_aWindow_Game[nCnt].rot.z + (D3DX_PI - g_aWindow_Game[nCnt].fAngle)) * g_aWindow_Game[nCnt].fLength;
		pVtx_Window_Game[1].pos.y = g_aWindow_Game[nCnt].pos.y + cosf(g_aWindow_Game[nCnt].rot.z + (D3DX_PI - g_aWindow_Game[nCnt].fAngle)) * g_aWindow_Game[nCnt].fLength;
		pVtx_Window_Game[2].pos.x = g_aWindow_Game[nCnt].pos.x + sinf(g_aWindow_Game[nCnt].rot.z - g_aWindow_Game[nCnt].fAngle) * g_aWindow_Game[nCnt].fLength;
		pVtx_Window_Game[2].pos.y = g_aWindow_Game[nCnt].pos.y + cosf(g_aWindow_Game[nCnt].rot.z - g_aWindow_Game[nCnt].fAngle) * g_aWindow_Game[nCnt].fLength;
		pVtx_Window_Game[3].pos.x = g_aWindow_Game[nCnt].pos.x + sinf(g_aWindow_Game[nCnt].rot.z + g_aWindow_Game[nCnt].fAngle) * g_aWindow_Game[nCnt].fLength;
		pVtx_Window_Game[3].pos.y = g_aWindow_Game[nCnt].pos.y + cosf(g_aWindow_Game[nCnt].rot.z + g_aWindow_Game[nCnt].fAngle) * g_aWindow_Game[nCnt].fLength;

		pVtx_Window_Game += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Window_Game->Unlock();
}

//************************************************
//ポーズウィンドウ構造体のアドレスを渡す
//************************************************
WINDOW_GAME* GetInfo_Window_Game(void)
{
	return &g_aWindow_Game[0];
}