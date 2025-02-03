//************************************************
//
// 武器表示、ヘッダファイル[weapon.h]
// Author：福田歩希
//
//************************************************
#ifndef _WEAPON_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _WEAPON_H_	// (二重インクルード防止、マクロ定義する)

/*---【インクルードファイル】---*/
#include "gameUI.h"

/*---【プロトタイプ宣言】---*/
void InitWeapon(int joined);	// 初期
void UninitWeapon(void);		// 終了
void UpdateWeapon(int joined);	// 更新
void DrawWeapon(void);			// 描画

void RotatePFW3(int id, float pw);	// 歯車回転

#endif