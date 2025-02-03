//************************************************
//
// レティクル[reticle.cpp]
// Author：福田歩希
//
//************************************************

/*/ インクルードファイル /*/
#include "reticle.h"
// 諸処理
#include "camera.h"
 
/*/ マクロ定義 /*/
#define AMOUNT_RETICLE 4	// レティクル最大数

// グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffReticle = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureReticle = NULL;		// テクスチャへのポインタ
Reticle g_Reticle[MAX_PLAYER];						// レティクル情報

//************************************************
// レティクル初期
//************************************************
void InitReticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_RETICLE; i++)
	{ // レティクル情報リセット
		g_Reticle[i].use = false;								// 使用フラグ
		g_Reticle[i].pos_moved = { 0.0f, 0.0f, 0.0f };			// 変動位置
		g_Reticle[i].pos = { 0.0f, 0.0f, 0.0f };				// 位置
		g_Reticle[i].rot = { 0.0f, 0.0f, 0.0f };				// 向き
		g_Reticle[i].span = { 0.0f, 0.0f };						// 大きさ用
		g_Reticle[i].angle = 0.0f;								// 角度
		g_Reticle[i].length = 0.0f;								// 対角線用
		g_Reticle[i].remain = 0;								// 寿命
		g_Reticle[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// 色
	}

	/*--------------------------------------------*/

	// テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\reticle.png",
		&g_pTextureReticle);

	/*--------------------------------------------*/

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_RETICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffReticle,
		NULL);

	// 頂点情報のポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffReticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_RETICLE; i++, pVtx += AMOUNT_VTX)
	{ // 頂点情報のリセット

		// 頂点座標の初期設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 視錐台の拡大率(?)の初期設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

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
	g_pVtxBuffReticle->Unlock();
}

//************************************************
// レティクル生成
//************************************************
void CreateReticle(int joined)
{
	for (int i = 0, j = 0; i < joined; i++)
	{
		if (i == 2)
		{
			j++;
		}

		// 適当にパラメータ設定
		g_Reticle[i].use = true;

		if (joined == 1)
		{
			g_Reticle[i].pos =
			{
				SCREEN_HALFWIDTH, SCREEN_HALFHEIGHT, 0.0f
			};

			g_Reticle[i].span = { 30.0f, 30.0f };	// 大きさ：適量
		}
		else if (joined == 2)
		{
			g_Reticle[i].pos =
			{
				SCREEN_HALFWIDTH * 0.5f + i * (SCREEN_HALFWIDTH), SCREEN_HALFHEIGHT, 0.0f
			};

			g_Reticle[i].span = { 20.0f, 20.0f };	// 大きさ：適量
		}
		else
		{
			g_Reticle[i].pos =
			{
				SCREEN_HALFWIDTH * 0.5f + i * (SCREEN_HALFWIDTH)-j * SCREEN_WIDTH, (SCREEN_HALFHEIGHT * 0.5f) + j * SCREEN_HALFHEIGHT, 0.0f
			};

			g_Reticle[i].span = { 15.0f, 15.0f };	// 大きさ：適量
		}

		// 角度を算出
		g_Reticle[i].angle = atan2f(g_Reticle[i].span.x, g_Reticle[i].span.y);

		// 対角線を算出
		g_Reticle[i].length = sqrtf(g_Reticle[i].span.x * g_Reticle[i].span.x +
			g_Reticle[i].span.y * g_Reticle[i].span.y);
	}
}

//************************************************
// レティクル破棄
//************************************************
void UninitReticle(void)
{
	if (g_pTextureReticle != NULL)
	{ // テクスチャの破棄
		g_pTextureReticle->Release();
		g_pTextureReticle = NULL;
	}

	if (g_pVtxBuffReticle != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffReticle->Release();
		g_pVtxBuffReticle = NULL;
	}
}

//************************************************
// レティクル更新
//************************************************
void UpdateReticle(int joined)
{
	// 生成
	CreateReticle(joined);

	// 展開
	SetVtxReticle(joined);
}

//************************************************
// レティクル展開
//************************************************
void SetVtxReticle(int joined)
{
	// 頂点情報のポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffReticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < joined; i++, pVtx += AMOUNT_VTX)
	{
		// 変形などあれば反映
		pVtx[0].pos =
		{
			g_Reticle[i].pos.x + sinf(g_Reticle[i].rot.z - (D3DX_PI - g_Reticle[i].angle)) * g_Reticle[i].length,
			g_Reticle[i].pos.y + cosf(g_Reticle[i].rot.z - (D3DX_PI - g_Reticle[i].angle)) * g_Reticle[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Reticle[i].pos.x + sinf(g_Reticle[i].rot.z + (D3DX_PI - g_Reticle[i].angle)) * g_Reticle[i].length,
			g_Reticle[i].pos.y + cosf(g_Reticle[i].rot.z + (D3DX_PI - g_Reticle[i].angle)) * g_Reticle[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Reticle[i].pos.x + sinf(g_Reticle[i].rot.z - g_Reticle[i].angle) * g_Reticle[i].length,
			g_Reticle[i].pos.y + cosf(g_Reticle[i].rot.z - g_Reticle[i].angle) * g_Reticle[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Reticle[i].pos.x + sinf(g_Reticle[i].rot.z + g_Reticle[i].angle) * g_Reticle[i].length,
			g_Reticle[i].pos.y + cosf(g_Reticle[i].rot.z + g_Reticle[i].angle) * g_Reticle[i].length,
			0.0f
		};
	}

	g_pVtxBuffReticle->Unlock();
}

//************************************************
// レティクル描画
//************************************************
void DrawReticle(int id)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスへのポインタ

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffReticle, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureReticle);

	// レティクルの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, id * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//************************************************
// レティクル情報を取得
//************************************************
Reticle* GetInfoReticle(void)
{
	return &g_Reticle[0];
}