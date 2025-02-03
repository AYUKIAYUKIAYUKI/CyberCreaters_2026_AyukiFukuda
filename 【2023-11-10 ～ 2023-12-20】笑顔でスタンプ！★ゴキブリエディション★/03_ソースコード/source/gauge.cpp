//************************************************
//
//ゲージ[gauge.cpp]
//Author：福田歩希
//
//************************************************
#include "gauge.h"

#include "debugproc.h"
#include "fade.h"
#include "input.h"

#include "player.h"

//ゲージ用
typedef enum
{
	TexGauge00 = 0,
	TexGaugeFrame00,
	TexRoachJet,
	TexGauge01,
	TexGaugeFrame01,
	TexEnegy,
	TexMax,
}TexType;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureGauge[TexMax] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;	//頂点バッファのポインタ
Gauge g_aGauge[TexMax];	//情報

//************************************************
//ゲージ初期
//************************************************
void InitGauge(void)
{
	//構造体の情報の初期化群
	for (int i = 0; i < TexMax; i++)
	{
		g_aGauge[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aGauge[i].sizeX = 0.0f;
		g_aGauge[i].sizeY = 0.0f;
		g_aGauge[i].F = 1.0f;	//汎用
	}

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	const char* pFileName[TexMax] =
	{
		"data\\texture\\gauge_00.png",
		"data\\texture\\guage_frame.png",
		"data\\texture\\roach_JET.png",
		"data\\texture\\gauge_01.png",
		"data\\texture\\guage_frame.png",
		"data\\texture\\enegy.png",
	};

	for (int i = 0; i < TexMax; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureGauge[i]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * TexMax,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGauge,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++)
	{
		//頂点座標の初期設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffGauge->Unlock();

	//情報を付与
	SetInfoGauge();

	//展開
	SetSizeGauge();
}

//************************************************
//ゲージ終了処理関数
//************************************************
void UninitGauge(void)
{
	//テクスチャの破棄
	for (int i = 0; i < TexMax; i++)
	{
		if (g_pTextureGauge[i] != NULL)
		{
			g_pTextureGauge[i]->Release();
			g_pTextureGauge[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}
}

//************************************************
//ゲージ更新
//************************************************
void UpdateGauge(void)
{
	//展開
	SetSizeGauge();

	//色変更
	//UpdateColGauge();
}

//************************************************
//ゲージ展開
//************************************************
void SetSizeGauge(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	Player* pPlayer = GetInfoPlayer();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		//頂点座標の設定
		pVtx[0].pos =
		{
			g_aGauge[i].pos.x - g_aGauge[i].sizeX,
			g_aGauge[i].pos.y - g_aGauge[i].sizeY,
			0.0f
		};

		pVtx[1].pos =
		{
			g_aGauge[i].pos.x + g_aGauge[i].sizeX,
			g_aGauge[i].pos.y - g_aGauge[i].sizeY,
			0.0f
		};

		pVtx[2].pos =
		{
			g_aGauge[i].pos.x - g_aGauge[i].sizeX,
			g_aGauge[i].pos.y + g_aGauge[i].sizeY,
			0.0f
		};

		pVtx[3].pos =
		{
			g_aGauge[i].pos.x + g_aGauge[i].sizeX,
			g_aGauge[i].pos.y + g_aGauge[i].sizeY,
			0.0f
		};
	
		if (i == TexGauge00)
		{
			//キャパ量当たりのゲージ減量を算出(クソ)
			if (pPlayer->nCapacity > AMOUNT_CAPACITY)
			{
				pPlayer->nCapacity = AMOUNT_CAPACITY;
			}

			float fNowCapacityPolygon = (pPlayer->nCapacity - AMOUNT_CAPACITY) * ((g_aGauge[i].sizeX * 2.0f) / AMOUNT_CAPACITY);	//ポリゴンの長さ÷キャパの量＝係数
			float fNowCapacityTexture = (pPlayer->nCapacity - AMOUNT_CAPACITY) * (1.0f / AMOUNT_CAPACITY);	//テクスチャの長さ÷キャパの量＝係数

			//ポリゴン伸縮
			pVtx[0].pos.x = g_aGauge[i].pos.x - g_aGauge[i].sizeX;
			pVtx[1].pos.x = g_aGauge[i].pos.x + g_aGauge[i].sizeX + fNowCapacityPolygon;
			pVtx[2].pos.x = g_aGauge[i].pos.x - g_aGauge[i].sizeX;
			pVtx[3].pos.x = g_aGauge[i].pos.x + g_aGauge[i].sizeX + fNowCapacityPolygon;

			//テクスチャ伸縮
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f + fNowCapacityTexture, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f + fNowCapacityTexture, 1.0f);
		}

		if (i == TexGauge01)
		{
			//キャパ量当たりのゲージ減量を算出(クソ)
			if (pPlayer->nEnegy > AMOUNT_ENEGY)
			{
				pPlayer->nEnegy = AMOUNT_ENEGY;
			}

			float fNowCapacityPolygon = (pPlayer->nEnegy - AMOUNT_ENEGY) * ((g_aGauge[i].sizeX * 2.0f) / AMOUNT_ENEGY);	//ポリゴンの長さ÷キャパの量＝係数
			float fNowCapacityTexture = (pPlayer->nEnegy - AMOUNT_ENEGY) * (1.0f / AMOUNT_ENEGY);	//テクスチャの長さ÷キャパの量＝係数

			//ポリゴン伸縮
			pVtx[0].pos.x = g_aGauge[i].pos.x - g_aGauge[i].sizeX;
			pVtx[1].pos.x = g_aGauge[i].pos.x + g_aGauge[i].sizeX + fNowCapacityPolygon;
			pVtx[2].pos.x = g_aGauge[i].pos.x - g_aGauge[i].sizeX;
			pVtx[3].pos.x = g_aGauge[i].pos.x + g_aGauge[i].sizeX + fNowCapacityPolygon;

			//テクスチャ伸縮
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f + fNowCapacityTexture, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f + fNowCapacityTexture, 1.0f);
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffGauge->Unlock();
}

//************************************************
//ゲージ色変更
//************************************************
void UpdateColGauge(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		//特になし
		pVtx[0].col = g_aGauge[i].col;
		pVtx[1].col = g_aGauge[i].col;
		pVtx[2].col = g_aGauge[i].col;
		pVtx[3].col = g_aGauge[i].col;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffGauge->Unlock();
}

//************************************************
//ゲージ描画
//************************************************
void DrawGauge(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TexMax; i++)
	{
		pDevice->SetTexture(0, g_pTextureGauge[i]);

		//ゲージの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//構造体の情報を設定する関数
//************************************************
void SetInfoGauge(void)
{
	for (int i = 0; i < TexMax; i++)
	{
		g_aGauge[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aGauge[i].F = 1.0f;	//汎用

		if (i == TexGauge00 || i == TexGaugeFrame00)
		{
			g_aGauge[i].pos = D3DXVECTOR3(1100.0f, 75.0f, 0.0f);
			g_aGauge[i].sizeX = 250.0f;
			g_aGauge[i].sizeY = 30.0f;
		}
		else if (i == TexRoachJet)
		{
			g_aGauge[i].pos = D3DXVECTOR3(g_aGauge[TexGauge00].pos.x - g_aGauge[TexGauge00].sizeX, g_aGauge[TexGauge00].pos.y - 5.0f, 0.0f);
			g_aGauge[i].sizeX = 18.0f;
			g_aGauge[i].sizeY = 56.25f;
		}
		else if (i == TexGauge01 || i == TexGaugeFrame01)
		{
			g_aGauge[i].pos = D3DXVECTOR3(1700.0f, 75.0f, 0.0f);
			g_aGauge[i].sizeX = 250.0f;
			g_aGauge[i].sizeY = 30.0f;
		}
		else if (i == TexEnegy)
		{
			g_aGauge[i].pos = D3DXVECTOR3(g_aGauge[TexGauge01].pos.x - g_aGauge[TexGauge01].sizeX - 15.0f, g_aGauge[TexGauge01].pos.y - 5.0f, 0.0f);
			g_aGauge[i].sizeX = 50.0f;
			g_aGauge[i].sizeY = 50.0f;
		}
	}
}
