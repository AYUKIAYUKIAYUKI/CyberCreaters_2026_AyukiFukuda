//************************************************
//
// 衝突判定[collision.cpp]
// Author：福田歩希
//
//************************************************

/*/ インクルードファイル /*/
#include "collision.h"
// デバッグ時
#ifdef _DEBUG
#include "debugproc.h"
#include <assert.h>
#endif	// _DEBUG

#include "player.h"

//************************************************
// 球同士の衝突判定
//************************************************
bool CollisionSph(D3DXVECTOR3 sph1, float r1, D3DXVECTOR3 sph2, float r2)
{
    // 球1から球2へのベクトルを算出
    D3DXVECTOR3 vec = sph2 - sph1;

    // 球間の距離を算出
    float dist = sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));

    // 球間距離が互いの半径の合計以下であれば接触
    return (dist <= r1 + r2);
}

//************************************************
// 球とAABBの衝突判定
//************************************************
bool CollisionSphAABB(D3DXVECTOR3 sph, float r, COLLISION_AABB box)
{ 
#if 0   // これ球の判定と同じ

    // 球から箱へのベクトルを算出
    D3DXVECTOR3 vec = box.pos - sph;

    // お互いの距離を算出
    float dist = sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));

    // 各軸で、距離がお互いの半径の合計以下であれば接触
    return (dist <= box.vec.x);

#elif 1 // 通常での球と箱の当たり判定

    // 球から箱へのベクトルを算出
    D3DXVECTOR3 vec = box.pos - sph;
    
    return ((float)fabsf(vec.x) < box.vec.x + r &&
        (float)fabsf(vec.y) < box.vec.y + r &&
        (float)fabsf(vec.z) < box.vec.z + r);

#elif 0 // Y軸補正での球と箱の当たり判定

    // 箱の位置をコピー
    D3DXVECTOR3 copy = box.pos;

    // Y軸に補正をかける
    copy.y += box.vec.y;

    // 球から箱へのベクトルを算出
    D3DXVECTOR3 vec = copy - sph;

    return ((float)fabsf(vec.x) < box.vec.x + r &&
        (float)fabsf(vec.y) < box.vec.y + r &&
        (float)fabsf(vec.z) < box.vec.z + r);

#endif
}

//************************************************
// AABB同士の衝突判定
//************************************************
bool CollisionAABB(COLLISION_AABB box1, COLLISION_AABB box2)
{
#if 0   // 値そのものを使用する方式

    // 各軸でお互いの最大・最小を結ぶ線分が重なれば接触
    return (box1.min.x < box2.max.x &&
        box1.max.x > box2.min.x &&
        box1.min.y < box2.max.y &&
        box1.max.y > box2.min.y &&
        box1.min.z < box2.max.z &&
        box1.max.z > box2.min.z);

#elif 1 // 中心点と各軸方向へのベクトルから値を出す方式

    // 各軸でお互いの最大・最小を結ぶ線分が重なれば接触
    return (box1.pos.x - box1.vec.x < box2.pos.x + box2.vec.x &&
        box1.pos.x + box1.vec.x > box2.pos.x - box2.vec.x &&
        box1.pos.y - box1.vec.y < box2.pos.y + box2.vec.y &&
        box1.pos.y + box1.vec.y > box2.pos.y - box2.vec.y &&
        box1.pos.z - box1.vec.z < box2.pos.z + box2.vec.z &&
        box1.pos.z + box1.vec.z > box2.pos.z - box2.vec.z);

#endif
}

