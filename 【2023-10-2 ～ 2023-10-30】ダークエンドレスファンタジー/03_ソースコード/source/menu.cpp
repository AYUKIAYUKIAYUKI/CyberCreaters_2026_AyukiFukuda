//************************************************
//
//���j���[����[menu.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "input.h"
#include "fade.h"
#include "menu.h"
#include "press_any.h"
#include "window_menu.h"

//************************************************
//���j���[�����������֐�
//************************************************
void Init_Menu()
{
	//�t�F�[�h���p
	FADE* pFade = GetInfo_Fade();

	//�t�F�[�h�C���J�n
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	Init_Press_Any(PRESS_TYPE_RESULT);
	Init_Window_Menu();
}

//************************************************
//���j���[�I�������֐�
//************************************************
void Uninit_Menu(void)
{
	Uninit_Press_Any();
	Uninit_Window_Menu();

	StopSound();
}

//************************************************
//���j���[�X�V�����֐�
//************************************************
void Update_Menu(void)
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
		Setinfo_Mode(MODE_GAME);	//�Q�[�����[�h�ɐݒ�
	}
}

//************************************************
//���j���[�`�揈���֐�
//************************************************
void Draw_Menu(void)
{
	Draw_Window_Menu();
	Draw_Press_Any();
}