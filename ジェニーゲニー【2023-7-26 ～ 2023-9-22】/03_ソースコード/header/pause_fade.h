//************************************************
//
//�|�[�Y�t�F�[�h�����A�w�b�_�t�@�C��[pause_fade.h]
//Author�F���c����
//
//************************************************
#ifndef _PAUSE_FADE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PAUSE_FADE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_BLACK_PAUSE_FADE	"data\\TEX\\01_menu\\blackbase.png"

#define AMOUNT_POLYGON_PAUSE_FADE	(1)	//�|���S����
#define AMOUNT_TEXTURE_PAUSE_FADE	(1)	//�Ǎ��݃e�N�X�`����

typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�F
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}PAUSE_FADE;

//�v���g�^�C�v�錾
void Init_Pause_Fade(void);
void Uninit_Pause_Fade(void);
void Update_Pause_Fade(void);
void Draw_Pause_Fade(void);
void Setinfo_Pause_Fade(void);
float* Getinfo_Pause_Fade(void);

#endif