//************************************************
//
//壁生成処理、ヘッダファイル[wall.h]
//Author：福田歩希
//
//************************************************
#ifndef _WALL_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _WALL_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"
#include "collision.h"

//壁構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
	D3DXVECTOR3 span;	//サイズ
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	COLLISION_AABB aabb;	//AABB
}Wall;

//プロトタイプ宣言
void InitWall(void);	//初期
void UninitWall(void);	//破棄
void UpdateWall(void);	//更新
void UpdateWallAABB(void);	//AABB
void CollisionWall(void);	//当たり判定
void DrawWall(void);	//描画

#endif