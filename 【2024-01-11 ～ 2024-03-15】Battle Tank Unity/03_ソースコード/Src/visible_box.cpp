//************************************************
//
// 箱形の当たり判定を可視化[visible_box.cpp]
// Author：福田歩希
//
//************************************************

/*---【インクルードファイル】---*/
#include "visible_box.h"

// 諸処理
#include "player.h"
#include "debugproc.h"
#include "input.h"
#include "object.h"

/*---【マクロ定義】---*/
#define MAX_BOX	512	//ボックスの最大数

/*---【グローバル変数】---*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBox = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffBox = NULL;	// インデックスバッファへのポインタ
Box g_Box[MAX_BOX] = {};						// ボックス情報
// 1ボックス当たり
static const int g_AmountVtx = 8;						// 頂点の数
static const int g_AmountPrimitive = 12;				// 辺の数
static const int g_AmountIdx = g_AmountPrimitive * 2;	// インデックスの数

/*---【プロトタイプ宣言】---*/
void SetVtxVisibleBox(void);	// ボックスを展開する

//************************************************
// ボックス初期
//************************************************
void InitVisibleBox(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	/*--------------------------------------------*/

	for (int i = 0; i < MAX_BOX; i++)
	{
		g_Box[i].use = false;
		g_Box[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Box[i].aabb = nullptr;
		g_Box[i].col = { 0.0f, 0.0f, 0.0f, 0.0f };
	}

	/*--------------------------------------------*/

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_AmountVtx * MAX_BOX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBox,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffBox->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_BOX; i++, pVtx += g_AmountVtx)
	{
		for (int j = 0; j < g_AmountVtx; j++)
		{
			// 頂点座標の設定
			pVtx[j].pos = { 0.0f, 0.0f, 0.0f };

			// 法線ベクトルの設定
			pVtx[j].nor = { 0.0f, 0.0f, 0.0f };

			// 頂点カラーの初期設定
			pVtx[j].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の初期設定
			pVtx[j].tex = { 0.0f, 0.0f };
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffBox->Unlock();

	/*--------------------------------------------*/

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_AmountIdx * MAX_BOX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffBox,
		NULL);

	// インデックスバッファのポインタ
	WORD* pIdx;

	// インデックスバッファをロック
	g_pIdxBuffBox->Lock(0, 0, (void**)&pIdx, 0);

	for (int i = 0; i < MAX_BOX; i++)
	{
		// X軸に平行な線を引く
		for (int j = 0; j < 8; j++, pIdx++)
		{
			pIdx[0] = (WORD)j;
		}

		// Y軸に平行な線を引く
		for (int j = 0, k = 0; j < 4; j++, pIdx += 2)
		{
			if (j == 2) k += 2;	// 0,1,4,5をレイの始点にするため3,4のインデックスを飛ばす

			pIdx[0] = (WORD)(j + k);
			pIdx[1] = (WORD)(j + 2 + k);
		}

		// Z軸に平行な線を引く
		for (int j = 0; j < 4; j++, pIdx += 2)
		{
			pIdx[0] = (WORD)(j);
			pIdx[1] = (WORD)(j + 4);
		}
	}

	// インデックスバッファをアンロック
	g_pIdxBuffBox->Unlock();

	// 試験的に箱を表示
	//CreateVisibleBox({ { 0.0f, 0.0f, 0.0f }, { 40.0f, 100.0f, 40.0f } }, { 0.0f, 1.0f, 1.0f, 1.0f }, &g_Box[0].aabb.pos);
}

//************************************************
// ボックス展開
//************************************************
int CreateVisibleBox(COLLISION_AABB* box, D3DXCOLOR col)
{
	VERTEX_3D* pVtx;	// 頂点情報のポインタ
	int id = -1;		// 識別番号格納

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffBox->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_BOX; i++, pVtx += g_AmountVtx)
	{
		if (g_Box[i].use)
		{ // 使用されていたらコンティニュー
			continue;
		}

		g_Box[i].use = true;
		g_Box[i].aabb = box;	// 判定情報のアドレスを渡す

#if 0	// 対象のワールド座標を相殺し頂点を展開

		pVtx[0].pos = { box.min.x - pPos->x, box.max.y - pPos->y, box.min.z - pPos->z };
		pVtx[1].pos = { box.max.x - pPos->x, box.max.y - pPos->y, box.min.z - pPos->z };
		pVtx[2].pos = { box.min.x - pPos->x, box.min.y - pPos->y, box.min.z - pPos->z };
		pVtx[3].pos = { box.max.x - pPos->x, box.min.y - pPos->y, box.min.z - pPos->z };
		pVtx[4].pos = { box.min.x - pPos->x, box.max.y - pPos->y, box.max.z - pPos->z };
		pVtx[5].pos = { box.max.x - pPos->x, box.max.y - pPos->y, box.max.z - pPos->z };
		pVtx[6].pos = { box.min.x - pPos->x, box.min.y - pPos->y, box.max.z - pPos->z };
		pVtx[7].pos = { box.max.x - pPos->x, box.min.y - pPos->y, box.max.z - pPos->z };

#elif 0	// Y軸を補正しつつ展開

		pVtx[0].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[1].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[2].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[3].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[4].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[5].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[6].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[7].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };

#elif 1	// 通常展開

		pVtx[0].pos = { -g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[1].pos = { +g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[2].pos = { -g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[3].pos = { +g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[4].pos = { -g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[5].pos = { +g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[6].pos = { -g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[7].pos = { +g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };

#endif	// 頂点の展開方法分岐

		for (int j = 0; j < g_AmountVtx; j++)
		{
			pVtx[j].col = col;
		}

		break;
	}

	// 頂点バッファをアンロック
	g_pVtxBuffBox->Unlock();

	return id;	// 識別番号を返す
}

//************************************************
// ボックス破棄
//************************************************
void UninitVisibleBox(void)
{
	if (g_pVtxBuffBox != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffBox->Release();
		g_pVtxBuffBox = NULL;
	}

	if (g_pIdxBuffBox != NULL)
	{ // インデックスバッファの破棄
		g_pIdxBuffBox->Release();
		g_pIdxBuffBox = NULL;
	}
}

//************************************************
// ボックス更新
//************************************************
void UpdateVisibleBox(void)
{
	//対象物の中心に
	for (int i = 0; i < MAX_BOX; i++)
	{
		if (!g_Box[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// ベースの判定に同期
		g_Box[i].pos = g_Box[i].aabb->pos;
	}

#if 0	// こちらからオブジェクトを回して箱の寸法を変更するヤツ

	Object* obj = GetInfoObject();

	obj->rot.y += D3DX_PI / 100.0f;

	// 回転を続けているテイの数値
	if (obj->rot.y >= D3DX_PI)
	{
		obj->rot.y = -D3DX_PI;
	}

	PrintDebugProc("\nobj1 rot y：%f\n", obj->rot.y);

	// サイズが変わり続ける
	if (GetKeyboardPress(DIK_SPACE))
	{
		g_Box[0].aabb->vec.x = obj->model.aabb.vec.x;
		g_Box[0].aabb->vec.z = obj->model.aabb.vec.z;
	}
	else
	{
		g_Box[0].aabb->vec.x = obj->model.aabb.vec.x * cosf(obj->rot.y);
	}

#endif

	// ボックスを展開
	SetVtxVisibleBox();

	// 行列計算
	CalcMtxVisibleBox();
}

//************************************************
// ボックスを展開
//************************************************
void SetVtxVisibleBox(void)
{
	VERTEX_3D* pVtx;	// 頂点情報のポインタ

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffBox->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_BOX; i++, pVtx += g_AmountVtx)
	{
		if (!g_Box[i].use)
		{ // 使用されていたらコンティニュー
			continue;
		}

#if 0	// Y軸を補正しつつ展開

		pVtx[0].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[1].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[2].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[3].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[4].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[5].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[6].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[7].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
	
#elif 1	// 通常展開

		pVtx[0].pos = { -g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[1].pos = { +g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[2].pos = { -g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[3].pos = { +g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[4].pos = { -g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[5].pos = { +g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[6].pos = { -g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[7].pos = { +g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };

#endif	// 頂点の展開方法分岐
	}

	// 頂点バッファをアンロック
	g_pVtxBuffBox->Unlock();
}

//************************************************
// ボックス用の行列を計算
//************************************************
void CalcMtxVisibleBox(void)
{
	D3DXMATRIX mtxTrans;	// 計算用マトリックス

	for (int i = 0; i < MAX_BOX; i++)
	{
		if (!g_Box[i].use)
		{ //  未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Box[i].mtxWorld);

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_Box[i].pos.x,
			g_Box[i].pos.y,
			g_Box[i].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_Box[i].mtxWorld,
			&g_Box[i].mtxWorld,
			&mtxTrans);
	}
}

//************************************************
// ボックス削除
//************************************************
void DeleteVisibleBox(int id)
{
	// 情報をリセット
	g_Box[id].use = false;
	g_Box[id].pos = { 0.0f, 0.0f, 0.0f };
	g_Box[id].aabb = nullptr;
	g_Box[id].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//************************************************
// ボックス描画
//************************************************
void DrawVisibleBox(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ライトをオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBox, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffBox);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < MAX_BOX; i++)
	{
		if (!g_Box[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Box[i].mtxWorld);

		// テクスチャの設定
		pDevice->SetTexture(0, NULL);

		// ボックスの描画
		pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, i * g_AmountVtx, 0, g_AmountVtx,
			0, g_AmountPrimitive);
	}

	// ライトをオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}