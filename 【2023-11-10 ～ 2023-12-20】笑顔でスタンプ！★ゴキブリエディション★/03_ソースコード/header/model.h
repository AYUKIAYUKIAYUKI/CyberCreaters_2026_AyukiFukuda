//************************************************
//
//モデル、ヘッダファイル[model.h]
//Author：福田歩希
//
//************************************************
#ifndef _MODEL_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _MODEL_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//モデル構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	COLLISION_AABB aabb;	//AABB衝突判定用
	int nIdxShadow;
}Model;

//プロトタイプ宣言
void InitModel(int mode);	//初期
void UninitModel(void);	//破棄
void UpdateModel(void);	//更新
void UpdateModelAABB(void);	//AABB更新
void CollisionModel(void);	//当たり判定
void DrawModel(void);	//描画
Model* GetInfoModel(void);

#endif