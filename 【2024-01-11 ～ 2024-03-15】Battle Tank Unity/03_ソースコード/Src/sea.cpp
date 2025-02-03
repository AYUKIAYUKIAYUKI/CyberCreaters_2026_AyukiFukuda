//************************************************
//
// 海生成[sea.cpp]
// Author：福田歩希
//
//************************************************

/*/ インクルードファイル /*/
#include "sea.h"

/*/ マクロ定義 /*/
#define AMOUNT_MESHFIELD 1		// 海の数
#define SPAN_MESHFIELD 10000.0f	// 海の大きさ

#define COLUMN_MESHFIELD 41	// 列(線の方)
#define LINE_MESHFIELD 41	// 行(こっちも)

#define NOR_VERIFY 0
#define WAVE_VERIFY	1		// うねうね型にするやつ
#define POINT_VERIFY	0	// 2×2の真ん中の頂点を上げるやつ

/*/ グローバル変数 /*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSea = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureSea = NULL;		// テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSea = NULL;	// インデックスバッファへのポインタ
Sea g_Sea[AMOUNT_MESHFIELD] = {};				// 海用構造体
static const float g_F = 1.0f;					// 汎用定数1.0f
// 今回の計算用
static const int g_AmountVtx = (COLUMN_MESHFIELD * LINE_MESHFIELD);						// 頂点の数
static const int g_AmountPrimitive = (((COLUMN_MESHFIELD - 1) * (LINE_MESHFIELD - 1)) * 2) + ((LINE_MESHFIELD - 2) * 4);	// 面の数
static const int g_AmountIdx = g_AmountPrimitive + 2;									// インデックスの数
static const float g_Column = g_F / (COLUMN_MESHFIELD - 1);								// 総列分の1
static const float g_Line = g_F / (LINE_MESHFIELD - 1);									// 総行分の1
static const int g_VisiblePrimitive = g_AmountPrimitive - ((LINE_MESHFIELD - 2) * 4);	// 可視面の数
float g_wave = 0.0f;																	// 波打ち用
bool g_switch = false;																		// 転換

/*---【プロトタイプ宣言】---*/
void SetVtxSea(void);	// 頂点を展開

//************************************************
// 海初期
//************************************************
void InitSea(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	
	g_wave = 0.0f;		// 波打ち用
	g_switch = false;	// 転換

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_MESHFIELD; i++)
	{ // 海用構造体の情報をクリア
		g_Sea[i].pos = D3DXVECTOR3(0.0f, -150.0f, 0.0f);
		g_Sea[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	/*--------------------------------------------*/

	// テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\water.png",
		&g_pTextureSea);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_AmountVtx * AMOUNT_MESHFIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSea,
		NULL);

	VERTEX_3D* pVtx;	// 頂点情報のポインタ

	/*--------------------------------------------*/

