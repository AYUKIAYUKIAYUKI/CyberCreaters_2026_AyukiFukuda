//============================================================================
// 
// 入力処理管理 [input.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "input.h"

//****************************************************
// 静的メンバの初期化
//****************************************************
LPDIRECTINPUT8 CInput::m_Input = nullptr;	// // DirectInputオブジェクト

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CInput::CInput() :
	m_pDevice{ nullptr }	// 入力デバイス情報
{

}

//============================================================================
// デストラクタ
//============================================================================
CInput::~CInput()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_Input == nullptr)
	{
		// DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(&m_Input), nullptr)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CInput::Uninit()
{
	// 入力デバイスの破棄
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	// DirectInputオブジェクトの破棄
	if (m_Input != nullptr)
	{
		m_Input->Release();
		m_Input = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CInputKeyboard::CInputKeyboard() :
	m_aKeyState{},			// プレス情報
	m_aKeyStateTrigger{}	// トリガー情報
{

}

//============================================================================
// デストラクタ
//============================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_Input == nullptr)
	{
		// DirectInputオブジェクトの生成
		if (FAILED(CInput::Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	// 入力デバイス(キーボード)の生成
	if (m_pDevice == nullptr)
	{
		if (FAILED(m_Input->CreateDevice(GUID_SysKeyboard, &m_pDevice, nullptr)))
		{
			return E_FAIL;
		}
	}

	// データフォーマットの設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定：フォアグラウンド
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CInputKeyboard::Uninit()
{
	// 基底クラスの終了処理
	CInput::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CInputKeyboard::Update()
{
	BYTE state_keyboard[MAX_KEY] = {};	// キー入力情報

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(state_keyboard), &state_keyboard[0])))
	{
		for (int i = 0; i < MAX_KEY; i++)
		{
			// キーボードのトリガー情報を保存
			m_aKeyStateTrigger[i] = (m_aKeyState[i] ^ state_keyboard[i]) & state_keyboard[i];

			// キーボードのプレス情報を保存
			m_aKeyState[i] = state_keyboard[i];
		}
	}
	else
	{
		// キーボードのアクセス権を獲得
		m_pDevice->Acquire();
	}
}

//============================================================================
// プレス情報取得
//============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return ((m_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//============================================================================
// トリガー情報取得
//============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return ((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CInputPad::CInputPad() :
	m_aKeyState{},			// プレス情報
	m_aKeyStateTrigger{}	// トリガー情報
{

}

//============================================================================
// デストラクタ
//============================================================================
CInputPad::~CInputPad()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CInputPad::Init()
{
	// プレス情報クリア
	memset(&m_aKeyState, 0, sizeof(XINPUT_STATE));

	// トリガー情報クリア
	memset(&m_aKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	// XInputのステート設定を有効にする
	XInputEnable(true);

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CInputPad::Uninit()
{
	// XInputのステート設定を無効にする
	XInputEnable(false);
}

//============================================================================
// 更新処理
//============================================================================
void CInputPad::Update()
{
	XINPUT_STATE state_joypad = {};	// コントローラの入力情報

	// コントローラの状態を取得
	if (XInputGetState(0, &state_joypad) == ERROR_SUCCESS)
	{
		// 左スティック入力を変換
#if LEFT_JOYSTICK_CONVERT

		// 左スティック入力を十字キーに変換
		g_state_joypad.press.Gamepad.wButtons |= ConvertJoyStick();

#else

		// スティック入力の調整
		AdjustJoyStick();

#endif	// LEFT_JOYSTICK_CONVERT

		// コントローラのトリガー情報を保存
		m_aKeyStateTrigger.Gamepad.wButtons = (m_aKeyState.Gamepad.wButtons ^ state_joypad.Gamepad.wButtons) & state_joypad.Gamepad.wButtons;
		m_aKeyStateTrigger.Gamepad.bLeftTrigger = (m_aKeyState.Gamepad.bLeftTrigger ^ state_joypad.Gamepad.bLeftTrigger) & state_joypad.Gamepad.bLeftTrigger;
		m_aKeyStateTrigger.Gamepad.bRightTrigger = (m_aKeyState.Gamepad.bRightTrigger ^ state_joypad.Gamepad.bRightTrigger) & state_joypad.Gamepad.bRightTrigger;

		// コントローラのプレス情報を保存
		m_aKeyState = state_joypad;
	}
}

//============================================================================
// プレス情報取得
//============================================================================
bool CInputPad::GetPress(JOYKEY Key)
{
	return (m_aKeyState.Gamepad.wButtons & (0x01 << static_cast<int>(Key))) ? true : false;
}

//============================================================================
// トリガー情報取得
//============================================================================
bool CInputPad::GetTrigger(JOYKEY Key)
{
	return (m_aKeyStateTrigger.Gamepad.wButtons & (0x01 << static_cast<int>(Key))) ? true : false;
}

//============================================================================
// 左スティックの傾き取得
//============================================================================
CInputPad::JOYSTICK CInputPad::GetJoyStickL(void)
{
	// スティックの傾きを格納
	JOYSTICK joystickL =
	{
		m_aKeyState.Gamepad.sThumbLX,
		m_aKeyState.Gamepad.sThumbLY
	};

	return joystickL;
}

//============================================================================
// 右スティックの傾き取得
//============================================================================
CInputPad::JOYSTICK CInputPad::GetJoyStickR(void)
{
	// スティックの傾きを格納
	JOYSTICK joystickR =
	{
		m_aKeyState.Gamepad.sThumbRX,
		m_aKeyState.Gamepad.sThumbRY
	};

	return joystickR;
}

//============================================================================
// スティック入力の調整
//============================================================================
void CInputPad::AdjustJoyStick(void)
{
	// 左
	if (m_aKeyState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		m_aKeyState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		m_aKeyState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		m_aKeyState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_aKeyState.Gamepad.sThumbLX = 0;
		m_aKeyState.Gamepad.sThumbLY = 0;
	}

	// 右
	if (m_aKeyState.Gamepad.sThumbRX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		m_aKeyState.Gamepad.sThumbRX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		m_aKeyState.Gamepad.sThumbRY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		m_aKeyState.Gamepad.sThumbRY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_aKeyState.Gamepad.sThumbRX = 0;
		m_aKeyState.Gamepad.sThumbRY = 0;
	}
}