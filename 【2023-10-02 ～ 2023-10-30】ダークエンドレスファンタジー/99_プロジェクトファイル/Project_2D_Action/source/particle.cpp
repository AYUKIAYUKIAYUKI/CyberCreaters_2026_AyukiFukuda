//************************************************
//
//パーティクル処理(テンプレ)[particle.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "camera.h"
#include "particle.h"
#include "player.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Particle[AMOUNT_TEX_PARTICLE] = {};	//テクスチャのポインタ
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
		TEXTURE_ATKED,
		&g_pTexture_Particle[PARTICLE_ATKED]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLOOD,
		&g_pTexture_Particle[PARTICLE_BLOOD]);

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
		g_aParticle[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCnt].nCntTex = 0;
		g_aParticle[nCnt].nCntPattern = 0;
		for (int i = 0; i < 2; i++)
		{
			g_aParticle[nCnt].fTexSpan[i] = 0;
			g_aParticle[nCnt].fRadius[i] = 0;
			g_aParticle[nCnt].fLength[i] = 0;
			g_aParticle[nCnt].fAngle[i] = 0;
		}
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
	for (int i = 0; i < AMOUNT_TEX_PARTICLE; i++)
	{
		if (g_pTexture_Particle[i] != NULL)
		{
			g_pTexture_Particle[i]->Release();
			g_pTexture_Particle[i] = NULL;
		}
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
	Update_Pos_Particle();
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

	for (int i = 0; i < AMOUNT_POLYGON_PARTICLE; i++)
	{
		//テクスチャの設定
		switch (g_aParticle[i].nStyle)
		{
		case PARTICLE_ATKED:
			pDevice->SetTexture(0, g_pTexture_Particle[PARTICLE_ATKED]);
			break;
		case PARTICLE_BLOOD:
			pDevice->SetTexture(0, g_pTexture_Particle[PARTICLE_BLOOD]);
			break;
		}

		////アルファブレンディングを加算合成に設定
		//pDevice->SetRenderState(D3DRS_BLENDOP,
		//	D3DBLENDOP_ADD);

		//pDevice->SetRenderState(D3DRS_SRCBLEND,
		//	D3DBLEND_SRCALPHA);

		//pDevice->SetRenderState(D3DRS_DESTBLEND,
		//	D3DBLEND_ONE);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	////アルファブレンディングを戻す設定
	//pDevice->SetRenderState(D3DRS_BLENDOP,
	//	D3DBLENDOP_ADD);

	//pDevice->SetRenderState(D3DRS_SRCBLEND,
	//	D3DBLEND_SRCALPHA);

	//pDevice->SetRenderState(D3DRS_DESTBLEND,
	//	D3DBLEND_INVSRCALPHA);
}

//************************************************
//パーティクルの情報を設定する関数
//************************************************
void Setinfo_Particle(int nStyle, D3DXVECTOR3 pos, D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE; nCnt++)
	{
		//使用されていないパーティクルを検知した時
		if (!g_aParticle[nCnt].bUse)
		{
			float fRandomX = 0.0f, fRandomY = 0.0f;
			int nRondom = 0;

			g_aParticle[nCnt].nStyle = nStyle;
			switch (g_aParticle[nCnt].nStyle)
			{
			case PARTICLE_ATKED:
				g_aParticle[nCnt].pos = pos;
				g_aParticle[nCnt].pos.y -= 50.0f;	//武器のテクスチャの位置に合うように補正
				fRandomX = (rand() % 314) * 0.01f;
				fRandomY = (rand() % 314) * 0.01f;
				nRondom = rand() % 2;
				nRondom == 0 ? 0 : fRandomX *= -1.0f, fRandomY *= -1.0f;
				g_aParticle[nCnt].move.x = sinf(D3DX_PI - fRandomX);
				g_aParticle[nCnt].move.y = cosf(D3DX_PI - fRandomY);
				g_aParticle[nCnt].pos += g_aParticle[nCnt].move * 15.0f;	//あらかじめ移動したことにしてある程度分散
				g_aParticle[nCnt].col = col;
				g_aParticle[nCnt].fTexSpan[0] = 0.0f;
				g_aParticle[nCnt].fTexSpan[1] = SPAN_CHANGE_TEX_PARTICLE;
				g_aParticle[nCnt].fRadius[0] = 50.0f;
				g_aParticle[nCnt].fRadius[1] = 50.0f;
				g_aParticle[nCnt].fLength[0] = sqrtf((g_aParticle[nCnt].fRadius[0] * g_aParticle[nCnt].fRadius[0]) + (g_aParticle[nCnt].fRadius[1] * g_aParticle[nCnt].fRadius[1]));
				g_aParticle[nCnt].fLength[1] = g_aParticle[nCnt].fLength[0];
				g_aParticle[nCnt].fAngle[0] = atan2f(g_aParticle[nCnt].fRadius[0] * 2.0f, g_aParticle[nCnt].fRadius[1] * 2.0f);
				g_aParticle[nCnt].fAngle[1] = g_aParticle[nCnt].fAngle[0];
				g_aParticle[nCnt].nRemain = REMAIN_TIME_PARTICLE;
				g_aParticle[nCnt].bUse = true;
				break;
			case PARTICLE_BLOOD:
				g_aParticle[nCnt].pos = pos;
				g_aParticle[nCnt].pos.y -= 40.0f;	//敵のテクスチャの位置に合うように補正
				fRandomX = (rand() % 314) * 0.01f;
				fRandomY = (rand() % 314) * 0.01f;
				nRondom = rand() % 2;
				nRondom == 0 ? 0 : fRandomX *= -1.0f, fRandomY *= -1.0f;
				g_aParticle[nCnt].move.x = sinf(D3DX_PI - fRandomX);
				g_aParticle[nCnt].move.y = cosf(D3DX_PI - fRandomY);
				g_aParticle[nCnt].pos += g_aParticle[nCnt].move * 5.0f;	//あらかじめ移動したことにしてある程度分散
				g_aParticle[nCnt].col = col;
				g_aParticle[nCnt].fTexSpan[0] = 0.0f;
				g_aParticle[nCnt].fTexSpan[1] = SPAN_CHANGE_TEX_PARTICLE;
				g_aParticle[nCnt].fRadius[0] = 50.0f;
				g_aParticle[nCnt].fRadius[1] = 50.0f;
				g_aParticle[nCnt].fLength[0] = sqrtf((g_aParticle[nCnt].fRadius[0] * g_aParticle[nCnt].fRadius[0]) + (g_aParticle[nCnt].fRadius[1] * g_aParticle[nCnt].fRadius[1]));
				g_aParticle[nCnt].fLength[1] = g_aParticle[nCnt].fLength[0];
				g_aParticle[nCnt].fAngle[0] = atan2f(g_aParticle[nCnt].fRadius[0] * 2.0f, g_aParticle[nCnt].fRadius[1] * 2.0f);
				g_aParticle[nCnt].fAngle[1] = g_aParticle[nCnt].fAngle[0];
				g_aParticle[nCnt].nRemain = REMAIN_TIME_PARTICLE;
				g_aParticle[nCnt].bUse = true;
				break;
			}
			break;
		}
	}
}

