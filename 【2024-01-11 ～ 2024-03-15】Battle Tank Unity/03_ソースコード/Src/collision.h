//************************************************
//
// �Փ˔���A�w�b�_�t�@�C��[collision.h]
// Author�F���c����
//
//************************************************
#ifndef _COLLISION_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _COLLISION_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*---�y�C���N���[�h�t�@�C���z---*/
#include "main.h"

/*---�y�v���g�^�C�v�錾�z---*/
bool CollisionSph(D3DXVECTOR3 sph1, float r1,
	D3DXVECTOR3 sph2, float r2);	// �����m�̏Փ˔���

bool CollisionSphAABB(D3DXVECTOR3 sph,
	float r, COLLISION_AABB box);	// ����AABB�̓����蔻��

bool CollisionAABB(COLLISION_AABB box1,
	COLLISION_AABB box2);			// AABB���m�̏Փ˔���

void CollisionVecSphAABB(int id, D3DXVECTOR3 sph,
	float r, COLLISION_AABB box);	// ����AABB�̏Փ˔���Ɖ�������(��)

#endif