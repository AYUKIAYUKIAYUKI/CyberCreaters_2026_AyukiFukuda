//************************************************
//
//催促処理[press_any.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "press_any.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Press_Any[AMOUNT_TEX_PRESS_ANY] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Press_Any = NULL;	//頂点バッファのポインタ
PRESS_ANY g_aPress_Any;	//催促情報
static float g_F;	//汎用浮動小数

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Press_Any(int nMode)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PRESS_ANY_MENU,
		&g_pTexture_Press_Any[PRESS_TYPE_MENU]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PRESS_ANY_RESULT,
		&g_pTexture_Press_Any[PRESS_TYPE_RESULT]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Press_Any,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Press_Any;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Press_Any->Lock(0, 0, (void**)&pVtx_Press_Any, 0);

	//頂点座標の初期設定
	pVtx_Press_Any[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Press_Any[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Press_Any[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Press_Any[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Press_Any[0].rhw = 1.0f;
	pVtx_Press_Any[1].rhw = 1.0f;
	pVtx_Press_Any[2].rhw = 1.0f;
	pVtx_Press_Any[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Press_Any[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Press_Any[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Press_Any[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Press_Any[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の初期設定
	pVtx_Press_Any[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Press_Any[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Press_Any[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Press_Any[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Press_Any->Unlock();

	//背景構造体の情報の初期化群
	g_aPress_Any.nType = nMode;
	g_aPress_Any.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPress_Any.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPress_Any.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPress_Any.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aPress_Any.fRadius[nCnt] = 0.0f;
	}
	g_aPress_Any.fLength = 0.0f;
	g_aPress_Any.fAngle = 0.0f;

	g_F = 0.01f;

	//背景構造体に情報を付与
	SetInfo_Press_Any();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Press_Any(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEX_PRESS_ANY; nCnt++)
	{
		if (g_pTexture_Press_Any[nCnt] != NULL)
		{
			g_pTexture_Press_Any[nCnt]->Release();
			g_pTexture_Press_Any[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Press_Any != NULL)
	{
		g_pVtxBuff_Press_Any->Release();
		g_pVtxBuff_Press_Any = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Press_Any(void)
{
	//展開
	Update_Pos_Press_Any();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Press_Any(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Press_Any, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	switch (g_aPress_Any.nType)
	{
	case PRESS_TYPE_MENU:
		pDevice->SetTexture(0, g_pTexture_Press_Any[PRESS_TYPE_MENU]);
		break;
	case PRESS_TYPE_RESULT:
		pDevice->SetTexture(0, g_pTexture_Press_Any[PRESS_TYPE_RESULT]);
		break;
	}

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//催促構造体の情報を設定する関数
//************************************************
void SetInfo_Press_Any(void)
{
	g_aPress_Any.pos = D3DXVECTOR3(990.0f, 900.0f, 0.0f);
	g_aPress_Any.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPress_Any.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPress_Any.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aPress_Any.fRadius[0] = 400.0f;
	g_aPress_Any.fRadius[1] = 100.0f;
	g_aPress_Any.fLength = sqrtf((g_aPress_Any.fRadius[0] * g_aPress_Any.fRadius[0]) + (g_aPress_Any.fRadius[1] * g_aPress_Any.fRadius[1]));
	g_aPress_Any.fAngle = atan2f(g_aPress_Any.fRadius[0] * 2.0f, g_aPress_Any.fRadius[1] * 2.0f);
}

//************************************************
//催促の位置を設定する関数
//************************************************
void Update_Pos_Press_Any(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Press_Any;

	//色変更
	Update_Col_Press_Any();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Press_Any->Lock(0, 0, (void**)&pVtx_Press_Any, 0);

	pVtx_Press_Any[0].pos.x = g_aPress_Any.pos.x + sinf(g_aPress_Any.rot.z - (D3DX_PI - g_aPress_Any.fAngle)) * g_aPress_Any.fLength;
	pVtx_Press_Any[0].pos.y = g_aPress_Any.pos.y + cosf(g_aPress_Any.rot.z - (D3DX_PI - g_aPress_Any.fAngle)) * g_aPress_Any.fLength;
	pVtx_Press_Any[1].pos.x = g_aPress_Any.pos.x + sinf(g_aPress_Any.rot.z + (D3DX_PI - g_aPress_Any.fAngle)) * g_aPress_Any.fLength;
	pVtx_Press_Any[1].pos.y = g_aPress_Any.pos.y + cosf(g_aPress_Any.rot.z + (D3DX_PI - g_aPress_Any.fAngle)) * g_aPress_Any.fLength;
	pVtx_Press_Any[2].pos.x = g_aPress_Any.pos.x + sinf(g_aPress_Any.rot.z - g_aPress_Any.fAngle) * g_aPress_Any.fLength;
	pVtx_Press_Any[2].pos.y = g_aPress_Any.pos.y + cosf(g_aPress_Any.rot.z - g_aPress_Any.fAngle) * g_aPress_Any.fLength;
	pVtx_Press_Any[3].pos.x = g_aPress_Any.pos.x + sinf(g_aPress_Any.rot.z + g_aPress_Any.fAngle) * g_aPress_Any.fLength;
	pVtx_Press_Any[3].pos.y = g_aPress_Any.pos.y + cosf(g_aPress_Any.rot.z + g_aPress_Any.fAngle) * g_aPress_Any.fLength;

	//頂点バッファをアンロックする
	g_pVtxBuff_Press_Any->Unlock();
}

//************************************************
//催促の色を変更する関数
//************************************************
void Update_Col_Press_Any(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Press_Any;

	g_aPress_Any.col.a -= g_F;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Press_Any->Lock(0, 0, (void**)&pVtx_Press_Any, 0);

	pVtx_Press_Any[0].col = g_aPress_Any.col;
	pVtx_Press_Any[1].col = g_aPress_Any.col;
	pVtx_Press_Any[2].col = g_aPress_Any.col;
	pVtx_Press_Any[3].col = g_aPress_Any.col;

	//頂点バッファをアンロックする
	g_pVtxBuff_Press_Any->Unlock();

	//明滅
	if (g_aPress_Any.col.a < 0.0f || g_aPress_Any.col.a > 1.0f)
	{
		g_F *= -1.0f;
	}
}

//************************************************
//催促構造体のアドレスを渡す
//************************************************
PRESS_ANY* GetInfo_Press_Any(void)
{
	return &g_aPress_Any;
}