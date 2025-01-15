//************************************************
//
//�X�R�A(���U���g)�����A�w�b�_�t�@�C��[score_result.h]
//Author�F���c����
//
//************************************************
#ifndef _SCORE_RESULT_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _SCORE_RESULT_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include <stdio.h>
#include "main.h"

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_NUMBER_SCORE_RESULT	"data\\TEX\\02_game\\number001.png"

#define AMOUNT_POLYGON_SCORE_RESULT	(30)	//�|���S����
#define AMOUNT_TEXTURE_SCORE_RESULT	(1)	//�e�N�X�`����

#define AMOUNT_USING_POLYGON_NUMBER_SCORE_RESULT	(6)	//�����Ɏg���Ă�|���S����

#define TEX_U_RIGHT_SCORE_RESULT	(0.1f)	//U���W�̉E�p

#define DISTANCESPAN_POLYGON_SCORE_RESULT	(30.0f)	//�|���S������ׂ�Ԋu
#define MOVE_SPAN_TEX_SCORE_RESULT	(0.1f)			//�e�N�X�`������

typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	float fSpanX;		//�T�C�Y
	float fSpanY;		//�T�C�Y
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�F
}SCORE_RESULT;

//�v���g�^�C�v�錾
void Init_Score_Result(void);
void Uninit_Score_Result(void);
void Update_Score_Result(void);
void Draw_Score_Result(void);
void Setinfo_Score_Result(void);
void SetPos_Vtx_Score_Result(void);

#endif