//************************************************
//
//���C�A�w�b�_�t�@�C��[ray.h]
//Author�F���c����
//
//************************************************
#ifndef _RAY_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _RAY_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//���C�\����
struct Ray
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
	float fPA;			//�Ɋp
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
};

//�v���g�^�C�v�錾
void InitRay(void);	//����
void UninitRay(void);	//�j��
void UpdateRay(void);	//�X�V
void DrawRay(void);	//�`��

#endif