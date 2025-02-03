//************************************************
//
//���f���A�w�b�_�t�@�C��[model.h]
//Author�F���c����
//
//************************************************
#ifndef _MODEL_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _MODEL_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//���f���\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	COLLISION_AABB aabb;	//AABB�Փ˔���p
	int nIdxShadow;
}Model;

//�v���g�^�C�v�錾
void InitModel(int mode);	//����
void UninitModel(void);	//�j��
void UpdateModel(void);	//�X�V
void UpdateModelAABB(void);	//AABB�X�V
void CollisionModel(void);	//�����蔻��
void DrawModel(void);	//�`��
Model* GetInfoModel(void);

#endif