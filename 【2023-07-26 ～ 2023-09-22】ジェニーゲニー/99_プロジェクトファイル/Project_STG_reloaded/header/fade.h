//************************************************
//
//���j���[�t�F�[�h�����A�w�b�_�t�@�C��[fade.h]
//Author�F���c����
//
//************************************************
#ifndef _FADE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _FADE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_BLACK_FADE_MENU	"data\\TEX\\01_menu\\blackbase.png"

#define AMOUNT_POLYGON_FADE_MENU	(1)	//�|���S����
#define AMOUNT_TEXTURE_FADE_MENU	(1)	//�Ǎ��݃e�N�X�`����

typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�F
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}FADE_MENU_OBJECT;

//�v���g�^�C�v�錾
void Init_Fade_Menu(void);
void Uninit_Fade_Menu(void);
void Update_Fade_Menu(void);
void Draw_Fade_Menu(void);
void Setinfo_Fade_Menu(void);
float* Getinfo_Fade_Menu(void);

#endif