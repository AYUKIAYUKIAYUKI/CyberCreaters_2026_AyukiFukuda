//************************************************
//
//�Q�[�������A�w�b�_�t�@�C��[game.h]
//Author�F���c����
//
//************************************************
#ifndef _GAME_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _GAME_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�|�[�Y���j���[�̑I����
typedef enum
{
	CONTINUE = 0,
	RETRY,
	RETIRE,
	RESULT,
	PAUSE_MENU_MAX,
}PAUSE_MENU;

//�v���g�^�C�v�錾

/*����*/
void Init_Game(void);

/*�I��*/
void Uninit_Game(void);

/*�X�V*/
void Update_Game(void);

/*�`��*/
void Draw_Game(void);

/*�|�[�Y���j���[�̑I�����ڂ������n��*/
int* Getinfo_Choose_Pause_Menu(void);

/*�X�R�A���L�^����*/
void Save_Score(void);

#endif