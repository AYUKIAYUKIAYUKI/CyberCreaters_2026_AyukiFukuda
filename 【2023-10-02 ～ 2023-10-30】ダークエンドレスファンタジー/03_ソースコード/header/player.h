//************************************************
//
//���@�����A�w�b�_�t�@�C��[player.h]
//Author�F���c����
//
//************************************************
#ifndef _PLEYER_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PLEYER_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_CHARACTER_IDLE_PLAYER	"data\\TEX\\player_idle.png"
#define	TEXTURE_CHARACTER_JUMP_PLAYER	"data\\TEX\\player_only_jump.png"
#define	TEXTURE_CHARACTER_LAND_PLAYER	"data\\TEX\\player_only_land.png"
#define	TEXTURE_CHARACTER_RUN_PLAYER	"data\\TEX\\player_run1.png"
#define	TEXTURE_CHARACTER_LIGHT1_PLAYER	"data\\TEX\\player_light1.png"
#define	TEXTURE_CHARACTER_LIGHT2_PLAYER	"data\\TEX\\player_light2.png"
#define	TEXTURE_CHARACTER_LIGHT3_PLAYER	"data\\TEX\\player_light3.png"
#define	TEXTURE_CHARACTER_HEAVY1_PLAYER	"data\\TEX\\player_heavy1.png"
#define	TEXTURE_CHARACTER_HEAVY2_PLAYER	"data\\TEX\\player_heavy2.png"
#define	TEXTURE_CHARACTER_HEAVY3_PLAYER	"data\\TEX\\player_heavy3.png"
#define	TEXTURE_CHARACTER_HURT1_PLAYER	"data\\TEX\\player_hurt_1.png"
#define	TEXTURE_CHARACTER_HURT2_PLAYER	"data\\TEX\\player_hurt_2.png"

#define AMOUNT_TEX_PLAYER	(12)	//�v���C���[�̃e�N�X�`������

#define RADIUS_PLAYER_X	(35.0f)	//������
#define RADIUS_PLAYER_Y	(50.0f)	//�c����

#define MOVE_SPD_PLAYER_X	(6.0f)	//���ړ����x
#define MOVE_SPD_ATK_PLAYER_X	(8.0f)	//�U�������ړ����x
#define MOVE_SPD_BRAKE_X	(0.75f)	//���ړ��u���[�L���x
#define MOVE_SPD_PLAYER_Y	(40.0f)	//�W�����v��
#define MOVE_SPD_GRAVITY_Y	(2.0f)	//�d�͉����x
#define ROTATE_SPD_PLAYER_Z	(-1.5625f)	//��]���x
#define ROTATE_SPD_BRAKE_Z	(0.8f)	//��]�u���[�L���x

#define AMOUNT_ABLE_JUMPS	(2)	//�\�W�����v��
//#define AMOUNT_MAX_LIFE_PLAYER	(7)	//���C�t��
#define AMOUNT_CT_LIGHT_COMBO	(40)	//��U���R���{�P�\
#define AMOUNT_CT_HEAVY_COMBO	(60)	//���U���R���{�P�\
#define AMOUNT_CT_LIGHT	(10)	//��U��CT
#define AMOUNT_CT_HEAVY	(25)	//���U��CT

#define FELL_RESET_MOVE_X	(50.0f)	//�����㕜�����ړ����x
#define FELL_RESET_MOVE_Y	(-50.0f)	//�����㕜���c�ړ����x
#define FELL_RESET_AREA_X	(100.0f)	//�����㕜�����͈�
#define FELL_RESET_AREA_Y	(50.0f)	//�����㕜���c�͈�

