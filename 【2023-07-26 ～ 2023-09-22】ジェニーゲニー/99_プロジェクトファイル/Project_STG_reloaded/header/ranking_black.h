//************************************************
//
//�����L���O�ɍ��_���o���A�w�b�_�t�@�C��[ranking_black.h]
//Author�F���c����
//
//************************************************
#ifndef _RANKING_BLACK_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _RANKING_BLACK_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"
#include "ranking.h"

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_RANKING_BLACK	"data\\TEX\\01_menu\\blackbase.png"

#define AMOUNT_POLYGON_RANKING_BLACK	(6)	//�|���S����
#define AMOUNT_TEXTURE_RANKING_BLACK	(1)	//�e�N�X�`����

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
	float colA;
}RANKING_BLACK;

//�v���g�^�C�v�錾
void Init_Ranking_Black(int nMode);
void Uninit_Ranking_Black(void);
void Update_Ranking_Black(void);
void Draw_Ranking_Black(void);
void Setinfo_Ranking_Black(int nmode);

#endif