//************************************************
//
// スコア表示、ヘッダファイル[score.h]
// Author：福田歩希
//
//************************************************
#ifndef _SCORE_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _SCORE_H_	// (二重インクルード防止、マクロ定義する)

/*---【インクルードファイル】---*/
#include "gameUI.h"

/*---【プロトタイプ宣言】---*/
void InitScore(int joined);	// 初期
void UninitScore(void);		// 終了
void UpdateScore(void);		// 更新
void DrawScore(void);		// 描画

#endif