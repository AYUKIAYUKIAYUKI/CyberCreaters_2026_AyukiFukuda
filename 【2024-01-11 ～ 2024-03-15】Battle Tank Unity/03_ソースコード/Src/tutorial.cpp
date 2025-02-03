//===============================================================================
//
//  2DアクションMaster版(tutorial.cpp)
//								制作：KURAMAESATOSHI
// 
//===============================================================================
#include "tutorial.h"
#include "input.h"
#include "score.h"
#include "tutorial_ready.h"
#include "sound.h"
//グローバル変数

LPDIRECT3DTEXTURE9 g_pTextureTutorial[NUM_TUTORIAL_TEX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;

Tutorial g_Tutorial[NUM_TUTORIAL_TEX];

bool bNextFaze;
D3DXVECTOR3 moveUI;	//移動量
//初期化処理
void InitTutorial(void)
{
	PlaySound(SOUND_LABEL_TUTORIAL_BGM);
	InitReady();

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TUTORIAL_TEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTutorial, NULL);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\TUTORIAL_TEXTURE\\tutorial.png", &g_pTextureTutorial[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\TUTORIAL_TEXTURE\\tutorial1.png", &g_pTextureTutorial[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\TUTORIAL_TEXTURE\\tutorial2.png", &g_pTextureTutorial[2]);


	moveUI = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	bNextFaze = false;

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_TUTORIAL_TEX; nCnt++)
	{
		g_Tutorial[nCnt].bUse = false;
		g_Tutorial[nCnt].pos = { 0.0f, 0.0f, 0.0f };
		g_Tutorial[nCnt].bMove = false;
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

	SetTutorial(D3DXVECTOR3(960.0f, 540.0f, 0.0f));
	SetTutorial(D3DXVECTOR3(-580.0f, 540.0f, 0.0f));
	SetTutorial(D3DXVECTOR3(2480.0f, 540.0f, 0.0f));

	//頂点バッファをアンロック
	g_pVtxBuffTutorial->Unlock();


}

//終了処理
void UninitTutorial(void)
{
	StopSound();
	UninitReady();
	for (int nCnt = 0; nCnt < NUM_TUTORIAL_TEX; nCnt++)
	{
		if (g_pTextureTutorial[nCnt] != NULL)
		{
			//テクスチャの破棄
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}

	}

	//頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}

//更新処理
void UpdateTutorial(void)
{
	//動作
	if (g_Tutorial[1].bUse == true)
	{
		if (g_Tutorial[1].pos.x < UICOORD_1)
		{
			g_Tutorial[1].bMove = true;
			g_Tutorial[1].pos.x += UISPEED;
		}
		else
		{
			g_Tutorial[1].bMove = false;
		}

	}
	if (g_Tutorial[2].bUse == true)
	{
		if (g_Tutorial[2].pos.x > UICOORD_2)
		{
			g_Tutorial[2].bMove = true;
			g_Tutorial[2].pos.x -= UISPEED;
		}
		else
		{
			g_Tutorial[2].bMove = false;
		}
	}

	if (g_Tutorial[1].bMove == false && g_Tutorial[2].bMove == false)
	{
		//プレイヤーがBボタン押すと進む
		if (GetJoypadTrigger(JOYKEY_B, 0) == true||
			GetJoypadTrigger(JOYKEY_B, 1) == true|| 
			GetJoypadTrigger(JOYKEY_B, 2) == true|| 
			GetJoypadTrigger(JOYKEY_B, 3) == true)
		{
			PlaySound(SOUND_LABEL_CLICK);
			bNextFaze = true;
		}
	}
	if (bNextFaze == true)
	{
		FadeTutorial();
	}




	VERTEX_2D* pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_TUTORIAL_TEX; nCnt++)
	{
		pVtx[0].pos = D3DXVECTOR3(g_Tutorial[nCnt].pos.x - g_Tutorial[nCnt].pSize1X, g_Tutorial[nCnt].pos.y - g_Tutorial[nCnt].pSize1Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Tutorial[nCnt].pos.x + g_Tutorial[nCnt].pSizeX, g_Tutorial[nCnt].pos.y - g_Tutorial[nCnt].pSize1Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Tutorial[nCnt].pos.x - g_Tutorial[nCnt].pSize1X, g_Tutorial[nCnt].pos.y + g_Tutorial[nCnt].pSizeY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Tutorial[nCnt].pos.x + g_Tutorial[nCnt].pSizeX, g_Tutorial[nCnt].pos.y + g_Tutorial[nCnt].pSizeY, 0.0f);
		pVtx += 4;
	}


	//頂点バッファをアンロック
	g_pVtxBuffTutorial->Unlock();

	//説明文が表示されてからREADYが表示できるようにする
	if (g_Tutorial[1].bUse == false && g_Tutorial[2].bUse == false)
	{
		UpdateReady();
	}

}

//描画処理
void DrawTutorial(void)
{
	DrawReady();
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_TUTORIAL_TEX; i++)
	{
		if (g_Tutorial[i].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureTutorial[i]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
		}
	}
}

