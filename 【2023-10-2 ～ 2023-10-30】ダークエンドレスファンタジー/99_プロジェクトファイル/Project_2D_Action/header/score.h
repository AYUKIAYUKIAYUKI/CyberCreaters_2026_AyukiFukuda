//************************************************
//
//�X�R�A�����A�w�b�_�t�@�C��[score.h]
//Author�F���c����
//
//************************************************
#ifndef _SCORE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _SCORE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_SCORE	"data\\TEX\\number.png"

#define AMOUNT_POLYGON_SCORE	(8)	//�|���S����

#define SPAN_EACH_POLYGON_SCORE	(30.0f)	//�|���S������ׂ�Ԋu
#define MOVE_SPAN_TEX_SCORE	(0.1f)			//�e�N�X�`������

#define AMOUNT_MAX_SCORE	(999999)	//�X�R�A���

//�X�R�A�p���[�h����
typedef enum
{
	SCORE_TYPE_GAME = 0,
	SCORE_TYPE_RESULT,
	SCORE_TYPE_MAX,
}SCORE_TYPE;

//�X�R�A�̕���
typedef enum
{
	SCORE_NEW = 0,
	SCORE_OLD,
	SCORE_STYLE_MAX
}SCORE_STYLE;

//�X�R�A�\���p�\����
typedef struct
{
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
}SCORE;

//�v���g�^�C�v�錾

/*����*/
void Init_Score(int nMode);

/*�j��*/
void Uninit_Score(void);

/*�X�V*/
void Update_Score(void);

/*�`��*/
void Draw_Score(void);

/*�X�R�A�\���p�Ƀf�[�^��t�^*/
void SetInfo_Score(int nMode);

/*�X�R�A�\���p�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Score(void);

/*�X�R�A�\���p�̃e�N�X�`�����X�V*/
void Update_Tex_Score(void);

/*�X�R�A����e�N�X�`�������v�Z*/
void Calc_Tex_Score(void);

/*��*/
void Animation_Score(void);

/*�X�R�A�\���p�̃A�h���X���擾*/
SCORE* GetInfo_SCORE(void);

/*�X�R�A�̃A�h���X���擾*/
int* GetInfo_Score(void);

/*�A�j���[�V��������*/
int* GetInfo_S_A_CT(void);

#endif