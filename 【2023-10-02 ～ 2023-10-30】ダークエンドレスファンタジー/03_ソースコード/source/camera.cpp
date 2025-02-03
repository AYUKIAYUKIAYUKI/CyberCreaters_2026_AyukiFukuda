//************************************************
//
//カメラ(偽)処理[camera.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "camera.h"
#include "player.h"

D3DXVECTOR3 g_Camera_pos;

//************************************************
//カメラ座標初期化処理
//************************************************
void Init_Camera(void)
{
	//位置を初期化
	g_Camera_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//************************************************
//スクロール処理
//************************************************
void ConvertInfo_Screen(D3DXVECTOR3* real_pos)
{
	PLAYER* pPlayer = GetInfo_Player();

	//プレイヤーの移動量をブロックにあてはめ
	real_pos->x -= pPlayer->move.x;
}