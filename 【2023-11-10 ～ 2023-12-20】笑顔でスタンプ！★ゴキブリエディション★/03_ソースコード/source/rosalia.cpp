//************************************************
//
//ロザリア生成[rosalia.cpp]
//Author：福田歩希
//
//************************************************
#include "rosalia.h"

#include "sound.h"

#include "player.h"
#include "shadow.h"

//マクロ定義
#define AMOUNT_ROSALIA	(1)	//ロザリアの数
#define SPAN_ROZALIA	(5.0f)	//サイズ

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRosalia = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRosalia = NULL;	//テクスチャへのポインタ
Rosalia g_aRosalia[AMOUNT_ROSALIA] = {};

//************************************************
//ロザリア初期
//************************************************
void InitRosalia(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//ロザリア情報初期化
	for (int i = 0; i < AMOUNT_ROSALIA; i++)
	{
		g_aRosalia[i].pos = D3DXVECTOR3(0.0f, 10.0f, 90.0f);
		g_aRosalia[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Rozalia.png",
		&g_pTextureRosalia);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_ROSALIA,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRosalia,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffRosalia->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_ROSALIA; i++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	g_pVtxBuffRosalia->Unlock();

	//初回のみ、サイズセット
	SetSizeRosalia();
}

//************************************************
//ロザリア破棄
//************************************************
void UninitRosalia(void)
{
	//テクスチャの破棄
	if (g_pTextureRosalia != NULL)
	{
		g_pTextureRosalia->Release();
		g_pTextureRosalia = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRosalia != NULL)
	{
		g_pVtxBuffRosalia->Release();
		g_pVtxBuffRosalia = NULL;
	}
}

//************************************************
//ロザリア更新
//************************************************
void UpdateRosalia(void)
{
	////距離計算
	//Player* pPlayer = GetInfoPlayer();
	//D3DXVECTOR3 Vector = pPlayer[0].pos - g_aRosalia[0].pos;
	//float fDistance = sqrtf((Vector.x * Vector.x) + (Vector.z * Vector.z)) * 0.5f;

	////音量情報を取得
	//float* pVol = GetInfoSoundVol();

	////離れていると消音
	//pVol[SOUND_LABEL_ROSALIA] = 0.0f;

	////一定範囲内で音量変更
	//if (fDistance < 100.0f)
	//{
	//	//いい感じの割合で近づくと音量増加
	//	pVol[SOUND_LABEL_ROSALIA] = (100.0f - fDistance) / 100;
	//}

	////最接近で爆音
	//if (pVol[SOUND_LABEL_ROSALIA] >= 0.9f)
	//{
	//	pVol[SOUND_LABEL_ROSALIA] = 1000.0f;
	//}

	////音量を反映
	//SetInfoSoundVol(SOUND_LABEL_ROSALIA);
}

//************************************************
//ロザリアサイズセット
//************************************************
void SetSizeRosalia(void)
{
	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffRosalia->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_ROSALIA; i++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-SPAN_ROZALIA, SPAN_ROZALIA * 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SPAN_ROZALIA, SPAN_ROZALIA * 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SPAN_ROZALIA, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SPAN_ROZALIA, 0.0f, 0.0f);

		pVtx += AMOUNT_VTX;
	}

	//頂点バッファをアンロック
	g_pVtxBuffRosalia->Unlock();
}

//************************************************
//ロザリア描画
//************************************************
void DrawRosalia(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//ライトをオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMATRIX mtxTrans;	//計算用マトリックス

	//ビューマトリックス取得
	D3DXMATRIX mtxView;

	for (int i = 0; i < AMOUNT_ROSALIA; i++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aRosalia[i].mtxWorld);

		//ビューマトリックス取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンをカメラの正面に向け続ける
		D3DXMatrixInverse(&g_aRosalia[i].mtxWorld, NULL, &mtxView);	//逆行列を求める

		g_aRosalia[i].mtxWorld._41 = 0.0f;
		g_aRosalia[i].mtxWorld._42 = 0.0f;
		g_aRosalia[i].mtxWorld._43 = 0.0f;

		//位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_aRosalia[i].pos.x,
			g_aRosalia[i].pos.y,
			g_aRosalia[i].pos.z);

		//位置を反映2
		D3DXMatrixMultiply(&g_aRosalia[i].mtxWorld,
			&g_aRosalia[i].mtxWorld,
			&mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aRosalia[i].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffRosalia, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRosalia);

		//ロザリアの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//ライトをオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}