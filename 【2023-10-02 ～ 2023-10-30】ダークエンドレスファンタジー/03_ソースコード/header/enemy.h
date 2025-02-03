//************************************************
//
//�G�����A�w�b�_�t�@�C��[enemy.h]
//Author�F���c����
//
//************************************************
#ifndef _ENEMY_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _ENEMY_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_ENEMY_00_MOVE "data\\TEX\\e00_move.png"
#define	TEXTURE_ENEMY_00_ATK "data\\TEX\\e00_atk.png"
#define	TEXTURE_ENEMY_00_HURT "data\\TEX\\e00_hurt.png"
#define	TEXTURE_ENEMY_00_DEATH "data\\TEX\\e00_death.png"

#define	TEXTURE_ENEMY_01_IDLE "data\\TEX\\e01_idle.png"
#define	TEXTURE_ENEMY_01_MOVE "data\\TEX\\e01_move.png"
#define	TEXTURE_ENEMY_01_ATK "data\\TEX\\e01_atk.png"
#define	TEXTURE_ENEMY_01_HURT "data\\TEX\\e01_hurt.png"
#define	TEXTURE_ENEMY_01_DEATH "data\\TEX\\e01_death.png"

#define	TEXTURE_ENEMY_02_IDLE "data\\TEX\\e02_idle.png"
#define	TEXTURE_ENEMY_02_MOVE "data\\TEX\\e02_move.png"
#define	TEXTURE_ENEMY_02_ATK "data\\TEX\\e02_atk.png"
#define	TEXTURE_ENEMY_02_HURT "data\\TEX\\e02_hurt.png"
#define	TEXTURE_ENEMY_02_DEATH "data\\TEX\\e02_death.png"

#define	TEXTURE_ENEMY_03_IDLE "data\\TEX\\e03_idle.png"
#define	TEXTURE_ENEMY_03_MOVE "data\\TEX\\e03_move.png"
#define	TEXTURE_ENEMY_03_ATK "data\\TEX\\e03_atk.png"
#define	TEXTURE_ENEMY_03_HURT "data\\TEX\\e03_hurt.png"
#define	TEXTURE_ENEMY_03_DEATH "data\\TEX\\e03_death.png"

#define	TEXTURE_ENEMY_04_IDLE "data\\TEX\\e04_idle.png"
#define	TEXTURE_ENEMY_04_MOVE "data\\TEX\\e04_move.png"
#define	TEXTURE_ENEMY_04_ATK "data\\TEX\\e04_atk.png"
#define	TEXTURE_ENEMY_04_HURT "data\\TEX\\e04_hurt.png"
#define	TEXTURE_ENEMY_04_DEATH "data\\TEX\\e04_death.png"

#define AMOUNT_POLYGON_ENEMY	(6)	//�G�̃|���S������
#define AMOUNT_TEX_ENEMY	(24)	//�G�̃e�N�X�`������

#define RADIUS_ENEMY_X	(30.0f)	//�ėp������(�����蔻��ɗp���܂��A�����ڃT�C�Y�p�ł͂Ȃ��I)
#define RADIUS_ENEMY_Y	(30.0f)	//�ėp�c����

#define AMOUN_RESPAWN_CT	(40)	//�S�̂̓G�̃��X�|�[���Ԋu(�t���[��)

#define AMOUNT_MAX_LIFE_ENEMY_00	(1)	//00���C�t
#define AMOUNT_MAX_LIFE_ENEMY_01	(2)	//01���C�t
#define AMOUNT_MAX_LIFE_ENEMY_02	(1)	//02���C�t
#define AMOUNT_MAX_LIFE_ENEMY_03	(3)	//03���C�t
#define AMOUNT_MAX_LIFE_ENEMY_04	(4)	//04���C�t

#define AMOUNT_CT_ATK_ENEMY_00	(30)	//00�U��CT
#define AMOUNT_CT_ATK_ENEMY_01	(50)	//01�U��CT
#define AMOUNT_CT_ATK_ENEMY_02	(20)	//02�U��CT
#define AMOUNT_CT_ATK_ENEMY_03	(80)	//03�U��CT
#define AMOUNT_CT_ATK_ENEMY_04	(80)	//04�U��CT

#define SPD_CHANGE_TEX_MOVE_ENEMY_00	(3)	//00�ړ����̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_MOVE_ENEMY_00	(8)	//00�ړ����̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_MOVE_ENEMY_00	(0.125f)	//00�ړ����̃A�j���[�V�����p

#define SPD_CHANGE_TEX_ATK_ENEMY_00	(2)	//00�U�����̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_ATK_ENEMY_00	(8)	//00�U�����̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_ATK_ENEMY_00	(0.125f)	//00�U�����̃A�j���[�V�����p

