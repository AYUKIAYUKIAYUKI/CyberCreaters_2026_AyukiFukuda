//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLE = 0,	//�^�C�g��
	SOUND_LABEL_BATTLE,		//�o�g��
	SOUND_LABEL_CHOOSE,		//�I��
	SOUND_LABEL_DEFINE,		//����
	SOUND_LABEL_JUMP00,		//�W�����v��1
	SOUND_LABEL_JUMP01,		//�W�����v��2
	SOUND_LABEL_LAND,		//���n��
	SOUND_LABEL_LIGHT1,		//��1
	SOUND_LABEL_LIGHT2,		//��2
	SOUND_LABEL_LIGHT3,		//��3
	SOUND_LABEL_HEAVY1,		//��1
	SOUND_LABEL_HEAVY2,		//��2
	SOUND_LABEL_HEAVY3_1,	//��3_1
	SOUND_LABEL_HEAVY3_2,	//��3_2
	SOUND_LABEL_HURT,		//��e
	SOUND_LABEL_SLAY,		//�E�Q
	SOUND_LABEL_PHURT,		//����e
	SOUND_LABEL_THURT,		//����e
	SOUND_LABEL_FALL,		//����
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
