//************************************************
//
//�Q�[�����쏈���A�w�b�_�t�@�C��[game.h]
//Author�F���c����
//
//************************************************
#ifndef _GAME_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _GAME_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_BLACK_GAME	"data\\TEX\\02_game\\blackbase.png"

#define AMOUNT_POLYGON_GAME	(1)	//�|���S����

#define CHANGE_SPD_FADE_COLORA_GAME	(25)	//�t�F�[�h��colA�ύX���x

#define AMOUNT_CNT_FINISH_GAME	(90)	//�Q�[���I�����̒x������

//�v���g�^�C�v�錾
void Init_Game(void);
void Uninit_Game(void);
void Update_Game(void);
void Draw_Game(void);
void SetPos_Vtx_Game(void);
void Fadein_Animation_Game(void);
void Fadeout_Animation_Game(void);
bool* Getinfo_Pause(void);	//�|�[�Y��cpp�Ƀ|�[�Y���肵�Ă�bool�̃A�h���X�n������

#endif