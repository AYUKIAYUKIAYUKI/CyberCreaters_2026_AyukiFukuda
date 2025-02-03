//************************************************
//
// 球形の当たり判定を可視化[visible_sph.cpp]
// Author：福田歩希
//
//************************************************

/*/ インクルードファイル /*/
#include "visible_sph.h"
// 諸処理
#include "player.h"
#include "game.h"

/*/ マクロ定義 /*/
#define AMOUNT_SPHERE 64	// スフィアの最大数
#define COLUMN_SPHERE 11	// 列(線の方)
#define LINE_SPHERE	11		// 行(こっちも)

/*/ グローバル変数 /*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSphere = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureSphere = NULL;			// テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSphere = NULL;		// インデックスバッファへのポインタ
Sph g_Sph[AMOUNT_SPHERE] = {};						// スフィア情報
static const float g_F = 1.0f;						// 1.0f
// 今回の計算用
static const int g_AmountVtx = (COLUMN_SPHERE * LINE_SPHERE);			// 頂点の数
static const int g_AmountPrimitive = (((COLUMN_SPHERE - 1) * (LINE_SPHERE - 1)) * 2) + ((LINE_SPHERE - 2) * 4);	// 面の数
static const int g_AmountIdx = g_AmountPrimitive + 2;					// インデックスの数
static const float g_COLUMN = g_F / (COLUMN_SPHERE - 1);				// 総列分の1
static const float g_LINE = g_F / (LINE_SPHERE - 1);					// 総行分の1
static const float g_COLUMNr = (D3DX_PI * 2.0f) / (COLUMN_SPHERE - 1);	// 総列分の1の角度
static const float g_LINEr = D3DX_PI / (LINE_SPHERE - 1);				// 総行分の1の角度

//************************************************
// スフィア初期
//************************************************
void InitVisibleSph(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_SPHERE; i++)
	{ // スフィア情報をリセット
		g_Sph[i].use = false;
		g_Sph[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Sph[i].pPos = NULL;
		g_Sph[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_Sph[i].dur = -1;
	}

	/*--------------------------------------------*/

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_AmountVtx * AMOUNT_SPHERE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSphere,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SPHERE; i++, pVtx += g_AmountVtx)
	{
		for (int j = 0; j < g_AmountVtx; j++)
		{
			// 頂点座標の設定
			pVtx[j].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 法線ベクトルの設定
			pVtx[j].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 頂点カラーの初期設定
			pVtx[j].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

			// テクスチャ座標の初期設定
			pVtx[j].tex = D3DXVECTOR2(0.0f, 0.0f);
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffSphere->Unlock();

	/*--------------------------------------------*/

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_AmountIdx * AMOUNT_SPHERE,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSphere,
		NULL);

	// インデックスバッファのポインタ
	WORD* pIdx;

	// インデックスバッファをロック
	g_pIdxBuffSphere->Lock(0, 0, (void**)&pIdx, 0);

	int Z = 0;	// 行数カウント用

	while (1)	// ループ回数は縮退ワープ数
	{
		// 行の起点から列を展開する
		for (int X = 0; X < COLUMN_SPHERE; X++, pIdx += 2)
		{ // 2頂点セットで列がずれていく
			pIdx[0] = (WORD)(COLUMN_SPHERE + X + (Z * COLUMN_SPHERE));	// 列数自体が起点のインデックスになる
			pIdx[1] = (WORD)(X + (Z * COLUMN_SPHERE));
		}


		if (Z >= LINE_SPHERE - 2)
		{ // 縮退ワープが出来なくなればループを抜ける
			break;
		}

		pIdx[0] = (WORD)((COLUMN_SPHERE * (Z + 1)) - 1);	// (列数 * (該当行 + 1)) - 1でその行の右上の角
		pIdx[1] = (WORD)((Z + 2) * COLUMN_SPHERE);	// (該当行 + 2) * 列数で起点のさらに1行下へ

		pIdx += 2;
		Z++;	// 行の起点を1段下げる
	}

	// インデックスバッファをアンロック
	g_pIdxBuffSphere->Unlock();
}