#define SPD_CHANGE_TEX_IDLE_PLAYER	(3)	//�ҋ@���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_IDLE_PLAYER	(18)	//�ҋ@���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_IDLE_PLAYER	(0.05555f)	//�ҋ@���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_JUMP_PLAYER	(2)	//�W�����v���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_JUMP_PLAYER	(14)	//�W�����v���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_JUMP_PLAYER	(0.06666f)	//�W�����v���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_LAND_PLAYER	(2)	//���n���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_LAND_PLAYER	(4)	//���n���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_LAND_PLAYER	(0.25f)	//���n���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_RUN_PLAYER	(2)	//���s���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_RUN_PLAYER	(24)	//���s���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_RUN_PLAYER	(0.04166f)	//���s���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_LIGHT1_PLAYER	(2)	//��1���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_LIGHT1_PLAYER	(8)	//��1���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_LIGHT1_PLAYER	(0.125f)	//��1���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_LIGHT2_PLAYER	(2)	//��2���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_LIGHT2_PLAYER	(7)	//��2���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_LIGHT2_PLAYER	(0.14285f)	//��2���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_LIGHT3_PLAYER	(2)	//��3���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_LIGHT3_PLAYER	(10)	//��3���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_LIGHT3_PLAYER	(0.09090f)	//��3���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_HEAVY1_PLAYER	(3)	//��1���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_HEAVY1_PLAYER	(12)	//��1���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_HEAVY1_PLAYER	(0.08333f)	//��1���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_HEAVY2_PLAYER	(3)	//��2���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_HEAVY2_PLAYER	(12)	//��2���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_HEAVY2_PLAYER	(0.08333f)	//��2���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_HEAVY3_PLAYER	(3)	//��3���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_HEAVY3_PLAYER	(16)	//��3���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_HEAVY3_PLAYER	(0.0625f)	//��3���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_HURT1_PLAYER	(3)	//��e1���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_HURT1_PLAYER	(7)	//��e1���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_HURT1_PLAYER	(0.14285f)	//��e1���̃A�j���[�V�����p

#define SPD_CHANGE_TEX_HURT2_PLAYER	(3)	//��e2���̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_HURT2_PLAYER	(7)	//��e2���̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_HURT2_PLAYER	(0.14285f)	//��e2���̃A�j���[�V�����p

//�v���C���[��Ԃ̗񋓌^
typedef enum
{
	PLAYER_STATE_IDLE = 0,	//�ҋ@
	PLAYER_STATE_JUMP,		//�W�����v
	PLAYER_STATE_FALL,		//����
	PLAYER_STATE_LAND,		//���n
	PLAYER_STATE_RUN,		//���s
	PLAYER_STATE_TURN,		//�U��ނ�
	PLAYER_STATE_SLIDE,		//�X���C�f�B���O
	PLAYER_STATE_LIGHT1,	//��1
	PLAYER_STATE_LIGHT2,	//��2
	PLAYER_STATE_LIGHT3,	//��3
	PLAYER_STATE_HEAVY1,	//��1
	PLAYER_STATE_HEAVY2,	//��2
	PLAYER_STATE_HEAVY3,	//��3
	PLAYER_STATE_BOW,		//�|
	PLAYER_STATE_HURT1,		//��e1
	PLAYER_STATE_HURT2,		//��e2
	PLAYER_STATE_CLIMB,		//��
	PLAYER_STATE_MAX,
}PLAYER_STATE;

//�v���C���[���̍\���^
typedef struct
{
	int nState;			//�v���C���[�̏��
	D3DXVECTOR3 BGpos;	//���ۈʒu
	D3DXVECTOR3 pos;	//�^���ʒu
	D3DXVECTOR3 oldpos;	//�O�̈ʒu
	D3DXVECTOR3 lastland;//�Ō�̒��n�ʒu
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
	bool bLanding;		//���n����
	int nJumpTimes;		//�W�����v��
	//int nLife;			//���C�t��
	bool bFell;			//��������
	int nLastATK;		//�ŏI�U���^�C�v
	bool bAfterATK;		//�U���㔻��
	int nCntAfterATK;	//�U����J�E���g
}PLAYER;

//�v���C���[�{�b�N�X���̍\���^
typedef struct
{
	float fRadius_Hold[2];	//���a
	float fLength_Hold[2];	//�Ίp��
	float fAngle_Hold[2];	//�p�x
}PLAYER_BOX;

//�v���g�^�C�v�錾

/*����*/
void Init_Player(void);

/*�j��*/
void Uninit_Player(void);

/*�X�V*/
void Update_Player(void);

/*�`��*/
void Draw_Player(void);

/*��������̃v���C���[�{�b�N�X�T�C�Y���Z�o(�e�N�X�`���p)*/
void CalcSize_Player_Box(void);

/*�v���C���[�Ƀf�[�^��t�^*/
void SetInfo_Player(void);

/*�v���C���[���ړ�������*/
void Move_Pos_Player(void);

/*�v���C���[�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Player(void);

/*�������̈ʒu�Ɩ{���̈ʒu�𒲐�*/
void Adjust_Pos_Player(void);

/*�e�N�X�`���A�j���[�V��������*/
void Update_Tex_Player(void);

/*�v���C���[�̃f�[�^���擾*/
PLAYER* GetInfo_Player(void);

/*�v���C���[�{�b�N�X�̃f�[�^���擾*/
PLAYER_BOX* GetInfo_Player_Box(void);

/*�v���C���[�̈ʒu���擾*/
D3DXVECTOR3 GetInfo_Pos_Player(void);

#endif