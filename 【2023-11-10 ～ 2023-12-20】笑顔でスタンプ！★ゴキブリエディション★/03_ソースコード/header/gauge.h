//************************************************
//
//�Q�[�W�A�w�b�_�t�@�C��[gauge.h]
//Author�F���c����
//
//************************************************
#ifndef _GAUGE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _GAUGE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�`���[�g���A���\���p
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	float sizeX;
	float sizeY;
	float F;
}Gauge;

//�v���g�^�C�v�錾
void InitGauge(void);	//����
void SetInfoGauge(void);	//�ݒ�
void UninitGauge(void);	//�j��
void UpdateGauge(void);	//�X�V
void SetSizeGauge(void);	//�W�J
void UpdateColGauge(void);	//�F�ύX
void DrawGauge(void);	//�`��

#endif