//配置
void SetTutorial(D3DXVECTOR3 pos)
{
	DeplayReady();
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_TUTORIAL_TEX; nCnt++, pVtx += 4)
	{
		if (g_Tutorial[nCnt].bUse == false)
		{
			//頂点座標の設定
			g_Tutorial[nCnt].pos = pos;

			if (nCnt == 0)
			{
				g_Tutorial[nCnt].pSize1X = UI_SIZEX1;
				g_Tutorial[nCnt].pSize1Y = UI_SIZEY1;
				g_Tutorial[nCnt].pSizeX = UI_SIZEX1;
				g_Tutorial[nCnt].pSizeY = UI_SIZEY1;
			}
			else if (nCnt == 1)
			{
				g_Tutorial[nCnt].pSize1X = UI_SIZEX2;
				g_Tutorial[nCnt].pSize1Y = UI_SIZEY2;
				g_Tutorial[nCnt].pSizeX = UI_SIZEX2;
				g_Tutorial[nCnt].pSizeY = UI_SIZEY2;
			}
			else if (nCnt == 2)
			{
				g_Tutorial[nCnt].pSize1X = UI_SIZEX2;
				g_Tutorial[nCnt].pSize1Y = UI_SIZEY2;
				g_Tutorial[nCnt].pSizeX = UI_SIZEX2;
				g_Tutorial[nCnt].pSizeY = UI_SIZEY2;
			}

			pVtx[0].pos = D3DXVECTOR3(g_Tutorial[nCnt].pos.x - g_Tutorial[nCnt].pSize1X, g_Tutorial[nCnt].pos.y - g_Tutorial[nCnt].pSize1Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Tutorial[nCnt].pos.x + g_Tutorial[nCnt].pSizeX, g_Tutorial[nCnt].pos.y - g_Tutorial[nCnt].pSize1Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Tutorial[nCnt].pos.x - g_Tutorial[nCnt].pSize1X, g_Tutorial[nCnt].pos.y + g_Tutorial[nCnt].pSizeY, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Tutorial[nCnt].pos.x + g_Tutorial[nCnt].pSizeX, g_Tutorial[nCnt].pos.y + g_Tutorial[nCnt].pSizeY, 0.0f);

			g_Tutorial[nCnt].bUse = true;
			break;
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffTutorial->Unlock();
}

//説明文退場
void FadeTutorial(void)
{
	g_Tutorial[1].bMove = true;
	g_Tutorial[2].bMove = true;

	if (g_Tutorial[1].bMove == true && g_Tutorial[2].bMove == true)
	{
		g_Tutorial[1].pos.y -= UISPEED;
		g_Tutorial[2].pos.y -= UISPEED;
	}
	if (g_Tutorial[1].pos.y == FADEUICOORD && g_Tutorial[2].pos.y == FADEUICOORD)
	{
		g_Tutorial[1].bUse = false;
		g_Tutorial[2].bUse = false;
	}
}

//UI情報
Tutorial* GetTutorial(void)
{
	return g_Tutorial;
}