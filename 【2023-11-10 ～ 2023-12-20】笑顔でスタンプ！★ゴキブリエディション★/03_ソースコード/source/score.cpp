//************************************************
//
//スコア処理[score.cpp]	(レガシー)
//Author：福田歩希
//
//************************************************
#include "score.h"

#include "input.h"
#include "sound.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Score[AMOUNT_TEXTURE_SCORE] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Score = NULL;	//頂点バッファのポインタ
float g_fMoveX_Score = 0.0f;	//ポリゴン移動量
int g_nScore[AMOUNT_POLYGON_SCORE] = {};	//画面表示用振り分け
int g_nHoldScore = 0;	//計算するときスコアの値を借りてくる
int g_nNowScore = 0;	//現在のスコア
int g_nCntWaitScore = 0;	//スコアカウント
int g_nAnimeScore[AMOUNT_POLYGON_SCORE] = {};	//アニメーション用疑似スコア格納
int g_nCntAnimeScore = 0;	//アニメーション用カウント
int g_nCntFinishAnimeScore = 0;	//アニメーション終了カウント
bool g_bAddedScore = false;	//スコアに加算があったか判定
int g_nScore_Digit = 0;	//桁数情報を格納

/* 追加 */
static const float g_AdjustX = 0.0f;
static const float g_AdjustY = 15.0f;

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Score(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLACK_SCORE,
		&g_pTexture_Score[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NUMBER_SCORE,
		&g_pTexture_Score[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SYMBOL_SCORE,
		&g_pTexture_Score[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Score,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Score;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Score->Lock(0, 0, (void**)&pVtx_Score, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Score[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Score[0].rhw = 1.0f;
		pVtx_Score[1].rhw = 1.0f;
		pVtx_Score[2].rhw = 1.0f;
		pVtx_Score[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Score[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Score[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Score[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Score[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Score[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Score += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Score->Unlock();

	//移動量をリセット
	g_fMoveX_Score = 0.0f;

	//振り分けをリセット
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE; nCnt++)
	{
		g_nScore[nCnt] = 0;
	}

	//保持をリセット
	g_nHoldScore = 0;

	//現在のスコアをリセット
	g_nNowScore = 0;

	//スコアカウント
	g_nCntWaitScore = 0;

	//疑似スコアリセット
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE; nCnt++)
	{
		g_nAnimeScore[nCnt] = 0;
	}

	//アニメーション用カウント
	g_nCntAnimeScore = 0;

	//アニメーション終了カウント
	g_nCntFinishAnimeScore = 0;

	//加算判定を無くす
	g_bAddedScore = false;

	//桁数情報を格納
	g_nScore_Digit = 0;

	//頂点の展開
	SetPos_Vtx_Score();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Score(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_SCORE; nCnt++)
	{
		if (g_pTexture_Score[nCnt] != NULL)
		{
			g_pTexture_Score[nCnt]->Release();
			g_pTexture_Score[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Score != NULL)
	{
		g_pVtxBuff_Score->Release();
		g_pVtxBuff_Score = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Score(void)
{
	//加算フラグの立っているときのみ解放
	if (g_bAddedScore)
	{
		Calc_Score();

		if (g_nCntFinishAnimeScore < 5)
		{
			g_nCntAnimeScore++;

			if (g_nCntAnimeScore > 2)
			{
				//数字アニメーション
				Animation_Score();

				g_nCntAnimeScore = 0;

				g_nCntFinishAnimeScore++;
			}
		}
		else
		{
			//最後に正確な値を並べる
			ReSetPos_Vtx_Score();

			//計算終了
			g_bAddedScore = false;

			g_nCntFinishAnimeScore = 0;
		}
	}
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Score(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Score, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE; nCnt++)
	{
		if (nCnt == 0)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexture_Score[0]);
		}
		else if (nCnt >= 1 && nCnt <= 6)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexture_Score[1]);
		}
		else
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexture_Score[2]);
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//スコア配置用処理関数
//************************************************
void SetPos_Vtx_Score(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Score;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Score->Lock(0, 0, (void**)&pVtx_Score, 0);

	//黒い棒を適当な位置へ
	pVtx_Score[0].pos = D3DXVECTOR3(385.0f + g_AdjustX, 20.0f + g_AdjustY, 0.0f);
	pVtx_Score[1].pos = D3DXVECTOR3(700.0f + g_AdjustX, 20.0f + g_AdjustY, 0.0f);
	pVtx_Score[2].pos = D3DXVECTOR3(360.0f + g_AdjustX, 100.0f + g_AdjustY, 0.0f);
	pVtx_Score[3].pos = D3DXVECTOR3(675.0f + g_AdjustX, 100.0f + g_AdjustY, 0.0f);

	//頂点カラーの設定
	pVtx_Score[0].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx_Score[1].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx_Score[2].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx_Score[3].col = D3DCOLOR_RGBA(255, 255, 255, 150);

	//数字へ
	pVtx_Score += AMOUNT_VTX;

	//最初は1桁のみ表示(なおこの後の処理のため最後のポリゴンを表示)
	for (int nCnt = 0; nCnt < AMOUNT_USING_POLYGON_NUMBER_SCORE; nCnt++)
	{
		if (nCnt == AMOUNT_USING_POLYGON_NUMBER_SCORE - 1)
		{
			//スコアを1桁表示(備考：始点470, 中点575, 終点680, 幅210, 数字幅60)
			pVtx_Score[0].pos = D3DXVECTOR3(535.0f + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[1].pos = D3DXVECTOR3(595.0f + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[2].pos = D3DXVECTOR3(535.0f + g_AdjustX, 80.0f + g_AdjustY, 0.0f);
			pVtx_Score[3].pos = D3DXVECTOR3(595.0f + g_AdjustX, 80.0f + g_AdjustY, 0.0f);

			//テクスチャ座標の設定
			pVtx_Score[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_Score[1].tex = D3DXVECTOR2(TEX_U_RIGHT_SCORE, 0.0f);
			pVtx_Score[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx_Score[3].tex = D3DXVECTOR2(TEX_U_RIGHT_SCORE, 1.0f);
		}

		//ポリゴン頂点は変更し続ける
		pVtx_Score += AMOUNT_VTX;
	}

	//シンボルをその辺に配置
	pVtx_Score[0].pos = D3DXVECTOR3(405.0f + g_AdjustX, 30.0f + g_AdjustY, 0.0f);
	pVtx_Score[1].pos = D3DXVECTOR3(445.0f + g_AdjustX, 30.0f + g_AdjustY, 0.0f);
	pVtx_Score[2].pos = D3DXVECTOR3(405.0f + g_AdjustX, 90.0f + g_AdjustY, 0.0f);
	pVtx_Score[3].pos = D3DXVECTOR3(445.0f + g_AdjustX, 90.0f + g_AdjustY, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Score->Unlock();
}

//************************************************
//スコア計算表示用処理関数
//************************************************
void Calc_Score(void)
{
	//桁数
	int nScore_Digit = 0;

	//オーバーフロー防止
	g_nNowScore >= AMOUNT_MAX_SCORE ? g_nNowScore = AMOUNT_MAX_SCORE : g_nNowScore;

	//計算用に、今のスコアを取得
	g_nHoldScore = g_nNowScore;

	//ホールド分計算する
	for (int nCnt = 0; nCnt < AMOUNT_USING_POLYGON_NUMBER_SCORE; nCnt++)
	{
		//配列のAMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt番目に1の位の数値を振り分ける
		g_nScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt] = g_nHoldScore % 10;

		//位を下げる
		g_nHoldScore /= 10;

		//桁数を取得
		nScore_Digit++;

		//位の下げようがないならここで終了
		if (g_nHoldScore < 0.5)
		{
			break;
		}
	}

	//桁数情報を渡す
	g_nScore_Digit = nScore_Digit;
}

//************************************************
//スコアを増やす用処理関数
//************************************************
void Add_Score(int Add)
{
	//加算開始の判定を出す
	g_bAddedScore = true;

	//引数分スコアが増える
	g_nNowScore += Add;

	//スコア加算時は計算中でもアニメカウントをリセット
	g_nCntFinishAnimeScore = 0;

	//そしてそれを計算
	Calc_Score();
}

//************************************************
//アニメーション処理関数
//************************************************
void Animation_Score(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Timer;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Score->Lock(0, 0, (void**)&pVtx_Timer, 0);

	pVtx_Timer += AMOUNT_VTX * AMOUNT_USING_POLYGON_NUMBER_SCORE;

	//疑似スコアリセット
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE; nCnt++)
	{
		g_nAnimeScore[nCnt] = 0;
	}

	int nDecreaseDigit = 0;
	g_nScore_Digit == 3 ?
		nDecreaseDigit = 1 :
		nDecreaseDigit = 2;

	for (int nCnt = 0; nCnt < g_nScore_Digit - nDecreaseDigit; nCnt++)
	{
		g_nAnimeScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt] = rand() % 10;

		//振り分けをベースにテクスチャ座標を変更
		pVtx_Timer[0].tex.x = MOVE_SPAN_TEX_SCORE * g_nAnimeScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt];
		pVtx_Timer[1].tex.x = MOVE_SPAN_TEX_SCORE * (g_nAnimeScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt] + 1);
		pVtx_Timer[2].tex.x = MOVE_SPAN_TEX_SCORE * g_nAnimeScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt];
		pVtx_Timer[3].tex.x = MOVE_SPAN_TEX_SCORE * (g_nAnimeScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt] + 1);

		pVtx_Timer -= AMOUNT_VTX;
	}
}

//************************************************
//ポリゴン再展開処理関数
//************************************************
void ReSetPos_Vtx_Score(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Score;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Score->Lock(0, 0, (void**)&pVtx_Score, 0);

	//ポインタを数字の最後へ
	pVtx_Score += AMOUNT_VTX * AMOUNT_USING_POLYGON_NUMBER_SCORE;

	g_fMoveX_Score = 0;

	//取得した桁数分回す
	for (int nCnt = 0; nCnt < g_nScore_Digit; nCnt++)
	{
		//現在スコアの桁数に応じてポリゴンを並べる
		switch (g_nScore_Digit)
		{
		case 1:

			pVtx_Score[0].pos = D3DXVECTOR3(535.0f + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[1].pos = D3DXVECTOR3(595.0f + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[2].pos = D3DXVECTOR3(535.0f + g_AdjustX, 80.0f + g_AdjustY, 0.0f);
			pVtx_Score[3].pos = D3DXVECTOR3(595.0f + g_AdjustX, 80.0f + g_AdjustY, 0.0f);

			break;

		case 2:

			pVtx_Score[0].pos = D3DXVECTOR3(550.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[1].pos = D3DXVECTOR3(610.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[2].pos = D3DXVECTOR3(550.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);
			pVtx_Score[3].pos = D3DXVECTOR3(610.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);

			break;

		case 3:

			pVtx_Score[0].pos = D3DXVECTOR3(565.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[1].pos = D3DXVECTOR3(625.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[2].pos = D3DXVECTOR3(565.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);
			pVtx_Score[3].pos = D3DXVECTOR3(625.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);

			break;

		case 4:

			pVtx_Score[0].pos = D3DXVECTOR3(580.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[1].pos = D3DXVECTOR3(640.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[2].pos = D3DXVECTOR3(580.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);
			pVtx_Score[3].pos = D3DXVECTOR3(640.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);

			break;

		case 5:

			pVtx_Score[0].pos = D3DXVECTOR3(595.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[1].pos = D3DXVECTOR3(655.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[2].pos = D3DXVECTOR3(595.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);
			pVtx_Score[3].pos = D3DXVECTOR3(655.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);

			break;

		case 6:

			pVtx_Score[0].pos = D3DXVECTOR3(610.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[1].pos = D3DXVECTOR3(670.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[2].pos = D3DXVECTOR3(610.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);
			pVtx_Score[3].pos = D3DXVECTOR3(670.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);

			break;
		}

		g_fMoveX_Score += DISTANCESPAN_POLYGON_SCORE;

		//振り分けをベースにテクスチャ座標を変更
		pVtx_Score[0].tex.x = MOVE_SPAN_TEX_SCORE * g_nScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt];
		pVtx_Score[1].tex.x = MOVE_SPAN_TEX_SCORE * (g_nScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt] + 1);
		pVtx_Score[2].tex.x = MOVE_SPAN_TEX_SCORE * g_nScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt];
		pVtx_Score[3].tex.x = MOVE_SPAN_TEX_SCORE * (g_nScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt] + 1);

		pVtx_Score -= AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Score->Unlock();
}

//*************************************
//スコア記録
//*************************************
void SaveScore(void)
{
	int nScoreInfo[3];

	FILE* pFile;

	//その時とったスコアを書込み
	if (fopen_s(&pFile, "data\\txt\\lastrank.txt", "w") == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			fprintf(pFile, "%d\n", g_nNowScore);
		}

		fclose(pFile);
	}

	if (fopen_s(&pFile, "data\\txt\\rank.txt", "r") == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			fscanf_s(pFile, "%d", &nScoreInfo[i]);
		}

		fclose(pFile);
	}

	int nScore[4] =
	{
		nScoreInfo[0],
		nScoreInfo[1],
		nScoreInfo[2],
		g_nNowScore,
	};

	int nScoreWrite[3];
	int nHold = 0;

	//ソート
	for (int i = 0; i < 4; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			if (nScore[i] < nScore[j])
			{
				nHold = nScore[i];
				nScore[i] = nScore[j];
				nScore[j] = nHold;
			}
		}
	}

	//並べ替え
	for (int i = 0; i < 3; i++)
	{
		nScoreWrite[i] = nScore[i];
	}

	//書込み
	if (fopen_s(&pFile, "data\\txt\\rank.txt", "w") == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			fprintf(pFile, "%d\n", nScoreWrite[i]);
		}

		fclose(pFile);
	}
}