//************************************************
//
//ランキングにスコアを出す[ranking_score.cpp]
//Author：福田歩希
//
//************************************************
#include "ranking_score.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Ranking_Score[AMOUNT_TEXTURE_RANKING_SCORE] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Ranking_Score = NULL;	//頂点バッファのポインタ
RANKING_SCORE g_aRanking_Score[AMOUNT_POLYGON_RANKING_SCORE];	//ポリゴンの情報を格納
READ_RANKING_SCORE g_aRead_Ranking_Score[6];
int g_nHold_Ranking_Score = 0;
int g_nView_Ranking_Score[AMOUNT_POLYGON_RANKING_SCORE][AMOUNT_POLYGON_RANKING_SCORE] = {};	//画面表示用振り分け
int g_nLastScore = 0;	//ゲームで獲得したスコア
char g_stringScore[6][256];

float g_fcolA = 0.0f;
bool g_bcol = false;

//************************************************
//初期化処理関数
//************************************************
void Init_Ranking_Score(int nMode)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NUMBER_RANKING_SCORE,
		&g_pTexture_Ranking_Score[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_RANKING_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Ranking_Score,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Ranking_Score;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Ranking_Score->Lock(0, 0, (void**)&pVtx_Ranking_Score, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_SCORE; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Ranking_Score[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Score[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Score[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Score[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Ranking_Score[0].rhw = 1.0f;
		pVtx_Ranking_Score[1].rhw = 1.0f;
		pVtx_Ranking_Score[2].rhw = 1.0f;
		pVtx_Ranking_Score[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Ranking_Score[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Score[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Score[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Score[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Ranking_Score[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Ranking_Score[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx_Ranking_Score[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Ranking_Score[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx_Ranking_Score += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Ranking_Score->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_SCORE; nCnt++)
	{
		g_aRanking_Score[nCnt].nStyle = 0;
		g_aRanking_Score[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Score[nCnt].fSpanX = 0.0f;
		g_aRanking_Score[nCnt].fSpanY = 0.0f;
		g_aRanking_Score[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Score[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Score[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aRanking_Score[nCnt].fLength = 0.0f;
		g_aRanking_Score[nCnt].fAngle = 0.0f;
		g_aRanking_Score[nCnt].fSPD_X = 0.0f;
		g_aRanking_Score[nCnt].colA = 0.0f;
	}

	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		g_aRead_Ranking_Score[nCnt].lfScore = 0;
		g_aRead_Ranking_Score[nCnt].nDigit = 0;
		
		for (int nWORD = 0; nWORD < 256; nWORD++)
		{
			g_stringScore[nCnt][nWORD] = {};
		}
	}

	g_nHold_Ranking_Score = 0;

	for (int nCnt1 = 0; nCnt1 < AMOUNT_POLYGON_RANKING_SCORE; nCnt1++)
	{
		for (int nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_RANKING_SCORE; nCnt2++)
		{
			g_nView_Ranking_Score[nCnt1][nCnt2] = 0;
		}
	}

	g_nLastScore = 0;

	g_fcolA = 1.0f;

	g_bcol = false;

	//スコア読込み
	Readinfo_Ranking_Score();

	//記録されたスコアとの比較
	if (nMode == 1)
	{
		SetNewinfo_Ranking();
	}

	//ある程度の事前情報を設定
	Setinfo_Ranking_Score();

	SetTex_Ranking_Score(nMode);
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Ranking_Score(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_RANKING_SCORE; nCnt++)
	{
		if (g_pTexture_Ranking_Score[nCnt] != NULL)
		{
			g_pTexture_Ranking_Score[nCnt]->Release();
			g_pTexture_Ranking_Score[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Ranking_Score != NULL)
	{
		g_pVtxBuff_Ranking_Score->Release();
		g_pVtxBuff_Ranking_Score = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Ranking_Score(void)
{
	////頂点情報へのポインタ
	//VERTEX_2D* pVtx_Ranking_Score;

	////頂点バッファをロックして頂点情報のポインタを取得
	//g_pVtxBuff_Ranking_Score->Lock(0, 0, (void**)&pVtx_Ranking_Score, 0);

	//for (int nRow = 0; nRow < 5; nRow++)
	//{
	//	if (g_aRead_Ranking_Score[nRow].lfScore == g_nLastScore)
	//	{
	//		for (int nCnt = 0; nCnt < g_aRead_Ranking_Score[nRow].nDigit; nCnt++)
	//		{
	//			if (g_fcolA > 0.0f && !g_bcol)
	//			{
	//				g_fcolA -= 0.01f;
	//			}
	//			else if (!g_bcol)
	//			{
	//				g_bcol = true;
	//			}

	//			if (g_fcolA < 1.0f && g_bcol)
	//			{
	//				g_fcolA += 0.01f;
	//			}
	//			else if (g_bcol)
	//			{
	//				g_bcol = false;
	//			}

	//			//振り分けをベースにテクスチャ座標を変更
	//			pVtx_Ranking_Score[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcolA);
	//			pVtx_Ranking_Score[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcolA);
	//			pVtx_Ranking_Score[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcolA);
	//			pVtx_Ranking_Score[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcolA);

	//			pVtx_Ranking_Score += AMOUNT_VTX;
	//		}
	//	}
	//	else
	//	{
	//		for (int nCnt = 0; nCnt < g_aRead_Ranking_Score[nRow].nDigit; nCnt++)
	//		{
	//			pVtx_Ranking_Score += AMOUNT_VTX;
	//		}
	//	}
	//}

	////頂点バッファをアンロックする
	//g_pVtxBuff_Ranking_Score->Unlock();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Ranking_Score(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Ranking_Score, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_SCORE; nCnt++)
	{
		if (g_aRanking_Score[nCnt].nStyle == 0)
		{
			pDevice->SetTexture(0, g_pTexture_Ranking_Score[0]);
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//スコア読込み関数
//************************************************
void Readinfo_Ranking_Score(void)
{
	int nRow = 0;

	//ファイルポインタを宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(FILE_SET_RANKING, "r");

	//ファイルが開けた
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf\n", &g_aRead_Ranking_Score[nRow].lfScore) != EOF)
		{
			nRow++;
		}

		fclose(pFile);
	}
}

//************************************************
//現在のスコアとかと比べる関数
//************************************************
void SetNewinfo_Ranking(void)
{
	int* pHoldLastScore;
	pHoldLastScore = Getinfo_HoldLastScore();

	//現在のスコアを取得
	g_nLastScore = *pHoldLastScore;

	////取ったスコアが記録されているものと同率だった場合
	//if ((int)g_aRead_Ranking_Score[nCnt].lfScore != g_nLastScore)
	//{
	//	//どうしようか
	//}

	//計算用に取ったスコア値を複製
	int nCopyLastScore = g_nLastScore;

	//既存のスコア大小を比べる
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		if ((int)g_aRead_Ranking_Score[nCnt].lfScore < nCopyLastScore)
		{
			//過去の低い記録を保持し、
			int nHold = (int)g_aRead_Ranking_Score[nCnt].lfScore;

			//取った記録をコピー
			g_aRead_Ranking_Score[nCnt].lfScore = nCopyLastScore;

			//低い方の記録を使って比較を繰り返す
			nCopyLastScore = nHold;
		}

		//書出し用に文字列に変換
		sprintf(&g_stringScore[nCnt][0], "%lf", g_aRead_Ranking_Score[nCnt].lfScore);
	}

	//比較が終わったら、スコアをファイルに書出す
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(FILE_SET_RANKING, "w");

	//開けた
	if (pFile != NULL)
	{
		//書込み
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			fprintf(pFile, "%s\n", &g_stringScore[nCnt][0]);
		}

		//ファイル閉じる
		fclose(pFile);
	}
}

//************************************************
//スコア表示用処理関数
//************************************************
void SetTex_Ranking_Score(int nMode)
{
	//ホールド分計算する
	for (int nRow = 0; nRow < AMOUNT_SET_RANKING_SCORE; nRow++)
	{
		//計算用に、スコアを取得
		g_nHold_Ranking_Score = (int)g_aRead_Ranking_Score[nRow].lfScore;

		for (int nLine = 0; nLine < AMOUNT_POLYGON_RANKING_SCORE; nLine++)
		{
			//数値を振り分ける
			g_nView_Ranking_Score[nRow][nLine] = g_nHold_Ranking_Score % 10;

			//位を下げる
			g_nHold_Ranking_Score *= 0.1;

			//桁数を取得
			g_aRead_Ranking_Score[nRow].nDigit++;

			//位の下げようがないならここで終了
			if (g_nHold_Ranking_Score < 0.5)
			{
				break;
			}
		}
	}

	//取ったスコアを取得
	g_nHold_Ranking_Score = g_nLastScore;

	for (int nLine = 0; nLine < AMOUNT_POLYGON_RANKING_SCORE; nLine++)
	{
		//数値を振り分ける
		g_nView_Ranking_Score[5][nLine] = g_nHold_Ranking_Score % 10;

		//位を下げる
		g_nHold_Ranking_Score *= 0.1;

		//桁数を取得
		g_aRead_Ranking_Score[5].nDigit++;

		//位の下げようがないならここで終了
		if (g_nHold_Ranking_Score < 0.5)
		{
			break;
		}
	}

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Ranking_Score;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Ranking_Score->Lock(0, 0, (void**)&pVtx_Ranking_Score, 0);

	for (int nRow = 0; nRow < AMOUNT_SET_RANKING_SCORE; nRow++)
	{
		for (int nCnt = 0; nCnt < g_aRead_Ranking_Score[nRow].nDigit; nCnt++)
		{
			//座標を指定
			switch (nRow)
			{
			case 0:

				g_aRanking_Score[nCnt].pos = D3DXVECTOR3(1540.0f - (125.0f * nCnt), 235.0f, 0.0f);

				g_aRanking_Score[nCnt].fSpanX = 75.0f;
				g_aRanking_Score[nCnt].fSpanY = 75.0f;
				g_aRanking_Score[nCnt].fLength = sqrtf((g_aRanking_Score[nCnt].fSpanX * g_aRanking_Score[nCnt].fSpanX) + (g_aRanking_Score[nCnt].fSpanY * g_aRanking_Score[nCnt].fSpanY));
				g_aRanking_Score[nCnt].fAngle = atan2f(g_aRanking_Score[nCnt].fSpanX * 2.0f, g_aRanking_Score[nCnt].fSpanY * 2.0f);

				break;

			case 1:

				g_aRanking_Score[nCnt].pos = D3DXVECTOR3(850.0f - (80.0f * nCnt), 525.0f, 0.0f);

				g_aRanking_Score[nCnt].fSpanX = 50.0f;
				g_aRanking_Score[nCnt].fSpanY = 50.0f;
				g_aRanking_Score[nCnt].fLength = sqrtf((g_aRanking_Score[nCnt].fSpanX * g_aRanking_Score[nCnt].fSpanX) + (g_aRanking_Score[nCnt].fSpanY * g_aRanking_Score[nCnt].fSpanY));
				g_aRanking_Score[nCnt].fAngle = atan2f(g_aRanking_Score[nCnt].fSpanX * 2.0f, g_aRanking_Score[nCnt].fSpanY * 2.0f);

				break;

			case 2:

				g_aRanking_Score[nCnt].pos = D3DXVECTOR3(1850.0f - (80.0f * nCnt), 525.0f, 0.0f);

				g_aRanking_Score[nCnt].fSpanX = 50.0f;
				g_aRanking_Score[nCnt].fSpanY = 50.0f;
				g_aRanking_Score[nCnt].fLength = sqrtf((g_aRanking_Score[nCnt].fSpanX * g_aRanking_Score[nCnt].fSpanX) + (g_aRanking_Score[nCnt].fSpanY * g_aRanking_Score[nCnt].fSpanY));
				g_aRanking_Score[nCnt].fAngle = atan2f(g_aRanking_Score[nCnt].fSpanX * 2.0f, g_aRanking_Score[nCnt].fSpanY * 2.0f);

				break;

			case 3:

				g_aRanking_Score[nCnt].pos = D3DXVECTOR3(830.0f - (70.0f * nCnt), 725.0f, 0.0f);

				g_aRanking_Score[nCnt].fSpanX = 40.0f;
				g_aRanking_Score[nCnt].fSpanY = 40.0f;
				g_aRanking_Score[nCnt].fLength = sqrtf((g_aRanking_Score[nCnt].fSpanX * g_aRanking_Score[nCnt].fSpanX) + (g_aRanking_Score[nCnt].fSpanY * g_aRanking_Score[nCnt].fSpanY));
				g_aRanking_Score[nCnt].fAngle = atan2f(g_aRanking_Score[nCnt].fSpanX * 2.0f, g_aRanking_Score[nCnt].fSpanY * 2.0f);

				break;

			case 4:

				g_aRanking_Score[nCnt].pos = D3DXVECTOR3(1830.0f - (70.0f * nCnt), 725.0f, 0.0f);

				g_aRanking_Score[nCnt].fSpanX = 40.0f;
				g_aRanking_Score[nCnt].fSpanY = 40.0f;
				g_aRanking_Score[nCnt].fLength = sqrtf((g_aRanking_Score[nCnt].fSpanX * g_aRanking_Score[nCnt].fSpanX) + (g_aRanking_Score[nCnt].fSpanY * g_aRanking_Score[nCnt].fSpanY));
				g_aRanking_Score[nCnt].fAngle = atan2f(g_aRanking_Score[nCnt].fSpanX * 2.0f, g_aRanking_Score[nCnt].fSpanY * 2.0f);

				break;
			}

			//移動、回転を反映
			pVtx_Ranking_Score[0].pos.x = g_aRanking_Score[nCnt].pos.x + sinf(g_aRanking_Score[nCnt].rot.z - (D3DX_PI - g_aRanking_Score[nCnt].fAngle)) * g_aRanking_Score[nCnt].fLength;
			pVtx_Ranking_Score[0].pos.y = g_aRanking_Score[nCnt].pos.y + cosf(g_aRanking_Score[nCnt].rot.z - (D3DX_PI - g_aRanking_Score[nCnt].fAngle)) * g_aRanking_Score[nCnt].fLength;
			pVtx_Ranking_Score[1].pos.x = g_aRanking_Score[nCnt].pos.x + sinf(g_aRanking_Score[nCnt].rot.z + (D3DX_PI - g_aRanking_Score[nCnt].fAngle)) * g_aRanking_Score[nCnt].fLength;
			pVtx_Ranking_Score[1].pos.y = g_aRanking_Score[nCnt].pos.y + cosf(g_aRanking_Score[nCnt].rot.z + (D3DX_PI - g_aRanking_Score[nCnt].fAngle)) * g_aRanking_Score[nCnt].fLength;
			pVtx_Ranking_Score[2].pos.x = g_aRanking_Score[nCnt].pos.x + sinf(g_aRanking_Score[nCnt].rot.z - g_aRanking_Score[nCnt].fAngle) * g_aRanking_Score[nCnt].fLength;
			pVtx_Ranking_Score[2].pos.y = g_aRanking_Score[nCnt].pos.y + cosf(g_aRanking_Score[nCnt].rot.z - g_aRanking_Score[nCnt].fAngle) * g_aRanking_Score[nCnt].fLength;
			pVtx_Ranking_Score[3].pos.x = g_aRanking_Score[nCnt].pos.x + sinf(g_aRanking_Score[nCnt].rot.z + g_aRanking_Score[nCnt].fAngle) * g_aRanking_Score[nCnt].fLength;
			pVtx_Ranking_Score[3].pos.y = g_aRanking_Score[nCnt].pos.y + cosf(g_aRanking_Score[nCnt].rot.z + g_aRanking_Score[nCnt].fAngle) * g_aRanking_Score[nCnt].fLength;

			//振り分けをベースにテクスチャ座標を変更
			pVtx_Ranking_Score[0].tex.x = 0.1f * g_nView_Ranking_Score[nRow][nCnt];
			pVtx_Ranking_Score[1].tex.x = 0.1f * (g_nView_Ranking_Score[nRow][nCnt] + 1);
			pVtx_Ranking_Score[2].tex.x = 0.1f * g_nView_Ranking_Score[nRow][nCnt];
			pVtx_Ranking_Score[3].tex.x = 0.1f * (g_nView_Ranking_Score[nRow][nCnt] + 1);

			pVtx_Ranking_Score += AMOUNT_VTX;
		}
	}

	if (nMode == 1)
	{
		for (int nCnt = 0; nCnt < g_aRead_Ranking_Score[5].nDigit; nCnt++)
		{
			g_aRanking_Score[5].pos = D3DXVECTOR3(1100.0f - (80.0f * nCnt), 925.0f, 0.0f);

			g_aRanking_Score[5].fSpanX = 50.0f;
			g_aRanking_Score[5].fSpanY = 50.0f;
			g_aRanking_Score[5].fLength = sqrtf((g_aRanking_Score[5].fSpanX * g_aRanking_Score[5].fSpanX) + (g_aRanking_Score[5].fSpanY * g_aRanking_Score[5].fSpanY));
			g_aRanking_Score[5].fAngle = atan2f(g_aRanking_Score[5].fSpanX * 2.0f, g_aRanking_Score[5].fSpanY * 2.0f);

			//移動、回転を反映
			pVtx_Ranking_Score[0].pos.x = g_aRanking_Score[5].pos.x + sinf(g_aRanking_Score[5].rot.z - (D3DX_PI - g_aRanking_Score[5].fAngle)) * g_aRanking_Score[5].fLength;
			pVtx_Ranking_Score[0].pos.y = g_aRanking_Score[5].pos.y + cosf(g_aRanking_Score[5].rot.z - (D3DX_PI - g_aRanking_Score[5].fAngle)) * g_aRanking_Score[5].fLength;
			pVtx_Ranking_Score[1].pos.x = g_aRanking_Score[5].pos.x + sinf(g_aRanking_Score[5].rot.z + (D3DX_PI - g_aRanking_Score[5].fAngle)) * g_aRanking_Score[5].fLength;
			pVtx_Ranking_Score[1].pos.y = g_aRanking_Score[5].pos.y + cosf(g_aRanking_Score[5].rot.z + (D3DX_PI - g_aRanking_Score[5].fAngle)) * g_aRanking_Score[5].fLength;
			pVtx_Ranking_Score[2].pos.x = g_aRanking_Score[5].pos.x + sinf(g_aRanking_Score[5].rot.z - g_aRanking_Score[5].fAngle) * g_aRanking_Score[5].fLength;
			pVtx_Ranking_Score[2].pos.y = g_aRanking_Score[5].pos.y + cosf(g_aRanking_Score[5].rot.z - g_aRanking_Score[5].fAngle) * g_aRanking_Score[5].fLength;
			pVtx_Ranking_Score[3].pos.x = g_aRanking_Score[5].pos.x + sinf(g_aRanking_Score[5].rot.z + g_aRanking_Score[5].fAngle) * g_aRanking_Score[5].fLength;
			pVtx_Ranking_Score[3].pos.y = g_aRanking_Score[5].pos.y + cosf(g_aRanking_Score[5].rot.z + g_aRanking_Score[5].fAngle) * g_aRanking_Score[5].fLength;

			//振り分けをベースにテクスチャ座標を変更
			pVtx_Ranking_Score[0].tex.x = 0.1f * g_nView_Ranking_Score[5][nCnt];
			pVtx_Ranking_Score[1].tex.x = 0.1f * (g_nView_Ranking_Score[5][nCnt] + 1);
			pVtx_Ranking_Score[2].tex.x = 0.1f * g_nView_Ranking_Score[5][nCnt];
			pVtx_Ranking_Score[3].tex.x = 0.1f * (g_nView_Ranking_Score[5][nCnt] + 1);

			pVtx_Ranking_Score += AMOUNT_VTX;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Ranking_Score->Unlock();
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Ranking_Score(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_SCORE; nCnt++)
	{
		g_aRanking_Score[nCnt].nStyle = nCnt;
		g_aRanking_Score[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRanking_Score[nCnt].fSPD_X = 1.0f;
		g_aRanking_Score[nCnt].colA = 0.01f;
	}
}