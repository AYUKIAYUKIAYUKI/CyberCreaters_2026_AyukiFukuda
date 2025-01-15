//************************************************
//
//リザルト表示処理(荒れ地)[result.cpp]
//Author：福田歩希
//
//************************************************
#include "../header/input.h"
#include "../header/sound.h"
#include "../header/player.h"
#include "../header/result.h"

//マクロ定義
#define MAX_RESULT	(10)		//ポリゴン数
#define TEXAMT_RESULT	(10)	//読込みテクスチャ数

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Result[TEXAMT_RESULT] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Result = NULL;			//頂点バッファのポインタ
int g_cursor_result = 0;									//タイトル用のカーソル
/*カーソルアニメーション用*/
float g_ANIMcursorL_r = 600.0f;
float g_ANIMcursorR_r = 700.0f;
bool g_bTurn_cursor_r = false;
/*色変更用*/
bool bStartFadein_Result = true;	//フェードインの許可
bool bStartFadeout_Result = false;	//フェードアウトの許可
int g_A_Result = 0;				//透明度の調整

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Result(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEX_1_RESULT,
		&g_pTexture_Result[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEX_2_RESULT,
		&g_pTexture_Result[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEX_3_RESULT,
		&g_pTexture_Result[2]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEX_4_RESULT,
		&g_pTexture_Result[3]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEX_5_RESULT,
		&g_pTexture_Result[4]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEX_6_RESULT,
		&g_pTexture_Result[5]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEX_7_RESULT,
		&g_pTexture_Result[6]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEX_8_RESULT,
		&g_pTexture_Result[7]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEX_9_RESULT,
		&g_pTexture_Result[8]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEX_10_RESULT,
		&g_pTexture_Result[9]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMT_PLG_RESULT * TEXAMT_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Result,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Result;

	//プレイヤー情報へのポインタ
	PLAYER* pPlayer;

	//プレイヤー情報の取得
	pPlayer = Getinfo_Player();	//プレイヤー情報系の先頭アドレスが代入される

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Result->Lock(0, 0, (void**)&pVtx_Result, 0);

	bStartFadein_Result = true;
	bStartFadeout_Result = false;
	g_A_Result = 255;

	//初期位置設定
	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			//ゲームクリア
			if (pPlayer->nLife > 0)
			{
				pVtx_Result[0].pos = D3DXVECTOR3(250.0f, 100.0f, 0.0f);
				pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 250.0f, 100.0f, 0.0f);
				pVtx_Result[2].pos = D3DXVECTOR3(250.0f, 400.0f, 0.0f);
				pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 250.0f, 400.0f, 0.0f);
			}

			break;

		case 1:

			//ゲームオーバー
			if (pPlayer->nLife <= 0)
			{
				pVtx_Result[0].pos = D3DXVECTOR3(250.0f, 100.0f, 0.0f);
				pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 250.0f, 100.0f, 0.0f);
				pVtx_Result[2].pos = D3DXVECTOR3(250.0f, 400.0f, 0.0f);
				pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 250.0f, 400.0f, 0.0f);
			}

			break;

		case 2:

			//メニュー灰色
			pVtx_Result[0].pos = D3DXVECTOR3(800.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 800.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(800.0f, SCREEN_HEIGHT - 400.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 800.0f, SCREEN_HEIGHT - 400.0f, 0.0f);

			break;

		case 3:

			//メニュー金色
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 4:

			//リトライ灰色
			pVtx_Result[0].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);

			break;

		case 5:

			//リトライ金色
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 6:

			//終了灰色
			pVtx_Result[0].pos = D3DXVECTOR3(850.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(850.0f, SCREEN_HEIGHT - 100.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 100.0f, 0.0f);

			break;

		case 7:

			//終了金色
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 8:

			//カーソル
			pVtx_Result[0].pos = D3DXVECTOR3(600.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(700.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(600.0f, SCREEN_HEIGHT - 400.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(700.0f, SCREEN_HEIGHT - 400.0f, 0.0f);

			break;

		case 9:

			//ブラックベース
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

			break;
		}

		//rhwの設定
		pVtx_Result[0].rhw = 1.0f;
		pVtx_Result[1].rhw = 1.0f;
		pVtx_Result[2].rhw = 1.0f;
		pVtx_Result[3].rhw = 1.0f;

		//頂点カラーの設定
		if (nCnt != 9)
		{
			pVtx_Result[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx_Result[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx_Result[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx_Result[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else
		{
			pVtx_Result[0].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
			pVtx_Result[1].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
			pVtx_Result[2].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
			pVtx_Result[3].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
		}

		//テクスチャ座標の設定
		pVtx_Result[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Result[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Result[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Result[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//ポインタをずらす
		pVtx_Result += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Result->Unlock();

	g_cursor_result = 0;
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Result(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < TEXAMT_RESULT; nCnt++)
	{
		if (g_pTexture_Result[nCnt] != NULL)
		{
			g_pTexture_Result[nCnt]->Release();
			g_pTexture_Result[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Result != NULL)
	{
		g_pVtxBuff_Result->Release();
		g_pVtxBuff_Result = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Result(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Result;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Result->Lock(0, 0, (void**)&pVtx_Result, 0);

	//フェードイン
	if (bStartFadein_Result == true)
	{
		g_A_Result -= 10;

		if (g_A_Result <= 0)
		{
			bStartFadein_Result = false;

			g_A_Result = 0;
		}

		pVtx_Result += 4 * 9;

		pVtx_Result[0].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
		pVtx_Result[1].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
		pVtx_Result[2].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
		pVtx_Result[3].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
	}

	//フェードイン後、自由選択可能
	if (bStartFadeout_Result == false && bStartFadein_Result == false)
	{
		if (GetKeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP) == true
			&& g_cursor_result > 0)
		{
			//カーソル上へ
			g_cursor_result--;

			//効果音を鳴らす
			PlaySound(SOUND_LABEL_SE_SELECT1);
		}
		else if (GetKeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true
			&& g_cursor_result < 2)
		{
			//カーソル下へ
			g_cursor_result++;

			//効果音を鳴らす
			PlaySound(SOUND_LABEL_SE_SELECT1);
		}

		//カーソルアニメーション(常時)
		Setcursor_Anim_R();

		switch (g_cursor_result)
		{
		case 0:

			//MENUを選択
			Setcursor_MENU();

			break;

		case 1:

			//RETRYを選択
			Setcursor_RETRY_R();

			break;

		case 2:

			//EXITを選択
			Setcursor_EXIT_R();

			break;
		}
	}

	//決定された
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true
		&& bStartFadeout_Result == false)
	{
		//効果音を鳴らす
		PlaySound(SOUND_LABEL_SE_SELECT2);

		bStartFadeout_Result = true;
	}

	if (bStartFadeout_Result == true)
	{
		//フェード開始
		g_A_Result += 10;

		pVtx_Result += 4 * 9;

		pVtx_Result[0].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
		pVtx_Result[1].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
		pVtx_Result[2].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
		pVtx_Result[3].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);

		if (g_A_Result >= 255)
		{
			//頂点バッファをアンロックする
			g_pVtxBuff_Result->Unlock();

			switch (g_cursor_result)
			{
			case 0:

				Setinfo_Mode(MODE_MENU);	//メニューモードへ

				break;

			case 1:

				Setinfo_Mode(MODE_GAME);	//ゲームモードへ

				break;

			case 2:

				//終了判定変数アドレス用のポインタ
				bool* pExit;

				//アドレスを代入
				pExit = Getinfo_End();

				*pExit = true;	//ゲーム終了

				break;
			}
		}
	}
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Result(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Result, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < TEXAMT_RESULT; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Result[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, AMT_TRI_RESULT);
	}
}

//************************************************
//カーソルMENU選択時処理
//************************************************
void Setcursor_MENU(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Result;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Result->Lock(0, 0, (void**)&pVtx_Result, 0);

	//カーソル用にポリゴン設定
	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		switch (nCnt)
		{
		case 2:

			//メニュー灰色
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 3:

			//メニュー金色
			pVtx_Result[0].pos = D3DXVECTOR3(800.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 800.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(800.0f, SCREEN_HEIGHT - 400.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 800.0f, SCREEN_HEIGHT - 400.0f, 0.0f);

			break;

		case 4:

			//リトライ灰色
			pVtx_Result[0].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);

			break;

		case 5:

			//リトライ金色
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 8:

			//カーソル
			pVtx_Result[0].pos = D3DXVECTOR3(g_ANIMcursorL_r, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(g_ANIMcursorR_r, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(g_ANIMcursorL_r, SCREEN_HEIGHT - 400.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(g_ANIMcursorR_r, SCREEN_HEIGHT - 400.0f, 0.0f);

			break;
		}

		//ポインタをずらす
		pVtx_Result += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Result->Unlock();
}

//************************************************
//カーソルRETRY選択時処理
//************************************************
void Setcursor_RETRY_R(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Result;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Result->Lock(0, 0, (void**)&pVtx_Result, 0);

	//カーソル用にポリゴン設定
	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		switch (nCnt)
		{
		case 2:

			//メニュー灰色
			pVtx_Result[0].pos = D3DXVECTOR3(800.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 800.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(800.0f, SCREEN_HEIGHT - 400.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 800.0f, SCREEN_HEIGHT - 400.0f, 0.0f);

			break;

		case 3:

			//メニュー金色
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 4:

			//リトライ灰色
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 5:

			//リトライ金色
			pVtx_Result[0].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);

			break;

		case 6:

			//終了灰色
			pVtx_Result[0].pos = D3DXVECTOR3(850.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(850.0f, SCREEN_HEIGHT - 100.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 100.0f, 0.0f);

			break;

		case 7:

			//終了金色
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 8:

			//カーソル
			pVtx_Result[0].pos = D3DXVECTOR3(g_ANIMcursorL_r, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(g_ANIMcursorR_r, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(g_ANIMcursorL_r, SCREEN_HEIGHT - 250.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(g_ANIMcursorR_r, SCREEN_HEIGHT - 250.0f, 0.0f);

			break;
		}

		//ポインタをずらす
		pVtx_Result += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Result->Unlock();
}

//************************************************
//カーソルEXIT選択時処理
//************************************************
void Setcursor_EXIT_R(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Result;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Result->Lock(0, 0, (void**)&pVtx_Result, 0);

	//カーソル用にポリゴン設定
	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		switch (nCnt)
		{
		case 4:

			//リトライ灰色
			pVtx_Result[0].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);

			break;

		case 5:

			//リトライ金色
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 6:

			//終了灰色
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 7:

			//終了金色
			pVtx_Result[0].pos = D3DXVECTOR3(850.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(850.0f, SCREEN_HEIGHT - 100.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 100.0f, 0.0f);

			break;

		case 8:

			//カーソル
			pVtx_Result[0].pos = D3DXVECTOR3(g_ANIMcursorL_r, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(g_ANIMcursorR_r, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(g_ANIMcursorL_r, SCREEN_HEIGHT - 100.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(g_ANIMcursorR_r, SCREEN_HEIGHT - 100.0f, 0.0f);

			break;
		}

		//ポインタをずらす
		pVtx_Result += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Result->Unlock();
}

//************************************************
//カーソルアニメーション処理
//************************************************
void Setcursor_Anim_R(void)
{
	if (g_ANIMcursorL_r < 600.0f + 10.0f && g_bTurn_cursor_r == false)
	{
		g_ANIMcursorL_r += 1.0f;
		g_ANIMcursorR_r += 1.0f;
	}
	else
	{
		g_bTurn_cursor_r = true;
	}

	if (g_ANIMcursorL_r > 600.0f - 10.0f && g_bTurn_cursor_r == true)
	{
		g_ANIMcursorL_r -= 1.0f;
		g_ANIMcursorR_r -= 1.0f;
	}
	else
	{
		g_bTurn_cursor_r = false;
	}
}