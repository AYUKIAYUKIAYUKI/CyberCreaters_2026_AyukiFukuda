//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLE = 0,	//タイトル
	SOUND_LABEL_BATTLE,		//バトル
	SOUND_LABEL_CHOOSE,		//選択
	SOUND_LABEL_DEFINE,		//決定
	SOUND_LABEL_JUMP00,		//ジャンプ音1
	SOUND_LABEL_JUMP01,		//ジャンプ音2
	SOUND_LABEL_LAND,		//着地音
	SOUND_LABEL_LIGHT1,		//弱1
	SOUND_LABEL_LIGHT2,		//弱2
	SOUND_LABEL_LIGHT3,		//弱3
	SOUND_LABEL_HEAVY1,		//強1
	SOUND_LABEL_HEAVY2,		//強2
	SOUND_LABEL_HEAVY3_1,	//強3_1
	SOUND_LABEL_HEAVY3_2,	//強3_2
	SOUND_LABEL_HURT,		//被弾
	SOUND_LABEL_SLAY,		//殺害
	SOUND_LABEL_PHURT,		//ｐ被弾
	SOUND_LABEL_THURT,		//ｔ被弾
	SOUND_LABEL_FALL,		//落下
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
