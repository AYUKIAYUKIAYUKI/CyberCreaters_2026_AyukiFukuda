//************************************************
//
//タイトルロゴパーティクル処理[particle_titlelogo.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "title.h"
#include "particle_titlelogo.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Particle_Titlelogo = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Particle_Titlelogo = NULL;	//頂点バッファのポインタ
PARTICLE_TITLELOGO g_aParticle_Titlelogo[AMOUNT_POLYGON_PARTICLE_TITLELOGO];	//パーティクル用情報を格納
float g_fcol = 0.5f;

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Particle_Titlelogo()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PARTICLE_TITLELOGO,
		&g_pTexture_Particle_Titlelogo);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_PARTICLE_TITLELOGO,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Particle_Titlelogo,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Particle_Titlelogo;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Particle_Titlelogo->Lock(0, 0, (void**)&pVtx_Particle_Titlelogo, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_TITLELOGO; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Particle_Titlelogo[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle_Titlelogo[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle_Titlelogo[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle_Titlelogo[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Particle_Titlelogo[0].rhw = 1.0f;
		pVtx_Particle_Titlelogo[1].rhw = 1.0f;
		pVtx_Particle_Titlelogo[2].rhw = 1.0f;
		pVtx_Particle_Titlelogo[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Particle_Titlelogo[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle_Titlelogo[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle_Titlelogo[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle_Titlelogo[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Particle_Titlelogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Particle_Titlelogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Particle_Titlelogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Particle_Titlelogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Particle_Titlelogo += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Particle_Titlelogo->Unlock();

	//構造体の中身を初期化
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_TITLELOGO; nCnt++)
	{
		g_aParticle_Titlelogo[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle_Titlelogo[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle_Titlelogo[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle_Titlelogo[nCnt].fRadius = 0.0f;
		g_aParticle_Titlelogo[nCnt].nRemain = 0;
		g_aParticle_Titlelogo[nCnt].bUse = false;
	}

	g_fcol = 0.5f;
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Particle_Titlelogo(void)
{
	//テクスチャの破棄
	if (g_pTexture_Particle_Titlelogo != NULL)
	{
		g_pTexture_Particle_Titlelogo->Release();
		g_pTexture_Particle_Titlelogo = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Particle_Titlelogo != NULL)
	{
		g_pVtxBuff_Particle_Titlelogo->Release();
		g_pVtxBuff_Particle_Titlelogo = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Particle_Titlelogo(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Particle_Titlelogo;

	bool* pStartFadeout;
	pStartFadeout = StartFadeout();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Particle_Titlelogo->Lock(0, 0, (void**)&pVtx_Particle_Titlelogo, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_TITLELOGO; nCnt++)
	{
		if (g_aParticle_Titlelogo[nCnt].bUse)
		{
			//縮む
			g_aParticle_Titlelogo[nCnt].fRadius -= CHANGE_SPD_RADIUS_PARTICLE_TITLELOGO;

			//裏返るの防止
			if (g_aParticle_Titlelogo[nCnt].fRadius <= 0)
			{
				g_aParticle_Titlelogo[nCnt].fRadius = 0.0f;
			}

			g_aParticle_Titlelogo[nCnt].pos += g_aParticle_Titlelogo[nCnt].move * MOVE_SPD_POS_PARTICLE_TITLELOGO;

			//頂点を展開する
			pVtx_Particle_Titlelogo[0].pos.x = g_aParticle_Titlelogo[nCnt].pos.x - g_aParticle_Titlelogo[nCnt].fRadius;
			pVtx_Particle_Titlelogo[0].pos.y = g_aParticle_Titlelogo[nCnt].pos.y - g_aParticle_Titlelogo[nCnt].fRadius;
			pVtx_Particle_Titlelogo[1].pos.x = g_aParticle_Titlelogo[nCnt].pos.x + g_aParticle_Titlelogo[nCnt].fRadius;
			pVtx_Particle_Titlelogo[1].pos.y = g_aParticle_Titlelogo[nCnt].pos.y - g_aParticle_Titlelogo[nCnt].fRadius;
			pVtx_Particle_Titlelogo[2].pos.x = g_aParticle_Titlelogo[nCnt].pos.x - g_aParticle_Titlelogo[nCnt].fRadius;
			pVtx_Particle_Titlelogo[2].pos.y = g_aParticle_Titlelogo[nCnt].pos.y + g_aParticle_Titlelogo[nCnt].fRadius;
			pVtx_Particle_Titlelogo[3].pos.x = g_aParticle_Titlelogo[nCnt].pos.x + g_aParticle_Titlelogo[nCnt].fRadius;
			pVtx_Particle_Titlelogo[3].pos.y = g_aParticle_Titlelogo[nCnt].pos.y + g_aParticle_Titlelogo[nCnt].fRadius;

			if (*pStartFadeout == true)
			{
				if (g_fcol > 0.0f)
				{
					g_fcol -= 0.1f;
				}

				pVtx_Particle_Titlelogo[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcol);
				pVtx_Particle_Titlelogo[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcol);
				pVtx_Particle_Titlelogo[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcol);
				pVtx_Particle_Titlelogo[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcol);
			}

			g_aParticle_Titlelogo[nCnt].nRemain--;

			//残存時間が無くなったとき
			if (g_aParticle_Titlelogo[nCnt].nRemain <= 0)
			{
				pVtx_Particle_Titlelogo[0].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle_Titlelogo[1].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle_Titlelogo[2].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle_Titlelogo[3].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);

				g_aParticle_Titlelogo[nCnt].bUse = false;	//使用判定を無くす
			}
		}

		pVtx_Particle_Titlelogo += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Particle_Titlelogo->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Particle_Titlelogo(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Particle_Titlelogo, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Particle_Titlelogo);

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP,
		D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND,
		D3DBLEND_ONE);

	//ポリゴンの描画
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_TITLELOGO; nCnt++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//アルファブレンディングを戻す設定
	pDevice->SetRenderState(D3DRS_BLENDOP,
		D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND,
		D3DBLEND_INVSRCALPHA);
}

//************************************************
//パーティクルの情報を設定する関数
//************************************************
void Setinfo_Particle_Titlelogo(D3DXVECTOR3 pos)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Particle_Titlelogo;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Particle_Titlelogo->Lock(0, 0, (void**)&pVtx_Particle_Titlelogo, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_TITLELOGO; nCnt++)
	{
		//使用されていないパーティクルを検知した時
		if (!g_aParticle_Titlelogo[nCnt].bUse)
		{
			g_aParticle_Titlelogo[nCnt].pos = pos;	//位置を適当に設定

			//それっぽく計算(要改善…)
			float fRandomX = (rand() % 314) * 0.01f;
			float fRandomY = (rand() % 314) * 0.01f;

			int nRondom = rand() % 2;

			nRondom == 0 ? 0 : fRandomX *= -1.0f, fRandomY *= -1.0f;

			g_aParticle_Titlelogo[nCnt].move.x = sinf(D3DX_PI - fRandomX);	//移動量を適当に設定
			g_aParticle_Titlelogo[nCnt].move.y = cosf(D3DX_PI - fRandomY);	//移動量を適当に設定
			g_aParticle_Titlelogo[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	//色を適当に設定
			g_aParticle_Titlelogo[nCnt].fRadius = RADIUS_PARTICLE_TITLELOGO;		//半径を適当に設定
			g_aParticle_Titlelogo[nCnt].nRemain = REMAIN_TIME_PARTICLE_TITLELOGO;	//残存時間を適当に設定
			g_aParticle_Titlelogo[nCnt].bUse = true;	//使用判定を出す

			break;
		}

		pVtx_Particle_Titlelogo += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Particle_Titlelogo->Unlock();
}