//************************************************
//
//スコア処理[score.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "input.h"
#include "score.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Score = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Score = NULL;	//頂点バッファのポインタ
SCORE g_aScore[AMOUNT_POLYGON_SCORE];	//スコア表示用
int g_nScore[SCORE_STYLE_MAX];	//スコア
int g_nScore_Digit;	//桁数
int g_nAnimeCnt;

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Score(int nMode)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SCORE,
		&g_pTexture_Score);

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

	//スコア構造体クリア
	for (int i = 0; i < AMOUNT_POLYGON_SCORE; i++)
	{
		g_aScore[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aScore[i].nCntTex = 0;
		g_aScore[i].nCntPattern = 0;
		for (int ii = 0; ii < AMOUNT_POLYGON_SCORE; ii++)
		{
			g_aScore[i].fTexSpan[ii] = 0.0f;
			g_aScore[i].fRadius[ii] = 0.0f;
			g_aScore[i].fLength[ii] = 0.0f;
			g_aScore[i].fAngle[ii] = 0.0f;
		}
	}

	//スコアクリア
	if (nMode != SCORE_TYPE_RESULT)
	{
		for (int i = 0; i < SCORE_STYLE_MAX; i++)
		{
			g_nScore[i] = 0;
		}
	}

	g_nScore_Digit = 0;

	g_nAnimeCnt = 0;

	//スコア表示用にデータをセット
	SetInfo_Score(nMode);
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Score(void)
{
	//テクスチャの破棄
	if (g_pTexture_Score != NULL)
	{
		g_pTexture_Score->Release();
		g_pTexture_Score = NULL;
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
	/*キモいので無し*/
	//数値の変動を検知してアニメーション
	//if (g_nAnimeCnt > 0)
	//{
	//	g_nAnimeCnt--;
	//	Animation_Score();
	//	Update_Tex_Score();
	//}
	//else
	//{
	//	g_nScore_Digit = 0;

		//オーバーフロー防止
		g_nScore[SCORE_NEW] >= AMOUNT_MAX_SCORE ? g_nScore[SCORE_NEW] = AMOUNT_MAX_SCORE : 0;

		//展開
		Update_Pos_Score();
	//}
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
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexture_Score);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//スコア表示用にデータを付与する関数
//************************************************
void SetInfo_Score(int nMode)
{
	for (int i = 0; i < AMOUNT_POLYGON_SCORE; i++)
	{
		switch (nMode)
		{
		case SCORE_TYPE_GAME:
			g_aScore[i].pos = D3DXVECTOR3(1500.0f + (55.0f * i), 100.0f, 0.0f);
			g_aScore[i].fRadius[0] = 25.0f;
			g_aScore[i].fRadius[1] = 45.0f;
			break;
		case SCORE_TYPE_RESULT:
			g_aScore[i].pos = D3DXVECTOR3(1000.0f + (100.0f * i), 625.0f, 0.0f);
			g_aScore[i].fRadius[0] = 50.0f;
			g_aScore[i].fRadius[1] = 90.0f;
			break;
		}
		g_aScore[i].fTexSpan[0] = 0.0f;
		g_aScore[i].fTexSpan[1] = 0.1f;
		g_aScore[i].fLength[0] = sqrtf((g_aScore[i].fRadius[0] * g_aScore[i].fRadius[0]) + (g_aScore[i].fRadius[1] * g_aScore[i].fRadius[1]));
		g_aScore[i].fLength[1] = g_aScore[i].fLength[0];
		g_aScore[i].fAngle[0] = atan2f(g_aScore[i].fRadius[0] * 2.0f, g_aScore[i].fRadius[1] * 2.0f);
		g_aScore[i].fAngle[1] = g_aScore[i].fAngle[0];
	}
}

//************************************************
//スコア表示用にバーテックスを更新関数
//************************************************
void Update_Pos_Score(void)
{
	//テクスチャを更新
	Update_Tex_Score();

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Score;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Score->Lock(0, 0, (void**)&pVtx_Score, 0);

	for (int i = 0; i < AMOUNT_POLYGON_SCORE; i++)
	{
		pVtx_Score[0].pos.x = g_aScore[i].pos.x + sinf(g_aScore[i].rot.z - (D3DX_PI - g_aScore[i].fAngle[0])) * g_aScore[i].fLength[0];
		pVtx_Score[0].pos.y = g_aScore[i].pos.y + cosf(g_aScore[i].rot.z - (D3DX_PI - g_aScore[i].fAngle[0])) * g_aScore[i].fLength[0];
		pVtx_Score[1].pos.x = g_aScore[i].pos.x + sinf(g_aScore[i].rot.z + (D3DX_PI - g_aScore[i].fAngle[0])) * g_aScore[i].fLength[0];
		pVtx_Score[1].pos.y = g_aScore[i].pos.y + cosf(g_aScore[i].rot.z + (D3DX_PI - g_aScore[i].fAngle[0])) * g_aScore[i].fLength[0];
		pVtx_Score[2].pos.x = g_aScore[i].pos.x + sinf(g_aScore[i].rot.z - g_aScore[i].fAngle[1]) * g_aScore[i].fLength[1];
		pVtx_Score[2].pos.y = g_aScore[i].pos.y + cosf(g_aScore[i].rot.z - g_aScore[i].fAngle[1]) * g_aScore[i].fLength[1];
		pVtx_Score[3].pos.x = g_aScore[i].pos.x + sinf(g_aScore[i].rot.z + g_aScore[i].fAngle[1]) * g_aScore[i].fLength[1];
		pVtx_Score[3].pos.y = g_aScore[i].pos.y + cosf(g_aScore[i].rot.z + g_aScore[i].fAngle[1]) * g_aScore[i].fLength[1];

		pVtx_Score += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Score->Unlock();
}

//************************************************
//スコア表示用にテクスチャを更新関数
//************************************************
void Update_Tex_Score(void)
{
	//テクスチャの幅をスコアから算出
	//if (g_nAnimeCnt <= 0)
	//{
		Calc_Tex_Score();
	//}

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Score;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Score->Lock(0, 0, (void**)&pVtx_Score, 0);

	for (int i = 0; i < AMOUNT_POLYGON_SCORE; i++)
	{
		pVtx_Score[0].tex = D3DXVECTOR2(g_aScore[i].fTexSpan[0], 0.0f);
		pVtx_Score[1].tex = D3DXVECTOR2(g_aScore[i].fTexSpan[1], 0.0f);
		pVtx_Score[2].tex = D3DXVECTOR2(g_aScore[i].fTexSpan[0], 1.0f);
		pVtx_Score[3].tex = D3DXVECTOR2(g_aScore[i].fTexSpan[1], 1.0f);

		pVtx_Score += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Score->Unlock();
}

//************************************************
//スコアからにテクスチャ幅を計算関数
//************************************************
void Calc_Tex_Score(void)
{
	//スコアを取得
	int nHold = g_nScore[SCORE_NEW];

	//計算する
	for (int i = 0; i < AMOUNT_POLYGON_SCORE; i++)
	{
		//1の位の数値を抜き出す
		int nNumber = nHold % 10;

		//抜き出た数字から幅をセット
		g_aScore[(AMOUNT_POLYGON_SCORE - 1) - i].fTexSpan[0] = 0.0f + (0.1f * nNumber);
		g_aScore[(AMOUNT_POLYGON_SCORE - 1) - i].fTexSpan[1] = 0.1f + (0.1f * nNumber);

		//スコアの桁をずらす
		nHold /= 10;

		//桁数を取得
		if (i > 0)
		{
			g_nScore_Digit++;
		}

		//位の下げようがないならここで終了
		if (nHold < 0.5)
		{
			break;
		}
	}
}

//************************************************
//ぐちゃ
//************************************************
void Animation_Score(void)
{
	//桁数分回す
	for (int i = 0; i < g_nScore_Digit; i++)
	{
		//適当に数値抜き出す
		int nNumber = rand() % 10;

		//抜き出た数字から幅をセット
		g_aScore[(AMOUNT_POLYGON_SCORE - 1) - i].fTexSpan[0] = 0.0f + (0.1f * nNumber);
		g_aScore[(AMOUNT_POLYGON_SCORE - 1) - i].fTexSpan[1] = 0.1f + (0.1f * nNumber);
	}
}

//************************************************
//スコア表示用のアドレスを渡す
//************************************************
SCORE* GetInfo_SCORE(void)
{
	return &g_aScore[0];
}

//************************************************
//スコアのアドレスを渡す
//************************************************
int* GetInfo_Score(void)
{
	return &g_nScore[0];
}

//************************************************
//アニメーション
//************************************************
int* GetInfo_S_A_CT(void)
{
	return &g_nAnimeCnt;
}