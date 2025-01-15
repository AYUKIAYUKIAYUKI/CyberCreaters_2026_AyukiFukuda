//************************************************
//
//弾道エフェクト処理[effect_bullet.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "effect_bullet.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Effect_Bullet = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Effect_Bullet = NULL;	//頂点バッファのポインタ
EFFECT_BULLET g_aEffect_Bullet[AMOUNT_POLYGON_EFFECT_BULLET];	//弾道エフェクト情報を格納

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Effect_Bullet()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_EFFECT_BULLET,
		&g_pTexture_Effect_Bullet);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_EFFECT_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Effect_Bullet,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Effect_Bullet;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Effect_Bullet->Lock(0, 0, (void**)&pVtx_Effect_Bullet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_BULLET; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Effect_Bullet[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Bullet[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Bullet[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Bullet[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Effect_Bullet[0].rhw = 1.0f;
		pVtx_Effect_Bullet[1].rhw = 1.0f;
		pVtx_Effect_Bullet[2].rhw = 1.0f;
		pVtx_Effect_Bullet[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Effect_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Effect_Bullet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Effect_Bullet[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Effect_Bullet[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Effect_Bullet[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Effect_Bullet += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Effect_Bullet->Unlock();

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_BULLET; nCnt++)
	{
		g_aEffect_Bullet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置を初期化
		g_aEffect_Bullet[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect_Bullet[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEffect_Bullet[nCnt].fRadius = 0.0f;							//半径を初期化
		g_aEffect_Bullet[nCnt].nRemain = 0;								//残存時間を初期化
		g_aEffect_Bullet[nCnt].bUse = false;							//使用判定を無くす
	}
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Effect_Bullet(void)
{
	//テクスチャの破棄
	if (g_pTexture_Effect_Bullet != NULL)
	{
		g_pTexture_Effect_Bullet->Release();
		g_pTexture_Effect_Bullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Effect_Bullet != NULL)
	{
		g_pVtxBuff_Effect_Bullet->Release();
		g_pVtxBuff_Effect_Bullet = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Effect_Bullet(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Effect_Bullet;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Effect_Bullet->Lock(0, 0, (void**)&pVtx_Effect_Bullet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_BULLET; nCnt++)
	{
		//エフェクトが使用されてるとき
		if (g_aEffect_Bullet[nCnt].bUse)
		{
			//移動
			g_aEffect_Bullet[nCnt].pos += g_aEffect_Bullet[nCnt].move * 0.75f;
			g_aEffect_Bullet[nCnt].pos.x -= 5.0f;

			//縮む
			g_aEffect_Bullet[nCnt].fRadius -= CHANGE_SPD_RADIUS_EFFECT_BULLET;

			//裏返るの防止
			if (g_aEffect_Bullet[nCnt].fRadius <= 0)
			{
				g_aEffect_Bullet[nCnt].fRadius = 0.0f;
			}

			pVtx_Effect_Bullet[0].pos.x = g_aEffect_Bullet[nCnt].pos.x - g_aEffect_Bullet[nCnt].fRadius;
			pVtx_Effect_Bullet[0].pos.y = g_aEffect_Bullet[nCnt].pos.y - g_aEffect_Bullet[nCnt].fRadius;
			pVtx_Effect_Bullet[1].pos.x = g_aEffect_Bullet[nCnt].pos.x + g_aEffect_Bullet[nCnt].fRadius;
			pVtx_Effect_Bullet[1].pos.y = g_aEffect_Bullet[nCnt].pos.y - g_aEffect_Bullet[nCnt].fRadius;
			pVtx_Effect_Bullet[2].pos.x = g_aEffect_Bullet[nCnt].pos.x - g_aEffect_Bullet[nCnt].fRadius;
			pVtx_Effect_Bullet[2].pos.y = g_aEffect_Bullet[nCnt].pos.y + g_aEffect_Bullet[nCnt].fRadius;
			pVtx_Effect_Bullet[3].pos.x = g_aEffect_Bullet[nCnt].pos.x + g_aEffect_Bullet[nCnt].fRadius;
			pVtx_Effect_Bullet[3].pos.y = g_aEffect_Bullet[nCnt].pos.y + g_aEffect_Bullet[nCnt].fRadius;

			pVtx_Effect_Bullet[0].col = g_aEffect_Bullet[nCnt].col;
			pVtx_Effect_Bullet[1].col = g_aEffect_Bullet[nCnt].col;
			pVtx_Effect_Bullet[2].col = g_aEffect_Bullet[nCnt].col;
			pVtx_Effect_Bullet[3].col = g_aEffect_Bullet[nCnt].col;

			//残存時間減る
			g_aEffect_Bullet[nCnt].nRemain--;

			//消える
			if (g_aEffect_Bullet[nCnt].nRemain <= 0)
			{
				pVtx_Effect_Bullet[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
				pVtx_Effect_Bullet[1].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
				pVtx_Effect_Bullet[2].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
				pVtx_Effect_Bullet[3].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);

				pVtx_Effect_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx_Effect_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx_Effect_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx_Effect_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				g_aEffect_Bullet[nCnt].bUse = false;
			}
		}

		pVtx_Effect_Bullet += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Effect_Bullet->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Effect_Bullet(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Effect_Bullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Effect_Bullet);

	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP,
		D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND,
		D3DBLEND_ONE);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_BULLET; nCnt++)
	{
		//ポリゴンの描画
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
//エフェクトの情報を設定する関数
//************************************************
void Setinfo_Effect_Bullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Effect_Bullet;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Effect_Bullet->Lock(0, 0, (void**)&pVtx_Effect_Bullet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_BULLET; nCnt++)
	{
		//使われていない時
		if (!g_aEffect_Bullet[nCnt].bUse)
		{
			g_aEffect_Bullet[nCnt].pos = pos;	//位置を代入
			g_aEffect_Bullet[nCnt].move = move;	//クソコード乙
			g_aEffect_Bullet[nCnt].col = col;	
			g_aEffect_Bullet[nCnt].fRadius = RADIUS_EFFECT_BULLET;	//適当に半径を調整
			g_aEffect_Bullet[nCnt].nRemain = REMAIN_TIME_EFFECT_BULLET;	//適当に残存時間を調整
			g_aEffect_Bullet[nCnt].bUse = true;	//使用判定を出す

			break;
		}

		pVtx_Effect_Bullet += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Effect_Bullet->Unlock();
}