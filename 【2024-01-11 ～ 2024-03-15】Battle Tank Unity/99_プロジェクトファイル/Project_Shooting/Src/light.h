//************************************************
//
// ライト、ヘッダファイル[light.h]
// Author：福田歩希
//
//************************************************
#ifndef _LIGHT_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _LIGHT_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル /*/
#include "main.h"

/*/ プロトタイプ宣言 /*/
void InitLight(void);			// 初期
void UpdateLight(void);			// 更新
void ChangeLightType(void);		// ライト番号を変更
void MoveLight(void);			// 移動
void ResetLight(void);			// リセット
void SetLight(void);			// 反映
D3DLIGHT9* GetInfoLight(void);	// ライト情報を取得
int GetInfoLightType(void);		// ライト番号を取得

#endif