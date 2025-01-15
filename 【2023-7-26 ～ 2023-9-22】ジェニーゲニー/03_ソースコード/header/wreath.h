//************************************************
//
//���[�X�\�������A�w�b�_�t�@�C��[wreath.h]
//Author�F���c����
//
//************************************************
#ifndef _WREATH_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _WREATH_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�f�o�b�O�p*/
#define	TEXTURE_WREATH	"data\\TEX\\02_game\\bulletwindow000.png"
#define	TEXTURE_WOOD	"data\\TEX\\99_nonuse\\stump000.png"

#define AMOUNT_POLYGON_WREATH	(2)	//�|���S����
#define AMOUNT_TEXTURE_WREATH	(2)		//�Ǎ��݃e�N�X�`����

#define POS_X_LEFT_WREATH	(20.0f)		//X���W�̍��p
#define POS_X_RIGHT_WREATH	(260.0f)	//X���W�̉E�p
#define POS_Y_UP_WREATH	(810.0f)		//Y���W�̏�p
#define POS_Y_DOWN_WREATH	(1060.0f)	//Y���W�̉��p

#define POS_WOOD	(55.0f)	//�؎M�p

//�v���g�^�C�v�錾
void Init_Wreath(void);
void Uninit_Wreath(void);
void Draw_Wreath(void);
void SetPos_Vtx_Wreath(void);

#endif