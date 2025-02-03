//==========================================================
//
//チュートリアル時のゲーム画面の描画処理[game.h]
//Author:kurasato
//
//==========================================================

#ifndef _TUTORIALGAME_H_
#define _TUTORIALGAME_H_

//include
#include "main.h"

//マクロ定義
#define MAX_ENEMY	(1024)		//敵の最大数
#define MAX_PATHWORD	(128)	//最大文字数
#define MAX_SYMBOL	(4)			//イコールなどを読み込む用


//プロトタイプ宣言
void InitTutorialGame(void);		//ゲーム画面の初期化処理
void UninitTutorialGame(void);		//ゲーム画面の終了処理
void UpdateTutorialGame(void);		//ゲーム画面の更新処理
void UpdateTutorialGame(void);	//チュートリアル時のゲーム画面アップデート
void DrawTutorialGame(void);		//チュートリアル時のゲーム画面の描画処理
void DrawTutorialGame(void);		//ゲーム画面の描画処理


#endif

