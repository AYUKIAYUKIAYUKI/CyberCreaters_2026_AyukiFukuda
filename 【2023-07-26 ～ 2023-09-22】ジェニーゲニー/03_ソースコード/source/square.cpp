//************************************************
//
//メニューの四角表示処理[square.cpp]
//Author：福田歩希
//
//************************************************
#include "square.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Square[AMOUNT_TEXTURE_SQUARE] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Square = NULL;	//頂点バッファのポインタ
SQUARE g_aSuquare[AMOUNT_POLYGON_SQUARE];	//メニュー用ポリゴンの情報を格納

//************************************************
//初期化処理関数
//************************************************
void Init_Square(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SUQUARE_SMALL,
		&g_pTexture_Square[0]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SUQUARE_MIDDLE,
		&g_pTexture_Square[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_SQUARE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Square,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Square;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Square->Lock(0, 0, (void**)&pVtx_Square, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SQUARE; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Square[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Square[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Square[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Square[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Square[0].rhw = 1.0f;
		pVtx_Square[1].rhw = 1.0f;
		pVtx_Square[2].rhw = 1.0f;
		pVtx_Square[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Square[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Square[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Square[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Square[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Square[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Square[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Square[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Square[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Square += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Square->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SQUARE; nCnt++)
	{
		g_aSuquare[nCnt].nStyle = 0;
		g_aSuquare[nCnt].nRute = 0;
		g_aSuquare[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSuquare[nCnt].fSpan = 0.0f;
		g_aSuquare[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSuquare[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSuquare[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aSuquare[nCnt].nCntSpawn = 0;
	}

	//初回のみ頂点を展開
	Setinfo_Square();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Square(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_SQUARE; nCnt++)
	{
		if (g_pTexture_Square[nCnt] != NULL)
		{
			g_pTexture_Square[nCnt]->Release();
			g_pTexture_Square[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Square != NULL)
	{
		g_pVtxBuff_Square->Release();
		g_pVtxBuff_Square = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Square(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Square;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Square->Lock(0, 0, (void**)&pVtx_Square, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SQUARE; nCnt++)
	{
		if (g_aSuquare[nCnt].nCntSpawn > 0)
		{
			g_aSuquare[nCnt].nCntSpawn--;
		}
		else
		{
			//移動
			g_aSuquare[nCnt].pos += g_aSuquare[nCnt].move;

			//どっか行ったら
			if (g_aSuquare[nCnt].pos.y <= -500.0f ||
				g_aSuquare[nCnt].pos.y >= 1580.0f ||
				g_aSuquare[nCnt].pos.x <= -500.0f ||
				g_aSuquare[nCnt].pos.x >= 2480.0f)
			{
				Disappear_Square(nCnt);
			}

			//移動、回転を反映
			pVtx_Square[0].pos.x = g_aSuquare[nCnt].pos.x - g_aSuquare[nCnt].fSpan;
			pVtx_Square[0].pos.y = g_aSuquare[nCnt].pos.y - g_aSuquare[nCnt].fSpan;
			pVtx_Square[1].pos.x = g_aSuquare[nCnt].pos.x + g_aSuquare[nCnt].fSpan;
			pVtx_Square[1].pos.y = g_aSuquare[nCnt].pos.y - g_aSuquare[nCnt].fSpan;
			pVtx_Square[2].pos.x = g_aSuquare[nCnt].pos.x - g_aSuquare[nCnt].fSpan;
			pVtx_Square[2].pos.y = g_aSuquare[nCnt].pos.y + g_aSuquare[nCnt].fSpan;
			pVtx_Square[3].pos.x = g_aSuquare[nCnt].pos.x + g_aSuquare[nCnt].fSpan;
			pVtx_Square[3].pos.y = g_aSuquare[nCnt].pos.y + g_aSuquare[nCnt].fSpan;

			pVtx_Square[0].col = g_aSuquare[nCnt].col;
			pVtx_Square[1].col = g_aSuquare[nCnt].col;
			pVtx_Square[2].col = g_aSuquare[nCnt].col;
			pVtx_Square[3].col = g_aSuquare[nCnt].col;
		}

		pVtx_Square += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Square->Unlock();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Square(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Square, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SQUARE; nCnt++)
	{
		switch (g_aSuquare[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Square[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_Square[1]);

			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Square(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SQUARE; nCnt++)
	{
		//ランダムに大小を決定
		g_aSuquare[nCnt].nStyle = rand() % 2;
		
		//ランダムに軌道を設定
		g_aSuquare[nCnt].nRute = (int)rand() % 4;

		//軌道に合わせてに出現位置をランダムに、移動量は規定値に設定
		int nRandom = 0;
		switch (g_aSuquare[nCnt].nRute)
		{
			//↑
		case 0:

			nRandom = rand() % 1980;

			g_aSuquare[nCnt].pos = D3DXVECTOR3((1.0f * nRandom), 1380.0f, 0.0f);
			g_aSuquare[nCnt].move = D3DXVECTOR3(0.0f, -3.0f, 0.0f);

			break;

			//↓
		case 1:

			nRandom = rand() % 1980;

			g_aSuquare[nCnt].pos = D3DXVECTOR3((1.0f * nRandom), -300.0f, 0.0f);
			g_aSuquare[nCnt].move = D3DXVECTOR3(0.0f, 3.0f, 0.0f);

			break;

			//←
		case 2:

			nRandom = rand() % 1080;

			g_aSuquare[nCnt].pos = D3DXVECTOR3(2280.0f, (1.0f * nRandom), 0.0f);
			g_aSuquare[nCnt].move = D3DXVECTOR3(-3.0f, 0.0f, 0.0f);

			break;

			//→
		case 3:

			nRandom = rand() % 1080;

			g_aSuquare[nCnt].pos = D3DXVECTOR3(-300.0f, (1.0f * nRandom), 0.0f);
			g_aSuquare[nCnt].move = D3DXVECTOR3(3.0f, 0.0f, 0.0f);

			break;
		}

		if (g_aSuquare[nCnt].nStyle == 0)
		{
			g_aSuquare[nCnt].fSpan = HALFSPAN_SMALL_SQUARE;
		}
		else
		{
			g_aSuquare[nCnt].fSpan = HALFSPAN_MIDDLE_SQUARE;
		}

		g_aSuquare[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSuquare[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		g_aSuquare[nCnt].nCntSpawn = (60 * nCnt);
	}
}

//************************************************
//ポリゴン情報を再設定する関数
//************************************************
void Disappear_Square(int nCnt)
{
	//ランダムに大小を再決定
	g_aSuquare[nCnt].nStyle = rand() % 2;

	//ランダムに軌道を再設定
	g_aSuquare[nCnt].nRute = (int)rand() % 4;

	//軌道に合わせてに出現位置をランダムに、移動量は規定値に再設定
	int nRandom = 0;
	switch (g_aSuquare[nCnt].nRute)
	{
		//↑
	case 0:

		nRandom = rand() % 1980;

		g_aSuquare[nCnt].pos = D3DXVECTOR3((1.0f * nRandom), 1380.0f, 0.0f);
		g_aSuquare[nCnt].move = D3DXVECTOR3(0.0f, -3.0f, 0.0f);

		break;

		//↓
	case 1:

		nRandom = rand() % 1980;

		g_aSuquare[nCnt].pos = D3DXVECTOR3((1.0f * nRandom), -300.0f, 0.0f);
		g_aSuquare[nCnt].move = D3DXVECTOR3(0.0f, 3.0f, 0.0f);

		break;

		//←
	case 2:

		nRandom = rand() % 1080;

		g_aSuquare[nCnt].pos = D3DXVECTOR3(2280.0f, (1.0f * nRandom), 0.0f);
		g_aSuquare[nCnt].move = D3DXVECTOR3(-3.0f, 0.0f, 0.0f);

		break;

		//→
	case 3:

		nRandom = rand() % 1080;

		g_aSuquare[nCnt].pos = D3DXVECTOR3(-300.0f, (1.0f * nRandom), 0.0f);
		g_aSuquare[nCnt].move = D3DXVECTOR3(3.0f, 0.0f, 0.0f);

		break;
	}

	if (g_aSuquare[nCnt].nStyle == 0)
	{
		g_aSuquare[nCnt].fSpan = HALFSPAN_SMALL_SQUARE;
	}
	else
	{
		g_aSuquare[nCnt].fSpan = HALFSPAN_MIDDLE_SQUARE;
	}
}