//************************************************
//
//葉っぱが舞う処理[leaves.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "block.h"
#include "leaves.h"
#include "timer.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Leaves[AMOUNT_TEXTURE_LEAVES] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Leaves = NULL;	//頂点バッファのポインタ
LEAVES g_aLeaves[AMOUNT_POLYGON_LEAVES];	//葉っぱ構造体を格納
float g_fLength_Leaves[2] = {};	//葉っぱの対角線情報を格納
float g_fAngle_Leaves[2] = {};	//葉っぱの角度情報を格納

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Leaves(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LEAF_1,
		&g_pTexture_Leaves[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LEAF_2,
		&g_pTexture_Leaves[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LEAF_3,
		&g_pTexture_Leaves[2]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LEAF_4,
		&g_pTexture_Leaves[3]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LEAF_5,
		&g_pTexture_Leaves[4]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_LEAVES,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Leaves,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Leaves;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Leaves->Lock(0, 0, (void**)&pVtx_Leaves, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LEAVES; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Leaves[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Leaves[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Leaves[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Leaves[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Leaves[0].rhw = 1.0f;
		pVtx_Leaves[1].rhw = 1.0f;
		pVtx_Leaves[2].rhw = 1.0f;
		pVtx_Leaves[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Leaves[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Leaves[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Leaves[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Leaves[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Leaves[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Leaves[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Leaves[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Leaves[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Leaves += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Leaves->Unlock();

	//葉っぱ構造体の情報を初期化
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LEAVES; nCnt++)
	{
		g_aLeaves[nCnt].nStyle = 0;
		g_aLeaves[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLeaves[nCnt].fHalfSpanX = 0.0f;
		g_aLeaves[nCnt].fHalfSpanY = 0.0f;
		g_aLeaves[nCnt].nRute = 0;
		g_aLeaves[nCnt].nKeepTime = 0;
		g_aLeaves[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLeaves[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLeaves[nCnt].bUse = false;
		g_aLeaves[nCnt].nCntSpawn = 0;
		g_aLeaves[nCnt].fLength = 0.0f;
		g_aLeaves[nCnt].fAngle = 0.0f;
	}

	//葉っぱに必要な値の計算を一度挟む
	SetSpan_Leaves();

	//あらかじめ毎回ランダムに出てくる葉っぱの情報を決める
	Setinfo_Leaves();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Leaves(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_LEAVES; nCnt++)
	{
		if (g_pTexture_Leaves[nCnt] != NULL)
		{
			g_pTexture_Leaves[nCnt]->Release();
			g_pTexture_Leaves[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Leaves != NULL)
	{
		g_pVtxBuff_Leaves->Release();
		g_pVtxBuff_Leaves = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Leaves(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Leaves;

	//ブロック情報用ポインタ
	BLOCK* pBlock;

	//タイマー情報のポインタ
	bool* pInversion;
	bool* pReInversion;

	//ブロック情報を取得
	pBlock = Getinfo_Block();

	//反転情報の取得
	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Leaves->Lock(0, 0, (void**)&pVtx_Leaves, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LEAVES; nCnt++)
	{
		if (!g_aLeaves[nCnt].bUse)
		{
			if (g_aLeaves[nCnt].nCntSpawn > 0)
			{
				g_aLeaves[nCnt].nCntSpawn--;
			}
			else
			{
				g_aLeaves[nCnt].bUse = true;
			}
		}
		else
		{
			//回転…?
			g_aLeaves[nCnt].rot.z += g_aLeaves[nCnt].move.z;

			//移動分岐
			switch(g_aLeaves[nCnt].nRute)
			{
			case 0:

				g_aLeaves[nCnt].nKeepTime++;

				if (g_aLeaves[nCnt].nKeepTime >= 100)
				{
					g_aLeaves[nCnt].nKeepTime = 0;
				}

				g_aLeaves[nCnt].nKeepTime < 50 ?
					g_aLeaves[nCnt].move.x += 0.2f :
					g_aLeaves[nCnt].move.x -= 0.2f;

				break;

			case 1:

				g_aLeaves[nCnt].nKeepTime++;

				if (g_aLeaves[nCnt].nKeepTime >= 70)
				{
					g_aLeaves[nCnt].nKeepTime = 0;
				}

				g_aLeaves[nCnt].nKeepTime < 35 ?
					g_aLeaves[nCnt].move.x += 0.3f :
					g_aLeaves[nCnt].move.x -= 0.2f;

				g_aLeaves[nCnt].pos.y += g_aLeaves[nCnt].move.y * 0.5f;

				break;

			case 2:

				g_aLeaves[nCnt].nKeepTime++;

				if (g_aLeaves[nCnt].nKeepTime >= 6)
				{
					g_aLeaves[nCnt].nKeepTime = 0;
				}

				g_aLeaves[nCnt].nKeepTime < 3 ?
					g_aLeaves[nCnt].move.x += 0.2f :
					g_aLeaves[nCnt].move.x -= 0.0f;

				break;
			}

			//移動
			if (*pInversion == false || *pReInversion == true)
			{
				g_aLeaves[nCnt].pos.x -= g_aLeaves[nCnt].move.x;

				if (*pReInversion == true)
				{
					g_aLeaves[nCnt].pos.x -= g_aLeaves[nCnt].move.x;
				}
			}
			else
			{
				g_aLeaves[nCnt].pos.x += g_aLeaves[nCnt].move.x;
			}

			g_aLeaves[nCnt].pos.y += g_aLeaves[nCnt].move.y;

			if (g_aLeaves[nCnt].pos.y > 1180)
			{
				Disappear_Leaves(nCnt);
			}

			//移動、回転を反映
			pVtx_Leaves[0].pos.x = g_aLeaves[nCnt].pos.x + sinf(g_aLeaves[nCnt].rot.z - (D3DX_PI - g_aLeaves[nCnt].fAngle)) * g_aLeaves[nCnt].fLength;
			pVtx_Leaves[0].pos.y = g_aLeaves[nCnt].pos.y + cosf(g_aLeaves[nCnt].rot.z - (D3DX_PI - g_aLeaves[nCnt].fAngle)) * g_aLeaves[nCnt].fLength;
			pVtx_Leaves[1].pos.x = g_aLeaves[nCnt].pos.x + sinf(g_aLeaves[nCnt].rot.z + (D3DX_PI - g_aLeaves[nCnt].fAngle)) * g_aLeaves[nCnt].fLength;
			pVtx_Leaves[1].pos.y = g_aLeaves[nCnt].pos.y + cosf(g_aLeaves[nCnt].rot.z + (D3DX_PI - g_aLeaves[nCnt].fAngle)) * g_aLeaves[nCnt].fLength;
			pVtx_Leaves[2].pos.x = g_aLeaves[nCnt].pos.x + sinf(g_aLeaves[nCnt].rot.z - g_aLeaves[nCnt].fAngle) * g_aLeaves[nCnt].fLength;
			pVtx_Leaves[2].pos.y = g_aLeaves[nCnt].pos.y + cosf(g_aLeaves[nCnt].rot.z - g_aLeaves[nCnt].fAngle) * g_aLeaves[nCnt].fLength;
			pVtx_Leaves[3].pos.x = g_aLeaves[nCnt].pos.x + sinf(g_aLeaves[nCnt].rot.z + g_aLeaves[nCnt].fAngle) * g_aLeaves[nCnt].fLength;
			pVtx_Leaves[3].pos.y = g_aLeaves[nCnt].pos.y + cosf(g_aLeaves[nCnt].rot.z + g_aLeaves[nCnt].fAngle) * g_aLeaves[nCnt].fLength;
		}

		pVtx_Leaves += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Leaves->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Leaves(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Leaves, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LEAVES; nCnt++)
	{
		switch (g_aLeaves[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Leaves[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_Leaves[1]);

			break;

		case 2:

			pDevice->SetTexture(0, g_pTexture_Leaves[2]);

			break;

		case 3:

			pDevice->SetTexture(0, g_pTexture_Leaves[3]);

			break;

		case 4:

			pDevice->SetTexture(0, g_pTexture_Leaves[4]);

			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//葉っぱに必要な値を一度のみ計算する関数
//***********************************************
void SetSpan_Leaves(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			g_fLength_Leaves[nCnt] = sqrtf((HALFSPAN_X_TINYLEAF_1 * HALFSPAN_X_TINYLEAF_1) +
				(HALFSPAN_Y_LEAF_1 * HALFSPAN_Y_LEAF_1)) * 0.5f;

			g_fAngle_Leaves[nCnt] = atan2f((HALFSPAN_X_TINYLEAF_1 * 2), (HALFSPAN_Y_LEAF_1 * 2));

			break;

		case 1:

			g_fLength_Leaves[nCnt] = sqrtf((HALFSPAN_X_LEAF_1 * HALFSPAN_X_LEAF_1) +
				(HALFSPAN_Y_LEAF_1 * HALFSPAN_Y_LEAF_1)) * 0.5f;

			g_fAngle_Leaves[nCnt] = atan2f((HALFSPAN_X_LEAF_1 * 2.0f), (HALFSPAN_Y_LEAF_1 * 2.0f));

			break;
		}
	}
}

//************************************************
//葉っぱの情報を設定する関数
//***********************************************
void Setinfo_Leaves(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LEAVES; nCnt++)
	{
		//ランダムに葉の種類を決める
		g_aLeaves[nCnt].nStyle = (int)rand() % 5;

		//ランダムに出てくる位置を決める
		g_aLeaves[nCnt].pos = D3DXVECTOR3(400.0f + (float)(90 * (rand() % 30)), -100.0f, 0.0f);

		g_aLeaves[nCnt].fHalfSpanY = HALFSPAN_Y_LEAF_1;

		//ランダムに落ち方を決める
		g_aLeaves[nCnt].nRute = (int)rand() % 3;
		//g_aLeaves[nCnt].nRute = 1;

		g_aLeaves[nCnt].nKeepTime = 0;
		g_aLeaves[nCnt].move.x = 0.0f;
		g_aLeaves[nCnt].move.y = 6.0f;

		float fRandomSPD = 0.02f;

		//回転の向きをランダムに決める
		int nRondom = (int)rand() % 2;

		nRondom == 0 ?
			0 :
			fRandomSPD *= -1.0f;

		g_aLeaves[nCnt].move.z = fRandomSPD;
		g_aLeaves[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLeaves[nCnt].bUse = false;

		//出てくるまでにかかる時間を決める
		g_aLeaves[nCnt].nCntSpawn = 30 + (30 * nCnt);

		if (nCnt % 2 == 1)
		{
			g_aLeaves[nCnt].nCntSpawn -= 20;
		}

		if (g_aLeaves[nCnt].nStyle == 0 || g_aLeaves[nCnt].nStyle == 3)
		{
			g_aLeaves[nCnt].fHalfSpanX = HALFSPAN_X_TINYLEAF_1;
			g_aLeaves[nCnt].fLength = g_fLength_Leaves[0];
			g_aLeaves[nCnt].fAngle = g_fAngle_Leaves[0];
		}
		else
		{
			g_aLeaves[nCnt].fHalfSpanX = HALFSPAN_X_LEAF_1;
			g_aLeaves[nCnt].fLength = g_fLength_Leaves[1];
			g_aLeaves[nCnt].fAngle = g_fAngle_Leaves[1];
		}
	}
}

//************************************************
//葉っぱの情報を再設定する関数
//***********************************************
void Disappear_Leaves(int nCnt)
{
	//タイマー情報のポインタ
	bool* pInversion;
	bool* pReInversion;

	//反転情報の取得
	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//ランダムに葉の種類を再決定
	g_aLeaves[nCnt].nStyle = (int)rand() % 5;

	//ランダムに出てくる位置を再決定
	if (*pInversion == false || *pReInversion == true)
	{
		g_aLeaves[nCnt].pos = D3DXVECTOR3(400.0f + (float)(90 * (rand() % 30)), -100.0f, 0.0f);
	}
	else
	{
		g_aLeaves[nCnt].pos = D3DXVECTOR3(-600.0f + (float)(90 * (rand() % 30)), -100.0f, 0.0f);
	}

	//ランダムに落ち方を決める
	g_aLeaves[nCnt].nRute = (int)rand() % 3;
	//g_aLeaves[nCnt].nRute = 1;

	g_aLeaves[nCnt].nKeepTime = 0;
	g_aLeaves[nCnt].move.x = 0.0f;
	g_aLeaves[nCnt].move.y = 6.0f;

	float fRandomSPD = 0.02f;

	//回転の向きをランダムに再決定
	int nRondom = (int)rand() % 2;

	nRondom == 0 ?
		0 :
		fRandomSPD *= -1.0f;

	g_aLeaves[nCnt].move.z = fRandomSPD;

	if (g_aLeaves[nCnt].nStyle == 0 || g_aLeaves[nCnt].nStyle == 3)
	{
		g_aLeaves[nCnt].fHalfSpanX = HALFSPAN_X_TINYLEAF_1;
		g_aLeaves[nCnt].fLength = g_fLength_Leaves[0];
		g_aLeaves[nCnt].fAngle = g_fAngle_Leaves[0];
	}
	else
	{
		g_aLeaves[nCnt].fHalfSpanX = HALFSPAN_X_LEAF_1;
		g_aLeaves[nCnt].fLength = g_fLength_Leaves[1];
		g_aLeaves[nCnt].fAngle = g_fAngle_Leaves[1];
	}
}