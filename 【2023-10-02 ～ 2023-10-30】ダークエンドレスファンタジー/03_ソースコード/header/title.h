//************************************************
//
//�^�C�g�������A�w�b�_�t�@�C��[title.h]
//Author�F���c����
//
//************************************************
#ifndef _TITLE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TITLE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�^�C�g�����j���[�̑I����
typedef enum
{
	START = 0,
	RANKING,
	END,
	TITLE_MENU_MAX,
}TITLE_MENU;

/*����*/
void Init_Title(void);

/*�j��*/
void Uninit_Title(void);

/*�X�V*/
void Update_Title(void);

/*�`��*/
void Draw_Title(void);

/*�^�C�g�����j���[�̑I�����ڂ������n��*/
int* Getinfo_Choose_Title_Menu(void);

#endif