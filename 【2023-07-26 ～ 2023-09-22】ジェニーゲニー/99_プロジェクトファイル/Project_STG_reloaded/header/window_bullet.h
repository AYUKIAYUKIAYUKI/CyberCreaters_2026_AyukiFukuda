//************************************************
//
//�e�E�B���h�E�\�������A�w�b�_�t�@�C��[window_bullet.h]
//Author�F���c����
//
//************************************************
#ifndef _WINDOW_BULLET_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _WINDOW_BULLET_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�f�o�b�O�p*/
#define	TEXTURE_WINDOW_BULLET	"data\\TEX\\02_game\\bulletwindow002.png"

#define POS_X_LEFT_WINDOW_BULLET	(20.0f)		//X���W�̍��p
#define POS_X_RIGHT_WINDOW_BULLET	(260.0f)	//X���W�̉E�p
#define POS_Y_UP_WINDOW_BULLET	(810.0f)		//Y���W�̏�p
#define POS_Y_DOWN_WINDOW_BULLET	(1060.0f)	//Y���W�̉��p

//�v���g�^�C�v�錾
void Init_Window_Bullet(void);
void Uninit_Window_Bullet(void);
void Draw_Window_Bullet(void);
void SetPos_Vtx_Window_Bullet(void);

#endif