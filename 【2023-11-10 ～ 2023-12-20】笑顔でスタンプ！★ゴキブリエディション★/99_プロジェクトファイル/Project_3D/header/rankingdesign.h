//************************************************
//
//ランキングデザイン、ヘッダファイル[titledesign.h]
//Author：福田歩希
//
//************************************************
#ifndef _RANKINGDESIGN_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RANKINGDESIGN_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//ランキング表示用
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	float sizeX;
	float sizeY;
	float F;
}RankingDesign;

//プロトタイプ宣言
void InitRankingDesign(void);	//初期
int* ChangeLastMode(void);	//最後のモードを入れる
void SetInfoRankingDesign(void);	//設定
void UninitRankingDesign(void);	//破棄
void UpdateRankingDesign(void);	//更新
void SetSizeRankingDesign(void);	//展開
void DrawRankingDesign(void);	//描画
void ReadScoreInfo(void);	//記録読込み

#endif