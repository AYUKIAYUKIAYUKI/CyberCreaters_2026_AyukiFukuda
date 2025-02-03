//************************************************
//
//�����L���O[ranking.cpp]
//Author�F���c����
//
//************************************************
#include "ranking.h"

#include "fade.h"
#include "input.h"
#include "sound.h"

#include "rankingdesign.h"

//************************************************
//�����L���O����
//************************************************
void InitRanking(void)
{
	//�t�F�[�h���p
	FADE* pFade = GetInfoFade();

	//�t�F�[�h�C���J�n
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	InitRankingDesign();
}

//************************************************
//�����L���O�I�������֐�
//************************************************
void UninitRanking(void)
{
	UninitRankingDesign();
}

//************************************************
//�����L���O�X�V
//************************************************
void UpdateRanking(void)
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

	UpdateRankingDesign();

	//�t�F�[�h�A�E�g��
	if (pFade->col.a >= 1.1f)
	{
		SetInfoMode(MODE_TITLE);
	}
}

//************************************************
//�����L���O�`��
//************************************************
void DrawRanking(void)
{
	DrawRankingDesign();
}