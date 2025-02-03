//************************************************
//
// 空処理、ヘッダファイル[sky.h]
// Author：福田歩希
//
//************************************************
#ifndef _SKY_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _SKY_H_	//(二重インクルード防止、マクロ定義する)

/*/ インクルードファイル /*/
#include "main.h"

// 空構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
}Sky;

/*/ プロトタイプ宣言 /*/
void InitSky(void);		// 初期
void UninitSky(void);	// 破棄
void UpdateSky(void);	// 更新
void CalcMtxSky(void);	// 行列計算
void DrawSky(void);		// 描画

#endif