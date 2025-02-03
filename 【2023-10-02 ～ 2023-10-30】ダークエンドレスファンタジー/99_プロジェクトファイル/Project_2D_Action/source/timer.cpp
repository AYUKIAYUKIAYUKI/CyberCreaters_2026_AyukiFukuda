//************************************************
//
//制限時間処理[timer.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "input.h"
#include "timer.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Timer = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Timer = NULL;	//頂点バッファのポインタ
TIMER g_aTimer[AMOUNT_POLYGON_TIMER];	//タイマー表示用
int g_nTimer = 0;	//タイマー
int g_nFrameCnt = 0;	//フレームカウント

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
		TEXTURE_TIMER,
		&g_pTexture_Timer);

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

	//タイマー表示用クリア
	for (int i = 0; i < AMOUNT_POLYGON_TIMER; i++)
	{
		g_aTimer[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTimer[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTimer[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTimer[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aTimer[i].nCntTex = 0;
		g_aTimer[i].nCntPattern = 0;
		for (int ii = 0; ii < AMOUNT_POLYGON_TIMER; ii++)
		{
			g_aTimer[i].fTexSpan[ii] = 0.0f;
			g_aTimer[i].fRadius[ii] = 0.0f;
			g_aTimer[i].fLength[ii] = 0.0f;
			g_aTimer[i].fAngle[ii] = 0.0f;
		}
	}

	//タイマークリア
	g_nTimer = 0;

	//フレームクリア
	g_nFrameCnt = 0;

	//タイマーに情報を付与
	SetInfo_Timer();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Timer(void)
{
	//テクスチャの破棄
	if (g_pTexture_Timer != NULL)
	{
		g_pTexture_Timer->Release();
		g_pTexture_Timer = NULL;
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
	//60フレーム経過で1秒減らす
	g_nFrameCnt++;
	if (g_nFrameCnt >= 60)
	{
		g_nFrameCnt = 0;
		g_nTimer--;
	}

	//展開
	Update_Pos_Timer();
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
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexture_Timer);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//タイマー表示用にデータを付与する関数
//************************************************
void SetInfo_Timer(void)
{
	//タイマーセット
	g_nTimer = 90;

	for (int i = 0; i < AMOUNT_POLYGON_TIMER; i++)
	{
		g_aTimer[i].pos = D3DXVECTOR3(100.0f + (55.0f * i), 100.0f, 0.0f);
		if (i > 1)
		{
			g_aTimer[i].pos.x += 40.0f;
		}
		g_aTimer[i].fTexSpan[0] = 0.0f;
		g_aTimer[i].fTexSpan[1] = 0.1f;
		g_aTimer[i].fRadius[0] = 25.0f;
		g_aTimer[i].fRadius[1] = 45.0f;
		g_aTimer[i].fLength[0] = sqrtf((g_aTimer[i].fRadius[0] * g_aTimer[i].fRadius[0]) + (g_aTimer[i].fRadius[1] * g_aTimer[i].fRadius[1]));
		g_aTimer[i].fLength[1] = g_aTimer[i].fLength[0];
		g_aTimer[i].fAngle[0] = atan2f(g_aTimer[i].fRadius[0] * 2.0f, g_aTimer[i].fRadius[1] * 2.0f);
		g_aTimer[i].fAngle[1] = g_aTimer[i].fAngle[0];
	}
}

//************************************************
//タイマー表示用にバーテックスを更新関数
//************************************************
void Update_Pos_Timer(void)
{
	//テクスチャを更新
	Update_Tex_Timer();

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Timer;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Timer->Lock(0, 0, (void**)&pVtx_Timer, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TIMER; i++)
	{
		pVtx_Timer[0].pos.x = g_aTimer[i].pos.x + sinf(g_aTimer[i].rot.z - (D3DX_PI - g_aTimer[i].fAngle[0])) * g_aTimer[i].fLength[0];
		pVtx_Timer[0].pos.y = g_aTimer[i].pos.y + cosf(g_aTimer[i].rot.z - (D3DX_PI - g_aTimer[i].fAngle[0])) * g_aTimer[i].fLength[0];
		pVtx_Timer[1].pos.x = g_aTimer[i].pos.x + sinf(g_aTimer[i].rot.z + (D3DX_PI - g_aTimer[i].fAngle[0])) * g_aTimer[i].fLength[0];
		pVtx_Timer[1].pos.y = g_aTimer[i].pos.y + cosf(g_aTimer[i].rot.z + (D3DX_PI - g_aTimer[i].fAngle[0])) * g_aTimer[i].fLength[0];
		pVtx_Timer[2].pos.x = g_aTimer[i].pos.x + sinf(g_aTimer[i].rot.z - g_aTimer[i].fAngle[1]) * g_aTimer[i].fLength[1];
		pVtx_Timer[2].pos.y = g_aTimer[i].pos.y + cosf(g_aTimer[i].rot.z - g_aTimer[i].fAngle[1]) * g_aTimer[i].fLength[1];
		pVtx_Timer[3].pos.x = g_aTimer[i].pos.x + sinf(g_aTimer[i].rot.z + g_aTimer[i].fAngle[1]) * g_aTimer[i].fLength[1];
		pVtx_Timer[3].pos.y = g_aTimer[i].pos.y + cosf(g_aTimer[i].rot.z + g_aTimer[i].fAngle[1]) * g_aTimer[i].fLength[1];

		pVtx_Timer += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Timer->Unlock();
}

//************************************************
//タイマー表示用にテクスチャを更新関数
//************************************************
void Update_Tex_Timer(void)
{
	//テクスチャの幅をタイムから算出
	Calc_Tex_Timer();

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Timer;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Timer->Lock(0, 0, (void**)&pVtx_Timer, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TIMER; i++)
	{
		pVtx_Timer[0].tex = D3DXVECTOR2(g_aTimer[i].fTexSpan[0], 0.0f);
		pVtx_Timer[1].tex = D3DXVECTOR2(g_aTimer[i].fTexSpan[1], 0.0f);
		pVtx_Timer[2].tex = D3DXVECTOR2(g_aTimer[i].fTexSpan[0], 1.0f);
		pVtx_Timer[3].tex = D3DXVECTOR2(g_aTimer[i].fTexSpan[1], 1.0f);

		pVtx_Timer += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Timer->Unlock();
}

//************************************************
//タイマーからにテクスチャ幅を計算関数
//************************************************
void Calc_Tex_Timer(void)
{
	//時間を取得
	int nHold = g_nTimer;

	//分と秒を分ける
	int nMinute = nHold / 60;
	nHold += (40 * nMinute);

	//計算する
	for (int i = 0; i < AMOUNT_POLYGON_TIMER; i++)
	{
		//1の位の数値を抜き出す
		int nNumber = nHold % 10;

		//抜き出た数字から幅をセット
		g_aTimer[(AMOUNT_POLYGON_TIMER - 1) - i].fTexSpan[0] = 0.0f + (0.1f * nNumber);
		g_aTimer[(AMOUNT_POLYGON_TIMER - 1) - i].fTexSpan[1] = 0.1f + (0.1f * nNumber);

		//スコアの桁をずらす
		nHold /= 10;
	}
}

//************************************************
//タイマー表示用のアドレスを渡す
//************************************************
TIMER* GetInfo_TIMER(void)
{
	return &g_aTimer[0];
}

//************************************************
//タイマーのアドレスを渡す
//************************************************
int* GetInfo_Timer(void)
{
	return &g_nTimer;
}