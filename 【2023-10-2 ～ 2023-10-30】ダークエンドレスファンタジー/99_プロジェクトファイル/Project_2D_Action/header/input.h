//************************************************
//
//�L�[���͏����A�w�b�_�t�@�C��[input.h]
//Author�F���c����
//
//************************************************
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//�R���g���[�����͗񋓌^
typedef enum
{
	JOYKEY_UP = 0,
	JOYKEY_DOWN,
	JOYKEY_LEFT,
	JOYKEY_RIGHT,
	JOYKEY_START,
	JOYKEY_BACK,
	JOYKEY_L3,
	JOYKEY_R3,
	JOYKEY_L,
	JOYKEY_R,
	JOYKEY_NONE1,
	JOYKEY_NONE2,
	JOYKEY_A,
	JOYKEY_B,
	JOYKEY_X,
	JOYKEY_Y,
	JOYKEY_MAX,
}JOYKEY;

//�v���g�^�C�v�錾

/*�L�[�{�[�h�̐���*/
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);

/*�L�[�{�[�h�̔j��*/
void UnInitKeyboard(void);

/*�L�[�{�[�h�̍X�V*/
void UpdateKeyboard(void);

/*�L�[�{�[�h�̃v���X����*/
bool GetKeyboardPress(int nKey);

/*�L�[�{�[�h�̃g���K�[����*/
bool GetKeyboardTrigger(int nKey);

/*�R���g���[���[�̃X�^�[�g*/
HRESULT InitJoypad(void);

/*�R���g���[���[�̔j��*/
void UninitJoypad(void);

/*�R���g���[���[�̍X�V*/
void UpdateJoypad(void);

/*�R���g���[���[�̃v���X����*/
bool GetJoypadPress(JOYKEY key);

/*�R���g���[���[�̃g���K�[����*/
bool GetJoypadTrigger(JOYKEY key);

/*�R���g���[���[�̃X�e�B�b�N����*/
WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);

/*�R���g���[���[�̐U��*/
void SetVibration(int time, WORD strength);

#endif