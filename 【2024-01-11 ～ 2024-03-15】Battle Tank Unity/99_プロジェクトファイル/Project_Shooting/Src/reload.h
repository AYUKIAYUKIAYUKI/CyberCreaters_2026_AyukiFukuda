//************************************************
//
// リロード表示、ヘッダファイル[reload.h]
// Author：福田歩希
//
//************************************************
#ifndef _RELOAD_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RELOAD_H_	// (二重インクルード防止、マクロ定義する)

/*---【インクルードファイル】---*/
#include "gameUI.h"

/*---【プロトタイプ宣言】---*/
void InitReload(int joined);	// 初期
void UninitReload(void);		// 終了
void UpdateReload(void);		// 更新
void DrawReload(void);			// 描画

#endif