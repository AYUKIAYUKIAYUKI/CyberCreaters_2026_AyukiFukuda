//************************************************
//
//�E�B���h�E���j���[�����A�w�b�_�t�@�C��[window_menu.h]
//Author�F���c����
//
//************************************************
#ifndef _WINDOW_MENU_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _WINDOW_MENU_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_WINDOW_MENU	"data\\TEX\\tutorial2.png"

#define RADIUS_WINDOW_MENU_X	(990.0f)	//������
#define RADIUS_WINDOW_MENU_Y	(540.0f)	//�c����

//�e�X�g���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength[2];	//�Ίp��
	float fAngle[2];	//�p�x
}WINDOW_MENU;

//�v���g�^�C�v�錾

/*����*/
void Init_Window_Menu(void);

/*�j��*/
void Uninit_Window_Menu(void);

/*�X�V*/
void Update_Window_Menu(void);

/*�`��*/
void Draw_Window_Menu(void);

/*�E�B���h�E�Ƀf�[�^��t�^*/
void SetInfo_Window_Menu(void);

/*�E�B���h�E�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Window_Menu(void);

/*�E�B���h�E�̃f�[�^���擾*/
WINDOW_MENU* GetInfo_Window_Menu(void);

#endif