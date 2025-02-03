//************************************************
//
//�L�[���͏���[input.cpp]
//Author�F���c����
//
//************************************************
#include "input.h"

// to do ���X�g
// �R���g���[��������������
// �}�E�X��������
// �A�P�R���g����悤�ɂ���
// ��y��肷����������

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
//�L�[���͗p�����������֐�
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
//�L�[���͗p�I�������֐�
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
//�L�[���͗p�X�V�����֐�
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
//�L�[�{�[�h�̃v���X�����擾�֐�
//************************************************
bool GetKeyboardPress(int nKey)
{
	return((g_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//************************************************
//�L�[�{�[�h�̃g���K�[�����擾�֐�
//************************************************
bool GetKeyboardTrigger(int nKey)
{
	return((g_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//************************************************
//�R���g���[�����͗p�����������֐�
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
//�R���g���[�����͗p�I�������֐�
//************************************************
void UninitJoypad(void)
{
	//XInput�̃X�e�[�g�ݒ�(?)�Ƃ������̂𖳌��ɂ���
	XInputEnable(false);
}

//************************************************
//�R���g���[�����͗p�X�V�����֐�
//************************************************
void UpdateJoypad(void)
{
	XINPUT_STATE JoyKeyState;	//�R���g���[���̓��͏��(g_�Ƃ͕�)

	//�R���g���[���̏�Ԃ��擾
	if (XInputGetState(0, &JoyKeyState) == ERROR_SUCCESS)
	{
		//���X�e�B�b�N����̓��͂�����{�^���ɕϊ�
		JoyKeyState.Gamepad.wButtons |= GetJoypadStick(g_JoyKeyState.Gamepad.sThumbLX, g_JoyKeyState.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

		//�R���g���[���̃g���K�[����ۑ�
		g_JoyKeyStateTrigger.Gamepad.wButtons = (g_JoyKeyState.Gamepad.wButtons ^ JoyKeyState.Gamepad.wButtons) & JoyKeyState.Gamepad.wButtons;
	
		//�R���g���[���̃v���X����ۑ�
		g_JoyKeyState = JoyKeyState;
	}

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
//�R���g���[���̃v���X�����擾�֐�
//************************************************
bool GetJoypadPress(JOYKEY key)
{
	return (g_JoyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//************************************************
//�R���g���[���̃g���K�[�����擾�֐�
//************************************************
bool GetJoypadTrigger(JOYKEY key)
{
	return (g_JoyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//************************************************
//�R���g���[���̃X�e�B�b�N���{�^���ɕϊ��֐�
//************************************************
WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	//�{�^�����͂̏��ɒu�������p
	WORD wButtons = 0;

	//�X�e�B�b�N�㑤�ɓ|�����Ƃ�
	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	//����
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	//��
	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	//�E
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	//�{�^�����͐M�������^�[��
	return wButtons;
}

//************************************************
//�R���g���[���̐U����ݒ�֐�
//************************************************
void SetVibration(int time, WORD strength)
{
	g_nTime = time;
	g_Strength = strength;
}