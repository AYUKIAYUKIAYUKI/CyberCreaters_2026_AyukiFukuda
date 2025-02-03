//************************************************
//
//ゲージ表示処理[guage.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "guage.h"
#include "player.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Guage = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Guage = NULL;	//頂点バッファのポインタ

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Guage()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GUAGE,
		&g_pTexture_Guage);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Guage,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Guage;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Guage->Lock(0, 0, (void**)&pVtx_Guage, 0);

	//頂点座標の初期設定
	pVtx_Guage[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Guage[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Guage[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Guage[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Guage[0].rhw = 1.0f;
	pVtx_Guage[1].rhw = 1.0f;
	pVtx_Guage[2].rhw = 1.0f;
	pVtx_Guage[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Guage[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Guage[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Guage[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Guage[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の初期設定
	pVtx_Guage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Guage[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Guage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Guage[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Guage->Unlock();

	//初回に一度ポリゴンを展開する
	SetPos_Vtx_Guage();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Guage(void)
{
	//テクスチャの破棄
	if (g_pTexture_Guage != NULL)
	{
		g_pTexture_Guage->Release();
		g_pTexture_Guage = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Guage != NULL)
	{
		g_pVtxBuff_Guage->Release();
		g_pVtxBuff_Guage = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Guage(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Guage;

	//プレイヤー情報へのポインタ
	PLAYER* pPlayer;

	//プレイヤー情報の取得
	pPlayer = Getinfo_Player();	//プレイヤー情報系の先頭アドレスが代入される

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Guage->Lock(0, 0, (void**)&pVtx_Guage, 0);

	//キャパ量当たりのゲージ減量を算出
	float fNowCapacityPolygon = (pPlayer->nCapacity - AMOUNT_CAPACITY_PLAYER) * DIVIDE_POLYGON_GUAGE;	//ポリゴンの長さ÷キャパの量＝係数
	float fNowCapacityTexture = (pPlayer->nCapacity - AMOUNT_CAPACITY_PLAYER) * DIVIDE_TEXTURE_GUAGE;	//テクスチャの長さ÷キャパの量＝係数

	//ポリゴン伸縮
	pVtx_Guage[0].pos = D3DXVECTOR3(POS_X_LEFT_GUAGE, POS_Y_UP_GUAGE, 0.0f);
	pVtx_Guage[1].pos = D3DXVECTOR3(POS_X_RIGHT_GUAGE + fNowCapacityPolygon, POS_Y_UP_GUAGE, 0.0f);
	pVtx_Guage[2].pos = D3DXVECTOR3(POS_X_LEFT_GUAGE, POS_Y_DOWN_GUAGE, 0.0f);
	pVtx_Guage[3].pos = D3DXVECTOR3(POS_X_RIGHT_GUAGE + fNowCapacityPolygon, POS_Y_DOWN_GUAGE, 0.0f);

	//テクスチャ伸縮
	pVtx_Guage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Guage[1].tex = D3DXVECTOR2(1.0f + fNowCapacityTexture, 0.0f);
	pVtx_Guage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Guage[3].tex = D3DXVECTOR2(1.0f + fNowCapacityTexture, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Guage->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Guage(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Guage, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Guage);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//頂点を展開する関数
//************************************************
void SetPos_Vtx_Guage(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Guage;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Guage->Lock(0, 0, (void**)&pVtx_Guage, 0);

	pVtx_Guage[0].pos = D3DXVECTOR3(POS_X_LEFT_GUAGE, POS_Y_UP_GUAGE, 0.0f);
	pVtx_Guage[1].pos = D3DXVECTOR3(POS_X_RIGHT_GUAGE, POS_Y_UP_GUAGE, 0.0f);
	pVtx_Guage[2].pos = D3DXVECTOR3(POS_X_LEFT_GUAGE, POS_Y_DOWN_GUAGE, 0.0f);
	pVtx_Guage[3].pos = D3DXVECTOR3(POS_X_RIGHT_GUAGE, POS_Y_DOWN_GUAGE, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Guage->Unlock();
}