//************************************************
// 球→AABBの衝突判定と押しだし(仮)
//************************************************
void CollisionVecSphAABB(int id, D3DXVECTOR3 sph, float r, COLLISION_AABB box)
{
    // 球から箱へのベクトルを算出
    D3DXVECTOR3 vec = box.pos - sph;

#if 0   // ゴミ

    if (sph.x + pPlayer[id].move.x < box.pos.x + (box.vec.x + r) &&
        sph.x + pPlayer[id].move.x > box.pos.x - (box.vec.x + r))
    { // X軸の範囲内に入りこんでいるか確認
        PrintDebugProc("X軸の範囲内\n");

        if (sph.z < box.pos.z)
        {
            PrintDebugProc("【南に検出しました】\n");
            vecnor = { 0.0f, 0.0f, -1.0f };
            posresult = { pPlayer[id].pos.x, 0.0f, box.pos.z - (box.vec.z + r) };
        }
        else
        {
            PrintDebugProc("【北に検出しました】\n");
            vecnor = { 0.0f, 0.0f, 1.0f };
            posresult = { pPlayer[id].pos.x, 0.0f, box.pos.z + (box.vec.z + r) };
        }
    }
    else if (sph.z + pPlayer[id].move.z < box.pos.z + (box.vec.z + r) &&
        sph.z + pPlayer[id].move.z > box.pos.z - (box.vec.z + r))
    { // Z軸の範囲内に入り込んでいるか確認
        PrintDebugProc("Z軸の範囲内\n");

        if (sph.x < box.pos.x)
        {
            PrintDebugProc("【西に検出しました】\n");
            vecnor = { -1.0f, 0.0f, 0.0f };
            posresult = { box.pos.x - (box.vec.x + r), 0.0f, pPlayer[id].pos.z };
        }
        else
        {
            PrintDebugProc("【東に検出しました】\n");
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

    // 区画を割り出す
    if (sph.z > box.pos.z)
    {
        if (pp == 0)
        {
            ppp = 0;
            PrintDebugProc("区画：A\n");
        }
        else
        {
            ppp = 1;
            PrintDebugProc("区画：B\n");
        }
    }
    else
    {
        if (pp == 0)
        {
            ppp = 2;
            PrintDebugProc("区画：C\n");
        }
        else
        {
            ppp = 3;
            PrintDebugProc("区画：D\n");
        }
    }

    if (ppp == 0)
    { // C区画の場合

        D3DXVECTOR3 startppp = { box.pos.x + box.vec.x, 0.0f, box.pos.z + box.vec.z }; // 始点
        D3DXVECTOR3 destppp = { box.pos.x - box.vec.x, 0.0f, box.pos.z + box.vec.z };  // 終点
        D3DXVECTOR3 vecvtxppp = destppp - startppp;
        D3DXVECTOR3 vecnearppp = sph - startppp;
        D3DXVECTOR3 v1ppp = vecvtxppp * D3DXVec3Dot(D3DXVec3Normalize(&vecvtxppp, &vecvtxppp), &vecnearppp) / D3DXVec3Length(&vecvtxppp) - vecnearppp;

        PrintDebugProc("%f %f %f\n", v1ppp.x, v1ppp.y, v1ppp.z);
    }
    if (ppp == 1)
    { // C区画の場合

        D3DXVECTOR3 startppp = { box.pos.x + box.vec.x, 0.0f, box.pos.z + box.vec.z }; // 始点
        D3DXVECTOR3 destppp = { box.pos.x - box.vec.x, 0.0f, box.pos.z + box.vec.z };  // 終点
        D3DXVECTOR3 vecvtxppp = destppp - startppp;
        D3DXVECTOR3 vecnearppp = sph - startppp;
        D3DXVECTOR3 v1ppp = vecvtxppp * D3DXVec3Dot(D3DXVec3Normalize(&vecvtxppp, &vecvtxppp), &vecnearppp) / D3DXVec3Length(&vecvtxppp) - vecnearppp;

        PrintDebugProc("%f %f %f\n", v1ppp.x, v1ppp.y, v1ppp.z);
    }

#endif

    if ((float)fabsf(vec.x) < box.vec.x + r &&
        (float)fabsf(vec.y) < box.vec.y + r &&
        (float)fabsf(vec.z) < box.vec.z + r)
    {   // その球がその箱と衝突しているなら

#if 0   //座標を比較(ゴミ)

        Player* pPlayer = GetInfoPlayer();

        // 箱の持つX軸範囲内に、球の中心が入っているか判定
        if (sph.x > box.pos.x - box.vec.x &&
            sph.x < box.pos.x + box.vec.x)
        {
            // 上下のどちら側にいるか判別
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
            // 左右のどちら側にいるか判別
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


#elif 0 // 仮想の面を生成してみる

        /* その箱に仮想の面を4面生成する
        (今回はAABBのため直接頂点を割り当ててみる)
        (Y軸の移動がないのでXZ軸の4方向で済ませる) */

        // 判定情報には面も頂点も含まれていないのでこちらで用意
        for (int id_face = 0; id_face < 4; id_face++)
        {
            PrintDebugProc("[ face %d ]\n", id_face + 1);

            // 頂点位置を割り当て格納
            D3DXVECTOR3 pos[4] = {};

            // 頂点情報を生成する
            switch (id_face)
            {
                // 前
            case 0:

                pos[0] = { box.pos.x - box.vec.x, box.pos.y + box.vec.y, box.pos.z - box.vec.z };
                pos[1] = { box.pos.x + box.vec.x, box.pos.y + box.vec.y, box.pos.z - box.vec.z };
                pos[2] = { box.pos.x - box.vec.x, box.pos.y - box.vec.y, box.pos.z - box.vec.z };
                pos[3] = { box.pos.x + box.vec.x, box.pos.y - box.vec.y, box.pos.z - box.vec.z };

                break;

                // 後
            case 1:

                pos[0] = { box.pos.x - box.vec.x, box.pos.y + box.vec.y, box.pos.z + box.vec.z };
                pos[1] = { box.pos.x + box.vec.x, box.pos.y + box.vec.y, box.pos.z + box.vec.z };
                pos[2] = { box.pos.x - box.vec.x, box.pos.y - box.vec.y, box.pos.z + box.vec.z };
                pos[3] = { box.pos.x + box.vec.x, box.pos.y - box.vec.y, box.pos.z + box.vec.z };

                break;

                // 左
            case 2:

                pos[0] = { box.pos.x - box.vec.x, box.pos.y + box.vec.y, box.pos.z + box.vec.z };
                pos[1] = { box.pos.x - box.vec.x, box.pos.y + box.vec.y, box.pos.z - box.vec.z };
                pos[2] = { box.pos.x - box.vec.x, box.pos.y - box.vec.y, box.pos.z + box.vec.z };
                pos[3] = { box.pos.x - box.vec.x, box.pos.y - box.vec.y, box.pos.z - box.vec.z };

                break;

                // 右
            case 3:

                pos[0] = { box.pos.x + box.vec.x, box.pos.y + box.vec.y, box.pos.z - box.vec.z };
                pos[1] = { box.pos.x + box.vec.x, box.pos.y + box.vec.y, box.pos.z + box.vec.z };
                pos[2] = { box.pos.x + box.vec.x, box.pos.y - box.vec.y, box.pos.z - box.vec.z };
                pos[3] = { box.pos.x + box.vec.x, box.pos.y - box.vec.y, box.pos.z + box.vec.z };

                break;
            }

            // デバッグ表示
            for (int id_vtx = 0; id_vtx < 4; id_vtx++)
            {
                PrintDebugProc("vtx %d : [ x %f ] [ y %f ] [ z %f ]\n", id_vtx + 1, pos[id_vtx].x, pos[id_vtx].y, pos[id_vtx].z);
            }
        }

#elif 0 // 法線ベクトルから算出(衝突点の法線を取得する方法を知らない)

        Player* pPlayer = GetInfoPlayer();

        // 移動ベクトルを算出
        D3DXVECTOR3 vecmove = (pPlayer->pos + pPlayer->move) - pPlayer->pos;

        // 面法線ベクトルを設定
        /*---【衝突地点の法線を取得しましょう】---*/
        D3DXVECTOR3 vecnor = { 0.0f, 0.0f, -1.0f };   // 仮

        // 壁ずりベクトルを算出
        D3DXVECTOR3 vecresult = vecmove + (-D3DXVec3Dot(&vecmove, &vecnor) * vecnor);

        // めりこんしまうので面の正面に移動
        pPlayer->pos.z = box.pos.z - (box.vec.z + r);

        // 壁ずりベクトルのみ反映
        pPlayer->move = vecresult;

#elif 1 // 正しそうな計算(無理やりプレイヤーを参照)

        int side = -1;  // 球が左右どちらにいるか
        int area = -1;  // 球がどの区画にいるか

        D3DXVECTOR3 start = {};     // 線分ベクトル用の始点
        D3DXVECTOR3 dest = {};      // 線分ベクトル用の終点
        D3DXVECTOR3 vecvtx = {};    // 線分のベクトル
        D3DXVECTOR3 vecp = {};      // 始点から球へのベクトル
        D3DXVECTOR3 vecarea = {};   // 球から始点へのベクトル…

        Player* pPlayer = GetInfoPlayer();  /*---【引数に足りない情報を特別に拡張】---*/
        D3DXVECTOR3 posresult = {}; // 補正位置
        D3DXVECTOR3 vecnor = {};    // 面法線ベクトル

        // 箱の中心から見て球が左右どちらにあるか
        if (sph.x < box.pos.x)
        {
            side = 0;
        }
        else
        {
            side = 1;
        }

        // 箱の中心から見て球がどの区画にあるか
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

        // ゴミ
        switch (area)
        { 
            // A区画の場合
        case 0:
            start = { box.pos.x + box.vec.x, 0.0f, box.pos.z + box.vec.z }; // 始点
            dest = { box.pos.x - box.vec.x, 0.0f, box.pos.z + box.vec.z };  // 終点

            vecvtx = dest - start;  // 線分のベクトル
            vecp = sph - start;     // 始点からプレイヤーへのベクトル

            // プレイヤーから面へのベクトル
            vecarea = vecvtx * D3DXVec3Dot(D3DXVec3Normalize(&vecvtx, &vecvtx), &vecp) / D3DXVec3Length(&vecvtx) - vecp;

            // どの面にあたるか推定し、位置の補正と法線ベクトルの算出をする
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

            // B区画の場合
        case 1:
            start = { box.pos.x + box.vec.x, 0.0f, box.pos.z + box.vec.z }; // 始点
            dest = { box.pos.x - box.vec.x, 0.0f, box.pos.z + box.vec.z };  // 終点

            vecvtx = dest - start;  // 線分のベクトル
            vecp = sph - start;     // 始点からプレイヤーへのベクトル

            // プレイヤーから面へのベクトル
            vecarea = vecvtx * D3DXVec3Dot(D3DXVec3Normalize(&vecvtx, &vecvtx), &vecp) / D3DXVec3Length(&vecvtx) - vecp;

            // どの面にあたるか推定し、位置の補正と法線ベクトルの算出をする
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

            // C区画の場合
        case 2:
            start = { box.pos.x - box.vec.x, 0.0f, box.pos.z - box.vec.z }; // 始点
            dest = { box.pos.x + box.vec.x, 0.0f, box.pos.z - box.vec.z };  // 終点

            vecvtx = dest - start;  // 線分のベクトル
            vecp = sph - start;     // 始点からプレイヤーへのベクトル

            // プレイヤーから面へのベクトル
            vecarea = vecvtx * D3DXVec3Dot(D3DXVec3Normalize(&vecvtx, &vecvtx), &vecp) / D3DXVec3Length(&vecvtx) - vecp;

            // どの面にあたるか推定し、位置の補正と法線ベクトルの算出をする
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

            // D区画の場合
        case 3:
            start = { box.pos.x - box.vec.x, 0.0f, box.pos.z - box.vec.z }; // 始点
            dest = { box.pos.x + box.vec.x, 0.0f, box.pos.z - box.vec.z };  // 終点

            vecvtx = dest - start;  // 線分のベクトル
            vecp = sph - start;     // 始点からプレイヤーへのベクトル

            // プレイヤーから面へのベクトル
            vecarea = vecvtx * D3DXVec3Dot(D3DXVec3Normalize(&vecvtx, &vecvtx), &vecp) / D3DXVec3Length(&vecvtx) - vecp;

            // どの面にあたるか推定し、位置の補正と法線ベクトルの算出をする
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

        // 移動ベクトルを算出
        D3DXVECTOR3 vecmove = (pPlayer[id].pos + pPlayer[id].move) - pPlayer[id].pos;

        // 壁ずりベクトルを算出
        D3DXVECTOR3 vecresult = vecmove + (-D3DXVec3Dot(&vecmove, &vecnor) * vecnor);

        // めりこんしまうので面の正面に移動(ゴミ)
        pPlayer[id].pos = posresult;

        // 壁ずりベクトルのみ反映
        pPlayer[id].move = vecresult;

#endif
    }
}