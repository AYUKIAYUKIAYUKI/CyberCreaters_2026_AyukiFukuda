//************************************************
//
//リザルト処理[result.cpp]
//Author：福田歩希
//
//************************************************
#include "result.h"

#include "fade.h"
#include "input.h"
#include "sound.h"

#include "resultdesign.h"

//************************************************
//リザルト初期
//************************************************
void InitResult()
{
	//フェード情報用
	FADE* pFade = GetInfoFade();

	//フェードイン開始
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	InitResultDesign();
}

//************************************************
//リザルト終了
//************************************************
void UninitResult(void)
{
	UninitResultDesign();
}

//************************************************
//リザルト更新
//************************************************
void UpdateResult(void)
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

	UpdateResultDesign();

	//フェードアウト後
	if (pFade->col.a >= 1.1f)
	{
		SetInfoMode(MODE_TITLE);
	}
}

//************************************************
//リザルト描画
//************************************************
void DrawResult(void)
{
	DrawResultDesign();
}