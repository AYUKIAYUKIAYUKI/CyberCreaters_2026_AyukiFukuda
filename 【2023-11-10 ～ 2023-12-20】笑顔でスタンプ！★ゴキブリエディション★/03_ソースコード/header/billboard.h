//************************************************
//
//ビルボード生成処理、ヘッダファイル[billboard.h]
//Author：福田歩希
//
//************************************************
#ifndef _BILLBOARD_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BILLBOARD_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//ビルボード構造体
struct Billboard
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き(仮想の進行方向などに)
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
};

//プロトタイプ宣言
void InitBillboard(void);	//初期
void UninitBillboard(void);	//破棄
void UpdateBillboard(void);	//更新
void DrawBillboard(void);	//描画

#endif