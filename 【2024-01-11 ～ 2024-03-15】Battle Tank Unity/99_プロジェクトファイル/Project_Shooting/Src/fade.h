//===============================================================================
//
//  3Dチーム制作(fade.h)
//								制作：元地弘汰
// 
//===============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
//フェード用構造体
typedef struct
{
	int nType;
	bool bUse;
	bool bFinish;
	MODE mode;
	bool bSoundUse[2];
}FADE;

//フェード移行先用列挙型
typedef enum
{
	FADE_IN = 0,
	FADE_OUT,
	FADE_MAX
}FADE_SET;

//プロトタイプ宣言
void InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(int nType,MODE mode);
#endif 
