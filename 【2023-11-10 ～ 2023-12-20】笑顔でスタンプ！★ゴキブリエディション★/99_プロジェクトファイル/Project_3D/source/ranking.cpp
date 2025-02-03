//************************************************
//
//ランキング[ranking.cpp]
//Author：福田歩希
//
//************************************************
#include "ranking.h"

#include "fade.h"
#include "input.h"
#include "sound.h"

#include "rankingdesign.h"

//************************************************
//ランキング初期
//************************************************
void InitRanking(void)
{
	//フェード情報用
	FADE* pFade = GetInfoFade();

	//フェードイン開始
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	InitRankingDesign();
}

//************************************************
//ランキング終了処理関数
//************************************************
void UninitRanking(void)
{
	UninitRankingDesign();
}

//************************************************
//ランキング更新
//************************************************
void UpdateRanking(void)
{
	//フェード情報用
	FADE* pFade = GetInfoFade();

	if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_B) || GetJoypadTrigger(JOYKEY_START))
	{
		//フェードアウト開始
		pFade->bFadeIn = false;
		pFade->bFadeOut = true;

		PlaySound(SOUND_LABEL_DEFINE);
	}

	UpdateRankingDesign();

	//フェードアウト後
	if (pFade->col.a >= 1.1f)
	{
		SetInfoMode(MODE_TITLE);
	}
}

//************************************************
//ランキング描画
//************************************************
void DrawRanking(void)
{
	DrawRankingDesign();
}