//************************************************
//
//�p�[�e�B�N�����������A�w�b�_�t�@�C��[billboard.h]
//Author�F���c����
//
//************************************************
#ifndef _PARTICLE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PARTICLE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

////�p�[�e�B�N���̎��
//enum ParticleStyle
//{
//	ParticleStyleBullet = 0,
//	ParticleStyleEnemy,
//	ParticleStyleMax
//};

//�p�[�e�B�N���\����
struct Particle
{
	bool bUse;			//�g�p����
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����(���z�̐i�s�����Ȃǂ�)
	D3DXCOLOR col;		//�F
	float fSize;		//�T�C�Y
	float fDecrease;	//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
};

//�v���g�^�C�v�錾
void InitParticle(void);	//����
void UninitParticle(void);	//�j��
void SetInfoParticle(D3DXVECTOR3 pos, D3DXCOLOR col, float fSize);	//�ݒ�
void SetSizeParticle(int nCnt);	//�T�C�Y�Z�b�g
void UpdateParticle(void);	//�X�V
void SetColParticle(int nCnt);	//�J���[�����O
void DisappearParticle(int nCnt);	//����
void DrawParticle(void);	//�`��

#endif