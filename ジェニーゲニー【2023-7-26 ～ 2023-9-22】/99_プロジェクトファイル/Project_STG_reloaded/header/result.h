//************************************************
//
//���U���g�\�������A�w�b�_�t�@�C��(�r��n)[result.h]
//Author�F���c����
//
//************************************************
#ifndef _RESULT_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _RESULT_H _	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "../header/main.h"

//�}�N����`
#define AMT_PLG_RESULT	(4)				//�|���S���̒��_��	
#define AMT_TRI_RESULT	(2)				//�|���S���̐�
#define RELATIVE_X_RESULT	(990.0f)	//X���Ε�
#define RELATIVE_Y_RESULT	(540.0f)	//Y���Ε�
#define SPAN_X_RESULT	(1980.0f)		//X�S��
#define SPAN_Y_RESULT	(1080.0f)		//Y�S��
#define	TEX_1_RESULT	"data\\TEX\\03_result\\GAMECLEAR000.png"//�摜�t�@�C��1
#define	TEX_2_RESULT	"data\\TEX\\03_result\\GAMEOVER000.png"	//�摜�t�@�C��2
#define	TEX_3_RESULT	"data\\TEX\\03_result\\menu000.png"		//�摜�t�@�C��3
#define	TEX_4_RESULT	"data\\TEX\\03_result\\menu001.png"		//�摜�t�@�C��4
#define	TEX_5_RESULT	"data\\TEX\\03_result\\retry000.png"	//�摜�t�@�C��5
#define	TEX_6_RESULT	"data\\TEX\\03_result\\retry001.png"	//�摜�t�@�C��6
#define	TEX_7_RESULT	"data\\TEX\\03_result\\exit000.png"		//�摜�t�@�C��7
#define	TEX_8_RESULT	"data\\TEX\\03_result\\exit001.png"		//�摜�t�@�C��8
#define	TEX_9_RESULT	"data\\TEX\\03_result\\cursor000.png"	//�摜�t�@�C��9
#define	TEX_10_RESULT	"data\\TEX\\03_result\\blackbase.png"	//�摜�t�@�C��10

//�v���g�^�C�v�錾
void Init_Result(void);
void Uninit_Result(void);
void Update_Result(void);
void Draw_Result(void);
void Setcursor_MENU(void);
void Setcursor_RETRY_R(void);
void Setcursor_EXIT_R(void);
void Setcursor_Anim_R(void);

#endif