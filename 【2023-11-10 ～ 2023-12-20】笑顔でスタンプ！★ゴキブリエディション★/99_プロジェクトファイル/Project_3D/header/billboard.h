//************************************************
//
//�r���{�[�h���������A�w�b�_�t�@�C��[billboard.h]
//Author�F���c����
//
//************************************************
#ifndef _BILLBOARD_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _BILLBOARD_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�r���{�[�h�\����
struct Billboard
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����(���z�̐i�s�����Ȃǂ�)
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
};

//�v���g�^�C�v�錾
void InitBillboard(void);	//����
void UninitBillboard(void);	//�j��
void UpdateBillboard(void);	//�X�V
void DrawBillboard(void);	//�`��

#endif