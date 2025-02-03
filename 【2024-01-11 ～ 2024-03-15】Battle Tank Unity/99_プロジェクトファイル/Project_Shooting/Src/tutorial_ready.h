//=====================================
//
//READYマーク表示用
//
//=====================================

#ifndef _READY_H_
#define _READY_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	bool bUse;				//使用しているかどうか
	int number;				//番号（1～4）
}Ready;

//プロトタイプ宣言
void InitReady(void);
void UninitReady(void);
void UpdateReady(void);
void DrawReady(void);
void SetReady(D3DXVECTOR3 pos, int nNumber);
void DeplayReady(void);
#endif // !_READY_H_

