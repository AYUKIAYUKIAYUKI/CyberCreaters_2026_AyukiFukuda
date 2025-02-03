//=========================================================
//tmt[pause.cpp]
//Author:Yumika Matsushita
//=========================================================

//=====================================
//インクルード
//=====================================
#include "main.h"	//Windowsアプリケーション内の宣言の複合体
#include "game.h"	
#include "input.h"	//キーボードの宣言の複合体
#include "Pause.h"	//ゲーム画面の宣言の複合体
#include "player.h"
#include "player_count.h"
#include "debugproc.h"
#include "fade.h"
#include "sound.h"
//#include "fade.h"

//=====================================
//マクロ定義
//=====================================
#define MAX_POLYGON			(3)			//ポリゴンの最大数
#define MAX_PL				(4)			//プレイヤーの最大人数
#define Brightness_POLYGON	(51)		//ポリゴンの明るさ
#define POLYGON_COL			(100)		//ポリゴンの不透明度(100)
#define POLYGON_MAXCOL		(255)		//ポリゴンの不透明度(255)
#define MA_WIDTH			(50.0f)		//矢印のポリゴンの横の長さ
#define MA_HEIGHT			(100.0f)	//矢印のポリゴンの縦の長さ
#define MD_WIDTH			(300.0f)	//選択出来るやつのポリゴンの横の長さ
#define MD_HEIGHT			(200.0f)	//選択出来るやつのポリゴンの縦の長さ
#define OI_WIDTH			(400.0f)	//操作方法のポリゴンの縦の長さ
#define OI_HEIGHT			(700.0f)	//操作方法のポリゴンの横の長さ

//=====================================
//グローバル変数
//=====================================

//背景(BackGround == BG)
LPDIRECT3DTEXTURE9	g_pTexturePauseBG = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPauseBG = NULL;		//頂点バッファへのポインタ

//操作方法(OI == OperationInstructions)
LPDIRECT3DTEXTURE9	g_pTexturePauseOI = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPauseOI = NULL;		//頂点バッファへのポインタ
PauseOI g_pauseOI;										//操作方法のポリゴンの構造体

//矢印(MA == MovingArrow)
LPDIRECT3DTEXTURE9	g_pTexturePauseMA = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPauseMA = NULL;		//頂点バッファへのポインタ
PauseMA g_pauseMA[MAX_POLYGON];							//矢印ポリゴンの構造体
int g_nCntChooseMA = 0;									//矢印のポリゴンを光らせる為のカウント
int g_Time = 0;											//矢印のポリゴンをずらしていくためのカウント
bool bg_MA = false;										//矢印のポリゴンを揺らすためのフラグ

//選択できるやつ(MD == mode)
LPDIRECT3DTEXTURE9	g_pTexturePauseMD[MAX_POLYGON] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffPauseMD = NULL;			//頂点バッファへのポインタ
PauseMD g_pauseMD[MAX_POLYGON];								//Pause(選択できるやつ)のポリゴンの構造体
int g_nCntChooseMD = 0;										//選択されたポリゴンを光らせる為のカウント

int g_nJoinedPlayer = 0;									// 参加人数

//=====================================
// ポーズ画面の初期化処理
//=====================================
void InitPause(void)
{
	//プレイ人数の取得
	g_nJoinedPlayer = ReturnSelectPlayerCount() + 1;

	InitPauseBackGroundPolygon();				// ポーズ画面の背景画像

	InitPauseOperationInstructionsPolygon();	// 画面右の操作方法の画像

	InitPauseModePolygon();						// ポーズ画面からどこに飛ぶかの画像

	InitPauseMovingArrowPolygon();				// カーソルを移動させたときの矢印の画像

}

//=====================================
// ポーズ画面の終了処理
//=====================================
void UninitPause(void)
{
	UninitPauseBackGroundPolygon();				// ポーズ画面の背景画像

	UninitPauseOperationInstructionsPolygon();	// 画面右の操作方法の画像

	UninitPauseModePolygon();					// ポーズ画面からどこに飛ぶかの画像

	UninitPauseMovingArrowPolygon();			// カーソルを移動させたときの矢印の画像
}

