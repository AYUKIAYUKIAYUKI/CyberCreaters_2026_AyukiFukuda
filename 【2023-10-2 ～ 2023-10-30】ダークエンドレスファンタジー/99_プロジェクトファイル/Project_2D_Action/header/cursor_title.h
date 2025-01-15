//************************************************
//
//�^�C�g���J�[�\�������A�w�b�_�t�@�C��[cursor_title.h]
//Author�F���c����
//
//************************************************
#ifndef _CURSOR_TITLE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _CURSOR_TITLE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_CURSOR_TITLE_1	"data\\TEX\\dain.png"

#define RADIUS_CURSOR_TITLE_X	(50.0f)	//������
#define RADIUS_CURSOR_TITLE_Y	(50.0f)	//�c����

//�^�C�g���J�[�\�����̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}CURSOR_TITLE;

//�v���g�^�C�v�錾

/*����*/
void Init_Cursor_Title(void);

/*�j��*/
void Uninit_Cursor_Title(void);

/*�X�V*/
void Update_Cursor_Title(void);

/*�`��*/
void Draw_Cursor_Title(void);

/*�J�[�\���Ƀf�[�^��t�^*/
void SetInfo_Cursor_Title(void);

/*�J�[�\���̃o�[�e�b�N�X���X�V*/
void Update_Pos_Cursor_Title(void);

/*�J�[�\���̏����擾*/
CURSOR_TITLE* GetInfo_Cursor_Title(void);

#endif