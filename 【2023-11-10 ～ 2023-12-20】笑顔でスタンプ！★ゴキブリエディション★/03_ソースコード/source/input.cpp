//************************************************
//
//�L�[���͏���[input.cpp]
//Author�F���c����
//
//************************************************
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX	(256)	//�L�[�̍ő吔

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_Input = NULL;				//DirectInput�I�u�W�F�N�g�̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];				//�L�[�{�[�h�̃v���X���
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];		//�L�[�{�[�h�̃g���K�[���
XINPUT_STATE g_JoyKeyState;					//�R���g���[���̃v���X���
XINPUT_STATE g_JoyKeyStateTrigger;			//�R���g���[���̃g���K�[���
bool bJoyKeyTrigger;						//�g���K�[���ǂ���
XINPUT_VIBRATION g_JoypadMotor;				//�R���g���[���̃��[�^�[���			
int g_nTime;								//�U����������
WORD g_Strength;							//�U���̋��� (0 �` 65535)

//************************************************
//�L�[���͏���
//************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_Input, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_Input->CreateDevice(GUID_SysKeyboard,&g_pDevKeyboard,NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//************************************************
//�L�[���͏I��
//************************************************
void UnInitKeyboard(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	//�L�[�{�[�h�̓��͏��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_Input != NULL)
	{
		g_Input->Release();
		g_Input = NULL;
	}
}

//************************************************
//�L�[���͍X�V
//************************************************
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//�L�[�{�[�h�̃g���K�[����ۑ�
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];

			//�L�[�{�[�h�̃v���X����ۑ�
			g_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		//�L�[�{�[�h�̃A�N�Z�X�����l��
		g_pDevKeyboard->Acquire();
	}
}

