//************************************************
//
//�`���[�g���A���A�w�b�_�t�@�C��[tutorial.h]
//Author�F���c����
//
//************************************************
#ifndef _TUTORIAL_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TUTORIAL_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_EXPLAIN_TUTORIAL	"data\\TEX\\01_menu\\tutorial.png"

#define AMOUNT_POLYGON_TUTORIAL	(1)

typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�F
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}TUTORIAL;

//�v���g�^�C�v�錾
void Init_Tutorial(void);
void Uninit_Tutorial(void);
void Update_Tutorial(void);
void Draw_Tutorial(void);
void Setinfo_Tutorial(void);
bool* Getinfo_Tutorial(void);

#endif