//************************************************
//
//���j���[�̃e�L�X�g�\�������A�w�b�_�t�@�C��[text_mode.h]
//Author�F���c����
//
//************************************************
#ifndef _TEXT_MODE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TEXT_MODE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_CHOOSE_MODE	"data\\TEX\\01_menu\\choosingmode.png"
#define	TEXTURE_WINDOW_MODE	"data\\TEX\\01_menu\\window.png"

#define AMOUNT_POLYGON_TEXT_MODE	(2)	//�|���S����
#define AMOUNT_TEXTURE_TEXT_MODE	(2)	//�Ǎ��݃e�N�X�`����

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
	float fSPD_X;
}TEXT_MODE;

//�v���g�^�C�v�錾
void Init_Text_Mode(void);
void Uninit_Text_Mode(void);
void Update_Text_Mode(void);
void Draw_Text_Mode(void);
void Setinfo_Text_Mode(void);

#endif