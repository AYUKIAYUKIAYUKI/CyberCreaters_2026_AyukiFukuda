//===============================================================================
//
//		リザルト画面(画面遷移確認用)(result.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "result.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "stdio.h"
#include "game.h"
#include "player_count.h"
#include "sound.h"
#define MAX_NUMBER_STR	8										//スコア桁数
#define MAX_SCORE_STR	2										//表示するスコアグループの数
#define RESULT_USE_POLY	(MAX_NUMBER_STR * MAX_SCORE_STR)		//上記二つの乗算(スコアの描画等で使うよ)
#define RESULT_USE_TEX	3										//リザルトUI用のテクスチャ数
#define SCORETEX_SIZE_X	120.0f
#define SCORETEX_SIZE_Y	175.0f


typedef enum
{
	RESULT_SCORE_SET = 0,
	RESULT_SERECT_SET,
	RESULT_MAX
}RESULT_SETC;

enum
{
	RESULT_TEX_GAMECLEAR = 0,
	RESULT_TEX_NOWSCORE,
	RESULT_TEX_HIGHSCORE,
};

//テクスチャ列挙
static const char* ResultTex[RESULT_USE_TEX]
{
	"data\\TEXTURE\\result\\result_Gameclear.png",		//うしろ！
	"data\\TEXTURE\\result\\nowscore.png",				//今回のスコア
	"data\\TEXTURE\\result\\highscore.png",				//最高スコア
};

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fHeight;
	float fWidth;
	float fAngle;
	float fLength;
	int Type;
}RESULT_POLY;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fHeight;
	float fWidth;
	float fAngle;
	float fLength;
}RESULT_SCORE;

