//************************************************
//
//ランキングにスコアを出す、ヘッダファイル[ranking_score.h]
//Author：福田歩希
//
//************************************************
#ifndef _RANKING_SCORE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RANKING_SCORE_H_	//(二重インクルード防止、マクロ定義する)

#include <stdio.h>
#include "main.h"

//マクロ定義

/*ファイルパス*/
#define	FILE_SET_RANKING	"data\\csv\\Ranking.csv"

/*画像パス*/
#define	TEXTURE_NUMBER_RANKING_SCORE	"data\\TEX\\04_ranking\\number.png"

#define AMOUNT_POLYGON_RANKING_SCORE	(64)	//ポリゴン数
#define AMOUNT_TEXTURE_RANKING_SCORE	(1)	//テクスチャ数

#define AMOUNT_SET_RANKING_SCORE	(5)	//読み込むスコア数

typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	float fSpanX;		//サイズ
	float fSpanY;		//サイズ
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//色
	float fLength;		//対角線
	float fAngle;		//角度
	float fSPD_X;
	float colA;
}RANKING_SCORE;

typedef struct
{
	double lfScore;	//スコア
	int nDigit;	//桁数
}READ_RANKING_SCORE;

//プロトタイプ宣言
void Init_Ranking_Score(int nMode);
void Uninit_Ranking_Score(void);
void Update_Ranking_Score(void);
void Draw_Ranking_Score(void);
void Readinfo_Ranking_Score(void);
void SetNewinfo_Ranking(void);
void SetTex_Ranking_Score(int nMode);
void Setinfo_Ranking_Score(void);

#endif