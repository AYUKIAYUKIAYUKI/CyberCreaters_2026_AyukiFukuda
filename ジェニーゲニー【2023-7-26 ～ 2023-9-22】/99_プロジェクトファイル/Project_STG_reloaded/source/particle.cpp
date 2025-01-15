//************************************************
//
//パーティクル処理(テンプレ)[particle.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "particle.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Particle = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Particle = NULL;	//頂点バッファのポインタ
PARTICLE g_aParticle[AMOUNT_POLYGON_PARTICLE];	//パーティクル用情報を格納

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Particle()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PARTICLE,
		&g_pTexture_Particle);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Particle,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Particle;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Particle->Lock(0, 0, (void**)&pVtx_Particle, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Particle[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Particle[0].rhw = 1.0f;
		pVtx_Particle[1].rhw = 1.0f;
		pVtx_Particle[2].rhw = 1.0f;
		pVtx_Particle[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Particle[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Particle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Particle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Particle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Particle[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Particle += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Particle->Unlock();

	//構造体の中身を初期化
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE; nCnt++)
	{
		g_aParticle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCnt].fRadius = 0.0f;
		g_aParticle[nCnt].nRemain = 0;
		g_aParticle[nCnt].bUse = false;
	}
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Particle(void)
{
	//テクスチャの破棄
	if (g_pTexture_Particle != NULL)
	{
		g_pTexture_Particle->Release();
		g_pTexture_Particle = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Particle != NULL)
	{
		g_pVtxBuff_Particle->Release();
		g_pVtxBuff_Particle = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Particle(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Particle;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Particle->Lock(0, 0, (void**)&pVtx_Particle, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse)
		{
			//縮む
			g_aParticle[nCnt].fRadius -= CHANGE_SPD_RADIUS_PARTICLE;

			//裏返るの防止
			if (g_aParticle[nCnt].fRadius <= 0)
			{
				g_aParticle[nCnt].fRadius = 0.0f;
			}

			g_aParticle[nCnt].pos += g_aParticle[nCnt].move * MOVE_SPD_POS_PARTICLE;

			//頂点を展開する
			pVtx_Particle[0].pos.x = g_aParticle[nCnt].pos.x - g_aParticle[nCnt].fRadius;
			pVtx_Particle[0].pos.y = g_aParticle[nCnt].pos.y - g_aParticle[nCnt].fRadius;
			pVtx_Particle[1].pos.x = g_aParticle[nCnt].pos.x + g_aParticle[nCnt].fRadius;
			pVtx_Particle[1].pos.y = g_aParticle[nCnt].pos.y - g_aParticle[nCnt].fRadius;
			pVtx_Particle[2].pos.x = g_aParticle[nCnt].pos.x - g_aParticle[nCnt].fRadius;
			pVtx_Particle[2].pos.y = g_aParticle[nCnt].pos.y + g_aParticle[nCnt].fRadius;
			pVtx_Particle[3].pos.x = g_aParticle[nCnt].pos.x + g_aParticle[nCnt].fRadius;
			pVtx_Particle[3].pos.y = g_aParticle[nCnt].pos.y + g_aParticle[nCnt].fRadius;

			//色反映
			pVtx_Particle[0].col = g_aParticle[nCnt].col;
			pVtx_Particle[1].col = g_aParticle[nCnt].col;
			pVtx_Particle[2].col = g_aParticle[nCnt].col;
			pVtx_Particle[3].col = g_aParticle[nCnt].col;

			g_aParticle[nCnt].nRemain--;

			//残存時間が無くなったとき
			if (g_aParticle[nCnt].nRemain <= 0)
			{
				pVtx_Particle[0].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle[1].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle[2].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle[3].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);

				pVtx_Particle[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx_Particle[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx_Particle[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx_Particle[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				g_aParticle[nCnt].bUse = false;	//使用判定を無くす
			}
		}

		pVtx_Particle += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Particle->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Particle(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Particle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Particle);

	//ポリゴンの描画
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE; nCnt++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//パーティクルの情報を設定する関数
//************************************************
void Setinfo_Particle(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Particle;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Particle->Lock(0, 0, (void**)&pVtx_Particle, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE; nCnt++)
	{
		//使用されていないパーティクルを検知した時
		if (!g_aParticle[nCnt].bUse)
		{
			g_aParticle[nCnt].pos = pos;	//位置を適当に設定

			//それっぽく計算(要改善…)
			float fRandomX = (rand() % 314) * 0.01f;
			float fRandomY = (rand() % 314) * 0.01f;

			int nRondom = rand() % 2;

			nRondom == 0 ? 0 : fRandomX *= -1.0f, fRandomY *= -1.0f;

			g_aParticle[nCnt].move.x = sinf(D3DX_PI - fRandomX);	//移動量を適当に設定
			g_aParticle[nCnt].move.y = cosf(D3DX_PI - fRandomY);	//移動量を適当に設定
			g_aParticle[nCnt].col = col;	//色を合わせて設定
			g_aParticle[nCnt].fRadius = RADIUS_PARTICLE;		//半径を適当に設定
			g_aParticle[nCnt].nRemain = REMAIN_TIME_PARTICLE;	//残存時間を適当に設定
			g_aParticle[nCnt].bUse = true;	//使用判定を出す

			break;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Particle->Unlock();
}