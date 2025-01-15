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
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UnInitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
bool GetJoypadTrigger(JOYKEY key);
WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);
void SetVibration(int time, WORD strength);

#endif