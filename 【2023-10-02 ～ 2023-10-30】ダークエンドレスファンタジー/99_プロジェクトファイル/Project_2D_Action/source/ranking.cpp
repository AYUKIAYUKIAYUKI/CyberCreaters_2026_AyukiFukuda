//************************************************
//
//ランキング処理[result.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "input.h"
#include "fade.h"
#include "press_any.h"
#include "ranking.h"
#include "score_ranking.h"
#include "text_ranking.h"

//************************************************
//ランキング初期化処理関数
//************************************************
void Init_Ranking()
{
	//フェード情報用
	FADE* pFade = GetInfo_Fade();

	//フェードイン開始
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	Init_Press_Any(PRESS_TYPE_MENU);
	Init_Score_Ranking();
	Init_Text_Ranking();

	StopSound();
}

//************************************************
//ランキング終了処理関数
//************************************************
void Uninit_Ranking(void)
{
	Uninit_Press_Any();
	Uninit_Score_Ranking();
	Uninit_Text_Ranking();
}

//************************************************
//ランキング更新処理関数
//************************************************
void Update_Ranking(void)
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
		Setinfo_Mode(MODE_TITLE);	//タイトルモードに設定
	}
}

//************************************************
//ランキング描画処理関数
//************************************************
void Draw_Ranking(void)
{
	Draw_Press_Any();
	Draw_Score_Ranking();
	Draw_Text_Ranking();
}