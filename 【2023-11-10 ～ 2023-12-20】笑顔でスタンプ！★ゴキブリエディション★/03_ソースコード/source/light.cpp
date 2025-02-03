//************************************************
//
//ライト[light.cpp]
//Author：福田歩希
//
//************************************************
#include "light.h"

#include "input.h"

//マクロ定義
#define AMOUNT_LIGHT	(3)	//ライトの数

//グローバル変数
D3DLIGHT9 g_aLight[AMOUNT_LIGHT] = {};	//ライト情報
int g_nLightType = 0;	//ライト識別

//************************************************
//ライト初期
//************************************************
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//ライトの情報を初期化
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	//ライト識別番号
	g_nLightType = 0;

	for (int i = 0; i < AMOUNT_LIGHT; i++)
	{
		D3DXVECTOR3 vecDir;	//設定用方向ベクトル

		//ライトの種類を設定
		g_aLight[i].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		g_aLight[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//ライトの方向を設定
		switch (i)
		{
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
		D3DXVec3Normalize(&vecDir, &vecDir);	//ベクトルを取得する
		g_aLight[i].Direction = vecDir;

		//ライトを設定する
		pDevice->SetLight(i, &g_aLight[i]);

		//ライトを有効にする
		pDevice->LightEnable(i, TRUE);
	}
}

//************************************************
//ライト破棄
//************************************************
void UninitLight(void)
{

}

//************************************************
//ライト更新
//************************************************
void UpdateLight(void)
{
	//ライト番号変更
	ChangeLightType();

	//移動
	MoveLight();

	//リセット
	ResetLight();

	//移動など反映
	SetLight();
}

//************************************************
//ライト番号変更
//************************************************
void ChangeLightType(void)
{
	//ライト番号変更
	if (GetKeyboardTrigger(DIK_0))
	{
		g_nLightType < 2 ? g_nLightType++ : g_nLightType = 0;
	}
}

//************************************************
//ライト移動
//************************************************
void MoveLight(void)
{
	//X方向変更
	if (GetKeyboardPress(DIK_1))
	{
		g_aLight[g_nLightType].Direction.x += 0.1f;
	}
	else if (GetKeyboardPress(DIK_2))
	{
		g_aLight[g_nLightType].Direction.x -= 0.1f;
	}

	//Y方向変更
	if (GetKeyboardPress(DIK_3))
	{
		g_aLight[g_nLightType].Direction.x += 0.1f;
	}
	else if (GetKeyboardPress(DIK_4))
	{
		g_aLight[g_nLightType].Direction.x -= 0.1f;
	}

	//Z方向変更
	if (GetKeyboardPress(DIK_5))
	{
		g_aLight[g_nLightType].Direction.z += 0.1f;
	}
	else if (GetKeyboardPress(DIK_6))
	{
		g_aLight[g_nLightType].Direction.z -= 0.1f;
	}
}

//************************************************
//ライトリセット
//************************************************
void ResetLight(void)
{
	//ライトリセット
	if (GetKeyboardTrigger(DIK_R))
	{
		switch (g_nLightType)
		{
		case 0:
			g_aLight[g_nLightType].Direction = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
			break;
		case 1:
			g_aLight[g_nLightType].Direction = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
			break;
		case 2:
			g_aLight[g_nLightType].Direction = D3DXVECTOR3(0.8f, 0.1f, 0.4f);
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
		D3DXVECTOR3 vecDir = g_aLight[i].Direction;	//設定用方向ベクトル
		D3DXVec3Normalize(&vecDir, &vecDir);	//ベクトルを取得する
		g_aLight[i].Direction = vecDir;

		//ライトを設定する
		pDevice->SetLight(i, &g_aLight[i]);
	}
}

//************************************************
//ライト情報を取得
//************************************************
D3DLIGHT9* GetInfoLight(void)
{
	return &g_aLight[0];
}

//************************************************
//ライト番号情報を取得
//************************************************
int GetInfoLightType(void)
{
	return g_nLightType;
}