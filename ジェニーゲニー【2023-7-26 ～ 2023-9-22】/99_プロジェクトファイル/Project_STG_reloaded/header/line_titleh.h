//************************************************
//
//�^�C�g���̐������A�w�b�_�t�@�C��[Line_title.h]
//Author�F���c����
//
//************************************************
#ifndef _LINE_TITLE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _LINE_TITLE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

#define AMOUNT_POLYGON_LINE_TITLE	(1024)	//�|���S����

typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	float fSpanX;		//�T�C�Y
	float fSpanY;		//�T�C�Y
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�F
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}LINE_TITLE;

//�v���g�^�C�v�錾
void Init_Line_title(void);
void Uninit_Line_title(void);
void Update_Line_title(void);
void Draw_Line_title(void);
void Setinfo_Line_title(void);

#endif