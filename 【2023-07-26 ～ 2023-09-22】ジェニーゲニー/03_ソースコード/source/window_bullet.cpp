//************************************************
//
//弾ウィンドウ表示処理[window_bullet.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "window_bullet.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Window_Bullet = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Window_Bullet = NULL;	//頂点バッファのポインタ

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Window_Bullet()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WINDOW_BULLET,
		&g_pTexture_Window_Bullet);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Window_Bullet,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Window_Bullet;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Window_Bullet->Lock(0, 0, (void**)&pVtx_Window_Bullet, 0);

	//頂点座標の初期設定
	pVtx_Window_Bullet[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Bullet[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Bullet[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Bullet[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Window_Bullet[0].rhw = 1.0f;
	pVtx_Window_Bullet[1].rhw = 1.0f;
	pVtx_Window_Bullet[2].rhw = 1.0f;
	pVtx_Window_Bullet[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Window_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Window_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Window_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Window_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の初期設定
	pVtx_Window_Bullet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Window_Bullet[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Window_Bullet[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Window_Bullet[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Window_Bullet->Unlock();

	//初回に一度ポリゴンを展開する
	SetPos_Vtx_Window_Bullet();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Window_Bullet(void)
{
	//テクスチャの破棄
	if (g_pTexture_Window_Bullet != NULL)
	{
		g_pTexture_Window_Bullet->Release();
		g_pTexture_Window_Bullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Window_Bullet != NULL)
	{
		g_pVtxBuff_Window_Bullet->Release();
		g_pVtxBuff_Window_Bullet = NULL;
	}
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Window_Bullet(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Window_Bullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Window_Bullet);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//頂点を展開する関数
//************************************************
void SetPos_Vtx_Window_Bullet(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Window_Bullet;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Window_Bullet->Lock(0, 0, (void**)&pVtx_Window_Bullet, 0);

	pVtx_Window_Bullet[0].pos = D3DXVECTOR3(POS_X_LEFT_WINDOW_BULLET, POS_Y_UP_WINDOW_BULLET, 0.0f);
	pVtx_Window_Bullet[1].pos = D3DXVECTOR3(POS_X_RIGHT_WINDOW_BULLET, POS_Y_UP_WINDOW_BULLET, 0.0f);
	pVtx_Window_Bullet[2].pos = D3DXVECTOR3(POS_X_LEFT_WINDOW_BULLET, POS_Y_DOWN_WINDOW_BULLET, 0.0f);
	pVtx_Window_Bullet[3].pos = D3DXVECTOR3(POS_X_RIGHT_WINDOW_BULLET, POS_Y_DOWN_WINDOW_BULLET, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Window_Bullet->Unlock();
}