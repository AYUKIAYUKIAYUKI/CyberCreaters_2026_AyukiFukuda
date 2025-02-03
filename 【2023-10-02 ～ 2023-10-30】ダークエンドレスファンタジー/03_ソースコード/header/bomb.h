//************************************************
//
//�{�������A�w�b�_�t�@�C��[bomb.h]
//Author�F���c����
//
//************************************************
#ifndef _BOMB_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _BOMB_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_BOMB_1	"data\\TEX\\epic01.png"
#define	TEXTURE_BOMB_2	"data\\TEX\\epic02.png"

#define AMOUNT_POLYGON_BOMB	(1)	//�^�C�g���{���̃|���S���ő吔
#define AMOUNT_TEX_BOMB	(2)	//�^�C�g���{���̃e�N�X�`������

#define SPAN_CHANGE_TEX_BOMB (0.14285f)
#define SPAN_CHANGE_TEX_EXPLOSION (0.125f)

typedef enum
{
	BOMB_IDLE = 0,
	BOMB_EXPLOSION,
	BOMB_STATE_MAX,
}BOMB_STATE;

//�^�C�g���{�����̍\����
typedef struct
{
	bool bUse;			//�o������
	int nState;			//BOMB�̏��
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 oldpos;	//�O�̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//��]
	D3DXCOLOR col;		//�F
	int LR;				//����
	int nCntTex;		//�e�N�X�`���ύX
	int nCntPattern;	//�e�N�X�`���ύX
	float fTexSpan[2];	//�e�N�X�`����
	float fTexSpanY[2];	//�e�N�X�`����
	float fRadius[2];	//���a
	float fLength[2];	//�Ίp��
	float fAngle[2];	//�p�x
	float nCT;			//�L���X�g
	float nCharge;		//�Ďg�p�܂�
}BOMB;

//B�{�b�N�X���̍\���^
typedef struct
{
	float fRadius_Hold[2];	//���a
	float fLength_Hold[2];	//�Ίp��
	float fAngle_Hold[2];	//�p�x
}BOMB_BOX;

//�v���g�^�C�v�錾

/*����*/
void Init_Bomb(void);

/*�j��*/
void Uninit_Bomb(void);

/*�X�V*/
void Update_Bomb(void);

/*�`��*/
void Draw_Bomb(void);

void CalcSize_Bomb_Box(void);

/*�{���Ƀf�[�^��t�^*/
void SetInfo_Bomb(void);

/*�{���̃o�[�e�b�N�X���X�V*/
void Update_Pos_Bomb(void);

/*�{���̃o�[�e�b�N�X�J���[���X�V*/
void Update_Col_Bomb(void);

/*�{���̃e�N�X�`�����X�V*/
void Update_Tex_Bomb(void);

/*�{���̏����擾*/
BOMB* GetInfo_Bomb(void);

int* GetInfo_Bomb_aa(void);

#endif