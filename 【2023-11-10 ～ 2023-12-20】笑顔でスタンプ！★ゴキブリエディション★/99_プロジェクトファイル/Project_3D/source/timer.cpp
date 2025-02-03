//************************************************
//
//制限時間処理[timer.cpp]	(レガシー)
//Author：福田歩希
//
//************************************************
#include "timer.h"

#include "fade.h"
#include "input.h"
#include "sound.h"

//タイマー関連構造体
typedef struct
{
	int nTime;			//実際の残り時間
	int nHold;			//残り時間情報コピー
	int nCntDecrease;	//残り時間を減らすフレームカウント
	int nCntWait;		//ぐちゃぐちゃのヤツ(アニメーション)
	int nCntInversion;	//反転する時間カウント
	int nCntReInversion;//再反転する時間カウント
	bool bInversion;	//反転判定
	bool bReInversion;	//再反転判定
}TIMER;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Timer[AMOUNT_TEXTURE_TIMER] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Timer = NULL;	//頂点バッファのポインタ
float g_fMoveX_Timer = 0.0f;	//数字ポリゴン移動量
int g_nTimer[AMOUNT_POLYGON_TIMER] = {};	//画面表示用振り分け
TIMER g_Timer;	//タイマー関連情報

static const float g_AdjustY = 15.0f;

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Timer(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLACK_TIMER,
		&g_pTexture_Timer[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NUMBER_TIMER,
		&g_pTexture_Timer[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NUMBER_SUB_TIMER,
		&g_pTexture_Timer[2]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CLOCK_TIMER,
		&g_pTexture_Timer[3]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TIMER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Timer,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Timer;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Timer->Lock(0, 0, (void**)&pVtx_Timer, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TIMER; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Timer[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Timer[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Timer[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Timer[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Timer[0].rhw = 1.0f;
		pVtx_Timer[1].rhw = 1.0f;
		pVtx_Timer[2].rhw = 1.0f;
		pVtx_Timer[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Timer[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Timer[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Timer[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Timer[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Timer[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Timer[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Timer[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Timer[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Timer += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Timer->Unlock();

	//移動量をリセット
	g_fMoveX_Timer = 0.0f;

	//振り分けをリセット
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TIMER; nCnt++)
	{
		g_nTimer[nCnt] = 0;
	}

	//タイマー系情報初期設定
	g_Timer.nTime = REMAIN_TIMER;
	g_Timer.nHold = 0;
	g_Timer.nCntDecrease = AMOUNT_CNT_MAX_TIMER - 1;
	g_Timer.nCntWait = 0;
	g_Timer.nCntInversion = 0;
	g_Timer.nCntReInversion = 0;
	g_Timer.bInversion = false;
	g_Timer.bReInversion = false;

	//頂点の展開と、制限時間の設定
	SetPos_Vtx_Timer();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Timer(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_TIMER; nCnt++)
	{
		if (g_pTexture_Timer[nCnt] != NULL)
		{
			g_pTexture_Timer[nCnt]->Release();
			g_pTexture_Timer[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Timer != NULL)
	{
		g_pVtxBuff_Timer->Release();
		g_pVtxBuff_Timer = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Timer(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Timer;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Timer->Lock(0, 0, (void**)&pVtx_Timer, 0);

	//残り時間減少用カウント
	g_Timer.nCntDecrease++;

	pVtx_Timer += AMOUNT_VTX * 6;

	if (g_Timer.nTime > 0)
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			//適当に数字を動かす
			if (g_Timer.nCntWait < 5)
			{
				g_Timer.nCntWait++;
			}
			else
			{
				g_nTimer[6 - nCnt] = rand() % 10;
			}

			//振り分けをベースにテクスチャ座標を変更
			pVtx_Timer[0].tex.x = MOVE_SPAN_TEX_TIMER * g_nTimer[6 - nCnt];
			pVtx_Timer[1].tex.x = MOVE_SPAN_TEX_TIMER * (g_nTimer[6 - nCnt] + 1);
			pVtx_Timer[2].tex.x = MOVE_SPAN_TEX_TIMER * g_nTimer[6 - nCnt];
			pVtx_Timer[3].tex.x = MOVE_SPAN_TEX_TIMER * (g_nTimer[6 - nCnt] + 1);

			pVtx_Timer -= AMOUNT_VTX;
		}
	}

	//計算用に、今の時間を取得
	g_Timer.nHold = g_Timer.nTime;

	int nMinute = g_Timer.nHold / 60;

	//時間を分とかに変換する
	g_Timer.nHold += (40 * nMinute);

	//桁ごとに振り分ける
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//配列の4 - nCnt番目に1の位の数値を振り分ける
		g_nTimer[4 - nCnt] = g_Timer.nHold % 10;

		//位を下げる
		g_Timer.nHold /= 10;

		//振り分けをベースにテクスチャ座標を変更
		pVtx_Timer[0].tex.x = MOVE_SPAN_TEX_TIMER * g_nTimer[4 - nCnt];
		pVtx_Timer[1].tex.x = MOVE_SPAN_TEX_TIMER * (g_nTimer[4 - nCnt] + 1);
		pVtx_Timer[2].tex.x = MOVE_SPAN_TEX_TIMER * g_nTimer[4 - nCnt];
		pVtx_Timer[3].tex.x = MOVE_SPAN_TEX_TIMER * (g_nTimer[4 - nCnt] + 1);

		pVtx_Timer -= AMOUNT_VTX;
	}

	//フレームカウントが一定に達すると
	if (g_Timer.nCntDecrease >= AMOUNT_CNT_MAX_TIMER && g_Timer.nTime > 0)
	{
		//1秒減る
		g_Timer.nTime--;

		g_Timer.nCntDecrease = 0;

		//時間経過でスクロール反転
		if (g_Timer.nCntInversion < INVERSION_TIMER)
		{
			g_Timer.nCntInversion++;
		}
		else
		{
			g_Timer.bInversion = true;
		}

		//時間経過でスクロール再反転
		if (g_Timer.nCntReInversion < REINVERSION_TIMER)
		{
			g_Timer.nCntReInversion++;
		}
		else
		{
			g_Timer.bReInversion = true;
		}
	}

	if (GetKeyboardTrigger(DIK_9) == true)
	{
		//ザ・ワールド
		g_Timer.nTime = 0;
	}

	//時間切れ
	if (g_Timer.nTime <= 0)
	{
		//フェード情報用
		FADE* pFade = GetInfoFade();

		//フェードアウト開始
		pFade->bFadeIn = false;
		pFade->bFadeOut = true;
	}
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Timer(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Timer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TIMER; nCnt++)
	{
		if (nCnt == 0)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexture_Timer[0]);
		}
		else if (nCnt >= 1 && nCnt <= 6)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexture_Timer[1]);
		}
		else if (nCnt == 7 || nCnt == 8)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexture_Timer[2]);
		}
		else
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexture_Timer[3]);
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//数字とか配置用処理関数
//************************************************
void SetPos_Vtx_Timer(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Timer;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Timer->Lock(0, 0, (void**)&pVtx_Timer, 0);

	//黒い棒をその辺に配置
	pVtx_Timer[0].pos = D3DXVECTOR3(0.0f, 20.0f + g_AdjustY, 0.0f);
	pVtx_Timer[1].pos = D3DXVECTOR3(365.0f, 20.0f + g_AdjustY, 0.0f);
	pVtx_Timer[2].pos = D3DXVECTOR3(0.0f, 100.0f + g_AdjustY, 0.0f);
	pVtx_Timer[3].pos = D3DXVECTOR3(340.0f, 100.0f + g_AdjustY, 0.0f);

	//頂点カラーの設定
	pVtx_Timer[0].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx_Timer[1].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx_Timer[2].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx_Timer[3].col = D3DCOLOR_RGBA(255, 255, 255, 150);

	//数字へ
	pVtx_Timer += AMOUNT_VTX;

	//数字分
	for (int nCnt = 0, nCntNumber = 0; nCnt < AMOUNT_USING_POLYGON_NUMBER_TIMER; nCnt++, nCntNumber++)
	{
		//時間をその辺に配置
		pVtx_Timer[0].pos = D3DXVECTOR3(85.0f + g_fMoveX_Timer, 40.0f + g_AdjustY, 0.0f);
		pVtx_Timer[1].pos = D3DXVECTOR3(145.0f + g_fMoveX_Timer, 40.0f + g_AdjustY, 0.0f);
		pVtx_Timer[2].pos = D3DXVECTOR3(85.0f + g_fMoveX_Timer, 80.0f + g_AdjustY, 0.0f);
		pVtx_Timer[3].pos = D3DXVECTOR3(145.0f + g_fMoveX_Timer, 80.0f + g_AdjustY, 0.0f);

		//毎回右にずれる
		g_fMoveX_Timer += DISTANCESPAN_POLYGON_TIMER;

		//なお2回に1回多めに幅を取る
		if (nCntNumber % 2 == 1)
		{
			g_fMoveX_Timer += MORE_DISTANCESPAN_POLYGON_TIMER;
		}

		//テクスチャ座標の設定
		pVtx_Timer[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Timer[1].tex = D3DXVECTOR2(TEX_U_RIGHT_TIMER, 0.0f);
		pVtx_Timer[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Timer[3].tex = D3DXVECTOR2(TEX_U_RIGHT_TIMER, 1.0f);

		pVtx_Timer += AMOUNT_VTX;
	}

	g_fMoveX_Timer = 0;

	//記号分
	for (int nCnt = 0, nCntNumber = 0; nCnt < AMOUNT_USING_POLYGON_SYMBOL_TIMER; nCnt++, nCntNumber++)
	{
		//記号をその辺に配置
		pVtx_Timer[0].pos = D3DXVECTOR3(142.5f + g_fMoveX_Timer, 45.0f + g_AdjustY, 0.0f);
		pVtx_Timer[1].pos = D3DXVECTOR3(192.5f + g_fMoveX_Timer, 45.0f + g_AdjustY, 0.0f);
		pVtx_Timer[2].pos = D3DXVECTOR3(142.5f + g_fMoveX_Timer, 80.0f + g_AdjustY, 0.0f);
		pVtx_Timer[3].pos = D3DXVECTOR3(192.5f + g_fMoveX_Timer, 80.0f + g_AdjustY, 0.0f);

		//毎回右にずれる
		g_fMoveX_Timer += DISTANCESPAN_POLYGON_SYMBOL_TIMER;

		if (nCnt == 0)
		{
			//テクスチャ座標の設定
			pVtx_Timer[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_Timer[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx_Timer[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx_Timer[3].tex = D3DXVECTOR2(0.5f, 1.0f);
		}
		else
		{
			//テクスチャ座標の設定
			pVtx_Timer[0].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx_Timer[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx_Timer[2].tex = D3DXVECTOR2(0.5f, 1.0f);
			pVtx_Timer[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		pVtx_Timer += AMOUNT_VTX;
	}

	//時計をその辺に配置
	pVtx_Timer[0].pos = D3DXVECTOR3(25.0f, 35.0f + g_AdjustY, 0.0f);
	pVtx_Timer[1].pos = D3DXVECTOR3(75.0f, 35.0f + g_AdjustY, 0.0f);
	pVtx_Timer[2].pos = D3DXVECTOR3(25.0f, 85.0f + g_AdjustY, 0.0f);
	pVtx_Timer[3].pos = D3DXVECTOR3(75.0f, 85.0f + g_AdjustY, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Timer->Unlock();
}

//************************************************
//制限時間情報のアドレスを渡す関数
//************************************************
int* Getinfo_Timer(void)
{
	return &g_Timer.nTime;	//残り時間情報を引き渡す
}

//************************************************
//反転判定のアドレスを渡す関数
//************************************************
bool* Getinfo_Inversion_Timer(void)
{
	return &g_Timer.bInversion;
}

//************************************************
//再反転判定のアドレスを渡す関数
//************************************************
bool* Getinfo_ReInversion_Timer(void)
{
	return &g_Timer.bReInversion;
}