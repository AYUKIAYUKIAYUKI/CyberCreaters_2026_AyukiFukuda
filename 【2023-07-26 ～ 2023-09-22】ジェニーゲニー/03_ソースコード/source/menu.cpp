//************************************************
//
//メニュー表示処理[menu.cpp]
//Author：福田歩希
//
//************************************************
#include "input.h"
#include "sound.h"
#include "menu.h"
#include "cursorh.h"
#include "fade.h"
#include "select_mode.h"
#include "square.h"
#include "text_mode.h"
#include "tutorial_cursor.h"
#include "tutorial_select.h"
#include "tutorial_window.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Menu[AMOUNT_TEXTURE_MENU] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Menu = NULL;	//頂点バッファのポインタ
MENU_OBJECT g_aMenu[AMOUNT_POLYGON_MENU];	//メニュー用ポリゴンの情報を格納
bool g_bPopup = false;
bool g_bStart = false;

//************************************************
//初期化処理関数
//************************************************
void Init_Menu(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WHITE_MENU,
		&g_pTexture_Menu[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_MENU,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Menu,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Menu;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Menu->Lock(0, 0, (void**)&pVtx_Menu, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_MENU; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Menu[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Menu[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Menu[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Menu[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Menu[0].rhw = 1.0f;
		pVtx_Menu[1].rhw = 1.0f;
		pVtx_Menu[2].rhw = 1.0f;
		pVtx_Menu[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Menu[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Menu[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Menu[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Menu[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Menu[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Menu[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Menu[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Menu[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Menu += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Menu->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_MENU; nCnt++)
	{
		g_aMenu[nCnt].nStyle = 0;
		g_aMenu[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMenu[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMenu[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMenu[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aMenu[nCnt].fLength = 0.0f;
		g_aMenu[nCnt].fAngle = 0.0f;
	}

	//初回のみ頂点を展開
	Setinfo_Menu();

	//そのほかの
	Init_Cursor();
	Init_Fade_Menu();
	Init_Select_Mode();
	Init_Square();
	Init_Text_Mode();
	Init_Tutorial_Cursor();
	Init_Tutorial_Select();
	Init_Tutorial_Window();

	g_bPopup = false;
	g_bStart = false;
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Menu(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_MENU; nCnt++)
	{
		if (g_pTexture_Menu[nCnt] != NULL)
		{
			g_pTexture_Menu[nCnt]->Release();
			g_pTexture_Menu[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Menu != NULL)
	{
		g_pVtxBuff_Menu->Release();
		g_pVtxBuff_Menu = NULL;
	}

	//そのほかの
	Uninit_Cursor();
	Uninit_Fade_Menu();
	Uninit_Select_Mode();
	Uninit_Square();
	Uninit_Text_Mode();
	Uninit_Tutorial_Cursor();
	Uninit_Tutorial_Select();
	Uninit_Tutorial_Window();
}

//************************************************
//更新処理関数
//************************************************
void Update_Menu(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Menu;

	//選んでるものへのポインタ
	int* pChoose;
	pChoose = Getinfo_Choose();
	int* pChoose_YesNo;
	pChoose_YesNo = Getinfo_Choose_YesNo();

	float* pFade;
	pFade = Getinfo_Fade_Menu();

	if (!g_bPopup)
	{
		//頂点バッファをロックして頂点情報のポインタを取得
		g_pVtxBuff_Menu->Lock(0, 0, (void**)&pVtx_Menu, 0);

		for (int nCnt = 0; nCnt < AMOUNT_POLYGON_MENU; nCnt++)
		{
			//移動、回転を反映
			pVtx_Menu[0].pos.x = g_aMenu[nCnt].pos.x + sinf(g_aMenu[nCnt].rot.z - (D3DX_PI - g_aMenu[nCnt].fAngle)) * g_aMenu[nCnt].fLength;
			pVtx_Menu[0].pos.y = g_aMenu[nCnt].pos.y + cosf(g_aMenu[nCnt].rot.z - (D3DX_PI - g_aMenu[nCnt].fAngle)) * g_aMenu[nCnt].fLength;
			pVtx_Menu[1].pos.x = g_aMenu[nCnt].pos.x + sinf(g_aMenu[nCnt].rot.z + (D3DX_PI - g_aMenu[nCnt].fAngle)) * g_aMenu[nCnt].fLength;
			pVtx_Menu[1].pos.y = g_aMenu[nCnt].pos.y + cosf(g_aMenu[nCnt].rot.z + (D3DX_PI - g_aMenu[nCnt].fAngle)) * g_aMenu[nCnt].fLength;
			pVtx_Menu[2].pos.x = g_aMenu[nCnt].pos.x + sinf(g_aMenu[nCnt].rot.z - g_aMenu[nCnt].fAngle) * g_aMenu[nCnt].fLength;
			pVtx_Menu[2].pos.y = g_aMenu[nCnt].pos.y + cosf(g_aMenu[nCnt].rot.z - g_aMenu[nCnt].fAngle) * g_aMenu[nCnt].fLength;
			pVtx_Menu[3].pos.x = g_aMenu[nCnt].pos.x + sinf(g_aMenu[nCnt].rot.z + g_aMenu[nCnt].fAngle) * g_aMenu[nCnt].fLength;
			pVtx_Menu[3].pos.y = g_aMenu[nCnt].pos.y + cosf(g_aMenu[nCnt].rot.z + g_aMenu[nCnt].fAngle) * g_aMenu[nCnt].fLength;

			//選んでるものに応じて背景色変更
			if (*pChoose == 0)
			{
				//g_aMenu[nCnt].col = D3DXCOLOR(1.0f, 0.85f, 0.5f, 1.0f);

				if (g_aMenu[nCnt].col.r < 1.0f)
				{
					g_aMenu[nCnt].col.r += 0.025f;
				}

				if (g_aMenu[nCnt].col.g < 1.0f)
				{
					g_aMenu[nCnt].col.g += 0.025f;
				}

				if (g_aMenu[nCnt].col.b > 0.5f)
				{
					g_aMenu[nCnt].col.b -= 0.025f;
				}
			}
			else
			{
				//g_aMenu[nCnt].col = D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f);

				if (g_aMenu[nCnt].col.r > 0.7f)
				{
					g_aMenu[nCnt].col.r -= 0.025f;
				}

				if (g_aMenu[nCnt].col.g > 0.7f)
				{
					g_aMenu[nCnt].col.g -= 0.025f;
				}

				if (g_aMenu[nCnt].col.b < 1.0f)
				{
					g_aMenu[nCnt].col.b += 0.025f;
				}
			}

			pVtx_Menu[2].col = g_aMenu[nCnt].col;
			pVtx_Menu[3].col = g_aMenu[nCnt].col;

			pVtx_Menu += AMOUNT_VTX;
		}

		//頂点バッファをアンロックする
		g_pVtxBuff_Menu->Unlock();

		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true
			|| GetJoypadTrigger(JOYKEY_A) == true && g_bPopup == false && g_bStart == false)
		{
			//効果音を鳴らす
			PlaySound(SOUND_LABEL_SE_SELECT2);

			if (*pChoose == 0)
			{
				g_bPopup = true;
			}
			else
			{
				g_bStart = true;
			}
		}
	}
	else if (g_bPopup && !g_bStart)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true
			|| GetJoypadTrigger(JOYKEY_A) == true && g_bPopup == true && g_bStart == false)
		{
			//効果音を鳴らす
			PlaySound(SOUND_LABEL_SE_SELECT2);

			g_bStart = true;
		}

		Update_Tutorial_Cursor();
		Update_Tutorial_Select();
		Update_Tutorial_Window();
	}

	if (g_bPopup && g_bStart)
	{
		Update_Tutorial_Cursor();
		Update_Tutorial_Select();
		Update_Tutorial_Window();
	}

	//そのほかの
	Update_Cursor();
	Update_Fade_Menu();
	Update_Select_Mode();
	Update_Square();
	Update_Text_Mode();

	if (g_bStart)
	{
		if (*pFade > 1.1f)
		{
			if (*pChoose == 0)
			{
				if (*pChoose_YesNo == 0)
				{
					Setinfo_Mode(MODE_TUTORIAL);	//チュートリアルモードへ
				}
				else
				{
					Setinfo_Mode(MODE_GAME);	//ゲームモードへ
				}
			}
			else
			{
				Setinfo_Mode(MODE_RANKING);	//ランキングモードへ
			}
		}
	}
}

//************************************************
//描画処理関数
//************************************************
void Draw_Menu(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Menu, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_MENU; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Menu[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//そのほかの(レイヤー遵守)
	Draw_Square();
	Draw_Cursor();
	Draw_Select_Mode();
	Draw_Text_Mode();

	Draw_Tutorial_Window();
	Draw_Tutorial_Cursor();
	Draw_Tutorial_Select();

	Draw_Fade_Menu();
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Menu(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_MENU; nCnt++)
	{
		g_aMenu[nCnt].nStyle = 0;
		g_aMenu[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
		g_aMenu[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMenu[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aMenu[nCnt].fLength = sqrtf((990.0f * 990.0f) + (540.0f * 540.0f));
		g_aMenu[nCnt].fAngle = atan2f(990.0f * 2.0f, 540.0f * 2.0f);
	}
}

//************************************************
//チュートリアル情報を送る関数
//************************************************
bool* Getinfo_Tutorial_Menu(void)
{
	return &g_bPopup;
}

//************************************************
//開始情報を送る関数
//************************************************
bool* Getinfo_Menu(void)
{
	return &g_bStart;
}