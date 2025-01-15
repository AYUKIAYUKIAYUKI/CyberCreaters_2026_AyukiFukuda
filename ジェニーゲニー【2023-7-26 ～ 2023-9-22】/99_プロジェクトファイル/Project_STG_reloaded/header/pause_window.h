//************************************************
//
//�|�[�Y�E�B���h�E�����A�w�b�_�t�@�C��[pause_window.h]
//Author�F���c����
//
//************************************************
#ifndef _PAUSE_WINDOW_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PAUSE_WINDOW_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"
#include "pause.h"

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_PAUSE_WINDOW	"data\\TEX\\01_menu\\tutorial_window.png"
#define	TEXTURE_PAUSE_TEXT	"data\\TEX\\02_game\\pause.png"

#define AMOUNT_POLYGON_PAUSE_WINDOW	(2)	//�|���S����
#define AMOUNT_TEXTURE_PAUSE_WINDOW	(2)	//�e�N�X�`����

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
}PAUSE_WINDOW;

//�v���g�^�C�v�錾
void Init_Pause_Window(void);
void Uninit_Pause_Window(void);
void Update_Pause_Window(void);
void Draw_Pause_Window(void);
void Setinfo_Pause_Window(void);

#endif