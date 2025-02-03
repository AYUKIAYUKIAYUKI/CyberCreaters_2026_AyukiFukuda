//************************************************
//
//ランキングテキスト処理[text_title.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "score_ranking.h"
#include "text_ranking.h"
#include "title.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Text_Ranking[AMOUNT_TEX_TEXT_RANKING] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Text_Ranking = NULL;	//頂点バッファのポインタ
TEXT_RANKING g_aText_Ranking[AMOUNT_POLYGON_TEXT_RANKING];	//ランキングテキスト情報

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Text_Ranking()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_RANKING_1,
		&g_pTexture_Text_Ranking[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_RANKING_2,
		&g_pTexture_Text_Ranking[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TEXT_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Text_Ranking,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Text_Ranking;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Text_Ranking->Lock(0, 0, (void**)&pVtx_Text_Ranking, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_RANKING; i++)
	{
		//頂点座標の初期設定
		pVtx_Text_Ranking[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Ranking[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Ranking[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Ranking[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Text_Ranking[0].rhw = 1.0f;
		pVtx_Text_Ranking[1].rhw = 1.0f;
		pVtx_Text_Ranking[2].rhw = 1.0f;
		pVtx_Text_Ranking[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Text_Ranking[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Ranking[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Ranking[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Ranking[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx_Text_Ranking[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Text_Ranking[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Text_Ranking[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Text_Ranking[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Text_Ranking += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Text_Ranking->Unlock();

	//背景構造体の情報の初期化群
	for (int i = 0; i < AMOUNT_POLYGON_TEXT_RANKING; i++)
	{
		g_aText_Ranking[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Ranking[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Ranking[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Ranking[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aText_Ranking[i].fRadius[nCnt] = 0.0f;
		}
		g_aText_Ranking[i].fLength = 0.0f;
		g_aText_Ranking[i].fAngle = 0.0f;
	}

	//背景構造体に情報を付与
	SetInfo_Text_Ranking();

	//位置に基づきポリゴンを展開
	Update_Pos_Text_Ranking();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Text_Ranking(void)
{
	//テクスチャの破棄
	for (int i = 0; i < AMOUNT_TEX_TEXT_RANKING; i++)
	{
		if (g_pTexture_Text_Ranking[i] != NULL)
		{
			g_pTexture_Text_Ranking[i]->Release();
			g_pTexture_Text_Ranking[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Text_Ranking != NULL)
	{
		g_pVtxBuff_Text_Ranking->Release();
		g_pVtxBuff_Text_Ranking = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Text_Ranking(void)
{

}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Text_Ranking(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Text_Ranking, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_RANKING; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexture_Text_Ranking[i]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ランキングテキスト構造体の情報を設定する関数
//************************************************
void SetInfo_Text_Ranking(void)
{
	SCORE_RANKING* pSCORE_RANKING = GetInfo_Score_Ranking();

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_RANKING; i++)
	{
		g_aText_Ranking[i].pos = pSCORE_RANKING[i * 8].pos;
		g_aText_Ranking[i].pos.x -= 525.0f;
		g_aText_Ranking[i].pos.y -= 10.0f;
		g_aText_Ranking[i].fRadius[0] = RADIUS_TEXT_RANKING_X;	//背景横半幅
		g_aText_Ranking[i].fRadius[1] = RADIUS_TEXT_RANKING_Y;	//背景縦半幅
		g_aText_Ranking[i].fLength = sqrtf((g_aText_Ranking[i].fRadius[0] * g_aText_Ranking[i].fRadius[0]) + (g_aText_Ranking[i].fRadius[1] * g_aText_Ranking[i].fRadius[1]));
		g_aText_Ranking[i].fAngle = atan2f(g_aText_Ranking[i].fRadius[0] * 2.0f, g_aText_Ranking[i].fRadius[1] * 2.0f);
	}
}

//************************************************
//ランキングテキストの位置を設定する関数
//************************************************
void Update_Pos_Text_Ranking(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Text_Ranking;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Text_Ranking->Lock(0, 0, (void**)&pVtx_Text_Ranking, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_RANKING; i++)
	{
		pVtx_Text_Ranking[0].pos.x = g_aText_Ranking[i].pos.x + sinf(g_aText_Ranking[i].rot.z - (D3DX_PI - g_aText_Ranking[i].fAngle)) * g_aText_Ranking[i].fLength;
		pVtx_Text_Ranking[0].pos.y = g_aText_Ranking[i].pos.y + cosf(g_aText_Ranking[i].rot.z - (D3DX_PI - g_aText_Ranking[i].fAngle)) * g_aText_Ranking[i].fLength;
		pVtx_Text_Ranking[1].pos.x = g_aText_Ranking[i].pos.x + sinf(g_aText_Ranking[i].rot.z + (D3DX_PI - g_aText_Ranking[i].fAngle)) * g_aText_Ranking[i].fLength;
		pVtx_Text_Ranking[1].pos.y = g_aText_Ranking[i].pos.y + cosf(g_aText_Ranking[i].rot.z + (D3DX_PI - g_aText_Ranking[i].fAngle)) * g_aText_Ranking[i].fLength;
		pVtx_Text_Ranking[2].pos.x = g_aText_Ranking[i].pos.x + sinf(g_aText_Ranking[i].rot.z - g_aText_Ranking[i].fAngle) * g_aText_Ranking[i].fLength;
		pVtx_Text_Ranking[2].pos.y = g_aText_Ranking[i].pos.y + cosf(g_aText_Ranking[i].rot.z - g_aText_Ranking[i].fAngle) * g_aText_Ranking[i].fLength;
		pVtx_Text_Ranking[3].pos.x = g_aText_Ranking[i].pos.x + sinf(g_aText_Ranking[i].rot.z + g_aText_Ranking[i].fAngle) * g_aText_Ranking[i].fLength;
		pVtx_Text_Ranking[3].pos.y = g_aText_Ranking[i].pos.y + cosf(g_aText_Ranking[i].rot.z + g_aText_Ranking[i].fAngle) * g_aText_Ranking[i].fLength;

		pVtx_Text_Ranking += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Text_Ranking->Unlock();
}

//************************************************
//ランキングテキスト構造体のアドレスを渡す
//************************************************
TEXT_RANKING* GetInfo_Text_Ranking(void)
{
	return &g_aText_Ranking[0];
}