//************************************************
//
// ゲージ表示、ヘッダファイル[bar.h]
// Author：福田歩希
//
//************************************************
#ifndef _BAR_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BAR_H_	// (二重インクルード防止、マクロ定義する)

/*---【インクルードファイル】---*/
#include "gameUI.h"

/*---【プロトタイプ宣言】---*/
void InitBar(int joined);	// 初期
void UninitBar(void);		// 終了
void UpdateBar(void);		// 更新
void DrawBar(void);			// 描画

#endif