#if 0

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffSea->Lock(0, 0, (void**)&pVtx, 0);

	// ポリゴンごとの外積を取得していく(テスト)
	D3DXVECTOR3 N[g_VisiblePrimitive] = {};		// 面法線ベクトル
	D3DXVECTOR3 V1[g_VisiblePrimitive] = {};	// ベクトル1
	D3DXVECTOR3 V2[g_VisiblePrimitive] = {};	// ベクトル2

	for (int i = 0, vtx = 0; i < g_VisiblePrimitive; i++)
	{ // 可視面の面法線ベクトルを生成
		switch (i % 2)
		{
		case 0:
			// 時計回りのポリゴン
			V1[i] = pVtx[0 + vtx].pos - pVtx[3 + vtx].pos;
			V2[i] = pVtx[4 + vtx].pos - pVtx[3 + vtx].pos;
			D3DXVec3Cross(&N[i], &V1[i], &V2[i]);
			D3DXVec3Normalize(&N[i], &N[i]);
			break;

		case 1:
			// 反時計回りのポリゴン
			V1[i] = pVtx[4 + vtx].pos - pVtx[0 + vtx].pos;
			V2[i] = pVtx[1 + vtx].pos - pVtx[0 + vtx].pos;
			D3DXVec3Cross(&N[i], &V1[i], &V2[i]);
			D3DXVec3Normalize(&N[i], &N[i]);

			// ここで頂点番号をずらす
			vtx++;
			break;
		}

		if (i == (COLUMN_MESHFIELD - 1))
		{
			vtx;
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffSea->Unlock();

#endif

	/*--------------------------------------------*/

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffSea->Lock(0, 0, (void**)&pVtx, 0);

	float fP[2] = {};	/*/ [0]→列、[1]→行 /*/
	for (int i = 0, j = 0; i < g_AmountVtx; i++, j++)
	{
		// 1列分ループしきった場合
		if (j >= COLUMN_MESHFIELD)
		{
			fP[1] += g_Line;	/*/ 総行分の1増加 /*/
			j = 0;	/*/ 列カウントリセット /*/
		}

		fP[0] = g_Column * (float)j;	/*/ 列カウント分、総列分の1増加 /*/

		// 頂点座標の設定
		pVtx[i].pos = D3DXVECTOR3((fP[0] * SPAN_MESHFIELD) - (SPAN_MESHFIELD * 0.5f),
			0.0f,
			(-fP[1] * SPAN_MESHFIELD) + (SPAN_MESHFIELD * 0.5f));

#if WAVE_VERIFY

		if (i != 0 && i % 2 != 0)
		{ // 奇数番頂点を上にあげる
			pVtx[i].pos.y = 30.0f;
		}

#elif POINT_VERIFY

		if (i == 4)
		{ // 2×2ブロックの中心の頂点を上にあげる
			pVtx[i].pos.y = 50.0f;
		}

#endif // 頂点上げるシリーズ

#if NOR_VERIFY

		// 法線ベクトルの設定
		if (i == 0 || i == 3 || i == 4)
		{
			pVtx[i].nor = N[0];
		}
		else
		{
			pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}

#endif

		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの初期設定
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の初期設定
		pVtx[i].tex = D3DXVECTOR2(fP[0], fP[1]);
	}

	// 頂点バッファをアンロック
	g_pVtxBuffSea->Unlock();

	/*--------------------------------------------*/

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_AmountIdx * AMOUNT_MESHFIELD,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSea,
		NULL);

	WORD* pIdx;	// インデックスバッファのポインタ

	// インデックスバッファをロック
	g_pIdxBuffSea->Lock(0, 0, (void**)&pIdx, 0);

	int Z = 0;	// 行数カウント用

	while (1)	// ループ回数は縮体ワープ数
	{
		// 行の起点から列を展開する
		for (int X = 0; X < COLUMN_MESHFIELD; X++, pIdx += 2)	// 2頂点セットで列がずれていく
		{
			pIdx[0] = (WORD)(COLUMN_MESHFIELD + X + (Z * COLUMN_MESHFIELD));	// 列数自体が起点のインデックスになる
			pIdx[1] = (WORD)(X + (Z * COLUMN_MESHFIELD));
		}

		// 縮体ワープが出来なくなればループを抜ける
		if (Z >= LINE_MESHFIELD - 2) break;

		pIdx[0] = (WORD)((COLUMN_MESHFIELD * (Z + 1)) - 1);	// (列数 * (該当行 + 1)) - 1でその行の右上の角
		pIdx[1] = (WORD)((Z + 2) * COLUMN_MESHFIELD);		// (該当行 + 2) * 列数で起点のさらに1行下へ

		pIdx += 2;
		Z++;	// 行の起点を1段下げる
	}

	// 行列計算
	CalcMtxSea();

	// インデックスバッファをアンロック
	g_pIdxBuffSea->Unlock();
}

//************************************************
// 海破棄
//************************************************
void UninitSea(void)
{
	if (g_pTextureSea != NULL)
	{ // テクスチャの破棄
		g_pTextureSea->Release();
		g_pTextureSea = NULL;
	}

	if (g_pVtxBuffSea != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffSea->Release();
		g_pVtxBuffSea = NULL;
	}

	if (g_pIdxBuffSea != NULL)
	{ // インデックスバッファの破棄
		g_pIdxBuffSea->Release();
		g_pIdxBuffSea = NULL;
	}
}

//************************************************
// 海更新
//************************************************
void UpdateSea(void)
{
	// 頂点位置を変更
	SetVtxSea();
#ifdef _DEBUG
	// 行列計算
	CalcMtxSea();
#endif
}

//************************************************
// 頂点更新
//************************************************
void SetVtxSea(void)
{
	VERTEX_3D* pVtx;	// 頂点情報のポインタ

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffSea->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < g_AmountVtx; i++)
	{
		// 適当にそれらしく動作
		if (g_switch)
		{
			pVtx[i].pos.y += sinf(g_wave) * 0.5f;

			if (i % 2 == 0)
			{
				pVtx[i].pos.y += cosf(g_wave) * 0.5f;
			}
		}
		else
		{
			pVtx[i].pos.y += sinf(g_wave) * 0.5f;

			if (i % 3 == 0)
			{
				pVtx[i].pos.y += cosf(g_wave) * 0.5f;
			}
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffSea->Unlock();

	// 循環する
	g_wave += D3DX_PI * 0.005f;

	if (g_wave > D3DX_PI)
	{
		g_wave = -D3DX_PI;
		
		g_switch = !g_switch;
	}
}

//************************************************
// 海用のワールドマトリックスを計算
//************************************************
void CalcMtxSea(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	for (int i = 0; i < AMOUNT_MESHFIELD; i++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Sea[i].mtxWorld);

		// 向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Sea[i].rot.y,
			g_Sea[i].rot.x,
			g_Sea[i].rot.z);

		// 向きを反映2
		D3DXMatrixMultiply(&g_Sea[i].mtxWorld,
			&g_Sea[i].mtxWorld,
			&mtxRot);

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_Sea[i].pos.x,
			g_Sea[i].pos.y,
			g_Sea[i].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_Sea[i].mtxWorld,
			&g_Sea[i].mtxWorld,
			&mtxTrans);
	}
}

//************************************************
// 海描画
//************************************************
void DrawSea(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSea, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffSea);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < AMOUNT_MESHFIELD; i++)
	{
		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Sea[i].mtxWorld);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureSea);

		// 海の描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_AmountVtx,
			0, g_AmountPrimitive);
	}
}