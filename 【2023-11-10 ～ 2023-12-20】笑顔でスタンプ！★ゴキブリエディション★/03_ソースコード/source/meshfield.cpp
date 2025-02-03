//************************************************
//
//メッシュフィールド生成[meshfield.cpp]
//Author：福田歩希
//
//************************************************
#include "meshfield.h"

//マクロ定義
#define AMOUNT_MESHFIELD	(1)	//メッシュフィールドの数
#define SPAN_MESHFIELD	(40.0f)	//メッシュフィールドの大きさ

#define COLUMN_MESHFIELD	(5)	//列(線の方)
#define LINE_MESHFIELD	(5)	//行(こっちも)

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;	//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;	//インデックスバッファへのポインタ
Meshfield g_aMeshfield[AMOUNT_MESHFIELD] = {};
static const float g_F = 1.0f;	//定数1.0f
/* 1ポリゴン当たり */
static const int g_nAmountVtx = (COLUMN_MESHFIELD * LINE_MESHFIELD);	//頂点の数
static const int g_nAmountPrimitive = (((COLUMN_MESHFIELD - 1) * (LINE_MESHFIELD - 1)) * 2) + ((LINE_MESHFIELD - 2) * 4);	//面の数
static const int g_nAmountIdx = g_nAmountPrimitive + 2;	//インデックスの数
static const float g_COLUMN = g_F / (COLUMN_MESHFIELD - 1);	//総列分の1
static const float g_LINE = g_F / (LINE_MESHFIELD - 1);	//総行分の1

//************************************************
//メッシュフィールド初期
//************************************************
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	for (int i = 0; i < AMOUNT_MESHFIELD; i++)
	{
		g_aMeshfield[i].pos = D3DXVECTOR3(0.0f, 10.0f, 30.0f);
		g_aMeshfield[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\UV.jpg",
		&g_pTextureMeshfield);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nAmountVtx * AMOUNT_MESHFIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	float fP[2] = {};	/* [0]→列、[1]→行 */
	for (int i = 0, j = 0; i < g_nAmountVtx; i++, j++)
	{
		//1列分ループしきった場合
		if (j >= COLUMN_MESHFIELD)
		{
			fP[1] += g_LINE;	/* 総行分の1増加 */
			j = 0;	/* 列カウントリセット */
		}

		fP[0] = g_COLUMN * (float)j;	/* 列カウント分、総列分の1増加 */

		//頂点座標の設定
		pVtx[i].pos = D3DXVECTOR3((fP[0] * SPAN_MESHFIELD) - (SPAN_MESHFIELD * 0.5f),
			0.0f,
			(-fP[1] * SPAN_MESHFIELD) + (SPAN_MESHFIELD * 0.5f));

		/* ↓解放で奇数番頂点を上昇 */
		if (i != 0 && i % 2 != 0) pVtx[i].pos.y = 5.0f;

		//法線ベクトルの設定
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの初期設定
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx[i].tex = D3DXVECTOR2(fP[0], fP[1]);
	}

	//頂点バッファをアンロック
	g_pVtxBuffMeshfield->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nAmountIdx * AMOUNT_MESHFIELD,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshfield,
		NULL);

	//インデックスバッファのポインタ
	WORD* pIdx;

	//インデックスバッファをロック
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	int Z = 0;	//行数カウント用
	while (1)	/* ループ回数は縮退ワープ数 */
	{
		//行の起点から列を展開する
		for (int X = 0; X < COLUMN_MESHFIELD; X++, pIdx += 2)	/* 2頂点セットで列がずれていく */
		{
			pIdx[0] = (WORD)(COLUMN_MESHFIELD + X + (Z * COLUMN_MESHFIELD));	/* 列数自体が起点のインデックスになる */
			pIdx[1] = (WORD)(X + (Z * COLUMN_MESHFIELD));
		}

		//縮退ワープが出来なくなればループを抜ける
		if (Z >= LINE_MESHFIELD - 2) break;

		pIdx[0] = (WORD)((COLUMN_MESHFIELD * (Z + 1)) - 1);	/* (列数 * (該当行 + 1)) - 1でその行の右上の角 */
		pIdx[1] = (WORD)((Z + 2) * COLUMN_MESHFIELD);	/* (該当行 + 2) * 列数で起点のさらに1行下へ */

		pIdx += 2;
		Z++;	/* 行の起点を1段下げる */
	}

	//インデックスバッファをアンロック
	g_pIdxBuffMeshfield->Unlock();
}

//************************************************
//メッシュフィールド破棄
//************************************************
void UninitMeshfield(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffMeshfield != NULL)
	{
		g_pIdxBuffMeshfield->Release();
		g_pIdxBuffMeshfield = NULL;
	}
}

//************************************************
//メッシュフィールド更新
//************************************************
void UpdateMeshfield(void)
{

}

//************************************************
//メッシュフィールド描画
//************************************************
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	for (int i = 0; i < AMOUNT_MESHFIELD; i++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aMeshfield[i].mtxWorld);

		//向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aMeshfield[i].rot.y,
			g_aMeshfield[i].rot.x,
			g_aMeshfield[i].rot.z);

		//向きを反映2
		D3DXMatrixMultiply(&g_aMeshfield[i].mtxWorld,
			&g_aMeshfield[i].mtxWorld,
			&mtxRot);

		//位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_aMeshfield[i].pos.x,
			g_aMeshfield[i].pos.y,
			g_aMeshfield[i].pos.z);

		//位置を反映2
		D3DXMatrixMultiply(&g_aMeshfield[i].mtxWorld,
			&g_aMeshfield[i].mtxWorld,
			&mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aMeshfield[i].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

		//頂点バッファをデータストリームに設定
		pDevice->SetIndices(g_pIdxBuffMeshfield);

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMeshfield);

		//メッシュフィールドの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_nAmountVtx,
			0, g_nAmountPrimitive);
	}
}