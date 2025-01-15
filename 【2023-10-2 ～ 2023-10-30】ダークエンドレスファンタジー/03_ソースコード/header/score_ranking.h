//************************************************
//
//�X�R�A(�����L���O)�����A�w�b�_�t�@�C��[score_ranking.h]
//Author�F���c����
//
//************************************************
#ifndef _SCORE_RANKING_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _SCORE_RANKING_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_SCORE_RANKING	"data\\TEX\\number.png"

#define AMOUNT_POLYGON_SCORE_RANKING	(16)	//�|���S����

#define SPAN_EACH_POLYGON_SCORE_RANKING	(30.0f)	//�|���S������ׂ�Ԋu
#define MOVE_SPAN_TEX_SCORE_RANKING	(0.1f)			//�e�N�X�`������

//�X�R�A�̕���
typedef enum
{
	SCORE_RANKING_HIGH = 0,
	SCORE_RANKING_LAST,
	SCORE_RANKING_STYLE_MAX
}SCORE_RANKING_STYLE;

//�X�R�A�\���p�\����
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
}SCORE_RANKING;

//�v���g�^�C�v�錾

/*����*/
void Init_Score_Ranking(void);

/*�j��*/
void Uninit_Score_Ranking(void);

/*�X�V*/
void Update_Score_Ranking(void);

/*�`��*/
void Draw_Score_Ranking(void);

/*�X�R�A�\���p�Ƀf�[�^��t�^*/
void SetInfo_Score_Ranking(void);

/*�ߋ��̃X�R�A��ǂݎ��*/
void ReadInfo_Score_Ranking(void);

/*�X�R�A�\���p�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Score_Ranking(void);

/*�X�R�A�\���p�̃e�N�X�`�����X�V*/
void Update_Tex_Score_Ranking(void);

/*�X�R�A����e�N�X�`�������v�Z*/
void Calc_Tex_Score_Ranking(void);

/*�X�R�A�\���p(��񂫂�)�̃A�h���X���擾*/
SCORE_RANKING* GetInfo_Score_Ranking(void);

#endif