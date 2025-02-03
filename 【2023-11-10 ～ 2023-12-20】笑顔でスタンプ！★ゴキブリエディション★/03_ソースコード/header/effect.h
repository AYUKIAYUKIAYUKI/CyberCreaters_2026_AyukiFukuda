//************************************************
//
//�G�t�F�N�g���������A�w�b�_�t�@�C��[billboard.h]
//Author�F���c����
//
//************************************************
#ifndef _EFFECT_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _EFFECT_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�G�t�F�N�g�̎��
enum EffectStyle
{
	EffectStyleBullet = 0,
	EffectStyleMax
};

//�G�t�F�N�g�\����
struct Effect
{
	bool bUse;			//�g�p����
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����(���z�̐i�s�����Ȃǂ�)
	D3DXCOLOR col;		//�F
	float fDecrease;	//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
};

//�v���g�^�C�v�錾
void InitEffect(void);	//����
void UninitEffect(void);	//�j��
void SetInfoEffect(int nStyle, D3DXVECTOR3 pos, D3DXCOLOR col);	//�ݒ�
void SetSizeEffect(int nCnt);	//�T�C�Y�Z�b�g
void UpdateEffect(void);	//�X�V
void SetColEffect(int nCnt);	//�J���[�����O
void DisappearEffect(int nCnt);	//����
void DrawEffect(void);	//�`��

#endif