//************************************************
//パーティクルのバーテックスを更新する関数
//************************************************
void Update_Pos_Particle(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Particle;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Particle->Lock(0, 0, (void**)&pVtx_Particle, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse)
		{
			//移動
			g_aParticle[nCnt].pos += g_aParticle[nCnt].move;

			if (g_aParticle[nCnt].nStyle == PARTICLE_ATKED)
			{
				//反動
				PLAYER* pPlayer = GetInfo_Player();
				pPlayer->LR == 0 ? g_aParticle[nCnt].pos.x += 1.5f : g_aParticle[nCnt].pos.x += -1.5f;
			}

			//縮小
			for (int q = 0; q < 2; q++)
			{
				g_aParticle[nCnt].fLength[q] *= CHANGE_SPD_RADIUS_PARTICLE;
				g_aParticle[nCnt].fLength[q] < 0 ? g_aParticle[nCnt].fLength[q] = 0.0f : 0;
			}

			//アニメーション
			Update_Tex_Particle(nCnt);

			//スクリーン変換
			ConvertInfo_Screen(&g_aParticle[nCnt].pos);

			pVtx_Particle[0].pos.x = g_aParticle[nCnt].pos.x + sinf(g_aParticle[nCnt].rot.z - (D3DX_PI - g_aParticle[nCnt].fAngle[0])) * g_aParticle[nCnt].fLength[0];
			pVtx_Particle[0].pos.y = g_aParticle[nCnt].pos.y + cosf(g_aParticle[nCnt].rot.z - (D3DX_PI - g_aParticle[nCnt].fAngle[0])) * g_aParticle[nCnt].fLength[0];
			pVtx_Particle[1].pos.x = g_aParticle[nCnt].pos.x + sinf(g_aParticle[nCnt].rot.z + (D3DX_PI - g_aParticle[nCnt].fAngle[0])) * g_aParticle[nCnt].fLength[0];
			pVtx_Particle[1].pos.y = g_aParticle[nCnt].pos.y + cosf(g_aParticle[nCnt].rot.z + (D3DX_PI - g_aParticle[nCnt].fAngle[0])) * g_aParticle[nCnt].fLength[0];
			pVtx_Particle[2].pos.x = g_aParticle[nCnt].pos.x + sinf(g_aParticle[nCnt].rot.z - g_aParticle[nCnt].fAngle[1]) * g_aParticle[nCnt].fLength[1];
			pVtx_Particle[2].pos.y = g_aParticle[nCnt].pos.y + cosf(g_aParticle[nCnt].rot.z - g_aParticle[nCnt].fAngle[1]) * g_aParticle[nCnt].fLength[1];
			pVtx_Particle[3].pos.x = g_aParticle[nCnt].pos.x + sinf(g_aParticle[nCnt].rot.z + g_aParticle[nCnt].fAngle[1]) * g_aParticle[nCnt].fLength[1];
			pVtx_Particle[3].pos.y = g_aParticle[nCnt].pos.y + cosf(g_aParticle[nCnt].rot.z + g_aParticle[nCnt].fAngle[1]) * g_aParticle[nCnt].fLength[1];

			pVtx_Particle[0].col = g_aParticle[nCnt].col;
			pVtx_Particle[1].col = g_aParticle[nCnt].col;
			pVtx_Particle[2].col = g_aParticle[nCnt].col;
			pVtx_Particle[3].col = g_aParticle[nCnt].col;
		}

		pVtx_Particle += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Particle->Unlock();
}

