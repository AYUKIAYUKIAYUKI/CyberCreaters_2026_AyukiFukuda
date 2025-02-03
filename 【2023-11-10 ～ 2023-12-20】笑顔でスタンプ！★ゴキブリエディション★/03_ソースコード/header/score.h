//************************************************
//
//�X�R�A�����A�w�b�_�t�@�C��[score.h]	(���K�V�[)
//Author�F���c����
//
//************************************************
#ifndef _SCORE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _SCORE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`
#define	TEXTURE_BLACK_SCORE	"data\\texture\\blackbase.png"
#define	TEXTURE_NUMBER_SCORE	"data\\texture\\NUM.png"
#define TEXTURE_SYMBOL_SCORE	"data\\texture\\timer000.png"

#define AMOUNT_POLYGON_SCORE	(8)	//�|���S����
#define AMOUNT_TEXTURE_SCORE	(3)	//�e�N�X�`����

#define AMOUNT_USING_POLYGON_NUMBER_SCORE	(6)	//�����Ɏg���Ă�|���S����

#define POS_X_LEFT_SCORE	(1900.0f)	//X���W�̍��p
#define POS_X_RIGHT_SCORE	(1950.0f)	//X���W�̉E�p
#define POS_Y_UP_SCORE	(30.0f)			//Y���W�̏�p
#define POS_Y_DOWN_SCORE	(105.0f)	//Y���W�̉��p

#define TEX_U_RIGHT_SCORE	(0.1f)	//U���W�̉E�p

#define DISTANCESPAN_POLYGON_SCORE	(30.0f)	//�|���S������ׂ�Ԋu
#define MOVE_SPAN_TEX_SCORE	(0.1f)			//�e�N�X�`������

#define AMOUNT_MAX_SCORE	(999999)	//�X�R�A���

//�v���g�^�C�v�錾
void Init_Score(void);
void Uninit_Score(void);
void Update_Score(void);
void Draw_Score(void);
void SetPos_Vtx_Score(void);
void Calc_Score(void);
void Add_Score(int Add);
void Animation_Score(void);
void ReSetPos_Vtx_Score(void);
void SaveScore(void);	//�X�R�A�L�^

#endif