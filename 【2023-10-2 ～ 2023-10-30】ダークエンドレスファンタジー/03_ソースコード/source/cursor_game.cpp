//************************************************
//
//ポーズカーソル処理[cursor_game.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "cursor_game.h"
#include "text_game.h"
#include "game.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Cursor_Game = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Cursor_Game = NULL;	//頂点バッファのポインタ
CURSOR_GAME g_aCursor_Game;	//ポーズカーソル情報

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Cursor_Game()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CURSOR_GAME_1,
		&g_pTexture_Cursor_Game);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Cursor_Game,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Cursor_Game;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Cursor_Game->Lock(0, 0, (void**)&pVtx_Cursor_Game, 0);

	//頂点座標の初期設定
	pVtx_Cursor_Game[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Cursor_Game[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Cursor_Game[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Cursor_Game[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Cursor_Game[0].rhw = 1.0f;
	pVtx_Cursor_Game[1].rhw = 1.0f;
	pVtx_Cursor_Game[2].rhw = 1.0f;
	pVtx_Cursor_Game[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Cursor_Game[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Cursor_Game[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Cursor_Game[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Cursor_Game[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の初期設定
	pVtx_Cursor_Game[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Cursor_Game[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Cursor_Game[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Cursor_Game[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Cursor_Game->Unlock();

	//背景構造体の情報の初期化群
	g_aCursor_Game.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCursor_Game.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCursor_Game.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCursor_Game.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aCursor_Game.fRadius[nCnt] = 0.0f;
	}
	g_aCursor_Game.fLength = 0.0f;
	g_aCursor_Game.fAngle = 0.0f;

	//背景構造体に情報を付与
	SetInfo_Cursor_Game();

	//位置に基づきポリゴンを展開
	Update_Pos_Cursor_Game();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Cursor_Game(void)
{
	//テクスチャの破棄
	if (g_pTexture_Cursor_Game != NULL)
	{
		g_pTexture_Cursor_Game->Release();
		g_pTexture_Cursor_Game = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Cursor_Game != NULL)
	{
		g_pVtxBuff_Cursor_Game->Release();
		g_pVtxBuff_Cursor_Game = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Cursor_Game(void)
{
	int* pChoose = Getinfo_Choose_Pause_Menu();
	TEXT_GAME* pText_Game = GetInfo_Text_Game();

	g_aCursor_Game.pos.y = pText_Game[*pChoose].pos.y;

	Update_Pos_Cursor_Game();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Cursor_Game(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Cursor_Game, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Cursor_Game);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//ポーズカーソル構造体の情報を設定する関数
//************************************************
void SetInfo_Cursor_Game(void)
{
	TEXT_GAME* pText_Game = GetInfo_Text_Game();

	g_aCursor_Game.pos.x = 650.0f;
	g_aCursor_Game.pos.y = pText_Game[CONTINUE].pos.y;
	g_aCursor_Game.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCursor_Game.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCursor_Game.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aCursor_Game.fRadius[0] = RADIUS_CURSOR_GAME_X;	//背景横半幅
	g_aCursor_Game.fRadius[1] = RADIUS_CURSOR_GAME_Y;	//背景縦半幅
	g_aCursor_Game.fLength = sqrtf((g_aCursor_Game.fRadius[0] * g_aCursor_Game.fRadius[0]) + (g_aCursor_Game.fRadius[1] * g_aCursor_Game.fRadius[1]));
	g_aCursor_Game.fAngle = atan2f(g_aCursor_Game.fRadius[0] * 2.0f, g_aCursor_Game.fRadius[1] * 2.0f);
}

//************************************************
//ポーズカーソルの位置を設定する関数
//************************************************
void Update_Pos_Cursor_Game(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Cursor_Game;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Cursor_Game->Lock(0, 0, (void**)&pVtx_Cursor_Game, 0);

	pVtx_Cursor_Game[0].pos.x = g_aCursor_Game.pos.x + sinf(g_aCursor_Game.rot.z - (D3DX_PI - g_aCursor_Game.fAngle)) * g_aCursor_Game.fLength;
	pVtx_Cursor_Game[0].pos.y = g_aCursor_Game.pos.y + cosf(g_aCursor_Game.rot.z - (D3DX_PI - g_aCursor_Game.fAngle)) * g_aCursor_Game.fLength;
	pVtx_Cursor_Game[1].pos.x = g_aCursor_Game.pos.x + sinf(g_aCursor_Game.rot.z + (D3DX_PI - g_aCursor_Game.fAngle)) * g_aCursor_Game.fLength;
	pVtx_Cursor_Game[1].pos.y = g_aCursor_Game.pos.y + cosf(g_aCursor_Game.rot.z + (D3DX_PI - g_aCursor_Game.fAngle)) * g_aCursor_Game.fLength;
	pVtx_Cursor_Game[2].pos.x = g_aCursor_Game.pos.x + sinf(g_aCursor_Game.rot.z - g_aCursor_Game.fAngle) * g_aCursor_Game.fLength;
	pVtx_Cursor_Game[2].pos.y = g_aCursor_Game.pos.y + cosf(g_aCursor_Game.rot.z - g_aCursor_Game.fAngle) * g_aCursor_Game.fLength;
	pVtx_Cursor_Game[3].pos.x = g_aCursor_Game.pos.x + sinf(g_aCursor_Game.rot.z + g_aCursor_Game.fAngle) * g_aCursor_Game.fLength;
	pVtx_Cursor_Game[3].pos.y = g_aCursor_Game.pos.y + cosf(g_aCursor_Game.rot.z + g_aCursor_Game.fAngle) * g_aCursor_Game.fLength;

	//頂点バッファをアンロックする
	g_pVtxBuff_Cursor_Game->Unlock();
}

//************************************************
//ポーズカーソル構造体のアドレスを渡す
//************************************************
CURSOR_GAME* GetInfo_Cursor_Game(void)
{
	return &g_aCursor_Game;
}