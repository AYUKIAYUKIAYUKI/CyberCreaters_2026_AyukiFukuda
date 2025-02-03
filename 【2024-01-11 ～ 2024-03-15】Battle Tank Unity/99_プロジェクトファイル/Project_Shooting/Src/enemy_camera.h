#ifdef _DEBUG	// ��ԉ��܂�

//************************************************
//
// �G�ҏW�J�����A�w�b�_�t�@�C��[enemy_camera.h]
// Author�F���c����
//
//************************************************
#ifndef _ENEMY_CAMERA_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _ENEMY_CAMERA_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� /*/
#include "main.h"

// �G�ҏW�J�������p
typedef struct
{
	D3DXVECTOR3 posV;			// �J�����̍��W
	D3DXVECTOR3 posR;			// �����_�̍��W
	D3DXVECTOR3 rot;			// ���݂̌���
	D3DXVECTOR3 rot_goal;		// �ڕW�̌���
	float distance;				// ���_�ƒ����_�̋���
	D3DXVECTOR3 vecU;			// ������x�N�g��
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	D3DVIEWPORT9 viewport;		// �r���[�|�[�g
} ENC;

/*/ �v���g�^�C�v�錾 /*/
void Init_ENC(void);							// ����
void Update_ENC(void);							// �X�V
void CalcPosV_ENC(const D3DXVECTOR3 target);	// ���_���Z�o
void CalcPosR_ENC(const D3DXVECTOR3 target);	// �����_���Z�o
void SetInfo_ENC(void);							// �J�����Z�b�g
ENC* GetInfo_ENC(void);							// �J�������擾

#endif	// _ENEMY_CAMERA_H_

#endif	// _DEBUG