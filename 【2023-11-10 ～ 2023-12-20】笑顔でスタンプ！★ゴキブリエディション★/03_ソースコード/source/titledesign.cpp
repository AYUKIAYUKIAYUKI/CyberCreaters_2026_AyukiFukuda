//************************************************
//
//タイトルデザイン[titledesign.cpp]
//Author：福田歩希
//
//************************************************
#include "titledesign.h"

#include "fade.h"
#include "input.h"
#include "sound.h"

//タイトルデザイン用
typedef enum
{
	TexLogo = 0,
	TexStart,
	TexRanking,
	TexEnd,
	TexBlack,
	TexArrow,
	TexTutorial,
	TexDo,
	TexDonot,
	TexMax
}TexType;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitleDesign[TexMax] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleDesign = NULL;	//頂点バッファのポインタ
TitleDesign g_aTitleDesign[TexMax];	//情報
int g_nChoose = TexStart;
bool g_bChoose = false;
bool g_bDoTutorial = true;

//************************************************
//タイトルデザイン初期
//************************************************
void InitTitleDesign(void)
{
	g_nChoose = TexStart;
	g_bChoose = false;
	g_bDoTutorial = true;

	//構造体の情報の初期化群
	for (int i = 0; i < TexMax; i++)
	{
		g_aTitleDesign[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitleDesign[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitleDesign[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitleDesign[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aTitleDesign[i].sizeX = 0.0f;
		g_aTitleDesign[i].sizeY = 0.0f;
		g_aTitleDesign[i].F = 1.0f;	//汎用
	}

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	const char* pFileName[TexMax] = 
	{
		"data\\texture\\roach.png",
		"data\\texture\\start.png",
		"data\\texture\\ranking.png",
		"data\\texture\\end.png",
		"data\\texture\\blackbase.png",
		"data\\texture\\arrow.png",
		"data\\texture\\choosetutorial.png",
		"data\\texture\\do.png",
		"data\\texture\\donot.png",
	};

	for (int i = 0; i < TexMax; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureTitleDesign[i]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * TexMax,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleDesign,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffTitleDesign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++)
	{
		//頂点座標の初期設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

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

	//頂点バッファをアンロックする
	g_pVtxBuffTitleDesign->Unlock();

	//情報を付与
	SetInfoTitleDesign();

	//展開
	SetSizeTitleDesign();
}

//************************************************
//タイトルデザイン終了処理関数
//************************************************
void UninitTitleDesign(void)
{
	//テクスチャの破棄
	for (int i = 0; i < TexMax; i++)
	{
		if (g_pTextureTitleDesign[i] != NULL)
		{
			g_pTextureTitleDesign[i]->Release();
			g_pTextureTitleDesign[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitleDesign != NULL)
	{
		g_pVtxBuffTitleDesign->Release();
		g_pVtxBuffTitleDesign = NULL;
	}
}

//************************************************
//タイトルデザイン更新
//************************************************
void UpdateTitleDesign(void)
{
	//フェード情報用
	FADE* pFade = GetInfoFade();

	//選択
	if (!g_bChoose)
	{
		if (GetKeyboardTrigger(DIK_W) || GetJoypadTrigger(JOYKEY_UP))
		{
			g_nChoose > TexStart ? g_nChoose-- : g_nChoose = TexEnd;
			PlaySound(SOUND_LABEL_CHOOSE);
		}
		else if (GetKeyboardTrigger(DIK_S) || GetJoypadTrigger(JOYKEY_DOWN))
		{
			g_nChoose < TexEnd ? g_nChoose++ : g_nChoose = TexStart;
			PlaySound(SOUND_LABEL_CHOOSE);
		}

		if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_B) || GetJoypadTrigger(JOYKEY_START))
		{
			if (g_nChoose == TexStart)
			{
				g_bChoose = true;
			}
			else
			{
				//フェードアウト開始
				pFade->bFadeIn = false;
				pFade->bFadeOut = true;
			}
			PlaySound(SOUND_LABEL_DEFINE);
		}
	}
	else
	{
		if (GetKeyboardTrigger(DIK_A) || GetKeyboardTrigger(DIK_D) || GetJoypadTrigger(JOYKEY_LEFT) || GetJoypadTrigger(JOYKEY_RIGHT))
		{
			g_bDoTutorial = !g_bDoTutorial;
			PlaySound(SOUND_LABEL_CHOOSE);
		}

		if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_B) || GetJoypadTrigger(JOYKEY_START))
		{
			//フェードアウト開始
			pFade->bFadeIn = false;
			pFade->bFadeOut = true;
			PlaySound(SOUND_LABEL_DEFINE);
		}
	}

	//展開
	SetSizeTitleDesign();

	//色変更
	UpdateColTitleDesign();
}

//************************************************
//タイトルデザイン展開
//************************************************
void SetSizeTitleDesign(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffTitleDesign->Lock(0, 0, (void**)&pVtx, 0);

	int nLoopAmount = 0;

	if (!g_bChoose)
	{
		nLoopAmount = TexTutorial;
	}
	else
	{
		nLoopAmount = TexMax;
	}

	for (int i = 0; i < nLoopAmount; i++, pVtx += AMOUNT_VTX)
	{
		if (!g_bChoose)
		{
			if (i == TexBlack)
			{
				continue;
			}

			if (i == TexArrow)
			{
				g_aTitleDesign[i].pos =
				{
					g_aTitleDesign[g_nChoose].pos.x - 175.0f,
					g_aTitleDesign[g_nChoose].pos.y,
					g_aTitleDesign[g_nChoose].pos.z,
				};
			}
		}
		else
		{
			if (i == TexArrow)
			{
				if (g_bDoTutorial)
				{
					g_aTitleDesign[i].pos =
					{
						g_aTitleDesign[TexDo].pos.x - 225.0f,
						g_aTitleDesign[TexDo].pos.y,
						g_aTitleDesign[TexDo].pos.z,
					};
				}
				else
				{
					g_aTitleDesign[i].pos =
					{
						g_aTitleDesign[TexDonot].pos.x - 375.0f,
						g_aTitleDesign[TexDonot].pos.y,
						g_aTitleDesign[TexDonot].pos.z,
					};
				}
			}
		}


		//頂点座標の初期設定
		pVtx[0].pos =
		{
			g_aTitleDesign[i].pos.x - g_aTitleDesign[i].sizeX,
			g_aTitleDesign[i].pos.y - g_aTitleDesign[i].sizeY,
			0.0f
		};

		pVtx[1].pos =
		{
			g_aTitleDesign[i].pos.x + g_aTitleDesign[i].sizeX,
			g_aTitleDesign[i].pos.y - g_aTitleDesign[i].sizeY,
			0.0f
		};

		pVtx[2].pos =
		{
			g_aTitleDesign[i].pos.x - g_aTitleDesign[i].sizeX,
			g_aTitleDesign[i].pos.y + g_aTitleDesign[i].sizeY,
			0.0f
		};

		pVtx[3].pos =
		{
			g_aTitleDesign[i].pos.x + g_aTitleDesign[i].sizeX,
			g_aTitleDesign[i].pos.y + g_aTitleDesign[i].sizeY,
			0.0f
		};
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitleDesign->Unlock();
}

//************************************************
//タイトルデザイン色変更
//************************************************
void UpdateColTitleDesign(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffTitleDesign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		//選んでるものの色を変更するだけ
		if (!g_bChoose)
		{
			if (i == g_nChoose)
			{
				g_aTitleDesign[i].col.r = 0.0f;
				g_aTitleDesign[i].col.b = 0.0f;
			}
			else
			{
				g_aTitleDesign[i].col.r = 1.0f;
				g_aTitleDesign[i].col.b = 1.0f;
			}
		}
		else
		{
			if (g_bDoTutorial)
			{
				g_aTitleDesign[TexDo].col.r = 0.0f;
				g_aTitleDesign[TexDo].col.b = 0.0f;

				g_aTitleDesign[TexDonot].col.r = 1.0f;
				g_aTitleDesign[TexDonot].col.b = 1.0f;
			}
			else
			{
				g_aTitleDesign[TexDo].col.r = 1.0f;
				g_aTitleDesign[TexDo].col.b = 1.0f;

				g_aTitleDesign[TexDonot].col.r = 0.0f;
				g_aTitleDesign[TexDonot].col.b = 0.0f;
			}
		}

		pVtx[0].col = g_aTitleDesign[i].col;
		pVtx[1].col = g_aTitleDesign[i].col;
		pVtx[2].col = g_aTitleDesign[i].col;
		pVtx[3].col = g_aTitleDesign[i].col;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitleDesign->Unlock();
}

//************************************************
//タイトルデザイン描画
//************************************************
void DrawTitleDesign(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleDesign, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TexMax; i++)
	{
		pDevice->SetTexture(0, g_pTextureTitleDesign[i]);

		//タイトルデザインの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//構造体の情報を設定する関数
//************************************************
void SetInfoTitleDesign(void)
{
	for (int i = 0; i < TexMax; i++)
	{
		g_aTitleDesign[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitleDesign[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitleDesign[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTitleDesign[i].F = 1.0f;	//汎用

		if (i == TexLogo || i == TexBlack || i == TexTutorial)
		{
			g_aTitleDesign[i].pos = D3DXVECTOR3((float)SCREEN_HALFWIDTH, (float)SCREEN_HALFHEIGHT, 0.0f);
			g_aTitleDesign[i].sizeX = (float)SCREEN_HALFWIDTH;
			g_aTitleDesign[i].sizeY = (float)SCREEN_HALFHEIGHT;

			if (i == TexBlack)
			{
				g_aTitleDesign[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
			}
		}
		else if (i == TexArrow)
		{
			g_aTitleDesign[i].sizeX = 50.0f;
			g_aTitleDesign[i].sizeY = 50.0f;
		}
		else if (i == TexDo)
		{
			g_aTitleDesign[i].pos = D3DXVECTOR3(500.0f, 850.0f, 0.0f);
			g_aTitleDesign[i].sizeX = 300.0f;
			g_aTitleDesign[i].sizeY = 80.0f;
		}
		else if (i == TexDonot)
		{
			g_aTitleDesign[i].pos = D3DXVECTOR3(1200.0f, 850.0f, 0.0f);
			g_aTitleDesign[i].sizeX = 300.0f;
			g_aTitleDesign[i].sizeY = 80.0f;
		}
		else
		{
			g_aTitleDesign[i].pos = D3DXVECTOR3(1800.0f, 700.0f + (i * 100.0f), 0.0f);
			g_aTitleDesign[i].sizeX = 125.0f;
			g_aTitleDesign[i].sizeY = 50.0f;
		}
	}
}

//************************************************
//何選んでるか
//************************************************
MODE GetChooseMode(void)
{
	int nChoose = 0;

	if (g_nChoose == TexStart)
	{
		if (g_bDoTutorial)
		{
			nChoose = MODE_TUTORIAL;
		}
		else
		{
			nChoose = MODE_GAME;
		}
	}
	else if (g_nChoose == TexRanking)
	{
		nChoose = MODE_RANKING;
	}
	else if (g_nChoose == TexEnd)
	{
		nChoose = MODE_END;
	}

	return (MODE)nChoose;
}