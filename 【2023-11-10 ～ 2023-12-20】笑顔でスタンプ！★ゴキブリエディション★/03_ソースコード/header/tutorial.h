//************************************************
//
//チュートリアル、ヘッダファイル[tutorial.h]
//Author：福田歩希
//
//************************************************
#ifndef _TUTORIAL_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TUTORIAL_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//プロトタイプ宣言
void InitTutorial(void);	//初期
void UninitTutorial(void);	//破棄
void UpdateTutorial(void);	//更新
void DrawTutorial(void);	//描画

#endif