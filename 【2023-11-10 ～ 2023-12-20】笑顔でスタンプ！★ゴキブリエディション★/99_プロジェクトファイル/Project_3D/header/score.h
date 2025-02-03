//************************************************
//
//スコア処理、ヘッダファイル[score.h]	(レガシー)
//Author：福田歩希
//
//************************************************
#ifndef _SCORE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _SCORE_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義
#define	TEXTURE_BLACK_SCORE	"data\\texture\\blackbase.png"
#define	TEXTURE_NUMBER_SCORE	"data\\texture\\NUM.png"
#define TEXTURE_SYMBOL_SCORE	"data\\texture\\timer000.png"

#define AMOUNT_POLYGON_SCORE	(8)	//ポリゴン数
#define AMOUNT_TEXTURE_SCORE	(3)	//テクスチャ数

#define AMOUNT_USING_POLYGON_NUMBER_SCORE	(6)	//数字に使ってるポリゴン数

#define POS_X_LEFT_SCORE	(1900.0f)	//X座標の左用
#define POS_X_RIGHT_SCORE	(1950.0f)	//X座標の右用
#define POS_Y_UP_SCORE	(30.0f)			//Y座標の上用
#define POS_Y_DOWN_SCORE	(105.0f)	//Y座標の下用

#define TEX_U_RIGHT_SCORE	(0.1f)	//U座標の右用

#define DISTANCESPAN_POLYGON_SCORE	(30.0f)	//ポリゴンを並べる間隔
#define MOVE_SPAN_TEX_SCORE	(0.1f)			//テクスチャ可動域

#define AMOUNT_MAX_SCORE	(999999)	//スコア上限

//プロトタイプ宣言
void Init_Score(void);
void Uninit_Score(void);
void Update_Score(void);
void Draw_Score(void);
void SetPos_Vtx_Score(void);
void Calc_Score(void);
void Add_Score(int Add);
void Animation_Score(void);
void ReSetPos_Vtx_Score(void);
void SaveScore(void);	//スコア記録

#endif