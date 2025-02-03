//========================
//
//ランキング処理:ranking.cpp
//Authar:KuramaeSatoshi
// 
//========================
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "sound.h"
#include <assert.h>
#include "player_count.h"
#include "game.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;		//頂点バッファへのポインタ
RankScore g_aRankScore[MAX_RANK][MAX_DIGIT];		//ランキングスコア情報([ランク数][桁数])
int g_nRankUpdate = -1;								//更新ランクNo.
int g_nTimerRanking;								//点灯させる時間
int g_NumPlayer_RANK = JOIN_VERIFY;	//プレイ人数格納

//背景処理用のグローバル変数
LPDIRECT3DTEXTURE9 g_pTextureRank_BG[NUM_RANK_UITEX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank_BG = NULL;
//=======================================================================
//ランキングの初期化処理
//=======================================================================
void InitRanking(void)
{
	PlaySound(SOUND_LABEL_RESULT_RANKING_BGM);
	InitRanking_BG();
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank = 0; //数をカウントする(順位)
	int nDataRank = 0;	//数をカウントする(桁数)

	g_NumPlayer_RANK = 0;	// 参加人数の初期化

	//プレイ人数の取得
	g_NumPlayer_RANK = ReturnSelectPlayerCount() + 1;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\result\\Number001.png", &g_pTextureRank);


	//ランキングの情報の初期化
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nDataRank = 0; nDataRank < MAX_DIGIT; nDataRank++)
		{
			g_aRankScore[nCntRank][nDataRank].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //スコアの位置の初期化
			g_aRankScore[nCntRank][nDataRank].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 360.0f - 80.0f * nDataRank, 100.0f + 210 * nCntRank, 0.0f);
			g_aRankScore[nCntRank][nDataRank].nScore = 0;                       //使用していない状態
			g_aRankScore[nCntRank][nDataRank].nScorePos = 0;					//テクスチャの位置
			g_aRankScore[nCntRank][nDataRank].bRight = false;					//点灯させるかどうか
		}
	}

	g_nTimerRanking = 0;	//点灯させる時間

//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * MAX_DIGIT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRank, NULL);

	//頂点情報のポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntRank = 0; nCntRank < MAX_RANK * MAX_DIGIT; nCntRank++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}


	//頂点バッファのアンロック
	g_pVtxBuffRank->Unlock();

	SetRanking(*GetInfoScore());

	//フェードイン処理
	SetFade(FADE_IN, MODE_MAX);//フェードイン時は二個目の引数無視されるのでなんでもいい

}

//=======================================================================
//ランキングの終了処理
//=======================================================================
void UninitRanking(void)
{
	StopSound();
	UninitRanking_BG();
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}
}

//=======================================================================
//ランキングの更新処理
//=======================================================================
void UpdateRanking(void)
{
	UpdateRanking_BG();
	g_nTimerRanking++;	//ランキングを点灯させる時間の更新

	//頂点情報のポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	int nCntRank = 0;
	int nCntDigit = 0;	//桁数

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A, 0))
	{//ENTERキーが押された or Aボタンが押された

		//モード設定(ゲーム画面に移行)
		SetFade(FADE_OUT, MODE_TITLE);
	}

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			pVtx[0].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x - MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y - MAX_RANKHEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x + MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y - MAX_RANKHEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x - MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y + MAX_RANKHEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x + MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y + MAX_RANKHEIGHT, 0.0f);



			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx += 4;
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffRank->Unlock();
}

//=======================================================================
//ランキングの描画処理
//=======================================================================
void DrawRanking(void)
{
	DrawRanking_BG();
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRank = 0; nCntRank < MAX_RANK * MAX_DIGIT; nCntRank++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRank);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRank * 4, 2);
	}
}


//=======================================================================
//ランキングのリセット処理
//=======================================================================
void ResetRanking(void)
{
	int nCntRank; //数をカウントする(順位)
	int nCntDigit;	//数をカウントする(桁数)

	//ランキングの情報の初期化
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			g_aRankScore[nCntRank][nCntDigit].nScore = 0;                       //使用していない状態
		}
	}

}

