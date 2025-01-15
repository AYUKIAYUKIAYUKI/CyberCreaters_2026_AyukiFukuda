//************************************************
//
//�`���[�g���A���Ñ����[�h�I���A�w�b�_�t�@�C��[tutorial_select.h]
//Author�F���c����
//
//************************************************
#ifndef _TUTORIAL_SELECT_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TUTORIAL_SELECT_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_TUTORIAL_SELECT_YES	"data\\TEX\\01_menu\\yes.png"
#define	TEXTURE_TUTORIAL_SELECT_NO	"data\\TEX\\01_menu\\no.png"

#define AMOUNT_POLYGON_TUTORIAL_SELECT	(2)	//�|���S����
#define AMOUNT_TEXTURE_TUTORIAL_SELECT	(2)	//�Ǎ��݃e�N�X�`����

typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	float fSpanX;		//�T�C�Y
	float fSpanY;		//�T�C�Y
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�F
	float colA;
}TUTORIAL_SELECT;

//�v���g�^�C�v�錾
void Init_Tutorial_Select(void);
void Uninit_Tutorial_Select(void);
void Update_Tutorial_Select(void);
void Draw_Tutorial_Select(void);
void Setinfo_Tutorial_Select(void);

#endif