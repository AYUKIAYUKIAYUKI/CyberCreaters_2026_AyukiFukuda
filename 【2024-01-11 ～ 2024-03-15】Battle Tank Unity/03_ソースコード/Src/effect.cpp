//************************************************
//
// エフェクト[effect.cpp]
// Author：葛西敬介
//
//************************************************

//include
#include "main.h"
#include "effect.h"

//グローバル変数宣言
EFFECT g_aEffect[MAX_EFFECT];	//エフェクトの情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL; //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;		//テクスチャへのポインタ

//************************************************
// エフェクトの初期化処理
//************************************************
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();  //デバイスへのポインタ

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_pTextureEffect);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffEffect, NULL);

	VERTEX_3D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//色
		g_aEffect[nCntEffect].fRadius = 0.0f;							//半径
		g_aEffect[nCntEffect].fLife = 0.0f;								//ライフ
		g_aEffect[nCntEffect].bUse = false;								//使用しているかどうか


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

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	}


	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();

}

//************************************************
// エフェクトの終了処理
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
// エフェクトの更新処理
//************************************************
void UpdateEffect(void)
{
	VERTEX_3D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		EFFECT* pEffect = &g_aEffect[nCntEffect];
		if (pEffect->bUse)
		{
			//法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//エフェクトの色を少しずつ小さくする
			pEffect->col.a -= 0.01f;
			if (pEffect->col.a <= 0.0f)
			{
				pEffect->col.a = 0.0f;

			}

			//エフェクトの大きさを少しずつ小さくする
			pEffect->fRadius -= 0.5f;

			//頂点カラーの設定
			pVtx[0].col = pEffect->col;
			pVtx[1].col = pEffect->col;
			pVtx[2].col = pEffect->col;
			pVtx[3].col = pEffect->col;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-pEffect->fRadius, +pEffect->fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+pEffect->fRadius, +pEffect->fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-pEffect->fRadius, -pEffect->fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+pEffect->fRadius, -pEffect->fRadius, 0.0f);

			pEffect->fLife--;
			if (pEffect->fLife <= 0.0f)
			{
				pEffect->bUse = false;
			}
		}
	}
	//頂点バッファのアンロック
	g_pVtxBuffEffect->Unlock();

}

//************************************************
// エフェクトの描画処理
//************************************************
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxView;		//ビューマトリックス取得用

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	/*---【1度で済む設定をfor文の外に移しました：福田】---*/

	// エフェクト情報のポインタ
	EFFECT* pEffect = &g_aEffect[0];

	// ライト反映を無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	// 深度テストの比較方法の変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// 深度バッファに描画しない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	/*----------------------------------------------------*/

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pEffect->mtxworld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&pEffect->mtxworld, NULL, &mtxView);

			//逆行列を求める
			pEffect->mtxworld._41 = 0.0f;
			pEffect->mtxworld._42 = 0.0f;
			pEffect->mtxworld._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, pEffect->pos.x, pEffect->pos.y, pEffect->pos.z);

			D3DXMatrixMultiply(&pEffect->mtxworld, &pEffect->mtxworld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pEffect->mtxworld);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect);

			//エフェクトの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}

	}

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	/*---【1度で済む設定をfor文の外に移しました：福田】---*/

	// ライト反映を有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// 深度バッファの比較方法の変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// 深度バッファに描画する
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	/*----------------------------------------------------*/
}

//************************************************
// エフェクトの設定処理
//************************************************
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, float fLife)
{
	VERTEX_3D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pVtx += 4)
	{
		if (!g_aEffect[nCntEffect].bUse)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].fLife = fLife;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, +g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius, +g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].bUse = true;

			break;
		}
	}

	//頂点バッファのアンロック
	g_pVtxBuffEffect->Unlock();

}

//************************************************
// エフェクトの情報を取得する処理
//************************************************
EFFECT* GetEffect(void)
{
	return g_aEffect;
}
