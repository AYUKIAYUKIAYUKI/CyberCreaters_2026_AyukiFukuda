//************************************************
//
//ライフ表記(int nLifeとかいう謎の引数要修正)[life.cpp]
//Author：福田歩希
//
//************************************************
#include "input.h"
#include "main.h"
#include "sound.h"
#include "life.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Life = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Life = NULL;	//頂点バッファのポインタ
float g_fTexU_Life = 0.0f;				//ライフテクスチャ用
float g_fTexV_Life = TEX_V_DOWN_LIFE;	//同上

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Life(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_HEARTS_LIFE,
		&g_pTexture_Life);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Life,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Life;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Life->Lock(0, 0, (void**)&pVtx_Life, 0);

	//頂点座標の初期設定
	pVtx_Life[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Life[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Life[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Life[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	//視錐台の拡大率(?)の初期設定
	pVtx_Life[0].rhw = 1.0f;
	pVtx_Life[1].rhw = 1.0f;
	pVtx_Life[2].rhw = 1.0f;
	pVtx_Life[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Life[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Life[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Life[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Life[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の初期設定
	pVtx_Life[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Life[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Life[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Life[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Life->Unlock();

	//ライフテクスチャ用変数初期化
	g_fTexU_Life = 0.0f;
	g_fTexV_Life = TEX_V_DOWN_LIFE;

	//初回に一度ポリゴンを展開する
	SetPos_Vtx_Life();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Life(void)
{
	//テクスチャの破棄
	if (g_pTexture_Life != NULL)
	{
		g_pTexture_Life->Release();
		g_pTexture_Life = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Life != NULL)
	{
		g_pVtxBuff_Life->Release();
		g_pVtxBuff_Life = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数(被弾や回復時)
//************************************************
void Update_Life(int nLife)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Life;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Life->Lock(0, 0, (void**)&pVtx_Life, 0);

	//ライフ数に合わせてテクスチャ変化
	switch (nLife)
	{
	case AMOUNT_LIFE_0:

		g_fTexU_Life = MOVE_SPAN_TEX_LIFE * 5;
		g_fTexV_Life = MOVE_SPAN_TEX_LIFE * 5 + TEX_V_DOWN_LIFE;

		break;

	case AMOUNT_LIFE_1:

		g_fTexU_Life = MOVE_SPAN_TEX_LIFE * 4;
		g_fTexV_Life = MOVE_SPAN_TEX_LIFE * 4 + TEX_V_DOWN_LIFE;

		break;

	case AMOUNT_LIFE_2:

		g_fTexU_Life = MOVE_SPAN_TEX_LIFE * 3;
		g_fTexV_Life = MOVE_SPAN_TEX_LIFE * 3 + TEX_V_DOWN_LIFE;

		break;

	case AMOUNT_LIFE_3:

		g_fTexU_Life = MOVE_SPAN_TEX_LIFE * 2;
		g_fTexV_Life = MOVE_SPAN_TEX_LIFE * 2 + TEX_V_DOWN_LIFE;

		break;

	case AMOUNT_LIFE_4:

		g_fTexU_Life = MOVE_SPAN_TEX_LIFE;
		g_fTexV_Life = MOVE_SPAN_TEX_LIFE + TEX_V_DOWN_LIFE;

		break;

	case AMOUNT_LIFE_MAX:

		g_fTexU_Life = 0.0f;
		g_fTexV_Life = TEX_V_DOWN_LIFE;

		break;
	}

	//テクスチャ座標の設定
	pVtx_Life[0].tex = D3DXVECTOR2(0.0f, g_fTexU_Life);
	pVtx_Life[1].tex = D3DXVECTOR2(1.0f, g_fTexU_Life);
	pVtx_Life[2].tex = D3DXVECTOR2(0.0f, g_fTexV_Life);
	pVtx_Life[3].tex = D3DXVECTOR2(1.0f, g_fTexV_Life);

	//頂点バッファをアンロックする
	g_pVtxBuff_Life->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Life(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Life, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Life);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//頂点を展開する関数
//************************************************
void SetPos_Vtx_Life(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Life;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Life->Lock(0, 0, (void**)&pVtx_Life, 0);

	pVtx_Life[0].pos = D3DXVECTOR3(POS_X_LEFT_LIFE, POS_Y_UP_LIFE, 0.0f);
	pVtx_Life[1].pos = D3DXVECTOR3(POS_X_RIGHT_LIFE, POS_Y_UP_LIFE, 0.0f);
	pVtx_Life[2].pos = D3DXVECTOR3(POS_X_LEFT_LIFE, POS_Y_DOWN_LIFE, 0.0f);
	pVtx_Life[3].pos = D3DXVECTOR3(POS_X_RIGHT_LIFE, POS_Y_DOWN_LIFE, 0.0f);

	pVtx_Life[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx_Life[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx_Life[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx_Life[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);

	pVtx_Life[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Life[1].tex = D3DXVECTOR2(TEX_U_RIGHT_LIFE, 0.0f);
	pVtx_Life[2].tex = D3DXVECTOR2(0.0f, TEX_V_DOWN_LIFE);
	pVtx_Life[3].tex = D3DXVECTOR2(TEX_U_RIGHT_LIFE, TEX_V_DOWN_LIFE);

	//頂点バッファをアンロックする
	g_pVtxBuff_Life->Unlock();
}