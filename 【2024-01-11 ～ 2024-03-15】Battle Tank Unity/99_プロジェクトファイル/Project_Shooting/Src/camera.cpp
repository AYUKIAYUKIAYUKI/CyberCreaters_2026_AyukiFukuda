//************************************************
//
// カメラ[camera.cpp]
// Author：福田歩希
//
//************************************************

/*/ インクルードファイル /*/
#include "camera.h"
// 中枢
#include "input.h"
// 諸処理
#include "player.h"

/*/ マクロ定義 /*/
#define TRACK_VERIFY	// 追従対象切り替え
#define LINE_SPAN 3		// 分割ラインのサイズ

/*/ グローバル変数 /*/
Camera g_Camera[AMOUNT_CAMERA];	// カメラ情報
UIport g_UIport;				// UI用ポート

//************************************************
// カメラ初期
//************************************************
void InitCamera(int joined)
{
	for (int i = 0; i < AMOUNT_CAMERA; i++)
	{ // カメラ情報の初期化	
		g_Camera[i].posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Camera[i].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Camera[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Camera[i].rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Camera[i].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_Camera[i].distance = 200.0f;

		switch (i)
		{ // ビューポートの位置
		case 0:
			g_Camera[i].viewport.X = 0;
			g_Camera[i].viewport.Y = 0;
			break;
		case 1:
			g_Camera[i].viewport.X = SCREEN_HALFWIDTH + LINE_SPAN;
			g_Camera[i].viewport.Y = 0;
			break;
		case 2:
			g_Camera[i].viewport.X = 0;
			g_Camera[i].viewport.Y = SCREEN_HALFHEIGHT + LINE_SPAN;
			break;
		case 3:
			g_Camera[i].viewport.X = SCREEN_HALFWIDTH + LINE_SPAN;
			g_Camera[i].viewport.Y = SCREEN_HALFHEIGHT + LINE_SPAN;
			break;
		}

		// ビューポートのサイズ
		g_Camera[i].viewport.Width = 0;
		g_Camera[i].viewport.Height = 0;

		// ビューポートの深度
		g_Camera[i].viewport.MinZ = 0.0f;
		g_Camera[i].viewport.MaxZ = 1.0f;

		g_Camera[i].durVib = 0;
	}

	// ビューポートサイズ分岐
	viewportSize Size = SetSizeViewport(joined);

	// ビューポートのサイズ反映
	for (int i = 0; i < joined; i++)
	{
		g_Camera[i].viewport.Width = Size.Width;
		g_Camera[i].viewport.Height = Size.Height;
	}

	// UIポートの初期化
	InitUIport();
}

//************************************************
// UIポート初期
//************************************************
void InitUIport(void)
{
	// ビューポートの位置
	g_UIport.viewport.X = 0;
	g_UIport.viewport.Y = 0;

	// ビューポートのサイズ
	g_UIport.viewport.Width = SCREEN_WIDTH;
	g_UIport.viewport.Height = SCREEN_HEIGHT;

	// ビューポートの深度
	g_UIport.viewport.MinZ = 0.0f;
	g_UIport.viewport.MaxZ = 1.0f;
}

//************************************************
// ビューポートサイズ設定
//************************************************
viewportSize SetSizeViewport(int joined)
{
	// ビューポートサイズ用
	viewportSize Size = { 0,0 };

	switch (joined)
	{ // 人数でそのまま分岐
	case 1:
		Size.Width = SCREEN_WIDTH;
		Size.Height = SCREEN_HEIGHT;
		break;

	case 2:
		Size.Width = SCREEN_HALFWIDTH - LINE_SPAN;
		Size.Height = SCREEN_HEIGHT;
		break;

	case 3:
		Size.Width = SCREEN_HALFWIDTH - LINE_SPAN;
		Size.Height = SCREEN_HALFHEIGHT - LINE_SPAN;
		break;

	case 4:
		Size.Width = SCREEN_HALFWIDTH - LINE_SPAN;
		Size.Height = SCREEN_HALFHEIGHT - LINE_SPAN;
		break;
	}

	return Size;
}

//************************************************
// カメラ更新
//************************************************
void UpdateCamera(int joined)
{
	const Player* pPlayer = GetInfoPlayer();	//!< 試験的にプレイヤーを参照します。

	// ビューポートサイズ分岐
	viewportSize Size = SetSizeViewport(joined);

	// ビューポートのサイズ反映
	for (int i = 0; i < joined; i++)
	{
		g_Camera[i].viewport.Width = Size.Width;
		g_Camera[i].viewport.Height = Size.Height;
	}

#if 0

	// キーボードで視点変更
	static int camera_id = -1;

	if (GetKeyboardTrigger(DIK_1))
	{
		camera_id = 0;
	}
	else if (GetKeyboardTrigger(DIK_2))
	{
		camera_id = 1;
	}
	else if (GetKeyboardTrigger(DIK_3))
	{
		camera_id = 2;
	}
	else if (GetKeyboardTrigger(DIK_4))
	{
		camera_id = 3;
	}

	// ズームイン / アウト
	if (GetKeyboardPress(DIK_AT) && g_Camera[camera_id].distance > 10.0f)
	{
		g_Camera[camera_id].distance -= 10.0f;
	}
	else if (GetKeyboardPress(DIK_COLON))
	{
		g_Camera[camera_id].distance += 10.0f;
	}
	
	// 距離間リセット
	if (GetKeyboardTrigger(DIK_BACKSLASH))
	{
		g_Camera[camera_id].distance = 200.0f;
	}

	// 左右
	if (GetKeyboardPress(DIK_RIGHT))
	{
		g_Camera[camera_id].rot_goal.y += 0.025f;
	}
	else if (GetKeyboardPress(DIK_LEFT))
	{
		g_Camera[camera_id].rot_goal.y -= 0.025f;
	}

	// 上下
	if (GetKeyboardPress(DIK_UP))
	{
		g_Camera[camera_id].rot_goal.x += 0.025f;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{
		g_Camera[camera_id].rot_goal.x -= 0.025f;
	}

#endif	// _DEBUG

	for (int i = 0; i < joined; i++)
	{
		if (!pPlayer[i].use)
		{ // 未使用の場合コンティニュー
			continue;
		}

		if (GetJoyStickR(i))
		{ // 右スティックで視点変更 (仮)

			const XINPUT_GAMEPAD GamePad = GetGamePad(i);

			g_Camera[i].rot_goal.x += (float)(GamePad.sThumbRY * 0.000001);
			g_Camera[i].rot_goal.y += (float)(GamePad.sThumbRX * 0.000001);
		}

		// 移動量ブレーキ
		g_Camera[i].rot_goal *= 0.8f;

		// 移動反映
		g_Camera[i].rot += g_Camera[i].rot_goal * 0.5f;

		// 水平方向の回転範囲
		if (g_Camera[i].rot.y > D3DX_PI)
		{
			g_Camera[i].rot.y = -D3DX_PI;
		}
		if (g_Camera[i].rot.y < -D3DX_PI)
		{
			g_Camera[i].rot.y = D3DX_PI;
		}

		// 偏角の回転範囲
		if (g_Camera[i].rot.x > D3DX_PI * 0.1f)
		{
			g_Camera[i].rot.x = D3DX_PI * 0.1f;
		}
		if (g_Camera[i].rot.x < -D3DX_PI * 0.1f)
		{
			g_Camera[i].rot.x = -D3DX_PI * 0.1f;
		}

		// 対象物の座標
		D3DXVECTOR3 target;
		target = pPlayer[i].pos;

		// 視点を算出
		CalcPosV(i, target);

		// 注視点を算出
		CalcPosR(i, target);
	}
}

//************************************************
// 視点を算出
//************************************************
void VibCamera(int id)
{
	g_Camera[id].durVib = 15;
}

//************************************************
// 視点を算出
//************************************************
void CalcPosV(int id, const D3DXVECTOR3 target)
{
	// 視点は対象物の後方に
	g_Camera[id].posV =
	{
		target.x - (sinf(g_Camera[id].rot.y) * cosf(g_Camera[id].rot.x) * (g_Camera[id].distance)),
		target.y - (sinf(g_Camera[id].rot.x) * (g_Camera[id].distance)),
		target.z - (cosf(g_Camera[id].rot.y) * cosf(g_Camera[id].rot.x) * (g_Camera[id].distance))
	};
}

//************************************************
// 注視点を算出
//************************************************
void CalcPosR(int id, const D3DXVECTOR3 target)
{
	// 注視点を対象物の前方に
	g_Camera[id].posR =
	{
		target.x + (sinf(g_Camera[id].rot.y) * cosf(g_Camera[id].rot.x) * g_Camera[id].distance),
		target.y + (sinf(g_Camera[id].rot.x) * g_Camera[id].distance),
		target.z + (cosf(g_Camera[id].rot.y) * cosf(g_Camera[id].rot.x) * g_Camera[id].distance)
	};
}

//************************************************
// カメラ設定
//************************************************
void SetInfoCamera(int id, int joined)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ビューポートの設定
	pDevice->SetViewport(&g_Camera[id].viewport);

	// 画面バッファクリア
	pDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// プロジェクションマトリックスを計算
	CalcMatrixProjectionCamera(id, joined);

	// ビューマトリックスを計算
	CalcMatrixViewCamera(id);
}

//************************************************
// プロジェクションマトリックスを計算
//************************************************
void CalcMatrixProjectionCamera(int id, int joined)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera[id].mtxProjection);

	// プロジェクションマトリックスを生成
	if (joined != 2)
	{ // 通常アスペクト比
		D3DXMatrixPerspectiveFovLH(&g_Camera[id].mtxProjection,
			D3DXToRadian(45.0f),
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
			10.0f,
			10000.0f);
	}
	else
	{ // 横幅のみ半幅サイズ
		D3DXMatrixPerspectiveFovLH(&g_Camera[id].mtxProjection,
			D3DXToRadian(45.0f),
			(float)SCREEN_HALFWIDTH / (float)SCREEN_HEIGHT,
			10.0f,
			10000.0f);
	}

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,
		&g_Camera[id].mtxProjection);
}

