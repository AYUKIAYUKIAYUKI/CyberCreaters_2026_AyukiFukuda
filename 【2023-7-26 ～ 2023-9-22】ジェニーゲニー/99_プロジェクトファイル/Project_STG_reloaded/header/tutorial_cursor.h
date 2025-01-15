//************************************************
//
//�`���[�g���A���Ñ��̃J�[�\�������A�w�b�_�t�@�C��[tutorial_cursor.h]
//Author�F���c����
//
//************************************************
#ifndef _TUTORIAL_CURSOR_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TUTORIAL_CURSOR_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_TUTORIAL_CURSOR	"data\\TEX\\01_menu\\cursor.png"

#define AMOUNT_POLYGON_TUTORIAL_CURSOR	(1)	//�|���S����
#define AMOUNT_TEXTURE_TUTORIAL_CURSOR	(1)	//�Ǎ��݃e�N�X�`����

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
	int nCntStop;		//�~�܂鎞��
	bool bTurn;			//�߂锻��
	float colA;
}TUTORIAL_CURSOR;

//�v���g�^�C�v�錾
void Init_Tutorial_Cursor(void);
void Uninit_Tutorial_Cursor(void);
void Update_Tutorial_Cursor(void);
void Draw_Tutorial_Cursor(void);
void Setinfo_Tutorial_Cursor(void);
void Animation_Tutorial_Cursor(void);
int* Getinfo_Choose_YesNo(void);

#endif