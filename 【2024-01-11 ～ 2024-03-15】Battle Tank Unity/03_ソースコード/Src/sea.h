//************************************************
//
// 海生成処理、ヘッダファイル[sea.h]
// Author：福田歩希
//
//************************************************
#ifndef _SEA_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _SEA_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル /*/
#include "main.h"

// 海用構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXCOLOR col;			// 色
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
}Sea;

/*/ プロトタイプ宣言 /*/
void InitSea(void);		// 初期
void UninitSea(void);	// 破棄
void UpdateSea(void);	// 更新
void CalcMtxSea(void);	// 行列計算
void DrawSea(void);		// 描画

#endif