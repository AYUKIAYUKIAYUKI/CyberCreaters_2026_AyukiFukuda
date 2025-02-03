//************************************************
//
//�^�C�g���f�U�C���A�w�b�_�t�@�C��[titledesign.h]
//Author�F���c����
//
//************************************************
#ifndef _TITLEDESIGN_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TITLEDESIGN_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�^�C�g���\���p
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	float sizeX;
	float sizeY;
	float F;
}TitleDesign;

//�v���g�^�C�v�錾
void InitTitleDesign(void);	//����
void SetInfoTitleDesign(void);	//�ݒ�
void UninitTitleDesign(void);	//�j��
void UpdateTitleDesign(void);	//�X�V
void SetSizeTitleDesign(void);	//�W�J
void UpdateColTitleDesign(void);	//�F�ύX
void DrawTitleDesign(void);	//�`��
MODE GetChooseMode(void);	//���I��ł�

#endif