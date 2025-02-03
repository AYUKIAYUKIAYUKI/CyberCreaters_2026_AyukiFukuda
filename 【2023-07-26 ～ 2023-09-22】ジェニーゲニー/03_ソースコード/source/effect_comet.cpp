//************************************************
//
//コメットエフェクト処理[effect_comet.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "effect_comet.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Effect_Comet = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Effect_Comet = NULL;	//頂点バッファのポインタ
COMET_EFFECT g_aEffect_Comet[AMOUNT_POLYGON_EFFECT_COMET];	//コメットエフェクト情報格納

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Effect_Comet(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_EFFECT_COMET,
		&g_pTexture_Effect_Comet);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_EFFECT_COMET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Effect_Comet,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Effect_Comet;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Effect_Comet->Lock(0, 0, (void**)&pVtx_Effect_Comet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_COMET; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Effect_Comet[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Comet[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Comet[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Comet[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Effect_Comet[0].rhw = 1.0f;
		pVtx_Effect_Comet[1].rhw = 1.0f;
		pVtx_Effect_Comet[2].rhw = 1.0f;
		pVtx_Effect_Comet[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Effect_Comet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Comet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Comet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Comet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Effect_Comet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Effect_Comet[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Effect_Comet[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Effect_Comet[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Effect_Comet += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Effect_Comet->Unlock();

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_COMET; nCnt++)
	{
		g_aEffect_Comet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect_Comet[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect_Comet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect_Comet[nCnt].bUse = false;
		g_aEffect_Comet[nCnt].fLength = 0.0f;
		g_aEffect_Comet[nCnt].fAngle = 0.0f;
		g_aEffect_Comet[nCnt].nPattern = 0;
		g_aEffect_Comet[nCnt].fTexX = 0.0f;
		g_aEffect_Comet[nCnt].fTexY = 0.0f;
	}
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Effect_Comet(void)
{
	//テクスチャの破棄
	if (g_pTexture_Effect_Comet != NULL)
	{
		g_pTexture_Effect_Comet->Release();
		g_pTexture_Effect_Comet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Effect_Comet != NULL)
	{
		g_pVtxBuff_Effect_Comet->Release();
		g_pVtxBuff_Effect_Comet = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Effect_Comet(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Effect_Comet;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Effect_Comet->Lock(0, 0, (void**)&pVtx_Effect_Comet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_COMET; nCnt++)
	{
		if (g_aEffect_Comet[nCnt].bUse)
		{
			//回転
			g_aEffect_Comet[nCnt].rot.z += ROTATE_SPD_EFFECT_COMET;

			//(敵や壁などに当たった場合移動量を同期)
			g_aEffect_Comet[nCnt].pos.x += g_aEffect_Comet[nCnt].move.x;

			pVtx_Effect_Comet[0].tex = D3DXVECTOR2(0.0f + g_aEffect_Comet[nCnt].fTexX, 0.0f + g_aEffect_Comet[nCnt].fTexY);
			pVtx_Effect_Comet[1].tex = D3DXVECTOR2(0.2f + g_aEffect_Comet[nCnt].fTexX, 0.0f + g_aEffect_Comet[nCnt].fTexY);
			pVtx_Effect_Comet[2].tex = D3DXVECTOR2(0.0f + g_aEffect_Comet[nCnt].fTexX, 0.5f + g_aEffect_Comet[nCnt].fTexY);
			pVtx_Effect_Comet[3].tex = D3DXVECTOR2(0.2f + g_aEffect_Comet[nCnt].fTexX, 0.5f + g_aEffect_Comet[nCnt].fTexY);

			//テクスチャが変化
			g_aEffect_Comet[nCnt].nPattern++;

			if (g_aEffect_Comet[nCnt].nPattern > 1)
			{
				g_aEffect_Comet[nCnt].fTexX += 0.2f;

				if (g_aEffect_Comet[nCnt].fTexX >= 1.0f)
				{
					g_aEffect_Comet[nCnt].fTexX = 0.0f;

					g_aEffect_Comet[nCnt].fTexY += 0.5f;

					if (g_aEffect_Comet[nCnt].fTexY >= 1.0f)
					{
						//消滅
						g_aEffect_Comet[nCnt].pos = D3DXVECTOR3(-1000.0f, -1000.0f, 0.0f);

						g_aEffect_Comet[nCnt].bUse = false;
					}
				}

				g_aEffect_Comet[nCnt].nPattern = 0;
			}

			//最後に反映
			pVtx_Effect_Comet[0].pos.x = g_aEffect_Comet[nCnt].pos.x + sinf(g_aEffect_Comet[nCnt].rot.z - (D3DX_PI - g_aEffect_Comet[nCnt].fAngle)) * g_aEffect_Comet[nCnt].fLength;
			pVtx_Effect_Comet[0].pos.y = g_aEffect_Comet[nCnt].pos.y + cosf(g_aEffect_Comet[nCnt].rot.z - (D3DX_PI - g_aEffect_Comet[nCnt].fAngle)) * g_aEffect_Comet[nCnt].fLength;
			pVtx_Effect_Comet[1].pos.x = g_aEffect_Comet[nCnt].pos.x + sinf(g_aEffect_Comet[nCnt].rot.z + (D3DX_PI - g_aEffect_Comet[nCnt].fAngle)) * g_aEffect_Comet[nCnt].fLength;
			pVtx_Effect_Comet[1].pos.y = g_aEffect_Comet[nCnt].pos.y + cosf(g_aEffect_Comet[nCnt].rot.z + (D3DX_PI - g_aEffect_Comet[nCnt].fAngle)) * g_aEffect_Comet[nCnt].fLength;
			pVtx_Effect_Comet[2].pos.x = g_aEffect_Comet[nCnt].pos.x + sinf(g_aEffect_Comet[nCnt].rot.z - g_aEffect_Comet[nCnt].fAngle) * g_aEffect_Comet[nCnt].fLength;
			pVtx_Effect_Comet[2].pos.y = g_aEffect_Comet[nCnt].pos.y + cosf(g_aEffect_Comet[nCnt].rot.z - g_aEffect_Comet[nCnt].fAngle) * g_aEffect_Comet[nCnt].fLength;
			pVtx_Effect_Comet[3].pos.x = g_aEffect_Comet[nCnt].pos.x + sinf(g_aEffect_Comet[nCnt].rot.z + g_aEffect_Comet[nCnt].fAngle) * g_aEffect_Comet[nCnt].fLength;
			pVtx_Effect_Comet[3].pos.y = g_aEffect_Comet[nCnt].pos.y + cosf(g_aEffect_Comet[nCnt].rot.z + g_aEffect_Comet[nCnt].fAngle) * g_aEffect_Comet[nCnt].fLength;
		}

		pVtx_Effect_Comet += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Effect_Comet->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Effect_Comet(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Effect_Comet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Effect_Comet);

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP,
		D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND,
		D3DBLEND_ONE);

	//ポリゴンの描画
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_COMET; nCnt++)
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
//頂点を展開する関数
//************************************************
void SetPos_Vtx_Effect_Comet(D3DXVECTOR3 pos, float moveX)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Effect_Comet;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Effect_Comet->Lock(0, 0, (void**)&pVtx_Effect_Comet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_COMET; nCnt++)
	{
		if (!g_aEffect_Comet[nCnt].bUse)
		{
			g_aEffect_Comet[nCnt].pos = pos;
			g_aEffect_Comet[nCnt].move.x = moveX;
			g_aEffect_Comet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEffect_Comet[nCnt].bUse = true;

			g_aEffect_Comet[nCnt].fLength = sqrtf(SPAN_X_EFFECT_COMET * SPAN_X_EFFECT_COMET +
				SPAN_Y_EFFECT_COMET * SPAN_Y_EFFECT_COMET) * 0.5f;

			g_aEffect_Comet[nCnt].fAngle = atan2f(SPAN_X_EFFECT_COMET, SPAN_Y_EFFECT_COMET);

			g_aEffect_Comet[nCnt].nPattern = 0;
			g_aEffect_Comet[nCnt].fTexX = 0.0f;
			g_aEffect_Comet[nCnt].fTexY = 0.0f;

			break;
		}

		pVtx_Effect_Comet += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Effect_Comet->Unlock();
}