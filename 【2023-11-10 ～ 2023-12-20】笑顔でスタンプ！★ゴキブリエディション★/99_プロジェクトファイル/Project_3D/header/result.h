//************************************************
//
//リザルト、ヘッダファイル[result.h]
//Author：福田歩希
//
//************************************************
#ifndef _RESULT_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RESULT_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//プロトタイプ宣言
void InitResult(void);	//初期
void UninitResult(void);	//破棄
void UpdateResult(void);	//更新
void DrawResult(void);	//描画

#endif