//************************************************
//
//レイ、ヘッダファイル[ray.h]
//Author：福田歩希
//
//************************************************
#ifndef _RAY_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RAY_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//レイ構造体
struct Ray
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
	float fPA;			//極角
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
};

//プロトタイプ宣言
void InitRay(void);	//初期
void UninitRay(void);	//破棄
void UpdateRay(void);	//更新
void DrawRay(void);	//描画

#endif