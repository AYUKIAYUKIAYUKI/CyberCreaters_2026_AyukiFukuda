//************************************************
//
//�ǐ��������A�w�b�_�t�@�C��[wall.h]
//Author�F���c����
//
//************************************************
#ifndef _WALL_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _WALL_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"
#include "collision.h"

//�Ǎ\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
	D3DXVECTOR3 span;	//�T�C�Y
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	COLLISION_AABB aabb;	//AABB
}Wall;

//�v���g�^�C�v�錾
void InitWall(void);	//����
void UninitWall(void);	//�j��
void UpdateWall(void);	//�X�V
void UpdateWallAABB(void);	//AABB
void CollisionWall(void);	//�����蔻��
void DrawWall(void);	//�`��

#endif