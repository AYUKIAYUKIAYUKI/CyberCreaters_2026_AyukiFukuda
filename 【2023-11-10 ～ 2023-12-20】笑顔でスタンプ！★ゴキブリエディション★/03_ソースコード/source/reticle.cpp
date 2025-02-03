//************************************************
//
//レティクル[reticle.cpp]
//Author：福田歩希
//
//************************************************
#include "reticle.h"

#include "camera.h"
#include "shadow.h"

//マクロ定義
#define AMOUNT_RETICLE	(1)	//レティクル数
#define SPAN_RETICLE	(30.0f)	//レティクルサイズ

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffReticle = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureReticle = NULL;	//テクスチャへのポインタ
Reticle g_aReticle[AMOUNT_RETICLE] = {};

//************************************************
//レティクル初期
//************************************************
void InitReticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//レティクル情報初期化
	for (int i = 0; i < AMOUNT_RETICLE; i++)
	{
		g_aReticle[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aReticle[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\250.png",
		&g_pTextureReticle);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_RETICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffReticle,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffReticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_RETICLE; i++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	//頂点バッファをアンロック
	g_pVtxBuffReticle->Unlock();

	SizeSetReticle();
}

//************************************************
//レティクル破棄
//************************************************
void UninitReticle(void)
{
	//テクスチャの破棄
	if (g_pTextureReticle != NULL)
	{
		g_pTextureReticle->Release();
		g_pTextureReticle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffReticle != NULL)
	{
		g_pVtxBuffReticle->Release();
		g_pVtxBuffReticle = NULL;
	}
}

//************************************************
//レティクル展開
//************************************************
void SizeSetReticle(void)
{
	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffReticle->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-SPAN_RETICLE, SPAN_RETICLE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SPAN_RETICLE, SPAN_RETICLE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-SPAN_RETICLE, -SPAN_RETICLE, -0.0f);
	pVtx[3].pos = D3DXVECTOR3(SPAN_RETICLE, -SPAN_RETICLE, -0.0f);

	//頂点バッファをアンロック
	g_pVtxBuffReticle->Unlock();
}

//************************************************
//レティクル更新
//************************************************
void UpdateReticle(void)
{
	Camera* pCamera = GetInfoCamera();

	//注視点の指す先にレティクルを設置
	g_aReticle[0].pos = pCamera->posR;
}

//************************************************
//レティクル描画
//************************************************
void DrawReticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//ライトをオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMATRIX mtxTrans;	//計算用マトリックス

	//ビューマトリックス取得
	D3DXMATRIX mtxView;

	for (int i = 0; i < AMOUNT_RETICLE; i++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aReticle[i].mtxWorld);

		//ビューマトリックス取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンをカメラの正面に向け続ける
		D3DXMatrixInverse(&g_aReticle[i].mtxWorld, NULL, &mtxView);	//逆行列を求める

		g_aReticle[i].mtxWorld._41 = 0.0f;
		g_aReticle[i].mtxWorld._42 = 0.0f;
		g_aReticle[i].mtxWorld._43 = 0.0f;

		//位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_aReticle[i].pos.x,
			g_aReticle[i].pos.y,
			g_aReticle[i].pos.z);

		//位置を反映2
		D3DXMatrixMultiply(&g_aReticle[i].mtxWorld,
			&g_aReticle[i].mtxWorld,
			&mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aReticle[i].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffReticle, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureReticle);

		//レティクルの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//ライトをオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//************************************************
//レティクル情報を取得
//************************************************
Reticle* GetInfoReticle(void)
{
	return &g_aReticle[0];
}