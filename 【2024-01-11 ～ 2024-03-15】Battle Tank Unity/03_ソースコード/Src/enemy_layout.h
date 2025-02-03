#ifdef _DEBUG	// 一番下まで

//************************************************
//
// エネミー配置、ヘッダファイル[enemy_layout.h]
// Author：福田歩希
//
//************************************************
#ifndef _ENEMY_LAYOUT_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _ENEMY_LAYOUT_H_	// (二重インクルード防止、マクロ定義する)

/*---【インクルードファイル】---*/
#include "main.h"
#include "enemy.h"

/*---【プロトタイプ宣言】---*/
void Init_EN(void);		// 初期
void Uninit_EN(void);	// 終了
void Update_EN(void);	// 更新
void Draw_EN(void);		// 描画

Enemy GetInfo_targetEN(void);	// 追跡対象の取得

#endif	// _ENEMY_LAYOUT_H_

#endif	// _DEBUG