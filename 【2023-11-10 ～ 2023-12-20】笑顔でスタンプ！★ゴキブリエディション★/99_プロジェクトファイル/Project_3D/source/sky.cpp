//************************************************
//
//空[sky.cpp]
//Author：福田歩希
//
//************************************************
#include "sky.h"

#include "debugproc.h"

#include "enemy.h"
#include "player.h"
#include "shadow.h"

//マクロ定義
#define AMOUNT_SKY	(1)	//空の数
#define SPAN_SKY	(250.0f)	//空の広さ
#define HEIGHT_SKY	(200.0f)	//空の高さ

#define COLUMN_SKY	(61)	//列(線の方)
#define LINE_SKY	(2)	//行(こっちも)

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSky = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureSky = NULL;	//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSky = NULL;	//インデックスバッファへのポインタ
Sky g_aSky[AMOUNT_SKY] = {};	//空情報
static const float g_F = 1.0f;	//定数1.0f
/* 1ポリゴン当たり */
static const int g_nAmountVtx = (COLUMN_SKY * LINE_SKY);	//頂点の数
static const int g_nAmountPrimitive = (((COLUMN_SKY - 1) * (LINE_SKY - 1)) * 2) + ((LINE_SKY - 2) * 4);	//面の数
static const int g_nAmountIdx = g_nAmountPrimitive + 2;	//インデックスの数
static const float g_COLUMN = g_F / (COLUMN_SKY - 1);	//総列分の1
static const float g_LINE = g_F / (LINE_SKY - 1);	//総行分の1

//************************************************
//空初期
//************************************************
void InitSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	for (int i = 0; i < AMOUNT_SKY; i++)
	{
		g_aSky[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSky[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\sky.png",
		&g_pTextureSky);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nAmountVtx * AMOUNT_SKY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSky,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffSky->Lock(0, 0, (void**)&pVtx, 0);

	float fP[3] = {};	/* [0]→列、[1]→行、[2]→texX (座標用とtex用が必要な理由要研究) */
	for (int i = 0, j = 0; i < g_nAmountVtx; i++, j++)
	{
		//1列分ループしきった場合
		if (j >= COLUMN_SKY)
		{
			fP[1] += g_LINE;	/* 総行分の1増加 */
			j = 0;	/* 列カウントリセット */
			fP[0] = 0.0f;	/* 円柱なので列位置もリセット */
		}

		fP[2] = g_COLUMN * (float)j;	/* 列カウント分、総列分の1増加 */

		//頂点座標の設定
		pVtx[i].pos = D3DXVECTOR3(sinf(D3DX_PI - fP[0]) * SPAN_SKY,
			HEIGHT_SKY * (fP[1]),
			cosf(D3DX_PI - fP[0]) * SPAN_SKY);

		//巻き具合…？(要研究)
		fP[0] += D3DX_PI * (2.0f / (COLUMN_SKY - 1));

		//法線ベクトルの設定
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの初期設定
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx[i].tex = D3DXVECTOR2(-fP[2] * 2.0f, -fP[1]);
	}

	//頂点バッファをアンロック
	g_pVtxBuffSky->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nAmountIdx * AMOUNT_SKY,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSky,
		NULL);

	//インデックスバッファのポインタ
	WORD* pIdx;

	//インデックスバッファをロック
	g_pIdxBuffSky->Lock(0, 0, (void**)&pIdx, 0);

	int Z = 0;	//行数カウント
	while (1)	/* ループ回数は縮退ワープ数 */
	{
		//行の起点から列を展開する
		for (int X = 0; X < COLUMN_SKY; X++, pIdx += 2)	/* 2頂点セットで列がずれていく */
		{
			pIdx[0] = (WORD)(COLUMN_SKY + X + (Z * COLUMN_SKY));	/* 列数自体が起点のインデックスになる */
			pIdx[1] = (WORD)(X + (Z * COLUMN_SKY));
		}

		//縮退ワープが出来なくなればループを抜ける
		if (Z >= LINE_SKY - 2) break;

		pIdx[0] = (WORD)((COLUMN_SKY * (Z + 1)) - 1);	/* (列数 * (該当行 + 1)) - 1でその行の右上の角 */
		pIdx[1] = (WORD)((Z + 2) * COLUMN_SKY);	/* (該当行 + 2) * 列数で起点のさらに1行下へ */

		pIdx += 2;
		Z++;	/* 行の起点を1段下げる */
	}

	//インデックスバッファをアンロック
	g_pIdxBuffSky->Unlock();
}

