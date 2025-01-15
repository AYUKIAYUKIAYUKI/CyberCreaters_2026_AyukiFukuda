//************************************************
//
//リザルト処理[result.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "input.h"
#include "fade.h"
#include "press_any.h"
#include "score.h"
#include "timer.h"
#include "result.h"
#include "text_result.h"
#include "window_result.h"

//グローバル変数
bool g_bCLEAR = false;	//trueでCLEAR

//************************************************
//リザルト初期化処理関数
//************************************************
void Init_Result()
{
	//フェード情報用
	FADE* pFade = GetInfo_Fade();

	//フェードイン開始
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	//タイマー0で終わってたらCLEARで
	int* pTimer = GetInfo_Timer();
	*pTimer <= 0 ? g_bCLEAR = true : g_bCLEAR = false;

	Init_Press_Any(PRESS_TYPE_MENU);
	Init_Score(SCORE_TYPE_RESULT);
	Init_Text_Result();
	Init_Window_Result();
}

//************************************************
//リザルト終了処理関数
//************************************************
void Uninit_Result(void)
{
	Uninit_Press_Any();
	Uninit_Score();
	Uninit_Text_Result();
	Uninit_Window_Result();
}

//************************************************
//リザルト更新処理関数
//************************************************
void Update_Result(void)
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
	Update_Score();

	//フェードアウト後
	if (pFade->col.a >= 1.0f)
	{
		Setinfo_Mode(MODE_TITLE);	//タイトルモードに設定
	}
}

//************************************************
//リザルト描画処理関数
//************************************************
void Draw_Result(void)
{
	Draw_Press_Any();
	Draw_Score();
	Draw_Text_Result();
	Draw_Window_Result();
}

//************************************************
//CLEAR判定を送る関数
//************************************************
bool* GetInfo_CLEAR(void)
{
	return &g_bCLEAR;
}