//=====================================
// ポーズ画面の更新処理
//=====================================
void UpdatePause(void)
{
	UpdatePauseBackGroundPolygon();				// ポーズ画面の背景画像

	UpdatePauseOperationInstructionsPolygon();	// 画面右の操作方法の画像

	UpdatePauseModePolygon();					// ポーズ画面からどこに飛ぶかの画像

	UpdatePauseMovingArrowPolygon();			// カーソルを移動させたときの矢印の画像

	SelectMode();								// ポーズ画面中のモード選択
}

//=====================================
// ポーズ画面の描画処理
//=====================================
void DrawPause(void)
{
	DrawPauseBackGroundPolygon();				// ポーズ画面の背景画像

	DrawPauseOperationInstructionsPolygon();	// 画面右の操作方法の画像

	DrawPauseModePolygon();						// ポーズ画面からどこに飛ぶかの画像

	DrawPauseMovingArrowPolygon();				// カーソルを移動させたときの矢印の画像
}
//=====================================
//背景のポリゴン初期化処理
//=====================================
void InitPauseBackGroundPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause.png",
		&g_pTexturePauseBG);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseBG,
		NULL);

	VERTEX_2D* pVtx;									//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseBG->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 120);
	pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 120);
	pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 120);
	pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 120);

	//テスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPauseBG->Unlock();

}

//=====================================
//操作方法のポリゴン初期化処理
//=====================================
void InitPauseOperationInstructionsPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得

	g_pauseOI.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_pauseOI.bUse = false;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause_menu.png",
		&g_pTexturePauseOI);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseOI,
		NULL);

	VERTEX_2D* pVtx;									//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseOI->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
	pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
	pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
	pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);

	//テスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//操作方法のポリゴン設置
	SetPauseOperationInstructions(D3DXVECTOR3(1400.0f, 200.0f, 0.0f));

	//頂点バッファをアンロックする
	g_pVtxBuffPauseOI->Unlock();
}

//=====================================
//モード選択のポリゴン初期化処理
//=====================================
void InitPauseModePolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pauseMD[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_pauseMD[nCntPause].nType = 0;
		g_pauseMD[nCntPause].bUse = false;
		g_pauseMD[nCntPause].bColUse = false;
	}

	g_nCntChooseMD = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\retry.png",
		&g_pTexturePauseMD[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\continue.png",
		&g_pTexturePauseMD[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\end.png",
		&g_pTexturePauseMD[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseMD,
		NULL);

	VERTEX_2D* pVtx;									//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseMD->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
		pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
		pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
		pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);

		//テスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//配置しているとこ
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		SetPauseMode(D3DXVECTOR3((SCREEN_WIDTH / 3), (nCntPause * 300.0f) + 150.0f, 0.0f));
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPauseMD->Unlock();
}

//=====================================
//動く矢印のポリゴン初期化処理
//=====================================
void InitPauseMovingArrowPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();			//デバイスの取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pause_select.png",
		&g_pTexturePauseMA);

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pauseMA[nCntPause].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_pauseMA[nCntPause].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_pauseMA[nCntPause].nType = 0;
		g_pauseMA[nCntPause].bUse = false;
		g_pauseMA[nCntPause].bColUse = false;
	}

	g_nCntChooseMA = 0;
	g_Time = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseMA,
		NULL);

	VERTEX_2D* pVtx;									//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseMA->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
		pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
		pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
		pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);

		//テスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//配置しているとこ
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		SetPauseMovingArrow(D3DXVECTOR3((SCREEN_WIDTH / 7), (nCntPause * 300.0f) + 210.0f, 0.0f));
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPauseMA->Unlock();
}

//=====================================
//背景のポリゴンの終了処理
//=====================================
void UninitPauseBackGroundPolygon(void)
{
	//テクスチャの破棄
	if (g_pTexturePauseBG != NULL)
	{
		g_pTexturePauseBG->Release();
		g_pTexturePauseBG = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPauseBG != NULL)
	{
		g_pVtxBuffPauseBG->Release();
		g_pVtxBuffPauseBG = NULL;
	}
}