//************************************************
//�L�[�{�[�h�̃v���X�����擾
//************************************************
bool GetKeyboardPress(int nKey)
{
	return((g_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//************************************************
//�L�[�{�[�h�̃g���K�[�����擾
//************************************************
bool GetKeyboardTrigger(int nKey)
{
	return((g_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//************************************************
//�R���g���[�����͏���
//************************************************
HRESULT InitJoypad(void)
{
	//�������̃N���A
	memset(&g_JoyKeyState, 0, sizeof(XINPUT_STATE));

	//�������̃N���A
	memset(&g_JoyKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	//�������̃N���A
	memset(&g_JoypadMotor, 0, sizeof(XINPUT_VIBRATION));

	//XInput�̃X�e�[�g�ݒ�(?)�Ƃ������̂�L���ɂ���
	XInputEnable(true);

	return S_OK;
}

//************************************************
//�R���g���[���I��
//************************************************
void UninitJoypad(void)
{
	//XInput�̃X�e�[�g�ݒ�(?)�Ƃ������̂𖳌��ɂ���
	XInputEnable(false);
}

//************************************************
//�R���g���[���X�V
//************************************************
void UpdateJoypad(void)
{
	XINPUT_STATE JoyKeyState;	//�R���g���[���̓��͏��(g_�Ƃ͕�)

	//�R���g���[���̏�Ԃ��擾
	if (XInputGetState(0, &JoyKeyState) == ERROR_SUCCESS)
	{
		//���X�e�B�b�N����̓��͂��\���L�[�ɕϊ�
		JoyKeyState.Gamepad.wButtons |= ConvertJoyStick(g_JoyKeyState.Gamepad.sThumbLX, g_JoyKeyState.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

		//�R���g���[���̃g���K�[����ۑ�
		g_JoyKeyStateTrigger.Gamepad.wButtons = (g_JoyKeyState.Gamepad.wButtons ^ JoyKeyState.Gamepad.wButtons) & JoyKeyState.Gamepad.wButtons;
		g_JoyKeyStateTrigger.Gamepad.bLeftTrigger = (g_JoyKeyState.Gamepad.bLeftTrigger ^ JoyKeyState.Gamepad.bLeftTrigger) & JoyKeyState.Gamepad.bLeftTrigger;
		g_JoyKeyStateTrigger.Gamepad.bRightTrigger = (g_JoyKeyState.Gamepad.bRightTrigger ^ JoyKeyState.Gamepad.bRightTrigger) & JoyKeyState.Gamepad.bRightTrigger;
	
		//�R���g���[���̃v���X����ۑ�
		g_JoyKeyState = JoyKeyState;
	}

	AdjustJoyStick();	//�X�e�B�b�N�̌X���̂�����

	//�U��
	g_JoypadMotor.wLeftMotorSpeed = g_Strength;		//���̃��[�^�[
	g_JoypadMotor.wRightMotorSpeed = g_Strength;	//�E�̃��[�^�[

	XInputSetState(0, &g_JoypadMotor);	//�U�����𑗂�

	//�U�����Ԃ̌��Z
	if (g_nTime > 0)
	{
		g_nTime--;
	}
	else
	{
		g_nTime = 0;
		g_Strength = 0;
	}
}

//************************************************
//�R���g���[���̃v���X�����擾
//************************************************
bool GetJoypadPress(JOYKEY key)
{
	return (g_JoyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//************************************************
//�R���g���[���̃g���K�[�����擾
//************************************************
bool GetJoypadTrigger(JOYKEY key)
{
	return (g_JoyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//************************************************
//�Q�[���p�b�h�̏����擾
//************************************************
XINPUT_GAMEPAD GetGamePad(void)
{
	return g_JoyKeyState.Gamepad;
}

//************************************************
//�R���g���[���̍��g���K�[�{�^���̃v���X����
//************************************************
bool GetPressTriggerButtonL(void)
{
	return (g_JoyKeyState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
}

//************************************************
//�R���g���[���̉E�g���K�[�{�^���̃v���X����
//************************************************
bool GetPressTriggerButtonR(void)
{
	return (g_JoyKeyState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
}

//************************************************
//�R���g���[���̉E�g���K�[�{�^���̃g���K�[����
//************************************************
bool GetTriggerTriggerButtonR(void)
{
	return (g_JoyKeyStateTrigger.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
}

//************************************************
//�R���g���[���̍��X�e�B�b�N����
//************************************************
bool GetJoyStickL(void)
{
	return (g_JoyKeyState.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
}

//************************************************
//�R���g���[���̉E�X�e�B�b�N����
//************************************************
bool GetJoyStickR(void)
{
	return (g_JoyKeyState.Gamepad.sThumbRX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState.Gamepad.sThumbRY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
}

//************************************************
//�R���g���[���̃X�e�B�b�N���͂̂�����
//************************************************
void AdjustJoyStick(void)
{
	//��
	if (g_JoyKeyState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_JoyKeyState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_JoyKeyState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_JoyKeyState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		g_JoyKeyState.Gamepad.sThumbLX = 0;
		g_JoyKeyState.Gamepad.sThumbLY = 0;
	}

	//�E
	if (g_JoyKeyState.Gamepad.sThumbRX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_JoyKeyState.Gamepad.sThumbRX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_JoyKeyState.Gamepad.sThumbRY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_JoyKeyState.Gamepad.sThumbRY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		g_JoyKeyState.Gamepad.sThumbRX = 0;
		g_JoyKeyState.Gamepad.sThumbRY = 0;
	}
}

//************************************************
//�R���g���[���̍��X�e�B�b�N���\���L�[�ɕϊ�
//************************************************
WORD ConvertJoyStick(SHORT sThumbLX, SHORT sThumbLY, SHORT sDeadZone)
{
	//�{�^�����͂̏��ɒu�������p
	WORD wButtons = 0;

	//�X�e�B�b�N�㑤�ɓ|�����Ƃ�
	if (sThumbLY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	//����
	else if (sThumbLY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	//��
	if (sThumbLX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	//�E
	else if (sThumbLX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	//�{�^�����͐M�������^�[��
	return wButtons;
}

//************************************************
//�R���g���[���̐U����ݒ�
//************************************************
void SetVibration(int time, WORD strength)
{
	g_nTime = time;
	g_Strength = strength;
}