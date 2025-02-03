//===============================================================================
//
//  人数選択処理(player_count.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "player_count.h"
#include "title_select.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

#define SELECT_TEXCOUNT	(11)		//テクスチャの数
#define SELECT_USE_POLY	(7)
#define SELECT_BASE_POS_X	(SCREEN_WIDTH * 0.5+ 320)

//テクスチャ列挙
static const char* PSelCnt[SELECT_TEXCOUNT]
{
	"data\\TEXTURE\\SelectCnt\\pSelect.png",	//鎖付いた板
	"data\\TEXTURE\\SelectCnt\\gear_l.png",		//左の歯車
	"data\\TEXTURE\\SelectCnt\\gear_r.png",		//右に歯車
	"data\\TEXTURE\\SelectCnt\\p1_on.png",		//一人色付き
	"data\\TEXTURE\\SelectCnt\\p2_on.png",		//二人色付き
	"data\\TEXTURE\\SelectCnt\\p3_on.png",		//三人色付き
	"data\\TEXTURE\\SelectCnt\\p4_on.png",		//四人色付き
	"data\\TEXTURE\\SelectCnt\\p1_off.png",		//一人色なし
	"data\\TEXTURE\\SelectCnt\\p2_off.png",		//二人色なし
	"data\\TEXTURE\\SelectCnt\\p3_off.png",		//三人色なし
	"data\\TEXTURE\\SelectCnt\\p4_off.png",		//四人色なし
};

//テクスチャ割り当て(順は上に〃)
typedef enum
{
	TEXTYPE_BASE = 0,
	TEXTYPE_GEAR_L,
	TEXTYPE_GEAR_R,
	TEXTYPE_PLAYER1_ON,
	TEXTYPE_PLAYER2_ON,
	TEXTYPE_PLAYER3_ON,
	TEXTYPE_PLAYER4_ON,
	TEXTYPE_PLAYER1_OFF,
	TEXTYPE_PLAYER2_OFF,
	TEXTYPE_PLAYER3_OFF,
	TEXTYPE_PLAYER4_OFF,
	TEXTYPE_MAX
}SELECT_TYPE;

//プレイヤーセレクト用構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fHeight;
	float fWidth;
	float fAngle;
	float fLength;
	int Type;
}PLAYERSELECT;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayerCount[SELECT_TEXCOUNT] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerCount = NULL;
int nSelectPlayerCnt;		//人数選択用変数
float nZoomSelectPCnt;		//ズームイン・アウト用
bool bSelectPlayerAnim;		//アニメーション判定用
bool AnimFinish;			//アニメーション終了判定
bool bSelPCnt[2];
PLAYERSELECT PlayerSelect[SELECT_USE_POLY];			//プレイヤー選択構造体

