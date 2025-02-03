//=====================================
//
//READYのUI表示用
//
//=====================================

#include "fade.h"
#include "main.h"
#include "input.h"
#include "tutorial_ready.h"
#include "tutorial.h"
#include "player_count.h"
#include "sound.h"
#include <assert.h>
#define NUM_READY (4)
#define MAX_COLOR (100.0f)

#define JOIN_VERIFY 4	// 人数指定

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureReady = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffReady = NULL;
float g_aPosTexReady[NUM_READY];

int NumPlayer = JOIN_VERIFY;	//プレイ人数格納
int nFadeCount;					//フェードするまでの時間
Ready g_Ready[NUM_READY];


//初期化処理
void InitReady(void)
{
#ifndef JOIN_VERIFY

	// 人数指定が無ければ固定
	g_AmountPlayer_Tuto = 1;

#endif	// JOIN_VERIFY

	//プレイ人数の取得
	NumPlayer = ReturnSelectPlayerCount() + 1;

	nFadeCount = 0;
#ifdef _DEBUG

	// 人数がおかしいと終了
	assert(NumPlayer > 0 && NumPlayer <= 4);

#endif	// _DEBUG
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_READY, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffReady, NULL);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\TUTORIAL_TEXTURE\\ready_font_3.png", &g_pTextureReady);

	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffReady->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_READY; nCnt++)
	{
		g_Ready[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ready[nCnt].bUse = true;
		g_Ready[nCnt].number = 0;

		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffReady->Unlock();

	SetFade(FADE_IN, MODE_MAX);
}

//終了処理
void UninitReady(void)
{
	//テクスチャの破棄
	if (g_pTextureReady != NULL)
	{
		g_pTextureReady->Release();
		g_pTextureReady = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffReady != NULL)
	{
		g_pVtxBuffReady->Release();
		g_pVtxBuffReady = NULL;
	}
}

//更新処理
void UpdateReady(void)
{
	//READY表示フラグ
	if (GetJoypadTrigger(JOYKEY_B, 0) == true)
	{
		PlaySound(SOUND_LABEL_CLICK);
		if (g_Ready[0].bUse == false)
		{
			g_Ready[0].bUse = true;
		}
	}
	else if (GetJoypadTrigger(JOYKEY_B, 1) == true)
	{
		PlaySound(SOUND_LABEL_CLICK);
		if (g_Ready[1].bUse == false)
		{
			g_Ready[1].bUse = true;
		}
	}
	else if (GetJoypadTrigger(JOYKEY_B, 2) == true)
	{
		PlaySound(SOUND_LABEL_CLICK);
		if (g_Ready[2].bUse == false)
		{
			g_Ready[2].bUse = true;
		}
	}
	else if (GetJoypadTrigger(JOYKEY_B, 3) == true)
	{
		PlaySound(SOUND_LABEL_CLICK);
		if (g_Ready[3].bUse == false)
		{
			g_Ready[3].bUse = true;
		}
	}


	//画面移行フラグ(フェード処理が入ります)
	if (NumPlayer == 1)
	{
		if (g_Ready[0].bUse == true)
		{
			nFadeCount++;
			if (nFadeCount == FADETOGAME)
			{
				SetFade(FADE_OUT,MODE_GAME);
				nFadeCount = 0;
			}

		}
	}
	else if (NumPlayer == 2)
	{
		if (g_Ready[0].bUse == true &&
			g_Ready[1].bUse == true)
		{
			nFadeCount++;
			if (nFadeCount == FADETOGAME)
			{
				SetFade(FADE_OUT, MODE_GAME);
				nFadeCount = 0;
			}
		}
	}
	else if (NumPlayer == 3)
	{
		if (g_Ready[0].bUse == true &&
			g_Ready[1].bUse == true &&
			g_Ready[2].bUse == true)
		{
			nFadeCount++;
			if (nFadeCount == FADETOGAME)
			{
				SetFade(FADE_OUT, MODE_GAME);
				nFadeCount = 0;
			}
		}
	}
	else if (NumPlayer == 4)
	{
		if (g_Ready[0].bUse == true &&
			g_Ready[1].bUse == true &&
			g_Ready[2].bUse == true &&
			g_Ready[3].bUse == true)
		{
			nFadeCount++;
			if (nFadeCount == FADETOGAME)
			{
				SetFade(FADE_OUT, MODE_GAME);
				nFadeCount = 0;
			}
		}
	}
}

//描画処理
void DrawReady(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffReady, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < NUM_READY; nCnt++)
	{
		if (g_Ready[nCnt].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureReady);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}

//Readyの配置
void SetReady(D3DXVECTOR3 pos, int nNumber)
{
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点座標へのポインタを取得
	g_pVtxBuffReady->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_READY; nCnt++)
	{
		if (g_Ready[nCnt].bUse == true)
		{
			g_Ready[nCnt].pos = pos;
			g_Ready[nCnt].number = nNumber;

			pVtx[0].pos = D3DXVECTOR3(g_Ready[nCnt].pos.x - 200.0f, g_Ready[nCnt].pos.y - 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Ready[nCnt].pos.x + 200.0f, g_Ready[nCnt].pos.y - 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Ready[nCnt].pos.x - 200.0f, g_Ready[nCnt].pos.y + 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Ready[nCnt].pos.x + 200.0f, g_Ready[nCnt].pos.y + 100.0f, 0.0f);

			g_Ready[nCnt].bUse = false;
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffReady->Unlock();
}

//READYの設置処理
void DeplayReady(void)
{
	//プレイヤーの人数ごとにREADYの配置を変える処理
	if (NumPlayer == 1)
	{
		SetReady(D3DXVECTOR3(960.0f, 800.0f, 0.0f), 0);
	}
	else if (NumPlayer == 2)
	{
		SetReady(D3DXVECTOR3(480.0f, 800.0f, 0.0f), 0);
		SetReady(D3DXVECTOR3(1440.0f, 800.0f, 0.0f), 1);
	}
	else if (NumPlayer == 3)
	{
		SetReady(D3DXVECTOR3(480.0f, 300.0f, 0.0f), 0);
		SetReady(D3DXVECTOR3(1440.0f, 300.0f, 0.0f), 1);
		SetReady(D3DXVECTOR3(480.0f, 800.0f, 0.0f), 2);
	}
	else if (NumPlayer == 4)
	{
		SetReady(D3DXVECTOR3(480.0f, 300.0f, 0.0f), 0);
		SetReady(D3DXVECTOR3(1440.0f, 300.0f, 0.0f), 1);
		SetReady(D3DXVECTOR3(480.0f, 810.0f, 0.0f), 2);
		SetReady(D3DXVECTOR3(1440.0f, 810.0f, 0.0f), 3);
	}

}