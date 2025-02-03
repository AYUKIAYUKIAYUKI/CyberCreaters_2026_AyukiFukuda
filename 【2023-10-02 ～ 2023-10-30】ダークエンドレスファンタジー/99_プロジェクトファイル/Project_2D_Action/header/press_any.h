//************************************************
//
//�Ñ������A�w�b�_�t�@�C��[logo_title.h]
//Author�F���c����
//
//************************************************
#ifndef _PRESS_ANY_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PRESS_ANY_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_PRESS_ANY_MENU	"data\\TEX\\startgame.png"
#define	TEXTURE_PRESS_ANY_RESULT	"data\\TEX\\endgame.png"

#define AMOUNT_TEX_PRESS_ANY	(2)	//�e�N�X�`����

#define RADIUS_PRESS_ANY_X	(850.0f)	//������
#define RADIUS_PRESS_ANY_Y	(100.0f)	//�c����

//�Ñ��̕���
typedef enum
{
	PRESS_TYPE_MENU = 0,
	PRESS_TYPE_RESULT,
	PRESS_TYPE_MAX,
}PRESS_ANY_TYPE;

//�Ñ����̍\����
typedef struct
{
	int nType;			//����
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}PRESS_ANY;

//�v���g�^�C�v�錾

/*����*/
void Init_Press_Any(int nMode);

/*�j��*/
void Uninit_Press_Any(void);

/*�X�V*/
void Update_Press_Any(void);

/*�`��*/
void Draw_Press_Any(void);

/*�Ñ��Ƀf�[�^��t�^*/
void SetInfo_Press_Any(void);

/*�Ñ��̃o�[�e�b�N�X���X�V*/
void Update_Pos_Press_Any(void);

/*�Ñ��̃o�[�e�b�N�X�J���[���X�V*/
void Update_Col_Press_Any(void);

/*�Ñ��̏����擾*/
PRESS_ANY* GetInfo_Press_Any(void);

#endif