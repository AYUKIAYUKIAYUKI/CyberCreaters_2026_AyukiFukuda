//===============================================================================
//
//  3Dゲーム基礎(Block.h)
//                                制作：元地弘汰
// 
//===============================================================================
#ifndef TUTORIAL_H
#define TUTORIAL_H
#include "main.h"

#define NUM_TUTORIAL_TEX (3)
#define UI_SIZEX1 (960.0f)
#define UI_SIZEY1 (540.0f)
#define UI_SIZEX2 (350.0f)
#define UI_SIZEY2 (120.0f)
#define UISPEED (10.0f)
#define FADEUICOORD (-250.0f)
#define UICOORD_1 (500.0f)
#define UICOORD_2 (1415.0f)
#define FADETOGAME    (60)    //チュートリアル画面からゲーム画面にフェードするまでの間隔
//プロトタイプ宣言
typedef struct
{
    D3DXVECTOR3 pos;        //位置
    bool bUse;                //使用しているかどうか
    bool bMove;                //移動するかどうか
    float pSizeX,
        pSizeY,
        pSize1X,
        pSize1Y;
}Tutorial;

//プロトタイプ宣言
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetTutorial(D3DXVECTOR3 pos);
void FadeTutorial(void);
Tutorial* GetTutorial(void);
#endif