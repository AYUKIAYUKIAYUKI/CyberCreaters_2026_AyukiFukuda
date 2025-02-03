//************************************************
//
//タイトル処理[title.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "input.h"
#include "fade.h"
#include "bg.h"
#include "title.h"
#include "cursor_title.h"
#include "logo_title.h"
#include "text_title.h"

//グローバル変数
static int g_nChoose;	//何を選択しているか

//************************************************
//タイトル初期化処理関数
//************************************************
void Init_Title()
{
	//フェード情報用
	FADE* pFade = GetInfo_Fade();

	//フェードイン開始
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	Init_BG(BG_TYPE_TITLE);
	Init_Logo_Title();
	Init_Text_Title();
	Init_Cursor_Title();

	g_nChoose = START;

	PlaySound(SOUND_LABEL_TITLE);
}

//************************************************
//タイトル終了処理関数
//************************************************
void Uninit_Title(void)
{
	Uninit_BG();
	Uninit_Cursor_Title();
	Uninit_Logo_Title();
	Uninit_Text_Title();
}

//************************************************
//タイトル更新処理関数
//************************************************
void Update_Title(void)
{
	//フェード情報用
	FADE* pFade = GetInfo_Fade();

	//フェードイン後
	if (pFade->col.a <= 0.0f)
	{
		//項目切り替え
		if (GetKeyboardTrigger(DIK_UP) || GetJoypadTrigger(JOYKEY_UP))
		{
			g_nChoose <= START ? g_nChoose = END : g_nChoose--;
			PlaySound(SOUND_LABEL_CHOOSE);
		}
		else if (GetKeyboardTrigger(DIK_DOWN) || GetJoypadTrigger(JOYKEY_DOWN))
		{
			g_nChoose >= END ? g_nChoose = START : g_nChoose++;
			PlaySound(SOUND_LABEL_CHOOSE);
		}

		//決定
		if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_START) || GetJoypadTrigger(JOYKEY_BACK))
		{
			PlaySound(SOUND_LABEL_DEFINE);
			//フェードアウト開始
			pFade->bFadeIn = false;
			pFade->bFadeOut = true;
		}
	}

	Update_BG();
	Update_Cursor_Title();
	Update_Text_Title();

	//フェードアウト後
	if (pFade->col.a >= 1.0f)
	{
		switch (g_nChoose)
		{
		case START:
			Setinfo_Mode(MODE_MENU);	//メニューモードに設定
			break;
		case RANKING:
			Setinfo_Mode(MODE_RANKING);	//ランキングモードに設定
			break;
		case END:
			bool* pExit = Getinfo_End();
			*pExit = true;
			break;
		}
	}
}

//************************************************
//タイトル描画処理関数
//************************************************
void Draw_Title(void)
{
	Draw_BG();
	Draw_Cursor_Title();
	Draw_Logo_Title();
	Draw_Text_Title();
}

//************************************************
//タイトルメニュー選択項目を引き渡す
//************************************************
int* Getinfo_Choose_Title_Menu(void)
{
	return &g_nChoose;
}