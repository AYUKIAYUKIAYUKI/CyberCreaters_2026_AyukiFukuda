//************************************************
//
//�Q�[�W�\�������A�w�b�_�t�@�C��[guage.h]
//Author�F���c����
//
//************************************************
#ifndef _GUAGE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _GUAGE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�f�o�b�O�p*/
#define	TEXTURE_GUAGE	"data\\TEX\\02_game\\guage000.png"

#define POS_X_LEFT_GUAGE	(130.0f)	//X���W�̍��p
#define POS_X_RIGHT_GUAGE	(843.0f)	//X���W�̉E�p
#define POS_Y_UP_GUAGE	(890.0f)		//Y���W�̏�p
#define POS_Y_DOWN_GUAGE	(1034.0f)	//Y���W�̉��p

#define DIVIDE_POLYGON_GUAGE	(2.376666f)	//�|���S��������
#define DIVIDE_TEXTURE_GUAGE	(0.003333f)	//�e�N�X�`��������

//�v���g�^�C�v�錾
void Init_Guage(void);
void Uninit_Guage(void);
void Update_Guage(void);
void Draw_Guage(void);
void SetPos_Vtx_Guage(void);

#endif
