//************************************************
//
// 影[shadow.cpp]
// Author：福田歩希
//
//************************************************

/*---【インクルードファイル】---*/
#include "shadow.h"

/*---【マクロ定義】---*/
#define AMOUNT_SHADOW 512	// 影の最大数

/*---【グローバル変数】---*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;			// テクスチャへのポインタ
Shadow g_Shadow[AMOUNT_SHADOW];						// 影情報

/*---【プロトタイプ宣言】---*/
void ClearInfoShadow(void);	// 影情報をクリア

//************************************************
// 影初期
//************************************************
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	// 影情報をクリア
	ClearInfoShadow();
	
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureShadow);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SHADOW; i++, pVtx += AMOUNT_VTX)
	{ // 頂点情報のリセット

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の初期設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();

	//// テクスチャ情報を取得
	//ImportTexShadow();

	//// 頂点情報を生成
	//CreateVtxBufferShadow();
}

//************************************************
// テクスチャ情報を読み込む
//************************************************
void ImportTexShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureShadow);
}

//************************************************
// 頂点情報を生成
//************************************************
void CreateVtxBufferShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SHADOW; i++, pVtx += AMOUNT_VTX)
	{ // 頂点情報のリセット

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の初期設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();
}

//************************************************
// 影破棄
//************************************************
void UninitShadow(void)
{
	if (g_pTextureShadow != NULL)
	{ // テクスチャの破棄
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	if (g_pVtxBuffShadow != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//************************************************
// 影生成
//************************************************
int CreateShadow(/*D3DXVECTOR3* pPos, */float rad)
{
	int id = -1;	// 識別番号用

	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		if (g_Shadow[i].use)
		{ // 使用中ならコンティニュー
			continue;
		}

		g_Shadow[i].use = true;
		//g_Shadow[i].pPos = pPos;			// 対象位置を取得
		g_Shadow[i].span = { rad, rad };	// 大きさ反映

		// 角度を算出
		g_Shadow[i].angle = atan2f(g_Shadow[i].span.x, g_Shadow[i].span.y);

		// 対角線を算出
		g_Shadow[i].length = sqrtf(g_Shadow[i].span.x * g_Shadow[i].span.x +
			g_Shadow[i].span.y * g_Shadow[i].span.y);

		id = i;	// 識別番号格納

		break;	// 終了
	}

	return id;	// 一応識別番号を渡す
}

//************************************************
// 影更新
//************************************************
void UpdateShadow(void)
{
	//for (int i = 0; i < AMOUNT_SHADOW; i++)
	//{ // 情報を更新

	//	if (!g_Shadow[i].use)
	//	{ // 未使用ならコンティニュー
	//		continue;
	//	}

	//	// 対象位置に追従
	//	//g_Shadow[i].pos = *g_Shadow[i].pPos;
	//	//g_Shadow[i].pos.y = 1.0f;
	//}

	// ポリゴンを展開
	SetVtxShadow();

	// 行列計算
	CalcMatrixShadow();
}

//************************************************
// 新しい影の追従
//************************************************
void TrackShadow(int id, D3DXVECTOR3 pos)
{
	// 位置を同期
	g_Shadow[id].pos = pos;
	g_Shadow[id].pos.y = 0.5f;

	g_Shadow[id].colA = 1.0f - (pos.y * 0.005f);
}

//************************************************
// 影展開
//************************************************
void SetVtxShadow(void)
{
	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SHADOW; i++, pVtx += AMOUNT_VTX)
	{
		if (!g_Shadow[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// 横
		pVtx[0].pos =
		{
			sinf(g_Shadow[i].rot.z - (D3DX_PI - g_Shadow[i].angle)) * g_Shadow[i].length,
			0.0f,
			-cosf(g_Shadow[i].rot.z - (D3DX_PI - g_Shadow[i].angle)) * g_Shadow[i].length
		};

		pVtx[1].pos =
		{
			sinf(g_Shadow[i].rot.z + (D3DX_PI - g_Shadow[i].angle)) * g_Shadow[i].length,
			0.0f,
			-cosf(g_Shadow[i].rot.z + (D3DX_PI - g_Shadow[i].angle)) * g_Shadow[i].length
		};

		pVtx[2].pos =
		{
			sinf(g_Shadow[i].rot.z - g_Shadow[i].angle) * g_Shadow[i].length,
			0.0f,
			-cosf(g_Shadow[i].rot.z - g_Shadow[i].angle) * g_Shadow[i].length
		};

		pVtx[3].pos =
		{
			sinf(g_Shadow[i].rot.z + g_Shadow[i].angle) * g_Shadow[i].length,
			0.0f,
			-cosf(g_Shadow[i].rot.z + g_Shadow[i].angle) * g_Shadow[i].length
		};


		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Shadow[i].colA);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Shadow[i].colA);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Shadow[i].colA);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Shadow[i].colA);
	}

	g_pVtxBuffShadow->Unlock();
}

//************************************************
// 影消去
//************************************************
void DeleteShadow(int id)
{
	g_Shadow[id].use = false;					// 使用フラグ
	//g_Shadow[id].pPos = nullptr;				// 対象位置
	g_Shadow[id].pos = { 0.0f, 0.0f, 0.0f };	// 位置
	g_Shadow[id].rot = { 0.0f, 0.0f, 0.0f };	// 向き
	g_Shadow[id].span = { 0.0f, 0.0f };			// 大きさ用
	g_Shadow[id].angle = 0.0f;					// 角度
	g_Shadow[id].length = 0.0f;					// 対角線用
	g_Shadow[id].colA = 0.0f;					// 透明度
}

//************************************************
// 影用の行列を計算
//************************************************
void CalcMatrixShadow(void)
{
	D3DXMATRIX mtxTrans;	// 計算用マトリックス

	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		if (!g_Shadow[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Shadow[i].mtxWorld);

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_Shadow[i].pos.x,
			g_Shadow[i].pos.y,
			g_Shadow[i].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_Shadow[i].mtxWorld,
			&g_Shadow[i].mtxWorld,
			&mtxTrans);
	}
}

//************************************************
// 影描画
//************************************************
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxTrans;						// 計算用マトリックス

	// アルファブレンディングを減算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ライト反映を無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		if (!g_Shadow[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[i].mtxWorld);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureShadow);

		// ビルボードの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	// アルファブレンディングを戻す設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ライト反映を有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// 影情報をクリア
//************************************************
void ClearInfoShadow(void)
{
	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		g_Shadow[i].use = false;				// 使用フラグ
		//g_Shadow[i].pPos = nullptr;			// 対象位置
		g_Shadow[i].pos = { 0.0f, 0.0f, 0.0f };	// 位置
		g_Shadow[i].rot = { 0.0f, 0.0f, 0.0f };	// 向き
		g_Shadow[i].span = { 0.0f, 0.0f };		// 大きさ用
		g_Shadow[i].angle = 0.0f;				// 角度
		g_Shadow[i].length = 0.0f;				// 対角線用
		g_Shadow[i].colA = 0.0f;				// 透明度
	}
}