//************************************************
//
// �Փ˔���[collision.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "collision.h"
// �f�o�b�O��
#ifdef _DEBUG
#include "debugproc.h"
#include <assert.h>
#endif	// _DEBUG

#include "player.h"

//************************************************
// �����m�̏Փ˔���
//************************************************
bool CollisionSph(D3DXVECTOR3 sph1, float r1, D3DXVECTOR3 sph2, float r2)
{
    // ��1���狅2�ւ̃x�N�g�����Z�o
    D3DXVECTOR3 vec = sph2 - sph1;

    // ���Ԃ̋������Z�o
    float dist = sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));

    // ���ԋ������݂��̔��a�̍��v�ȉ��ł���ΐڐG
    return (dist <= r1 + r2);
}

//************************************************
// ����AABB�̏Փ˔���
//************************************************
bool CollisionSphAABB(D3DXVECTOR3 sph, float r, COLLISION_AABB box)
{ 
#if 0   // ���ꋅ�̔���Ɠ���

    // �����甠�ւ̃x�N�g�����Z�o
    D3DXVECTOR3 vec = box.pos - sph;

    // ���݂��̋������Z�o
    float dist = sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));

    // �e���ŁA���������݂��̔��a�̍��v�ȉ��ł���ΐڐG
    return (dist <= box.vec.x);

#elif 1 // �ʏ�ł̋��Ɣ��̓����蔻��

    // �����甠�ւ̃x�N�g�����Z�o
    D3DXVECTOR3 vec = box.pos - sph;
    
    return ((float)fabsf(vec.x) < box.vec.x + r &&
        (float)fabsf(vec.y) < box.vec.y + r &&
        (float)fabsf(vec.z) < box.vec.z + r);

#elif 0 // Y���␳�ł̋��Ɣ��̓����蔻��

    // ���̈ʒu���R�s�[
    D3DXVECTOR3 copy = box.pos;

    // Y���ɕ␳��������
    copy.y += box.vec.y;

    // �����甠�ւ̃x�N�g�����Z�o
    D3DXVECTOR3 vec = copy - sph;

    return ((float)fabsf(vec.x) < box.vec.x + r &&
        (float)fabsf(vec.y) < box.vec.y + r &&
        (float)fabsf(vec.z) < box.vec.z + r);

#endif
}

//************************************************
// AABB���m�̏Փ˔���
//************************************************
bool CollisionAABB(COLLISION_AABB box1, COLLISION_AABB box2)
{
#if 0   // �l���̂��̂��g�p�������

    // �e���ł��݂��̍ő�E�ŏ������Ԑ������d�Ȃ�ΐڐG
    return (box1.min.x < box2.max.x &&
        box1.max.x > box2.min.x &&
        box1.min.y < box2.max.y &&
        box1.max.y > box2.min.y &&
        box1.min.z < box2.max.z &&
        box1.max.z > box2.min.z);

#elif 1 // ���S�_�Ɗe�������ւ̃x�N�g������l���o������

    // �e���ł��݂��̍ő�E�ŏ������Ԑ������d�Ȃ�ΐڐG
    return (box1.pos.x - box1.vec.x < box2.pos.x + box2.vec.x &&
        box1.pos.x + box1.vec.x > box2.pos.x - box2.vec.x &&
        box1.pos.y - box1.vec.y < box2.pos.y + box2.vec.y &&
        box1.pos.y + box1.vec.y > box2.pos.y - box2.vec.y &&
        box1.pos.z - box1.vec.z < box2.pos.z + box2.vec.z &&
        box1.pos.z + box1.vec.z > box2.pos.z - box2.vec.z);

#endif
}

