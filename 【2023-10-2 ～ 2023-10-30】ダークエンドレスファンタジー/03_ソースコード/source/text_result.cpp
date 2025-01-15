//************************************************
//
//リザルトテキスト処理[logo_title.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "score.h"
#include "text_result.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Text_Result = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Text_Result = NULL;	//頂点バッファのポインタ
TEXT_RESULT g_aText_Result;	//リザルトテキスト情報

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Text_Result()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_RESULT,
		&g_pTexture_Text_Result);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Text_Result,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Text_Result;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Text_Result->Lock(0, 0, (void**)&pVtx_Text_Result, 0);

	//頂点座標の初期設定
	pVtx_Text_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Text_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Text_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Text_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Text_Result[0].rhw = 1.0f;
	pVtx_Text_Result[1].rhw = 1.0f;
	pVtx_Text_Result[2].rhw = 1.0f;
	pVtx_Text_Result[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Text_Result[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Text_Result[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Text_Result[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Text_Result[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の初期設定
	pVtx_Text_Result[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Text_Result[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Text_Result[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Text_Result[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Text_Result->Unlock();

	//背景構造体の情報の初期化群
	g_aText_Result.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aText_Result.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aText_Result.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aText_Result.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aText_Result.fRadius[nCnt] = 0.0f;
	}
	g_aText_Result.fLength = 0.0f;
	g_aText_Result.fAngle = 0.0f;

	//背景構造体に情報を付与
	SetInfo_Text_Result();

	//位置に基づきポリゴンを展開
	Update_Pos_Text_Result();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Text_Result(void)
{
	//テクスチャの破棄
	if (g_pTexture_Text_Result != NULL)
	{
		g_pTexture_Text_Result->Release();
		g_pTexture_Text_Result = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Text_Result != NULL)
	{
		g_pVtxBuff_Text_Result->Release();
		g_pVtxBuff_Text_Result = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Text_Result(void)
{

}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Text_Result(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Text_Result, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Text_Result);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//リザルトテキスト構造体の情報を設定する関数
//************************************************
void SetInfo_Text_Result(void)
{
	SCORE* pSCORE = GetInfo_SCORE();

	g_aText_Result.pos = pSCORE->pos;
	g_aText_Result.pos.x -= 425.0f;
	g_aText_Result.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aText_Result.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aText_Result.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aText_Result.fRadius[0] = 350.0f;
	g_aText_Result.fRadius[1] = 100.0f;
	g_aText_Result.fLength = sqrtf((g_aText_Result.fRadius[0] * g_aText_Result.fRadius[0]) + (g_aText_Result.fRadius[1] * g_aText_Result.fRadius[1]));
	g_aText_Result.fAngle = atan2f(g_aText_Result.fRadius[0] * 2.0f, g_aText_Result.fRadius[1] * 2.0f);
}

//************************************************
//リザルトテキストの位置を設定する関数
//************************************************
void Update_Pos_Text_Result(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Text_Result;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Text_Result->Lock(0, 0, (void**)&pVtx_Text_Result, 0);

	pVtx_Text_Result[0].pos.x = g_aText_Result.pos.x + sinf(g_aText_Result.rot.z - (D3DX_PI - g_aText_Result.fAngle)) * g_aText_Result.fLength;
	pVtx_Text_Result[0].pos.y = g_aText_Result.pos.y + cosf(g_aText_Result.rot.z - (D3DX_PI - g_aText_Result.fAngle)) * g_aText_Result.fLength;
	pVtx_Text_Result[1].pos.x = g_aText_Result.pos.x + sinf(g_aText_Result.rot.z + (D3DX_PI - g_aText_Result.fAngle)) * g_aText_Result.fLength;
	pVtx_Text_Result[1].pos.y = g_aText_Result.pos.y + cosf(g_aText_Result.rot.z + (D3DX_PI - g_aText_Result.fAngle)) * g_aText_Result.fLength;
	pVtx_Text_Result[2].pos.x = g_aText_Result.pos.x + sinf(g_aText_Result.rot.z - g_aText_Result.fAngle) * g_aText_Result.fLength;
	pVtx_Text_Result[2].pos.y = g_aText_Result.pos.y + cosf(g_aText_Result.rot.z - g_aText_Result.fAngle) * g_aText_Result.fLength;
	pVtx_Text_Result[3].pos.x = g_aText_Result.pos.x + sinf(g_aText_Result.rot.z + g_aText_Result.fAngle) * g_aText_Result.fLength;
	pVtx_Text_Result[3].pos.y = g_aText_Result.pos.y + cosf(g_aText_Result.rot.z + g_aText_Result.fAngle) * g_aText_Result.fLength;

	//頂点バッファをアンロックする
	g_pVtxBuff_Text_Result->Unlock();
}

//************************************************
//リザルトテキスト構造体のアドレスを渡す
//************************************************
TEXT_RESULT* GetInfo_Text_Result(void)
{
	return &g_aText_Result;
}