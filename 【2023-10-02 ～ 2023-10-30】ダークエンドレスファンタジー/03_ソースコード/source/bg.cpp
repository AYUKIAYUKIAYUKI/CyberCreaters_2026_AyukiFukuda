//************************************************
//
//背景処理[bg.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "bg.h"
#include "player.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_BG[AMOUNT_TEX_BG] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_BG = NULL;	//頂点バッファのポインタ
BG g_aBG[AMOUNT_POLYGON_BG];	//背景情報
static float g_F = 0.0f;	//汎用浮動小数
int g_Mode;

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_BG(int nMode)
{
	g_Mode = nMode;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_1,
		&g_pTexture_BG[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_2,
		&g_pTexture_BG[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_3,
		&g_pTexture_BG[2]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_4,
		&g_pTexture_BG[3]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_5,
		&g_pTexture_BG[4]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_6,
		&g_pTexture_BG[5]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_7,
		&g_pTexture_BG[6]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_8,
		&g_pTexture_BG[7]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_9,
		&g_pTexture_BG[8]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_10,
		&g_pTexture_BG[9]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_BG,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_BG;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_BG->Lock(0, 0, (void**)&pVtx_BG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_BG[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_BG[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_BG[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_BG[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_BG[0].rhw = 1.0f;
		pVtx_BG[1].rhw = 1.0f;
		pVtx_BG[2].rhw = 1.0f;
		pVtx_BG[3].rhw = 1.0f;

		//頂点カラーの初期設定
		switch (nMode)
		{
		case BG_TYPE_TITLE:
			pVtx_BG[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
			pVtx_BG[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
			pVtx_BG[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
			pVtx_BG[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
			break;
		case BG_TYPE_GAME:
			pVtx_BG[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx_BG[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx_BG[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx_BG[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		//テクスチャ座標の初期設定
		pVtx_BG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_BG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_BG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_BG[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_BG += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_BG->Unlock();

	//背景構造体の情報の初期化群
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		g_aBG[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBG[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBG[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBG[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aBG[nCnt].fRadius[nCnt2] = 0.0f;
			g_aBG[nCnt].fTex[nCnt2] = 0.0f;
		}
		g_aBG[nCnt].fLength = 0.0f;
		g_aBG[nCnt].fAngle = 0.0f;
		g_aBG[nCnt].nLayer = 0;
	}

	g_F = 0.01f;

	//背景構造体に情報を付与
	SetInfo_BG();

	//位置に基づきポリゴンを展開
	Update_Pos_BG();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_BG(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEX_BG; nCnt++)
	{
		if (g_pTexture_BG[nCnt] != NULL)
		{
			g_pTexture_BG[nCnt]->Release();
			g_pTexture_BG[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_BG != NULL)
	{
		g_pVtxBuff_BG->Release();
		g_pVtxBuff_BG = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_BG(void)
{
	//クモは動く
	Update_Pos_BG();

	//色変更
	if(g_Mode == BG_TYPE_GAME)
	{
		Update_Col_BG();
	}

	//テクスチャアニメーション
	Update_Tex_BG();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_BG(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_BG, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		//テクスチャの設定
		//if (nCnt >= AMOUNT_TEX_BG)
		//{
		//	pDevice->SetTexture(0, g_pTexture_BG[9]);
		//}
		//else
		//{
			pDevice->SetTexture(0, g_pTexture_BG[nCnt]);
		//}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//背景構造体の情報を設定する関数
//************************************************
void SetInfo_BG(void)
{
	int nCntLayer = 0;
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		if (nCnt < AMOUNT_TEX_BG - 1)
		{
			switch (nCnt)
			{
			case 2:
				nCntLayer++;
				break;
			case 3:
				nCntLayer++;
				break;
			case 5:
				nCntLayer++;
				break;
			case 6:
				nCntLayer++;
				break;
			case 7:
				nCntLayer++;
				break;
			}
			g_aBG[nCnt].pos = D3DXVECTOR3(SCREEN_HALFWIDTH, SCREEN_HALFHEIGHT, 0.0f);
			g_aBG[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_aBG[nCnt].fRadius[0] = RADIUS_BG_X;	//背景横半幅
			g_aBG[nCnt].fRadius[1] = RADIUS_BG_Y;	//背景縦半幅
			g_aBG[nCnt].fLength = sqrtf((g_aBG[nCnt].fRadius[0] * g_aBG[nCnt].fRadius[0]) + (g_aBG[nCnt].fRadius[1] * g_aBG[nCnt].fRadius[1]));
			g_aBG[nCnt].fAngle = atan2f(g_aBG[nCnt].fRadius[0] * 2.0f, g_aBG[nCnt].fRadius[1] * 2.0f);
			g_aBG[nCnt].nLayer = nCntLayer;
			g_aBG[nCnt].fTex[0] = 0.0f;
			g_aBG[nCnt].fTex[1] = 2.0f;
		}
		////クモには別のデータを設定する
		//else
		//{
		//	//出現位置や移動量はランダムに決まる
		//	g_aBG[nCnt].pos = D3DXVECTOR3(SCREEN_HALFWIDTH, 200, 0.0f);
		//	g_aBG[nCnt].move = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		//	g_aBG[nCnt].fRadius[0] = RADIUS_CLOUD_X;	//クモ横半幅
		//	g_aBG[nCnt].fRadius[1] = RADIUS_CLOUD_Y;	//クモ縦半幅
		//	g_aBG[nCnt].fLength = sqrtf((g_aBG[nCnt].fRadius[0] * g_aBG[nCnt].fRadius[0]) + (g_aBG[nCnt].fRadius[1] * g_aBG[nCnt].fRadius[1]));
		//	g_aBG[nCnt].fAngle = atan2f(g_aBG[nCnt].fRadius[0] * 2.0f, g_aBG[nCnt].fRadius[1] * 2.0f);
		//	g_aBG[nCnt].fTex[0] = 0.0f;
		//	g_aBG[nCnt].fTex[1] = 1.0f;
		//}
	}
}

//************************************************
//背景の位置を設定する関数
//************************************************
void Update_Pos_BG(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_BG;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_BG->Lock(0, 0, (void**)&pVtx_BG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		//クモは動く
		g_aBG[nCnt].pos += g_aBG[nCnt].move;

		pVtx_BG[0].pos.x = g_aBG[nCnt].pos.x + sinf(g_aBG[nCnt].rot.z - (D3DX_PI - g_aBG[nCnt].fAngle)) * g_aBG[nCnt].fLength;
		pVtx_BG[0].pos.y = g_aBG[nCnt].pos.y + cosf(g_aBG[nCnt].rot.z - (D3DX_PI - g_aBG[nCnt].fAngle)) * g_aBG[nCnt].fLength;
		pVtx_BG[1].pos.x = g_aBG[nCnt].pos.x + sinf(g_aBG[nCnt].rot.z + (D3DX_PI - g_aBG[nCnt].fAngle)) * g_aBG[nCnt].fLength;
		pVtx_BG[1].pos.y = g_aBG[nCnt].pos.y + cosf(g_aBG[nCnt].rot.z + (D3DX_PI - g_aBG[nCnt].fAngle)) * g_aBG[nCnt].fLength;
		pVtx_BG[2].pos.x = g_aBG[nCnt].pos.x + sinf(g_aBG[nCnt].rot.z - g_aBG[nCnt].fAngle) * g_aBG[nCnt].fLength;
		pVtx_BG[2].pos.y = g_aBG[nCnt].pos.y + cosf(g_aBG[nCnt].rot.z - g_aBG[nCnt].fAngle) * g_aBG[nCnt].fLength;
		pVtx_BG[3].pos.x = g_aBG[nCnt].pos.x + sinf(g_aBG[nCnt].rot.z + g_aBG[nCnt].fAngle) * g_aBG[nCnt].fLength;
		pVtx_BG[3].pos.y = g_aBG[nCnt].pos.y + cosf(g_aBG[nCnt].rot.z + g_aBG[nCnt].fAngle) * g_aBG[nCnt].fLength;

		pVtx_BG += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_BG->Unlock();
}

//************************************************
//背景の色を変更する関数
//************************************************
void Update_Col_BG(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_BG;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_BG->Lock(0, 0, (void**)&pVtx_BG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		if (nCnt == 4)
		{
			g_aBG[nCnt].col.a -= g_F;

			pVtx_BG[0].col = g_aBG[nCnt].col;
			pVtx_BG[1].col = g_aBG[nCnt].col;
			pVtx_BG[2].col = g_aBG[nCnt].col;
			pVtx_BG[3].col = g_aBG[nCnt].col;
		}

		//明滅
		if (g_aBG[nCnt].col.a < 0.0f || g_aBG[nCnt].col.a > 1.0f)
		{
			g_F *= -1.0f;
		}

		pVtx_BG += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_BG->Unlock();
}

//************************************************
//背景のテクスチャを動かす関数
//************************************************
void Update_Tex_BG(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_BG;

	PLAYER* pPlayer = GetInfo_Player();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_BG->Lock(0, 0, (void**)&pVtx_BG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		if (g_aBG[nCnt].nLayer == 2)
		{
			for (int nCntLR = 0; nCntLR < 2; nCntLR++)
			{
				g_aBG[nCnt].fTex[nCntLR] += pPlayer->move.x * 0.0005f;
			}
		}

		switch (g_aBG[nCnt].nLayer)
		{
		case 5:
			for (int nCntLR = 0; nCntLR < 2; nCntLR++)
			{
				g_aBG[nCnt].fTex[nCntLR] += 0.0002f;
				g_aBG[nCnt].fTex[nCntLR] += pPlayer->move.x * 0.0002f;
			}
		case 4:
			for (int nCntLR = 0; nCntLR < 2; nCntLR++)
			{
				g_aBG[nCnt].fTex[nCntLR] += 0.0002f;
				g_aBG[nCnt].fTex[nCntLR] += pPlayer->move.x * 0.0002f;
			}
		case 3:
			for (int nCntLR = 0; nCntLR < 2; nCntLR++)
			{
				g_aBG[nCnt].fTex[nCntLR] += 0.0002f;
				g_aBG[nCnt].fTex[nCntLR] += pPlayer->move.x * 0.0002f;
			}
		case 1:
			for (int nCntLR = 0; nCntLR < 2; nCntLR++)
			{
				g_aBG[nCnt].fTex[nCntLR] += 0.0002f;
				g_aBG[nCnt].fTex[nCntLR] += pPlayer->move.x * 0.0002f;
			}
			break;
		}

		pVtx_BG[0].tex = D3DXVECTOR2(g_aBG[nCnt].fTex[0], 0.0f);
		pVtx_BG[1].tex = D3DXVECTOR2(g_aBG[nCnt].fTex[1], 0.0f);
		pVtx_BG[2].tex = D3DXVECTOR2(g_aBG[nCnt].fTex[0], 1.0f);
		pVtx_BG[3].tex = D3DXVECTOR2(g_aBG[nCnt].fTex[1], 1.0f);

		pVtx_BG += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_BG->Unlock();
}

//************************************************
//背景構造体のアドレスを渡す
//************************************************
BG* GetInfo_BG(void)
{
	return &g_aBG[0];
}