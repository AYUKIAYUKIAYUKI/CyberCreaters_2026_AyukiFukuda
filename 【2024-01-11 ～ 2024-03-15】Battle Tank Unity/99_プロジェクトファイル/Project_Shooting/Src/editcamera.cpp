//************************************************
//
// 編集カメラ[editcamera.cpp]
// Author：福田歩希
//
//************************************************

/*/ インクルードファイル /*/
#include "editcamera.h"
// 中枢
#include "input.h"
// 諸処理
#include "object.h"

/*/ マクロ定義 /*/
#define AA_MODE	1	// 投影モード変更

/*/ グローバル変数 /*/
EditCamera g_EditCamera;	// 編集カメラ情報

//************************************************
// カメラ初期
//************************************************
void InitEditCamera(void)
{
	// 編集カメラ情報の初期化	
	g_EditCamera.posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_EditCamera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_EditCamera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_EditCamera.rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_EditCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_EditCamera.distance = 300.0f;

	// ビューポートの位置
	g_EditCamera.viewport.X = 0;
	g_EditCamera.viewport.Y = 0;

	// ビューポートのサイズ
	g_EditCamera.viewport.Width = SCREEN_WIDTH;
	g_EditCamera.viewport.Height = SCREEN_HEIGHT;

	// ビューポートの深度
	g_EditCamera.viewport.MinZ = 0.0f;
	g_EditCamera.viewport.MaxZ = 1.0f;
}

//************************************************
// カメラ更新
//************************************************
void UpdateEditCamera(void)
{
	const Object* pGizmoObject = GetInfoGizmoObject();

	// ズームイン / アウト
	if (GetKeyboardPress(DIK_AT) && g_EditCamera.distance > 10.0f)
	{
		g_EditCamera.distance -= 10.0f;
	}
	else if (GetKeyboardPress(DIK_COLON))
	{
		g_EditCamera.distance += 10.0f;
	}

	// 距離間リセット
	if (GetKeyboardTrigger(DIK_BACKSLASH))
	{
		g_EditCamera.distance = 200.0f;
	}

	if (GetKeyboardPress(DIK_LALT))
	{ // L - Alt押下
		bool move = false;
		float X = 0.0f;
		float Z = 0.0f;

		if (GetKeyboardPress(DIK_LEFT))
		{
			X = -1.0f;
		}
		else if (GetKeyboardPress(DIK_RIGHT))
		{
			X = 1.0f;
		}

		if (GetKeyboardPress(DIK_UP))
		{
			Z = 1.0f;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{
			Z = -1.0f;
		}

		if (X != 0.0f || Z != 0.0f)
		{ // 何かを入力していれば移動している判定
			move = true;
		}

		if (move)
		{
			g_EditCamera.rot.y = atan2f(X, Z);
		}
	}
	else
	{
		// 左右
		if (GetKeyboardPress(DIK_RIGHT))
		{
			g_EditCamera.rot_goal.y += 0.025f;
		}
		else if (GetKeyboardPress(DIK_LEFT))
		{
			g_EditCamera.rot_goal.y -= 0.025f;
		}

		// 上下
		if (GetKeyboardPress(DIK_UP))
		{
			g_EditCamera.rot_goal.x += 0.025f;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{
			g_EditCamera.rot_goal.x -= 0.025f;
		}
	}

	// 移動量ブレーキ
	g_EditCamera.rot_goal *= 0.8f;

	// 移動反映
	g_EditCamera.rot += g_EditCamera.rot_goal * 0.5f;

	// 水平方向の回転範囲
	if (g_EditCamera.rot.y > D3DX_PI)
	{
		g_EditCamera.rot.y = -D3DX_PI;
	}
	else if (g_EditCamera.rot.y < -D3DX_PI)
	{
		g_EditCamera.rot.y = D3DX_PI;
	}

	//偏角の回転範囲
	if (g_EditCamera.rot.x > D3DX_PI * 0.45f)
	{
		g_EditCamera.rot.x = D3DX_PI * 0.45f;
	}
	else if (g_EditCamera.rot.x < -D3DX_PI * 0.45f)
	{
		g_EditCamera.rot.x = -D3DX_PI * 0.45f;
	}

	// 対象物の座標
	D3DXVECTOR3 target;
	target = pGizmoObject->pos;

	// 視点を算出
	CalcEditPosV(target);

	// 注視点を算出
	CalcEditPosR(target);
}

//************************************************
// 視点を算出
//************************************************
void CalcEditPosV(const D3DXVECTOR3 target)
{
	// 視点は対象物の後方に
	g_EditCamera.posV =
	{
		target.x - (sinf(g_EditCamera.rot.y) * cosf(g_EditCamera.rot.x) * (g_EditCamera.distance)),
		target.y - (sinf(g_EditCamera.rot.x) * (g_EditCamera.distance)),
		target.z - (cosf(g_EditCamera.rot.y) * cosf(g_EditCamera.rot.x) * (g_EditCamera.distance))
	};
}

//************************************************
// 注視点を算出
//************************************************
void CalcEditPosR(const D3DXVECTOR3 target)
{
	// 注視点を対象物の前方に
	g_EditCamera.posR =
	{
		target.x + (sinf(g_EditCamera.rot.y) * cosf(g_EditCamera.rot.x) * g_EditCamera.distance),
		target.y + (sinf(g_EditCamera.rot.x) * g_EditCamera.distance),
		target.z + (cosf(g_EditCamera.rot.y) * cosf(g_EditCamera.rot.x) * g_EditCamera.distance)
	};
}

//************************************************
// カメラ設定
//************************************************
void SetInfoEditCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ビューポートの設定
	pDevice->SetViewport(&g_EditCamera.viewport);

	// 画面バッファクリア
	pDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_EditCamera.mtxProjection);

#if AA_MODE

	// プロジェクションマトリックスを生成
	D3DXMatrixPerspectiveFovLH(&g_EditCamera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

#else

	// 平行投影モード
	D3DXMatrixOrthoLH(&g_EditCamera.mtxProjection,
		(float)SCREEN_WIDTH,
		(float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

#endif	// AA_MODE

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,
		&g_EditCamera.mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_EditCamera.mtxView);

	// 視点位置の調整用
	D3DXVECTOR3 posV = g_EditCamera.posV;
	D3DXVECTOR3 posR = g_EditCamera.posR;

	// ビューマトリックスの生成
	D3DXMatrixLookAtLH(&g_EditCamera.mtxView,
		&posV,
		&posR,
		&g_EditCamera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW,
		&g_EditCamera.mtxView);
}

//************************************************
// カメラ情報を取得
//************************************************
EditCamera* GetInfoEditCamera(void)
{
	return &g_EditCamera;
}