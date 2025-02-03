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

//プロトタイプ宣言

HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//キーボード生成
void UnInitKeyboard(void);	//キーボード破棄
void UpdateKeyboard(void);	//キーボード更新
bool GetKeyboardPress(int nKey);	//キーボードプレス
bool GetKeyboardTrigger(int nKey);	//キーボードトリガー
HRESULT InitJoypad(void);	//コントローラー生成
void UninitJoypad(void);	//コントローラー破棄
void UpdateJoypad(void);	//コントローラー更新
bool GetJoypadPress(JOYKEY key);	//コントローラープレス
bool GetJoypadTrigger(JOYKEY key);	//コントローラートリガー
XINPUT_GAMEPAD GetGamePad(void);
bool GetPressTriggerButtonL(void);	//左トリガーボタンのプレス入力
bool GetPressTriggerButtonR(void);	//右トリガーボタンのプレス入力
bool GetTriggerTriggerButtonR(void);	//右トリガーボタンのトリガー入力
bool GetJoyStickL(void);	//左スティック入力
bool GetJoyStickR(void);	//右スティック入力
void AdjustJoyStick(void);	//コントローラ入力のあそび
WORD ConvertJoyStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);	//左スティックを十字キーに変換
void SetVibration(int time, WORD strength);	//コントローラー振動

#endif