//************************************************
//
//キー入力処理[input.cpp]
//Author：福田歩希
//
//************************************************
#include "input.h"

// to do リスト
// コントローラ早く実装しろ
// マウス実装しろ
// アケコン使えるようにしろ
// 先輩よりすごいもん作れ

//マクロ定義
#define NUM_KEY_MAX	(256)	//キーの最大数

//グローバル変数
LPDIRECTINPUT8 g_Input = NULL;				//DirectInputオブジェクトのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	//入力デバイス(キーボード)へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];				//キーボードのプレス情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];		//キーボードのトリガー情報
XINPUT_STATE g_JoyKeyState;					//コントローラのプレス情報
XINPUT_STATE g_JoyKeyStateTrigger;			//コントローラのトリガー情報
bool bJoyKeyTrigger;						//トリガーかどうか
XINPUT_VIBRATION g_JoypadMotor;				//コントローラのモーター情報			
int g_nTime;								//振動持続時間
WORD g_Strength;							//振動の強さ (0 ～ 65535)

//************************************************
//キー入力用初期化処理関数
//************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_Input, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス(キーボード)の生成
	if (FAILED(g_Input->CreateDevice(GUID_SysKeyboard,&g_pDevKeyboard,NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットの設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//************************************************
//キー入力用終了処理関数
//************************************************
void UnInitKeyboard(void)
{
	//入力デバイス(キーボード)の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	//キーボードの入力情報
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_Input != NULL)
	{
		g_Input->Release();
		g_Input = NULL;
	}
}

//************************************************
//キー入力用更新処理関数
//************************************************
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];	//キーボードの入力情報
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//キーボードのトリガー情報を保存
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];

			//キーボードのプレス情報を保存
			g_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		//キーボードのアクセス権を獲得
		g_pDevKeyboard->Acquire();
	}
}

//************************************************
//キーボードのプレス情報を取得関数
//************************************************
bool GetKeyboardPress(int nKey)
{
	return((g_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//************************************************
//キーボードのトリガー情報を取得関数
//************************************************
bool GetKeyboardTrigger(int nKey)
{
	return((g_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//************************************************
//コントローラ入力用初期化処理関数
//************************************************
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_JoyKeyState, 0, sizeof(XINPUT_STATE));

	//メモリのクリア
	memset(&g_JoyKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	//メモリのクリア
	memset(&g_JoypadMotor, 0, sizeof(XINPUT_VIBRATION));

	//XInputのステート設定(?)とかいうのを有効にする
	XInputEnable(true);

	return S_OK;
}

//************************************************
//コントローラ入力用終了処理関数
//************************************************
void UninitJoypad(void)
{
	//XInputのステート設定(?)とかいうのを無効にする
	XInputEnable(false);
}

//************************************************
//コントローラ入力用更新処理関数
//************************************************
void UpdateJoypad(void)
{
	XINPUT_STATE JoyKeyState;	//コントローラの入力情報(g_とは別)

	//コントローラの状態を取得
	if (XInputGetState(0, &JoyKeyState) == ERROR_SUCCESS)
	{
		//左スティックからの入力を方向ボタンに変換
		JoyKeyState.Gamepad.wButtons |= GetJoypadStick(g_JoyKeyState.Gamepad.sThumbLX, g_JoyKeyState.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

		//コントローラのトリガー情報を保存
		g_JoyKeyStateTrigger.Gamepad.wButtons = (g_JoyKeyState.Gamepad.wButtons ^ JoyKeyState.Gamepad.wButtons) & JoyKeyState.Gamepad.wButtons;
	
		//コントローラのプレス情報を保存
		g_JoyKeyState = JoyKeyState;
	}

	//振動
	g_JoypadMotor.wLeftMotorSpeed = g_Strength;		//左のモーター
	g_JoypadMotor.wRightMotorSpeed = g_Strength;	//右のモーター

	XInputSetState(0, &g_JoypadMotor);	//振動情報を送る

	//振動時間の減算
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
//コントローラのプレス情報を取得関数
//************************************************
bool GetJoypadPress(JOYKEY key)
{
	return (g_JoyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//************************************************
//コントローラのトリガー情報を取得関数
//************************************************
bool GetJoypadTrigger(JOYKEY key)
{
	return (g_JoyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//************************************************
//コントローラのスティックをボタンに変換関数
//************************************************
WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	//ボタン入力の情報に置き換え用
	WORD wButtons = 0;

	//スティック上側に倒したとき
	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	//下に
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	//左
	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	//右
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	//ボタン入力信号をリターン
	return wButtons;
}

//************************************************
//コントローラの振動を設定関数
//************************************************
void SetVibration(int time, WORD strength)
{
	g_nTime = time;
	g_Strength = strength;
}