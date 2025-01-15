//************************************************
//
//�����L���O�A�w�b�_�t�@�C��[ranking.h]
//Author�F���c����
//
//************************************************
#ifndef _RANKING_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _RANKING_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_RANKING_BG	"data\\TEX\\04_ranking\\BG_demo000.png"

#define AMOUNT_POLYGON_RANKING	(1)	//�|���S����
#define AMOUNT_TEXTURE_RANKING	(1)	//�e�N�X�`����

typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�F
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}RANKING;

//�v���g�^�C�v�錾
void Init_Ranking(int nMode);
void Uninit_Ranking(void);
void Update_Ranking(void);
void Draw_Ranking(void);
void Setinfo_Ranking(void);
bool* Getinfo_Ranking(void);

#endif