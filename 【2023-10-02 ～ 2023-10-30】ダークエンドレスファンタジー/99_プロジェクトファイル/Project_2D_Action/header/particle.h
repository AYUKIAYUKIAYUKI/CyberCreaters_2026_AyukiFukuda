//************************************************
//
//�p�[�e�B�N������(�e���v��)�A�w�b�_�t�@�C��[particle.h]
//Author�F���c����
//
//************************************************
#ifndef _PARTICLE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PARTICLE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�f�o�b�O�p*/
#define	TEXTURE_ATKED	"data\\TEX\\atked.png"
#define	TEXTURE_BLOOD	"data\\TEX\\blood.png"

#define AMOUNT_POLYGON_PARTICLE	(256)	//�|���S����
#define AMOUNT_TEX_PARTICLE	(2)	//�e�N�X�`����

#define RADIUS_PARTICLE	(20.0f)			//���a�p
#define REMAIN_TIME_PARTICLE	(30)	//�c������

#define MOVE_SPD_POS_PARTICLE	(2.0f)		//�ړ����x
#define CHANGE_SPD_RADIUS_PARTICLE	(0.9f)	//�k�����x

#define SPD_CHANGE_TEX_PARTICLE	(1)	//�A�j���[�V�������x
#define AMOUNT_STYLE_TEX_PARTICLE	(8)	//�A�j���[�V�����p
#define SPAN_CHANGE_TEX_PARTICLE	(0.125f)	//�A�j���[�V�����p

typedef enum
{
	PARTICLE_ATKED = 0,
	PARTICLE_BLOOD,
	PARTICLE_STYLE_MAX,
}PARTICLE_STYLE;

//�p�[�e�B�N���\����
typedef struct
{
	int nStyle;
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ�
	D3DXVECTOR3 rot;	//��]
	D3DXCOLOR col;		//�F
	int nCntTex;		//�e�N�X�`���ύX
	int nCntPattern;	//�e�N�X�`���ύX
	float fTexSpan[2];	//�e�N�X�`����
	float fRadius[2];	//���a
	float fLength[2];	//�Ίp��
	float fAngle[2];	//�p�x
	int nRemain;		//�c������
	bool bUse;			//�g�p����
}PARTICLE;

//�v���g�^�C�v�錾

/*����*/
void Init_Particle(void);

/*�I��*/
void Uninit_Particle(void);

/*�X�V*/
void Update_Particle(void);

/*�`��*/
void Draw_Particle(void);

/*�p�[�e�B�N���Ƀf�[�^��t�^*/
void Setinfo_Particle(int nStyle, D3DXVECTOR3 pos, D3DXCOLOR col);

/*�p�[�e�B�N���o�[�e�b�N�X���X�V*/
void Update_Pos_Particle(void);

/*�e�N�X�`���A�j���[�V��������*/
void Update_Tex_Particle(int nCnt);

#endif