//************************************************
//
//�f�o�b�O�\���p�X�N���[���o�[�A�w�b�_�t�@�C��[debugscroll.h]
//Author�F���c����
//
//************************************************
#ifndef _DEBUGSCROLL_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _DEBUGSCROLL_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`
#define AMOUNT_DEBUGSCROLL	(2)	//�X�N���[���p�|���S����

//�f�o�b�O�X�N���[��
struct DebugScroll
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;		//�F
};

//�v���g�^�C�v�錾
void InitDebugScroll(void);	//����
void UninitDebugScroll(void);	//�j��
void UpdateDebugScroll(void);	//�X�V
void DrawDebugScroll(void);	//�`��

#endif