//************************************************
//空破棄
//************************************************
void UninitSky(void)
{
	//テクスチャの破棄
	if (g_pTextureSky != NULL)
	{
		g_pTextureSky->Release();
		g_pTextureSky = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSky != NULL)
	{
		g_pVtxBuffSky->Release();
		g_pVtxBuffSky = NULL;
	}

	//インデックスバッファの破棄
	if (g_pIdxBuffSky != NULL)
	{
		g_pIdxBuffSky->Release();
		g_pIdxBuffSky = NULL;
	}
}

//************************************************
//空更新
//************************************************
void UpdateSky(void)
{
	Player* pPlayer = GetInfoPlayer();

	D3DXVECTOR3 VecPlayer = pPlayer->pos - g_aSky[0].pos;
	float DistPlayer = sqrtf((VecPlayer.x * VecPlayer.x) + (VecPlayer.y * VecPlayer.y) + (VecPlayer.z * VecPlayer.z));

	D3DXVECTOR3 NorVec = { 0.0f,0.0f,0.0f };

	D3DXVec3Normalize(&NorVec, &VecPlayer);

	if (DistPlayer > SPAN_SKY - 15.0f)
	{
		//はみ出ようものなら円周に強制固定
		pPlayer->pos = NorVec * (SPAN_SKY - 15.0f);
	}

	PrintDebugProc("Vector:%f %f %f\n", VecPlayer.x, VecPlayer.y, VecPlayer.z);
	PrintDebugProc("Distance:%f\n", DistPlayer);
	PrintDebugProc("test:%f %f %f\n", NorVec.x, NorVec.y, NorVec.z);

	Enemy* pEnemy = GetInfoEnemy();

	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		if (!pEnemy[i].bUse) continue;

		D3DXVECTOR3 VecEnemy = pEnemy[i].pos - g_aSky[0].pos;
		float DistEnemy = sqrtf((VecEnemy.x * VecEnemy.x) + (VecEnemy.y * VecEnemy.y) + (VecEnemy.z * VecEnemy.z));

		D3DXVec3Normalize(&NorVec, &VecEnemy);

		if (DistEnemy > SPAN_SKY)
		{
			//はみ出ようものなら消滅
			pEnemy[i].bUse = false;
			pEnemy[i].nState = EnemyStateNormal;
			pEnemy[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pEnemy[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pEnemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pEnemy[i].fRadius = 0.0f;
			pEnemy[i].nLife = 0;
			pEnemy[i].nCntState = 0;
			pEnemy[i].nNowMotion = EnemyMotionStateNormal;
			pEnemy[i].nOldMotion = EnemyMotionStateNormal;

			DisappearShadow(&pEnemy[i].pos);
		}
	}
}

//************************************************
//空描画
//************************************************
void DrawSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	for (int i = 0; i < AMOUNT_SKY; i++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aSky[i].mtxWorld);

		//向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aSky[i].rot.y,
			g_aSky[i].rot.x,
			g_aSky[i].rot.z);

		//向きを反映2
		D3DXMatrixMultiply(&g_aSky[i].mtxWorld,
			&g_aSky[i].mtxWorld,
			&mtxRot);

		//位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_aSky[i].pos.x,
			g_aSky[i].pos.y,
			g_aSky[i].pos.z);

		//位置を反映2
		D3DXMatrixMultiply(&g_aSky[i].mtxWorld,
			&g_aSky[i].mtxWorld,
			&mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aSky[i].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffSky, 0, sizeof(VERTEX_3D));

		//頂点バッファをデータストリームに設定
		pDevice->SetIndices(g_pIdxBuffSky);

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureSky);

		//空の描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_nAmountVtx,
			0, g_nAmountPrimitive);
	}
}