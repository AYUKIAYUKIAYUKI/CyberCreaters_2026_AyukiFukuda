//************************************************
//
//影生成[shadow.cpp]
//Author：福田歩希
//
//************************************************
#include "shadow.h"

#include "debugproc.h"

#include "player.h"

//マクロ定義
#define AMOUNT_SHADOW	(512)	//影の数

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;	//テクスチャへのポインタ
Shadow g_aShadow[AMOUNT_SHADOW];	//影情報

//************************************************
//影初期
//************************************************
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//影情報を初期化
	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		g_aShadow[i].nIdx = 0;
		g_aShadow[i].fSize = 0.0f;
		g_aShadow[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[i].pPos = NULL;
		g_aShadow[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[i].bUse = false;
	}

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\shadow000.jpg",
		&g_pTextureShadow);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	//頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();
}

//************************************************
//影破棄
//************************************************
void UninitShadow(void)
{
	//テクスチャの破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//************************************************
//影セット
//************************************************
void SetInfoShadow(float fSize, D3DXVECTOR3* pPos)
{
	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		if (!g_aShadow[i].bUse)
		{
			g_aShadow[i].nIdx = i;
			g_aShadow[i].bUse = true;
			g_aShadow[i].pPos = pPos;
			g_aShadow[i].fSize = fSize;

			//サイズセット
			SetSizeShadow(i, MODE_GAME);

			break;
		}
	}
}

//************************************************
//影サイズセット
//************************************************
void SetSizeShadow(int nCnt, int mode)
{
	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX * nCnt;

	if (mode == MODE_GAME)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCnt].fSize, 0.0f, g_aShadow[nCnt].fSize);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCnt].fSize, 0.0f, g_aShadow[nCnt].fSize);
		pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nCnt].fSize, 0.0f, -g_aShadow[nCnt].fSize);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCnt].fSize, 0.0f, -g_aShadow[nCnt].fSize);
	}
	else
	{
		Player* pPlayer = GetInfoPlayer();

		g_aShadow[nCnt].fSize = pPlayer->aParts[0].mtxWorld._42;

		pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCnt].fSize, 0.0f, g_aShadow[nCnt].fSize);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCnt].fSize, 0.0f, g_aShadow[nCnt].fSize);
		pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nCnt].fSize, 0.0f, -g_aShadow[nCnt].fSize);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCnt].fSize, 0.0f, -g_aShadow[nCnt].fSize);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - pPlayer->aParts[0].mtxWorld._42 * 0.015f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - pPlayer->aParts[0].mtxWorld._42 * 0.015f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - pPlayer->aParts[0].mtxWorld._42 * 0.015f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - pPlayer->aParts[0].mtxWorld._42 * 0.015f);
	}

	//頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();
}

//************************************************
//影更新
//************************************************
void UpdateShadow(int mode)
{
	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		if (mode != MODE_TITLE)
		{
			if (g_aShadow[i].bUse)
			{
				//影は下に追従
				g_aShadow[i].pos = *g_aShadow[i].pPos;
				g_aShadow[i].pos.y = 0.01f;
			}
		}
		else
		{
			if (g_aShadow[i].bUse)
			{
				Player* pPlayer = GetInfoPlayer();

				//影はモデルパーツに追従
				g_aShadow[i].pos.x = pPlayer->aParts[0].mtxWorld._41;
				g_aShadow[i].pos.z = pPlayer->aParts[0].mtxWorld._43;
				g_aShadow[i].pos.y = 0.01f;

				//特別にサイズ変更
				SetSizeShadow(i, mode);
			}
		}
	}
}

//************************************************
//影消滅
//************************************************
void DisappearShadow(D3DXVECTOR3* pPos)
{
	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		//アドレスが一致すればその影を削除
		if (g_aShadow[i].pPos == pPos)
		{
			g_aShadow[i].bUse = false;

			break;
		}
	}
}

//************************************************
//影描画
//************************************************
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		if (g_aShadow[i].bUse)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aShadow[i].mtxWorld);

			//向きを反映1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aShadow[i].rot.y,
				g_aShadow[i].rot.x,
				g_aShadow[i].rot.z);

			//向きを反映2
			D3DXMatrixMultiply(&g_aShadow[i].mtxWorld,
				&g_aShadow[i].mtxWorld,
				&mtxRot);

			//位置を反映1
			D3DXMatrixTranslation(&mtxTrans,
				g_aShadow[i].pos.x,
				g_aShadow[i].pos.y,
				g_aShadow[i].pos.z);

			//位置を反映2
			D3DXMatrixMultiply(&g_aShadow[i].mtxWorld,
				&g_aShadow[i].mtxWorld,
				&mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[i].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureShadow);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}

	//アルファテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//減算合成の解除
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}