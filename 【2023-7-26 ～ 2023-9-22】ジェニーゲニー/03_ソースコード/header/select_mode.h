//************************************************
//
//���j���[�̃��[�h�I�������A�w�b�_�t�@�C��[select_mode.h]
//Author�F���c����
//
//************************************************
#ifndef _SELECT_MODE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _SELECT_MODE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_MODE_GAME	"data\\TEX\\01_menu\\gamemode.png"
#define	TEXTURE_MODE_RANK	"data\\TEX\\01_menu\\rankingmode.png"

#define AMOUNT_POLYGON_SELECT_MODE	(2)	//�|���S����
#define AMOUNT_TEXTURE_SELECT_MODE	(2)	//�Ǎ��݃e�N�X�`����

typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	float fSpanX;		//�T�C�Y
	float fSpanY;		//�T�C�Y
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�F
}SELECT_MODE;

//�v���g�^�C�v�錾
void Init_Select_Mode(void);
void Uninit_Select_Mode(void);
void Update_Select_Mode(void);
void Draw_Select_Mode(void);
void Setinfo_Select_Mode(void);

#endif