//************************************************
// ビューマトリックスを計算
//************************************************
void CalcMatrixViewCamera(int id)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera[id].mtxView);

	// 視点位置の調整用
	D3DXVECTOR3 posV = g_Camera[id].posV;
	D3DXVECTOR3 posR = g_Camera[id].posR;
	posV.y += 150.0f;

	if (g_Camera[id].durVib > 0)
	{
		posV += { (float)(rand() % 15), 0.0f, (float)(rand() % 15) };
		posR += { (float)(rand() % 15), 0.0f, (float)(rand() % 15) };
			
		g_Camera[id].durVib--;
	}

	// ビューマトリックスの生成
	D3DXMatrixLookAtLH(&g_Camera[id].mtxView,
		&posV,
		&posR,
		&g_Camera[id].vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW,
		&g_Camera[id].mtxView);
}

//************************************************
// UIポートの設定
//************************************************
void SetInfoUIport(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ビューポートの設定
	pDevice->SetViewport(&g_UIport.viewport);

	/*---【クリアしない…？】---*/

	// 画面バッファクリア
	//pDevice->Clear(0, NULL,
	//	(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
	//	D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
}

//************************************************
// カメラ情報を取得
//************************************************
Camera* GetInfoCamera(void)
{
	return &g_Camera[0];
}