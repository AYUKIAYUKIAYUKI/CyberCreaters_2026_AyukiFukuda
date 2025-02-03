//************************************************
//
// �{�X�̒e�A�w�b�_�t�@�C��[boss_bullet.h]
// Author�F�����h��
//
//************************************************
#ifndef _BOSS_BULLET_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _BOSS_BULLET_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

//include
#include "main.h"

//�}�N����`
#define MAX_BOSSBULLET (32)		// �{�X�̒e�̍ő吔
#define MAX_BULLETSIZE	(20)		// �e�̑傫��
#define SHADOWSIZE	(40)			// �e�ɂ��e�̑傫��
#define MAX_VARTEX	(4)				// ���_��

//�{�X�̒e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXVECTOR3 rot;		// ����
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	float fWidth;			// �e�̕�
	float fHeight;			// �e�̍���
	float fLife;			// �e�̎���
	float rad;				// ������p�̃T�C�Y
	bool bUse;				// �g�p���Ă��邩�ǂ���
	int id_sph;				// �����蔻������ԍ�
	int id_shadow;			// �e�̎��ʔԍ�
	int nBulletIndex;		// �e�̔ԍ�
}BOSSBULLET;

// �v���g�^�C�v�錾
void InitBossBullet(void);																			// ����������
void UninitBossBullet(void);																		// �I������
void UpdateBossBullet(void);																		// �X�V����
void DrawBossBullet(void);																			// �`�揈��
void MoveBossBullet(int id);																		// �e�̈ړ�
void CheckUseBossBullet(int id);																	// �e���g�p���Ă��邩�ǂ���
void SetBossBullet(D3DXVECTOR3 pos,D3DXVECTOR3 move,float fLife);									// �e�̐ݒ菈��
BOSSBULLET* GetBullet(void);																		// �e�̏��̎擾
void CollisionBossBullet(int id);																	// �{�X�̒e�ƌ����̓����蔻��
void BossBulletPlayerCollision(int id);																// �{�X�̒e�ƃv���C���[�̓����蔻��
#endif