//************************************************
//
//スコア(リザルト)処理、ヘッダファイル[score_result.h]
//Author：福田歩希
//
//************************************************
#ifndef _SCORE_RESULT_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _SCORE_RESULT_H_	//(二重インクルード防止、マクロ定義する)

#include <stdio.h>
#include "main.h"

//マクロ定義

/*画像パス*/
#define	TEXTURE_NUMBER_SCORE_RESULT	"data\\TEX\\02_game\\number001.png"

#define AMOUNT_POLYGON_SCORE_RESULT	(30)	//ポリゴン数
#define AMOUNT_TEXTURE_SCORE_RESULT	(1)	//テクスチャ数

#define AMOUNT_USING_POLYGON_NUMBER_SCORE_RESULT	(6)	//数字に使ってるポリゴン数

#define TEX_U_RIGHT_SCORE_RESULT	(0.1f)	//U座標の右用

#define DISTANCESPAN_POLYGON_SCORE_RESULT	(30.0f)	//ポリゴンを並べる間隔
#define MOVE_SPAN_TEX_SCORE_RESULT	(0.1f)			//テクスチャ可動域

typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	float fSpanX;		//サイズ
	float fSpanY;		//サイズ
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//色
}SCORE_RESULT;

//プロトタイプ宣言
void Init_Score_Result(void);
void Uninit_Score_Result(void);
void Update_Score_Result(void);
void Draw_Score_Result(void);
void Setinfo_Score_Result(void);
void SetPos_Vtx_Score_Result(void);

#endif