//************************************************
// ����AABB�̏Փ˔���Ɖ�������(��)
//************************************************
void CollisionVecSphAABB(int id, D3DXVECTOR3 sph, float r, COLLISION_AABB box)
{
    // �����甠�ւ̃x�N�g�����Z�o
    D3DXVECTOR3 vec = box.pos - sph;

#if 0   // �S�~

    if (sph.x + pPlayer[id].move.x < box.pos.x + (box.vec.x + r) &&
        sph.x + pPlayer[id].move.x > box.pos.x - (box.vec.x + r))
    { // X���͈͓̔��ɓ��肱��ł��邩�m�F
        PrintDebugProc("X���͈͓̔�\n");

        if (sph.z < box.pos.z)
        {
            PrintDebugProc("�y��Ɍ��o���܂����z\n");
            vecnor = { 0.0f, 0.0f, -1.0f };
            posresult = { pPlayer[id].pos.x, 0.0f, box.pos.z - (box.vec.z + r) };
        }
        else
        {
            PrintDebugProc("�y�k�Ɍ��o���܂����z\n");
            vecnor = { 0.0f, 0.0f, 1.0f };
            posresult = { pPlayer[id].pos.x, 0.0f, box.pos.z + (box.vec.z + r) };
        }
    }
    else if (sph.z + pPlayer[id].move.z < box.pos.z + (box.vec.z + r) &&
        sph.z + pPlayer[id].move.z > box.pos.z - (box.vec.z + r))
    { // Z���͈͓̔��ɓ��荞��ł��邩�m�F
        PrintDebugProc("Z���͈͓̔�\n");

        if (sph.x < box.pos.x)
        {
            PrintDebugProc("�y���Ɍ��o���܂����z\n");
            vecnor = { -1.0f, 0.0f, 0.0f };
            posresult = { box.pos.x - (box.vec.x + r), 0.0f, pPlayer[id].pos.z };
        }
        else
        {
            PrintDebugProc("�y���Ɍ��o���܂����z\n");
            vecnor = { 1.0f, 0.0f, 0.0f };
            posresult = { box.pos.x + (box.vec.x + r), 0.0f, pPlayer[id].pos.z };
        }
    } 

#elif 0

    int pp = -1;
    int ppp = -1;

    if (sph.x < box.pos.x)
    {
        pp = 0;
    }
    else
    {
        pp = 1;
    }

    // ��������o��
    if (sph.z > box.pos.z)
    {
        if (pp == 0)
        {
            ppp = 0;
            PrintDebugProc("���FA\n");
        }
        else
        {
            ppp = 1;
            PrintDebugProc("���FB\n");
        }
    }
    else
    {
        if (pp == 0)
        {
            ppp = 2;
            PrintDebugProc("���FC\n");
        }
        else
        {
            ppp = 3;
            PrintDebugProc("���FD\n");
        }
    }

    if (ppp == 0)
    { // C���̏ꍇ

        D3DXVECTOR3 startppp = { box.pos.x + box.vec.x, 0.0f, box.pos.z + box.vec.z }; // �n�_
        D3DXVECTOR3 destppp = { box.pos.x - box.vec.x, 0.0f, box.pos.z + box.vec.z };  // �I�_
        D3DXVECTOR3 vecvtxppp = destppp - startppp;
        D3DXVECTOR3 vecnearppp = sph - startppp;
        D3DXVECTOR3 v1ppp = vecvtxppp * D3DXVec3Dot(D3DXVec3Normalize(&vecvtxppp, &vecvtxppp), &vecnearppp) / D3DXVec3Length(&vecvtxppp) - vecnearppp;

        PrintDebugProc("%f %f %f\n", v1ppp.x, v1ppp.y, v1ppp.z);
    }
    if (ppp == 1)
    { // C���̏ꍇ

        D3DXVECTOR3 startppp = { box.pos.x + box.vec.x, 0.0f, box.pos.z + box.vec.z }; // �n�_
        D3DXVECTOR3 destppp = { box.pos.x - box.vec.x, 0.0f, box.pos.z + box.vec.z };  // �I�_
        D3DXVECTOR3 vecvtxppp = destppp - startppp;
        D3DXVECTOR3 vecnearppp = sph - startppp;
        D3DXVECTOR3 v1ppp = vecvtxppp * D3DXVec3Dot(D3DXVec3Normalize(&vecvtxppp, &vecvtxppp), &vecnearppp) / D3DXVec3Length(&vecvtxppp) - vecnearppp;

        PrintDebugProc("%f %f %f\n", v1ppp.x, v1ppp.y, v1ppp.z);
    }

#endif

    if ((float)fabsf(vec.x) < box.vec.x + r &&
        (float)fabsf(vec.y) < box.vec.y + r &&
        (float)fabsf(vec.z) < box.vec.z + r)
    {   // ���̋������̔��ƏՓ˂��Ă���Ȃ�

#if 0   //���W���r(�S�~)

        Player* pPlayer = GetInfoPlayer();

        // ���̎���X���͈͓��ɁA���̒��S�������Ă��邩����
        if (sph.x > box.pos.x - box.vec.x &&
            sph.x < box.pos.x + box.vec.x)
        {
            // �㉺�̂ǂ��瑤�ɂ��邩����
            if (sph.z < box.pos.z)
            {
                pPlayer->pos.z = box.pos.z - (box.vec.z + r);
            }
            else if (sph.z > box.pos.z)
            {
                pPlayer->pos.z = box.pos.z - (box.vec.z + r);
            }

            pPlayer->move.z = 0.0f;
        }
        else if (sph.x <= box.pos.x - box.vec.x ||
            sph.x >= box.pos.x + box.vec.x)
        {
            // ���E�̂ǂ��瑤�ɂ��邩����
            if (sph.x < box.pos.x)
            {
                pPlayer->pos.z = box.pos.z - (box.vec.z + r);
            }
            else if (sph.z > box.pos.z)
            {
                pPlayer->pos.z = box.pos.z - (box.vec.z + r);
            }

            pPlayer->move.z = 0.0f;
        }


#elif 0 // ���z�̖ʂ𐶐����Ă݂�

        /* ���̔��ɉ��z�̖ʂ�4�ʐ�������
        (�����AABB�̂��ߒ��ڒ��_�����蓖�ĂĂ݂�)
        (Y���̈ړ����Ȃ��̂�XZ����4�����ōς܂���) */

        // ������ɂ͖ʂ����_���܂܂�Ă��Ȃ��̂ł�����ŗp��
        for (int id_face = 0; id_face < 4; id_face++)
        {
            PrintDebugProc("[ face %d ]\n", id_face + 1);

            // ���_�ʒu�����蓖�Ċi�[
            D3DXVECTOR3 pos[4] = {};

            // ���_���𐶐�����
            switch (id_face)
            {
                // �O
            case 0:

                pos[0] = { box.pos.x - box.vec.x, box.pos.y + box.vec.y, box.pos.z - box.vec.z };
                pos[1] = { box.pos.x + box.vec.x, box.pos.y + box.vec.y, box.pos.z - box.vec.z };
                pos[2] = { box.pos.x - box.vec.x, box.pos.y - box.vec.y, box.pos.z - box.vec.z };
                pos[3] = { box.pos.x + box.vec.x, box.pos.y - box.vec.y, box.pos.z - box.vec.z };

                break;

                // ��
            case 1:

                pos[0] = { box.pos.x - box.vec.x, box.pos.y + box.vec.y, box.pos.z + box.vec.z };
                pos[1] = { box.pos.x + box.vec.x, box.pos.y + box.vec.y, box.pos.z + box.vec.z };
                pos[2] = { box.pos.x - box.vec.x, box.pos.y - box.vec.y, box.pos.z + box.vec.z };
                pos[3] = { box.pos.x + box.vec.x, box.pos.y - box.vec.y, box.pos.z + box.vec.z };

                break;

                // ��
            case 2:

                pos[0] = { box.pos.x - box.vec.x, box.pos.y + box.vec.y, box.pos.z + box.vec.z };
                pos[1] = { box.pos.x - box.vec.x, box.pos.y + box.vec.y, box.pos.z - box.vec.z };
                pos[2] = { box.pos.x - box.vec.x, box.pos.y - box.vec.y, box.pos.z + box.vec.z };
                pos[3] = { box.pos.x - box.vec.x, box.pos.y - box.vec.y, box.pos.z - box.vec.z };

                break;

                // �E
            case 3:

                pos[0] = { box.pos.x + box.vec.x, box.pos.y + box.vec.y, box.pos.z - box.vec.z };
                pos[1] = { box.pos.x + box.vec.x, box.pos.y + box.vec.y, box.pos.z + box.vec.z };
                pos[2] = { box.pos.x + box.vec.x, box.pos.y - box.vec.y, box.pos.z - box.vec.z };
                pos[3] = { box.pos.x + box.vec.x, box.pos.y - box.vec.y, box.pos.z + box.vec.z };

                break;
            }

            // �f�o�b�O�\��
            for (int id_vtx = 0; id_vtx < 4; id_vtx++)
            {
                PrintDebugProc("vtx %d : [ x %f ] [ y %f ] [ z %f ]\n", id_vtx + 1, pos[id_vtx].x, pos[id_vtx].y, pos[id_vtx].z);
            }
        }

#elif 0 // �@���x�N�g������Z�o(�Փ˓_�̖@�����擾������@��m��Ȃ�)

        Player* pPlayer = GetInfoPlayer();

        // �ړ��x�N�g�����Z�o
        D3DXVECTOR3 vecmove = (pPlayer->pos + pPlayer->move) - pPlayer->pos;

        // �ʖ@���x�N�g����ݒ�
        /*---�y�Փ˒n�_�̖@�����擾���܂��傤�z---*/
        D3DXVECTOR3 vecnor = { 0.0f, 0.0f, -1.0f };   // ��

        // �ǂ���x�N�g�����Z�o
        D3DXVECTOR3 vecresult = vecmove + (-D3DXVec3Dot(&vecmove, &vecnor) * vecnor);

        // �߂肱�񂵂܂��̂Ŗʂ̐��ʂɈړ�
        pPlayer->pos.z = box.pos.z - (box.vec.z + r);

        // �ǂ���x�N�g���̂ݔ��f
        pPlayer->move = vecresult;

#elif 1 // ���������Ȍv�Z(�������v���C���[���Q��)

        int side = -1;  // �������E�ǂ���ɂ��邩
        int area = -1;  // �����ǂ̋��ɂ��邩

        D3DXVECTOR3 start = {};     // �����x�N�g���p�̎n�_
        D3DXVECTOR3 dest = {};      // �����x�N�g���p�̏I�_
        D3DXVECTOR3 vecvtx = {};    // �����̃x�N�g��
        D3DXVECTOR3 vecp = {};      // �n�_���狅�ւ̃x�N�g��
        D3DXVECTOR3 vecarea = {};   // ������n�_�ւ̃x�N�g���c

        Player* pPlayer = GetInfoPlayer();  /*---�y�����ɑ���Ȃ�������ʂɊg���z---*/
        D3DXVECTOR3 posresult = {}; // �␳�ʒu
        D3DXVECTOR3 vecnor = {};    // �ʖ@���x�N�g��

        // ���̒��S���猩�ċ������E�ǂ���ɂ��邩
        if (sph.x < box.pos.x)
        {
            side = 0;
        }
        else
        {
            side = 1;
        }

        // ���̒��S���猩�ċ����ǂ̋��ɂ��邩
        if (sph.z > box.pos.z)
        {
            if (side == 0)
            {
                area = 0;
            }
            else
            {
                area = 1;
            }
        }
        else
        {
            if (side == 0)
            {
                area = 2;
            }
            else
            {
                area = 3;
            }
        }

        // �S�~
        switch (area)
        { 
            // A���̏ꍇ
        case 0:
            start = { box.pos.x + box.vec.x, 0.0f, box.pos.z + box.vec.z }; // �n�_
            dest = { box.pos.x - box.vec.x, 0.0f, box.pos.z + box.vec.z };  // �I�_

            vecvtx = dest - start;  // �����̃x�N�g��
            vecp = sph - start;     // �n�_����v���C���[�ւ̃x�N�g��

            // �v���C���[����ʂւ̃x�N�g��
            vecarea = vecvtx * D3DXVec3Dot(D3DXVec3Normalize(&vecvtx, &vecvtx), &vecp) / D3DXVec3Length(&vecvtx) - vecp;

            // �ǂ̖ʂɂ����邩���肵�A�ʒu�̕␳�Ɩ@���x�N�g���̎Z�o������
            if (vecarea.z > -(r + pPlayer[id].move.z))
            {
                vecnor = { -1.0f, 0.0f, 0.0f };
                posresult = { box.pos.x - (box.vec.x + r), 0.0f, pPlayer[id].pos.z };
            }
            else if (vecarea.x > vecarea.z)
            {
                vecnor = { 0.0f, 0.0f, 1.0f };
                posresult = { pPlayer[id].pos.x, 0.0f, box.pos.z + (box.vec.z + r) };
            }
            break;

            // B���̏ꍇ
        case 1:
            start = { box.pos.x + box.vec.x, 0.0f, box.pos.z + box.vec.z }; // �n�_
            dest = { box.pos.x - box.vec.x, 0.0f, box.pos.z + box.vec.z };  // �I�_

            vecvtx = dest - start;  // �����̃x�N�g��
            vecp = sph - start;     // �n�_����v���C���[�ւ̃x�N�g��

            // �v���C���[����ʂւ̃x�N�g��
            vecarea = vecvtx * D3DXVec3Dot(D3DXVec3Normalize(&vecvtx, &vecvtx), &vecp) / D3DXVec3Length(&vecvtx) - vecp;

            // �ǂ̖ʂɂ����邩���肵�A�ʒu�̕␳�Ɩ@���x�N�g���̎Z�o������
            if (vecarea.x < vecarea.z)
            {
                vecnor = { 1.0f, 0.0f, 0.0f };
                posresult = { box.pos.x + (box.vec.x + r), 0.0f, pPlayer[id].pos.z };
            }
            else if (vecarea.x > vecarea.z)
            {
                vecnor = { 0.0f, 0.0f, 1.0f };
                posresult = { pPlayer[id].pos.x, 0.0f, box.pos.z + (box.vec.z + r) };
            }
            break;

            // C���̏ꍇ
        case 2:
            start = { box.pos.x - box.vec.x, 0.0f, box.pos.z - box.vec.z }; // �n�_
            dest = { box.pos.x + box.vec.x, 0.0f, box.pos.z - box.vec.z };  // �I�_

            vecvtx = dest - start;  // �����̃x�N�g��
            vecp = sph - start;     // �n�_����v���C���[�ւ̃x�N�g��

            // �v���C���[����ʂւ̃x�N�g��
            vecarea = vecvtx * D3DXVec3Dot(D3DXVec3Normalize(&vecvtx, &vecvtx), &vecp) / D3DXVec3Length(&vecvtx) - vecp;

            // �ǂ̖ʂɂ����邩���肵�A�ʒu�̕␳�Ɩ@���x�N�g���̎Z�o������
            if (vecarea.x > vecarea.z)
            {
                vecnor = { -1.0f, 0.0f, 0.0f };
                posresult = { box.pos.x - (box.vec.x + r), 0.0f, pPlayer[id].pos.z };
            }
            else if (vecarea.x < vecarea.z)
            {
                vecnor = { 0.0f, 0.0f, -1.0f };
                posresult = { pPlayer[id].pos.x, 0.0f, box.pos.z - (box.vec.z + r) };
            }
            break;

            // D���̏ꍇ
        case 3:
            start = { box.pos.x - box.vec.x, 0.0f, box.pos.z - box.vec.z }; // �n�_
            dest = { box.pos.x + box.vec.x, 0.0f, box.pos.z - box.vec.z };  // �I�_

            vecvtx = dest - start;  // �����̃x�N�g��
            vecp = sph - start;     // �n�_����v���C���[�ւ̃x�N�g��

            // �v���C���[����ʂւ̃x�N�g��
            vecarea = vecvtx * D3DXVec3Dot(D3DXVec3Normalize(&vecvtx, &vecvtx), &vecp) / D3DXVec3Length(&vecvtx) - vecp;

            // �ǂ̖ʂɂ����邩���肵�A�ʒu�̕␳�Ɩ@���x�N�g���̎Z�o������
            if (vecarea.z < (r - pPlayer[id].move.z))
            {
                vecnor = { 1.0f, 0.0f, 0.0f };
                posresult = { box.pos.x + (box.vec.x + r), 0.0f, pPlayer[id].pos.z };
            }
            else if (vecarea.x < vecarea.z)
            {
                vecnor = { 0.0f, 0.0f, -1.0f };
                posresult = { pPlayer[id].pos.x, 0.0f, box.pos.z - (box.vec.z + r) };
            }
            break;
        }

        // �ړ��x�N�g�����Z�o
        D3DXVECTOR3 vecmove = (pPlayer[id].pos + pPlayer[id].move) - pPlayer[id].pos;

        // �ǂ���x�N�g�����Z�o
        D3DXVECTOR3 vecresult = vecmove + (-D3DXVec3Dot(&vecmove, &vecnor) * vecnor);

        // �߂肱�񂵂܂��̂Ŗʂ̐��ʂɈړ�(�S�~)
        pPlayer[id].pos = posresult;

        // �ǂ���x�N�g���̂ݔ��f
        pPlayer[id].move = vecresult;

#endif
    }
}