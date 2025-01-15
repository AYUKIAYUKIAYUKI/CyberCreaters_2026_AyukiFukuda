//************************************************
//
//草むら処理(クソコード注意)[bush.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "bush.h"
#include "timer.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Bush[AMOUNT_TEXTURE_BUSH] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Bush = NULL;	//頂点バッファのポインタ
BUSH g_aBush[AMOUNT_POLYGON_BUSH];	//前景ポリゴン用情報構造体
float g_fLength_Bush[2] = {};	//対角線情報を格納
float g_fAngle_Bush[2] = {};	//角度情報を格納
int g_nStartingSet_Bush = 0;	//開幕だけ画面内に草を置くため

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Bush(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BUSH_1,
		&g_pTexture_Bush[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BUSH_2,
		&g_pTexture_Bush[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BUSH_3,
		&g_pTexture_Bush[2]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BUSH_4,
		&g_pTexture_Bush[3]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BUSH_5,
		&g_pTexture_Bush[4]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BUSH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Bush,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Bush;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Bush->Lock(0, 0, (void**)&pVtx_Bush, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BUSH; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Bush[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bush[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bush[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bush[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Bush[0].rhw = 1.0f;
		pVtx_Bush[1].rhw = 1.0f;
		pVtx_Bush[2].rhw = 1.0f;
		pVtx_Bush[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Bush[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Bush[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Bush[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Bush[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Bush[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Bush[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Bush[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Bush[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Bush += AMOUNT_VTX;
	}

	//草むら初期化
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BUSH; nCnt++)
	{
		g_aBush[nCnt].nStyle = 0;
		g_aBush[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBush[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBush[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBush[nCnt].bUse = false;
		g_aBush[nCnt].nCntSpawn = 0;
		g_aBush[nCnt].fLength = 0.0f;
		g_aBush[nCnt].fAngle = 0.0f;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Bush->Unlock();

	g_nStartingSet_Bush = 0;

	//必要な値の計算を一度挟む
	SetSpan_Bush();

	//初回に一度情報を設定する
	Setinfo_Vtx_Bush();

	////設定した情報をもとに一度だけ展開しておく
	//Update_Bush();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Bush(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_BUSH; nCnt++)
	{
		if (g_pTexture_Bush[nCnt] != NULL)
		{
			g_pTexture_Bush[nCnt]->Release();
			g_pTexture_Bush[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Bush != NULL)
	{
		g_pVtxBuff_Bush->Release();
		g_pVtxBuff_Bush = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Bush(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Bush;

	//タイマー情報のポインタ
	bool* pInversion;
	bool* pReInversion;

	//反転情報の取得
	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Bush->Lock(0, 0, (void**)&pVtx_Bush, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BUSH; nCnt++)
	{
		if (!g_aBush[nCnt].bUse)
		{
			if (g_aBush[nCnt].nCntSpawn > 0)
			{
				g_aBush[nCnt].nCntSpawn--;
			}
			else
			{
				g_aBush[nCnt].bUse = true;
			}
		}
		else
		{
			//移動
			g_aBush[nCnt].pos.x += g_aBush[nCnt].move.x;
			g_aBush[nCnt].pos.y += g_aBush[nCnt].move.y;

			//反転判定が出ているとき
			if (*pInversion == true &&
				g_aBush[nCnt].move.x <= 8.0f &&
				*pReInversion == false)
			{
				g_aBush[nCnt].move.x += 0.1f;
			}
			else if (*pInversion == true &&
				g_aBush[nCnt].move.x >= -12.0f &&
				*pReInversion == true)
			{
				g_aBush[nCnt].move.x -= 0.1f;
			}

			if (g_aBush[nCnt].pos.x < -1000.0f ||
				g_aBush[nCnt].pos.x > 3000.0f)
			{
				Disappear_Bush(nCnt);
			}

			//移動、回転を反映
			pVtx_Bush[0].pos.x = g_aBush[nCnt].pos.x + sinf(g_aBush[nCnt].rot.z - (D3DX_PI - g_aBush[nCnt].fAngle)) * g_aBush[nCnt].fLength;
			pVtx_Bush[0].pos.y = g_aBush[nCnt].pos.y + cosf(g_aBush[nCnt].rot.z - (D3DX_PI - g_aBush[nCnt].fAngle)) * g_aBush[nCnt].fLength;
			pVtx_Bush[1].pos.x = g_aBush[nCnt].pos.x + sinf(g_aBush[nCnt].rot.z + (D3DX_PI - g_aBush[nCnt].fAngle)) * g_aBush[nCnt].fLength;
			pVtx_Bush[1].pos.y = g_aBush[nCnt].pos.y + cosf(g_aBush[nCnt].rot.z + (D3DX_PI - g_aBush[nCnt].fAngle)) * g_aBush[nCnt].fLength;
			pVtx_Bush[2].pos.x = g_aBush[nCnt].pos.x + sinf(g_aBush[nCnt].rot.z - g_aBush[nCnt].fAngle) * g_aBush[nCnt].fLength;
			pVtx_Bush[2].pos.y = g_aBush[nCnt].pos.y + cosf(g_aBush[nCnt].rot.z - g_aBush[nCnt].fAngle) * g_aBush[nCnt].fLength;
			pVtx_Bush[3].pos.x = g_aBush[nCnt].pos.x + sinf(g_aBush[nCnt].rot.z + g_aBush[nCnt].fAngle) * g_aBush[nCnt].fLength;
			pVtx_Bush[3].pos.y = g_aBush[nCnt].pos.y + cosf(g_aBush[nCnt].rot.z + g_aBush[nCnt].fAngle) * g_aBush[nCnt].fLength;
		}

		pVtx_Bush += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Bush->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Bush(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Bush, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BUSH; nCnt++)
	{
		switch (g_aBush[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Bush[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_Bush[1]);

			break;

		case 2:

			pDevice->SetTexture(0, g_pTexture_Bush[2]);

			break;

		case 3:

			pDevice->SetTexture(0, g_pTexture_Bush[3]);

			break;

		case 4:

			pDevice->SetTexture(0, g_pTexture_Bush[4]);

			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//必要な値を計算する関数
//***********************************************
void SetSpan_Bush(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			g_fLength_Bush[nCnt] = sqrtf((HALFSPAN_X_BUSH * HALFSPAN_X_BUSH) +
				(HALFSPAN_Y_BUSH * HALFSPAN_Y_BUSH)) * 0.5f;

			g_fAngle_Bush[nCnt] = atan2f(HALFSPAN_X_BUSH * 2.0f, HALFSPAN_X_BUSH * 2.0f);

			break;

		case 1:

			g_fLength_Bush[nCnt] = sqrtf((HALFSPAN_X_LONGBUSH * HALFSPAN_X_LONGBUSH) +
				(HALFSPAN_X_BUSH * HALFSPAN_X_BUSH)) * 0.5f;

			g_fAngle_Bush[nCnt] = atan2f(HALFSPAN_X_LONGBUSH * 2.0f, HALFSPAN_X_BUSH * 2.0f);

			break;
		}
	}
}

//************************************************
//ポリゴン情報を設定関数
//************************************************
void Setinfo_Vtx_Bush(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Bush;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Bush->Lock(0, 0, (void**)&pVtx_Bush, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BUSH; nCnt++)
	{
		g_nStartingSet_Bush++;

		//ランダムに種類を設定
		g_aBush[nCnt].nStyle = (int)rand() % 5;
		//g_aBush[nCnt].nStyle = 0;

		g_aBush[nCnt].move = D3DXVECTOR3(-6.0f, 0.0f, 0.0f);
		g_aBush[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBush[nCnt].bUse = false;

		if (g_nStartingSet_Bush >= 7)
		{
			g_aBush[nCnt].nCntSpawn = 60 * (nCnt - 7);
		}

		//int nRandom = (int)rand() % 2;

		//if (nRandom == 0)
		//{
		//	pVtx_Bush[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//	pVtx_Bush[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//	pVtx_Bush[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//	pVtx_Bush[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		//}
		////反転
		//else
		//{
		//	pVtx_Bush[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		//	pVtx_Bush[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		//	pVtx_Bush[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		//	pVtx_Bush[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		//}

		if (g_nStartingSet_Bush < 7)
		{
			g_aBush[nCnt].nCntSpawn = 0;

			switch (g_aBush[nCnt].nStyle)
			{
			case 0:

				g_aBush[nCnt].pos = D3DXVECTOR3(2500.0f - (320.0f * (g_nStartingSet_Bush + 1)), 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[0];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

				break;

			case 1:

				g_aBush[nCnt].pos = D3DXVECTOR3(2500.0f - (320.0f * (g_nStartingSet_Bush + 1)), 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[1];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

				break;

			case 2:

				g_aBush[nCnt].pos = D3DXVECTOR3(2500.0f - (320.0f * (g_nStartingSet_Bush + 1)), 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[0];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

				break;

			case 3:

				g_aBush[nCnt].pos = D3DXVECTOR3(2500.0f - (320.0f * (g_nStartingSet_Bush + 1)), 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[1];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

				break;

			case 4:

				g_aBush[nCnt].pos = D3DXVECTOR3(2500.0f - (320.0f * (g_nStartingSet_Bush + 1)), 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[1];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

				break;
			}
		}
		else
		{
			switch (g_aBush[nCnt].nStyle)
			{
			case 0:

				g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[0];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

				break;

			case 1:

				g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[1];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

				break;

			case 2:

				g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[0];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

				break;

			case 3:

				g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[1];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

				break;

			case 4:

				g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[1];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

				break;
			}
		}

		pVtx_Bush += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Bush->Unlock();
}

//************************************************
//ポリゴンの情報を再設定する関数
//***********************************************
void Disappear_Bush(int nCnt)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Bush;

	//タイマー情報のポインタ
	bool* pInversion;
	bool* pReInversion;

	//反転情報の取得
	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Bush->Lock(0, 0, (void**)&pVtx_Bush, 0);

	pVtx_Bush += AMOUNT_VTX * nCnt;

	//ランダムに種類を再決定
	g_aBush[nCnt].nStyle = (int)rand() % 5;

	g_aBush[nCnt].bUse = false;
	g_aBush[nCnt].nCntSpawn = 20;

	//int nRandom = (int)rand() % 2;

	//if (nRandom == 0)
	//{
	//	pVtx_Bush[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx_Bush[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx_Bush[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx_Bush[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//}
	////反転
	//else
	//{
	//	pVtx_Bush[0].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx_Bush[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx_Bush[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	//	pVtx_Bush[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	//}

	if (*pInversion == false || *pReInversion == true)
	{
		switch (g_aBush[nCnt].nStyle)
		{
		case 0:

			g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[0];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

			break;

		case 1:

			g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[1];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

			break;

		case 2:

			g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[0];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

			break;

		case 3:

			g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[1];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

			break;

		case 4:

			g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[1];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

			break;
		}
	}
	else
	{
		switch (g_aBush[nCnt].nStyle)
		{
		case 0:

			g_aBush[nCnt].pos = D3DXVECTOR3(-200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[0];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

			break;

		case 1:

			g_aBush[nCnt].pos = D3DXVECTOR3(-200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[1];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

			break;

		case 2:

			g_aBush[nCnt].pos = D3DXVECTOR3(-200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[0];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

			break;

		case 3:

			g_aBush[nCnt].pos = D3DXVECTOR3(-200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[1];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

			break;

		case 4:

			g_aBush[nCnt].pos = D3DXVECTOR3(-200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[1];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

			break;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Bush->Unlock();
}