//************************************************
//
//守護対象ゲージ処理[gauge_tower.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "gauge_tower.h"
#include "tower.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Gauge_Tower[AMOUNT_TEX_GAUGE_TOWER] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Gauge_Tower = NULL;	//頂点バッファのポインタ
GAUGE_TOWER g_aGauge_Tower[AMOUNT_POLYGON_GAUGE_TOWER];	//守護対象ゲージ情報
static int g_nHold;	//汎用整数保管用

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Gauge_Tower()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GAUGE_TOWER,
		&g_pTexture_Gauge_Tower[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GAUGE_HEART,
		&g_pTexture_Gauge_Tower[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_GAUGE_TOWER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Gauge_Tower,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Gauge_Tower;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Gauge_Tower->Lock(0, 0, (void**)&pVtx_Gauge_Tower, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAUGE_TOWER; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Gauge_Tower[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Gauge_Tower[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Gauge_Tower[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Gauge_Tower[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Gauge_Tower[0].rhw = 1.0f;
		pVtx_Gauge_Tower[1].rhw = 1.0f;
		pVtx_Gauge_Tower[2].rhw = 1.0f;
		pVtx_Gauge_Tower[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Gauge_Tower[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Gauge_Tower[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Gauge_Tower[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Gauge_Tower[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx_Gauge_Tower[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Gauge_Tower[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Gauge_Tower[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Gauge_Tower[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Gauge_Tower += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Gauge_Tower->Unlock();

	//守護対象ゲージ構造体の情報の初期化群
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAUGE_TOWER; nCnt++)
	{
		g_aGauge_Tower[nCnt].nStyle = 0;
		g_aGauge_Tower[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge_Tower[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge_Tower[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge_Tower[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aGauge_Tower[nCnt].nCntTex = 0;
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aGauge_Tower[nCnt].fTexSpan[nCnt2] = 0.0f;
			g_aGauge_Tower[nCnt].fRadius[nCnt2] = 0.0f;
			g_aGauge_Tower[nCnt].fLength[nCnt2] = 0.0f;
			g_aGauge_Tower[nCnt].fAngle[nCnt2] = 0.0f;
		}
	}

	g_nHold = AMOUNT_MAX_LIFE_TOWER;

	//守護対象ゲージ構造体に情報を付与
	SetInfo_Gauge_Tower();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Gauge_Tower(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEX_GAUGE_TOWER; nCnt++)
	{
		if (g_pTexture_Gauge_Tower[nCnt] != NULL)
		{
			g_pTexture_Gauge_Tower[nCnt]->Release();
			g_pTexture_Gauge_Tower[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Gauge_Tower != NULL)
	{
		g_pVtxBuff_Gauge_Tower->Release();
		g_pVtxBuff_Gauge_Tower = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Gauge_Tower(void)
{
	TOWER* pTower = GetInfo_Tower();

	//移動など
	Update_Pos_Gauge_Tower();

	//テクスチャアニメーション
	Update_Tex_Gauge_Tower();

	//カラー変更
	Update_Col_Gauge_Tower();

	//前回の守護対象を保持
	g_nHold = pTower->nLife;
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Gauge_Tower(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Gauge_Tower, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAUGE_TOWER; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexture_Gauge_Tower[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//守護対象ゲージ構造体の情報を設定する関数
//************************************************
void SetInfo_Gauge_Tower(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAUGE_TOWER; nCnt++)
	{
		g_aGauge_Tower[nCnt].nStyle = nCnt;
		g_aGauge_Tower[nCnt].pos = D3DXVECTOR3(800.0f - (nCnt * SPAN_EACH_GAUGE_TOWER_X), 110.0f - (nCnt * SPAN_EACH_GAUGE_TOWER_Y), 0.0f);
		g_aGauge_Tower[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		switch (g_aGauge_Tower[nCnt].nStyle)
		{
		case GAUGE_TOWER_STYLE_GAUGE:
			g_aGauge_Tower[nCnt].fTexSpan[0] = 0.0f;
			g_aGauge_Tower[nCnt].fTexSpan[1] = SPAN_CHANGE_TEX_GAUGE_TOWER;
			g_aGauge_Tower[nCnt].fRadius[0] = RADIUS_GAUGE_TOWER_X;	//守護対象ゲージ横半幅
			g_aGauge_Tower[nCnt].fRadius[1] = RADIUS_GAUGE_TOWER_Y;	//守護対象ゲージ縦半幅
			for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
			{
				g_aGauge_Tower[nCnt].fLength[nCnt2] = sqrtf((g_aGauge_Tower[nCnt].fRadius[0] * g_aGauge_Tower[nCnt].fRadius[0]) + (g_aGauge_Tower[nCnt].fRadius[1] * g_aGauge_Tower[nCnt].fRadius[1]));
				g_aGauge_Tower[nCnt].fAngle[nCnt2] = atan2f(g_aGauge_Tower[nCnt].fRadius[0] * 2.0f, g_aGauge_Tower[nCnt].fRadius[1] * 2.0f);
			}
			break;
		case GAUGE_TOWER_STYLE_HEART:
			g_aGauge_Tower[nCnt].fTexSpan[0] = 0.0f;
			g_aGauge_Tower[nCnt].fTexSpan[1] = 1.0f;
			g_aGauge_Tower[nCnt].fRadius[0] = RADIUS_GAUGE_HEART_X;	//守護対象ハート横半幅
			g_aGauge_Tower[nCnt].fRadius[1] = RADIUS_GAUGE_HEART_Y;	//守護対象ハート縦半幅
			for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
			{
				g_aGauge_Tower[nCnt].fLength[nCnt2] = sqrtf((g_aGauge_Tower[nCnt].fRadius[0] * g_aGauge_Tower[nCnt].fRadius[0]) + (g_aGauge_Tower[nCnt].fRadius[1] * g_aGauge_Tower[nCnt].fRadius[1]));
				g_aGauge_Tower[nCnt].fAngle[nCnt2] = atan2f(g_aGauge_Tower[nCnt].fRadius[0] * 2.0f, g_aGauge_Tower[nCnt].fRadius[1] * 2.0f);
			}
			break;
		}
	}
}

//************************************************
//守護対象ゲージの位置を設定する関数
//************************************************
void Update_Pos_Gauge_Tower(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Gauge_Tower;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Gauge_Tower->Lock(0, 0, (void**)&pVtx_Gauge_Tower, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAUGE_TOWER; nCnt++)
	{
		//色の変更期間に乗じてこちらも微振動
		if (g_aGauge_Tower[nCnt].nCntTex > 0)
		{
			//適当に位置を変更
			int X = rand() % 25, Y = rand() % 25, RX = rand() % 2, RY = rand() % 2;
			//上下左右の移動もランダムに反転
			RX == 0 ? 0 : X *= -1;
			RY == 0 ? 0 : Y *= -1;
			g_aGauge_Tower[nCnt].pos = D3DXVECTOR3(800.0f - (nCnt * SPAN_EACH_GAUGE_TOWER_X) + X, 110.0f - (nCnt * SPAN_EACH_GAUGE_TOWER_Y) + Y, 0.0f);
		}
		//期間以外は定位置に
		else
		{
			g_aGauge_Tower[nCnt].pos = D3DXVECTOR3(800.0f - (nCnt * SPAN_EACH_GAUGE_TOWER_X), 110.0f - (nCnt * SPAN_EACH_GAUGE_TOWER_Y), 0.0f);
		}

		pVtx_Gauge_Tower[0].pos.x = g_aGauge_Tower[nCnt].pos.x + sinf(g_aGauge_Tower[nCnt].rot.z - (D3DX_PI - g_aGauge_Tower[nCnt].fAngle[0])) * g_aGauge_Tower[nCnt].fLength[0];
		pVtx_Gauge_Tower[0].pos.y = g_aGauge_Tower[nCnt].pos.y + cosf(g_aGauge_Tower[nCnt].rot.z - (D3DX_PI - g_aGauge_Tower[nCnt].fAngle[0])) * g_aGauge_Tower[nCnt].fLength[0];
		pVtx_Gauge_Tower[1].pos.x = g_aGauge_Tower[nCnt].pos.x + sinf(g_aGauge_Tower[nCnt].rot.z + (D3DX_PI - g_aGauge_Tower[nCnt].fAngle[0])) * g_aGauge_Tower[nCnt].fLength[0];
		pVtx_Gauge_Tower[1].pos.y = g_aGauge_Tower[nCnt].pos.y + cosf(g_aGauge_Tower[nCnt].rot.z + (D3DX_PI - g_aGauge_Tower[nCnt].fAngle[0])) * g_aGauge_Tower[nCnt].fLength[0];
		pVtx_Gauge_Tower[2].pos.x = g_aGauge_Tower[nCnt].pos.x + sinf(g_aGauge_Tower[nCnt].rot.z - g_aGauge_Tower[nCnt].fAngle[1]) * g_aGauge_Tower[nCnt].fLength[1];
		pVtx_Gauge_Tower[2].pos.y = g_aGauge_Tower[nCnt].pos.y + cosf(g_aGauge_Tower[nCnt].rot.z - g_aGauge_Tower[nCnt].fAngle[1]) * g_aGauge_Tower[nCnt].fLength[1];
		pVtx_Gauge_Tower[3].pos.x = g_aGauge_Tower[nCnt].pos.x + sinf(g_aGauge_Tower[nCnt].rot.z + g_aGauge_Tower[nCnt].fAngle[1]) * g_aGauge_Tower[nCnt].fLength[1];
		pVtx_Gauge_Tower[3].pos.y = g_aGauge_Tower[nCnt].pos.y + cosf(g_aGauge_Tower[nCnt].rot.z + g_aGauge_Tower[nCnt].fAngle[1]) * g_aGauge_Tower[nCnt].fLength[1];

		pVtx_Gauge_Tower += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Gauge_Tower->Unlock();
}

//************************************************
//ゲージの色を変更する関数
//************************************************
void Update_Col_Gauge_Tower(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Gauge_Tower;

	TOWER* pTower = GetInfo_Tower();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Gauge_Tower->Lock(0, 0, (void**)&pVtx_Gauge_Tower, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAUGE_TOWER; nCnt++)
	{
		//体力に変動があると
		if (g_nHold != pTower->nLife)
		{
			//変更期間を付与
			g_aGauge_Tower[nCnt].nCntTex = 8;
		}

		//期間中いい感じに明滅
		if (g_aGauge_Tower[nCnt].nCntTex > 0)
		{
			g_aGauge_Tower[nCnt].nCntTex--;

			if (g_aGauge_Tower[nCnt].nCntTex < 4)
			{
				g_aGauge_Tower[nCnt].col.r = 0.0f;
			}
			g_aGauge_Tower[nCnt].col.g = 0.0f;
			g_aGauge_Tower[nCnt].col.b = 0.0f;
		}
		//終わると戻る
		else
		{
			g_aGauge_Tower[nCnt].col.r = 1.0f;
			g_aGauge_Tower[nCnt].col.g = 1.0f;
			g_aGauge_Tower[nCnt].col.b = 1.0f;
		}

		pVtx_Gauge_Tower[0].col = g_aGauge_Tower[nCnt].col;
		pVtx_Gauge_Tower[1].col = g_aGauge_Tower[nCnt].col;
		pVtx_Gauge_Tower[2].col = g_aGauge_Tower[nCnt].col;
		pVtx_Gauge_Tower[3].col = g_aGauge_Tower[nCnt].col;

		pVtx_Gauge_Tower += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Gauge_Tower->Unlock();
}

//************************************************
//守護対象ゲージのテクスチャを動かす関数
//************************************************
void Update_Tex_Gauge_Tower(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Gauge_Tower;

	TOWER* pTower = GetInfo_Tower();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Gauge_Tower->Lock(0, 0, (void**)&pVtx_Gauge_Tower, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAUGE_TOWER; nCnt++)
	{
		if (g_aGauge_Tower[nCnt].nStyle == GAUGE_TOWER_STYLE_GAUGE)
		{
			g_aGauge_Tower[nCnt].fTexSpan[0] = 1.0f - (SPAN_CHANGE_TEX_GAUGE_TOWER * (pTower->nLife + 1));
			g_aGauge_Tower[nCnt].fTexSpan[1] = 1.0f - (SPAN_CHANGE_TEX_GAUGE_TOWER * pTower->nLife);
		}

		pVtx_Gauge_Tower[0].tex = D3DXVECTOR2(0.0f, g_aGauge_Tower[nCnt].fTexSpan[0]);
		pVtx_Gauge_Tower[1].tex = D3DXVECTOR2(1.0f, g_aGauge_Tower[nCnt].fTexSpan[0]);
		pVtx_Gauge_Tower[2].tex = D3DXVECTOR2(0.0f, g_aGauge_Tower[nCnt].fTexSpan[1]);
		pVtx_Gauge_Tower[3].tex = D3DXVECTOR2(1.0f, g_aGauge_Tower[nCnt].fTexSpan[1]);

		pVtx_Gauge_Tower += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Gauge_Tower->Unlock();
}

//************************************************
//守護対象ゲージ構造体のアドレスを渡す
//************************************************
GAUGE_TOWER* GetInfo_Gauge_Tower(void)
{
	return &g_aGauge_Tower[0];
}