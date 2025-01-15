//************************************************
//
//���j���[�\�������A�w�b�_�t�@�C��[menu.h]
//Author�F���c����
//
//************************************************
#ifndef _MENU_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _MENU_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_WHITE_MENU	"data\\TEX\\01_menu\\whitebase.png"

#define AMOUNT_POLYGON_MENU	(1)	//�|���S����
#define AMOUNT_TEXTURE_MENU	(1)	//�Ǎ��݃e�N�X�`����

typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�F
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}MENU_OBJECT;

//�v���g�^�C�v�錾
void Init_Menu(void);
void Uninit_Menu(void);
void Update_Menu(void);
void Draw_Menu(void);
void Setinfo_Menu(void);
bool* Getinfo_Tutorial_Menu(void);
bool* Getinfo_Menu(void);

#endif