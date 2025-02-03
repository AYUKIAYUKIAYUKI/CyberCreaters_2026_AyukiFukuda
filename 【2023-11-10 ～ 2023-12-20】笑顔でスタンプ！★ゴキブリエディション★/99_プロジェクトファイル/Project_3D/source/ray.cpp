//************************************************
//
//レイ[ray.cpp]
//Author：福田歩希
//
//************************************************
#include "ray.h"

#include "camera.h"
#include "player.h"

//マクロ定義
#define AMOUNT_RAY	(1)	//レイの数
#define SPAN_RAY	(1.0f)	//レイの広さ
#define HEIGHT_RAY	(1000.0f)	//レイの高さ

#define COLUMN_RAY	(31)	//列(線の方)
#define LINE_RAY	(100)	//行(こっちも)

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRay = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRay = NULL;	//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffRay = NULL;	//インデックスバッファへのポインタ
Ray g_aRay[AMOUNT_RAY] = {};	//レイ情報
static const float g_F = 1.0f;	//定数1.0f
/* 1ポリゴン当たり */
static const int g_nAmountVtx = (COLUMN_RAY * LINE_RAY);	//頂点の数
static const int g_nAmountPrimitive = (((COLUMN_RAY - 1) * (LINE_RAY - 1)) * 2) + ((LINE_RAY - 2) * 4);	//面の数
static const int g_nAmountIdx = g_nAmountPrimitive + 2;	//インデックスの数
static const float g_COLUMN = g_F / (COLUMN_RAY - 1);	//総列分の1
static const float g_LINE = g_F / (LINE_RAY - 1);	//総行分の1

//************************************************
//レイ初期
//************************************************
void InitRay(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	for (int i = 0; i < AMOUNT_RAY; i++)
	{
		g_aRay[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRay[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRay[i].fPA = 0.0f;
	}

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\",
		&g_pTextureRay);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nAmountVtx * AMOUNT_RAY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRay,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffRay->Lock(0, 0, (void**)&pVtx, 0);

	float fP[3] = {};	/* [0]→列、[1]→行、[2]→texX (座標用とtex用が必要な理由要研究) */
	for (int i = 0, j = 0; i < g_nAmountVtx; i++, j++)
	{
		//1列分ループしきった場合
		if (j >= COLUMN_RAY)
		{
			fP[1] += g_LINE;	/* 総行分の1増加 */
			j = 0;	/* 列カウントリセット */
			fP[0] = 0.0f;	/* 円柱なので列位置もリセット */
		}

		fP[2] = g_COLUMN * (float)j;	/* 列カウント分、総列分の1増加 */

		//頂点座標の設定
		pVtx[i].pos = D3DXVECTOR3(-cosf(fP[0]) * SPAN_RAY,
			HEIGHT_RAY * (fP[1]),
			sinf(fP[0]) * SPAN_RAY);

		//巻き具合…？(要研究)
		fP[0] += D3DX_PI * (2.0f / (COLUMN_RAY - 1));

		//法線ベクトルの設定
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの初期設定
		pVtx[i].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

		//テクスチャ座標の初期設定
		pVtx[i].tex = D3DXVECTOR2(-fP[2] * 2.0f, -fP[1]);
	}

	//頂点バッファをアンロック
	g_pVtxBuffRay->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nAmountIdx * AMOUNT_RAY,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffRay,
		NULL);

	//インデックスバッファのポインタ
	WORD* pIdx;

	//インデックスバッファをロック
	g_pIdxBuffRay->Lock(0, 0, (void**)&pIdx, 0);

	int Z = 0;	//行数カウント
	while (1)	/* ループ回数は縮退ワープ数 */
	{
		//行の起点から列を展開する
		for (int X = 0; X < COLUMN_RAY; X++, pIdx += 2)	/* 2頂点セットで列がずれていく */
		{
			pIdx[0] = (WORD)(COLUMN_RAY + X + (Z * COLUMN_RAY));	/* 列数自体が起点のインデックスになる */
			pIdx[1] = (WORD)(X + (Z * COLUMN_RAY));
		}

		//縮退ワープが出来なくなればループを抜ける
		if (Z >= LINE_RAY - 2) break;

		pIdx[0] = (WORD)((COLUMN_RAY * (Z + 1)) - 1);	/* (列数 * (該当行 + 1)) - 1でその行の右上の角 */
		pIdx[1] = (WORD)((Z + 2) * COLUMN_RAY);	/* (該当行 + 2) * 列数で起点のさらに1行下へ */

		pIdx += 2;
		Z++;	/* 行の起点を1段下げる */
	}

	//インデックスバッファをアンロック
	g_pIdxBuffRay->Unlock();
}

//************************************************
//レイ破棄
//************************************************
void UninitRay(void)
{
	//テクスチャの破棄
	if (g_pTextureRay != NULL)
	{
		g_pTextureRay->Release();
		g_pTextureRay = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRay != NULL)
	{
		g_pVtxBuffRay->Release();
		g_pVtxBuffRay = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffRay != NULL)
	{
		g_pIdxBuffRay->Release();
		g_pIdxBuffRay = NULL;
	}
}

//************************************************
//レイ更新(未完成)
//************************************************
void UpdateRay(void)
{
	/* テスト状態 */
	const Player* pPlayer = GetInfoPlayer();
	const Camera* pCamera = GetInfoCamera();

	for (int i = 0; i < AMOUNT_RAY; i++)
	{
		//光線のピボットをプレイヤーの位置に
		g_aRay[i].pos = pPlayer->pos;

		//光線の向きをカメラ→注視点の方向に
		g_aRay[i].rot.x = -pCamera->fPA + D3DX_PI * 0.5f;
		g_aRay[i].rot.y = pCamera->rot.y;
		g_aRay[i].rot.z;
	}
}

//************************************************
//レイ描画
//************************************************
void DrawRay(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//ライトをオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ワイヤーフレーム描画開始
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	for (int i = 0; i < AMOUNT_RAY; i++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aRay[i].mtxWorld);

		//向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aRay[i].rot.y,
			g_aRay[i].rot.x,
			g_aRay[i].rot.z);

		//向きを反映2
		D3DXMatrixMultiply(&g_aRay[i].mtxWorld,
			&g_aRay[i].mtxWorld,
			&mtxRot);

		//位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_aRay[i].pos.x,
			g_aRay[i].pos.y,
			g_aRay[i].pos.z);

		//位置を反映2
		D3DXMatrixMultiply(&g_aRay[i].mtxWorld,
			&g_aRay[i].mtxWorld,
			&mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aRay[i].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffRay, 0, sizeof(VERTEX_3D));

		//頂点バッファをデータストリームに設定
		pDevice->SetIndices(g_pIdxBuffRay);

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRay);

		//レイの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_nAmountVtx,
			0, g_nAmountPrimitive);

		//ライトをオン
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	//ワイヤーフレーム描画終了
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}