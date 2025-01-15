//************************************************
//
//UIの後ろの処理[back.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "back.h"
#include "score.h"
#include "timer.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Back = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Back = NULL;	//頂点バッファのポインタ
BACK g_aBack[AMOUNT_POLYGON_BACK];	//UIの後ろの情報

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Back()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BACK,
		&g_pTexture_Back);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BACK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Back,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Back;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Back->Lock(0, 0, (void**)&pVtx_Back, 0);

	for (int i = 0; i < AMOUNT_POLYGON_BACK; i++)
	{
		//頂点座標の初期設定
		pVtx_Back[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Back[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Back[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Back[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Back[0].rhw = 1.0f;
		pVtx_Back[1].rhw = 1.0f;
		pVtx_Back[2].rhw = 1.0f;
		pVtx_Back[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Back[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		pVtx_Back[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		pVtx_Back[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		pVtx_Back[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);

		//テクスチャ座標の初期設定
		pVtx_Back[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Back[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Back[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Back[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Back += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Back->Unlock();

	//UIの後ろの構造体の情報の初期化群
	for (int i = 0; i < AMOUNT_POLYGON_BACK; i++)
	{
		g_aBack[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBack[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBack[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBack[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aBack[i].fRadius[nCnt] = 0.0f;
		}
		g_aBack[i].fLength = 0.0f;
		g_aBack[i].fAngle = 0.0f;
	}

	//UIの後ろの構造体に情報を付与
	SetInfo_Back();

	//展開
	Update_Pos_Back();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Back(void)
{
	//テクスチャの破棄
	if (g_pTexture_Back != NULL)
	{
		g_pTexture_Back->Release();
		g_pTexture_Back = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Back != NULL)
	{
		g_pVtxBuff_Back->Release();
		g_pVtxBuff_Back = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Back(void)
{

}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Back(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Back, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int i = 0; i < AMOUNT_POLYGON_BACK; i++)
	{
		pDevice->SetTexture(0, g_pTexture_Back);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//UIの後ろの構造体の情報を設定する関数
//************************************************
void SetInfo_Back(void)
{
	SCORE* pScore = GetInfo_SCORE();
	TIMER* pTimer = GetInfo_TIMER();

	for (int i = 0; i < AMOUNT_POLYGON_BACK; i++)
	{
		switch (i)
		{
		case 0:
			g_aBack[i].pos = pScore[0].pos;
			g_aBack[i].fRadius[0] = 430.0f;
			break;
		case 1:
			g_aBack[i].pos = pTimer[0].pos;
			g_aBack[i].fRadius[0] = 240.0f;
			break;
		}
		g_aBack[i].fRadius[1] = 55.0f;
	}
}

//************************************************
//UIの後ろのの位置を設定する関数
//************************************************
void Update_Pos_Back(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Back;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Back->Lock(0, 0, (void**)&pVtx_Back, 0);

	for (int i = 0; i < AMOUNT_POLYGON_BACK; i++)
	{
		pVtx_Back[0].pos.x = g_aBack[i].pos.x - 40.0f;
		pVtx_Back[0].pos.y = g_aBack[i].pos.y - g_aBack[i].fRadius[1];
		pVtx_Back[1].pos.x = g_aBack[i].pos.x + g_aBack[i].fRadius[0] + 15.0f;
		pVtx_Back[1].pos.y = g_aBack[i].pos.y - g_aBack[i].fRadius[1];
		pVtx_Back[2].pos.x = g_aBack[i].pos.x - 55.0f;
		pVtx_Back[2].pos.y = g_aBack[i].pos.y + g_aBack[i].fRadius[1];
		pVtx_Back[3].pos.x = g_aBack[i].pos.x + g_aBack[i].fRadius[0];
		pVtx_Back[3].pos.y = g_aBack[i].pos.y + g_aBack[i].fRadius[1];

		pVtx_Back += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Back->Unlock();
}

//************************************************
//UIの後ろのの構造体のアドレスを渡す
//************************************************
BACK* GetInfo_Back(void)
{
	return &g_aBack[0];
}