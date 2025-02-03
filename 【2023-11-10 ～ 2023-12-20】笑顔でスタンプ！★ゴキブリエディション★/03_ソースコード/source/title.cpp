//************************************************
//
//�^�C�g��[title.cpp]
//Author�F���c����
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
//�^�C�g������
//************************************************
void InitTitle(void)
{
	//�t�F�[�h���p
	FADE* pFade = GetInfoFade();

	//�t�F�[�h�C���J�n
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
//�^�C�g���I�������֐�
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
//�^�C�g���X�V
//************************************************
void UpdateTitle(void)
{
	//�t�F�[�h���p
	FADE* pFade = GetInfoFade();

	UpdateCamera(MODE_TITLE);
	UpdateField();
	UpdateLight();
	UpdatePlayer(MODE_TITLE);
	UpdateShadow(MODE_TITLE);
	UpdateTitleDesign();

	//�t�F�[�h�A�E�g��
	if (pFade->col.a >= 1.1f)
	{
		SetInfoMode(GetChooseMode());
	}
}

//************************************************
//�^�C�g���`��
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