#define SPD_CHANGE_TEX_HURT_ENEMY_00	(3)	//00��e���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_HURT_ENEMY_00	(4)	//00��e���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_HURT_ENEMY_00	(0.25f)	//00��e���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_DEATH_ENEMY_00	(4)	//00���S���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_DEATH_ENEMY_00	(4)	//00���S���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_DEATH_ENEMY_00	(0.25f)	//00���S���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_IDLE_ENEMY_01	(7)	//01�ҋ@���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_IDLE_ENEMY_01	(4)	//01�ҋ@���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_IDLE_ENEMY_01	(0.25f)	//01�ҋ@���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_MOVE_ENEMY_01	(5)	//01�ړ����̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_MOVE_ENEMY_01	(8)	//01�ړ����̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_MOVE_ENEMY_01	(0.125f)	//01�ړ����̃A�j���[�V�����p

#define SPD_CHANGE_TEX_ATK_ENEMY_01	(2)	//01�U�����̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_ATK_ENEMY_01	(8)	//01�U�����̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_ATK_ENEMY_01	(0.125f)	//01�U�����̃A�j���[�V�����p

#define SPD_CHANGE_TEX_HURT_ENEMY_01	(4)	//01��e���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_HURT_ENEMY_01	(4)	//01��e���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_HURT_ENEMY_01	(0.25f)	//01��e���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_DEATH_ENEMY_01	(4)	//01���S���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_DEATH_ENEMY_01	(4)	//01���S���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_DEATH_ENEMY_01	(0.25f)	//01���S���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_IDLE_ENEMY_02	(5)	//02�ҋ@���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_IDLE_ENEMY_02	(4)	//02�ҋ@���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_IDLE_ENEMY_02	(0.25f)	//02�ҋ@���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_MOVE_ENEMY_02	(3)	//02�ړ����̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_MOVE_ENEMY_02	(8)	//02�ړ����̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_MOVE_ENEMY_02	(0.125f)	//02�ړ����̃A�j���[�V�����p

#define SPD_CHANGE_TEX_ATK_ENEMY_02	(3)	//02�U�����̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_ATK_ENEMY_02	(8)	//02�U�����̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_ATK_ENEMY_02	(0.125f)	//02�U�����̃A�j���[�V�����p

#define SPD_CHANGE_TEX_HURT_ENEMY_02	(3)	//02��e���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_HURT_ENEMY_02	(4)	//02��e���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_HURT_ENEMY_02	(0.25f)	//02��e���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_DEATH_ENEMY_02	(4)	//02���S���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_DEATH_ENEMY_02	(4)	//02���S���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_DEATH_ENEMY_02	(0.25f)	//02���S���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_IDLE_ENEMY_03	(6)	//03�ҋ@���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_IDLE_ENEMY_03	(4)	//03�ҋ@���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_IDLE_ENEMY_03	(0.25f)	//03�ҋ@���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_MOVE_ENEMY_03	(4)	//03�ړ����̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_MOVE_ENEMY_03	(4)	//03�ړ����̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_MOVE_ENEMY_03	(0.25f)	//03�ړ����̃A�j���[�V�����p

#define SPD_CHANGE_TEX_ATK_ENEMY_03	(5)	//03�U�����̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_ATK_ENEMY_03	(8)	//03�U�����̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_ATK_ENEMY_03	(0.125f)	//03�U�����̃A�j���[�V�����p

#define SPD_CHANGE_TEX_HURT_ENEMY_03	(3)	//03��e���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_HURT_ENEMY_03	(4)	//03��e���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_HURT_ENEMY_03	(0.25f)	//03��e���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_DEATH_ENEMY_03	(4)	//03���S���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_DEATH_ENEMY_03	(4)	//03���S���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_DEATH_ENEMY_03	(0.25f)	//03���S���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_IDLE_ENEMY_04	(3)	//04�ҋ@���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_IDLE_ENEMY_04	(9)	//04�ҋ@���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_IDLE_ENEMY_04	(0.11111f)	//04�ҋ@���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_MOVE_ENEMY_04	(3)	//04�ړ����̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_MOVE_ENEMY_04	(9)	//04�ړ����̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_MOVE_ENEMY_04	(0.11111f)	//04�ړ����̃A�j���[�V�����p

#define SPD_CHANGE_TEX_ATK_ENEMY_04	(3)	//04�U�����̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_ATK_ENEMY_04	(16)	//04�U�����̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_ATK_ENEMY_04	(0.0625f)	//04�U�����̃A�j���[�V�����p

