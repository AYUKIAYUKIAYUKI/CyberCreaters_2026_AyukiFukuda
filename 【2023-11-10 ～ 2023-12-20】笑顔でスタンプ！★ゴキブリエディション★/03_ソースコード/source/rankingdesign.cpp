//************************************************
//
//ランキングデザイン[rankingdesign.cpp]
//Author：福田歩希
//
//************************************************
#include "rankingdesign.h"

#include "debugproc.h"
#include "fade.h"
#include "input.h"

#define AMOUNT_NUM (24)	//使える数字の最大数

//デザインテクスチャ識別
typedef enum
{
	TexLogo = 0,
	Tex1st,
	Tex2nd,
	Tex3rd,
	TexNow,
	TexLast,
	TexMax
}TexType;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureRankingDesign[TexMax] = {};	//テクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankingScore = NULL;	//数字テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingDesign = NULL;	//頂点バッファのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingScore = NULL;	//数字頂点バッファのポインタ
RankingDesign g_aRankingDesign[TexMax];	//情報
RankingDesign g_aRankingScore[AMOUNT_NUM];	//情報

int g_nScoreInfo[3];	//記録
int g_nLastScore = 0;
int g_nLastMode = 0;	//以前のモード

//************************************************
//ランキングデザイン初期
//************************************************
void InitRankingDesign(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < 3; i++)
	{
		g_nScoreInfo[i]= 0;
	}

	//デザイン情報群
	//**************************************************************************

	//デザイン情報の初期化群
	for (int i = 0; i < TexMax; i++)
	{
		g_aRankingDesign[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingDesign[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingDesign[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingDesign[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aRankingDesign[i].sizeX = 0.0f;
		g_aRankingDesign[i].sizeY = 0.0f;
		g_aRankingDesign[i].F = 1.0f;	//汎用
	}

	//デザインテクスチャの読込み
	const char* pFileName[TexMax] =
	{
		"data\\texture\\roachrank.png",
		"data\\texture\\1st.png",
		"data\\texture\\2nd.png",
		"data\\texture\\3rd.png",
		"data\\texture\\nowscore.png",
		"data\\texture\\lastscore.png",
	};


	for (int i = 0; i < TexMax; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureRankingDesign[i]);
	}

	//デザイン頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * TexMax,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingDesign,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffRankingDesign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
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
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankingDesign->Unlock();

	//数字情報群
	//**************************************************************************

	//数字情報の初期化群
	for (int i = 0; i < AMOUNT_NUM; i++)
	{
		g_aRankingScore[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingScore[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingScore[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingScore[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aRankingScore[i].sizeX = 0.0f;
		g_aRankingScore[i].sizeY = 0.0f;
		g_aRankingScore[i].F = 1.0f;	//汎用
	}

	//数字テクスチャの読み込み
	const char* pScoreTexture =
	{
		"data\\texture\\NUM.png",
	};

	for (int i = 0; i < AMOUNT_NUM; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			pScoreTexture,
			&g_pTextureRankingScore);
	}

	//数字頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingScore,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtxNum;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtxNum, 0);

	for (int i = 0; i < AMOUNT_NUM; i++, pVtxNum += AMOUNT_VTX)
	{
		//頂点座標の初期設定
		pVtxNum[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtxNum[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtxNum[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtxNum[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtxNum[0].rhw = 1.0f;
		pVtxNum[1].rhw = 1.0f;
		pVtxNum[2].rhw = 1.0f;
		pVtxNum[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtxNum[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtxNum[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtxNum[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtxNum[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtxNum[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtxNum[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtxNum[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtxNum[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankingScore->Unlock();

	//情報を付与
	SetInfoRankingDesign();

	//記録を読み込む
	ReadScoreInfo();

	//展開
	SetSizeRankingDesign();
}

//************************************************
//最後に遊んでたモードを決めるため
//************************************************
int* ChangeLastMode(void)
{
	return &g_nLastMode;
}

//************************************************
//ランキングデザイン終了処理関数
//************************************************
void UninitRankingDesign(void)
{
	//デザイン群
	//**************************************************************************

	//デザインテクスチャの破棄
	for (int i = 0; i < TexMax; i++)
	{
		if (g_pTextureRankingDesign[i] != NULL)
		{
			g_pTextureRankingDesign[i]->Release();
			g_pTextureRankingDesign[i] = NULL;
		}
	}

	//デザイン頂点バッファの破棄
	if (g_pVtxBuffRankingDesign != NULL)
	{
		g_pVtxBuffRankingDesign->Release();
		g_pVtxBuffRankingDesign = NULL;
	}

	//数字群
	//**************************************************************************

	//数字テクスチャの破棄
	if (g_pTextureRankingScore != NULL)
	{
		g_pTextureRankingScore->Release();
		g_pTextureRankingScore = NULL;
	}

	//数字頂点バッファの破棄
	if (g_pVtxBuffRankingScore != NULL)
	{
		g_pVtxBuffRankingScore->Release();
		g_pVtxBuffRankingScore = NULL;
	}
}

//************************************************
//ランキングデザイン更新
//************************************************
void UpdateRankingDesign(void)
{
	PrintDebugProc("%f %f %f\n", g_aRankingDesign[TexNow].pos.x, g_aRankingDesign[TexNow].pos.y, g_aRankingDesign[TexNow].pos.z);
	PrintDebugProc("%f %f %f\n", g_aRankingDesign[TexLast].pos.x, g_aRankingDesign[TexLast].pos.y, g_aRankingDesign[TexLast].pos.z);

	for (int i = 16; i < AMOUNT_NUM; i++)
	{
		PrintDebugProc("数字%d : %f %f %f\n", i + 1, g_aRankingScore[i].pos.x, g_aRankingScore[i].pos.y, g_aRankingScore[i].pos.z);
	}
}

//************************************************
//ランキングデザイン展開
//************************************************
void SetSizeRankingDesign(void)
{
	//デザイン
	//**************************************************************************

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffRankingDesign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		//頂点座標の初期設定
		pVtx[0].pos =
		{
			g_aRankingDesign[i].pos.x - g_aRankingDesign[i].sizeX,
			g_aRankingDesign[i].pos.y - g_aRankingDesign[i].sizeY,
			0.0f
		};

		pVtx[1].pos =
		{
			g_aRankingDesign[i].pos.x + g_aRankingDesign[i].sizeX,
			g_aRankingDesign[i].pos.y - g_aRankingDesign[i].sizeY,
			0.0f
		};

		pVtx[2].pos =
		{
			g_aRankingDesign[i].pos.x - g_aRankingDesign[i].sizeX,
			g_aRankingDesign[i].pos.y + g_aRankingDesign[i].sizeY,
			0.0f
		};

		pVtx[3].pos =
		{
			g_aRankingDesign[i].pos.x + g_aRankingDesign[i].sizeX,
			g_aRankingDesign[i].pos.y + g_aRankingDesign[i].sizeY,
			0.0f
		};
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankingDesign->Unlock();

	//スコア
	//**************************************************************************

	//頂点情報へのポインタ
	VERTEX_2D* pVtxNum;

	//疑似スコア用意
	int nCopyScoreInfo[3];

	for (int i = 0; i < 3; i++)
	{
		nCopyScoreInfo[i] = g_nScoreInfo[i];
	}

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtxNum, 0);

	for (int i = 0, j = 0; i < AMOUNT_NUM; i++, pVtxNum += AMOUNT_VTX)
	{
		if (i < 6)
		{
			j = 0;
		}
		else if (i >= 6 && i < 12)
		{
			j = 1;
		}
		else if (i >= 12 && i < 18)
		{
			j = 2;
		}
		else if (i == 18)
		{
			nCopyScoreInfo[j] = g_nLastScore;
		}

		//頂点座標の初期設定
		pVtxNum[0].pos =
		{
			g_aRankingScore[i].pos.x - g_aRankingScore[i].sizeX,
			g_aRankingScore[i].pos.y - g_aRankingScore[i].sizeY,
			0.0f
		};

		pVtxNum[1].pos =
		{
			g_aRankingScore[i].pos.x + g_aRankingScore[i].sizeX,
			g_aRankingScore[i].pos.y - g_aRankingScore[i].sizeY,
			0.0f
		};

		pVtxNum[2].pos =
		{
			g_aRankingScore[i].pos.x - g_aRankingScore[i].sizeX,
			g_aRankingScore[i].pos.y + g_aRankingScore[i].sizeY,
			0.0f
		};

		pVtxNum[3].pos =
		{
			g_aRankingScore[i].pos.x + g_aRankingScore[i].sizeX,
			g_aRankingScore[i].pos.y + g_aRankingScore[i].sizeY,
			0.0f
		};

		//計算用に数値を分裂
		int Value = nCopyScoreInfo[j];

		//片方は剰余算
		int Span = Value % 10;

		//片方は桁を減らす
		nCopyScoreInfo[j] /= 10;

		//振り分けをベースにテクスチャ座標を変更
		pVtxNum[0].tex.x = 0.1f * Span;
		pVtxNum[1].tex.x = 0.1f * (Span + 1);
		pVtxNum[2].tex.x = 0.1f * Span;
		pVtxNum[3].tex.x = 0.1f * (Span + 1);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRankingScore->Unlock();
}

//************************************************
//ランキングデザイン描画
//************************************************
void DrawRankingDesign(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//デザイン
	//**************************************************************************

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankingDesign, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TexMax; i++)
	{
		pDevice->SetTexture(0, g_pTextureRankingDesign[i]);

		//ランキングデザインの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//数字
	//**************************************************************************

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankingScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ランキングデザインの描画
	for (int i = 0; i < AMOUNT_NUM; i++)
	{
		//テクスチャの描画
		pDevice->SetTexture(0, g_pTextureRankingScore);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//構造体の情報を設定する関数
//************************************************
void SetInfoRankingDesign(void)
{
	//デザイン
	for (int i = 0; i < TexMax; i++)
	{
		if (i == TexLogo)
		{
			g_aRankingDesign[i].pos = D3DXVECTOR3((float)SCREEN_HALFWIDTH, (float)SCREEN_HALFHEIGHT, 0.0f);
			g_aRankingDesign[i].sizeX = (float)SCREEN_HALFWIDTH;
			g_aRankingDesign[i].sizeY = (float)SCREEN_HALFHEIGHT;
		}
		else
		{
			g_aRankingDesign[i].pos = D3DXVECTOR3(650.0f, 150.0f + (i * 200.0f), 0.0f);
			g_aRankingDesign[i].sizeX = 175.0f;
			g_aRankingDesign[i].sizeY = 100.0f;
		}

		if (g_nLastMode == MODE_GAME)
		{
			if (i == TexNow)
			{
				g_aRankingDesign[i].pos = D3DXVECTOR3(700.0f, 950.0f, 0.0f);
				g_aRankingDesign[i].sizeX = 400.0f;
				g_aRankingDesign[i].sizeY = 100.0f;
			}
			else if (i == TexLast)
			{
				g_aRankingDesign[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aRankingDesign[i].sizeX = 0.0f;
				g_aRankingDesign[i].sizeY = 0.0f;
			}
		}
		else if (g_nLastMode == MODE_TITLE)
		{
			if (i == TexNow)
			{
				g_aRankingDesign[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aRankingDesign[i].sizeX = 0.0f;
				g_aRankingDesign[i].sizeY = 0.0f;
			}
			else if (i == TexLast)
			{
				g_aRankingDesign[i].pos = D3DXVECTOR3(700.0f, 950.0f, 0.0f);
				g_aRankingDesign[i].sizeX = 400.0f;
				g_aRankingDesign[i].sizeY = 100.0f;
			}
		}

		g_aRankingDesign[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingDesign[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingDesign[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRankingDesign[i].F = 1.0f;	//汎用
	}

	//数字
	for (int i = 0; i < AMOUNT_NUM; i++)
	{
		if (i < 6)
		{
			g_aRankingScore[i].pos = D3DXVECTOR3((g_aRankingDesign[Tex1st].pos.x + 800.0f) + (i * -100.0f), g_aRankingDesign[Tex1st].pos.y, 0.0f);
		}
		else if (i >= 6 && i < 12)
		{
			g_aRankingScore[i].pos = D3DXVECTOR3((g_aRankingDesign[Tex2nd].pos.x + 800.0f) + ((i - 6) * -100.0f), g_aRankingDesign[Tex2nd].pos.y, 0.0f);
		}
		else if (i >= 12 && i < 18)
		{
			g_aRankingScore[i].pos = D3DXVECTOR3((g_aRankingDesign[Tex3rd].pos.x + 800.0f) + ((i - 12) * -100.0f), g_aRankingDesign[Tex3rd].pos.y, 0.0f);
		}
		else if (i >= 18 && i < 24)
		{
			if (g_nLastMode == MODE_TITLE)
			{
				g_aRankingScore[i].pos = D3DXVECTOR3((g_aRankingDesign[TexLast].pos.x + 1200.0f) + ((i - 16) * -100.0f), g_aRankingDesign[TexLast].pos.y, 0.0f);
			}
			else
			{
				g_aRankingScore[i].pos = D3DXVECTOR3((g_aRankingDesign[TexNow].pos.x + 1200.0f) + ((i - 16) * -100.0f), g_aRankingDesign[TexNow].pos.y, 0.0f);
			}
		}
		g_aRankingScore[i].sizeX = (float)100.0f;
		g_aRankingScore[i].sizeY = (float)80.0f;
		g_aRankingScore[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingScore[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingScore[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRankingScore[i].F = 1.0f;	//汎用
	}
}

//************************************************
//過去のスコアの記録を読み込む
//************************************************
void ReadScoreInfo(void)
{
	FILE* pFile;

	if (fopen_s(&pFile, "data\\txt\\rank.txt", "r") == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			fscanf_s(pFile, "%d", &g_nScoreInfo[i]);
		}

		fclose(pFile);
	}

	if (fopen_s(&pFile, "data\\txt\\lastrank.txt", "r") == 0)
	{

		fscanf_s(pFile, "%d", &g_nLastScore);

		fclose(pFile);
	}
}