//=====================================
//操作方法のポリゴンの終了処理
//=====================================
void UninitPauseOperationInstructionsPolygon(void)
{
	//テクスチャの破棄
	if (g_pTexturePauseOI != NULL)
	{
		g_pTexturePauseOI->Release();
		g_pTexturePauseOI = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPauseOI != NULL)
	{
		g_pVtxBuffPauseOI->Release();
		g_pVtxBuffPauseOI = NULL;
	}
}

//=====================================
//モード選択のポリゴンの終了処理
//=====================================
void UninitPauseModePolygon(void)
{
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//テクスチャの破棄
		if (g_pTexturePauseMD[nCntPause] != NULL)
		{
			g_pTexturePauseMD[nCntPause]->Release();
			g_pTexturePauseMD[nCntPause] = NULL;
		}

		//頂点バッファの破棄
		if (g_pVtxBuffPauseMD != NULL)
		{
			g_pVtxBuffPauseMD->Release();
			g_pVtxBuffPauseMD = NULL;
		}

	}

}

//=====================================
//動く矢印の終了処理
//=====================================
void UninitPauseMovingArrowPolygon(void)
{
	//テクスチャの破棄
	if (g_pTexturePauseMA != NULL)
	{
		g_pTexturePauseMA->Release();
		g_pTexturePauseMA = NULL;
	}


	//頂点バッファの破棄
	if (g_pVtxBuffPauseMA != NULL)
	{
		g_pVtxBuffPauseMA->Release();
		g_pVtxBuffPauseMA = NULL;
	}
}

//=====================================
//背景のポリゴン更新処理(空)
//=====================================
void UpdatePauseBackGroundPolygon(void)
{

}

//=====================================
//操作方法のポリゴン更新処理(空)
//=====================================
void UpdatePauseOperationInstructionsPolygon(void)
{

}

//=====================================
//モード選択のポリゴン更新処理
//=====================================
void UpdatePauseModePolygon(void)
{
	VERTEX_2D* pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseMD->Lock(0, 0, (void**)&pVtx, 0);

	//選択出来るポリゴンの構造体のフラグを全てfalseにする
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pauseMD[nCntPause].bColUse = false;
	}
	//選ばれたカウントの値のフラグをtrueにする
	g_pauseMD[g_nCntChooseMD].bColUse = true;		//選択出来るポリゴン

	//選択できるポリゴンの数分回してます
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//もし選ばれたポリゴンのフラグがfalseの場合
		if (g_pauseMD[nCntPause].bColUse == false)
		{//不透明度を低くする
			//頂点カラーの設定(false時)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_COL);
		}

		//もし選ばれたポリゴンのフラグがtrueの場合
		if (g_pauseMD[nCntPause].bColUse == true)
		{//不透明度を高くする
			//頂点カラーの設定(true時)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
		}

		pVtx += 4;			
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPauseMD->Unlock();
}

