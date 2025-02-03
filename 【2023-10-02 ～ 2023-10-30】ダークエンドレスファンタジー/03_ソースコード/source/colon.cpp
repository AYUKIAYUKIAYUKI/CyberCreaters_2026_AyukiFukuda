//************************************************
//
//コロン処理[logo_title.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "colon.h"
#include "timer.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Colon = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Colon = NULL;	//頂点バッファのポインタ
COLON g_aColon;	//コロン情報

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Colon()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_COLON,
		&g_pTexture_Colon);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Colon,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Colon;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Colon->Lock(0, 0, (void**)&pVtx_Colon, 0);

	//頂点座標の初期設定
	pVtx_Colon[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Colon[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Colon[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Colon[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Colon[0].rhw = 1.0f;
	pVtx_Colon[1].rhw = 1.0f;
	pVtx_Colon[2].rhw = 1.0f;
	pVtx_Colon[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Colon[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Colon[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Colon[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Colon[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の初期設定
	pVtx_Colon[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Colon[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Colon[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Colon[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Colon->Unlock();

	//背景構造体の情報の初期化群
	g_aColon.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aColon.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aColon.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aColon.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aColon.fRadius[nCnt] = 0.0f;
	}
	g_aColon.fLength = 0.0f;
	g_aColon.fAngle = 0.0f;

	//背景構造体に情報を付与
	SetInfo_Colon();

	//位置に基づきポリゴンを展開
	Update_Pos_Colon();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Colon(void)
{
	//テクスチャの破棄
	if (g_pTexture_Colon != NULL)
	{
		g_pTexture_Colon->Release();
		g_pTexture_Colon = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Colon != NULL)
	{
		g_pVtxBuff_Colon->Release();
		g_pVtxBuff_Colon = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Colon(void)
{

}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Colon(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Colon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Colon);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//コロン構造体の情報を設定する関数
//************************************************
void SetInfo_Colon(void)
{
	TIMER* pTimer = GetInfo_TIMER();

	g_aColon.pos = pTimer[0].pos;
	g_aColon.pos.x += 100.0f;
	g_aColon.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aColon.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aColon.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aColon.fRadius[0] = 15.0f;
	g_aColon.fRadius[1] = 35.0f;
	g_aColon.fLength = sqrtf((g_aColon.fRadius[0] * g_aColon.fRadius[0]) + (g_aColon.fRadius[1] * g_aColon.fRadius[1]));
	g_aColon.fAngle = atan2f(g_aColon.fRadius[0] * 2.0f, g_aColon.fRadius[1] * 2.0f);
}

//************************************************
//コロンの位置を設定する関数
//************************************************
void Update_Pos_Colon(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Colon;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Colon->Lock(0, 0, (void**)&pVtx_Colon, 0);

	pVtx_Colon[0].pos.x = g_aColon.pos.x + sinf(g_aColon.rot.z - (D3DX_PI - g_aColon.fAngle)) * g_aColon.fLength;
	pVtx_Colon[0].pos.y = g_aColon.pos.y + cosf(g_aColon.rot.z - (D3DX_PI - g_aColon.fAngle)) * g_aColon.fLength;
	pVtx_Colon[1].pos.x = g_aColon.pos.x + sinf(g_aColon.rot.z + (D3DX_PI - g_aColon.fAngle)) * g_aColon.fLength;
	pVtx_Colon[1].pos.y = g_aColon.pos.y + cosf(g_aColon.rot.z + (D3DX_PI - g_aColon.fAngle)) * g_aColon.fLength;
	pVtx_Colon[2].pos.x = g_aColon.pos.x + sinf(g_aColon.rot.z - g_aColon.fAngle) * g_aColon.fLength;
	pVtx_Colon[2].pos.y = g_aColon.pos.y + cosf(g_aColon.rot.z - g_aColon.fAngle) * g_aColon.fLength;
	pVtx_Colon[3].pos.x = g_aColon.pos.x + sinf(g_aColon.rot.z + g_aColon.fAngle) * g_aColon.fLength;
	pVtx_Colon[3].pos.y = g_aColon.pos.y + cosf(g_aColon.rot.z + g_aColon.fAngle) * g_aColon.fLength;

	//頂点バッファをアンロックする
	g_pVtxBuff_Colon->Unlock();
}

//************************************************
//コロン構造体のアドレスを渡す
//************************************************
COLON* GetInfo_Colon(void)
{
	return &g_aColon;
}