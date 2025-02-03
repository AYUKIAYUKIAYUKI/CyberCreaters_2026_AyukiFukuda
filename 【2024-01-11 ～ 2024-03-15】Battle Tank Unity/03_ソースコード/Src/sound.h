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
	SOUND_LABEL_CLICK = 0,	//���艹
	SOUND_LABEL_CANCEL,	//�L�����Z����
	SOUND_LABEL_CURSORMOVE,	//�J�[�\���ړ�
	SOUND_LABEL_NOMALGUNSHOT,	//�ʏ�̎ˌ���
	SOUND_LABEL_ROCKETLAUNCERSHOT,	//���P�����̎ˌ���
	SOUND_LABEL_MACHINEGUNSHOT,	//�}�V���K���ˌ���
	SOUND_LABEL_SHOTGUNSHOT,	//�V���b�g�K���̎ˌ���
	SOUND_LABEL_PICK_WEAPON,	//���푕�����̉�
	SOUND_LABEL_PLAYERHIT,		//��e��
	SOUND_LABEL_PLAYERDEAD,		//���S��
	SOUND_LABEL_EXPLOSION,		//������
	SOUND_LABEL_EXPLOSION_1,	//��������鎞�̉�
	SOUND_LABEL_TELEPORT,		//�{�X�̃e���|�[�g�����Ƃ��̉�
	SOUND_LABEL_FADE_OPEN,		//�t�F�[�h�I�[�v�����鎞�̉�
	SOUND_LABEL_FADE_GEAR,		//�t�F�[�h�̃M�A�ғ���
	SOUND_LABEL_TITLE_BGM,		//�^�C�g��BGM	
	SOUND_LABEL_TUTORIAL_BGM,	//�`���[�g���A��BGM
	SOUND_LABEL_GAME_BGM,		//�Q�[����BGM
	SOUND_LABEL_RESULT_RANKING_BGM,	//�����L���O�A���U���gBGM
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
