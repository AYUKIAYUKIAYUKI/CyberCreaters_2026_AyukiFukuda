//************************************************
//
//キー入力処理、ヘッダファイル[input.h]
//Author：福田歩希
//
//************************************************
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//コントローラ入力列挙型
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

//プロトタイプ宣言

/*キーボードの生成*/
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);

/*キーボードの破棄*/
void UnInitKeyboard(void);

/*キーボードの更新*/
void UpdateKeyboard(void);

/*キーボードのプレス入力*/
bool GetKeyboardPress(int nKey);

/*キーボードのトリガー入力*/
bool GetKeyboardTrigger(int nKey);

/*コントローラーのスタート*/
HRESULT InitJoypad(void);

/*コントローラーの破棄*/
void UninitJoypad(void);

/*コントローラーの更新*/
void UpdateJoypad(void);

/*コントローラーのプレス入力*/
bool GetJoypadPress(JOYKEY key);

/*コントローラーのトリガー入力*/
bool GetJoypadTrigger(JOYKEY key);

/*コントローラーのスティック入力*/
WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);

/*コントローラーの振動*/
void SetVibration(int time, WORD strength);

#endif