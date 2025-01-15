//************************************************
//
//前景処理(クソコード注意)[fg.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "fg.h"
#include "timer.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_FG[AMOUNT_TEXTURE_FG] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_FG = NULL;	//頂点バッファのポインタ
FG_OBJECT g_aObject[AMOUNT_POLYGON_FG];	//前景ポリゴン用情報構造体
float g_fLength_Object[2] = {};	//対角線情報を格納
float g_fAngle_Object[2] = {};	//角度情報を格納
int g_nStartingSet_Ivy = 0;	//開幕だけ画面内にツタを置くため

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_FG(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_IVY_1,
		&g_pTexture_FG[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_IVY_2,
		&g_pTexture_FG[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_IVY_3,
		&g_pTexture_FG[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_FG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_FG,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_FG;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_FG->Lock(0, 0, (void**)&pVtx_FG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FG; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_FG[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_FG[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_FG[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_FG[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_FG[0].rhw = 1.0f;
		pVtx_FG[1].rhw = 1.0f;
		pVtx_FG[2].rhw = 1.0f;
		pVtx_FG[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_FG[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_FG[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_FG[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_FG[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_FG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_FG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_FG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_FG[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_FG += AMOUNT_VTX;
	}

	//前景用ポリゴン初期化
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FG; nCnt++)
	{
		g_aObject[nCnt].nStyle = 0;
		g_aObject[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCnt].bUse = false;
		g_aObject[nCnt].nCntSpawn = 0;
		g_aObject[nCnt].fLength = 0.0f;
		g_aObject[nCnt].fAngle = 0.0f;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_FG->Unlock();

	g_nStartingSet_Ivy = 0;

	//必要な値の計算を一度挟む
	SetSpan_FG();

	//必要な情報を設定する
	Setinfo_Vtx_FG();

	////設定した情報をもとにポリゴンを展開しておく
	//Update_FG();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_FG(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_FG; nCnt++)
	{
		if (g_pTexture_FG[nCnt] != NULL)
		{
			g_pTexture_FG[nCnt]->Release();
			g_pTexture_FG[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_FG != NULL)
	{
		g_pVtxBuff_FG->Release();
		g_pVtxBuff_FG = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_FG(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_FG;

	//タイマー情報のポインタ
	bool* pInversion;
	bool* pReInversion;

	//反転情報の取得
	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_FG->Lock(0, 0, (void**)&pVtx_FG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FG; nCnt++)
	{
		if (!g_aObject[nCnt].bUse)
		{
			if (g_aObject[nCnt].nCntSpawn > 0)
			{
				g_aObject[nCnt].nCntSpawn--;
			}
			else
			{
				g_aObject[nCnt].bUse = true;
			}
		}
		else
		{
			//移動
			g_aObject[nCnt].pos.x += g_aObject[nCnt].move.x;
			g_aObject[nCnt].pos.y += g_aObject[nCnt].move.y;

			//反転判定が出ているとき
			if (*pInversion == true &&
				g_aObject[nCnt].move.x <= 8.0f &&
				*pReInversion == false)
			{
				g_aObject[nCnt].move.x += 0.1f;
			}
			else if (*pInversion == true &&
				g_aObject[nCnt].move.x >= -12.0f &&
				*pReInversion == true)
			{
				g_aObject[nCnt].move.x -= 0.1f;
			}

			if (g_aObject[nCnt].pos.x < -1000.0f ||
				g_aObject[nCnt].pos.x > 3000.0f)
			{
				Disappear_FG(nCnt);
			}

			//移動、回転を反映
			pVtx_FG[0].pos.x = g_aObject[nCnt].pos.x + sinf(g_aObject[nCnt].rot.z - (D3DX_PI - g_aObject[nCnt].fAngle)) * g_aObject[nCnt].fLength;
			pVtx_FG[0].pos.y = g_aObject[nCnt].pos.y + cosf(g_aObject[nCnt].rot.z - (D3DX_PI - g_aObject[nCnt].fAngle)) * g_aObject[nCnt].fLength;
			pVtx_FG[1].pos.x = g_aObject[nCnt].pos.x + sinf(g_aObject[nCnt].rot.z + (D3DX_PI - g_aObject[nCnt].fAngle)) * g_aObject[nCnt].fLength;
			pVtx_FG[1].pos.y = g_aObject[nCnt].pos.y + cosf(g_aObject[nCnt].rot.z + (D3DX_PI - g_aObject[nCnt].fAngle)) * g_aObject[nCnt].fLength;
			pVtx_FG[2].pos.x = g_aObject[nCnt].pos.x + sinf(g_aObject[nCnt].rot.z - g_aObject[nCnt].fAngle) * g_aObject[nCnt].fLength;
			pVtx_FG[2].pos.y = g_aObject[nCnt].pos.y + cosf(g_aObject[nCnt].rot.z - g_aObject[nCnt].fAngle) * g_aObject[nCnt].fLength;
			pVtx_FG[3].pos.x = g_aObject[nCnt].pos.x + sinf(g_aObject[nCnt].rot.z + g_aObject[nCnt].fAngle) * g_aObject[nCnt].fLength;
			pVtx_FG[3].pos.y = g_aObject[nCnt].pos.y + cosf(g_aObject[nCnt].rot.z + g_aObject[nCnt].fAngle) * g_aObject[nCnt].fLength;
		}

		pVtx_FG += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_FG->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_FG(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_FG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FG; nCnt++)
	{
		switch (g_aObject[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_FG[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_FG[1]);

			break;

		case 2:

			pDevice->SetTexture(0, g_pTexture_FG[2]);

			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//必要な値を計算する関数
//***********************************************
void SetSpan_FG(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			g_fLength_Object[nCnt] = sqrtf((HALFSPAN_X_IVY * HALFSPAN_X_IVY) +
				(HALFSPAN_Y_IVY * HALFSPAN_Y_IVY)) * 0.5f;

			g_fAngle_Object[nCnt] = atan2f(HALFSPAN_X_IVY * 2.0f, HALFSPAN_X_IVY * 2.0f);

			break;

		case 1:

			g_fLength_Object[nCnt] = sqrtf((HALFSPAN_X_LONGIVY * HALFSPAN_X_LONGIVY) +
				(HALFSPAN_Y_LONGIVY * HALFSPAN_Y_LONGIVY)) * 0.5f;

			g_fAngle_Object[nCnt] = atan2f(HALFSPAN_X_LONGIVY * 2.0f, HALFSPAN_Y_LONGIVY * 2.0f);

			break;
		}
	}
}

//************************************************
//ポリゴン情報を設定関数
//************************************************
void Setinfo_Vtx_FG(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_FG;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_FG->Lock(0, 0, (void**)&pVtx_FG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FG; nCnt++)
	{
		g_nStartingSet_Ivy++;

		//ランダムに種類を設定
		int nRandomStyle = (int)rand() % 5;

		if (nRandomStyle == 1 || nRandomStyle == 2)
		{
			g_aObject[nCnt].nStyle = 1;
		}
		else if (nRandomStyle == 3 || nRandomStyle == 4)
		{
			g_aObject[nCnt].nStyle = 2;
		}
		else
		{
			g_aObject[nCnt].nStyle = 0;
		}

		g_aObject[nCnt].move = D3DXVECTOR3(-6.0f, 0.0f, 0.0f);
		g_aObject[nCnt].bUse = false;

		if (g_nStartingSet_Ivy >= 5)
		{
			g_aObject[nCnt].nCntSpawn = 90 * (nCnt - 5);
		}

		int nRandom = (int)rand() % 2;

		if (nRandom == 0)
		{
			pVtx_FG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_FG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx_FG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx_FG[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		//反転
		else
		{
			pVtx_FG[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx_FG[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_FG[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx_FG[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		}

		if (g_nStartingSet_Ivy < 5)
		{
			g_aObject[nCnt].nCntSpawn = 0;

			if (g_aObject[nCnt].nStyle == 0)
			{
				g_aObject[nCnt].pos = D3DXVECTOR3(2200.0f - (396.0f * (g_nStartingSet_Ivy + 1)), 20.0f, 0.0f);
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.25f);
				g_aObject[nCnt].fLength = g_fLength_Object[0];
				g_aObject[nCnt].fAngle = g_fAngle_Object[0];
			}
			else if (g_aObject[nCnt].nStyle == 1)
			{
				g_aObject[nCnt].pos = D3DXVECTOR3(2500.0f - (396.0f * (g_nStartingSet_Ivy + 1)), 20.0f, 0.0f);

				if (nRandom == 0)
				{
					g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, -0.1f);
				}
				else
				{
					g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.1f);
				}

				g_aObject[nCnt].fLength = g_fLength_Object[1];
				g_aObject[nCnt].fAngle = g_fAngle_Object[1];
			}
			else if (g_aObject[nCnt].nStyle == 2)
			{
				g_aObject[nCnt].pos = D3DXVECTOR3(2500.0f - (396.0f * (g_nStartingSet_Ivy + 1)), 30.0f, 0.0f);
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aObject[nCnt].fLength = g_fLength_Object[1];
				g_aObject[nCnt].fAngle = g_fAngle_Object[1];
			}
		}
		else
		{
			if (g_aObject[nCnt].nStyle == 0)
			{
				g_aObject[nCnt].pos = D3DXVECTOR3(2200.0f, 20.0f, 0.0f);
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.25f);
				g_aObject[nCnt].fLength = g_fLength_Object[0];
				g_aObject[nCnt].fAngle = g_fAngle_Object[0];
			}
			else if (g_aObject[nCnt].nStyle == 1)
			{
				g_aObject[nCnt].pos = D3DXVECTOR3(2500.0f, 20.0f, 0.0f);

				if (nRandom == 0)
				{
					g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, -0.1f);
				}
				else
				{
					g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.1f);
				}

				g_aObject[nCnt].fLength = g_fLength_Object[1];
				g_aObject[nCnt].fAngle = g_fAngle_Object[1];
			}
			else if (g_aObject[nCnt].nStyle == 2)
			{
				g_aObject[nCnt].pos = D3DXVECTOR3(2500.0f, 30.0f, 0.0f);
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aObject[nCnt].fLength = g_fLength_Object[1];
				g_aObject[nCnt].fAngle = g_fAngle_Object[1];
			}
		}

		pVtx_FG += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_FG->Unlock();
}

//************************************************
//ポリゴンの情報を再設定する関数
//***********************************************
void Disappear_FG(int nCnt)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_FG;

	//タイマー情報のポインタ
	bool* pInversion;
	bool* pReInversion;

	//反転情報の取得
	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_FG->Lock(0, 0, (void**)&pVtx_FG, 0);

	pVtx_FG += AMOUNT_VTX * nCnt;

	//ランダムにツタの種類を再決定
	int nRandomStyle = (int)rand() % 5;

	if (nRandomStyle == 1 || nRandomStyle == 2)
	{
		g_aObject[nCnt].nStyle = 1;
	}
	else if (nRandomStyle == 3 || nRandomStyle == 4)
	{
		g_aObject[nCnt].nStyle = 2;
	}
	else
	{
		g_aObject[nCnt].nStyle = 0;
	}

	int nRandom = (int)rand() % 2;

	if (nRandom == 0)
	{
		pVtx_FG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_FG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_FG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_FG[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//反転
	else
	{
		pVtx_FG[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_FG[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_FG[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx_FG[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	}

	//ランダムに出てくる位置を再決定
	if (*pInversion == false || *pReInversion == true)
	{
		if (g_aObject[nCnt].nStyle == 0)
		{
			g_aObject[nCnt].pos = D3DXVECTOR3(2200.0f, 20.0f, 0.0f);
			g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.25f);
			g_aObject[nCnt].fLength = g_fLength_Object[0];
			g_aObject[nCnt].fAngle = g_fAngle_Object[0];
		}
		else if (g_aObject[nCnt].nStyle == 1)
		{
			g_aObject[nCnt].pos = D3DXVECTOR3(2500.0f, 20.0f, 0.0f);

			if (nRandom == 0)
			{
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, -0.1f);
			}
			else
			{
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.1f);
			}

			g_aObject[nCnt].fLength = g_fLength_Object[1];
			g_aObject[nCnt].fAngle = g_fAngle_Object[1];
		}
		else if (g_aObject[nCnt].nStyle == 2)
		{
			g_aObject[nCnt].pos = D3DXVECTOR3(2500.0f, 30.0f, 0.0f);
			g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aObject[nCnt].fLength = g_fLength_Object[1];
			g_aObject[nCnt].fAngle = g_fAngle_Object[1];
		}
	}
	else
	{
		if (g_aObject[nCnt].nStyle == 0)
		{
			g_aObject[nCnt].pos = D3DXVECTOR3(-200.0f, 20.0f, 0.0f);
			g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.25f);
			g_aObject[nCnt].fLength = g_fLength_Object[0];
			g_aObject[nCnt].fAngle = g_fAngle_Object[0];
		}
		else if (g_aObject[nCnt].nStyle == 1)
		{
			g_aObject[nCnt].pos = D3DXVECTOR3(-500.0f, 20.0f, 0.0f);

			if (nRandom == 0)
			{
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, -0.1f);
			}
			else
			{
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.1f);
			}

			g_aObject[nCnt].fLength = g_fLength_Object[1];
			g_aObject[nCnt].fAngle = g_fAngle_Object[1];
		}
		else if (g_aObject[nCnt].nStyle == 2)
		{
			g_aObject[nCnt].pos = D3DXVECTOR3(-500.0f, 30.0f, 0.0f);
			g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aObject[nCnt].fLength = g_fLength_Object[1];
			g_aObject[nCnt].fAngle = g_fAngle_Object[1];
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_FG->Unlock();
}