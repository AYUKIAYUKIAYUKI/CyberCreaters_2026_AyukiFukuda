//************************************************
//
//エフェクト生成[effect.cpp]
//Author：福田歩希
//
//************************************************
#include "effect.h"

//マクロ定義
#define AMOUNT_EFFECT	(1024)	//エフェクトの数
#define SPAN_EFFECT	(4.0f)	//エフェクトの大きさ

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;	//テクスチャへのポインタ
Effect g_aEffect[AMOUNT_EFFECT] = {};	//エフェクト情報

//************************************************
//エフェクト初期
//************************************************
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//エフェクト情報初期化
	for (int i = 0; i < AMOUNT_EFFECT; i++)
	{
		g_aEffect[i].bUse = false;
		g_aEffect[i].nStyle = 0;
		g_aEffect[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEffect[i].fDecrease = 0.0f;
	}

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\shadow000.jpg",
		&g_pTextureEffect);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_EFFECT; i++)
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
	g_pVtxBuffEffect->Unlock();
}

//************************************************
//エフェクト破棄
//************************************************
void UninitEffect(void)
{
	//テクスチャの破棄
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//************************************************
//エフェクト設定
//************************************************
void SetInfoEffect(int nStyle, D3DXVECTOR3 pos, D3DXCOLOR col)
{
	for (int i = 0; i < AMOUNT_EFFECT; i++)
	{
		if (!g_aEffect[i].bUse)
		{
			g_aEffect[i].bUse = true;
			g_aEffect[i].nStyle = nStyle;
			g_aEffect[i].pos = pos;
			g_aEffect[i].col = col;
			g_aEffect[i].fDecrease = 0.1f;

			//種類に合わせてサイズをセット
			SetSizeEffect(i);

			break;
		}
	}
}

//************************************************
//エフェクトサイズセット
//************************************************
void SetSizeEffect(int nCnt)
{
	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX * nCnt;

	//サイズ変更
	switch (g_aEffect[nCnt].nStyle)
	{
	case EffectStyleBullet:
		pVtx[0].pos = D3DXVECTOR3(-SPAN_EFFECT, SPAN_EFFECT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SPAN_EFFECT, SPAN_EFFECT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SPAN_EFFECT, -SPAN_EFFECT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SPAN_EFFECT, -SPAN_EFFECT, 0.0f);
		break;
	}

	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

//************************************************
//エフェクト更新
//************************************************
void UpdateEffect(void)
{
	for (int i = 0; i < AMOUNT_EFFECT; i++)
	{
		if (g_aEffect[i].bUse)
		{
			//カラーリング
			SetColEffect(i);

			//消滅処理
			DisappearEffect(i);
		}
	}
}

//************************************************
//エフェクトカラーリング
//************************************************
void SetColEffect(int nCnt)
{
	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//薄く
	g_aEffect[nCnt].col.a -= 0.01f;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX * nCnt;

	//色変更
	pVtx[0].col = g_aEffect[nCnt].col;
	pVtx[1].col = g_aEffect[nCnt].col;
	pVtx[2].col = g_aEffect[nCnt].col;
	pVtx[3].col = g_aEffect[nCnt].col;

	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

//************************************************
//エフェクト消滅
//************************************************
void DisappearEffect(int nCnt)
{
	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX * nCnt;

	//減少加速度
	g_aEffect[nCnt].fDecrease += 0.0025f;

	//ポリゴンが展開可能なサイズがあるとき
	if (pVtx[0].pos.x <= 0.0f)
	{
		//縮小
		pVtx[0].pos.x += g_aEffect[nCnt].fDecrease;
		pVtx[0].pos.y -= g_aEffect[nCnt].fDecrease;
		pVtx[1].pos.x -= g_aEffect[nCnt].fDecrease;
		pVtx[1].pos.y -= g_aEffect[nCnt].fDecrease;
		pVtx[2].pos.x += g_aEffect[nCnt].fDecrease;
		pVtx[2].pos.y += g_aEffect[nCnt].fDecrease;
		pVtx[3].pos.x -= g_aEffect[nCnt].fDecrease;
		pVtx[3].pos.y += g_aEffect[nCnt].fDecrease;
	}
	//ポリゴンが消失したとき
	else
	{
		g_aEffect[nCnt].bUse = false;
	}

	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

//************************************************
//エフェクト描画
//************************************************
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//ライトをオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z位置の比較方法の変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	D3DXMATRIX mtxTrans;	//計算用マトリックス

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ビューマトリックス取得
	D3DXMATRIX mtxView;

	for (int i = 0; i < AMOUNT_EFFECT; i++)
	{
		if (g_aEffect[i].bUse)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEffect[i].mtxWorld);

			//ビューマトリックス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラの正面に向け続ける
			D3DXMatrixInverse(&g_aEffect[i].mtxWorld, NULL, &mtxView);	//逆行列を求める

			g_aEffect[i].mtxWorld._41 = 0.0f;
			g_aEffect[i].mtxWorld._42 = 0.0f;
			g_aEffect[i].mtxWorld._43 = 0.0f;

			//位置を反映1
			D3DXMatrixTranslation(&mtxTrans,
				g_aEffect[i].pos.x,
				g_aEffect[i].pos.y,
				g_aEffect[i].pos.z);

			//位置を反映2
			D3DXMatrixMultiply(&g_aEffect[i].mtxWorld,
				&g_aEffect[i].mtxWorld,
				&mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[i].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect);

			//エフェクトの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}

	//ライトをオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Z位置の比較方法の変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Zバッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファブレンディングを戻す設定
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
}