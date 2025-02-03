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
	SOUND_LABEL_CLICK = 0,	//決定音
	SOUND_LABEL_CANCEL,	//キャンセル音
	SOUND_LABEL_CURSORMOVE,	//カーソル移動
	SOUND_LABEL_NOMALGUNSHOT,	//通常の射撃音
	SOUND_LABEL_ROCKETLAUNCERSHOT,	//ロケランの射撃音
	SOUND_LABEL_MACHINEGUNSHOT,	//マシンガン射撃音
	SOUND_LABEL_SHOTGUNSHOT,	//ショットガンの射撃音
	SOUND_LABEL_PICK_WEAPON,	//武器装備時の音
	SOUND_LABEL_PLAYERHIT,		//被弾音
	SOUND_LABEL_PLAYERDEAD,		//死亡音
	SOUND_LABEL_EXPLOSION,		//爆発音
	SOUND_LABEL_EXPLOSION_1,	//建物崩れる時の音
	SOUND_LABEL_TELEPORT,		//ボスのテレポートしたときの音
	SOUND_LABEL_FADE_OPEN,		//フェードオープンする時の音
	SOUND_LABEL_FADE_GEAR,		//フェードのギア稼働音
	SOUND_LABEL_TITLE_BGM,		//タイトルBGM	
	SOUND_LABEL_TUTORIAL_BGM,	//チュートリアルBGM
	SOUND_LABEL_GAME_BGM,		//ゲーム中BGM
	SOUND_LABEL_RESULT_RANKING_BGM,	//ランキング、リザルトBGM
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
