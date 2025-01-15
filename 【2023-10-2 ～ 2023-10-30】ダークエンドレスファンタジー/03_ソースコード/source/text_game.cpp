//************************************************
//
//ポーズテキスト処理[text_game.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "text_game.h"
#include "game.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Text_Game[AMOUNT_TEX_TEXT_GAME] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Text_Game = NULL;	//頂点バッファのポインタ
TEXT_GAME g_aText_Game[AMOUNT_POLYGON_TEXT_GAME];	//ポーズテキスト情報

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Text_Game()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_GAME_1,
		&g_pTexture_Text_Game[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_GAME_2,
		&g_pTexture_Text_Game[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_GAME_3,
		&g_pTexture_Text_Game[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TEXT_GAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Text_Game,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Text_Game;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Text_Game->Lock(0, 0, (void**)&pVtx_Text_Game, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_GAME; i++)
	{
		//頂点座標の初期設定
		pVtx_Text_Game[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Game[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Game[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Game[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Text_Game[0].rhw = 1.0f;
		pVtx_Text_Game[1].rhw = 1.0f;
		pVtx_Text_Game[2].rhw = 1.0f;
		pVtx_Text_Game[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Text_Game[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Game[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Game[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Game[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx_Text_Game[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Text_Game[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Text_Game[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Text_Game[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Text_Game += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Text_Game->Unlock();

	//背景構造体の情報の初期化群
	for (int i = 0; i < AMOUNT_POLYGON_TEXT_GAME; i++)
	{
		g_aText_Game[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Game[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Game[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Game[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aText_Game[i].fRadius[nCnt] = 0.0f;
		}
		g_aText_Game[i].fLength = 0.0f;
		g_aText_Game[i].fAngle = 0.0f;
	}

	//背景構造体に情報を付与
	SetInfo_Text_Game();

	//位置に基づきポリゴンを展開
	Update_Pos_Text_Game();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Text_Game(void)
{
	//テクスチャの破棄
	for (int i = 0; i < AMOUNT_TEX_TEXT_GAME; i++)
	{
		if (g_pTexture_Text_Game[i] != NULL)
		{
			g_pTexture_Text_Game[i]->Release();
			g_pTexture_Text_Game[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Text_Game != NULL)
	{
		g_pVtxBuff_Text_Game->Release();
		g_pVtxBuff_Text_Game = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Text_Game(void)
{
	Update_Col_Text_Game();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Text_Game(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Text_Game, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_GAME; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexture_Text_Game[i]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポーズテキスト構造体の情報を設定する関数
//************************************************
void SetInfo_Text_Game(void)
{
	for (int i = 0; i < AMOUNT_POLYGON_TEXT_GAME; i++)
	{
		g_aText_Game[i].pos = D3DXVECTOR3(990.0f, 500.0f + (i * 150.0f), 0.0f);
		g_aText_Game[i].fRadius[0] = RADIUS_TEXT_GAME_X;	//背景横半幅
		g_aText_Game[i].fRadius[1] = RADIUS_TEXT_GAME_Y;	//背景縦半幅
		g_aText_Game[i].fLength = sqrtf((g_aText_Game[i].fRadius[0] * g_aText_Game[i].fRadius[0]) + (g_aText_Game[i].fRadius[1] * g_aText_Game[i].fRadius[1]));
		g_aText_Game[i].fAngle = atan2f(g_aText_Game[i].fRadius[0] * 2.0f, g_aText_Game[i].fRadius[1] * 2.0f);
	}
}

//************************************************
//ポーズテキストの位置を設定する関数
//************************************************
void Update_Pos_Text_Game(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Text_Game;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Text_Game->Lock(0, 0, (void**)&pVtx_Text_Game, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_GAME; i++)
	{
		pVtx_Text_Game[0].pos.x = g_aText_Game[i].pos.x + sinf(g_aText_Game[i].rot.z - (D3DX_PI - g_aText_Game[i].fAngle)) * g_aText_Game[i].fLength;
		pVtx_Text_Game[0].pos.y = g_aText_Game[i].pos.y + cosf(g_aText_Game[i].rot.z - (D3DX_PI - g_aText_Game[i].fAngle)) * g_aText_Game[i].fLength;
		pVtx_Text_Game[1].pos.x = g_aText_Game[i].pos.x + sinf(g_aText_Game[i].rot.z + (D3DX_PI - g_aText_Game[i].fAngle)) * g_aText_Game[i].fLength;
		pVtx_Text_Game[1].pos.y = g_aText_Game[i].pos.y + cosf(g_aText_Game[i].rot.z + (D3DX_PI - g_aText_Game[i].fAngle)) * g_aText_Game[i].fLength;
		pVtx_Text_Game[2].pos.x = g_aText_Game[i].pos.x + sinf(g_aText_Game[i].rot.z - g_aText_Game[i].fAngle) * g_aText_Game[i].fLength;
		pVtx_Text_Game[2].pos.y = g_aText_Game[i].pos.y + cosf(g_aText_Game[i].rot.z - g_aText_Game[i].fAngle) * g_aText_Game[i].fLength;
		pVtx_Text_Game[3].pos.x = g_aText_Game[i].pos.x + sinf(g_aText_Game[i].rot.z + g_aText_Game[i].fAngle) * g_aText_Game[i].fLength;
		pVtx_Text_Game[3].pos.y = g_aText_Game[i].pos.y + cosf(g_aText_Game[i].rot.z + g_aText_Game[i].fAngle) * g_aText_Game[i].fLength;

		pVtx_Text_Game += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Text_Game->Unlock();
}

//************************************************
//テキストの色を変更する関数
//************************************************
void Update_Col_Text_Game(void)
{
	int* pChoose = Getinfo_Choose_Pause_Menu();

	//選んでるものの色を変更する形式
	for (int i = 0; i < AMOUNT_POLYGON_TEXT_GAME; i++)
	{
		if (i != *pChoose)
		{
			g_aText_Game[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		}
		else
		{
			g_aText_Game[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Text_Game;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Text_Game->Lock(0, 0, (void**)&pVtx_Text_Game, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_GAME; i++)
	{
		pVtx_Text_Game[0].col = g_aText_Game[i].col;
		pVtx_Text_Game[1].col = g_aText_Game[i].col;
		pVtx_Text_Game[2].col = g_aText_Game[i].col;
		pVtx_Text_Game[3].col = g_aText_Game[i].col;

		pVtx_Text_Game += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Text_Game->Unlock();
}

//************************************************
//ポーズテキスト構造体のアドレスを渡す
//************************************************
TEXT_GAME* GetInfo_Text_Game(void)
{
	return &g_aText_Game[0];
}