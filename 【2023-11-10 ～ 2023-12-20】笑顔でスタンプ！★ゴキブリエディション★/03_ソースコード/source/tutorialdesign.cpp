//************************************************
//
//チュートリアルデザイン[tutorialdesign.cpp]
//Author：福田歩希
//
//************************************************
#include "tutorialdesign.h"

#include "fade.h"
#include "input.h"
#include "sound.h"

#include "player.h"

//チュートリアルデザイン用
typedef enum
{
	Tex0 = 0,
	Tex1,
	Tex2,
	Tex3,
	Tex4,
	TexMax
}TexType;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTutorialDesign[TexMax] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialDesign = NULL;	//頂点バッファのポインタ
TutorialDesign g_aTutorialDesign[TexMax];	//情報
int g_nScenario = 0;	//チュートリアルの進度
int g_nChangeCT = 0;	//進度変更時の変遷に少し遅延
bool g_bSpawn = false;	//湧くかどうか
bool g_bStamp = false;	//殺判定

//************************************************
//チュートリアルデザイン初期
//************************************************
void InitTutorialDesign(void)
{
	//構造体の情報の初期化群
	for (int i = 0; i < TexMax; i++)
	{
		g_aTutorialDesign[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorialDesign[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorialDesign[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorialDesign[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aTutorialDesign[i].sizeX = 0.0f;
		g_aTutorialDesign[i].sizeY = 0.0f;
		g_aTutorialDesign[i].F = 1.0f;	//汎用
	}

	//進度
	g_nScenario = Tex0;

	//遅延
	g_nChangeCT = 0;

	g_bSpawn = false;
	g_bStamp = false;

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	const char* pFileName[TexMax] =
	{
		"data\\texture\\tutorial00.png",
		"data\\texture\\tutorial01.png",
		"data\\texture\\tutorial02.png",
		"data\\texture\\tutorial03.png",
		"data\\texture\\tutorial04.png",
	};

	for (int i = 0; i < TexMax; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureTutorialDesign[i]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * TexMax,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialDesign,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffTutorialDesign->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTutorialDesign->Unlock();

	//情報を付与
	SetInfoTutorialDesign();

	//展開
	SetSizeTutorialDesign();
}

//************************************************
//チュートリアルデザイン終了処理関数
//************************************************
void UninitTutorialDesign(void)
{
	//テクスチャの破棄
	for (int i = 0; i < TexMax; i++)
	{
		if (g_pTextureTutorialDesign[i] != NULL)
		{
			g_pTextureTutorialDesign[i]->Release();
			g_pTextureTutorialDesign[i] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTutorialDesign != NULL)
	{
		g_pVtxBuffTutorialDesign->Release();
		g_pVtxBuffTutorialDesign = NULL;
	}
}

//************************************************
//チュートリアルデザイン更新
//************************************************
void UpdateTutorialDesign(void)
{
	//フェード情報用
	FADE* pFade = GetInfoFade();

	//Player* pPlayer = GetInfoPlayer();

	if (g_nChangeCT > 0)
	{
		g_nChangeCT--;

		if (g_nChangeCT <= 0)
		{
			g_nScenario++;
		}
	}

	//展開
	SetSizeTutorialDesign();

	//色変更
	//UpdateColTutorialDesign();

	if (g_nChangeCT <= 0)
	{
		switch (g_nScenario)
		{
		case Tex0:
			//if (pPlayer->pos != pPlayer->posOld)
			if (GetKeyboardTrigger(DIK_W) || GetKeyboardTrigger(DIK_A) || GetKeyboardTrigger(DIK_S) || GetKeyboardTrigger(DIK_D) || GetJoyStickL())
			{
				g_nChangeCT += 40;
			}
			break;
		case Tex1:
			if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_LEFT) || GetKeyboardTrigger(DIK_RIGHT) || GetKeyboardTrigger(DIK_DOWN) || GetJoyStickR())
			{
				g_nChangeCT += 40;
				g_bSpawn = true;
			}
			break;
		case Tex2:
			if (GetKeyboardTrigger(DIK_SPACE) || GetTriggerTriggerButtonR())
			{
				g_nChangeCT += 40;
				g_bStamp = false;
			}
			break;
		case Tex3:
			if (g_bStamp && g_nChangeCT <= 0)
			{
				g_nChangeCT += 40;
			}
			break;
		case Tex4:
			if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_START))
			{
				//フェードアウト開始
				pFade->bFadeIn = false;
				pFade->bFadeOut = true;

				PlaySound(SOUND_LABEL_DEFINE);
			}
		}
	}
}

//************************************************
//チュートリアルデザイン展開
//************************************************
void SetSizeTutorialDesign(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffTutorialDesign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		if (g_nScenario == i)
		{
			//頂点座標の設定
			pVtx[0].pos =
			{
				g_aTutorialDesign[i].pos.x - g_aTutorialDesign[i].sizeX,
				g_aTutorialDesign[i].pos.y - g_aTutorialDesign[i].sizeY,
				0.0f
			};

			pVtx[1].pos =
			{
				g_aTutorialDesign[i].pos.x + g_aTutorialDesign[i].sizeX,
				g_aTutorialDesign[i].pos.y - g_aTutorialDesign[i].sizeY,
				0.0f
			};

			pVtx[2].pos =
			{
				g_aTutorialDesign[i].pos.x - g_aTutorialDesign[i].sizeX,
				g_aTutorialDesign[i].pos.y + g_aTutorialDesign[i].sizeY,
				0.0f
			};

			pVtx[3].pos =
			{
				g_aTutorialDesign[i].pos.x + g_aTutorialDesign[i].sizeX,
				g_aTutorialDesign[i].pos.y + g_aTutorialDesign[i].sizeY,
				0.0f
			};
		}
		else
		{
			pVtx[0].pos = {};
			pVtx[1].pos = {};
			pVtx[2].pos = {};
			pVtx[3].pos = {};
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTutorialDesign->Unlock();
}

//************************************************
//チュートリアルデザイン色変更
//************************************************
void UpdateColTutorialDesign(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffTutorialDesign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		//特になし
		pVtx[0].col = g_aTutorialDesign[i].col;
		pVtx[1].col = g_aTutorialDesign[i].col;
		pVtx[2].col = g_aTutorialDesign[i].col;
		pVtx[3].col = g_aTutorialDesign[i].col;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTutorialDesign->Unlock();
}

//************************************************
//チュートリアルデザイン描画
//************************************************
void DrawTutorialDesign(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialDesign, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TexMax; i++)
	{
		pDevice->SetTexture(0, g_pTextureTutorialDesign[i]);

		//チュートリアルデザインの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//構造体の情報を設定する関数
//************************************************
void SetInfoTutorialDesign(void)
{
	for (int i = 0; i < TexMax; i++)
	{
		g_aTutorialDesign[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorialDesign[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorialDesign[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTutorialDesign[i].F = 1.0f;	//汎用

		g_aTutorialDesign[i].pos = D3DXVECTOR3((float)SCREEN_HALFWIDTH, (float)SCREEN_HALFHEIGHT, 0.0f);
		g_aTutorialDesign[i].sizeX = (float)SCREEN_HALFWIDTH;
		g_aTutorialDesign[i].sizeY = (float)SCREEN_HALFHEIGHT;
	}
}

//************************************************
//敵がわくかどうか判定
//************************************************
bool* GetInfoSpawnEnemy(void)
{
	return &g_bSpawn;
}

//************************************************
//敵をつぶしたか判定
//************************************************
bool* GetInfoStampEnemy(void)
{
	return &g_bStamp;
}