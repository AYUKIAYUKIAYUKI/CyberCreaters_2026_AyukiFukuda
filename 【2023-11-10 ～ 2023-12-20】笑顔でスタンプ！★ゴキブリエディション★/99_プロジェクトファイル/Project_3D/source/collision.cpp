//************************************************
//
//�Փ˔���[collision.cpp]
//Author�F���c����
//
//************************************************
#include "collision.h"

#include "debugproc.h"

//************************************************
//�����m�̏Փ˔���
//************************************************
bool CollisionSphere(const D3DXVECTOR3 obj1, const float radius1, const D3DXVECTOR3 obj2, const float radius2)
{
    D3DXVECTOR3 Vector = obj1 - obj2;
    float Distance = sqrtf((Vector.x * Vector.x) + (Vector.y * Vector.y) + (Vector.z * Vector.z));

    return (Distance < radius1 + radius2);
}

//************************************************
//AABB���m�̏Փ˔���
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
//XZ���ʂ�AABB�ɂ����āA�ǂ̉ӏ����G��Ă��邩�𔻒�
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
    
    /* obj1�̕Б���X����obj2�̗�����X�����͂ݏo���Ă��� */
    if (obj1.max.x > obj2.min.x &&
        obj1.max.x > obj2.max.x ||
        obj1.min.x < obj2.min.x &&
        obj1.min.x < obj2.max.x)
    {
        /* obj1��min��Z����obj2�̗�����Z���̕��Ɏ��܂��Ă��� */
        if (obj1.min.z < obj2.max.z &&
            obj1.min.z > obj2.min.z)
        {
            minZ = true;

            CntVtx++;
        }

        /* obj1��max��Z����obj2�̗�����Z�̕��Ɏ��܂��Ă��� */
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

    /* obj1�̕Б���Z����obj2�̗�����Z�����͂ݏo���Ă��� */
    if (obj1.max.z > obj2.min.z &&
        obj1.max.z > obj2.max.z ||
        obj1.min.z > obj2.min.z &&
        obj1.min.z > obj2.max.z)
    {
        /* obj1��min��X����obj2�̗�����X���̕��Ɏ��܂��Ă��� */
        if (obj1.min.x < obj2.max.x &&
            obj1.min.x > obj2.min.x)
        {
            minX = true;

            CntVtx++;
        }

        /* obj1��max��X����obj2�̗�����X���̕��Ɏ��܂��Ă��� */
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

    PrintDebugProc("�ڐG���_�F[%d]\n", CntVtx);

    if (CntVtx <= 1)
    {
        Type = OnlyVtx;
    }

    return Type;
}