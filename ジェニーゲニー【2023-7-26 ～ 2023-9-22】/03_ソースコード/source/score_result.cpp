//************************************************
//
//スコア(リザルト)処理[score_result.cpp]
//Author：福田歩希
//
//************************************************
#include "score_result.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Score_Result[AMOUNT_TEXTURE_SCORE_RESULT] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Score_Result = NULL;	//頂点バッファのポインタ
float g_fMoveX_Score_Result = 0.0f;	//ポリゴン移動量
int g_aFileData_Score[5]= {};	//ファイルからデータを格納
int g_nAnimeScore_Result[AMOUNT_POLYGON_SCORE_RESULT] = {};	//アニメーション用疑似スコア格納
SCORE_RESULT g_aScore_Result[AMOUNT_POLYGON_SCORE_RESULT];	//

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Score_Result(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NUMBER_SCORE_RESULT,
		&g_pTexture_Score_Result[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_SCORE_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Score_Result,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Score_Result;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Score_Result->Lock(0, 0, (void**)&pVtx_Score_Result, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE_RESULT; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Score_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Score_Result[0].rhw = 1.0f;
		pVtx_Score_Result[1].rhw = 1.0f;
		pVtx_Score_Result[2].rhw = 1.0f;
		pVtx_Score_Result[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Score_Result[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score_Result[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score_Result[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score_Result[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Score_Result[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Score_Result[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Score_Result[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Score_Result[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Score_Result += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Score_Result->Unlock();

	//移動量をリセット
	g_fMoveX_Score_Result = 0.0f;

	//ファイル格納用初期化
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		g_aFileData_Score[nCnt] = 0;
	}

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE_RESULT; nCnt++)
	{
		g_nAnimeScore_Result[nCnt] = 0;

		g_aScore_Result[nCnt].nStyle = 0;
		g_aScore_Result[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Result[nCnt].fSpanX = 0.0f;
		g_aScore_Result[nCnt].fSpanY = 0.0f;
		g_aScore_Result[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Result[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Result[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//情報の読み取り
	Setinfo_Score_Result();

	//頂点の展開
	SetPos_Vtx_Score_Result();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Score_Result(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_SCORE_RESULT; nCnt++)
	{
		if (g_pTexture_Score_Result[nCnt] != NULL)
		{
			g_pTexture_Score_Result[nCnt]->Release();
			g_pTexture_Score_Result[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Score_Result != NULL)
	{
		g_pVtxBuff_Score_Result->Release();
		g_pVtxBuff_Score_Result = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Score_Result(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Score_Result;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Score_Result->Lock(0, 0, (void**)&pVtx_Score_Result, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE_RESULT; nCnt++)
	{
		//移動、回転を反映
		pVtx_Score_Result[0].pos.x = g_aScore_Result[nCnt].pos.x - g_aScore_Result[nCnt].fSpanX;
		pVtx_Score_Result[0].pos.y = g_aScore_Result[nCnt].pos.y - g_aScore_Result[nCnt].fSpanY;
		pVtx_Score_Result[1].pos.x = g_aScore_Result[nCnt].pos.x + g_aScore_Result[nCnt].fSpanX;
		pVtx_Score_Result[1].pos.y = g_aScore_Result[nCnt].pos.y - g_aScore_Result[nCnt].fSpanY;
		pVtx_Score_Result[2].pos.x = g_aScore_Result[nCnt].pos.x - g_aScore_Result[nCnt].fSpanX;
		pVtx_Score_Result[2].pos.y = g_aScore_Result[nCnt].pos.y + g_aScore_Result[nCnt].fSpanY;
		pVtx_Score_Result[3].pos.x = g_aScore_Result[nCnt].pos.x + g_aScore_Result[nCnt].fSpanX;
		pVtx_Score_Result[3].pos.y = g_aScore_Result[nCnt].pos.y + g_aScore_Result[nCnt].fSpanY;

		pVtx_Score_Result[0].col = g_aScore_Result[nCnt].col;
		pVtx_Score_Result[1].col = g_aScore_Result[nCnt].col;
		pVtx_Score_Result[2].col = g_aScore_Result[nCnt].col;
		pVtx_Score_Result[3].col = g_aScore_Result[nCnt].col;

		//テクスチャ座標の初期設定
		pVtx_Score_Result[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_nAnimeScore_Result[nCnt]), 0.0f);
		pVtx_Score_Result[1].tex = D3DXVECTOR2(TEX_U_RIGHT_SCORE_RESULT + (0.1f * g_nAnimeScore_Result[nCnt]), 0.0f);
		pVtx_Score_Result[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_nAnimeScore_Result[nCnt]), 1.0f);
		pVtx_Score_Result[3].tex = D3DXVECTOR2(TEX_U_RIGHT_SCORE_RESULT + (0.1f * g_nAnimeScore_Result[nCnt]), 1.0f);

		pVtx_Score_Result += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Score_Result->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Score_Result(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Score_Result, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE_RESULT; nCnt++)
	{
		//テクスチャの設定
		switch (g_aScore_Result[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Score_Result[0]);

			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//スコア情報読み取り処理関数
//************************************************
void Setinfo_Score_Result(void)
{
	//ファイルポインタを宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen("data\\txt\\rank.txt", "r");

	//ファイルが開けた
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			fscanf(pFile, "%d", &g_aFileData_Score[nCnt]);
		}

		fclose(pFile);
	}

	//読み取るスコアデータ分回す
	for (int nCnt1 = 0; nCnt1 < 5; nCnt1++)
	{
		//ホールド分計算する
		for (int nCnt2 = 0 + (6 * nCnt1); nCnt2 < 30; nCnt2++)
		{
			g_nAnimeScore_Result[nCnt2] = g_aFileData_Score[nCnt1] % 10;

			//位を下げる
			g_aFileData_Score[nCnt1] *= 0.1;

			//位の下げようがないならここで終了
			if (g_aFileData_Score[nCnt1] < 0.5)
			{
				break;
			}
		}
	}
}

//************************************************
//スコア配置用処理関数
//************************************************
void SetPos_Vtx_Score_Result(void)
{
	int nCntDigit = 0;
	int nLine = 0;

	for (int nCnt = 0; nCnt < 30; nCnt++)
	{
		g_aScore_Result[nCnt].nStyle = 0;
		g_aScore_Result[nCnt].pos = D3DXVECTOR3(900.0f - (50.0f * nCntDigit), 300.0f + (150.0f * nLine), 0.0f);
		g_aScore_Result[nCnt].fSpanX = 30.0f;
		g_aScore_Result[nCnt].fSpanY = 37.5f;
		g_aScore_Result[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Result[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Result[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		nCntDigit++;

		if (nCntDigit > 5)
		{
			nCntDigit = 0;
			nLine++;
		}
	}
}