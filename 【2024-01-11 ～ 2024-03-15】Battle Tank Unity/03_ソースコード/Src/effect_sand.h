//===============================================================================
//
//  3Dゲーム基礎(Block.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _EFFECTSAND_H_
#define _EFFECTSAND_H_
#include "main.h"


//プロトタイプ宣言
void InitEffectSand(void);
void UninitEffectSand(void);
void UpdateEffectSand(void);
void DrawEffectSand(void);
void SetEffectSand(D3DXVECTOR3 pos, int nType, float nSize, int nID);
#endif 

