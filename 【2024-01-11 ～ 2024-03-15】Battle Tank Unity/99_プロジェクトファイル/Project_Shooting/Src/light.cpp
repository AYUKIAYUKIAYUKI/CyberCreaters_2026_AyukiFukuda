//************************************************
//
// ライト[light.cpp]
// Author：福田歩希
//
//************************************************

/*/ インクルードファイル /*/
#include "light.h"
// 中枢
#include "input.h"

/*/ マクロ定義 /*/
#define AMOUNT_LIGHT 3	// ライトの数

/*/ グローバル変数 /*/
D3DLIGHT9 g_Light[AMOUNT_LIGHT] = {};	// ライト情報
int g_LightType = 0;					// ライト番号識別用

//************************************************
//ライト初期
//************************************************
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ライトの情報を初期化
	ZeroMemory(&g_Light[0], sizeof(D3DLIGHT9));

	// ライト番号
	g_LightType = 0;

	for (int i = 0; i < AMOUNT_LIGHT; i++)
	{
		D3DXVECTOR3 vecDir;	// 設定用方向ベクトル

		// ライトの種類を設定
		g_Light[i].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの拡散光を設定
		g_Light[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		switch (i)
		{ // ライトの方向を設定
		case 0:
			vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
			break;
		case 1:
			vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
			break;
		case 2:
			vecDir = D3DXVECTOR3(0.8f, 0.1f, 0.4f);
			break;
		}

		D3DXVec3Normalize(&vecDir, &vecDir);	// ベクトルを取得する
		g_Light[i].Direction = vecDir;

		// ライトを設定する
		pDevice->SetLight(i, &g_Light[i]);

		// ライトを有効にする
		pDevice->LightEnable(i, TRUE);
	}
}

//************************************************
// ライト更新
//************************************************
void UpdateLight(void)
{
	// 移動
	MoveLight();

	// 移動反映
	SetLight();
}

//************************************************
// ライト番号変更
//************************************************
void ChangeLightType(void)
{
	if (GetKeyboardTrigger(DIK_LSHIFT))
	{ // ライト番号変更
		g_LightType < 2 ? g_LightType++ : g_LightType = 0;
	}
}

//************************************************
// ライト移動
//************************************************
void MoveLight(void)
{
	// ライト番号変更
	ChangeLightType();

	if (GetKeyboardPress(DIK_5))
	{ // X方向変更
		g_Light[g_LightType].Direction.x += 0.1f;
	}
	else if (GetKeyboardPress(DIK_6))
	{
		g_Light[g_LightType].Direction.x -= 0.1f;
	}

	if (GetKeyboardPress(DIK_7))
	{ //Y方向変更
		g_Light[g_LightType].Direction.y += 0.1f;
	}
	else if (GetKeyboardPress(DIK_8))
	{
		g_Light[g_LightType].Direction.y -= 0.1f;
	}

	if (GetKeyboardPress(DIK_9))
	{ // Z方向変更
		g_Light[g_LightType].Direction.z += 0.1f;
	}
	else if (GetKeyboardPress(DIK_0))
	{
		g_Light[g_LightType].Direction.z -= 0.1f;
	}

	// 全ライト移動リセット
	ResetLight();
}

//************************************************
// ライトリセット
//************************************************
void ResetLight(void)
{
	if (GetKeyboardTrigger(DIK_R))
	{ // ライトリセット
		switch (g_LightType)
		{
		case 0:
			g_Light[g_LightType].Direction = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
			break;
		case 1:
			g_Light[g_LightType].Direction = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
			break;
		case 2:
			g_Light[g_LightType].Direction = D3DXVECTOR3(0.8f, 0.1f, 0.4f);
			break;
		}
	}
}

//************************************************
//ライト反映
//************************************************
void SetLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//変更反映
	for (int i = 0; i < AMOUNT_LIGHT; i++)
	{
		D3DXVECTOR3 vecDir = g_Light[i].Direction;	//設定用方向ベクトル
		D3DXVec3Normalize(&vecDir, &vecDir);	//ベクトルを取得する
		g_Light[i].Direction = vecDir;

		//ライトを設定する
		pDevice->SetLight(i, &g_Light[i]);
	}
}

//************************************************
// ライト情報を取得
//************************************************
D3DLIGHT9* GetInfoLight(void)
{
	return &g_Light[0];
}

//************************************************
// ライト番号情報を取得
//************************************************
int GetInfoLightType(void)
{
	return g_LightType;
}