//************************************************
//
//デバッグ表示用スクロールバー、ヘッダファイル[debugscroll.h]
//Author：福田歩希
//
//************************************************
#ifndef _DEBUGSCROLL_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _DEBUGSCROLL_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義
#define AMOUNT_DEBUGSCROLL	(2)	//スクロール用ポリゴン数

//デバッグスクロール
struct DebugScroll
{
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;		//色
};

//プロトタイプ宣言
void InitDebugScroll(void);	//初期
void UninitDebugScroll(void);	//破棄
void UpdateDebugScroll(void);	//更新
void DrawDebugScroll(void);	//描画

#endif