typedef struct
{
	int nScore;
	D3DXVECTOR3 pos;
	RESULT_SCORE Number[MAX_NUMBER_STR];
}SCORE_OFFSET;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResult[RESULT_USE_TEX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
//数字テクスチャ用
LPDIRECT3DTEXTURE9 g_pTextureResultNumber = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultNumber = NULL;

RESULT_POLY g_ResultStr[RESULT_USE_TEX];
SCORE_OFFSET g_ResultScore[MAX_SCORE_STR];

void InitResultScore(void);
void UninitResultScore(void);
void UpdateResultScore(void);
void DrawResultScore(void);
void SetResultScore(void);
void SetPosResultScore(int Num,D3DXVECTOR3 pos);
void EditResultData(void);

//===============================================================================
//リザルトの初期化処理
//===============================================================================
void InitResult(void)
{
	PlaySound(SOUND_LABEL_RESULT_RANKING_BGM);
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	for (int i = 0; i < RESULT_USE_TEX; i++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			ResultTex[i],
			&g_pTextureResult[i]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RESULT_USE_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	for (int i = 0; i < RESULT_USE_TEX; i++)
	{
		switch (i)
		{
		case RESULT_TEX_GAMECLEAR:
			g_ResultStr[i].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0);
			g_ResultStr[i].fWidth = SCREEN_WIDTH;
			g_ResultStr[i].fHeight = SCREEN_HEIGHT;
			g_ResultStr[i].Type = i;
			break;
		case RESULT_TEX_NOWSCORE:
			g_ResultStr[i].pos = D3DXVECTOR3(500.0f, 500.0f, 0);
			g_ResultStr[i].fWidth  = 750;
			g_ResultStr[i].fHeight = 250;
			g_ResultStr[i].Type = i;
			break;
		case RESULT_TEX_HIGHSCORE:
			g_ResultStr[i].pos = D3DXVECTOR3(600.0f, 700.0f, 0);
			g_ResultStr[i].fWidth  = 750;
			g_ResultStr[i].fHeight = 250;
			g_ResultStr[i].Type = i;
			break;
		}
		g_ResultStr[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//一応初期化
		g_ResultStr[i].fAngle = atan2f(g_ResultStr[i].fWidth, g_ResultStr[i].fHeight);
		g_ResultStr[i].fLength = sqrtf(g_ResultStr[i].fWidth * g_ResultStr[i].fWidth + g_ResultStr[i].fHeight * g_ResultStr[i].fHeight) / 2;
	}

	VERTEX_2D* pVtx;	//頂点情報のポインタ

	//頂点バッファをロックして、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int n = 0; n < RESULT_USE_TEX; n++)
	{
		//頂点座標の設定
		pVtx[0].pos.x = g_ResultStr[n].pos.x + sinf(g_ResultStr[n].rot.z - (D3DX_PI - g_ResultStr[n].fAngle)) * g_ResultStr[n].fLength;
		pVtx[0].pos.y = g_ResultStr[n].pos.y + cosf(g_ResultStr[n].rot.z - (D3DX_PI - g_ResultStr[n].fAngle)) * g_ResultStr[n].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_ResultStr[n].pos.x + sinf(g_ResultStr[n].rot.z + (D3DX_PI - g_ResultStr[n].fAngle)) * g_ResultStr[n].fLength;
		pVtx[1].pos.y = g_ResultStr[n].pos.y + cosf(g_ResultStr[n].rot.z + (D3DX_PI - g_ResultStr[n].fAngle)) * g_ResultStr[n].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_ResultStr[n].pos.x + sinf(g_ResultStr[n].rot.z - g_ResultStr[n].fAngle) * g_ResultStr[n].fLength;
		pVtx[2].pos.y = g_ResultStr[n].pos.y + cosf(g_ResultStr[n].rot.z - g_ResultStr[n].fAngle) * g_ResultStr[n].fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_ResultStr[n].pos.x + sinf(g_ResultStr[n].rot.z + g_ResultStr[n].fAngle) * g_ResultStr[n].fLength;
		pVtx[3].pos.y = g_ResultStr[n].pos.y + cosf(g_ResultStr[n].rot.z + g_ResultStr[n].fAngle) * g_ResultStr[n].fLength;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffResult->Unlock();	

	InitResultScore();

	EditResultData();

	SetResultScore();

	SetPosResultScore(0, {1650.0f,500.0f,0.0f});
	SetPosResultScore(1, {1650.0f,700.0f,0.0f});

	//フェードイン処理
	SetFade(FADE_IN, MODE_MAX);//フェードイン時は二個目の引数無視されるのでなんでもいい
}

//===============================================================================
//リザルトの終了処理
//===============================================================================
void UninitResult(void)
{
	StopSound();
	for (int i = 0; i < RESULT_USE_TEX; i++)
	{
		//テクスチャの破棄
		if (g_pTextureResult[i] != NULL)
		{					
			g_pTextureResult[i]->Release();
			g_pTextureResult[i] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
	UninitResultScore();
}


//===============================================================================
//リザルトの更新処理
//===============================================================================
void UpdateResult(void)
{
	UpdateResultScore();
	if (GetJoypadTrigger(JOYKEY_A,0) == true || GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//フェードアウト処理
		SetFade(FADE_OUT, MODE_TITLE);//二つ目に移行先
	}
}


//===============================================================================
//リザルトの描画処理
//===============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int i = 0; i < RESULT_USE_TEX; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResult[g_ResultStr[i].Type]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * i,
			2);
	}
	DrawResultScore();
}

//===============================================================================
//リザルトのスコア初期化処理
//===============================================================================
void InitResultScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\result\\Number001.png",	
		&g_pTextureResultNumber);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RESULT_USE_POLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultNumber,
		NULL);

	for (int i = 0; i < MAX_SCORE_STR; i++)
	{
		g_ResultScore[i].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0);
		g_ResultScore[i].nScore = 0;
		for (int j = 0; j < MAX_NUMBER_STR; j++)
		{
			g_ResultScore[i].Number[j].rot = { 0.0f,0.0f,0.0f };
			g_ResultScore[i].Number[j].fWidth  = SCORETEX_SIZE_X;
			g_ResultScore[i].Number[j].fHeight = SCORETEX_SIZE_Y;
			g_ResultScore[i].Number[j].fAngle  = atan2f(g_ResultScore[i].Number[j].fWidth,g_ResultScore[i].Number[j].fHeight);
			g_ResultScore[i].Number[j].fLength = sqrtf(g_ResultScore[i].Number[j].fWidth *g_ResultScore[i].Number[j].fWidth + g_ResultScore[i].Number[j].fHeight * g_ResultScore[i].Number[j].fHeight) / 2;
			g_ResultScore[i].Number[j].pos = { g_ResultScore[i].pos.x - g_ResultScore[i].Number[j].fWidth * 0.5f, g_ResultScore[i].pos.y,g_ResultScore[i].pos.z };
		}
	}
	VERTEX_2D* pVtx;	//頂点情報のポインタ
	
	//頂点バッファをロックして、頂点情報へのポインタを取得
	g_pVtxBuffResultNumber->Lock(0, 0, (void**)&pVtx, 0);

	for (int n = 0; n < MAX_SCORE_STR; n++)
	{
		for (int m = 0; m < MAX_NUMBER_STR; m++)
		{
			//頂点座標の設定
			pVtx[0].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z - (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[0].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z - (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z + (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[1].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z + (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z - g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[2].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z - g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z + g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[3].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z + g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[3].pos.z = 0.0f;

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffResultNumber->Unlock();

}

//===============================================================================
//リザルトのスコア終了処理
//===============================================================================
void UninitResultScore(void)
{
	//テクスチャの破棄
	if (g_pTextureResultNumber != NULL)
	{
		g_pTextureResultNumber->Release();
		g_pTextureResultNumber = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResultNumber != NULL)
	{
		g_pVtxBuffResultNumber->Release();
		g_pVtxBuffResultNumber = NULL;
	}
}

//===============================================================================
//リザルトのスコア更新処理
//===============================================================================
void UpdateResultScore(void)
{
	VERTEX_2D* pVtx;	//頂点情報のポインタ

	//頂点バッファをロックして、頂点情報へのポインタを取得
	g_pVtxBuffResultNumber->Lock(0, 0, (void**)&pVtx, 0);

	for (int n = 0; n < MAX_SCORE_STR; n++)
	{
		for (int m = 0; m < MAX_NUMBER_STR; m++)
		{
			//頂点座標の設定
			pVtx[0].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z - (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[0].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z - (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z + (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[1].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z + (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z - g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[2].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z - g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z + g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[3].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z + g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[3].pos.z = 0.0f;

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



			pVtx += 4;
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffResultNumber->Unlock();
}

//===============================================================================
//リザルトの描画処理
//===============================================================================
void DrawResultScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResultNumber, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int i = 0; i < RESULT_USE_POLY; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureResultNumber);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * i,
			2);
	}
}

//===============================================================================
//リザルトのスコアを反映する処理
//===============================================================================
void SetResultScore(void)
{
	int PosTex[2][8];
	
	int nScore[2];
	for (int i = 0; i < MAX_SCORE_STR; i++)
	{
		int nType = 1;
		nScore[i] = g_ResultScore[i].nScore;
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			nType *= 10;
			PosTex[i][nCnt] = (nScore[i] % nType * 10) / nType;
		}
	}

	VERTEX_2D* pVtx;
	g_pVtxBuffResultNumber->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < MAX_SCORE_STR; i++)
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.1f * (PosTex[i][nCnt] + 1) - 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * (PosTex[i][nCnt] + 1), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * (PosTex[i][nCnt] + 1) - 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * (PosTex[i][nCnt] + 1), 1.0f);

			pVtx += 4;
		}
	}
	g_pVtxBuffResultNumber->Unlock();
}

//===============================================================================
//リザルトのスコア座標設定処理
//===============================================================================
void SetPosResultScore(int Num, D3DXVECTOR3 pos)
{
	int i = Num;
	g_ResultScore[i].pos = pos;
	for (int j = 0; j < MAX_NUMBER_STR; j++)
	{
		g_ResultScore[i].Number[j].rot = { 0.0f,0.0f,0.0f };
		g_ResultScore[i].Number[j].fWidth = SCORETEX_SIZE_X;
		g_ResultScore[i].Number[j].fHeight = SCORETEX_SIZE_Y;
		g_ResultScore[i].Number[j].fAngle = atan2f(g_ResultScore[i].Number[j].fWidth, g_ResultScore[i].Number[j].fHeight);
		g_ResultScore[i].Number[j].fLength = sqrtf(g_ResultScore[i].Number[j].fWidth * g_ResultScore[i].Number[j].fWidth + g_ResultScore[i].Number[j].fHeight * g_ResultScore[i].Number[j].fHeight) / 2;
		g_ResultScore[i].Number[j].pos = D3DXVECTOR3((g_ResultScore[i].pos.x - g_ResultScore[i].Number[j].fWidth* 0.75f * j), g_ResultScore[i].pos.y,g_ResultScore[i].pos.z);
	}
}

//===============================================================================
//リザルトのスコアデータの取得処理
//===============================================================================
void EditResultData(void)
{
	int *Score = GetInfoScore();
	g_ResultScore[0].nScore = *Score;

	FILE* pFile;
	pFile = fopen("data\\TXT\\SCORE\\Ranking.txt", "r");
	if (pFile != NULL)
	{	
		fscanf(pFile, "%d", &g_ResultScore[1].nScore);
		fclose(pFile);

	}
	else
	{
		return;
	}
}