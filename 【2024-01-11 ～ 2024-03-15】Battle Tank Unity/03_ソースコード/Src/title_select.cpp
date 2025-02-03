//===============================================================================
//
//  タイトル画面選択処理(title_select.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "title.h"
#include "title_select.h"
#include "title_anim.h"
#include "player_count.h"
#include "input.h"
#include "game.h"
#include "sound.h"

#define DEFTITLE_SELECT	(10)
#define TITLE_SELECT_COUNT	(5)
#define TITLE_SELECT_FLASH	(5)

#define TITLE_ANY_HEIGHT			(150)
#define TITLE_START_WIDTH			(300)
#define TITLE_TUTORIAL_WIDTH		(600)
#define TITLE_FINISH_WIDTH			(300)
#define TITLE_ZOOM_SIZE				(25)

//テクスチャ列挙
static const char* TitleSelectName[DEFTITLE_SELECT]
{
	"data\\TEXTURE\\Title\\start0.png",			//スタート選択
	"data\\TEXTURE\\Title\\tutorial0.png",		//チュートリアル選択
	"data\\TEXTURE\\Title\\ranking0.png",		//チュートリアル選択
	"data\\TEXTURE\\Title\\finish0.png",		//終了選択
	"data\\TEXTURE\\Title\\start1.png",			//スタート非選択
	"data\\TEXTURE\\Title\\tutorial1.png",		//チュートリアル非選択
	"data\\TEXTURE\\Title\\ranking1.png",		//チュートリアル選択
	"data\\TEXTURE\\Title\\finish1.png",		//終了非選択
	"data\\TEXTURE\\Title\\finishselect0.png",		//終了選択肢(はい)
	"data\\TEXTURE\\Title\\finishselect1.png",		//終了選択肢(いいえ)
};
//選択肢の列挙
enum
{//何が選択されてるかな？
	SELECTED_START = 0,
	SELECTED_TUTORIAL,
	SELECTED_RANKING,
	SELECTED_FINISH
};
//選択肢の構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fAngle;
	float fLength;
	int Type;
}TITLEINFO;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitleSelect[DEFTITLE_SELECT] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleSelect = NULL;
int nSelectTitle;
int nSelectFinish;
int nSelectAlpha;
float nZoomTitle;
bool bSelectMode;
bool bSelectFinish;
bool bSwitchSelAlpha;
TITLEINFO TitleInfo[TITLE_SELECT_COUNT];
//===============================================================================
//タイトル選択の初期化処理
//===============================================================================
void InitTitleSelect(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	for (int i = 0; i < DEFTITLE_SELECT; i++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			TitleSelectName[i],
			&g_pTextureTitleSelect[i]);
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLE_SELECT_COUNT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleSelect,
		NULL);
	for (int i = 0; i < TITLE_SELECT_COUNT; i++)
	{
		TitleInfo[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		switch (i)
		{
		case SELECTED_START:		//選択：スタート
			TitleInfo[i].fAngle = atan2f(TITLE_START_WIDTH, TITLE_ANY_HEIGHT);
			TitleInfo[i].fLength = sqrtf(TITLE_START_WIDTH * TITLE_START_WIDTH + TITLE_ANY_HEIGHT * TITLE_ANY_HEIGHT) / 2.0f;
			TitleInfo[i].Type = SELECT_TITLE_START_ON;
			TitleInfo[i].pos = D3DXVECTOR3(450, 350, 0);
			break;
		case SELECTED_TUTORIAL:		//選択：チュートリアル
			TitleInfo[i].fAngle = atan2f(TITLE_TUTORIAL_WIDTH, TITLE_ANY_HEIGHT);
			TitleInfo[i].fLength = sqrtf(TITLE_TUTORIAL_WIDTH * TITLE_TUTORIAL_WIDTH + TITLE_ANY_HEIGHT * TITLE_ANY_HEIGHT) / 2.0f;
			TitleInfo[i].Type = SELECT_TITLE_TUTORIAL_OFF;
			TitleInfo[i].pos = D3DXVECTOR3(450, 500, 0);
			break;
		case SELECTED_RANKING:		//選択：ランキング
			TitleInfo[i].fAngle = atan2f(TITLE_TUTORIAL_WIDTH, TITLE_ANY_HEIGHT);
			TitleInfo[i].fLength = sqrtf(TITLE_TUTORIAL_WIDTH * TITLE_TUTORIAL_WIDTH + TITLE_ANY_HEIGHT * TITLE_ANY_HEIGHT) / 2.0f;
			TitleInfo[i].Type = SELECT_TITLE_RANKING_OFF;
			TitleInfo[i].pos = D3DXVECTOR3(450, 650, 0);
			break;
		case SELECTED_FINISH:		//選択：選択
			TitleInfo[i].fAngle = atan2f(TITLE_FINISH_WIDTH, TITLE_ANY_HEIGHT);
			TitleInfo[i].fLength = sqrtf(TITLE_FINISH_WIDTH * TITLE_FINISH_WIDTH + TITLE_ANY_HEIGHT * TITLE_ANY_HEIGHT) / 2.0f;
			TitleInfo[i].Type = SELECT_TITLE_FINISH_OFF;
			TitleInfo[i].pos = D3DXVECTOR3(450, 800, 0);
			break;
		case 4:
			TitleInfo[i].fAngle = atan2f(SCREEN_WIDTH, SCREEN_HEIGHT);
			TitleInfo[i].fLength = sqrtf(SCREEN_WIDTH * SCREEN_WIDTH + SCREEN_HEIGHT * SCREEN_HEIGHT) / 2.0f;
			TitleInfo[i].Type = 8;
			TitleInfo[i].pos = D3DXVECTOR3((SCREEN_WIDTH * 1.25f), (SCREEN_HEIGHT / 2), 0);
		}
	}
	VERTEX_2D* pVtx;	//頂点情報のポインタ

	//頂点バッファをロックして、頂点情報へのポインタを取得
	g_pVtxBuffTitleSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < TITLE_SELECT_COUNT; nCnt++)
	{

		//頂点座標の設定
		pVtx[0].pos.x = TitleInfo[nCnt].pos.x + sinf(TitleInfo[nCnt].rot.z - (D3DX_PI - TitleInfo[nCnt].fAngle)) * TitleInfo[nCnt].fLength;
		pVtx[0].pos.y = TitleInfo[nCnt].pos.y + cosf(TitleInfo[nCnt].rot.z - (D3DX_PI - TitleInfo[nCnt].fAngle)) * TitleInfo[nCnt].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = TitleInfo[nCnt].pos.x + sinf(TitleInfo[nCnt].rot.z + (D3DX_PI - TitleInfo[nCnt].fAngle)) * TitleInfo[nCnt].fLength;
		pVtx[1].pos.y = TitleInfo[nCnt].pos.y + cosf(TitleInfo[nCnt].rot.z + (D3DX_PI - TitleInfo[nCnt].fAngle)) * TitleInfo[nCnt].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = TitleInfo[nCnt].pos.x + sinf(TitleInfo[nCnt].rot.z - TitleInfo[nCnt].fAngle) * TitleInfo[nCnt].fLength;
		pVtx[2].pos.y = TitleInfo[nCnt].pos.y + cosf(TitleInfo[nCnt].rot.z - TitleInfo[nCnt].fAngle) * TitleInfo[nCnt].fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = TitleInfo[nCnt].pos.x + sinf(TitleInfo[nCnt].rot.z + TitleInfo[nCnt].fAngle) * TitleInfo[nCnt].fLength;
		pVtx[3].pos.y = TitleInfo[nCnt].pos.y + cosf(TitleInfo[nCnt].rot.z + TitleInfo[nCnt].fAngle) * TitleInfo[nCnt].fLength;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffTitleSelect->Unlock();
	nSelectTitle = 0;
	nSelectFinish = 0;
	nZoomTitle = 0;
	nSelectAlpha = 255;		//透明度管理
	bSelectMode = false;
	bSelectFinish = false;
	bSwitchSelAlpha = false;
}

