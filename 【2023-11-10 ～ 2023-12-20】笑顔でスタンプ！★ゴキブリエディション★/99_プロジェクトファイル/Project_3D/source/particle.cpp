//************************************************
//
//パーティクル生成[particle.cpp]
//Author：福田歩希
//
//************************************************
#include "particle.h"

//マクロ定義
#define AMOUNT_PARTICLE	(1024)	//パーティクルの数
#define SPAN_PARTICLE	(3.0f)	//パーティクルの大きさ

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;	//テクスチャへのポインタ
Particle g_aParticle[AMOUNT_PARTICLE] = {};	//パーティクル情報

//************************************************
//パーティクル初期
//************************************************
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//パーティクル情報初期化
	for (int i = 0; i < AMOUNT_PARTICLE; i++)
	{
		g_aParticle[i].bUse = false;
		g_aParticle[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aParticle[i].fSize = 0.0f;
		g_aParticle[i].fDecrease = 0.0f;
	}

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\shadow000.jpg",
		&g_pTextureParticle);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_PARTICLE; i++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
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
	g_pVtxBuffParticle->Unlock();
}

//************************************************
//パーティクル破棄
//************************************************
void UninitParticle(void)
{
	//テクスチャの破棄
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//************************************************
//パーティクル設定
//************************************************
void SetInfoParticle(D3DXVECTOR3 pos, D3DXCOLOR col, float fSize)
{
	for (int i = 0; i < AMOUNT_PARTICLE; i++)
	{
		if (!g_aParticle[i].bUse)
		{
			g_aParticle[i].bUse = true;
			g_aParticle[i].pos = pos;
			g_aParticle[i].rot.y = (float)(rand() % 100);	/*パーティクル飛ばす方向を適当に*/
			g_aParticle[i].col = col;
			g_aParticle[i].fSize = fSize;
			g_aParticle[i].fDecrease = 0.1f;

			//サイズセット
			SetSizeParticle(i);

			break;
		}
	}
}

//************************************************
//パーティクルサイズセット
//************************************************
void SetSizeParticle(int nCnt)
{
	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX * nCnt;

	//サイズ変更
	pVtx[0].pos = D3DXVECTOR3(-g_aParticle[nCnt].fSize, g_aParticle[nCnt].fSize, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCnt].fSize, g_aParticle[nCnt].fSize, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-g_aParticle[nCnt].fSize, -g_aParticle[nCnt].fSize, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCnt].fSize, -g_aParticle[nCnt].fSize, 0.0f);

	//頂点バッファをアンロック
	g_pVtxBuffParticle->Unlock();
}

//************************************************
//パーティクル更新
//************************************************
void UpdateParticle(void)
{
	for (int i = 0; i < AMOUNT_PARTICLE; i++)
	{
		if (g_aParticle[i].bUse)
		{
			//移動
			g_aParticle[i].pos.x += sinf(D3DX_PI - g_aParticle[i].rot.y);
			g_aParticle[i].pos.z -= cosf(D3DX_PI - g_aParticle[i].rot.y);

			//カラーリング
			SetColParticle(i);

			//消滅処理
			DisappearParticle(i);
		}
	}
}

//************************************************
//パーティクルカラーリング
//************************************************
void SetColParticle(int nCnt)
{
	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	g_aParticle[nCnt].col.a -= 0.05f;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX * nCnt;

	//カラーリング
	pVtx[0].col = g_aParticle[nCnt].col;
	pVtx[1].col = g_aParticle[nCnt].col;
	pVtx[2].col = g_aParticle[nCnt].col;
	pVtx[3].col = g_aParticle[nCnt].col;

	//頂点バッファをアンロック
	g_pVtxBuffParticle->Unlock();
}

//************************************************
//パーティクル消滅
//************************************************
void DisappearParticle(int nCnt)
{
	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX * nCnt;

	//減少加速度
	g_aParticle[nCnt].fDecrease += 0.01f;

	//ポリゴンが展開可能なサイズがあるとき
	if (pVtx[0].pos.x <= 0.0f)
	{
		//縮小
		pVtx[0].pos.x += g_aParticle[nCnt].fDecrease;
		pVtx[0].pos.y -= g_aParticle[nCnt].fDecrease;
		pVtx[1].pos.x -= g_aParticle[nCnt].fDecrease;
		pVtx[1].pos.y -= g_aParticle[nCnt].fDecrease;
		pVtx[2].pos.x += g_aParticle[nCnt].fDecrease;
		pVtx[2].pos.y += g_aParticle[nCnt].fDecrease;
		pVtx[3].pos.x -= g_aParticle[nCnt].fDecrease;
		pVtx[3].pos.y += g_aParticle[nCnt].fDecrease;
	}
	//ポリゴンが消失したとき
	else
	{
		g_aParticle[nCnt].bUse = false;
	}

	//頂点バッファをアンロック
	g_pVtxBuffParticle->Unlock();
}

//************************************************
//パーティクル描画
//************************************************
void DrawParticle(void)
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

	for (int i = 0; i < AMOUNT_PARTICLE; i++)
	{
		if (g_aParticle[i].bUse)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aParticle[i].mtxWorld);

			//ビューマトリックス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラの正面に向け続ける
			D3DXMatrixInverse(&g_aParticle[i].mtxWorld, NULL, &mtxView);	//逆行列を求める

			g_aParticle[i].mtxWorld._41 = 0.0f;
			g_aParticle[i].mtxWorld._42 = 0.0f;
			g_aParticle[i].mtxWorld._43 = 0.0f;

			//位置を反映1
			D3DXMatrixTranslation(&mtxTrans,
				g_aParticle[i].pos.x,
				g_aParticle[i].pos.y,
				g_aParticle[i].pos.z);

			//位置を反映2
			D3DXMatrixMultiply(&g_aParticle[i].mtxWorld,
				&g_aParticle[i].mtxWorld,
				&mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aParticle[i].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureParticle);

			//パーティクルの描画
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
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}