//************************************************
//
//�e�A�w�b�_�t�@�C��[bullet.h]
//Author�F���c����
//
//************************************************
#ifndef _BULLET_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _BULLET_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`
#define AMOUNT_BULLET	(256)	//�e��
#define SPAN_BULLET	(2.0f)	//�e�̑傫��
#define SPD_BULLET	(7.0f)	//�e�̑���

//�e�����ɓ��������̂���ޕ���
enum CollisionMode
{
	CollisionModeEnemy = 0,
	CollisionModeWall,
	CollisionModeMax
};

//�e�\����
struct Bullet
{
	bool bUse;			//�g�p����
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
	float fPA;			//�Ɋp
	float fRadius;		//���a
	int nRemain;		//�c��
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nIdxShadow;
};

//�v���g�^�C�v�錾
void InitBullet(void);		//����
void UninitBullet(void);	//�j��
void SetInfoBullet(void);	//�ݒ�
void UpdateBullet(void);	//�X�V
void DisappearBullet(int nCnt);	//����
void DrawBullet(void);		//�`��
void CollisionBullet(int nMode, int nCnt);	//�����蔻��
Bullet* GetInfoBullet(void);	//�e�����擾

#endif