//===============================================================================
//タイトル選択終了処理
//===============================================================================
void UninitTitleSelect(void)
{
	for (int nCnt = 0; nCnt < DEFTITLE_SELECT; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureTitleSelect[nCnt] != NULL)
		{
			g_pTextureTitleSelect[nCnt]->Release();
			g_pTextureTitleSelect[nCnt] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitleSelect != NULL)
	{
		g_pVtxBuffTitleSelect->Release();
		g_pVtxBuffTitleSelect = NULL;
	}
}

//===============================================================================
//タイトル選択更新処理
//===============================================================================
void UpdateTitleSelect(void)
{
	VERTEX_2D* pVtx;	//頂点情報のポインタ

	//頂点バッファをロックして、頂点情報へのポインタを取得
	g_pVtxBuffTitleSelect->Lock(0, 0, (void**)&pVtx, 0);
	if (ReturnTitleAnimFinish() == true)
	{
		if (bSelectMode == false)
		{
			if (bSelectFinish == false)
			{
				if (TitleInfo[4].pos.x < (SCREEN_WIDTH * 1.25))
				{
					TitleInfo[4].pos.x += SCREEN_WIDTH * 0.035f;
				}
				if (GetJoypadTrigger(JOYKEY_UP, 0) == true
					|| GetKeyboardTrigger(DIK_UPARROW) == true)
				{
					PlaySound(SOUND_LABEL_CURSORMOVE);

					if (nSelectTitle == SELECTED_START)
					{
						nSelectTitle = SELECTED_FINISH;
					}
					else
					{
						nSelectTitle--;
					}
					nZoomTitle = 0;
				}
				else if (GetJoypadTrigger(JOYKEY_DOWN, 0) == true
					|| GetKeyboardTrigger(DIK_DOWNARROW) == true)
				{
					PlaySound(SOUND_LABEL_CURSORMOVE);

					if (nSelectTitle == SELECTED_FINISH)
					{
						nSelectTitle = SELECTED_START;
					}
					else
					{
						nSelectTitle++;
					}
					nZoomTitle = 0;
				}
				switch (nSelectTitle)
				{
				case SELECTED_START:		//選択：スタート
					TitleInfo[0].Type = SELECT_TITLE_START_ON;
					TitleInfo[1].Type = SELECT_TITLE_TUTORIAL_OFF;
					TitleInfo[2].Type = SELECT_TITLE_RANKING_OFF;
					TitleInfo[3].Type = SELECT_TITLE_FINISH_OFF;
					break;
				case SELECTED_TUTORIAL:		//選択：チュートリアル
					TitleInfo[0].Type = SELECT_TITLE_START_OFF;
					TitleInfo[1].Type = SELECT_TITLE_TUTORIAL_ON;
					TitleInfo[2].Type = SELECT_TITLE_RANKING_OFF;
					TitleInfo[3].Type = SELECT_TITLE_FINISH_OFF;
					break;
				case SELECTED_RANKING:		//選択：ランキング
					TitleInfo[0].Type = SELECT_TITLE_START_OFF;
					TitleInfo[1].Type = SELECT_TITLE_TUTORIAL_OFF;
					TitleInfo[2].Type = SELECT_TITLE_RANKING_ON;
					TitleInfo[3].Type = SELECT_TITLE_FINISH_OFF;
					break;
				case SELECTED_FINISH:		//選択：終了
					TitleInfo[0].Type = SELECT_TITLE_START_OFF;
					TitleInfo[1].Type = SELECT_TITLE_TUTORIAL_OFF;
					TitleInfo[2].Type = SELECT_TITLE_RANKING_OFF;
					TitleInfo[3].Type = SELECT_TITLE_FINISH_ON;
					break;
				}
			}
			else
			{
				if (TitleInfo[4].pos.x > (SCREEN_WIDTH * 0.5f))
				{
					TitleInfo[4].pos.x -= SCREEN_WIDTH * 0.035f;
				}
				if (GetJoypadTrigger(JOYKEY_UP, 0) == true
					|| GetJoypadTrigger(JOYKEY_DOWN, 0) == true
					|| GetKeyboardTrigger(DIK_UPARROW) == true
					|| GetKeyboardTrigger(DIK_DOWNARROW) == true)
				{
					PlaySound(SOUND_LABEL_CURSORMOVE);
					if (nSelectFinish == 0)
					{
						nSelectFinish = 1;
					}
					else
					{
						nSelectFinish = 0;
					}
				}
				if (nSelectFinish == 0)
				{
					TitleInfo[4].Type = 8;
				}
				else
				{
					TitleInfo[4].Type = 9;
				}
				if (GetJoypadTrigger(JOYKEY_A, 0) == true
					|| GetKeyboardTrigger(DIK_RETURN) == true)
				{
					PlaySound(SOUND_LABEL_CURSORMOVE);
					if (nSelectFinish == 0)
					{
						SetExitGame();
					}
					else
					{
						bSelectFinish = false;
						return;
					}
				}
			}
		}
		if (nZoomTitle < TITLE_ZOOM_SIZE)//ズーム処理
		{
			nZoomTitle += TITLE_ZOOM_SIZE * 0.1f;
		}
		if (nSelectAlpha >= 255 || nSelectAlpha <= 105)
		{
			bSwitchSelAlpha = bSwitchSelAlpha ? false : true;
		}

		if (bSwitchSelAlpha == false)
		{
			nSelectAlpha += TITLE_SELECT_FLASH;
		}
		else
		{
			nSelectAlpha -= TITLE_SELECT_FLASH;
		}

		for (int nCnt = 0; nCnt < TITLE_SELECT_COUNT; nCnt++)
		{

			if (TitleInfo[nCnt].Type == nCnt)
			{//選択されているものを拡大表示
				//頂点座標の設定
				pVtx[0].pos.x = TitleInfo[nCnt].pos.x + sinf(TitleInfo[nCnt].rot.z - (D3DX_PI - TitleInfo[nCnt].fAngle)) * TitleInfo[nCnt].fLength - nZoomTitle;
				pVtx[0].pos.y = TitleInfo[nCnt].pos.y + cosf(TitleInfo[nCnt].rot.z - (D3DX_PI - TitleInfo[nCnt].fAngle)) * TitleInfo[nCnt].fLength - nZoomTitle;
				pVtx[0].pos.z = 0.0f;
				pVtx[1].pos.x = TitleInfo[nCnt].pos.x + sinf(TitleInfo[nCnt].rot.z + (D3DX_PI - TitleInfo[nCnt].fAngle)) * TitleInfo[nCnt].fLength + nZoomTitle;
				pVtx[1].pos.y = TitleInfo[nCnt].pos.y + cosf(TitleInfo[nCnt].rot.z + (D3DX_PI - TitleInfo[nCnt].fAngle)) * TitleInfo[nCnt].fLength - nZoomTitle;
				pVtx[1].pos.z = 0.0f;
				pVtx[2].pos.x = TitleInfo[nCnt].pos.x + sinf(TitleInfo[nCnt].rot.z - TitleInfo[nCnt].fAngle) * TitleInfo[nCnt].fLength - nZoomTitle;
				pVtx[2].pos.y = TitleInfo[nCnt].pos.y + cosf(TitleInfo[nCnt].rot.z - TitleInfo[nCnt].fAngle) * TitleInfo[nCnt].fLength + nZoomTitle;
				pVtx[2].pos.z = 0.0f;
				pVtx[3].pos.x = TitleInfo[nCnt].pos.x + sinf(TitleInfo[nCnt].rot.z + TitleInfo[nCnt].fAngle) * TitleInfo[nCnt].fLength + nZoomTitle;
				pVtx[3].pos.y = TitleInfo[nCnt].pos.y + cosf(TitleInfo[nCnt].rot.z + TitleInfo[nCnt].fAngle) * TitleInfo[nCnt].fLength + nZoomTitle;
				pVtx[3].pos.z = 0.0f;

				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, nSelectAlpha);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, nSelectAlpha);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, nSelectAlpha);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, nSelectAlpha);
			}
			else
			{//非選択を縮小
				//頂点座標の設定
				pVtx[0].pos.x = TitleInfo[nCnt].pos.x + sinf(TitleInfo[nCnt].rot.z - (D3DX_PI - TitleInfo[nCnt].fAngle)) * TitleInfo[nCnt].fLength;
				pVtx[0].pos.y = TitleInfo[nCnt].pos.y + cosf(TitleInfo[nCnt].rot.z - (D3DX_PI - TitleInfo[nCnt].fAngle)) * TitleInfo[nCnt].fLength;
				pVtx[0].pos.z = 0.0f;
				pVtx[1].pos.x = TitleInfo[nCnt].pos.x + sinf(TitleInfo[nCnt].rot.z + (D3DX_PI - TitleInfo[nCnt].fAngle)) * TitleInfo[nCnt].fLength;
				pVtx[1].pos.y = TitleInfo[nCnt].pos.y + cosf(TitleInfo[nCnt].rot.z + (D3DX_PI - TitleInfo[nCnt].fAngle)) * TitleInfo[nCnt].fLength;
				pVtx[1].pos.z = 0.0f;
				pVtx[2].pos.x = TitleInfo[nCnt].pos.x + sinf(TitleInfo[nCnt].rot.z - TitleInfo[nCnt].fAngle) * TitleInfo[nCnt].fLength;
				pVtx[2].pos.y = TitleInfo[nCnt].pos.y + cosf(TitleInfo[nCnt].rot.z - TitleInfo[nCnt].fAngle) * TitleInfo[nCnt].fLength;
				pVtx[2].pos.z = 0.0f;
				pVtx[3].pos.x = TitleInfo[nCnt].pos.x + sinf(TitleInfo[nCnt].rot.z + TitleInfo[nCnt].fAngle) * TitleInfo[nCnt].fLength;
				pVtx[3].pos.y = TitleInfo[nCnt].pos.y + cosf(TitleInfo[nCnt].rot.z + TitleInfo[nCnt].fAngle) * TitleInfo[nCnt].fLength;
				pVtx[3].pos.z = 0.0f;

				//頂点カラーの設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}

			pVtx += 4;
		}

		//モード決定
		if (GetJoypadTrigger(JOYKEY_A, 0) == true && bSelectMode == false
			|| GetKeyboardTrigger(DIK_RETURN) == true && bSelectMode == false)
		{
			PlaySound(SOUND_LABEL_CLICK);

			if (nSelectTitle == SELECTED_FINISH)
			{//もし終了が選択されていたら
				bSelectFinish = true;			//ゲーム終了の選択をさせる
			}
			else if (nSelectTitle == SELECTED_RANKING)
			{
				MovetoRanking();
			}
			else
			{//それ以外なら
				SwitchSelectMode();		//選択モード切り替え関数
				AnimSwitch();			//アニメーション切り替え関数
			}
		}
	}

	//頂点バッファのアンロック
	g_pVtxBuffTitleSelect->Unlock();
}

//===============================================================================
//タイトル選択描画
//===============================================================================
void DrawTitleSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleSelect, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	for (int nCnt = 0; nCnt < TITLE_SELECT_COUNT; nCnt++)
	{
		pDevice->SetTexture(0, g_pTextureTitleSelect[TitleInfo[nCnt].Type]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * nCnt,
			2);
	}
}

//===============================================================================
//選択画面を切り替える処理(ゲームとチュートリアルor人数選択)
//===============================================================================
void SwitchSelectMode(void)
{
	bSelectMode = bSelectMode ? false : true;
}

//===============================================================================
//現在人数選択かモード選択かを判断する為に使います
//===============================================================================
bool ReturnNowSelect(void)
{
	return bSelectMode;
}

//===============================================================================
//選択されたモードを判別したいから返す関数
//===============================================================================
int ReturnSelectedMode(void)
{
	if (nSelectTitle == 0)
	{
		return MODE_GAME;		//次に移行する画面はゲーム
	}
	else
	{
		return MODE_TUTORIAL;	//次に移行する画面はチュートリアル
	}
}