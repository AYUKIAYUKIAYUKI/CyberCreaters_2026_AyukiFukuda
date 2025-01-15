//************************************************
//
//メニュー処理[menu.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "input.h"
#include "fade.h"
#include "menu.h"
#include "press_any.h"
#include "window_menu.h"

//************************************************
//メニュー初期化処理関数
//************************************************
void Init_Menu()
{
	//フェード情報用
	FADE* pFade = GetInfo_Fade();

	//フェードイン開始
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	Init_Press_Any(PRESS_TYPE_RESULT);
	Init_Window_Menu();
}

//************************************************
//メニュー終了処理関数
//************************************************
void Uninit_Menu(void)
{
	Uninit_Press_Any();
	Uninit_Window_Menu();

	StopSound();
}

//************************************************
//メニュー更新処理関数
//************************************************
void Update_Menu(void)
{
	//フェード情報用
	FADE* pFade = GetInfo_Fade();

	//フェードイン後
	if (pFade->col.a <= 0.0f)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_START) || GetJoypadTrigger(JOYKEY_BACK))
		{
			PlaySound(SOUND_LABEL_DEFINE);
			//フェードアウト開始
			pFade->bFadeIn = false;
			pFade->bFadeOut = true;
		}
	}

	Update_Press_Any();

	//フェードアウト後
	if (pFade->col.a >= 1.0f)
	{
		Setinfo_Mode(MODE_GAME);	//ゲームモードに設定
	}
}

//************************************************
//メニュー描画処理関数
//************************************************
void Draw_Menu(void)
{
	Draw_Window_Menu();
	Draw_Press_Any();
}