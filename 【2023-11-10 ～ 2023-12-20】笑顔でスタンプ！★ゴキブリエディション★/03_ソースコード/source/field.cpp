//************************************************
//
//地面生成[field.cpp]
//Author：福田歩希
//
//************************************************
#include "field.h"

//マクロ定義
#define AMOUNT_FIELD	(1)	//床の数
#define SPAN_FIELD	(250.0f)	//床のサイズ

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureField = NULL;	//テクスチャへのポインタ
Field g_aField[AMOUNT_FIELD] = {};

//************************************************
//地面初期
//************************************************
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	for (int i = 0; i < AMOUNT_FIELD; i++)
	{
		g_aField[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\soil_circle.png",
		&g_pTextureField);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_FIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_FIELD; i++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-SPAN_FIELD, 0.0f, SPAN_FIELD);
		pVtx[1].pos = D3DXVECTOR3(SPAN_FIELD, 0.0f, SPAN_FIELD);
		pVtx[2].pos = D3DXVECTOR3(-SPAN_FIELD, 0.0f, -SPAN_FIELD);
		pVtx[3].pos = D3DXVECTOR3(SPAN_FIELD, 0.0f, -SPAN_FIELD);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	g_pVtxBuffField->Unlock();
}

//************************************************
//地面破棄
//************************************************
void UninitField(void)
{
	//テクスチャの破棄
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//************************************************
//地面更新
//************************************************
void UpdateField(void)
{

}

//************************************************
//地面描画
//************************************************
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	for (int i = 0; i < AMOUNT_FIELD; i++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aField[i].mtxWorld);

		//向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aField[i].rot.y,
			g_aField[i].rot.x,
			g_aField[i].rot.z);

		//向きを反映2
		D3DXMatrixMultiply(&g_aField[i].mtxWorld,
			&g_aField[i].mtxWorld,
			&mtxRot);

		//位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_aField[i].pos.x,
			g_aField[i].pos.y,
			g_aField[i].pos.z);

		//位置を反映2
		D3DXMatrixMultiply(&g_aField[i].mtxWorld,
			&g_aField[i].mtxWorld,
			&mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aField[i].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureField);

		//地面の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}