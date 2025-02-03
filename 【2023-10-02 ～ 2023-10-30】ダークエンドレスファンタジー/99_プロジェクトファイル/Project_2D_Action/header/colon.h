//************************************************
//
//�R���������A�w�b�_�t�@�C��[logo_title.h]
//Author�F���c����
//
//************************************************
#ifndef _COLON_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _COLON_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_COLON	"data\\TEX\\colon.png"

//�R�������̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}COLON;

//�v���g�^�C�v�錾

/*����*/
void Init_Colon(void);

/*�j��*/
void Uninit_Colon(void);

/*�X�V*/
void Update_Colon(void);

/*�`��*/
void Draw_Colon(void);

/*�R�����Ƀf�[�^��t�^*/
void SetInfo_Colon(void);

/*�R�����̃o�[�e�b�N�X���X�V*/
void Update_Pos_Colon(void);

/*�R�����̏����擾*/
COLON* GetInfo_Colon(void);

#endif