//************************************************
//
//�����L���O�t�F�[�h�����A�w�b�_�t�@�C��[ranking_fade.h]
//Author�F���c����
//
//************************************************
#ifndef _RANKING_FADE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _RANKING_FADE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_BLACK_RANKING_FADE	"data\\TEX\\01_menu\\blackbase.png"

#define AMOUNT_POLYGON_RANKING_FADE	(1)	//�|���S����
#define AMOUNT_TEXTURE_RANKING_FADE	(1)	//�Ǎ��݃e�N�X�`����

typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�F
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}RANKING_FADE;

//�v���g�^�C�v�錾
void Init_Ranking_Fade(void);
void Uninit_Ranking_Fade(void);
void Update_Ranking_Fade(void);
void Draw_Ranking_Fade(void);
void Setinfo_Ranking_Fade(void);
float* Getinfo_Ranking_Fade(void);

#endif