//************************************************
//
//タイトルテキスト処理[text_title.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "text_title.h"
#include "title.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Text_Title[AMOUNT_TEX_TEXT_TITLE] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Text_Title = NULL;	//頂点バッファのポインタ
TEXT_TITLE g_aText_Title[AMOUNT_POLYGON_TEXT_TITLE];	//タイトルテキスト情報

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Text_Title()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_TITLE_1,
		&g_pTexture_Text_Title[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_TITLE_2,
		&g_pTexture_Text_Title[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_TITLE_3,
		&g_pTexture_Text_Title[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TEXT_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Text_Title,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Text_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Text_Title->Lock(0, 0, (void**)&pVtx_Text_Title, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_TITLE; i++)
	{
		//頂点座標の初期設定
		pVtx_Text_Title[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Title[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Title[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Title[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Text_Title[0].rhw = 1.0f;
		pVtx_Text_Title[1].rhw = 1.0f;
		pVtx_Text_Title[2].rhw = 1.0f;
		pVtx_Text_Title[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Text_Title[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Title[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Title[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Title[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx_Text_Title[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Text_Title[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Text_Title[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Text_Title[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Text_Title += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Text_Title->Unlock();

	//背景構造体の情報の初期化群
	for (int i = 0; i < AMOUNT_POLYGON_TEXT_TITLE; i++)
	{
		g_aText_Title[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Title[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Title[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Title[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aText_Title[i].fRadius[nCnt] = 0.0f;
		}
		g_aText_Title[i].fLength = 0.0f;
		g_aText_Title[i].fAngle = 0.0f;
	}

	//背景構造体に情報を付与
	SetInfo_Text_Title();

	//位置に基づきポリゴンを展開
	Update_Pos_Text_Title();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Text_Title(void)
{
	//テクスチャの破棄
	for (int i = 0; i < AMOUNT_TEX_TEXT_TITLE; i++)
	{
		if (g_pTexture_Text_Title[i] != NULL)
		{
			g_pTexture_Text_Title[i]->Release();
			g_pTexture_Text_Title[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Text_Title != NULL)
	{
		g_pVtxBuff_Text_Title->Release();
		g_pVtxBuff_Text_Title = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Text_Title(void)
{
	Update_Col_Text_Title();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Text_Title(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Text_Title, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_TITLE; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexture_Text_Title[i]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//タイトルテキスト構造体の情報を設定する関数
//************************************************
void SetInfo_Text_Title(void)
{
	for (int i = 0; i < AMOUNT_POLYGON_TEXT_TITLE; i++)
	{
		g_aText_Title[i].pos = D3DXVECTOR3(990.0f, 600.0f + (i * 150.0f), 0.0f);
		g_aText_Title[i].fRadius[0] = RADIUS_TEXT_TITLE_X;	//背景横半幅
		g_aText_Title[i].fRadius[1] = RADIUS_TEXT_TITLE_Y;	//背景縦半幅
		g_aText_Title[i].fLength = sqrtf((g_aText_Title[i].fRadius[0] * g_aText_Title[i].fRadius[0]) + (g_aText_Title[i].fRadius[1] * g_aText_Title[i].fRadius[1]));
		g_aText_Title[i].fAngle = atan2f(g_aText_Title[i].fRadius[0] * 2.0f, g_aText_Title[i].fRadius[1] * 2.0f);
	}
}

//************************************************
//タイトルテキストの位置を設定する関数
//************************************************
void Update_Pos_Text_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Text_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Text_Title->Lock(0, 0, (void**)&pVtx_Text_Title, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_TITLE; i++)
	{
		pVtx_Text_Title[0].pos.x = g_aText_Title[i].pos.x + sinf(g_aText_Title[i].rot.z - (D3DX_PI - g_aText_Title[i].fAngle)) * g_aText_Title[i].fLength;
		pVtx_Text_Title[0].pos.y = g_aText_Title[i].pos.y + cosf(g_aText_Title[i].rot.z - (D3DX_PI - g_aText_Title[i].fAngle)) * g_aText_Title[i].fLength;
		pVtx_Text_Title[1].pos.x = g_aText_Title[i].pos.x + sinf(g_aText_Title[i].rot.z + (D3DX_PI - g_aText_Title[i].fAngle)) * g_aText_Title[i].fLength;
		pVtx_Text_Title[1].pos.y = g_aText_Title[i].pos.y + cosf(g_aText_Title[i].rot.z + (D3DX_PI - g_aText_Title[i].fAngle)) * g_aText_Title[i].fLength;
		pVtx_Text_Title[2].pos.x = g_aText_Title[i].pos.x + sinf(g_aText_Title[i].rot.z - g_aText_Title[i].fAngle) * g_aText_Title[i].fLength;
		pVtx_Text_Title[2].pos.y = g_aText_Title[i].pos.y + cosf(g_aText_Title[i].rot.z - g_aText_Title[i].fAngle) * g_aText_Title[i].fLength;
		pVtx_Text_Title[3].pos.x = g_aText_Title[i].pos.x + sinf(g_aText_Title[i].rot.z + g_aText_Title[i].fAngle) * g_aText_Title[i].fLength;
		pVtx_Text_Title[3].pos.y = g_aText_Title[i].pos.y + cosf(g_aText_Title[i].rot.z + g_aText_Title[i].fAngle) * g_aText_Title[i].fLength;

		pVtx_Text_Title += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Text_Title->Unlock();
}

//************************************************
//テキストの色を変更する関数
//************************************************
void Update_Col_Text_Title(void)
{
	int* pChoose = Getinfo_Choose_Title_Menu();

	//選んでるものの色を変更する形式
	for (int i = 0; i < AMOUNT_POLYGON_TEXT_TITLE; i++)
	{
		if (i != *pChoose)
		{
			g_aText_Title[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		}
		else
		{
			g_aText_Title[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Text_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Text_Title->Lock(0, 0, (void**)&pVtx_Text_Title, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_TITLE; i++)
	{
		pVtx_Text_Title[0].col = g_aText_Title[i].col;
		pVtx_Text_Title[1].col = g_aText_Title[i].col;
		pVtx_Text_Title[2].col = g_aText_Title[i].col;
		pVtx_Text_Title[3].col = g_aText_Title[i].col;

		pVtx_Text_Title += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Text_Title->Unlock();
}

//************************************************
//タイトルテキスト構造体のアドレスを渡す
//************************************************
TEXT_TITLE* GetInfo_Text_Title(void)
{
	return &g_aText_Title[0];
}