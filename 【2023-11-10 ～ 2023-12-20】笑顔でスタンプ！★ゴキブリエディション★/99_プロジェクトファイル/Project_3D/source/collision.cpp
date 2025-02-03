//************************************************
//
//衝突判定[collision.cpp]
//Author：福田歩希
//
//************************************************
#include "collision.h"

#include "debugproc.h"

//************************************************
//球同士の衝突判定
//************************************************
bool CollisionSphere(const D3DXVECTOR3 obj1, const float radius1, const D3DXVECTOR3 obj2, const float radius2)
{
    D3DXVECTOR3 Vector = obj1 - obj2;
    float Distance = sqrtf((Vector.x * Vector.x) + (Vector.y * Vector.y) + (Vector.z * Vector.z));

    return (Distance < radius1 + radius2);
}

//************************************************
//AABB同士の衝突判定
//************************************************
bool CollisionAABB(const COLLISION_AABB obj1, const COLLISION_AABB obj2)
{
    return (obj1.min.x < obj2.max.x &&
        obj1.max.x > obj2.min.x &&
        obj1.min.y < obj2.max.y &&
        obj1.max.y > obj2.min.y &&
        obj1.min.z < obj2.max.z &&
        obj1.max.z > obj2.min.z);
}

//************************************************
//XZ平面のAABBにおいて、どの箇所が触れているかを判定
//************************************************
//int CollisionAABB_Vtx(const D3DXVECTOR3 pos1, const D3DXVECTOR3 move, const COLLISION_AABB obj1, const D3DXVECTOR3 pos2, const COLLISION_AABB obj2)
int CollisionAABB_Vtx(const COLLISION_AABB obj1, const COLLISION_AABB obj2)
{
    int Type = -1;
    bool minX = false;
    bool maxX = false;
    bool minZ = false;
    bool maxZ = false;
    int CntVtx = 0;
    
    /* obj1の片側のX軸がobj2の両方のX軸をはみ出している */
    if (obj1.max.x > obj2.min.x &&
        obj1.max.x > obj2.max.x ||
        obj1.min.x < obj2.min.x &&
        obj1.min.x < obj2.max.x)
    {
        /* obj1のminのZ軸がobj2の両方のZ軸の幅に収まっている */
        if (obj1.min.z < obj2.max.z &&
            obj1.min.z > obj2.min.z)
        {
            minZ = true;

            CntVtx++;
        }

        /* obj1のmaxのZ軸がobj2の両方のZの幅に収まっている */
        if (obj1.max.z < obj2.max.z &&
            obj1.max.z > obj2.min.z)
        {
            maxZ = true;

            CntVtx++;
        }

        if (minZ && maxZ)
        {
            Type = Xside;
        }
    }

    /* obj1の片側のZ軸がobj2の両方のZ軸をはみ出している */
    if (obj1.max.z > obj2.min.z &&
        obj1.max.z > obj2.max.z ||
        obj1.min.z > obj2.min.z &&
        obj1.min.z > obj2.max.z)
    {
        /* obj1のminのX軸がobj2の両方のX軸の幅に収まっている */
        if (obj1.min.x < obj2.max.x &&
            obj1.min.x > obj2.min.x)
        {
            minX = true;

            CntVtx++;
        }

        /* obj1のmaxのX軸がobj2の両方のX軸の幅に収まっている */
        if (obj1.max.x < obj2.max.x &&
            obj1.max.x > obj2.min.x)
        {
            maxX = true;

            CntVtx++;
        }

        if (minX && maxX)
        {
            Type = Zside;
        }
    }

    PrintDebugProc("接触頂点：[%d]\n", CntVtx);

    if (CntVtx <= 1)
    {
        Type = OnlyVtx;
    }

    return Type;
}