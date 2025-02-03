//************************************************
//
//ランキング、ヘッダファイル[ranking.h]
//Author：福田歩希
//
//************************************************
#ifndef _RANKING_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RANKING_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//プロトタイプ宣言
void InitRanking(void);	//初期
void UninitRanking(void);	//破棄
void UpdateRanking(void);	//更新
void DrawRanking(void);	//描画

#endif