#define SPD_CHANGE_TEX_HURT_ENEMY_04	(4)	//04��e���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_HURT_ENEMY_04	(3)	//04��e���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_HURT_ENEMY_04	(0.33333f)	//04��e���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_DEATH_ENEMY_04	(4)	//04���S���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_DEATH_ENEMY_04	(8)	//04���S���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_DEATH_ENEMY_04	(0.125)	//04���S���̃A�j���[�V�����p

//�G�񋓌^
typedef enum
{
	ENEMY_00 = 0,
	ENEMY_01,
	ENEMY_02,
	ENEMY_03,
	ENEMY_04,
	ENEMY_MAX
}ENEMY_STYLE;

//�G00�̏�Ԃ̗񋓌^
typedef enum
{
	ENEMY_00_STATE_MOVE,	//�ړ�
	ENEMY_00_STATE_ATK,		//�U��
	ENEMY_00_STATE_HURT,	//��e
	ENEMY_00_STATE_DEATH,	//���S
}ENEMY_00_STATE;

//�G01�̏�Ԃ̗񋓌^
typedef enum
{
	ENEMY_01_STATE_IDLE,	//�ҋ@
	ENEMY_01_STATE_MOVE,	//�ړ�
	ENEMY_01_STATE_ATK,		//�U��
	ENEMY_01_STATE_HURT,	//��e
	ENEMY_01_STATE_DEATH,	//���S
}ENEMY_01_STATE;

//�G02�̏�Ԃ̗񋓌^
typedef enum
{
	ENEMY_02_STATE_IDLE,	//�ҋ@
	ENEMY_02_STATE_MOVE,	//�ړ�
	ENEMY_02_STATE_ATK,		//�U��
	ENEMY_02_STATE_HURT,	//��e
	ENEMY_02_STATE_DEATH,	//���S
}ENEMY_02_STATE;

//�G03�̏�Ԃ̗񋓌^
typedef enum
{
	ENEMY_03_STATE_IDLE,	//�ҋ@
	ENEMY_03_STATE_MOVE,	//�ړ�
	ENEMY_03_STATE_ATK,		//�U��
	ENEMY_03_STATE_HURT,	//��e
	ENEMY_03_STATE_DEATH,	//���S
}ENEMY_03_STATE;

//�G04�̏�Ԃ̗񋓌^
typedef enum
{
	ENEMY_04_STATE_IDLE,	//�ҋ@
	ENEMY_04_STATE_MOVE,	//�ړ�
	ENEMY_04_STATE_ATK,		//�U��
	ENEMY_04_STATE_HURT,	//��e
	ENEMY_04_STATE_DEATH,	//���S
}ENEMY_04_STATE;

//�v���C���[���̍\���^
typedef struct
{
	bool bUse;			//�o������
	int nStyle;			//�G�̎��
	int nState;			//�G�̏��
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 oldpos;	//�O�̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//��]
	D3DXCOLOR col;		//�F
	int LR;				//����
	int nCntTex;		//�e�N�X�`���ύX
	int nCntPattern;	//�e�N�X�`���ύX
	float fTexSpan[2];	//�e�N�X�`����
	float fRadius[2];	//���a
	float fLength[2];	//�Ίp��
	float fAngle[2];	//�p�x
	float fDisappear;	//�`�W�~
	int nLife;			//���C�t��
	int nCT;			//�L���X�g�^�C��
	bool bLockonP;		//�v���C���[���G
}ENEMY;

//t�G�{�b�N�X���̍\���^
typedef struct
{
	float fRadius_Hold[2];	//���a
	float fLength_Hold[2];	//�Ίp��
	float fAngle_Hold[2];	//�p�x
}ENEMY_BOX;

//�v���g�^�C�v�錾

/*����*/
void Init_Enemy(void);

/*�j��*/
void Uninit_Enemy(void);

/*�X�V*/
void Update_Enemy(void);

/*�`��*/
void Draw_Enemy(void);

/*��������̃G�l�~�[�{�b�N�X�T�C�Y���Z�o(�e�N�X�`���p)*/
void CalcSize_Enemy_Box(void);

/*�G�Ƀf�[�^��t�^*/
void SetInfo_Enemy(void);

/*�G�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Enemy(int i);

/*�G��|�����Ƃ��̏��ŏ���*/
void Disapper_Enemy(int i);

/*�������̈ʒu�Ɩ{���̈ʒu�𒲐�*/
void Adjust_Pos_Enemy(int i);

/*�e�N�X�`���A�j���[�V��������*/
void Update_Tex_Enemy(int i);

/*�G�Ƃ̓����蔻��*/
//void Hit_Detection_Enemy(int i);

/*�G�̃f�[�^���擾*/
ENEMY* GetInfo_Enemy(void);

#endif