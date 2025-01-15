//************************************************
//
//スコア(ランキング)処理[score.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "score_ranking.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Score_Ranking = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Score_Ranking = NULL;	//頂点バッファのポインタ
SCORE_RANKING g_aScore_Ranking[AMOUNT_POLYGON_SCORE_RANKING];	//スコア表示用
int g_nScore_Ranking[SCORE_RANKING_STYLE_MAX];	//スコア

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Score_Ranking(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SCORE_RANKING,
		&g_pTexture_Score_Ranking);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_SCORE_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Score_Ranking,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Score_Ranking;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Score_Ranking->Lock(0, 0, (void**)&pVtx_Score_Ranking, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE_RANKING; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Score_Ranking[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score_Ranking[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score_Ranking[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score_Ranking[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Score_Ranking[0].rhw = 1.0f;
		pVtx_Score_Ranking[1].rhw = 1.0f;
		pVtx_Score_Ranking[2].rhw = 1.0f;
		pVtx_Score_Ranking[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Score_Ranking[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score_Ranking[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score_Ranking[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score_Ranking[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Score_Ranking[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Score_Ranking[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Score_Ranking[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Score_Ranking[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Score_Ranking += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Score_Ranking->Unlock();

	//スコア構造体クリア
	for (int i = 0; i < AMOUNT_POLYGON_SCORE_RANKING; i++)
	{
		g_aScore_Ranking[i].nStyle = 0;
		g_aScore_Ranking[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Ranking[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Ranking[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Ranking[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aScore_Ranking[i].nCntTex = 0;
		g_aScore_Ranking[i].nCntPattern = 0;
		for (int ii = 0; ii < AMOUNT_POLYGON_SCORE_RANKING; ii++)
		{
			g_aScore_Ranking[i].fTexSpan[ii] = 0.0f;
			g_aScore_Ranking[i].fRadius[ii] = 0.0f;
			g_aScore_Ranking[i].fLength[ii] = 0.0f;
			g_aScore_Ranking[i].fAngle[ii] = 0.0f;
		}
	}

	//スコアクリア
	for (int i = 0; i < SCORE_RANKING_STYLE_MAX; i++)
	{
		g_nScore_Ranking[i] = 0;
	}

	//スコア表示用にデータをセット
	SetInfo_Score_Ranking();

	//スコアデータを取得
	ReadInfo_Score_Ranking();

	//展開
	Update_Pos_Score_Ranking();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Score_Ranking(void)
{
	//テクスチャの破棄
	if (g_pTexture_Score_Ranking != NULL)
	{
		g_pTexture_Score_Ranking->Release();
		g_pTexture_Score_Ranking = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Score_Ranking != NULL)
	{
		g_pVtxBuff_Score_Ranking->Release();
		g_pVtxBuff_Score_Ranking = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Score_Ranking(void)
{

}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Score_Ranking(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Score_Ranking, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE_RANKING; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexture_Score_Ranking);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//スコア表示用にデータを付与する関数
//************************************************
void SetInfo_Score_Ranking(void)
{
	for (int i = 0; i < AMOUNT_POLYGON_SCORE_RANKING; i++)
	{
		i >= 8 ? g_aScore_Ranking[i].nStyle = SCORE_RANKING_LAST : g_aScore_Ranking[i].nStyle = SCORE_RANKING_HIGH;

		switch (g_aScore_Ranking[i].nStyle)
		{
		case SCORE_RANKING_HIGH:
			g_aScore_Ranking[i].pos = D3DXVECTOR3(1125.0f + (100.0f * i), 275.0f, 0.0f);
			g_aScore_Ranking[i].fRadius[0] = 50.0f;
			g_aScore_Ranking[i].fRadius[1] = 90.0f;
			break;
		case SCORE_RANKING_LAST:
			g_aScore_Ranking[i].pos = D3DXVECTOR3(1125.0f + (100.0f * (i - 8)), 600.0f, 0.0f);
			g_aScore_Ranking[i].fRadius[0] = 50.0f;
			g_aScore_Ranking[i].fRadius[1] = 90.0f;
			break;
		}
		g_aScore_Ranking[i].fTexSpan[0] = 0.0f;
		g_aScore_Ranking[i].fTexSpan[1] = 0.1f;
		g_aScore_Ranking[i].fLength[0] = sqrtf((g_aScore_Ranking[i].fRadius[0] * g_aScore_Ranking[i].fRadius[0]) + (g_aScore_Ranking[i].fRadius[1] * g_aScore_Ranking[i].fRadius[1]));
		g_aScore_Ranking[i].fLength[1] = g_aScore_Ranking[i].fLength[0];
		g_aScore_Ranking[i].fAngle[0] = atan2f(g_aScore_Ranking[i].fRadius[0] * 2.0f, g_aScore_Ranking[i].fRadius[1] * 2.0f);
		g_aScore_Ranking[i].fAngle[1] = g_aScore_Ranking[i].fAngle[0];
	}
}

//************************************************
//スコアに過去のデータを付与する関数
//************************************************
void ReadInfo_Score_Ranking(void)
{
	FILE* pFile;
	pFile = fopen("data\\txt\\ranking.txt", "r");

	if (pFile != NULL)
	{
		for (int i = 0; i < SCORE_RANKING_STYLE_MAX; i++)
		{
			fscanf(pFile, "%d", &g_nScore_Ranking[i]);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}

//************************************************
//スコア表示用にバーテックスを更新関数
//************************************************
void Update_Pos_Score_Ranking(void)
{
	//テクスチャを更新
	Update_Tex_Score_Ranking();

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Score_Ranking;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Score_Ranking->Lock(0, 0, (void**)&pVtx_Score_Ranking, 0);

	for (int i = 0; i < AMOUNT_POLYGON_SCORE_RANKING; i++)
	{
		pVtx_Score_Ranking[0].pos.x = g_aScore_Ranking[i].pos.x + sinf(g_aScore_Ranking[i].rot.z - (D3DX_PI - g_aScore_Ranking[i].fAngle[0])) * g_aScore_Ranking[i].fLength[0];
		pVtx_Score_Ranking[0].pos.y = g_aScore_Ranking[i].pos.y + cosf(g_aScore_Ranking[i].rot.z - (D3DX_PI - g_aScore_Ranking[i].fAngle[0])) * g_aScore_Ranking[i].fLength[0];
		pVtx_Score_Ranking[1].pos.x = g_aScore_Ranking[i].pos.x + sinf(g_aScore_Ranking[i].rot.z + (D3DX_PI - g_aScore_Ranking[i].fAngle[0])) * g_aScore_Ranking[i].fLength[0];
		pVtx_Score_Ranking[1].pos.y = g_aScore_Ranking[i].pos.y + cosf(g_aScore_Ranking[i].rot.z + (D3DX_PI - g_aScore_Ranking[i].fAngle[0])) * g_aScore_Ranking[i].fLength[0];
		pVtx_Score_Ranking[2].pos.x = g_aScore_Ranking[i].pos.x + sinf(g_aScore_Ranking[i].rot.z - g_aScore_Ranking[i].fAngle[1]) * g_aScore_Ranking[i].fLength[1];
		pVtx_Score_Ranking[2].pos.y = g_aScore_Ranking[i].pos.y + cosf(g_aScore_Ranking[i].rot.z - g_aScore_Ranking[i].fAngle[1]) * g_aScore_Ranking[i].fLength[1];
		pVtx_Score_Ranking[3].pos.x = g_aScore_Ranking[i].pos.x + sinf(g_aScore_Ranking[i].rot.z + g_aScore_Ranking[i].fAngle[1]) * g_aScore_Ranking[i].fLength[1];
		pVtx_Score_Ranking[3].pos.y = g_aScore_Ranking[i].pos.y + cosf(g_aScore_Ranking[i].rot.z + g_aScore_Ranking[i].fAngle[1]) * g_aScore_Ranking[i].fLength[1];

		pVtx_Score_Ranking += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Score_Ranking->Unlock();
}

//************************************************
//スコア表示用にテクスチャを更新関数
//************************************************
void Update_Tex_Score_Ranking(void)
{
	//テクスチャの幅をスコアから算出
	Calc_Tex_Score_Ranking();

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Score_Ranking;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Score_Ranking->Lock(0, 0, (void**)&pVtx_Score_Ranking, 0);

	for (int i = 0; i < AMOUNT_POLYGON_SCORE_RANKING; i++)
	{
		pVtx_Score_Ranking[0].tex = D3DXVECTOR2(g_aScore_Ranking[i].fTexSpan[0], 0.0f);
		pVtx_Score_Ranking[1].tex = D3DXVECTOR2(g_aScore_Ranking[i].fTexSpan[1], 0.0f);
		pVtx_Score_Ranking[2].tex = D3DXVECTOR2(g_aScore_Ranking[i].fTexSpan[0], 1.0f);
		pVtx_Score_Ranking[3].tex = D3DXVECTOR2(g_aScore_Ranking[i].fTexSpan[1], 1.0f);

		pVtx_Score_Ranking += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Score_Ranking->Unlock();
}

//************************************************
//スコアからにテクスチャ幅を計算関数
//************************************************
void Calc_Tex_Score_Ranking(void)
{
	//スコアを取得
	int nHold[SCORE_RANKING_STYLE_MAX];
	for (int i = 0; i < SCORE_RANKING_STYLE_MAX; i++)
	{
		nHold[i] = g_nScore_Ranking[i];
	}

	//計算する
	for (int i = 0; i < AMOUNT_POLYGON_SCORE_RANKING; i++)
	{
		if (i < 8)
		{
			//1の位の数値を抜き出す
			int nNumber = nHold[SCORE_RANKING_HIGH] % 10;

			//抜き出た数字から幅をセット
			g_aScore_Ranking[(8 - 1) - i].fTexSpan[0] = 0.0f + (0.1f * nNumber);
			g_aScore_Ranking[(8 - 1) - i].fTexSpan[1] = 0.1f + (0.1f * nNumber);

			//スコアの桁をずらす
			nHold[SCORE_RANKING_HIGH] /= 10;
		}
		else
		{
			//1の位の数値を抜き出す
			int nNumber = nHold[SCORE_RANKING_LAST] % 10;

			//抜き出た数字から幅をセット
			g_aScore_Ranking[(AMOUNT_POLYGON_SCORE_RANKING - 1) - (i - 8)].fTexSpan[0] = 0.0f + (0.1f * nNumber);
			g_aScore_Ranking[(AMOUNT_POLYGON_SCORE_RANKING - 1) - (i - 8)].fTexSpan[1] = 0.1f + (0.1f * nNumber);

			//スコアの桁をずらす
			nHold[SCORE_RANKING_LAST] /= 10;
		}
	}
}


//************************************************
//スコア表示用のアドレスを取得する関数
//************************************************
SCORE_RANKING* GetInfo_Score_Ranking(void)
{
	return &g_aScore_Ranking[0];
}