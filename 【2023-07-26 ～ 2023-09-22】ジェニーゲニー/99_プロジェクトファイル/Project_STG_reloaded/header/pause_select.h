//************************************************
//
//�|�[�Y��ʃ��[�h�I���A�w�b�_�t�@�C��[pause_select.h]
//Author�F���c����
//
//************************************************
#ifndef _PAUSE_SELECT_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PAUSE_SELECT_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_PAUSE_CONTINUE	"data\\TEX\\02_game\\continue.png"
#define	TEXTURE_PAUSE_RETRY	"data\\TEX\\02_game\\retry.png"
#define	TEXTURE_PAUSE_MENU	"data\\TEX\\02_game\\menu.png"
#define	TEXTURE_PAUSE_TITLE	"data\\TEX\\02_game\\title.png"

#define AMOUNT_POLYGON_PAUSE_SELECT	(4)	//�|���S����
#define AMOUNT_TEXTURE_PAUSE_SELECT	(4)	//�Ǎ��݃e�N�X�`����

typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	float fSpanX;		//�T�C�Y
	float fSpanY;		//�T�C�Y
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�F
	float colA;
}PAUSE_SELECT;

//�v���g�^�C�v�錾
void Init_Pause_Select(void);
void Uninit_Pause_Select(void);
void Update_Pause_Select(void);
void Draw_Pause_Select(void);
void Setinfo_Pause_Select(void);

#endif