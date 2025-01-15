//************************************************
//
//�����L���O�e�L�X�g�����A�w�b�_�t�@�C��[text_title.h]
//Author�F���c����
//
//************************************************
#ifndef _TEXT_RANKING_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TEXT_RANKING_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_TEXT_RANKING_1	"data\\TEX\\high_score.png"
#define	TEXTURE_TEXT_RANKING_2	"data\\TEX\\last_score.png"

#define AMOUNT_POLYGON_TEXT_RANKING	(2)	//�����L���O�e�L�X�g�̃|���S���ő吔
#define AMOUNT_TEX_TEXT_RANKING	(2)	//�����L���O�e�L�X�g�̃e�N�X�`������

#define RADIUS_TEXT_RANKING_X	(450.0f)	//������
#define RADIUS_TEXT_RANKING_Y	(100.0f)	//�c����

//�����L���O�e�L�X�g���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}TEXT_RANKING;

//�v���g�^�C�v�錾

/*����*/
void Init_Text_Ranking(void);

/*�j��*/
void Uninit_Text_Ranking(void);

/*�X�V*/
void Update_Text_Ranking(void);

/*�`��*/
void Draw_Text_Ranking(void);

/*�e�L�X�g�Ƀf�[�^��t�^*/
void SetInfo_Text_Ranking(void);

/*�e�L�X�g�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Text_Ranking(void);

/*�e�L�X�g�̏����擾*/
TEXT_RANKING* GetInfo_Text_Ranking(void);

#endif