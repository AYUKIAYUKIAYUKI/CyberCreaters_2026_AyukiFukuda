//************************************************
//
//�����L���O�ɃX�R�A���o���A�w�b�_�t�@�C��[ranking_score.h]
//Author�F���c����
//
//************************************************
#ifndef _RANKING_SCORE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _RANKING_SCORE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include <stdio.h>
#include "main.h"

//�}�N����`

/*�t�@�C���p�X*/
#define	FILE_SET_RANKING	"data\\csv\\Ranking.csv"

/*�摜�p�X*/
#define	TEXTURE_NUMBER_RANKING_SCORE	"data\\TEX\\04_ranking\\number.png"

#define AMOUNT_POLYGON_RANKING_SCORE	(64)	//�|���S����
#define AMOUNT_TEXTURE_RANKING_SCORE	(1)	//�e�N�X�`����

#define AMOUNT_SET_RANKING_SCORE	(5)	//�ǂݍ��ރX�R�A��

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
}RANKING_SCORE;

typedef struct
{
	double lfScore;	//�X�R�A
	int nDigit;	//����
}READ_RANKING_SCORE;

//�v���g�^�C�v�錾
void Init_Ranking_Score(int nMode);
void Uninit_Ranking_Score(void);
void Update_Ranking_Score(void);
void Draw_Ranking_Score(void);
void Readinfo_Ranking_Score(void);
void SetNewinfo_Ranking(void);
void SetTex_Ranking_Score(int nMode);
void Setinfo_Ranking_Score(void);

#endif