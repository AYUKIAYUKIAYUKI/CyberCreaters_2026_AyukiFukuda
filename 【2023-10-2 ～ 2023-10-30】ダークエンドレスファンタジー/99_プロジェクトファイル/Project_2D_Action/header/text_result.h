//************************************************
//
//���U���g�e�L�X�g�����A�w�b�_�t�@�C��[logo_title.h]
//Author�F���c����
//
//************************************************
#ifndef _TEXT_RESULT_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TEXT_RESULT_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_TEXT_RESULT	"data\\TEX\\now_score.png"

#define RADIUS_TEXT_RESULT_X	(850.0f)	//������
#define RADIUS_TEXT_RESULT_Y	(100.0f)	//�c����

//���U���g�e�L�X�g���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}TEXT_RESULT;

//�v���g�^�C�v�錾

/*����*/
void Init_Text_Result(void);

/*�j��*/
void Uninit_Text_Result(void);

/*�X�V*/
void Update_Text_Result(void);

/*�`��*/
void Draw_Text_Result(void);

/*�e�L�X�g�Ƀf�[�^��t�^*/
void SetInfo_Text_Result(void);

/*�e�L�X�g�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Text_Result(void);

/*�e�L�X�g�̏����擾*/
TEXT_RESULT* GetInfo_Text_Result(void);

#endif