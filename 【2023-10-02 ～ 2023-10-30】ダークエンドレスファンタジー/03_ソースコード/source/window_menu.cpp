//************************************************
//
//ウィンドウメニュー処理[window_menu.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "window_menu.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Window_Menu = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Window_Menu = NULL;	//頂点バッファのポインタ
WINDOW_MENU g_aWindow_Menu;	//ウィンドウメニュー情報

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Window_Menu()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WINDOW_MENU,
		&g_pTexture_Window_Menu);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Window_Menu,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Window_Menu;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Window_Menu->Lock(0, 0, (void**)&pVtx_Window_Menu, 0);

	//頂点座標の初期設定
	pVtx_Window_Menu[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Menu[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Menu[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Menu[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Window_Menu[0].rhw = 1.0f;
	pVtx_Window_Menu[1].rhw = 1.0f;
	pVtx_Window_Menu[2].rhw = 1.0f;
	pVtx_Window_Menu[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Window_Menu[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Window_Menu[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Window_Menu[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Window_Menu[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の初期設定
	pVtx_Window_Menu[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Window_Menu[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Window_Menu[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Window_Menu[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Window_Menu->Unlock();

	//ウィンドウメニュー構造体の情報の初期化群
	g_aWindow_Menu.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Menu.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Menu.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Menu.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aWindow_Menu.fRadius[nCnt] = 0.0f;
		g_aWindow_Menu.fLength[nCnt] = 0.0f;
		g_aWindow_Menu.fAngle[nCnt] = 0.0f;
	}

	//ウィンドウメニュー構造体に情報を付与
	SetInfo_Window_Menu();

	//位置に基づきポリゴンを展開
	Update_Pos_Window_Menu();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Window_Menu(void)
{
	//テクスチャの破棄
	if (g_pTexture_Window_Menu != NULL)
	{
		g_pTexture_Window_Menu->Release();
		g_pTexture_Window_Menu = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Window_Menu != NULL)
	{
		g_pVtxBuff_Window_Menu->Release();
		g_pVtxBuff_Window_Menu = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Window_Menu(void)
{

}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Window_Menu(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Window_Menu, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Window_Menu);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//ウィンドウメニュー構造体の情報を設定する関数
//************************************************
void SetInfo_Window_Menu(void)
{
	g_aWindow_Menu.pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
	g_aWindow_Menu.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Menu.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Menu.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aWindow_Menu.fRadius[0] = RADIUS_WINDOW_MENU_X;	//横半幅
	g_aWindow_Menu.fRadius[1] = RADIUS_WINDOW_MENU_Y;	//縦半幅
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aWindow_Menu.fLength[nCnt] = sqrtf((g_aWindow_Menu.fRadius[0] * g_aWindow_Menu.fRadius[0]) + (g_aWindow_Menu.fRadius[1] * g_aWindow_Menu.fRadius[1]));
		g_aWindow_Menu.fAngle[nCnt] = atan2f(g_aWindow_Menu.fRadius[0] * 2.0f, g_aWindow_Menu.fRadius[1] * 2.0f);
	}
}

//************************************************
//ウィンドウメニューの位置を設定する関数
//************************************************
void Update_Pos_Window_Menu(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Window_Menu;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Window_Menu->Lock(0, 0, (void**)&pVtx_Window_Menu, 0);

	pVtx_Window_Menu[0].pos.x = g_aWindow_Menu.pos.x + sinf(g_aWindow_Menu.rot.z - (D3DX_PI - g_aWindow_Menu.fAngle[0])) * g_aWindow_Menu.fLength[0];
	pVtx_Window_Menu[0].pos.y = g_aWindow_Menu.pos.y + cosf(g_aWindow_Menu.rot.z - (D3DX_PI - g_aWindow_Menu.fAngle[0])) * g_aWindow_Menu.fLength[0];
	pVtx_Window_Menu[1].pos.x = g_aWindow_Menu.pos.x + sinf(g_aWindow_Menu.rot.z + (D3DX_PI - g_aWindow_Menu.fAngle[0])) * g_aWindow_Menu.fLength[0];
	pVtx_Window_Menu[1].pos.y = g_aWindow_Menu.pos.y + cosf(g_aWindow_Menu.rot.z + (D3DX_PI - g_aWindow_Menu.fAngle[0])) * g_aWindow_Menu.fLength[0];
	pVtx_Window_Menu[2].pos.x = g_aWindow_Menu.pos.x + sinf(g_aWindow_Menu.rot.z - g_aWindow_Menu.fAngle[0]) * g_aWindow_Menu.fLength[0];
	pVtx_Window_Menu[2].pos.y = g_aWindow_Menu.pos.y + cosf(g_aWindow_Menu.rot.z - g_aWindow_Menu.fAngle[0]) * g_aWindow_Menu.fLength[0];
	pVtx_Window_Menu[3].pos.x = g_aWindow_Menu.pos.x + sinf(g_aWindow_Menu.rot.z + g_aWindow_Menu.fAngle[0]) * g_aWindow_Menu.fLength[0];
	pVtx_Window_Menu[3].pos.y = g_aWindow_Menu.pos.y + cosf(g_aWindow_Menu.rot.z + g_aWindow_Menu.fAngle[0]) * g_aWindow_Menu.fLength[0];

	//頂点バッファをアンロックする
	g_pVtxBuff_Window_Menu->Unlock();
}

//************************************************
//ウィンドウメニュー構造体のアドレスを渡す
//************************************************
WINDOW_MENU* GetInfo_Window_Menu(void)
{
	return &g_aWindow_Menu;
}