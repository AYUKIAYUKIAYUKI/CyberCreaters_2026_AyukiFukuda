//===============================================================================
//
//  3D�Q�[����b(Block.h)
//                                ����F���n�O��
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
#define FADETOGAME    (60)    //�`���[�g���A����ʂ���Q�[����ʂɃt�F�[�h����܂ł̊Ԋu
//�v���g�^�C�v�錾
typedef struct
{
    D3DXVECTOR3 pos;        //�ʒu
    bool bUse;                //�g�p���Ă��邩�ǂ���
    bool bMove;                //�ړ����邩�ǂ���
    float pSizeX,
        pSizeY,
        pSize1X,
        pSize1Y;
}Tutorial;

//�v���g�^�C�v�錾
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetTutorial(D3DXVECTOR3 pos);
void FadeTutorial(void);
Tutorial* GetTutorial(void);
#endif