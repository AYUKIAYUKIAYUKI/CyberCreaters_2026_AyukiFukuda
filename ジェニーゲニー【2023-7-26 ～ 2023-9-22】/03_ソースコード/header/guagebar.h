//************************************************
//
//�Q�[�W�o�[�\�������A�w�b�_�t�@�C��[guagebar.h]
//Author�F���c����
//
//************************************************
#ifndef _GUAGEBAR_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _GUAGEBAR_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�f�o�b�O�p*/
#define	TEXTURE_GUAGEBAR	"data\\TEX\\02_game\\bulletwindow001.png"

#define POS_X_LEFT_GUAGEBAR	(130.0f)		//X���W�̍��p
#define POS_X_RIGHT_GUAGEBAR	(843.0f)	//X���W�̉E�p
#define POS_Y_UP_GUAGEBAR	(890.0f)		//Y���W�̏�p
#define POS_Y_DOWN_GUAGEBAR	(1034.0f)		//Y���W�̉��p

//�v���g�^�C�v�錾
void Init_GuageBar(void);
void Uninit_GuageBar(void);
void Draw_GuageBar(void);
void SetPos_Vtx_GuageBar(void);

#endif