//=====================================
//動く矢印のポリゴン更新処理
//=====================================
void UpdatePauseMovingArrowPolygon(void)
{
	VERTEX_2D* pVtx;		//頂点情報へのポインタ

	g_Time++;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseMA->Lock(0, 0, (void**)&pVtx, 0);

	//矢印のポリゴンの構造体のフラグをfalseにする
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		g_pauseMA[nCntPause].bColUse = false;
	}

	//選ばれたカウントの値のフラグをtrueにする
	g_pauseMA[g_nCntChooseMA].bColUse = true;		//矢印のポリゴン

	//矢印のポリゴンの数分回してます
	for (int nCntPauseSL = 0; nCntPauseSL < MAX_POLYGON; nCntPauseSL++)
	{
		//もし選ばれたポリゴンのフラグがfalseの場合
		if (g_pauseMA[nCntPauseSL].bColUse == false)
		{//不透明度を低くする
			//頂点カラーの設定(false時)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 0);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 0);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 0);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, 0);
		}

		//もし選ばれたポリゴンのフラグがtrueの場合
		if (g_pauseMA[nCntPauseSL].bColUse == true)
		{//不透明度を高くする
			//頂点カラーの設定(true時)
			pVtx[0].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[1].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[2].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
			pVtx[3].col = D3DCOLOR_RGBA(POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL, POLYGON_MAXCOL);
		}

		if (g_Time % 60 == 0)
		{
			bg_MA = bg_MA ? false : true;
		}

		if (bg_MA == true)
		{
			g_pauseMA[nCntPauseSL].move.x = 1.0f;
		}
		if (bg_MA == false)
		{
			g_pauseMA[nCntPauseSL].move.x = -1.0f;
		}

		g_pauseMA[nCntPauseSL].pos += g_pauseMA[nCntPauseSL].move;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_pauseMA[nCntPauseSL].pos.x - MA_WIDTH, g_pauseMA[nCntPauseSL].pos.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_pauseMA[nCntPauseSL].pos.x + MA_WIDTH, g_pauseMA[nCntPauseSL].pos.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_pauseMA[nCntPauseSL].pos.x - MA_WIDTH, g_pauseMA[nCntPauseSL].pos.y + MA_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_pauseMA[nCntPauseSL].pos.x + MA_WIDTH, g_pauseMA[nCntPauseSL].pos.y + MA_HEIGHT, 0.0f);


		pVtx += 4;			//いつもの
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPauseMA->Unlock();
}

//=====================================
//背景のポリゴンの描画処理
//=====================================
void DrawPauseBackGroundPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスへのポインタ

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseBG);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================
//操作方法のポリゴンの描画処理
//=====================================
void DrawPauseOperationInstructionsPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスへのポインタ

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseOI, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseOI);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================
//モード選択のポリゴンの描画処理
//=====================================
void DrawPauseModePolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスへのポインタ

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMD, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//選択できるポリゴンの最大数分回してます
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePauseMD[nCntPause]);		//テクスチャ三個分あります

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);		//ポリゴン三つ分あります
	}
}

//=====================================
//動く矢印のポリゴンの描画処理
//=====================================
void DrawPauseMovingArrowPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスへのポインタ

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMA, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//選択できるポリゴンの最大数分回してます
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePauseMA);		//テクスチャ1個分あります

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);		//ポリゴン三つ分あります
	}
}

//=====================================
//モード選択のポリゴンの設定処理
//=====================================
void SetPauseMode(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseMD->Lock(0, 0, (void**)&pVtx, 0);

	//選択できるポリゴンの最大数分回してます
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		if (g_pauseMD[nCntPause].bUse == false)
		{
			g_pauseMD[nCntPause].pos = pos;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_pauseMD[nCntPause].pos.x - MD_WIDTH, g_pauseMD[nCntPause].pos.y - 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_pauseMD[nCntPause].pos.x + MD_WIDTH, g_pauseMD[nCntPause].pos.y - 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_pauseMD[nCntPause].pos.x - MD_WIDTH, g_pauseMD[nCntPause].pos.y + MD_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_pauseMD[nCntPause].pos.x + MD_WIDTH, g_pauseMD[nCntPause].pos.y + MD_HEIGHT, 0.0f);

			g_pauseMD[nCntPause].bUse = true;
			g_pauseMD[nCntPause].bColUse = false;

			break;
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPauseMD->Unlock();
}

//=====================================
//操作方法のポリゴンの設定処理
//=====================================
void SetPauseOperationInstructions(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseOI->Lock(0, 0, (void**)&pVtx, 0);

	if (g_pauseOI.bUse == false)
	{
		g_pauseOI.pos = pos;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_pauseOI.pos.x - OI_WIDTH, g_pauseOI.pos.y - 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_pauseOI.pos.x + OI_WIDTH, g_pauseOI.pos.y - 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_pauseOI.pos.x - OI_WIDTH, g_pauseOI.pos.y + OI_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_pauseOI.pos.x + OI_WIDTH, g_pauseOI.pos.y + OI_HEIGHT, 0.0f);

		g_pauseOI.bUse = true;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPauseOI->Unlock();
}