//************************************************
// スフィア生成
//************************************************
int CreateVisibleSph(const float rad, D3DXCOLOR col, D3DXVECTOR3* pPos)
{
	VERTEX_3D* pVtx;	// 頂点情報のポインタ
	int id = -1;		// 識別番号格納

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SPHERE; i++, pVtx += g_AmountVtx)
	{
		if (g_Sph[i].use)
		{ // 使用されていればコンティニュー
			continue;
		}

		float yaw = 0.0f;					// 方角
		float pitch = -(D3DX_PI * 0.5f);	// 仰俯

		for (int j = 0; j < g_AmountVtx; j++, yaw += g_COLUMNr)
		{
			// 角度の調整
			if (yaw >= (D3DX_PI * 2.0f))
			{
				yaw = 0.0f;
				pitch += g_LINEr;
			}

			// 頂点座標の設定
			pVtx[j].pos =
			{
				(rad * cosf(yaw) * cosf(pitch)),
				(rad * sinf(pitch)),
				(rad * sinf(yaw) * cosf(pitch))
			};

			// 色の反映
			pVtx[j].col = col;
		}

		g_Sph[i].use = true;	// 使用
		g_Sph[i].pPos = pPos;	// 対象物の位置情報を格納
		id = i;					// 識別番号をコピー

		break;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffSphere->Unlock();

	return id;	// 識別番号を返す
}

//************************************************
// スフィア破棄
//************************************************
void UninitVisibleSph(void)
{
	if (g_pVtxBuffSphere != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffSphere->Release();
		g_pVtxBuffSphere = NULL;
	}

	if (g_pIdxBuffSphere != NULL)
	{ // インデックスバッファの破棄
		g_pIdxBuffSphere->Release();
		g_pIdxBuffSphere = NULL;
	}
}

//************************************************
// スフィア更新
//************************************************
void UpdateVisibleSph(void)
{
	for (int i = 0; i < AMOUNT_SPHERE; i++)
	{
		if (!g_Sph[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// 対象物と位置を同期する
		g_Sph[i].pos = *g_Sph[i].pPos;

		// 簡易スフィア管理
		ManageInstantVisibleSph(i);
	}

	// 行列計算
	CalcMtxVisibleSph();
}

//************************************************
// スフィア用の行列を計算
//************************************************
void CalcMtxVisibleSph(void)
{
	D3DXMATRIX mtxTrans;	// 計算用マトリックス

	for (int i = 0; i < AMOUNT_SPHERE; i++)
	{
		if (!g_Sph[i].use)
		{ //  未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Sph[i].mtxWorld);

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_Sph[i].pos.x,
			g_Sph[i].pos.y,
			g_Sph[i].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_Sph[i].mtxWorld,
			&g_Sph[i].mtxWorld,
			&mtxTrans);
	}
}

//************************************************
// スフィア削除
//************************************************
void DeleteVisibleSph(int id)
{
	// 情報をリセット
	g_Sph[id].use = false;
	g_Sph[id].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Sph[id].pPos = NULL;
	g_Sph[id].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_Sph[id].dur = -1;
}

//************************************************
// スフィア簡易生成
//************************************************
void CreateInstantVisibleSph(float rad, D3DXCOLOR col, D3DXVECTOR3* pPos, int dur)
{
	VERTEX_3D* pVtx;	// 頂点情報のポインタ

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SPHERE; i++, pVtx += g_AmountVtx)
	{
		if (g_Sph[i].use)
		{ // 使用されていればコンティニュー
			continue;
		}

		float yaw = 0.0f;					// 方角
		float pitch = -(D3DX_PI * 0.5f);	// 仰俯

		for (int j = 0; j < g_AmountVtx; j++, yaw += g_COLUMNr)
		{
			// 角度の調整
			if (yaw >= (D3DX_PI * 2.0f))
			{
				yaw = 0.0f;
				pitch += g_LINEr;
			}

			// 頂点座標の設定
			pVtx[j].pos =
			{
				(rad * cosf(yaw) * cosf(pitch)),
				(rad * sinf(pitch)),
				(rad * sinf(yaw) * cosf(pitch))
			};

			// 色の反映
			pVtx[j].col = col;
		}

		g_Sph[i].use = true;	// 使用
		g_Sph[i].pPos = pPos;	// 対象物の位置情報を格納
		g_Sph[i].dur = dur;		// 期間設定

		break;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffSphere->Unlock();
}

//************************************************
// 簡易生成スフィア管理
//************************************************
void ManageInstantVisibleSph(int id)
{
	if (g_Sph[id].dur == -1)
	{ // 継続時間が無限ならリターン
		return;
	}

	if (CntDuration(&g_Sph[id].dur))
	{ // 消去

		DeleteVisibleSph(id);
	}
}

//************************************************
// スフィア描画
//************************************************
void DrawVisibleSph(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ライトをオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSphere, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffSphere);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < AMOUNT_SPHERE; i++)
	{
		if (!g_Sph[i].use)
		{ //  未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		pDevice->SetTransform(D3DTS_WORLD, &g_Sph[i].mtxWorld);

		// テクスチャの設定
		pDevice->SetTexture(0, NULL);

		// スフィアの描画
		pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, i * g_AmountVtx, 0, g_AmountVtx,
			0, g_AmountPrimitive);
	}

	// ライトをオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}