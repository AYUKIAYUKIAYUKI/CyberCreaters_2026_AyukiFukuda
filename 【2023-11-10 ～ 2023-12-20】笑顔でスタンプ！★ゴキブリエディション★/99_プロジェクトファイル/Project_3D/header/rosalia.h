//************************************************
//
//ロザリア生成処理、ヘッダファイル[rosalia.h]
//Author：福田歩希
//
//************************************************
#ifndef _ROSALIA_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _ROSALIA_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//ロザリア構造体
struct Rosalia
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き(仮想の進行方向などに)
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
};

//プロトタイプ宣言
void InitRosalia(void);	//初期
void UninitRosalia(void);	//破棄
void UpdateRosalia(void);	//更新
void SetSizeRosalia(void);	//サイズセット
void DrawRosalia(void);	//描画

#endif