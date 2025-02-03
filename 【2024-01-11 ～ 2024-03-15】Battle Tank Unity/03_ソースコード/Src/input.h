//************************************************
//
// キー入力処理、ヘッダファイル[input.h]
// Author：福田歩希, kasai keisuke
//
//************************************************
#ifndef _INPUT_H_
#define _INPUT_H_

/*/ インクルードファイル /*/
#include "main.h"

// コントローラ入力列挙型
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

/*/ プロトタイプ宣言  /*/
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	// キーボード生成
void UnInitKeyboard(void);					// キーボード破棄
void UpdateKeyboard(void);					// キーボード更新
bool GetKeyboardPress(int nKey);			// キーボードプレス
bool GetKeyboardTrigger(int nKey);			// キーボードトリガー
HRESULT InitJoypad(void);					// コントローラー生成
void UninitJoypad(void);					// コントローラー破棄
void UpdateJoypad(void);					// コントローラー更新
bool GetJoypadPress(JOYKEY key,int nContIndex);			// コントローラープレス(何のボタンを押したか,何番目のコントローラーで押したのか)
bool GetJoypadTrigger(JOYKEY key,int nContIndex);		// コントローラートリガー(何のボタンを押したか,何番目のコントローラーで押したのか)
XINPUT_GAMEPAD GetGamePad(int nContIndex);
bool GetPressTriggerButtonL(int nContIndex);			// 左トリガーボタンのプレス入力
bool GetPressTriggerButtonR(int nContIndex);			// 右トリガーボタンのプレス入力
bool GetTriggerTriggerButtonL(int nContIndex);		// 左トリガーボタンのトリガー入力
bool GetTriggerTriggerButtonR(int nContIndex);		// 右トリガーボタンのトリガー入力
bool GetJoyStickL(int nContIndex);					// 左スティック入力
bool GetJoyStickR(int nContIndex);					// 右スティック入力
void AdjustJoyStick(void);					// コントローラ入力のあそび
WORD ConvertJoyStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);	// 左スティックを十字キーに変換
void SetVibration(int time, WORD strength);	// コントローラー振動

#endif