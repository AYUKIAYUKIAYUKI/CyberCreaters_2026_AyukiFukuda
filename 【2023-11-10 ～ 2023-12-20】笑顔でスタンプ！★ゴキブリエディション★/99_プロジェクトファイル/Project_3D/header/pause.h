//************************************************
//
//ポーズデザイン、ヘッダファイル[pausedesign.h]
//Author：福田歩希
//
//************************************************
#ifndef _TUTORIALDESIGN_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TUTORIALDESIGN_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//ポーズ表示用
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	float sizeX;
	float sizeY;
	float F;
}Pause;

//プロトタイプ宣言
void InitPause(void);	//初期
void SetInfoPause(void);	//設定
void UninitPause(void);	//破棄
void UpdatePause(void);	//更新
void SetSizePause(void);	//展開
void UpdateColPause(void);	//色変更
void DrawPause(void);	//描画
MODE GetInfoChoosePause(void);	//ポーズ選択

#endif