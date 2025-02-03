//************************************************
//
//�X�e�[�W�I�u�W�F�N�g�z�u�����A�w�b�_�t�@�C��[stage.h]
//Author�F���c����
//
//************************************************
#ifndef _STAGE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _STAGE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�t�@�C���p�X�n*/
#define DATA_STAGE_OBJECT	"data\\csv\\info_stage_object.csv"
#define POS_STAGE_OBJECT	"data\\csv\\posinfo_stage_object.csv"
#define DATA_STAGE_OBJECT_OLD	"data\\csv\\info_stage_object_old.csv"

#define AMOUNT_POLYGON_STAGE	(256)	//�X�e�[�W�I�u�W�F�N�g�̃|���S���ő吔
#define AMOUNT_TEX_STAGE	(3)	//�X�e�[�W�I�u�W�F�N�g�̃e�N�X�`������

#define SPAN_CUT_SIDE_SATAGE	(6.0f)	//���␳�W��

/*�摜�p�X*/
#define	TEXTURE_STAGE_OBJECT_BLOCK	"data\\TEX\\tile_0000.png"
#define	TEXTURE_STAGE_OBJECT_LEFT	"data\\TEX\\tile_0001.png"
#define	TEXTURE_STAGE_OBJECT_RIGHT	"data\\TEX\\tile_0002.png"

//�X�e�[�W�I�u�W�F�N�g��ޕ���
typedef enum
{
	STAGE_OBJECT_STYLE_NONE = 0,
	STAGE_OBJECT_STYLE_BLOCK,
	STAGE_OBJECT_STYLE_LEFT,
	STAGE_OBJECT_STYLE_RIGHT,
	STAGE_OBJECT_STYLE_LEFT_J,	//��΂ɃW�����v����R�A2�ӏ����݂���
	STAGE_OBJECT_STYLE_RIGHT_J,
	STAGE_OBJECT_STYLE_MAX,
}STAGE_OBJECT_STYLE;

//�����ޕ���
typedef enum
{
	HIT_TYPE_PLAYER = 0,
	HIT_TYPE_ENEMY,
	HIT_TYPE_MAX,
}HIT_TYPE;

//�v���C���[���̗񋓌^
typedef struct
{
	int nStyle;			//���
	bool bUse;			//�g�p
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength[2];	//�Ίp��
	float fAngle[2];	//�p�x
}STAGE;

//�v���g�^�C�v�錾

/*����*/
void Init_Stage(void);

/*�j��*/
void Uninit_Stage(void);

/*�X�V*/
void Update_Stage(void);

/*�`��*/
void Draw_Stage(void);

/*���l�f�[�^��ǂݎ��(��)*/
void ReadInfo_Stage_Old(void);

/*���l�f�[�^��ǂݎ��*/
void ReadInfo_Stage(void);

/*���l�f�[�^��ǂݎ��*/
void ReadPosInfo_Stage(void);

/*�X�e�[�W�I�u�W�F�N�g�Ƀf�[�^��t�^*/
void SetInfo_Stage(void);

/*�X�e�[�W�I�u�W�F�N�g�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Stage(void);

/*�X�e�[�W�I�u�W�F�N�g�Ƃ̓����蔻��*/
bool HitDetection_Stage(int nEnemy, int nType, D3DXVECTOR3* pos, D3DXVECTOR3* oldpos, D3DXVECTOR3* move, float fRadius[2]);

/*�X�e�[�W�I�u�W�F�N�g�̃f�[�^���擾*/
STAGE* GetInfo_Stage(void);

#endif