//************************************************
//
//�^�C�g���e�L�X�g�����A�w�b�_�t�@�C��[text_title.h]
//Author�F���c����
//
//************************************************
#ifndef _TEXT_TITLE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TEXT_TITLE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_TEXT_TITLE_1	"data\\TEX\\start.png"
#define	TEXTURE_TEXT_TITLE_2	"data\\TEX\\ranking.png"
#define	TEXTURE_TEXT_TITLE_3	"data\\TEX\\end.png"

#define AMOUNT_POLYGON_TEXT_TITLE	(3)	//�^�C�g���e�L�X�g�̃|���S���ő吔
#define AMOUNT_TEX_TEXT_TITLE	(3)	//�^�C�g���e�L�X�g�̃e�N�X�`������

#define RADIUS_TEXT_TITLE_X	(250.0f)	//������
#define RADIUS_TEXT_TITLE_Y	(60.0f)	//�c����

//�^�C�g���e�L�X�g���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}TEXT_TITLE;

//�v���g�^�C�v�錾

/*����*/
void Init_Text_Title(void);

/*�j��*/
void Uninit_Text_Title(void);

/*�X�V*/
void Update_Text_Title(void);

/*�`��*/
void Draw_Text_Title(void);

/*�e�L�X�g�Ƀf�[�^��t�^*/
void SetInfo_Text_Title(void);

/*�e�L�X�g�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Text_Title(void);

/*�e�L�X�g�̃o�[�e�b�N�X�J���[���X�V*/
void Update_Col_Text_Title(void);

/*�e�L�X�g�̏����擾*/
TEXT_TITLE* GetInfo_Text_Title(void);

#endif