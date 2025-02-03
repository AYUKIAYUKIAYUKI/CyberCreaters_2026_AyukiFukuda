//************************************************
//
// タイマー表示、ヘッダファイル[timer.h]
// Author：福田歩希
//
//************************************************
#ifndef _TIMER_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TIMER_H_	// (二重インクルード防止、マクロ定義する)

/*---【インクルードファイル】---*/
#include "gameUI.h"

/*---【プロトタイプ宣言】---*/
void InitTimer(int joined);	// 初期
void UninitTimer(void);		// 終了
void UpdateTimer(void);		// 更新
void DrawTimer(void);		// 描画

#endif