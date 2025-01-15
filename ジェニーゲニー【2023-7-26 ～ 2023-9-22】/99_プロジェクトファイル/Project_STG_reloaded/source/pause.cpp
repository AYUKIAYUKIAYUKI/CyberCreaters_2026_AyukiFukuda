//************************************************
//
//ポーズ画面(荒れ地)[pause.cpp]
//Author：福田歩希
//
//************************************************
#include "input.h"
#include "sound.h"
#include "game.h"
#include "pause.h"
#include "pause_cursor.h"
#include "pause_fade.h"
#include "pause_select.h"
#include "pause_window.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Pause = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Pause = NULL;	//頂点バッファのポインタ
bool g_bPause_Return = false;

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Pause(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WHITE_PAUSE,
		&g_pTexture_Pause);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Pause,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Pause;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Pause->Lock(0, 0, (void**)&pVtx_Pause, 0);

	//頂点座標の初期設定
	pVtx_Pause[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Pause[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx_Pause[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx_Pause[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Pause[0].rhw = 1.0f;
	pVtx_Pause[1].rhw = 1.0f;
	pVtx_Pause[2].rhw = 1.0f;
	pVtx_Pause[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Pause[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx_Pause[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx_Pause[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx_Pause[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

	//テクスチャ座標の初期設定
	pVtx_Pause[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Pause[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Pause[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Pause[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Pause->Unlock();

	g_bPause_Return = false;

	//そのほかの
	Init_Pause_Cursor();
	Init_Pause_Fade();
	Init_Pause_Select();
	Init_Pause_Window();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Pause(void)
{
	//テクスチャの破棄
	if (g_pTexture_Pause != NULL)
	{
		g_pTexture_Pause->Release();
		g_pTexture_Pause = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Pause != NULL)
	{
		g_pVtxBuff_Pause->Release();
		g_pVtxBuff_Pause = NULL;
	}

	//そのほかの
	Uninit_Pause_Cursor();
	Uninit_Pause_Fade();
	Uninit_Pause_Select();
	Uninit_Pause_Window();
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Pause(void)
{
	//ポーズ判定
	bool* pStop;
	pStop = Getinfo_Pause();

	int* pChoose_Pause;
	pChoose_Pause = Getinfo_Choose_Pause();

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true &&
		!g_bPause_Return)
	{
		//効果音を鳴らす
		PlaySound(SOUND_LABEL_SE_SELECT2);

		g_bPause_Return = true;
	}

	//そのほかの
	Update_Pause_Cursor();
	Update_Pause_Fade();
	Update_Pause_Select();
	Update_Pause_Window();

	if (g_bPause_Return)
	{
		float* pFade_Menu;
		pFade_Menu = Getinfo_Pause_Fade();

		switch (*pChoose_Pause)
		{
		case 0:

			*pStop = false;	//続きから

			g_bPause_Return = false;

			Uninit_Pause_Cursor();
			Uninit_Pause_Fade();
			Uninit_Pause_Select();
			Uninit_Pause_Window();

			Init_Pause_Cursor();
			Init_Pause_Fade();
			Init_Pause_Select();
			Init_Pause_Window();

			break;

		case 1:

			if (*pFade_Menu >= 1.1f)
			{
				Setinfo_Mode(MODE_GAME);	//リトライ
			}

			break;

		case 2:

			if (*pFade_Menu >= 1.1f)
			{
				Setinfo_Mode(MODE_MENU);	//メニューに設定
			}

			break;

		case 3:

			if (*pFade_Menu >= 1.1f)
			{
				Setinfo_Mode(MODE_TITLE);	//タイトルに設定
			}

			break;
		}
	}
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Pause(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Pause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Pause);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);

	//そのほかの
	Draw_Pause_Window();
	Draw_Pause_Cursor();
	Draw_Pause_Select();
	Draw_Pause_Fade();
}

//************************************************
//メニュー決定情報を送る関数
//************************************************
bool* Getinfo_Return_Pause(void)
{
	return &g_bPause_Return;
}