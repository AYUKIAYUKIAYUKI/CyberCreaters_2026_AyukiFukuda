//************************************************
//
//���U���g�̏��ʕ\�������A�w�b�_�t�@�C��[grade.h]
//Author�F���c����
//
//************************************************
#ifndef _GRADE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _GRADE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_GRADE_1	"data\\TEX\\01_menu\\"

#define AMOUNT_POLYGON_GRADE	(5)	//�|���S����
#define AMOUNT_TEXTURE_GRADE	(1)	//�Ǎ��݃e�N�X�`����

typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	float fSpanX;		//�T�C�Y
	float fSpanY;		//�T�C�Y
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�F
}GRADE;

//�v���g�^�C�v�錾
void Init_Grade(void);
void Uninit_Grade(void);
void Update_Grade(void);
void Draw_Grade(void);
void Setinfo_Grade(void);

#endif