//===============================================================================
//人数選択画面の初期化処理
//===============================================================================
void InitPlayerCount(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	for (int i = 0; i < SELECT_TEXCOUNT; i++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			PSelCnt[i],
			&g_pTexturePlayerCount[i]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * SELECT_USE_POLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerCount,
		NULL);

	for (int i = 0; i < SELECT_USE_POLY; i++)
	{
		switch (i)
		{
		case TEXTYPE_BASE:
			PlayerSelect[i].pos = D3DXVECTOR3(SELECT_BASE_POS_X, -(SCREEN_HEIGHT * 0.5f), 0);
			PlayerSelect[i].fWidth = 460;
			PlayerSelect[i].fHeight = SCREEN_HEIGHT;
			PlayerSelect[i].Type = i;
			break;
		case TEXTYPE_GEAR_L:
			PlayerSelect[i].pos = D3DXVECTOR3(SELECT_BASE_POS_X - 250.0f, 0.0f, 0);
			PlayerSelect[i].fWidth = 120;
			PlayerSelect[i].fHeight = 120;
			PlayerSelect[i].Type = i;
			break;
		case TEXTYPE_GEAR_R:
			PlayerSelect[i].pos = D3DXVECTOR3(SELECT_BASE_POS_X + 250.0f, 0.0f, 0);
			PlayerSelect[i].fWidth = 120;
			PlayerSelect[i].fHeight = 120;
			PlayerSelect[i].Type = i;
			break;
		case TEXTYPE_PLAYER1_ON:
			PlayerSelect[i].pos = D3DXVECTOR3(SELECT_BASE_POS_X, -300, 0);
			PlayerSelect[i].fWidth = 180;
			PlayerSelect[i].fHeight = 80;
			PlayerSelect[i].Type = TEXTYPE_PLAYER1_ON;
			break;
		case TEXTYPE_PLAYER2_ON:
			PlayerSelect[i].pos = D3DXVECTOR3(SELECT_BASE_POS_X, -300, 0);
			PlayerSelect[i].fWidth = 180;
			PlayerSelect[i].fHeight = 80;
			PlayerSelect[i].Type = TEXTYPE_PLAYER2_OFF;
			break;
		case TEXTYPE_PLAYER3_ON:
			PlayerSelect[i].pos = D3DXVECTOR3(SELECT_BASE_POS_X, -300, 0);
			PlayerSelect[i].fWidth = 180;
			PlayerSelect[i].fHeight = 80;
			PlayerSelect[i].Type = TEXTYPE_PLAYER3_OFF;
			break;
		case TEXTYPE_PLAYER4_ON:
			PlayerSelect[i].pos = D3DXVECTOR3(SELECT_BASE_POS_X, -300, 0);
			PlayerSelect[i].fWidth = 180;
			PlayerSelect[i].fHeight = 80;
			PlayerSelect[i].Type = TEXTYPE_PLAYER4_OFF;
			break;
		}
		PlayerSelect[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//一応初期化
		PlayerSelect[i].fAngle = atan2f(PlayerSelect[i].fWidth, PlayerSelect[i].fHeight);
		PlayerSelect[i].fLength = sqrtf(PlayerSelect[i].fWidth * PlayerSelect[i].fWidth + PlayerSelect[i].fHeight * PlayerSelect[i].fHeight) / 2;
	}
	VERTEX_2D* pVtx;	//頂点情報のポインタ

	//頂点バッファをロックして、頂点情報へのポインタを取得
	g_pVtxBuffPlayerCount->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < SELECT_USE_POLY; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z - (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength;
		pVtx[0].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z - (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z + (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength;
		pVtx[1].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z + (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z - PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength;
		pVtx[2].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z - PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z + PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength;
		pVtx[3].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z + PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength;
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
	g_pVtxBuffPlayerCount->Unlock();
	nSelectPlayerCnt = 0;
	nZoomSelectPCnt = 0;
	bSelectPlayerAnim = false;
	AnimFinish = false;
	bSelPCnt[0] = false;
	bSelPCnt[1] = false;
}
//===============================================================================
//人数選択画面の終了処理
//===============================================================================
void UninitPlayerCount(void)
{
	for (int nCnt = 0; nCnt < SELECT_TEXCOUNT; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTexturePlayerCount[nCnt] != NULL)
		{
			g_pTexturePlayerCount[nCnt]->Release();
			g_pTexturePlayerCount[nCnt] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPlayerCount != NULL)
	{
		g_pVtxBuffPlayerCount->Release();
		g_pVtxBuffPlayerCount = NULL;
	}
}

//===============================================================================
//人数選択画面の更新処理
//===============================================================================
void UpdatePlayerCount(void)
{
	enum
	{
		SELECTTYPE_START = 0,
		SELECTTYPE_TUTORIAL,
		SELECTTYPE_RANKING,
		SELECTTYPE_FINISH
	};
	bSelPCnt[0] = ReturnNowSelect();
	if (bSelPCnt[0] == true&& bSelPCnt[1] == false)
	{
		//動かしたら切り替わるよ
		if (GetJoypadTrigger(JOYKEY_UP, 0) == true 
			|| GetKeyboardTrigger(DIK_UPARROW) == true)//上押したとき
		{
			PlaySound(SOUND_LABEL_CURSORMOVE);
			if (nSelectPlayerCnt == SELECTTYPE_START)
			{//もし一番上なら
				nSelectPlayerCnt = SELECTTYPE_FINISH;//下行きます
			}
			else
			{
				nSelectPlayerCnt--;
			}
			nZoomSelectPCnt = 0;

		}
		if (GetJoypadTrigger(JOYKEY_DOWN, 0) == true 
			|| GetKeyboardTrigger(DIK_DOWNARROW) == true)//下押したとき
		{
			PlaySound(SOUND_LABEL_CURSORMOVE);
			if (nSelectPlayerCnt == SELECTTYPE_FINISH)
			{//もし一番下なら
				nSelectPlayerCnt = SELECTTYPE_START;//上行きます
			}
			else
			{
				nSelectPlayerCnt++;
			}
			nZoomSelectPCnt = 0;

		}
		//どれが選択されてるか
		switch (nSelectPlayerCnt)
		{
		case SELECTTYPE_START:
			PlayerSelect[TEXTYPE_PLAYER1_ON].Type = TEXTYPE_PLAYER1_ON;
			PlayerSelect[TEXTYPE_PLAYER2_ON].Type = TEXTYPE_PLAYER2_OFF;
			PlayerSelect[TEXTYPE_PLAYER3_ON].Type = TEXTYPE_PLAYER3_OFF;
			PlayerSelect[TEXTYPE_PLAYER4_ON].Type = TEXTYPE_PLAYER4_OFF;
			break;
		case SELECTTYPE_TUTORIAL:
			PlayerSelect[TEXTYPE_PLAYER1_ON].Type = TEXTYPE_PLAYER1_OFF;
			PlayerSelect[TEXTYPE_PLAYER2_ON].Type = TEXTYPE_PLAYER2_ON;
			PlayerSelect[TEXTYPE_PLAYER3_ON].Type = TEXTYPE_PLAYER3_OFF;
			PlayerSelect[TEXTYPE_PLAYER4_ON].Type = TEXTYPE_PLAYER4_OFF;
			break;
		case SELECTTYPE_RANKING:
			PlayerSelect[TEXTYPE_PLAYER1_ON].Type = TEXTYPE_PLAYER1_OFF;
			PlayerSelect[TEXTYPE_PLAYER2_ON].Type = TEXTYPE_PLAYER2_OFF;
			PlayerSelect[TEXTYPE_PLAYER3_ON].Type = TEXTYPE_PLAYER3_ON;
			PlayerSelect[TEXTYPE_PLAYER4_ON].Type = TEXTYPE_PLAYER4_OFF;
			break;
		case SELECTTYPE_FINISH:
			PlayerSelect[TEXTYPE_PLAYER1_ON].Type = TEXTYPE_PLAYER1_OFF;
			PlayerSelect[TEXTYPE_PLAYER2_ON].Type = TEXTYPE_PLAYER2_OFF;
			PlayerSelect[TEXTYPE_PLAYER3_ON].Type = TEXTYPE_PLAYER3_OFF;
			PlayerSelect[TEXTYPE_PLAYER4_ON].Type = TEXTYPE_PLAYER4_ON;
			break;
		}

		//ズームイン・アウトの処理
		if (nZoomSelectPCnt < 12)
		{
			nZoomSelectPCnt += 1.2f;
		}

		//動かす部分のアニメーション
		if (bSelectPlayerAnim == false)
		{//選択肢降りてくる
			if (PlayerSelect[0].pos.y < SCREEN_HEIGHT * 0.5f)
			{
				PlayerSelect[0].pos.y += 48.0f;
				PlayerSelect[1].rot.z -= 0.3f;
				PlayerSelect[2].rot.z += 0.3f;
			}
			if (PlayerSelect[0].pos.y >= SCREEN_HEIGHT * 0.5f)
			{
				AnimFinish = true;
			}
		}//選択肢戻る
		else
		{
			if (PlayerSelect[0].pos.y > -SCREEN_HEIGHT * 0.5f)
			{
				PlayerSelect[0].pos.y -= 48.0f;
				PlayerSelect[1].rot.z += 0.3f;
				PlayerSelect[2].rot.z -= 0.3f;
			}
			else if (PlayerSelect[0].pos.y <= -SCREEN_HEIGHT * 0.5f)
			{
				SwitchSelectMode();
			}
		}
		//画面上での人数表示の相対値設定
		PlayerSelect[3].pos.y = PlayerSelect[0].pos.y - 165.0f;
		PlayerSelect[4].pos.y = PlayerSelect[0].pos.y - 40.0f;
		PlayerSelect[5].pos.y = PlayerSelect[0].pos.y + 80.0f;
		PlayerSelect[6].pos.y = PlayerSelect[0].pos.y + 210.0f;

		VERTEX_2D* pVtx;	//頂点情報のポインタ

		//頂点バッファをロックして、頂点情報へのポインタを取得
		g_pVtxBuffPlayerCount->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < SELECT_USE_POLY; nCnt++)
		{
			if (nCnt > 2)
			{
				if (PlayerSelect[nCnt].Type == nCnt)
				{
					//頂点座標の設定
					pVtx[0].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z - (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength - nZoomSelectPCnt;
					pVtx[0].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z - (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength - nZoomSelectPCnt;
					pVtx[0].pos.z = 0.0f;

					pVtx[1].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z + (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength + nZoomSelectPCnt;
					pVtx[1].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z + (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength - nZoomSelectPCnt;
					pVtx[1].pos.z = 0.0f;

					pVtx[2].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z - PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength - nZoomSelectPCnt;
					pVtx[2].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z - PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength + nZoomSelectPCnt;
					pVtx[2].pos.z = 0.0f;

					pVtx[3].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z + PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength + nZoomSelectPCnt;
					pVtx[3].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z + PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength + nZoomSelectPCnt;
					pVtx[3].pos.z = 0.0f;
				}
				else
				{
					//頂点座標の設定
					pVtx[0].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z - (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength;
					pVtx[0].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z - (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength;
					pVtx[0].pos.z = 0.0f;

					pVtx[1].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z + (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength;
					pVtx[1].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z + (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength;
					pVtx[1].pos.z = 0.0f;

					pVtx[2].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z - PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength;
					pVtx[2].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z - PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength;
					pVtx[2].pos.z = 0.0f;

					pVtx[3].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z + PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength;
					pVtx[3].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z + PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength;
					pVtx[3].pos.z = 0.0f;
				}
			}
			else
			{

				//頂点座標の設定
				pVtx[0].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z - (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength;
				pVtx[0].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z - (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength;
				pVtx[0].pos.z = 0.0f;

				pVtx[1].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z + (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength;
				pVtx[1].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z + (D3DX_PI - PlayerSelect[nCnt].fAngle)) * PlayerSelect[nCnt].fLength;
				pVtx[1].pos.z = 0.0f;

				pVtx[2].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z - PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength;
				pVtx[2].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z - PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength;
				pVtx[2].pos.z = 0.0f;

				pVtx[3].pos.x = PlayerSelect[nCnt].pos.x + sinf(PlayerSelect[nCnt].rot.z + PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength;
				pVtx[3].pos.y = PlayerSelect[nCnt].pos.y + cosf(PlayerSelect[nCnt].rot.z + PlayerSelect[nCnt].fAngle) * PlayerSelect[nCnt].fLength;
				pVtx[3].pos.z = 0.0f;

			}

			pVtx += 4;
		}

	}
	//頂点バッファのアンロック
	g_pVtxBuffPlayerCount->Unlock();
	if (GetJoypadTrigger(JOYKEY_A, 0) == true && AnimFinish == true
		 || GetKeyboardTrigger(DIK_RETURN) == true && AnimFinish == true)//決定！
	{
		PlaySound(SOUND_LABEL_CLICK);
		int Mode = ReturnSelectedMode();

		//フェードアウト処理
		SetFade(FADE_OUT, (MODE)Mode);//二つ目に移行先
		bSelPCnt[1] = true;
	}
	if (GetJoypadTrigger(JOYKEY_B, 0) == true && AnimFinish == true 
		 || GetKeyboardTrigger(DIK_BACKSPACE) == true && AnimFinish == true)//嘘！
	{
		PlaySound(SOUND_LABEL_CANCEL);
		bSelectPlayerAnim = true;
		AnimFinish = false;
	}
}

//===============================================================================
//人数選択画面系の描画
//===============================================================================
void DrawPlayerCount(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayerCount, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	for (int nCnt = 0; nCnt < SELECT_USE_POLY; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexturePlayerCount[PlayerSelect[nCnt].Type]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * nCnt,
			2);
	}
}

//===============================================================================
//選択されている人数を返す関数
//===============================================================================
int ReturnSelectPlayerCount(void)
{
	return nSelectPlayerCnt;		//これを int i = ReturnSelectPlayerCount()するだけで人数取得できます(0～3)
}

//===============================================================================
//アニメーションが終わったことを返す関数
//===============================================================================
bool ReturnAnimFinish(void)
{
	return AnimFinish;
}

//===============================================================================
//別のcppからアニメーションを作動させる関数
//===============================================================================
void AnimSwitch(void)
{
	bSelectPlayerAnim = false;
}