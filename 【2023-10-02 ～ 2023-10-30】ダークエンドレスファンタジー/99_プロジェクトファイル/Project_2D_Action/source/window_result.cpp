//************************************************
//
//ウィンドウリザルト処理[window_menu.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "result.h"
#include "window_result.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Window_Result[AMOUNT_TEX_WINDOW_RESULT] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Window_Result = NULL;	//頂点バッファのポインタ
WINDOW_RESULT g_aWindow_Result;	//ウィンドウリザルト情報

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Window_Result()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WINDOW_RESULT1,
		&g_pTexture_Window_Result[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WINDOW_RESULT2
		,
		&g_pTexture_Window_Result[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Window_Result,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Window_Result;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Window_Result->Lock(0, 0, (void**)&pVtx_Window_Result, 0);

	//頂点座標の初期設定
	pVtx_Window_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Window_Result[0].rhw = 1.0f;
	pVtx_Window_Result[1].rhw = 1.0f;
	pVtx_Window_Result[2].rhw = 1.0f;
	pVtx_Window_Result[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Window_Result[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Window_Result[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Window_Result[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Window_Result[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の初期設定
	pVtx_Window_Result[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Window_Result[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Window_Result[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Window_Result[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Window_Result->Unlock();

	//ウィンドウリザルト構造体の情報の初期化群
	g_aWindow_Result.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Result.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Result.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Result.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aWindow_Result.fRadius[nCnt] = 0.0f;
		g_aWindow_Result.fLength[nCnt] = 0.0f;
		g_aWindow_Result.fAngle[nCnt] = 0.0f;
	}

	//ウィンドウリザルト構造体に情報を付与
	SetInfo_Window_Result();

	//位置に基づきポリゴンを展開
	Update_Pos_Window_Result();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Window_Result(void)
{
	//テクスチャの破棄
	for (int i = 0; i < AMOUNT_TEX_WINDOW_RESULT; i++)
	{
		if (g_pTexture_Window_Result[i] != NULL)
		{
			g_pTexture_Window_Result[i]->Release();
			g_pTexture_Window_Result[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Window_Result != NULL)
	{
		g_pVtxBuff_Window_Result->Release();
		g_pVtxBuff_Window_Result = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Window_Result(void)
{

}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Window_Result(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Window_Result, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	bool* pCLEAR = GetInfo_CLEAR();

	//テクスチャの設定
	if (*pCLEAR)
	{
		pDevice->SetTexture(0, g_pTexture_Window_Result[0]);
	}
	else
	{
		pDevice->SetTexture(0, g_pTexture_Window_Result[1]);
	}

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//ウィンドウリザルト構造体の情報を設定する関数
//************************************************
void SetInfo_Window_Result(void)
{
	g_aWindow_Result.pos = D3DXVECTOR3(990.0f, 290.0f, 0.0f);
	g_aWindow_Result.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Result.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Result.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aWindow_Result.fRadius[0] = RADIUS_WINDOW_RESULT_X;	//横半幅
	g_aWindow_Result.fRadius[1] = RADIUS_WINDOW_RESULT_Y;	//縦半幅
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aWindow_Result.fLength[nCnt] = sqrtf((g_aWindow_Result.fRadius[0] * g_aWindow_Result.fRadius[0]) + (g_aWindow_Result.fRadius[1] * g_aWindow_Result.fRadius[1]));
		g_aWindow_Result.fAngle[nCnt] = atan2f(g_aWindow_Result.fRadius[0] * 2.0f, g_aWindow_Result.fRadius[1] * 2.0f);
	}
}

//************************************************
//ウィンドウリザルトの位置を設定する関数
//************************************************
void Update_Pos_Window_Result(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Window_Result;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Window_Result->Lock(0, 0, (void**)&pVtx_Window_Result, 0);

	pVtx_Window_Result[0].pos.x = g_aWindow_Result.pos.x + sinf(g_aWindow_Result.rot.z - (D3DX_PI - g_aWindow_Result.fAngle[0])) * g_aWindow_Result.fLength[0];
	pVtx_Window_Result[0].pos.y = g_aWindow_Result.pos.y + cosf(g_aWindow_Result.rot.z - (D3DX_PI - g_aWindow_Result.fAngle[0])) * g_aWindow_Result.fLength[0];
	pVtx_Window_Result[1].pos.x = g_aWindow_Result.pos.x + sinf(g_aWindow_Result.rot.z + (D3DX_PI - g_aWindow_Result.fAngle[0])) * g_aWindow_Result.fLength[0];
	pVtx_Window_Result[1].pos.y = g_aWindow_Result.pos.y + cosf(g_aWindow_Result.rot.z + (D3DX_PI - g_aWindow_Result.fAngle[0])) * g_aWindow_Result.fLength[0];
	pVtx_Window_Result[2].pos.x = g_aWindow_Result.pos.x + sinf(g_aWindow_Result.rot.z - g_aWindow_Result.fAngle[0]) * g_aWindow_Result.fLength[0];
	pVtx_Window_Result[2].pos.y = g_aWindow_Result.pos.y + cosf(g_aWindow_Result.rot.z - g_aWindow_Result.fAngle[0]) * g_aWindow_Result.fLength[0];
	pVtx_Window_Result[3].pos.x = g_aWindow_Result.pos.x + sinf(g_aWindow_Result.rot.z + g_aWindow_Result.fAngle[0]) * g_aWindow_Result.fLength[0];
	pVtx_Window_Result[3].pos.y = g_aWindow_Result.pos.y + cosf(g_aWindow_Result.rot.z + g_aWindow_Result.fAngle[0]) * g_aWindow_Result.fLength[0];

	//頂点バッファをアンロックする
	g_pVtxBuff_Window_Result->Unlock();
}

//************************************************
//ウィンドウリザルト構造体のアドレスを渡す
//************************************************
WINDOW_RESULT* GetInfo_Window_Result(void)
{
	return &g_aWindow_Result;
}