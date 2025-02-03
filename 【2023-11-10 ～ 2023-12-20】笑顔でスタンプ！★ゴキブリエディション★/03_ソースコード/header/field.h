//************************************************
//
//地面生成処理、ヘッダファイル[field.h]
//Author：福田歩希
//
//************************************************
#ifndef _FIELD_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _FIELD_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//地面構造体
struct Field
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
};

//プロトタイプ宣言
void InitField(void);	//初期
void UninitField(void);	//破棄
void UpdateField(void);	//更新
void DrawField(void);	//描画

#endif