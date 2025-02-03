//************************************************
//
//カメラ[camera.cpp]
//Author：福田歩希
//
//************************************************
#include "camera.h"

#include "debugproc.h"
#include "input.h"

#include "player.h"

//グローバル変数
Camera g_Camera;	//カメラ情報
static const float g_UP = 80.0f;	/* (視点 - 注視点間に出来る球形軌道そのもののy座標を変更する数値) */

//************************************************
//カメラ初期
//************************************************
void InitCamera(void)
{
	//カメラ情報の初期セット
	g_Camera.posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.rotGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.fPA = 0.0f;
	g_Camera.fPAGoal = 0.0f;
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.fDistance = 150.0f;
	g_Camera.bTrack = false;
}

//************************************************
//カメラ破棄
//************************************************
void UninitCamera(void)
{
	/* 現段階では無し */
}

//************************************************
//カメラ更新
//************************************************
void UpdateCamera(int mode)
{
	//追尾対象物変更
	if (mode != MODE_TITLE)
	{
		//if (GetKeyboardPress(DIK_F1) || GetPressTriggerButtonL()) g_Camera.bTrack = true;
		//else g_Camera.bTrack = false;
	}

	//右スティックで視点変更 (仮)
	if (GetJoyStickR())
	{
		const XINPUT_GAMEPAD GamePad = GetGamePad();

		g_Camera.fPAGoal += (float)(GamePad.sThumbRY * 0.000001);
		g_Camera.rotGoal.y += (float)(GamePad.sThumbRX * 0.000001);
	}
	//キーボードで視点変更
	else
	{
		//左右
		if (GetKeyboardPress(DIK_RIGHT)) g_Camera.rotGoal.y += 0.05f;
		else if (GetKeyboardPress(DIK_LEFT)) g_Camera.rotGoal.y -= 0.05f;

		//上下
		if (GetKeyboardPress(DIK_UP)) g_Camera.fPAGoal += 0.025f;
		else if (GetKeyboardPress(DIK_DOWN)) g_Camera.fPAGoal -= 0.025f;
	}

	//ブレーキ
	g_Camera.rotGoal *= 0.8f;
	g_Camera.fPAGoal *= 0.8f;

	//移動
	g_Camera.rot += g_Camera.rotGoal * 0.5f;
	g_Camera.fPA += g_Camera.fPAGoal * 0.5f;

	//回転範囲
	if (g_Camera.rot.y > D3DX_PI) g_Camera.rot.y = -D3DX_PI;
	if (g_Camera.rot.y < -D3DX_PI) g_Camera.rot.y = D3DX_PI;

	//偏角範囲
	if (g_Camera.fPA > D3DX_PI * 0.45f) g_Camera.fPA = D3DX_PI * 0.45f;
	if (g_Camera.fPA < -D3DX_PI * 0.45f) g_Camera.fPA = -D3DX_PI * 0.45f;

	//対象物の座標
	D3DXVECTOR3 target;
	const Player* pPlayer = GetInfoPlayer();	//プレイヤーを参照
	target = pPlayer->pos;

	//視点を算出
	CalcPosV(target);

	//注視点を算出
	CalcPosR(target);

	PrintDebugProc("カメラの座標( %f %f %f )\n", g_Camera.posV.x, g_Camera.posV.y, g_Camera.posV.z);
}


//************************************************
//視点を算出
//************************************************
void CalcPosV(const D3DXVECTOR3 target)
{
	/* ↓なんとかする予定 */

	static float fA[2] = {};	/* スコープしたとき、視点が注視点に接近するための係数を入れる… */

	g_Camera.bTrack ? fA[1] = g_Camera.fDistance * 1.8f : fA[1] = 0.0f;	/* まあこれぐらい */

	//移動
	fA[0] += (fA[1] - fA[0]) * 0.3f;

	//視点は対象物の後方に
	g_Camera.posV =
	{
		target.x - (sinf(g_Camera.rot.y) * cosf(g_Camera.fPA) * (g_Camera.fDistance - fA[0])),
		target.y - (sinf(g_Camera.fPA) * (g_Camera.fDistance - fA[0])),
		target.z - (cosf(g_Camera.rot.y) * cosf(g_Camera.fPA) * (g_Camera.fDistance - fA[0]))
	};
}

//************************************************
//注視点を算出
//************************************************
void CalcPosR(const D3DXVECTOR3 target)
{
	//注視点を対象物の前方に
	g_Camera.posR =
	{
		target.x + (sinf(g_Camera.rot.y) * cosf(g_Camera.fPA) * g_Camera.fDistance),
		target.y + (sinf(g_Camera.fPA) * g_Camera.fDistance),
		target.z + (cosf(g_Camera.rot.y) * cosf(g_Camera.fPA) * g_Camera.fDistance)
	};
}

//************************************************
//カメラ設定
//************************************************
void SetInfoCamera(int mode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	//プロジェクションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,
		&g_Camera.mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxView);

	D3DXVECTOR3 posV = g_Camera.posV;

	if (mode == MODE_TITLE)
	{
		posV.y += 110.0f;
	}
	else
	{
		if (!g_Camera.bTrack) posV.y += g_UP;
	}

	//ビューマトリックスの生成
	D3DXMatrixLookAtLH(&g_Camera.mtxView,
		&posV,
		&g_Camera.posR,
		&g_Camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW,
		&g_Camera.mtxView);
}

//************************************************
//カメラ情報を取得
//************************************************
Camera* GetInfoCamera(void)
{
	return &g_Camera;
}