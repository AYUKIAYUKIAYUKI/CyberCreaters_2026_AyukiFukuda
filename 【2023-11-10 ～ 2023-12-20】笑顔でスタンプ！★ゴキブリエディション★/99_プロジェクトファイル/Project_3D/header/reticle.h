//************************************************
//
//���e�B�N���A�w�b�_�t�@�C��[reticle.h]
//Author�F���c����
//
//************************************************
#ifndef _RETICLE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _RETICLE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`
#define	TEXTURE_RETICLE	"data\\texture\\250.png"

//�r���{�[�h�\����
struct Reticle
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����(���z�̐i�s�����Ȃǂ�)
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
};

//�v���g�^�C�v�錾
void InitReticle(void);	//����
void UninitReticle(void);	//�I��
void SizeSetReticle(void);	//�W�J
void UpdateReticle(void);	//�X�V
void DrawReticle(void);	//�`��
Reticle* GetInfoReticle(void);	//�擾

#endif