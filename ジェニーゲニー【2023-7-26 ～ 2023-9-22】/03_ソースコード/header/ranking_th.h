//************************************************
//
//���ʂ̂�A�w�b�_�t�@�C��[ranking_th.h]
//Author�F���c����
//
//************************************************
#ifndef _RANKING_TH_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _RANKING_TH_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"
#include "ranking.h"

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_RANKING_1ST	"data\\TEX\\04_ranking\\1st.png"
#define	TEXTURE_RANKING_2ND	"data\\TEX\\04_ranking\\2nd.png"
#define	TEXTURE_RANKING_3RD	"data\\TEX\\04_ranking\\3rd.png"
#define	TEXTURE_RANKING_4TH	"data\\TEX\\04_ranking\\4th.png"
#define	TEXTURE_RANKING_5TH	"data\\TEX\\04_ranking\\5th.png"
#define	TEXTURE_RANKING_YOURS	"data\\TEX\\04_ranking\\yours.png"

#define AMOUNT_POLYGON_RANKING_TH	(6)	//�|���S����
#define AMOUNT_TEXTURE_RANKING_TH	(6)	//�e�N�X�`����

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
}RANKING_TH;

//�v���g�^�C�v�錾
void Init_Ranking_TH(int nMode);
void Uninit_Ranking_TH(void);
void Update_Ranking_TH(void);
void Draw_Ranking_TH(void);
void Setinfo_Ranking_TH(int nMode);

#endif