//************************************************
//
//メニューのカーソル処理[tutorial_cursor.cpp]
//Author：福田歩希
//
//************************************************
#include "input.h"
#include "sound.h"
#include "tutorial_cursor.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Tutorial_Cursor[AMOUNT_TEXTURE_TUTORIAL_CURSOR] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Tutorial_Cursor = NULL;	//頂点バッファのポインタ
TUTORIAL_CURSOR g_aTutorial_Cursor[AMOUNT_POLYGON_TUTORIAL_CURSOR];	//カーソル用ポリゴンの情報を格納
int g_nChoosing_Tutorial_Cursor = 0;	//今何を選んでる
float g_fRotateSPD_Tutorial_Cursor = 0.0f;

//************************************************
//初期化処理関数
//************************************************
void Init_Tutorial_Cursor(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TUTORIAL_CURSOR,
		&g_pTexture_Tutorial_Cursor[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TUTORIAL_CURSOR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Tutorial_Cursor,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Tutorial_Cursor;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Tutorial_Cursor->Lock(0, 0, (void**)&pVtx_Tutorial_Cursor, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_CURSOR; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Tutorial_Cursor[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Cursor[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Cursor[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Cursor[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Tutorial_Cursor[0].rhw = 1.0f;
		pVtx_Tutorial_Cursor[1].rhw = 1.0f;
		pVtx_Tutorial_Cursor[2].rhw = 1.0f;
		pVtx_Tutorial_Cursor[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Tutorial_Cursor[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Cursor[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Cursor[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Cursor[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Tutorial_Cursor[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Tutorial_Cursor[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Tutorial_Cursor[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Tutorial_Cursor[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Tutorial_Cursor += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Tutorial_Cursor->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_CURSOR; nCnt++)
	{
		g_aTutorial_Cursor[nCnt].nStyle = 0;
		g_aTutorial_Cursor[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].fSpanX = 0.0f;
		g_aTutorial_Cursor[nCnt].fSpanY = 0.0f;
		g_aTutorial_Cursor[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].fLength = 0.0f;
		g_aTutorial_Cursor[nCnt].fAngle = 0.0f;
		g_aTutorial_Cursor[nCnt].nCntStop = 0;
		g_aTutorial_Cursor[nCnt].bTurn = false;
		g_aTutorial_Cursor[nCnt].colA = 0.0f;
	}

	//今選んでるもの初期化
	g_nChoosing_Tutorial_Cursor = 0;

	g_fRotateSPD_Tutorial_Cursor = -0.001f;

	//初回のみ頂点を展開
	Setinfo_Tutorial_Cursor();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Tutorial_Cursor(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_TUTORIAL_CURSOR; nCnt++)
	{
		if (g_pTexture_Tutorial_Cursor[nCnt] != NULL)
		{
			g_pTexture_Tutorial_Cursor[nCnt]->Release();
			g_pTexture_Tutorial_Cursor[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Tutorial_Cursor != NULL)
	{
		g_pVtxBuff_Tutorial_Cursor->Release();
		g_pVtxBuff_Tutorial_Cursor = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Tutorial_Cursor(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Tutorial_Cursor;

	bool* pStart;
	pStart = Getinfo_Menu();

	bool* pPopup;
	pPopup = Getinfo_Tutorial_Menu();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Tutorial_Cursor->Lock(0, 0, (void**)&pVtx_Tutorial_Cursor, 0);

	if (*pStart == false && *pPopup == true)
	{
		if (GetKeyboardTrigger(DIK_LEFT) == true || GetJoypadTrigger(JOYKEY_LEFT) == true)
		{
			if (g_nChoosing_Tutorial_Cursor > 0)
			{
				g_nChoosing_Tutorial_Cursor--;

				//効果音を鳴らす
				PlaySound(SOUND_LABEL_SE_SELECT1);
			}
		}
		else if (GetKeyboardTrigger(DIK_RIGHT) == true || GetJoypadTrigger(JOYKEY_RIGHT) == true)
		{
			if (g_nChoosing_Tutorial_Cursor < 1)
			{
				g_nChoosing_Tutorial_Cursor++;

				//効果音を鳴らす
				PlaySound(SOUND_LABEL_SE_SELECT1);
			}
		}
	}

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_CURSOR; nCnt++)
	{
		if (g_aTutorial_Cursor[nCnt].colA < 1.0f)
		{
			g_aTutorial_Cursor[nCnt].colA *= 1.1f;
		}
		else
		{
			g_aTutorial_Cursor[nCnt].colA = 1.0;
		}

		g_aTutorial_Cursor[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTutorial_Cursor[nCnt].colA);

		if (g_nChoosing_Tutorial_Cursor == 0)
		{
			if (g_aTutorial_Cursor[nCnt].pos.x > 1020.0f)
			{
				if (g_aTutorial_Cursor[nCnt].move.x < 50.0f)
				{
					g_aTutorial_Cursor[nCnt].move.x += 20.0f;
				}
			}
			else
			{
				if (g_aTutorial_Cursor[nCnt].move.x > 0.0f)
				{
					g_aTutorial_Cursor[nCnt].move.x -= 10.0f;
				}
			}

			g_aTutorial_Cursor[nCnt].pos.x -= g_aTutorial_Cursor[nCnt].move.x;
		}
		else
		{
			if (g_aTutorial_Cursor[nCnt].pos.x < 1250.0f)
			{
				if (g_aTutorial_Cursor[nCnt].move.x < 50.0f)
				{
					g_aTutorial_Cursor[nCnt].move.x += 20.0f;
				}
			}
			else
			{
				if (g_aTutorial_Cursor[nCnt].move.x > 0.0f)
				{
					g_aTutorial_Cursor[nCnt].move.x -= 10.0f;
				}
			}

			g_aTutorial_Cursor[nCnt].pos.x += g_aTutorial_Cursor[nCnt].move.x;
		}

		//移動を反映
		pVtx_Tutorial_Cursor[0].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z - (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[0].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z - (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[1].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z + (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[1].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z + (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[2].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z - g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[2].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z - g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[3].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z + g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[3].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z + g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;

		pVtx_Tutorial_Cursor[0].col = g_aTutorial_Cursor[nCnt].col;
		pVtx_Tutorial_Cursor[1].col = g_aTutorial_Cursor[nCnt].col;
		pVtx_Tutorial_Cursor[2].col = g_aTutorial_Cursor[nCnt].col;
		pVtx_Tutorial_Cursor[3].col = g_aTutorial_Cursor[nCnt].col;

		pVtx_Tutorial_Cursor += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Tutorial_Cursor->Unlock();

	//ぐりぐりアニメーション
	Animation_Tutorial_Cursor();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Tutorial_Cursor(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Tutorial_Cursor, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_CURSOR; nCnt++)
	{
		switch (g_aTutorial_Cursor[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Tutorial_Cursor[0]);

			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Tutorial_Cursor(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_CURSOR; nCnt++)
	{
		g_aTutorial_Cursor[nCnt].nStyle = nCnt;
		g_aTutorial_Cursor[nCnt].pos = D3DXVECTOR3(750.0f + 120.0f, 600.0f + 125.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].fSpanX = 50.0f;
		g_aTutorial_Cursor[nCnt].fSpanY = 50.0f;
		g_aTutorial_Cursor[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].fLength = sqrtf((g_aTutorial_Cursor[nCnt].fSpanX * g_aTutorial_Cursor[nCnt].fSpanX) + (g_aTutorial_Cursor[nCnt].fSpanY * g_aTutorial_Cursor[nCnt].fSpanY));
		g_aTutorial_Cursor[nCnt].fAngle = atan2f(g_aTutorial_Cursor[nCnt].fSpanX * 2.0f, g_aTutorial_Cursor[nCnt].fSpanX * 2.0f);
		g_aTutorial_Cursor[nCnt].nCntStop = 0;
		g_aTutorial_Cursor[nCnt].bTurn = false;
		g_aTutorial_Cursor[nCnt].colA = 0.01f;
	}
}

//************************************************
//ぐりぐりアニメーション関数
//************************************************
void Animation_Tutorial_Cursor(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Tutorial_Cursor;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Tutorial_Cursor->Lock(0, 0, (void**)&pVtx_Tutorial_Cursor, 0);

	//回転の反映
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_CURSOR; nCnt++)
	{
		if (g_aTutorial_Cursor[nCnt].rot.z > -0.6f && !g_aTutorial_Cursor[nCnt].bTurn)
		{
			g_fRotateSPD_Tutorial_Cursor *= 1.1f;

			g_aTutorial_Cursor[nCnt].rot.z += g_fRotateSPD_Tutorial_Cursor;
		}
		else
		{
			g_aTutorial_Cursor[nCnt].bTurn = true;

			g_aTutorial_Cursor[nCnt].nCntStop++;

			if (g_aTutorial_Cursor[nCnt].nCntStop > 9)
			{
				g_aTutorial_Cursor[nCnt].rot.z += 0.075f;

				if (g_aTutorial_Cursor[nCnt].rot.z >= 0.0f)
				{
					g_aTutorial_Cursor[nCnt].nCntStop = 0;

					g_aTutorial_Cursor[nCnt].rot.z = 0.0f;

					g_aTutorial_Cursor[nCnt].bTurn = false;

					g_fRotateSPD_Tutorial_Cursor = -0.001f;
				}
			}
		}

		pVtx_Tutorial_Cursor[0].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z - (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[0].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z - (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[1].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z + (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[1].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z + (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[2].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z - g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[2].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z - g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[3].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z + g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[3].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z + g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Tutorial_Cursor->Unlock();
}

//************************************************
//選択状況を引き渡す関数
//************************************************
int* Getinfo_Choose_YesNo(void)
{
	return &g_nChoosing_Tutorial_Cursor;
}