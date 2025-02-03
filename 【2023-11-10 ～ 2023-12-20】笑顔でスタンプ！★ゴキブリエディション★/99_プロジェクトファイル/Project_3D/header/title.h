//************************************************
//
//タイトル、ヘッダファイル[title.h]
//Author：福田歩希
//
//************************************************
#ifndef _TITLE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TITLE_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//プロトタイプ宣言
void InitTitle(void);	//初期
void UninitTitle(void);	//破棄
void UpdateTitle(void);	//更新
void DrawTitle(void);	//描画

#endif