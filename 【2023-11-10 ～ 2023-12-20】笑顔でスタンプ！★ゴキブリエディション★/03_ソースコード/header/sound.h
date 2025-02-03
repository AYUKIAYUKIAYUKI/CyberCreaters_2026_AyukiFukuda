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
	SOUND_LABEL_TUTORIAL,	//�`���[�g���A��
	SOUND_LABEL_GAME,	//�Q�[��
	SOUND_LABEL_CHOOSE,	//�I��
	SOUND_LABEL_DEFINE,	//����
	SOUND_LABEL_ATK,	//�U��
	SOUND_LABEL_DAMAGE,	//��e
	SOUND_LABEL_HIT,	//����
	SOUND_LABEL_STAMP,	//�E�Q
	SOUND_LABEL_ROSALIA,	//���L���L�}�b�N�X���[�h
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
float* GetInfoSoundVol(void);	//���ʏ����擾
void SetInfoSoundVol(int label);	//���ʂ�ݒ�

#endif
