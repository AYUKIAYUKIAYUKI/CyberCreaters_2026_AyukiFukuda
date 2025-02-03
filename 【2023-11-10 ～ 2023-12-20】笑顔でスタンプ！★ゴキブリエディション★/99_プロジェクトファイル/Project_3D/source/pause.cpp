//************************************************
//
//ポーズ[pause.cpp]
//Author：福田歩希
//
//************************************************
#include "pause.h"

#include "game.h"

#include "fade.h"
#include "input.h"
#include "sound.h"

#include "player.h"

//ポーズ用
typedef enum
{
	TexWindow = 0,
	TexContinue,
	TexRetry,
	TexRetire,
	TexArrow,
	TexMax,
}TexType;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePause[TexMax] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;	//頂点バッファのポインタ
Pause g_aPause[TexMax];	//情報
int g_nChoosePause = TexContinue;

//************************************************
//ポーズ初期
//************************************************
void InitPause(void)
{
	g_nChoosePause = TexContinue;

	//構造体の情報の初期化群
	for (int i = 0; i < TexMax; i++)
	{
		g_aPause[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aPause[i].sizeX = 0.0f;
		g_aPause[i].sizeY = 0.0f;
		g_aPause[i].F = 1.0f;	//汎用
	}

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	const char* pFileName[TexMax] =
	{
		"data\\texture\\pause.png",
		"data\\texture\\continue.png",
		"data\\texture\\retry.png",
		"data\\texture\\retire.png",
		"data\\texture\\arrow.png",
	};

	for (int i = 0; i < TexMax; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTexturePause[i]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * TexMax,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffPause->Unlock();

	//情報を付与
	SetInfoPause();

	//展開
	SetSizePause();
}

//************************************************
//ポーズ終了処理関数
//************************************************
void UninitPause(void)
{
	//テクスチャの破棄
	for (int i = 0; i < TexMax; i++)
	{
		if (g_pTexturePause[i] != NULL)
		{
			g_pTexturePause[i]->Release();
			g_pTexturePause[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//************************************************
//ポーズ更新
//************************************************
void UpdatePause(void)
{
	//ポーズ情報用
	bool* pPause = GetInfoPause();

	//フェード情報用
	FADE* pFade = GetInfoFade();

	if (GetKeyboardTrigger(DIK_W) || GetJoypadTrigger(JOYKEY_UP))
	{
		g_nChoosePause > TexContinue ? g_nChoosePause-- : g_nChoosePause = TexRetire;
		PlaySound(SOUND_LABEL_CHOOSE);
	}
	else if (GetKeyboardTrigger(DIK_S) || GetJoypadTrigger(JOYKEY_DOWN))
	{
		g_nChoosePause < TexRetire ? g_nChoosePause++ : g_nChoosePause = TexContinue;
		PlaySound(SOUND_LABEL_CHOOSE);
	}

	//if (GetJoypadTrigger(JOYKEY_START))
	//{
	//	*pPause = false;
	//	g_nChoosePause = TexContinue;
	//}

	if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_B))
	{
		switch(g_nChoosePause)
		{
		case TexContinue:
			*pPause = false;
			break;

		case TexRetry:
			//フェードアウト開始
			pFade->bFadeIn = false;
			pFade->bFadeOut = true;
			break;

		case TexRetire:
			//フェードアウト開始
			pFade->bFadeIn = false;
			pFade->bFadeOut = true;
			break;
		}
		PlaySound(SOUND_LABEL_DEFINE);
	}

	//展開
	SetSizePause();

	//色変更
	UpdateColPause();
}

//************************************************
//ポーズ展開
//************************************************
void SetSizePause(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		if (i == TexArrow)
		{
			g_aPause[i].pos =
			{
				g_aPause[g_nChoosePause].pos.x - 220.0f,
				g_aPause[g_nChoosePause].pos.y,
				g_aPause[g_nChoosePause].pos.z,
			};
		}

		//頂点座標の設定
		pVtx[0].pos =
		{
			g_aPause[i].pos.x - g_aPause[i].sizeX,
			g_aPause[i].pos.y - g_aPause[i].sizeY,
			0.0f
		};

		pVtx[1].pos =
		{
			g_aPause[i].pos.x + g_aPause[i].sizeX,
			g_aPause[i].pos.y - g_aPause[i].sizeY,
			0.0f
		};

		pVtx[2].pos =
		{
			g_aPause[i].pos.x - g_aPause[i].sizeX,
			g_aPause[i].pos.y + g_aPause[i].sizeY,
			0.0f
		};

		pVtx[3].pos =
		{
			g_aPause[i].pos.x + g_aPause[i].sizeX,
			g_aPause[i].pos.y + g_aPause[i].sizeY,
			0.0f
		};
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}

//************************************************
//ポーズ色変更
//************************************************
void UpdateColPause(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		//特になし
		if (i == g_nChoosePause)
		{
			g_aPause[i].col.r = 0.0f;
			g_aPause[i].col.b = 0.0f;
		}
		else
		{
			g_aPause[i].col.r = 1.0f;
			g_aPause[i].col.b = 1.0f;
		}
		
		pVtx[0].col = g_aPause[i].col;
		pVtx[1].col = g_aPause[i].col;
		pVtx[2].col = g_aPause[i].col;
		pVtx[3].col = g_aPause[i].col;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}

//************************************************
//ポーズ描画
//************************************************
void DrawPause(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TexMax; i++)
	{
		pDevice->SetTexture(0, g_pTexturePause[i]);

		//ポーズの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//構造体の情報を設定する関数
//************************************************
void SetInfoPause(void)
{
	for (int i = 0; i < TexMax; i++)
	{
		g_aPause[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPause[i].F = 1.0f;	//汎用

		if (i == TexWindow)
		{
			g_aPause[i].pos = D3DXVECTOR3((float)SCREEN_HALFWIDTH, (float)SCREEN_HALFHEIGHT, 0.0f);
			g_aPause[i].sizeX = (float)SCREEN_HALFWIDTH;
			g_aPause[i].sizeY = (float)SCREEN_HALFHEIGHT;
		}
		else if (i == TexArrow)
		{
			g_aPause[i].sizeX = 55.0f;
			g_aPause[i].sizeY = 55.0f;
		}
		else
		{
			g_aPause[i].pos = D3DXVECTOR3(850.0f, 350.0f + (i * 125.0f), 0.0f);
			g_aPause[i].sizeX = 175.0f;
			g_aPause[i].sizeY = 55.0f;
		}
	}
}

//************************************
//ポーズ選択を取得
//************************************
MODE GetInfoChoosePause(void)
{
	int nChoose = 0;

	switch (g_nChoosePause)
	{
	case TexRetry:
		nChoose = MODE_GAME;
		break;

	case TexRetire:
		nChoose = MODE_TITLE;
		break;
	}

	return (MODE)nChoose;
}