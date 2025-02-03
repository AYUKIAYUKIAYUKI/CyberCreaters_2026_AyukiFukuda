//************************************************
//
//���U���g����[result.cpp]
//Author�F���c����
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

//�O���[�o���ϐ�
bool g_bCLEAR = false;	//true��CLEAR

//************************************************
//���U���g�����������֐�
//************************************************
void Init_Result()
{
	//�t�F�[�h���p
	FADE* pFade = GetInfo_Fade();

	//�t�F�[�h�C���J�n
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	//�^�C�}�[0�ŏI����Ă���CLEAR��
	int* pTimer = GetInfo_Timer();
	*pTimer <= 0 ? g_bCLEAR = true : g_bCLEAR = false;

	Init_Press_Any(PRESS_TYPE_MENU);
	Init_Score(SCORE_TYPE_RESULT);
	Init_Text_Result();
	Init_Window_Result();
}

//************************************************
//���U���g�I�������֐�
//************************************************
void Uninit_Result(void)
{
	Uninit_Press_Any();
	Uninit_Score();
	Uninit_Text_Result();
	Uninit_Window_Result();
}

//************************************************
//���U���g�X�V�����֐�
//************************************************
void Update_Result(void)
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
	Update_Score();

	//�t�F�[�h�A�E�g��
	if (pFade->col.a >= 1.0f)
	{
		Setinfo_Mode(MODE_TITLE);	//�^�C�g�����[�h�ɐݒ�
	}
}

//************************************************
//���U���g�`�揈���֐�
//************************************************
void Draw_Result(void)
{
	Draw_Press_Any();
	Draw_Score();
	Draw_Text_Result();
	Draw_Window_Result();
}

//************************************************
//CLEAR����𑗂�֐�
//************************************************
bool* GetInfo_CLEAR(void)
{
	return &g_bCLEAR;
}