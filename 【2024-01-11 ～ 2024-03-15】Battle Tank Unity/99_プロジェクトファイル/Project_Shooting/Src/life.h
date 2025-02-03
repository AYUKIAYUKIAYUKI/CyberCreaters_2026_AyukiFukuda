//************************************************
//
// ライフ表示、ヘッダファイル[life.h]
// Author：福田歩希
//
//************************************************
#ifndef _LIFE_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _LIFE_H_	// (二重インクルード防止、マクロ定義する)

/*---【インクルードファイル】---*/
#include "gameUI.h"

/*---【プロトタイプ宣言】---*/
void InitLife(int joined);	// 初期
void UninitLife(void);		// 終了
void UpdateLife(void);		// 更新
void DrawLife(void);		// 描画

#endif