//************************************************
//
//�Փ˔���A�w�b�_�t�@�C��[collision.h]
//Author�F���c����
//
//************************************************
#ifndef _COLLISION_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _COLLISION_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

typedef enum
{
	Xside = 0,
	Zside,
	OnlyVtx,
	Bothside,
	CollisionMax
}CollisionType;

//�v���g�^�C�v�錾
bool CollisionSphere(const D3DXVECTOR3 obj1, const float radius1, const D3DXVECTOR3 obj2, const float radius2);	//�����m�̏Փ˔���
bool CollisionAABB(const COLLISION_AABB obj1, const COLLISION_AABB obj2);   //AABB���m�̏Փ˔���
int CollisionAABB_Vtx(COLLISION_AABB obj1, const COLLISION_AABB obj2);	//AABB�̂ǂ̖ʂ��G��Ă��邩����

#endif