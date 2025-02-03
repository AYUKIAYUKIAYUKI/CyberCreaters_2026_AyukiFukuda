//************************************************
//
//�J�����A�w�b�_�t�@�C��[camera.h]
//Author�F���c����
//
//************************************************
#ifndef _CAMERA_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _CAMERA_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�J�����\����
struct Camera
{
	D3DXVECTOR3 posV;	//�ʒu
	D3DXVECTOR3 posR;	//�����_
	D3DXVECTOR3 rot;	//���݂̌���
	D3DXVECTOR3 rotGoal;//�ڕW�̌���
	float fPA;			//���݂̋Ɋp
	float fPAGoal;		//�ڕW�̋Ɋp
	float fDistance;	//���_�ƒ����_�̋���
	bool bTrack;		//�Ώە��ύX
	D3DXVECTOR3 vecU;	//������x�N�g��
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
};

//�v���g�^�C�v�錾
void InitCamera(void);	//����
void UninitCamera(void);	//�j��
void UpdateCamera(int mode);	//�X�V
void CalcPosV(const D3DXVECTOR3 target);	//���_���Z�o
void CalcPosR(const D3DXVECTOR3 target);	//�����_���Z�o
void SetInfoCamera(int mode);	//�J�����Z�b�g
Camera* GetInfoCamera(void);	//�J�������擾

#endif