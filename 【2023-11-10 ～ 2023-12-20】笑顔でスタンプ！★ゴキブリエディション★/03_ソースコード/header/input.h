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
enum JOYKEY
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
};

//�v���g�^�C�v�錾

HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//�L�[�{�[�h����
void UnInitKeyboard(void);	//�L�[�{�[�h�j��
void UpdateKeyboard(void);	//�L�[�{�[�h�X�V
bool GetKeyboardPress(int nKey);	//�L�[�{�[�h�v���X
bool GetKeyboardTrigger(int nKey);	//�L�[�{�[�h�g���K�[
HRESULT InitJoypad(void);	//�R���g���[���[����
void UninitJoypad(void);	//�R���g���[���[�j��
void UpdateJoypad(void);	//�R���g���[���[�X�V
bool GetJoypadPress(JOYKEY key);	//�R���g���[���[�v���X
bool GetJoypadTrigger(JOYKEY key);	//�R���g���[���[�g���K�[
XINPUT_GAMEPAD GetGamePad(void);
bool GetPressTriggerButtonL(void);	//���g���K�[�{�^���̃v���X����
bool GetPressTriggerButtonR(void);	//�E�g���K�[�{�^���̃v���X����
bool GetTriggerTriggerButtonR(void);	//�E�g���K�[�{�^���̃g���K�[����
bool GetJoyStickL(void);	//���X�e�B�b�N����
bool GetJoyStickR(void);	//�E�X�e�B�b�N����
void AdjustJoyStick(void);	//�R���g���[�����͂̂�����
WORD ConvertJoyStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);	//���X�e�B�b�N���\���L�[�ɕϊ�
void SetVibration(int time, WORD strength);	//�R���g���[���[�U��

#endif