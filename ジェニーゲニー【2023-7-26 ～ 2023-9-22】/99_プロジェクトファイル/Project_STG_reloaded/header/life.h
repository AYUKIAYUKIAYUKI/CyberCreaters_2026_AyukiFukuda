//************************************************
//
//���C�t�\�L�A�w�b�_�t�@�C��[life.h]
//Author�F���c����
//
//************************************************
#ifndef _LIFE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _LIFE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_HEARTS_LIFE	"data\\TEX\\02_game\\life000.png"

#define POS_X_LEFT_LIFE	(270.0f)		//X���W�̍��p
#define POS_X_RIGHT_LIFE	(670.0f)	//X���W�̉E�p
#define POS_Y_UP_LIFE	(875.0f)		//Y���W�̏�p
#define POS_Y_DOWN_LIFE	(945.0f)		//Y���W�̉��p

#define TEX_U_RIGHT_LIFE	(1.0f)	//U���W�̉E�p
#define TEX_V_DOWN_LIFE	(0.16f)		//V���W�̉��p

#define MOVE_SPAN_TEX_LIFE	(0.168f)	//�e�N�X�`������

//���C�t���񋓌^
typedef enum
{
	AMOUNT_LIFE_0 = 0,
	AMOUNT_LIFE_1,
	AMOUNT_LIFE_2,
	AMOUNT_LIFE_3,
	AMOUNT_LIFE_4,
	AMOUNT_LIFE_MAX,
}AMOUNT_LIFE;

//�v���g�^�C�v�錾
void Init_Life(void);
void Uninit_Life(void);
void Update_Life(int nLife);
void Draw_Life(void);
void SetPos_Vtx_Life(void);

#endif