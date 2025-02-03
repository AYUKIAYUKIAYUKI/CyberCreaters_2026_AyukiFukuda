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
	SOUND_LABEL_BGM000 = 0,		// BGM1
	SOUND_LABEL_BGM001,			// BGM2
	SOUND_LABEL_SE_SELECT1,		// 選択音1
	SOUND_LABEL_SE_SELECT2,		// 線タキオン2
	SOUND_LABEL_SE_PAUSE,		// ポーズ音
	SOUND_LABEL_SE_BULLET,		// 弾発射音
	SOUND_LABEL_SE_DAMAGE,		// ヒット音
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
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
