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
	SOUND_LABEL_TUTORIAL,	//チュートリアル
	SOUND_LABEL_GAME,	//ゲーム
	SOUND_LABEL_CHOOSE,	//選択
	SOUND_LABEL_DEFINE,	//決定
	SOUND_LABEL_ATK,	//攻撃
	SOUND_LABEL_DAMAGE,	//被弾
	SOUND_LABEL_HIT,	//命中
	SOUND_LABEL_STAMP,	//殺害
	SOUND_LABEL_ROSALIA,	//ムキムキマックスモード
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
float* GetInfoSoundVol(void);	//音量情報を取得
void SetInfoSoundVol(int label);	//音量を設定

#endif
