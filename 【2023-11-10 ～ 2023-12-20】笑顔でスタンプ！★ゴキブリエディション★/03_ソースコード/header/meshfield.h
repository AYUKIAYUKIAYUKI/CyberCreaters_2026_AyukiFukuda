//************************************************
//
//メッシュフィールド生成処理、ヘッダファイル[meshfield.h]
//Author：福田歩希
//
//************************************************
#ifndef _MESHFIELD_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _MESHFIELD_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//メッシュフィールド構造体
struct Meshfield
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
};

//プロトタイプ宣言
void InitMeshfield(void);	//初期
void UninitMeshfield(void);	//破棄
void UpdateMeshfield(void);	//更新
void DrawMeshfield(void);	//描画

#endif