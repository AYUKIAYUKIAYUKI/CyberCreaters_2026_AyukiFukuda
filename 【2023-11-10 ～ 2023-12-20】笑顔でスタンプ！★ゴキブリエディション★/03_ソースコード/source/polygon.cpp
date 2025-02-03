////************************************************
////
////ポリゴン生成[polygon.cpp]
////Author：福田歩希
////
////************************************************
//#include "polygon.h"
//
////マクロ定義
//#define AMOUNT_POLYGON	(1)
//
////グローバル変数
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//頂点バッファへのポインタ
//LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;	//テクスチャへのポインタ
//Polygon g_aPolygon[AMOUNT_POLYGON] = {};
//
////************************************************
////ポリゴン初期
////************************************************
//void InitPolygon(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
//
//	//ポリゴン情報初期化
//	for (int i = 0; i < AMOUNT_POLYGON; i++)
//	{
//		g_aPolygon[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aPolygon[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	}
//
//	//テクスチャの読込み
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\texture\\dain.png",
//		&g_pTexturePolygon);
//
//	//頂点バッファの生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_POLYGON,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffPolygon,
//		NULL);
//
//	//頂点情報のポインタ
//	VERTEX_3D* pVtx;
//
//	//頂点バッファをロックし頂点情報時へのポインタを取得
//	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int i = 0; i < AMOUNT_POLYGON; i++)
//	{
//		//頂点座標の設定
//		pVtx[0].pos = D3DXVECTOR3(-25.0f, 0.0f, 25.0f);
//		pVtx[1].pos = D3DXVECTOR3(25.0f, 0.0f, 25.0f);
//		pVtx[2].pos = D3DXVECTOR3(-25.0f, 0.0f, -25.0f);
//		pVtx[3].pos = D3DXVECTOR3(25.0f, 0.0f, -25.0f);
//
//		//法線ベクトルの設定
//		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//		//頂点カラーの初期設定
//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//テクスチャ座標の初期設定
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += AMOUNT_VTX;
//	}
//
//	//頂点バッファをアンロック
//	g_pVtxBuffPolygon->Unlock();
//}
//
////************************************************
////ポリゴン破棄
////************************************************
//void UninitPolygon(void)
//{
//	//テクスチャの破棄
//	if (g_pTexturePolygon != NULL)
//	{
//		g_pTexturePolygon->Release();
//		g_pTexturePolygon = NULL;
//	}
//
//	//頂点バッファの破棄
//	if (g_pVtxBuffPolygon != NULL)
//	{
//		g_pVtxBuffPolygon->Release();
//		g_pVtxBuffPolygon = NULL;
//	}
//}
//
////************************************************
////ポリゴン更新
////************************************************
//void UpdatePolygon(void)
//{
//	
//}
//
////************************************************
////ポリゴン描画
////************************************************
//void DrawPolygon(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
//
//	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
//	
//	for (int i = 0; i < AMOUNT_POLYGON; i++)
//	{
//		//ワールドマトリックスの初期化
//		D3DXMatrixIdentity(&g_aPolygon[i].mtxWorld);
//
//		//向きを反映1
//		D3DXMatrixRotationYawPitchRoll(&mtxRot,
//			g_aPolygon[i].rot.y,
//			g_aPolygon[i].rot.x,
//			g_aPolygon[i].rot.z);
//
//		//向きを反映2
//		D3DXMatrixMultiply(&g_aPolygon[i].mtxWorld,
//			&g_aPolygon[i].mtxWorld,
//			&mtxRot);
//
//		//位置を反映1
//		D3DXMatrixTranslation(&mtxTrans,
//			g_aPolygon[i].pos.x,
//			g_aPolygon[i].pos.y,
//			g_aPolygon[i].pos.z);
//
//		//位置を反映2
//		D3DXMatrixMultiply(&g_aPolygon[i].mtxWorld,
//			&g_aPolygon[i].mtxWorld,
//			&mtxTrans);
//
//		//ワールドマトリックスの設定
//		pDevice->SetTransform(D3DTS_WORLD, &g_aPolygon[i].mtxWorld);
//
//		//頂点バッファをデータストリームに設定
//		pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));
//
//		//頂点フォーマットの設定
//		pDevice->SetFVF(FVF_VERTEX_3D);
//
//		//テクスチャの設定
//		pDevice->SetTexture(0, g_pTexturePolygon);
//
//		//ポリゴンの描画
//		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
//	}
//}