//=======================================================================
//ランキングのセット処理
//=======================================================================
void SetRanking(int nScore)
{
	//頂点情報のポインタ
	VERTEX_2D* pVtx;

	FILE* pFile = NULL;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	int nCnt = 0;
	int nCntRank = 0;
	int nCntDigit = 0;	//桁数

	int nCntData = 0;	//要素1の情報
	int nAddRank = 0;	//今回のスコア
	int nCopyData = 0;	//データの受け皿
	bool bFlag = false;	//光らせるフラグ
	bool SkipFlag = false;	//ランク内に同じスコアがある場合処理を飛ばすフラグ
	int nData[MAX_RANK];	//すでにランクインしてるスコア	
	int nDataRank[MAX_RANK];	//データを保存する用
	int nDataSave[MAX_RANK];	//ランクインしたスコアの保存(並べ替えた後)


	pFile = fopen("data\\TXT\\SCORE\\Ranking.txt", "r");



	if (pFile != NULL)
	{
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			fscanf(pFile, "%d", &nData[nCntRank]);	//スコアをファイルから読み込む

			nDataRank[nCntRank] = nData[nCntRank];	//保存する

			nDataSave[nCntRank] = 0;	//初期化
		}

		nAddRank = nScore;	//今回のスコアを代入する
	}

	fclose(pFile);

	for (int i = 0; i < MAX_RANK; i++)
	{
		if (nAddRank == nData[i])
		{
			SkipFlag = true;
		}
	}

	if (nAddRank >= nData[MAX_RANK - 1] && SkipFlag == false)
	{//もし5位より現在のスコアが高かったら
		nData[MAX_RANK - 1] = nAddRank;//5位に現在のスコアを代入
	}

	for (nCntData = 0; nCntData <= MAX_RANK - 1; nCntData++)//要素1と要素2を比較する
	{
		for (nCntRank = nCntData + 1; nCntRank < MAX_RANK; nCntRank++)
		{
			if (nData[nCntData] < nData[nCntRank])
			{
				nCopyData = nData[nCntData];	//受け皿に要素1を代入
				nData[nCntData] = nData[nCntRank];	//要素1に要素2を代入
				nData[nCntRank] = nCopyData;		//数値を入れ替える
			}
		}
	}


	pFile = fopen("data\\TXT\\SCORE\\Ranking.txt", "w");



	if (pFile != NULL)
	{
		for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fprintf(pFile, "%d\n", nData[nCnt]);	//並べ替えたものを改めて保存する
		}
	}

	fclose(pFile);



	for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		nDataSave[nCnt] = nData[nCnt];	//スコアの代入
	}

	for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			g_aRankScore[nCnt][nCntDigit].nScorePos = nData[nCnt] % 10;
			nData[nCnt] = nData[nCnt] / 10;
		}
	}

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 1.0f);

			pVtx += 4;
		}


	}
	//頂点バッファのアンロック
	g_pVtxBuffRank->Unlock();
}

//=====================================================
//
//ランキング画面の背景処理
//
//=====================================================

//初期化処理
void InitRanking_BG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\Ranking.png", &g_pTextureRank_BG[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\ranking_ui.png", &g_pTextureRank_BG[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_RANK_UITEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRank_BG, NULL);

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRank_BG->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < NUM_RANK_UITEX; i++)
	{
		if (i == 0)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		}
		if (i == 1)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(500.0f, 10.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(650.0f, 10.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(500.0f, 1010.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(650.0f, 1010.0f, 0.0f);

		}

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffRank_BG->Unlock();
}

//終了処理
void UninitRanking_BG(void)
{
	for (int i = 0; i < NUM_RANK_UITEX; i++)
	{
		//テクスチャの破棄
		if (g_pTextureRank_BG[i] != NULL)
		{
			g_pTextureRank_BG[i]->Release();
			g_pTextureRank_BG[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRank_BG != NULL)
	{
		g_pVtxBuffRank_BG->Release();
		g_pVtxBuffRank_BG = NULL;
	}
}

//更新処理(特に動きなし)
void UpdateRanking_BG(void)
{

}

//描画処理
void DrawRanking_BG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRank_BG, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_RANK_UITEX; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRank_BG[i]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}

}