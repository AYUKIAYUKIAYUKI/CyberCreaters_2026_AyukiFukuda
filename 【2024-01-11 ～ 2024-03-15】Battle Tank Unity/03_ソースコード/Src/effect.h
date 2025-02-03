//************************************************
//
// エフェクト、ヘッダファイル[effect.h]
// Author：葛西敬介
//
//************************************************

#ifndef _EFFECT_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _EFFECT_H_	// (二重インクルード防止、マクロ定義する)

//include
#include "main.h"

//マクロ定義
#define MAX_EFFECT	(512)	//エフェクトの最大数

//エフェクトの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	D3DXMATRIX mtxworld;	//ワールドマトリックス
	float fLife;			//ライフ
	float fRadius;			//半径
	bool bUse;				//使用しているかどうか							
}EFFECT;

//プロトタイプ宣言
void InitEffect(void);														//初期化処理
void UninitEffect(void);													//終了処理
void UpdateEffect(void);													//更新処理
void DrawEffect(void);														//描画処理
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, float fLife);	//設定処理
EFFECT* GetEffect(void);													//情報を取得
#endif