//************************************************
//パーティクルのテクスチャを更新する関数
//************************************************
void Update_Tex_Particle(int nCnt)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Particle;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Particle->Lock(0, 0, (void**)&pVtx_Particle, 0);

	pVtx_Particle += AMOUNT_VTX * nCnt;

	//テクスチャを変更
	g_aParticle[nCnt].nCntTex++;
	if (g_aParticle[nCnt].nCntTex > SPD_CHANGE_TEX_PARTICLE)
	{
		g_aParticle[nCnt].nCntTex = 0;
		g_aParticle[nCnt].nCntPattern++;
		g_aParticle[nCnt].fTexSpan[0] += SPAN_CHANGE_TEX_PARTICLE;
		g_aParticle[nCnt].fTexSpan[1] += SPAN_CHANGE_TEX_PARTICLE;
		if (g_aParticle[nCnt].nCntPattern >= AMOUNT_STYLE_TEX_PARTICLE)
		{
			g_aParticle[nCnt].nCntPattern = 0;
			g_aParticle[nCnt].fTexSpan[0] = 0;
			g_aParticle[nCnt].fTexSpan[1] = 0;
			g_aParticle[nCnt].bUse = false;
		}
	}

	pVtx_Particle[0].tex = D3DXVECTOR2(g_aParticle[nCnt].fTexSpan[0], 0.0f);
	pVtx_Particle[1].tex = D3DXVECTOR2(g_aParticle[nCnt].fTexSpan[1], 0.0f);
	pVtx_Particle[2].tex = D3DXVECTOR2(g_aParticle[nCnt].fTexSpan[0], 1.0f);
	pVtx_Particle[3].tex = D3DXVECTOR2(g_aParticle[nCnt].fTexSpan[1], 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Particle->Unlock();
}