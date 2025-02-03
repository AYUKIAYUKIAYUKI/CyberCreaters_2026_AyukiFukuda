//************************************************
//
//ゲーム、ヘッダファイル[game.h]
//Author：福田歩希
//
//************************************************
#ifndef _GAME_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _GAME_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//プロトタイプ宣言
void InitGame(void);	//初期
void UninitGame(void);	//破棄
void UpdateGame(void);	//更新
void DrawGame(void);	//描画
bool* GetInfoPause(void);	//ポーズ情報を取得

#endif