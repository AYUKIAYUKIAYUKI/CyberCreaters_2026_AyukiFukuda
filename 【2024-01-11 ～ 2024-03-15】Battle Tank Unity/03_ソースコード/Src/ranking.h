//========================
//
//ランキング処理;ranking.h
//Authar:KuramaeSatoshi
// 
//========================

#include "main.h"
#define JOIN_VERIFY 4    // 人数指定
#define MAX_RANK (5) //ランクの数
#define MAX_RANKTEX (3)
#define MAX_DIGIT    (8)    //桁数
#define MAX_RANKWIDTH    (60.0f)    //ランキングの幅
#define MAX_RANKHEIGHT    (65.0f)    //ランキングの高さ
#define NUM_RANK_UITEX    (2)

//ランキング構造体
typedef struct
{
    D3DXVECTOR3 pos;
    int nScore;
    int nScorePos;
    bool bRight;        //新しくランクインした場合点灯させる
}RankScore;

//プロトタイプ宣言
void InitRanking(void);
void InitRanking_BG(void);
void UninitRanking(void);
void UninitRanking_BG(void);
void UpdateRanking(void);
void UpdateRanking_BG(void);
void DrawRanking_BG(void);
void DrawRanking(void);
void ResetRanking(void);
void SetRanking(int nScore);