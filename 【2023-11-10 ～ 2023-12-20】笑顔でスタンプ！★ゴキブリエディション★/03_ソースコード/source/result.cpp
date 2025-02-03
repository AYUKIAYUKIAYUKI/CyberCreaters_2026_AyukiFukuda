//************************************************
//
//���U���g����[result.cpp]
//Author�F���c����
//
//************************************************
#include "result.h"

#include "fade.h"
#include "input.h"
#include "sound.h"

#include "resultdesign.h"

//************************************************
//���U���g����
//************************************************
void InitResult()
{
	//�t�F�[�h���p
	FADE* pFade = GetInfoFade();

	//�t�F�[�h�C���J�n
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	InitResultDesign();
}

//************************************************
//���U���g�I��
//************************************************
void UninitResult(void)
{
	UninitResultDesign();
}

//************************************************
//���U���g�X�V
//************************************************
void UpdateResult(void)
{
	//�t�F�[�h���p
	FADE* pFade = GetInfoFade();

	if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_B) || GetJoypadTrigger(JOYKEY_START))
	{
		//�t�F�[�h�A�E�g�J�n
		pFade->bFadeIn = false;
		pFade->bFadeOut = true;

		PlaySound(SOUND_LABEL_DEFINE);
	}

	UpdateResultDesign();

	//�t�F�[�h�A�E�g��
	if (pFade->col.a >= 1.1f)
	{
		SetInfoMode(MODE_TITLE);
	}
}

//************************************************
//���U���g�`��
//************************************************
void DrawResult(void)
{
	DrawResultDesign();
}