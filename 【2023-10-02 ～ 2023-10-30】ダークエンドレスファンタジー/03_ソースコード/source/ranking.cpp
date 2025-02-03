//************************************************
//
//�����L���O����[result.cpp]
//Author�F���c����
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
//�����L���O�����������֐�
//************************************************
void Init_Ranking()
{
	//�t�F�[�h���p
	FADE* pFade = GetInfo_Fade();

	//�t�F�[�h�C���J�n
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	Init_Press_Any(PRESS_TYPE_MENU);
	Init_Score_Ranking();
	Init_Text_Ranking();

	StopSound();
}

//************************************************
//�����L���O�I�������֐�
//************************************************
void Uninit_Ranking(void)
{
	Uninit_Press_Any();
	Uninit_Score_Ranking();
	Uninit_Text_Ranking();
}

//************************************************
//�����L���O�X�V�����֐�
//************************************************
void Update_Ranking(void)
{
	//�t�F�[�h���p
	FADE* pFade = GetInfo_Fade();

	//�t�F�[�h�C����
	if (pFade->col.a <= 0.0f)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_START) || GetJoypadTrigger(JOYKEY_BACK))
		{
			PlaySound(SOUND_LABEL_DEFINE);
			//�t�F�[�h�A�E�g�J�n
			pFade->bFadeIn = false;
			pFade->bFadeOut = true;
		}
	}

	Update_Press_Any();

	//�t�F�[�h�A�E�g��
	if (pFade->col.a >= 1.0f)
	{
		Setinfo_Mode(MODE_TITLE);	//�^�C�g�����[�h�ɐݒ�
	}
}

//************************************************
//�����L���O�`�揈���֐�
//************************************************
void Draw_Ranking(void)
{
	Draw_Press_Any();
	Draw_Score_Ranking();
	Draw_Text_Ranking();
}