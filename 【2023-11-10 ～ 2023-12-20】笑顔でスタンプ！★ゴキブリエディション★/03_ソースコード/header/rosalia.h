//************************************************
//
//���U���A���������A�w�b�_�t�@�C��[rosalia.h]
//Author�F���c����
//
//************************************************
#ifndef _ROSALIA_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _ROSALIA_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//���U���A�\����
struct Rosalia
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����(���z�̐i�s�����Ȃǂ�)
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
};

//�v���g�^�C�v�錾
void InitRosalia(void);	//����
void UninitRosalia(void);	//�j��
void UpdateRosalia(void);	//�X�V
void SetSizeRosalia(void);	//�T�C�Y�Z�b�g
void DrawRosalia(void);	//�`��

#endif