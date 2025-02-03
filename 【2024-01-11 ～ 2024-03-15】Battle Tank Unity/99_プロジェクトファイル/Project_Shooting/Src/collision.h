//************************************************
//
// 衝突判定、ヘッダファイル[collision.h]
// Author：福田歩希
//
//************************************************
#ifndef _COLLISION_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _COLLISION_H_	// (二重インクルード防止、マクロ定義する)

/*---【インクルードファイル】---*/
#include "main.h"

/*---【プロトタイプ宣言】---*/
bool CollisionSph(D3DXVECTOR3 sph1, float r1,
	D3DXVECTOR3 sph2, float r2);	// 球同士の衝突判定

bool CollisionSphAABB(D3DXVECTOR3 sph,
	float r, COLLISION_AABB box);	// 球とAABBの当たり判定

bool CollisionAABB(COLLISION_AABB box1,
	COLLISION_AABB box2);			// AABB同士の衝突判定

void CollisionVecSphAABB(int id, D3DXVECTOR3 sph,
	float r, COLLISION_AABB box);	// 球→AABBの衝突判定と押しだし(仮)

#endif