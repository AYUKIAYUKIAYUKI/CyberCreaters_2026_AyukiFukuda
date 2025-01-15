//************************************************
//
//�^�C�g�����S�����A�w�b�_�t�@�C��[logo_title.h]
//Author�F���c����
//
//************************************************
#ifndef _LOGO_TITLE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _LOGO_TITLE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_LOGO_TITLE	"data\\TEX\\logo_title.png"

#define RADIUS_LOGO_TITLE_X	(850.0f)	//������
#define RADIUS_LOGO_TITLE_Y	(100.0f)	//�c����

//�^�C�g�����S���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}LOGO_TITLE;

//�v���g�^�C�v�錾

/*����*/
void Init_Logo_Title(void);

/*�j��*/
void Uninit_Logo_Title(void);

/*�X�V*/
void Update_Logo_Title(void);

/*�`��*/
void Draw_Logo_Title(void);

/*���S�Ƀf�[�^��t�^*/
void SetInfo_Logo_Title(void);

/*���S�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Logo_Title(void);

/*���S�̏����擾*/
LOGO_TITLE* GetInfo_Logo_Title(void);

#endif