//************************************************
//
//�|�[�Y�f�U�C���A�w�b�_�t�@�C��[pausedesign.h]
//Author�F���c����
//
//************************************************
#ifndef _TUTORIALDESIGN_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TUTORIALDESIGN_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�|�[�Y�\���p
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	float sizeX;
	float sizeY;
	float F;
}Pause;

//�v���g�^�C�v�錾
void InitPause(void);	//����
void SetInfoPause(void);	//�ݒ�
void UninitPause(void);	//�j��
void UpdatePause(void);	//�X�V
void SetSizePause(void);	//�W�J
void UpdateColPause(void);	//�F�ύX
void DrawPause(void);	//�`��
MODE GetInfoChoosePause(void);	//�|�[�Y�I��

#endif