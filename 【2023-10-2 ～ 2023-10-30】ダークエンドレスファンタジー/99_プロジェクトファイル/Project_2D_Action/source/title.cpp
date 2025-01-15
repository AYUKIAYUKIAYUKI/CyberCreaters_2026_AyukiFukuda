//************************************************
//
//�^�C�g������[title.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "input.h"
#include "fade.h"
#include "bg.h"
#include "title.h"
#include "cursor_title.h"
#include "logo_title.h"
#include "text_title.h"

//�O���[�o���ϐ�
static int g_nChoose;	//����I�����Ă��邩

//************************************************
//�^�C�g�������������֐�
//************************************************
void Init_Title()
{
	//�t�F�[�h���p
	FADE* pFade = GetInfo_Fade();

	//�t�F�[�h�C���J�n
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	Init_BG(BG_TYPE_TITLE);
	Init_Logo_Title();
	Init_Text_Title();
	Init_Cursor_Title();

	g_nChoose = START;

	PlaySound(SOUND_LABEL_TITLE);
}

//************************************************
//�^�C�g���I�������֐�
//************************************************
void Uninit_Title(void)
{
	Uninit_BG();
	Uninit_Cursor_Title();
	Uninit_Logo_Title();
	Uninit_Text_Title();
}

//************************************************
//�^�C�g���X�V�����֐�
//************************************************
void Update_Title(void)
{
	//�t�F�[�h���p
	FADE* pFade = GetInfo_Fade();

	//�t�F�[�h�C����
	if (pFade->col.a <= 0.0f)
	{
		//���ڐ؂�ւ�
		if (GetKeyboardTrigger(DIK_UP) || GetJoypadTrigger(JOYKEY_UP))
		{
			g_nChoose <= START ? g_nChoose = END : g_nChoose--;
			PlaySound(SOUND_LABEL_CHOOSE);
		}
		else if (GetKeyboardTrigger(DIK_DOWN) || GetJoypadTrigger(JOYKEY_DOWN))
		{
			g_nChoose >= END ? g_nChoose = START : g_nChoose++;
			PlaySound(SOUND_LABEL_CHOOSE);
		}

		//����
		if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_START) || GetJoypadTrigger(JOYKEY_BACK))
		{
			PlaySound(SOUND_LABEL_DEFINE);
			//�t�F�[�h�A�E�g�J�n
			pFade->bFadeIn = false;
			pFade->bFadeOut = true;
		}
	}

	Update_BG();
	Update_Cursor_Title();
	Update_Text_Title();

	//�t�F�[�h�A�E�g��
	if (pFade->col.a >= 1.0f)
	{
		switch (g_nChoose)
		{
		case START:
			Setinfo_Mode(MODE_MENU);	//���j���[���[�h�ɐݒ�
			break;
		case RANKING:
			Setinfo_Mode(MODE_RANKING);	//�����L���O���[�h�ɐݒ�
			break;
		case END:
			bool* pExit = Getinfo_End();
			*pExit = true;
			break;
		}
	}
}

//************************************************
//�^�C�g���`�揈���֐�
//************************************************
void Draw_Title(void)
{
	Draw_BG();
	Draw_Cursor_Title();
	Draw_Logo_Title();
	Draw_Text_Title();
}

//************************************************
//�^�C�g�����j���[�I�����ڂ������n��
//************************************************
int* Getinfo_Choose_Title_Menu(void)
{
	return &g_nChoose;
}