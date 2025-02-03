//************************************************
//
//タイトル[title.cpp]
//Author：福田歩希
//
//************************************************
#include "title.h"

#include "fade.h"
#include "input.h"
#include "sound.h"

#include "camera.h"
#include "field.h"
#include "light.h"
#include "player.h"
#include "rankingdesign.h"
#include "shadow.h"
#include "titledesign.h"

//************************************************
//タイトル初期
//************************************************
void InitTitle(void)
{
	//フェード情報用
	FADE* pFade = GetInfoFade();

	//フェードイン開始
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	int* pLastMode = ChangeLastMode();
	*pLastMode = MODE_TITLE;

	InitShadow();

	InitCamera();
	InitField();
	InitLight();
	InitPlayer(MODE_TITLE);
	InitTitleDesign();

	PlaySound(SOUND_LABEL_TITLE);
}

//************************************************
//タイトル終了処理関数
//************************************************
void UninitTitle(void)
{
	UninitCamera();
	UninitField();
	UninitLight();
	UninitPlayer();
	UninitShadow();
	UninitTitleDesign();

	StopSound();
}

//************************************************
//タイトル更新
//************************************************
void UpdateTitle(void)
{
	//フェード情報用
	FADE* pFade = GetInfoFade();

	UpdateCamera(MODE_TITLE);
	UpdateField();
	UpdateLight();
	UpdatePlayer(MODE_TITLE);
	UpdateShadow(MODE_TITLE);
	UpdateTitleDesign();

	//フェードアウト後
	if (pFade->col.a >= 1.1f)
	{
		SetInfoMode(GetChooseMode());
	}
}

//************************************************
//タイトル描画
//************************************************
void DrawTitle(void)
{
	SetInfoCamera(MODE_TITLE);
	DrawField();
	SetLight();
	DrawPlayer();
	DrawShadow();
	DrawTitleDesign();
}