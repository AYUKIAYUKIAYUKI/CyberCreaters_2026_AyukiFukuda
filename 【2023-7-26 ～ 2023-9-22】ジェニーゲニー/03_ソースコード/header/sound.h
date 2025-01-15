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
	SOUND_LABEL_BGM000 = 0,		// BGM1
	SOUND_LABEL_BGM001,			// BGM2
	SOUND_LABEL_SE_SELECT1,		// �I����1
	SOUND_LABEL_SE_SELECT2,		// ���^�L�I��2
	SOUND_LABEL_SE_PAUSE,		// �|�[�Y��
	SOUND_LABEL_SE_BULLET,		// �e���ˉ�
	SOUND_LABEL_SE_DAMAGE,		// �q�b�g��
	SOUND_LABEL_SE_EXPLOSION,	// ������
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