//=====================================
//動く矢印のポリゴンの設定処理
//=====================================
void SetPauseMovingArrow(D3DXVECTOR3 pos)
{
	VERTEX_2D* pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseMA->Lock(0, 0, (void**)&pVtx, 0);

	//選択できるポリゴンの最大数分回してます
	for (int nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++, pVtx += 4)
	{
		if (g_pauseMA[nCntPause].bUse == false)
		{
			g_pauseMA[nCntPause].pos = pos;
			g_pauseMA[nCntPause].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_pauseMA[nCntPause].pos.x - MA_WIDTH, g_pauseMA[nCntPause].pos.y - 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_pauseMA[nCntPause].pos.x + MA_WIDTH, g_pauseMA[nCntPause].pos.y - 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_pauseMA[nCntPause].pos.x - MA_WIDTH, g_pauseMA[nCntPause].pos.y + MA_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_pauseMA[nCntPause].pos.x + MA_WIDTH, g_pauseMA[nCntPause].pos.y + MA_HEIGHT, 0.0f);

			g_pauseMA[nCntPause].bUse = true;
			g_pauseMA[nCntPause].bColUse = false;

			break;
		}

	}

	//頂点バッファをアンロックする
	g_pVtxBuffPauseMA->Unlock();
}

//=====================================
// ポーズ画面中のモード選択
//=====================================
void SelectMode(void)
{
	//↑キー押されたら
	if (GetKeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP, 0) == true)
	{
		PlaySound(SOUND_LABEL_CURSORMOVE);
		g_nCntChooseMD--;		//カウントをマイナスする(上に進む)
		g_nCntChooseMA--;	//上記と同じ(こちらは矢印のもの)
	}

	//↓キー押されたら
	if (GetKeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN, 0) == true)
	{
		PlaySound(SOUND_LABEL_CURSORMOVE);
		g_nCntChooseMD++;		//カウントをプラスする(下に進む)
		g_nCntChooseMA++;	//上記と同じ(こちらは矢印のもの)
	}

	//もしカウントが使用されているポリゴン数よりもマイナス値になってしまった時
	if (g_nCntChooseMD < PAUSEMODE_RETRY)
	{
		g_nCntChooseMD = PAUSEMODE_QUIT;	//強制的にカウントを2にする(retryからendにとばす)
		g_nCntChooseMA = PAUSEMODE_QUIT;	//上記と同じ(こちらは矢印のもの)
	}

	//もしカウントが使用されているポリゴン数よりもプラス値になってしまった時
	if (g_nCntChooseMD > PAUSEMODE_QUIT)
	{
		g_nCntChooseMD = PAUSEMODE_RETRY;	//強制的にカウントを0にする(endからretryにとばす)
		g_nCntChooseMA = PAUSEMODE_RETRY;	//上記と同じ(こちらは矢印のもの)
	}


	for (int nCntPlayer = 0; nCntPlayer < g_nJoinedPlayer; nCntPlayer++)	//タイトルで選択した参加人数を返したのをMAX_PLのとこにいれてください
	{
		if (GetJoypadTrigger(JOYKEY_A, nCntPlayer) || GetKeyboardPress(DIK_RETURN))
		{// Aボタンを押したとき
			PlaySound(SOUND_LABEL_CLICK);

			if (g_pauseMD[TEXTYPE_RETRY].bColUse == true)
			{// 選択したものがRETRYならゲームを最初からにする
				//フェードアウト処理
				SetFade(FADE_OUT, MODE_GAME);//二つ目に移行先
			}
			if (g_pauseMD[TEXTYPE_CONTINUE].bColUse == true)
			{// 選択したものがCONTINUEならポーズ状態を解除する
				SetEnablePause(false);
			}
			if (g_pauseMD[TEXTYPE_QUIT].bColUse == true)
			{// 選択したものがQUITならタイトル画面に戻る
				//フェードアウト処理
				SetFade(FADE_OUT, MODE_TITLE);//二つ目に移行先
			}

		}

	}



}

