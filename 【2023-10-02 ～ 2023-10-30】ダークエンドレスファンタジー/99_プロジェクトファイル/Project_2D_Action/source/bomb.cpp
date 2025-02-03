//************************************************
//
//ボム処理[bomb.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "bomb.h"
#include "attack_box.h"
#include "camera.h"
#include "player.h"
#include "stage.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Bomb[AMOUNT_TEX_BOMB] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Bomb = NULL;	//頂点バッファのポインタ
BOMB g_aBomb[AMOUNT_POLYGON_BOMB];	//ボム情報
BOMB_BOX g_aBomb_Box[BOMB_STATE_MAX];
int g_nCharge = 0;
static float g_F = 0;	//汎用浮動小数

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Bomb()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BOMB_1,
		&g_pTexture_Bomb[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BOMB_2,
		&g_pTexture_Bomb[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BOMB,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Bomb,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Bomb;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Bomb->Lock(0, 0, (void**)&pVtx_Bomb, 0);

	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		//頂点座標の初期設定
		pVtx_Bomb[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bomb[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bomb[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bomb[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Bomb[0].rhw = 1.0f;
		pVtx_Bomb[1].rhw = 1.0f;
		pVtx_Bomb[2].rhw = 1.0f;
		pVtx_Bomb[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Bomb[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Bomb[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Bomb[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Bomb[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx_Bomb[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Bomb[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Bomb[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Bomb[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Bomb += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Bomb->Unlock();

	//BOMB構造体の情報の初期化群
	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		g_aBomb[i].bUse = false;
		g_aBomb[i].nState = 0;
		g_aBomb[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBomb[i].oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBomb[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBomb[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBomb[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aBomb[i].LR = 0;
		g_aBomb[i].nCntTex = 0;
		g_aBomb[i].nCntPattern = 0;
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aBomb[i].fTexSpan[nCnt] = 0.0f;
			g_aBomb[i].fTexSpanY[nCnt] = 0.0f;
			g_aBomb[i].fRadius[nCnt] = 0.0f;
			g_aBomb[i].fLength[nCnt] = 0.0f;
			g_aBomb[i].fAngle[nCnt] = 0.0f;
		}
		g_aBomb[i].nCT = 0;
		g_aBomb[i].nCharge = 0;
	}

	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aBomb_Box[i].fRadius_Hold[nCnt] = 0.0f;
			g_aBomb_Box[i].fLength_Hold[nCnt] = 0.0f;
			g_aBomb_Box[i].fAngle_Hold[nCnt] = 0.0f;
		}
	}

	g_nCharge = 0;

	g_F = 0;

	CalcSize_Bomb_Box();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Bomb(void)
{
	//テクスチャの破棄
	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		if (g_pTexture_Bomb[i] != NULL)
		{
			g_pTexture_Bomb[i]->Release();
			g_pTexture_Bomb[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Bomb != NULL)
	{
		g_pVtxBuff_Bomb->Release();
		g_pVtxBuff_Bomb = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Bomb(void)
{
	Update_Pos_Bomb();

	//ボムのリキャスト減少
	if (g_nCharge > 0)
	{
		g_nCharge--;
	}

	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		//使用判定が出ている
		if (g_aBomb[i].bUse)
		{
			if (g_aBomb[i].nState == BOMB_EXPLOSION &&
				g_aBomb[i].nCntTex == 0)
			{
				//爆発
				GiveInfo_Attack_Box(1);

				//ボムリキャスト設定
				g_nCharge = 120;
			}
		}
	}
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Bomb(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Bomb, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		//テクスチャの設定
		switch (g_aBomb[i].nState)
		{
		case 0:
			pDevice->SetTexture(0, g_pTexture_Bomb[0]);
			break;
		case 1:
			pDevice->SetTexture(0, g_pTexture_Bomb[1]);
			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

void CalcSize_Bomb_Box(void)
{
	for (int i = 0; i < BOMB_STATE_MAX; i++)
	{
		switch (i)
		{
		case 0:

			g_aBomb_Box[i].fRadius_Hold[0] = 30.0f;
			g_aBomb_Box[i].fRadius_Hold[1] = 30.0f;

			g_aBomb_Box[i].fLength_Hold[0] = sqrtf((g_aBomb_Box[i].fRadius_Hold[0] * g_aBomb_Box[i].fRadius_Hold[0]) +
				(g_aBomb_Box[i].fRadius_Hold[1] * g_aBomb_Box[i].fRadius_Hold[1]));
			g_aBomb_Box[i].fLength_Hold[1] = g_aBomb_Box[i].fLength_Hold[0];

			g_aBomb_Box[i].fAngle_Hold[0] = atan2f(g_aBomb_Box[i].fRadius_Hold[0] * 2.0f, g_aBomb_Box[i].fRadius_Hold[1] * 2.0f);
			g_aBomb_Box[i].fAngle_Hold[1] = g_aBomb_Box[i].fAngle_Hold[0];

			break;

		case 1:

			g_aBomb_Box[i].fRadius_Hold[0] = 170.0f;
			g_aBomb_Box[i].fRadius_Hold[1] = 170.0f;

			g_aBomb_Box[i].fLength_Hold[0] = sqrtf((g_aBomb_Box[i].fRadius_Hold[0] * g_aBomb_Box[i].fRadius_Hold[0]) +
				(g_aBomb_Box[i].fRadius_Hold[1] * g_aBomb_Box[i].fRadius_Hold[1]));
			g_aBomb_Box[i].fLength_Hold[1] = g_aBomb_Box[i].fLength_Hold[0];

			g_aBomb_Box[i].fAngle_Hold[0] = atan2f(g_aBomb_Box[i].fRadius_Hold[0] * 2.0f, g_aBomb_Box[i].fRadius_Hold[1] * 2.0f);
			g_aBomb_Box[i].fAngle_Hold[1] = g_aBomb_Box[i].fAngle_Hold[0];

			break;
		}
	}
}

//************************************************
//ボム構造体の情報を設定する関数
//************************************************
void SetInfo_Bomb(void)
{
	PLAYER* pPlayer = GetInfo_Player();

	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		//リキャスト済みなら
		if (!g_aBomb[i].bUse && g_nCharge <= 0)
		{
			g_aBomb[i].bUse = true;
			g_aBomb[i].nState = BOMB_IDLE;
			g_aBomb[i].pos = pPlayer->pos;
			pPlayer->LR == 0 ? g_aBomb[i].move.x = 12.5f : g_aBomb[i].move.x = -12.5f;
			g_aBomb[i].move.y = -15.0f;
			g_aBomb[i].oldpos = g_aBomb[i].pos;
			for (int ii = 0; ii < 2; ii++)
			{
				g_aBomb[i].fRadius[ii] = g_aBomb_Box[i].fRadius_Hold[ii];
				g_aBomb[i].fLength[ii] = g_aBomb_Box[i].fLength_Hold[ii];
				g_aBomb[i].fAngle[ii] = g_aBomb_Box[i].fAngle_Hold[ii];
			}
			g_aBomb[i].nCT = 45;

			g_aBomb[i].fTexSpan[0] = 0.0f;
			g_aBomb[i].fTexSpan[1] = SPAN_CHANGE_TEX_BOMB;
			g_aBomb[i].fTexSpanY[0] = 0.0f;
			g_aBomb[i].fTexSpanY[1] = SPAN_CHANGE_TEX_BOMB;

			g_F = 1.0f;

			break;
		}
	}
}

//************************************************
//ボムの位置を設定する関数
//************************************************
void Update_Pos_Bomb(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Bomb;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Bomb->Lock(0, 0, (void**)&pVtx_Bomb, 0);

	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		if (g_aBomb[i].bUse)
		{
			//過去の位置を記録
			g_aBomb[i].oldpos = g_aBomb[i].pos;

			//移動
			g_aBomb[i].pos += g_aBomb[i].move;

			//横移動慣性
			if (g_aBomb[i].nState != BOMB_EXPLOSION)
			{
				g_aBomb[i].move.x = g_aBomb[i].move.x * 0.98f;
			}
			else
			{
				g_aBomb[i].move.x = 0.0f;
			}

			//重力
			g_aBomb[i].move.y = g_aBomb[i].move.y + 1.0f;

			//アニメーション
			Update_Tex_Bomb();

			//状態に合わせてボックス調整
			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				g_aBomb[i].fLength[nCnt] = g_aBomb_Box[g_aBomb[i].nState].fLength_Hold[nCnt];
				g_aBomb[i].fAngle[nCnt] = g_aBomb_Box[g_aBomb[i].nState].fAngle_Hold[nCnt];
			}


			if (g_aBomb[i].nState == BOMB_EXPLOSION)
			{
				if (g_F > 1.0f)
				{
					g_F = 1.0f;
				}
			}


			//地面
			HitDetection_Stage(0, 1, &g_aBomb[i].pos, &g_aBomb[i].oldpos, &g_aBomb[i].move, &g_aBomb[i].fRadius[0]);

			//見かけ移動
			ConvertInfo_Screen(&g_aBomb[i].pos);
		}
		//使用してないならデータクリア
		else
		{
			g_aBomb[i].bUse = false;
			g_aBomb[i].nState = 0;
			g_aBomb[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBomb[i].oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBomb[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBomb[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBomb[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			g_aBomb[i].LR = 0;
			g_aBomb[i].nCntTex = 0;
			g_aBomb[i].nCntPattern = 0;
			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				g_aBomb[i].fTexSpan[nCnt] = 0.0f;
				g_aBomb[i].fTexSpanY[nCnt] = 0.0f;
				g_aBomb[i].fRadius[nCnt] = 0.0f;
				g_aBomb[i].fLength[nCnt] = 0.0f;
				g_aBomb[i].fAngle[nCnt] = 0.0f;
			}
			g_aBomb[i].nCT = 0;
			g_aBomb[i].nCharge = 0;
		}
			
		pVtx_Bomb[0].pos.x = g_aBomb[i].pos.x + sinf(g_aBomb[i].rot.z - (D3DX_PI - g_aBomb[i].fAngle[0])) * g_aBomb[i].fLength[0] * g_F;
		pVtx_Bomb[0].pos.y = g_aBomb[i].pos.y + cosf(g_aBomb[i].rot.z - (D3DX_PI - g_aBomb[i].fAngle[0])) * g_aBomb[i].fLength[0] * g_F;
		pVtx_Bomb[1].pos.x = g_aBomb[i].pos.x + sinf(g_aBomb[i].rot.z + (D3DX_PI - g_aBomb[i].fAngle[0])) * g_aBomb[i].fLength[0] * g_F;
		pVtx_Bomb[1].pos.y = g_aBomb[i].pos.y + cosf(g_aBomb[i].rot.z + (D3DX_PI - g_aBomb[i].fAngle[0])) * g_aBomb[i].fLength[0] * g_F;
		pVtx_Bomb[2].pos.x = g_aBomb[i].pos.x + sinf(g_aBomb[i].rot.z - g_aBomb[i].fAngle[1]) * g_aBomb[i].fLength[1] * g_F;
		pVtx_Bomb[2].pos.y = g_aBomb[i].pos.y + cosf(g_aBomb[i].rot.z - g_aBomb[i].fAngle[1]) * g_aBomb[i].fLength[1] * g_F;
		pVtx_Bomb[3].pos.x = g_aBomb[i].pos.x + sinf(g_aBomb[i].rot.z + g_aBomb[i].fAngle[1]) * g_aBomb[i].fLength[1] * g_F;
		pVtx_Bomb[3].pos.y = g_aBomb[i].pos.y + cosf(g_aBomb[i].rot.z + g_aBomb[i].fAngle[1]) * g_aBomb[i].fLength[1] * g_F;

		if (g_aBomb[i].nState == BOMB_IDLE)
		{
			pVtx_Bomb[0].pos.y += -40.0f;
			pVtx_Bomb[1].pos.y += -40.0f;
			pVtx_Bomb[2].pos.y += -40.0f;
			pVtx_Bomb[3].pos.y += -40.0f;

			g_F *= 1.03f;
		}

		if (g_aBomb[i].nState == BOMB_EXPLOSION)
		{
			pVtx_Bomb[0].pos.y += -40.0f;
			pVtx_Bomb[1].pos.y += -40.0f;
			pVtx_Bomb[2].pos.y += -40.0f;
			pVtx_Bomb[3].pos.y += -40.0f;

			g_F *= 0.96f;
		}

		pVtx_Bomb += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Bomb->Unlock();
}

void Update_Tex_Bomb(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Bomb;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Bomb->Lock(0, 0, (void**)&pVtx_Bomb, 0);

	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		if (g_aBomb[i].bUse)
		{
			//テクスチャを変更
			switch (g_aBomb[i].nState)
			{
			case BOMB_IDLE:
				g_aBomb[i].nCntTex++;
				if (g_aBomb[i].nCntTex > 0)
				{
					g_aBomb[i].nCntTex = 0;
					g_aBomb[i].nCntPattern++;
					g_aBomb[i].fTexSpan[0] += SPAN_CHANGE_TEX_BOMB;
					g_aBomb[i].fTexSpan[1] += SPAN_CHANGE_TEX_BOMB;

					if (g_aBomb[i].fTexSpan[0] >= 1.0f)
					{
						if (g_aBomb[i].fTexSpanY[1] >= SPAN_CHANGE_TEX_BOMB * 6.0f && g_aBomb[i].fTexSpan[1] >= SPAN_CHANGE_TEX_BOMB * 4.0f)
						{
							g_aBomb[i].nCntTex = 0;
							g_aBomb[i].fTexSpan[0] = 0.0f;
							g_aBomb[i].fTexSpan[1] = SPAN_CHANGE_TEX_EXPLOSION;

							g_aBomb[i].nState = BOMB_EXPLOSION;

							break;
						}

						g_aBomb[i].fTexSpan[0] = 0.0f;
						g_aBomb[i].fTexSpan[1] = SPAN_CHANGE_TEX_BOMB;

						g_aBomb[i].fTexSpanY[0] += SPAN_CHANGE_TEX_BOMB;
						g_aBomb[i].fTexSpanY[1] += SPAN_CHANGE_TEX_BOMB;
					}
				}
				break;
			case BOMB_EXPLOSION:
				g_aBomb[i].nCntTex++;
				g_aBomb[i].fTexSpan[0] += SPAN_CHANGE_TEX_EXPLOSION;
				g_aBomb[i].fTexSpan[1] += SPAN_CHANGE_TEX_EXPLOSION;
				g_aBomb[i].fTexSpanY[0] = 0.0f;
				g_aBomb[i].fTexSpanY[1] = SPAN_CHANGE_TEX_EXPLOSION;
				if (g_aBomb[i].nCntTex >= 30)
				{
					g_aBomb[i].fTexSpan[0] = 0.0f;
					g_aBomb[i].fTexSpan[1] = 0.0f;

					g_aBomb[i].fTexSpanY[0] = 0.0f;
					g_aBomb[i].fTexSpanY[1] = 0.0f;

					g_aBomb[i].bUse = false;
				}
				break;
			}

			pVtx_Bomb[0].tex = D3DXVECTOR2(g_aBomb[i].fTexSpan[0], 	g_aBomb[i].fTexSpanY[0]);
			pVtx_Bomb[1].tex = D3DXVECTOR2(g_aBomb[i].fTexSpan[1], 	g_aBomb[i].fTexSpanY[0]);
			pVtx_Bomb[2].tex = D3DXVECTOR2(g_aBomb[i].fTexSpan[0], 	g_aBomb[i].fTexSpanY[1]);
			pVtx_Bomb[3].tex = D3DXVECTOR2(g_aBomb[i].fTexSpan[1], 	g_aBomb[i].fTexSpanY[1]);
		}

		pVtx_Bomb += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Bomb->Unlock();
}

//************************************************
//ボム構造体のアドレスを渡す
//************************************************
BOMB* GetInfo_Bomb(void)
{
	return &g_aBomb[0];
}

int* GetInfo_Bomb_aa(void)
{
	return &g_nCharge;
}