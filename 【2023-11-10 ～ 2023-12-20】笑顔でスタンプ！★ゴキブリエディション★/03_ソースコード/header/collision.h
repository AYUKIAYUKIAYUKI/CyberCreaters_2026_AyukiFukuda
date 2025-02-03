//************************************************
//
//衝突判定、ヘッダファイル[collision.h]
//Author：福田歩希
//
//************************************************
#ifndef _COLLISION_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _COLLISION_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

typedef enum
{
	Xside = 0,
	Zside,
	OnlyVtx,
	Bothside,
	CollisionMax
}CollisionType;

//プロトタイプ宣言
bool CollisionSphere(const D3DXVECTOR3 obj1, const float radius1, const D3DXVECTOR3 obj2, const float radius2);	//球同士の衝突判定
bool CollisionAABB(const COLLISION_AABB obj1, const COLLISION_AABB obj2);   //AABB同士の衝突判定
int CollisionAABB_Vtx(COLLISION_AABB obj1, const COLLISION_AABB obj2);	//AABBのどの面が触れているか判定

#endif