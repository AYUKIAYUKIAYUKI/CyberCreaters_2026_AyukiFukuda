//************************************************
//
//�n�ʐ��������A�w�b�_�t�@�C��[field.h]
//Author�F���c����
//
//************************************************
#ifndef _FIELD_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _FIELD_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�n�ʍ\����
struct Field
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
};

//�v���g�^�C�v�錾
void InitField(void);	//����
void UninitField(void);	//�j��
void UpdateField(void);	//�X�V
void DrawField(void);	//�`��

#endif