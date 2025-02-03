//************************************************
//
//�e���������A�w�b�_�t�@�C��[shadow.h]
//Author�F���c����
//
//************************************************
#ifndef _SHADOW_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _SHADOW_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�{�c�e�T�C�Y�v���Z�b�g
enum ShadowStyle
{
	ShadowStyleSmall = 0,
	ShadowStyleMiddle,
	ShadowStyleLarge,
	ShadowStyleMax
};

//�e�\����
struct Shadow
{
	int nIdx;			//�ԍ�
	bool bUse;			//�g�p����
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3* pPos;	//�Ǐ]�Ώۂ̈ʒu
	D3DXVECTOR3 rot;	//����(���z�̐i�s�����Ȃǂ�)
	float fSize;		//�e�T�C�Y
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
};

//�v���g�^�C�v�錾
void InitShadow(void);	//����
void UninitShadow(void);	//�j��
void SetInfoShadow(float fSize, D3DXVECTOR3* pPos);	//�ݒ�
void SetSizeShadow(int nCnt, int mode);	//�T�C�Y�Z�b�g
void UpdateShadow(int mode);	//�X�V
void DisappearShadow(D3DXVECTOR3* pos);	//�I��
void DrawShadow(void);	//�`��

#endif