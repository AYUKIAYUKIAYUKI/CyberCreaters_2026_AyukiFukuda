//===============================================================================
//
//  タイトル画面アニメーション処理(title_anim.h)
//								制作：元地弘汰
// 
//===============================================================================

#ifndef _TITLEANIM_H_
#define _TITLEANIM_H_

#include "main.h"



//プロトタイプ宣言
void InitTitleAnim(void);
void UninitTitleAnim(void);
void UpdateTitleAnim(void);
void DrawTitleAnim(void);
bool ReturnTitleAnimFinish(void);
void TitlePlateFade(void);

#endif 