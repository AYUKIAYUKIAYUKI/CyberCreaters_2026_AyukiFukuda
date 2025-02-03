////************************************************
////
////矩形の当たり判定を可視化[visible_rect.cpp]
////Author：福田歩希
////
////************************************************
//#include "visible_rect.h"
//
//#include "player.h"
//
////マクロ定義
//#define AMOUNT_RECT	(128)	//レクトの最大数
//
////グローバル変数
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRect = NULL;	//頂点バッファへのポインタ
//LPDIRECT3DINDEXBUFFER9 g_pIdxBuffRect = NULL;	//インデックスバッファへのポインタ
//Rect g_aRect[AMOUNT_RECT] = {};	//レクト情報
///* 1レクト当たり */
//static const int g_nAmountVtx = 8;	//頂点の数
//static const int g_nAmountPrimitive = 12;	//辺の数
//static const int g_nAmountIdx = g_nAmountPrimitive * 2;	//インデックスの数
//
////************************************************
////レクト初期
////************************************************
//void InitVisible_Rect(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
//
//	for (int i = 0; i < AMOUNT_RECT; i++)
//	{
//		g_aRect[i].bUse = false;
//		g_aRect[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aRect[i].pPos = NULL;
//		g_aRect[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//	}
//
//	//頂点バッファの生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nAmountVtx * AMOUNT_RECT,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffRect,
//		NULL);
//
//	//頂点情報のポインタ
//	VERTEX_3D* pVtx;
//
//	//頂点バッファをロックし頂点情報時へのポインタを取得
//	g_pVtxBuffRect->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int i = 0; i < g_nAmountVtx * AMOUNT_RECT; i++)
//	{
//		//頂点座標の設定
//		pVtx[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//法線ベクトルの設定
//		pVtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//頂点カラーの初期設定
//		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//テクスチャ座標の初期設定
//		pVtx[i].tex = D3DXVECTOR2(0.0f, 0.0f);
//	}
//
//	//頂点バッファをアンロック
//	g_pVtxBuffRect->Unlock();
//
//	//インデックスバッファの生成
//	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nAmountIdx * AMOUNT_RECT,
//		D3DUSAGE_WRITEONLY,
//		D3DFMT_INDEX16,
//		D3DPOOL_MANAGED,
//		&g_pIdxBuffRect,
//		NULL);
//
//	//インデックスバッファのポインタ
//	WORD* pIdx;
//
//	//インデックスバッファをロック
//	g_pIdxBuffRect->Lock(0, 0, (void**)&pIdx, 0);
//
//	for (int i = 0; i < AMOUNT_RECT; i++)
//	{
//		/* X軸に平行な線を引く */
//		for (int j = 0; j < 8; j++, pIdx++)
//		{
//			pIdx[0] = (WORD)j;
//		}
//
//		/* Y軸に平行な線を引く */
//		for (int j = 0, k = 0; j < 4; j++, pIdx += 2)
//		{
//			if (j == 2) k += 2;	/* 0,1,4,5をレイの始点にするため3,4のインデックスを飛ばす */
//
//			pIdx[0] = (WORD)(j + k);
//			pIdx[1] = (WORD)(j + 2 + k);
//		}
//
//		/* Z軸に平行な線を引く */
//		for (int j = 0; j < 4; j++, pIdx += 2)
//		{
//			pIdx[0] = (WORD)(j);
//			pIdx[1] = (WORD)(j + 4);
//		}
//	}
//
//	//インデックスバッファをアンロック
//	g_pIdxBuffRect->Unlock();
//}
//
////************************************************
////レクト展開
////************************************************
//void SetSizeVisible_Rect(const COLLISION_AABB obj, D3DXCOLOR col, D3DXVECTOR3* pPos)
//{
//	//頂点情報のポインタ
//	VERTEX_3D* pVtx;
//
//	//頂点バッファをロックし頂点情報時へのポインタを取得
//	g_pVtxBuffRect->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int i = 0; i < AMOUNT_RECT; i++, pVtx += g_nAmountVtx)
//	{
//		if (g_aRect[i].bUse) continue;
//
//		g_aRect[i].bUse = true;
//
//		/* 対象のワールド座標を相殺し頂点を展開する */
//		pVtx[0].pos = { obj.min.x - pPos->x, obj.max.y - pPos->y, obj.min.z - pPos->z };
//		pVtx[1].pos = { obj.max.x - pPos->x, obj.max.y - pPos->y, obj.min.z - pPos->z };
//		pVtx[2].pos = { obj.min.x - pPos->x, obj.min.y - pPos->y, obj.min.z - pPos->z };
//		pVtx[3].pos = { obj.max.x - pPos->x, obj.min.y - pPos->y, obj.min.z - pPos->z };
//		pVtx[4].pos = { obj.min.x - pPos->x, obj.max.y - pPos->y, obj.max.z - pPos->z };
//		pVtx[5].pos = { obj.max.x - pPos->x, obj.max.y - pPos->y, obj.max.z - pPos->z };
//		pVtx[6].pos = { obj.min.x - pPos->x, obj.min.y - pPos->y, obj.max.z - pPos->z };
//		pVtx[7].pos = { obj.max.x - pPos->x, obj.min.y - pPos->y, obj.max.z - pPos->z };
//
//		for (int j = 0; j < g_nAmountVtx; j++)
//		{
//			pVtx[j].col = col;
//		}
//
//		/* 対象のワールド座標に同期する */
//		g_aRect[i].pPos = pPos;
//
//		break;
//	}
//
//	//頂点バッファをアンロック
//	g_pVtxBuffRect->Unlock();
//}
//
////************************************************
////レクト破棄
////************************************************
//void UninitVisible_Rect(void)
//{
//	//頂点バッファの破棄
//	if (g_pVtxBuffRect != NULL)
//	{
//		g_pVtxBuffRect->Release();
//		g_pVtxBuffRect = NULL;
//	}
//
//	//インデックスバッファの破棄
//	if (g_pIdxBuffRect != NULL)
//	{
//		g_pIdxBuffRect->Release();
//		g_pIdxBuffRect = NULL;
//	}
//}
//
////************************************************
////レクト更新
////************************************************
//void UpdateVisible_Rect(void)
//{
//	//対象物の中心に
//	for (int i = 0; i < AMOUNT_RECT; i++)
//	{
//		if (!g_aRect[i].bUse) continue;
//
//		g_aRect[i].pos = *g_aRect[i].pPos;
//	}
//
//	///* 線を太くするため3軸方向に少しずつずらす */
//	//g_aRect[1].pos.x += 0.15f;
//	//g_aRect[2].pos.x += -0.15f;
//
//	//g_aRect[3].pos.y += 0.15f;
//	//g_aRect[4].pos.y += -0.15f;
//
//	//g_aRect[5].pos.z += 0.15f;
//	//g_aRect[6].pos.z += -0.15f;
//}
//
////************************************************
////レクト描画
////************************************************
//void DrawVisible_Rect(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
//
//	//ライトをオフ
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
//
//	for (int i = 0; i < AMOUNT_RECT; i++)
//	{
//		if (!g_aRect[i].bUse) continue;
//
//		//ワールドマトリックスの初期化
//		D3DXMatrixIdentity(&g_aRect[i].mtxWorld);
//
//		//位置を反映1
//		D3DXMatrixTranslation(&mtxTrans,
//			g_aRect[i].pos.x,
//			g_aRect[i].pos.y,
//			g_aRect[i].pos.z);
//
//		//位置を反映2
//		D3DXMatrixMultiply(&g_aRect[i].mtxWorld,
//			&g_aRect[i].mtxWorld,
//			&mtxTrans);
//
//		//ワールドマトリックスの設定
//		pDevice->SetTransform(D3DTS_WORLD, &g_aRect[i].mtxWorld);
//
//		//頂点バッファをデータストリームに設定
//		pDevice->SetStreamSource(0, g_pVtxBuffRect, 0, sizeof(VERTEX_3D));
//
//		//インデックスバッファをデータストリームに設定
//		pDevice->SetIndices(g_pIdxBuffRect);
//
//		//頂点フォーマットの設定
//		pDevice->SetFVF(FVF_VERTEX_3D);
//
//		//テクスチャの設定
//		//pDevice->SetTexture(0, NULL);
//
//		//レクトの描画
//		pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, i * g_nAmountVtx, 0, g_nAmountVtx,
//			0, g_nAmountPrimitive);
//	}
//
//	//ライトをオン
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//}