//************************************************
//
//���b�V���t�B�[���h���������A�w�b�_�t�@�C��[meshfield.h]
//Author�F���c����
//
//************************************************
#ifndef _MESHFIELD_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _MESHFIELD_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//���b�V���t�B�[���h�\����
struct Meshfield
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
};

//�v���g�^�C�v�錾
void InitMeshfield(void);	//����
void UninitMeshfield(void);	//�j��
void UpdateMeshfield(void);	//�X�V
void DrawMeshfield(void);	//�`��

#endif