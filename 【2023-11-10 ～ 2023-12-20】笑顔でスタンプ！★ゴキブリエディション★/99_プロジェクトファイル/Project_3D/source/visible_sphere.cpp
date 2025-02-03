////************************************************
////
////球形の当たり判定を可視化[visible_sphere.cpp]
////Author：福田歩希
////
////************************************************
//#include "visible_sphere.h"
//
//#include "player.h"
//
////マクロ定義
//#define AMOUNT_SPHERE	(1024)	//スフィアの最大数
//
//#define COLUMN_SPHERE	(11)	//列(線の方)
//#define LINE_SPHERE	(11)	//行(こっちも)
//
////グローバル変数
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSphere = NULL;	//頂点バッファへのポインタ
//LPDIRECT3DTEXTURE9 g_pTextureSphere = NULL;	//テクスチャへのポインタ
//LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSphere = NULL;	//インデックスバッファへのポインタ
//Sphere g_aSphere[AMOUNT_SPHERE] = {};	//レイ情報
//static const float g_F = 1.0f;	//定数1.0f
///* 1ポリゴン当たり */
//static const int g_nAmountVtx = (COLUMN_SPHERE * LINE_SPHERE);	//頂点の数
//static const int g_nAmountPrimitive = (((COLUMN_SPHERE - 1) * (LINE_SPHERE - 1)) * 2) + ((LINE_SPHERE - 2) * 4);	//面の数
//static const int g_nAmountIdx = g_nAmountPrimitive + 2;	//インデックスの数
//static const float g_COLUMN = g_F / (COLUMN_SPHERE - 1);	//総列分の1
//static const float g_LINE = g_F / (LINE_SPHERE - 1);	//総行分の1
//static const float g_COLUMNr = (D3DX_PI * 2.0f) / (COLUMN_SPHERE - 1);	//総列分の1の角度
//static const float g_LINEr = D3DX_PI / (LINE_SPHERE - 1);	//総行分の1の角度
//
////************************************************
////スフィア初期
////************************************************
//void InitVisible_Sphere(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
//
//	for (int i = 0; i < AMOUNT_SPHERE; i++)
//	{
//		g_aSphere[i].bUse = false;
//		g_aSphere[i].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
//		g_aSphere[i].pPos = NULL;
//		g_aSphere[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//	}
//
//	//頂点バッファの生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nAmountVtx * AMOUNT_SPHERE,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffSphere,
//		NULL);
//
//	//頂点情報のポインタ
//	VERTEX_3D* pVtx;
//
//	//頂点バッファをロックし頂点情報時へのポインタを取得
//	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int i = 0; i < g_nAmountVtx; i++)
//	{
//		//頂点座標の設定
//		pVtx[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//法線ベクトルの設定
//		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//		//頂点カラーの初期設定
//		pVtx[i].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);
//
//		//テクスチャ座標の初期設定
//		pVtx[i].tex = D3DXVECTOR2(0.0f, 0.0f);
//	}
//
//	//頂点バッファをアンロック
//	g_pVtxBuffSphere->Unlock();
//
//	//インデックスバッファの生成
//	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nAmountIdx * AMOUNT_SPHERE,
//		D3DUSAGE_WRITEONLY,
//		D3DFMT_INDEX16,
//		D3DPOOL_MANAGED,
//		&g_pIdxBuffSphere,
//		NULL);
//
//	//インデックスバッファのポインタ
//	WORD* pIdx;
//
//	//インデックスバッファをロック
//	g_pIdxBuffSphere->Lock(0, 0, (void**)&pIdx, 0);
//
//	int Z = 0;	//行数カウント
//	while (1)	/* ループ回数は縮退ワープ数 */
//	{
//		//行の起点から列を展開する
//		for (int X = 0; X < COLUMN_SPHERE; X++, pIdx += 2)	/* 2頂点セットで列がずれていく */
//		{
//			pIdx[0] = (WORD)(COLUMN_SPHERE + X + (Z * COLUMN_SPHERE));	/* 列数自体が起点のインデックスになる */
//			pIdx[1] = (WORD)(X + (Z * COLUMN_SPHERE));
//		}
//
//		//縮退ワープが出来なくなればループを抜ける
//		if (Z >= LINE_SPHERE - 2) break;
//
//		pIdx[0] = (WORD)((COLUMN_SPHERE * (Z + 1)) - 1);	/* (列数 * (該当行 + 1)) - 1でその行の右上の角 */
//		pIdx[1] = (WORD)((Z + 2) * COLUMN_SPHERE);	/* (該当行 + 2) * 列数で起点のさらに1行下へ */
//
//		pIdx += 2;
//		Z++;	/* 行の起点を1段下げる */
//	}
//
//	//インデックスバッファをアンロック
//	g_pIdxBuffSphere->Unlock();
//}
//
////************************************************
////スフィア展開
////************************************************
//void SetSizeVisible_Sphere(const float fRadius, D3DXCOLOR col, D3DXVECTOR3* pPos)
//{
//	//頂点情報のポインタ
//	VERTEX_3D* pVtx;
//
//	//頂点バッファをロックし頂点情報時へのポインタを取得
//	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int i = 0; i < AMOUNT_SPHERE; i++, pVtx += g_nAmountVtx)
//	{
//		if (g_aSphere[i].bUse) continue;
//
//		g_aSphere[i].bUse = true;
//
//		float fArg = 0.0f;	//φ
//		float fAZ = -(D3DX_PI * 0.5f);	//θ
//		for (int j = 0; j < g_nAmountVtx; j++, fArg += g_COLUMNr)
//		{
//			//角度の調整
//			if (fArg >= (D3DX_PI * 2.0f))
//			{
//				fArg = 0.0f;
//				fAZ += g_LINEr;
//			}
//
//			//頂点座標の設定
//			pVtx[j].pos =
//			{
//				(fRadius * cosf(fArg) * cosf(fAZ)),
//				(fRadius * sinf(fAZ)),
//				(fRadius * sinf(fArg) * cosf(fAZ))
//			};
//
//			pVtx[j].col = col;
//		}
//
//		/* 対象のワールド座標に同期する */
//		g_aSphere[i].pPos = pPos;
//
//		break;
//	}
//
//	//頂点バッファをアンロック
//	g_pVtxBuffSphere->Unlock();
//}
//
////************************************************
////スフィア破棄
////************************************************
//void UninitVisible_Sphere(void)
//{
//	//頂点バッファの破棄
//	if (g_pVtxBuffSphere != NULL)
//	{
//		g_pVtxBuffSphere->Release();
//		g_pVtxBuffSphere = NULL;
//	}
//
//	//インデックスバッファの破棄
//	if (g_pIdxBuffSphere != NULL)
//	{
//		g_pIdxBuffSphere->Release();
//		g_pIdxBuffSphere = NULL;
//	}
//}
//
////************************************************
////スフィア更新(未完成)
////************************************************
//void UpdateVisible_Sphere(void)
//{
//	//対象物の中心に
//	for (int i = 0; i < AMOUNT_SPHERE; i++)
//	{
//		if (!g_aSphere[i].bUse) continue;
//
//		g_aSphere[i].pos = *g_aSphere[i].pPos;
//	}
//}
//
////************************************************
////スフィア消滅
////************************************************
//void DisappearVisible_Sphere(D3DXVECTOR3* pPos)
//{
//	for (int i = 0; i < AMOUNT_SPHERE; i++)
//	{
//		//アドレスが一致すればその影を削除
//		if (g_aSphere[i].pPos == pPos)
//		{
//			g_aSphere[i].bUse = false;
//			break;
//		}
//	}
//}
//
////************************************************
////スフィア描画
////************************************************
//void DrawVisible_Sphere(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
//
//	//ライトをオフ
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
//
//	for (int i = 0; i < AMOUNT_SPHERE; i++)
//	{
//		if (!g_aSphere[i].bUse) continue;
//
//		//ワールドマトリックスの初期化
//		D3DXMatrixIdentity(&g_aSphere[i].mtxWorld);
//
//		//位置を反映1
//		D3DXMatrixTranslation(&mtxTrans,
//			g_aSphere[i].pos.x,
//			g_aSphere[i].pos.y,
//			g_aSphere[i].pos.z);
//
//		//位置を反映2
//		D3DXMatrixMultiply(&g_aSphere[i].mtxWorld,
//			&g_aSphere[i].mtxWorld,
//			&mtxTrans);
//
//		//ワールドマトリックスの設定
//		pDevice->SetTransform(D3DTS_WORLD, &g_aSphere[i].mtxWorld);
//
//		//頂点バッファをデータストリームに設定
//		pDevice->SetStreamSource(0, g_pVtxBuffSphere, 0, sizeof(VERTEX_3D));
//
//		//インデックスバッファをデータストリームに設定
//		pDevice->SetIndices(g_pIdxBuffSphere);
//
//		//頂点フォーマットの設定
//		pDevice->SetFVF(FVF_VERTEX_3D);
//
//		//スフィアの描画
//		pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, i * g_nAmountVtx, 0, g_nAmountVtx,
//			0, g_nAmountPrimitive);
//	}
//
//	//ライトをオン
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//}