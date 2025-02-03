//************************************************
//
//���U���g�f�U�C���A�w�b�_�t�@�C��[result.h]
//Author�F���c����
//
//************************************************
#ifndef _RESULTDESIGN_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _RESULTDESIGN_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//���U���g�\���p
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	float sizeX;
	float sizeY;
	float F;
}ResultDesign;

//�v���g�^�C�v�錾
void InitResultDesign(void);	//����
void SetInfoResultDesign(void);	//�ݒ�
void UninitResultDesign(void);	//�j��
void UpdateResultDesign(void);	//�X�V
void SetSizeResultDesign(void);	//�W�J
void UpdateColResultDesign(void);	//�F�ύX
void DrawResultDesign(void);	//�`��

#endif