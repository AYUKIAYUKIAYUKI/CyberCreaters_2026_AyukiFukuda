//************************************************
//
//�������ԏ����A�w�b�_�t�@�C��[timer.h]	(���K�V�[)
//Author�F���c����
//
//************************************************
#ifndef _TIMER_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TIMER_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`
#define	TEXTURE_BLACK_TIMER	"data\\texture\\blackbase.png"
#define	TEXTURE_NUMBER_TIMER	"data\\texture\\NUM.png"
#define TEXTURE_NUMBER_SUB_TIMER	"data\\texture\\NOTNUM.png"
#define TEXTURE_CLOCK_TIMER	"data\\texture\\timer000.png"

#define AMOUNT_POLYGON_TIMER	(10)	//�|���S����
#define AMOUNT_TEXTURE_TIMER	(4)		//�Ǎ��݃e�N�X�`����

#define AMOUNT_USING_POLYGON_NUMBER_TIMER	(6)	//�����Ɏg���Ă�|���S����
#define AMOUNT_USING_POLYGON_SYMBOL_TIMER	(2)	//�L���Ɏg���Ă�|���S����

#define TEX_U_RIGHT_TIMER	(0.1f)	//U���W�̉E�p

#define DISTANCESPAN_POLYGON_TIMER	(30.0f)		//�����|���S������ׂ�Ԋu
#define MORE_DISTANCESPAN_POLYGON_TIMER	(20.0f)	//����ɊԊu����

#define DISTANCESPAN_POLYGON_SYMBOL_TIMER	(82.5f)	//�L���̃|���S���Ԋu

#define MOVE_SPAN_TEX_TIMER	(0.1f)	//�e�N�X�`������

#define REMAIN_TIMER	(90)			//�Q�[���̎c�莞��
#define AMOUNT_CNT_MAX_TIMER	(60)	//1�b���炷�̂ɕK�v�ȃJ�E���g(�t���[��)��
#define INVERSION_TIMER	(44)			//���]�ɂ����鎞��
#define REINVERSION_TIMER	(73)		//�Ĕ��]�ɂ����鎞��

//�v���g�^�C�v�錾(��)
void Init_Timer(void);
void Uninit_Timer(void);
void Update_Timer(void);
void Draw_Timer(void);
void SetPos_Vtx_Timer(void);
int* Getinfo_Timer(void);
bool* Getinfo_Inversion_Timer(void);
bool* Getinfo_ReInversion_Timer(void);

#endif