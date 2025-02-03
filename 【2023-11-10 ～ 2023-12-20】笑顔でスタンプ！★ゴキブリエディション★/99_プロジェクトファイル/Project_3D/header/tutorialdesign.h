//************************************************
//
//�`���[�g���A���f�U�C���A�w�b�_�t�@�C��[tutorialdesign.h]
//Author�F���c����
//
//************************************************
#ifndef _TUTORIALDESIGN_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TUTORIALDESIGN_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�`���[�g���A���\���p
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	float sizeX;
	float sizeY;
	float F;
}TutorialDesign;

//�v���g�^�C�v�錾
void InitTutorialDesign(void);	//����
void SetInfoTutorialDesign(void);	//�ݒ�
void UninitTutorialDesign(void);	//�j��
void UpdateTutorialDesign(void);	//�X�V
void SetSizeTutorialDesign(void);	//�W�J
void UpdateColTutorialDesign(void);	//�F�ύX
void DrawTutorialDesign(void);	//�`��1
bool* GetInfoSpawnEnemy(void);	//�G���킭���ǂ�������
bool* GetInfoStampEnemy(void);	//�G���Ԃ���������

#endif