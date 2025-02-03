//************************************************
//
// キー入力処理[input.cpp]
// Author：福田歩希, kasai keisuke
//
//************************************************

/*/ インクルードファイル /*/
#include "input.h"

/*/ マクロ定義 /*/
#define NUM_KEY_MAX	256	// キーの最大数

/*/ グローバル変数 /*/
LPDIRECTINPUT8 g_Input = NULL;				// DirectInputオブジェクトのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	// 入力デバイス(キーボード)へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];				// キーボードのプレス情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];		// キーボードのトリガー情報
XINPUT_STATE g_JoyKeyState[MAX_PLAYER];		//コントローラーのプレス情報(人数分)
XINPUT_STATE g_JoyKeyStateTrigger[MAX_PLAYER];//コントローラーのトリガー情報(人数分)
bool bJoyKeyTrigger;						// トリガーかどうか
XINPUT_VIBRATION g_JoypadMotor;				// コントローラのモーター情報			
int g_nTime;								// 振動持続時間
WORD g_Strength;							// 振動の強さ (0 ～ 65535)

//************************************************
// キー入力初期
//************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_Input, NULL)))
	{ // DirectInputオブジェクトの生成
		return E_FAIL;
	}

	if (FAILED(g_Input->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{ // 入力デバイス(キーボード)の生成
		return E_FAIL;
	}

	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{ // データフォーマットの設定
		return E_FAIL;
	}

	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{ // 協調モードを設定
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//************************************************
// キー入力終了
//************************************************
void UnInitKeyboard(void)
{
	if (g_pDevKeyboard != NULL)
	{ // 入力デバイス(キーボード)の破棄
		g_pDevKeyboard->Unacquire();	// キーボードの入力情報
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	if (g_Input != NULL)
	{ // DirectInputオブジェクトの破棄
		g_Input->Release();
		g_Input = NULL;
	}
}

//************************************************
// キー入力更新
//************************************************
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	// キーボードの入力情報
	int nCntKey;

	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{ // 入力デバイスからデータを取得
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// キーボードのトリガー情報を保存
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];

			// キーボードのプレス情報を保存
			g_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		// キーボードのアクセス権を獲得
		g_pDevKeyboard->Acquire();
	}
}

//************************************************
// キーボードのプレス情報を取得
//************************************************
bool GetKeyboardPress(int nKey)
{
	return((g_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//************************************************
// キーボードのトリガー情報を取得
//************************************************
bool GetKeyboardTrigger(int nKey)
{
	return((g_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//************************************************
// コントローラ入力初期
//************************************************
HRESULT InitJoypad(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		//メモリのクリア
		memset(&g_JoyKeyState[nCntPlayer], 0, sizeof(XINPUT_STATE));

		//メモリのクリア
		memset(&g_JoyKeyStateTrigger[nCntPlayer], 0, sizeof(XINPUT_STATE));

		//コントローラーの初期化
		if (XInputGetState(nCntPlayer, &g_JoyKeyState[nCntPlayer]) == ERROR_SUCCESS)
		{
			g_JoyKeyStateTrigger[nCntPlayer] = g_JoyKeyState[nCntPlayer];
		}
	}

	// XInputのステート設定(?)とかいうのを有効にする
	XInputEnable(true);

	return S_OK;
}

//************************************************
// コントローラ終了
//************************************************
void UninitJoypad(void)
{
	// XInputのステート設定(?)とかいうのを無効にする
	XInputEnable(false);
}

//==================================================
//ゲームパッド更新
//==================================================
void UpdateJoypad()
{
	XINPUT_STATE joykeystate[MAX_PLAYER] = {};

	for (int PadNum = 0; PadNum < XUSER_MAX_COUNT; PadNum++)
	{
		//ジョイパッドの状態を取得
		if (XInputGetState(PadNum, &joykeystate[PadNum]) == ERROR_SUCCESS)
		{
			AdjustJoyStick();	// スティックの傾きのあそび

			//コントローラーのトリガー情報を保存
			g_JoyKeyStateTrigger[PadNum].Gamepad.wButtons = (g_JoyKeyState[PadNum].Gamepad.wButtons ^ joykeystate[PadNum].Gamepad.wButtons) & joykeystate[PadNum].Gamepad.wButtons;
			g_JoyKeyStateTrigger[PadNum].Gamepad.bLeftTrigger = (g_JoyKeyState[PadNum].Gamepad.bLeftTrigger ^ joykeystate[PadNum].Gamepad.bLeftTrigger) & joykeystate[PadNum].Gamepad.bLeftTrigger;
			g_JoyKeyStateTrigger[PadNum].Gamepad.bRightTrigger = (g_JoyKeyState[PadNum].Gamepad.bRightTrigger ^ joykeystate[PadNum].Gamepad.bRightTrigger) & joykeystate[PadNum].Gamepad.bRightTrigger;

			g_JoyKeyState[PadNum] = joykeystate[PadNum];
		}
	}
}
//************************************************
// コントローラのプレス情報を取得
//************************************************
bool GetJoypadPress(JOYKEY key, int nContIndex)
{
	return (g_JoyKeyState[nContIndex].Gamepad.wButtons & (0x01 << key)) ? true : false;

}

//************************************************
// コントローラのトリガー情報を取得
//************************************************
bool GetJoypadTrigger(JOYKEY key, int nContIndex)
{
	return (g_JoyKeyStateTrigger[nContIndex].Gamepad.wButtons & (0x01 << key)) ? true : false;

}

//************************************************
// ゲームパッドの情報を取得
//************************************************
XINPUT_GAMEPAD GetGamePad(int nContIndex)
{
		return g_JoyKeyState[nContIndex].Gamepad;
}

//************************************************
// コントローラの左トリガーボタンのプレス入力
//************************************************
bool GetPressTriggerButtonL(int nContIndex)
{
	return (g_JoyKeyState[nContIndex].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
}

//************************************************
// コントローラの右トリガーボタンのプレス入力
//************************************************
bool GetPressTriggerButtonR(int nContIndex)
{
	return (g_JoyKeyState[nContIndex].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
}

//************************************************
// コントローラの左トリガーボタンのトリガー入力
//************************************************
bool GetTriggerTriggerButtonL(int nContIndex)
{
	return (g_JoyKeyStateTrigger[nContIndex].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
}

//************************************************
// コントローラの右トリガーボタンのトリガー入力
//************************************************
bool GetTriggerTriggerButtonR(int nContIndex)
{
	return (g_JoyKeyStateTrigger[nContIndex].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD + 30.0f);
}

//************************************************
// コントローラの左スティック入力
//************************************************
bool GetJoyStickL(int nContIndex)
{
	return (g_JoyKeyState[nContIndex].Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState[nContIndex].Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState[nContIndex].Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState[nContIndex].Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

}

//************************************************
// コントローラの右スティック入力
//************************************************
bool GetJoyStickR(int nContIndex)
{
	return (g_JoyKeyState[nContIndex].Gamepad.sThumbRX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState[nContIndex].Gamepad.sThumbRX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState[nContIndex].Gamepad.sThumbRY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		g_JoyKeyState[nContIndex].Gamepad.sThumbRY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
}

//************************************************
// コントローラのスティック入力のあそび
//************************************************
void AdjustJoyStick(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (g_JoyKeyState[nCntPlayer].Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{ // 左
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbLX = 0;
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbLY = 0;
		}

		if (g_JoyKeyState[nCntPlayer].Gamepad.sThumbRX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbRX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbRY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbRY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{ // 右
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbRX = 0;
			g_JoyKeyState[nCntPlayer].Gamepad.sThumbRY = 0;
		}

	}

}

//************************************************
// コントローラの左スティックを十字キーに変換
//************************************************
WORD ConvertJoyStick(SHORT sThumbLX, SHORT sThumbLY, SHORT sDeadZone)
{
	// ボタン入力の情報に置き換え用
	WORD wButtons = 0;

	if (sThumbLY >= sDeadZone)
	{ // スティック上側に倒したとき
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbLY <= -sDeadZone)
	{ // スティック上側に倒したとき
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbLX <= -sDeadZone)
	{ // 左
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbLX >= sDeadZone)
	{ // 右
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	// ボタン入力信号をリターン
	return wButtons;
}

//************************************************
// コントローラの振動を設定
//************************************************
void SetVibration(int time, WORD strength)
{
	g_nTime = time;
	g_Strength = strength;
}

