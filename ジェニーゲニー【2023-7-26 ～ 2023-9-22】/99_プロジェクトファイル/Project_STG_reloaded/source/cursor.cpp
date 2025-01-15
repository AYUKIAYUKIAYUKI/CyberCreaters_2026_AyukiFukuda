//************************************************
//
//メニューのカーソル処理[cursor.cpp]
//Author：福田歩希
//
//************************************************
#include "input.h"
#include "sound.h"
#include "cursorh.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Cursor[AMOUNT_TEXTURE_CURSOR] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Cursor = NULL;	//頂点バッファのポインタ
CURSOR g_aCursor[AMOUNT_POLYGON_CURSOR];	//カーソル用ポリゴンの情報を格納
int g_nChoosing = 0;	//今何を選んでる
float g_fRotateSPD = 0.0f;

//************************************************
//初期化処理関数
//************************************************
void Init_Cursor(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CURSOR,
		&g_pTexture_Cursor[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_CURSOR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Cursor,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Cursor;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Cursor->Lock(0, 0, (void**)&pVtx_Cursor, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_CURSOR; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Cursor[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Cursor[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Cursor[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Cursor[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Cursor[0].rhw = 1.0f;
		pVtx_Cursor[1].rhw = 1.0f;
		pVtx_Cursor[2].rhw = 1.0f;
		pVtx_Cursor[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Cursor[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Cursor[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Cursor[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Cursor[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Cursor[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Cursor[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Cursor[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Cursor[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Cursor += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Cursor->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_CURSOR; nCnt++)
	{
		g_aCursor[nCnt].nStyle = 0;
		g_aCursor[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCursor[nCnt].fSpanX = 0.0f;
		g_aCursor[nCnt].fSpanY = 0.0f;
		g_aCursor[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCursor[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCursor[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aCursor[nCnt].fLength = 0.0f;
		g_aCursor[nCnt].fAngle = 0.0f;
		g_aCursor[nCnt].nCntStop = 0;
		g_aCursor[nCnt].bTurn = false;
	}

	//今選んでるもの初期化
	g_nChoosing = 0;

	g_fRotateSPD = -0.001f;

	//初回のみ頂点を展開
	Setinfo_Cursor();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Cursor(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_CURSOR; nCnt++)
	{
		if (g_pTexture_Cursor[nCnt] != NULL)
		{
			g_pTexture_Cursor[nCnt]->Release();
			g_pTexture_Cursor[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Cursor != NULL)
	{
		g_pVtxBuff_Cursor->Release();
		g_pVtxBuff_Cursor = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Cursor(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Cursor;

	bool* pStart;
	pStart = Getinfo_Menu();

	bool* pPopup;
	pPopup = Getinfo_Tutorial_Menu();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Cursor->Lock(0, 0, (void**)&pVtx_Cursor, 0);

	if (*pStart == false && *pPopup == false)
	{
		if (GetKeyboardTrigger(DIK_LEFT) == true || GetJoypadTrigger(JOYKEY_LEFT) == true)
		{
			if (g_nChoosing > 0)
			{
				g_nChoosing--;

				//効果音を鳴らす
				PlaySound(SOUND_LABEL_SE_SELECT1);
			}
		}
		else if (GetKeyboardTrigger(DIK_RIGHT) == true || GetJoypadTrigger(JOYKEY_RIGHT) == true)
		{
			if (g_nChoosing < 1)
			{
				g_nChoosing++;

				//効果音を鳴らす
				PlaySound(SOUND_LABEL_SE_SELECT1);
			}
		}
	}

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_CURSOR; nCnt++)
	{
		if (g_nChoosing == 0)
		{
			//g_aCursor[nCnt].pos = D3DXVECTOR3(820.0f, 760.0f, 0.0f);

			if (g_aCursor[nCnt].pos.x > 1035.0f)
			{
				if (g_aCursor[nCnt].move.x < 50.0f)
				{
					g_aCursor[nCnt].move.x += 20.0f;
				}
			}
			else
			{
				if (g_aCursor[nCnt].move.x > 0.0f)
				{
					g_aCursor[nCnt].move.x -= 10.0f;
				}
			}

			g_aCursor[nCnt].pos.x -= g_aCursor[nCnt].move.x;
		}
		else
		{
			//g_aCursor[nCnt].pos = D3DXVECTOR3(1830.0f, 760.0f, 0.0f);

			if (g_aCursor[nCnt].pos.x < 1615.0f)
			{
				if (g_aCursor[nCnt].move.x < 50.0f)
				{
					g_aCursor[nCnt].move.x += 20.0f;
				}
			}
			else
			{
				if (g_aCursor[nCnt].move.x > 0.0f)
				{
					g_aCursor[nCnt].move.x -= 10.0f;
				}
			}

			g_aCursor[nCnt].pos.x += g_aCursor[nCnt].move.x;
		}

		//移動を反映
		pVtx_Cursor[0].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z - (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[0].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z - (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[1].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z + (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[1].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z + (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[2].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z - g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[2].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z - g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[3].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z + g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[3].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z + g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;

		pVtx_Cursor[0].col = g_aCursor[nCnt].col;
		pVtx_Cursor[1].col = g_aCursor[nCnt].col;
		pVtx_Cursor[2].col = g_aCursor[nCnt].col;
		pVtx_Cursor[3].col = g_aCursor[nCnt].col;

		pVtx_Cursor += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Cursor->Unlock();

	//ぐりぐりアニメーション
	Animation_Cursor();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Cursor(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Cursor, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_CURSOR; nCnt++)
	{
		switch (g_aCursor[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Cursor[0]);

			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Cursor(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_CURSOR; nCnt++)
	{
		g_aCursor[nCnt].nStyle = nCnt;
		g_aCursor[nCnt].pos = D3DXVECTOR3(570.0f + 295.0f, 650.0f + 285.0f, 0.0f);
		g_aCursor[nCnt].fSpanX = 50.0f;
		g_aCursor[nCnt].fSpanY = 50.0f;
		g_aCursor[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCursor[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCursor[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aCursor[nCnt].fLength = sqrtf((g_aCursor[nCnt].fSpanX * g_aCursor[nCnt].fSpanX) + (g_aCursor[nCnt].fSpanY * g_aCursor[nCnt].fSpanY));
		g_aCursor[nCnt].fAngle = atan2f(g_aCursor[nCnt].fSpanX * 2.0f, g_aCursor[nCnt].fSpanX * 2.0f);
		g_aCursor[nCnt].nCntStop = 0;
		g_aCursor[nCnt].bTurn = false;
	}
}

//************************************************
//ぐりぐりアニメーション関数
//************************************************
void Animation_Cursor(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Cursor;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Cursor->Lock(0, 0, (void**)&pVtx_Cursor, 0);

	//回転の反映
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_CURSOR; nCnt++)
	{
		if (g_aCursor[nCnt].rot.z > -0.6f && !g_aCursor[nCnt].bTurn)
		{
			g_fRotateSPD *= 1.1f;

			g_aCursor[nCnt].rot.z += g_fRotateSPD;
		}
		else
		{
			g_aCursor[nCnt].bTurn = true;
			
			g_aCursor[nCnt].nCntStop++;
		
			if (g_aCursor[nCnt].nCntStop > 9)
			{
				g_aCursor[nCnt].rot.z += 0.075f;

				if (g_aCursor[nCnt].rot.z >= 0.0f)
				{
					g_aCursor[nCnt].nCntStop = 0;

					g_aCursor[nCnt].rot.z = 0.0f;

					g_aCursor[nCnt].bTurn = false;

					g_fRotateSPD = -0.001f;
				}
			}
		}

		pVtx_Cursor[0].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z - (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[0].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z - (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[1].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z + (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[1].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z + (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[2].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z - g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[2].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z - g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[3].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z + g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[3].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z + g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Cursor->Unlock();
}

//************************************************
//選択状況を引き渡す関数
//************************************************
int* Getinfo_Choose(void)
{
	return &g_nChoosing;
}