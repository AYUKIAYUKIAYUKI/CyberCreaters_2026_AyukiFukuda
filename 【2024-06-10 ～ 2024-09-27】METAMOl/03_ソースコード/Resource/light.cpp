//============================================================================
// 
// ライト [light.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "light.h"

// キーボード取得用
#include "manager.h"

// デバイス取得用
#include "renderer.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CLight::CLight()
{
	// ライト情報クリア
	ZeroMemory(&m_light[0], sizeof(D3DLIGHT9));

	for (int i = 0; i < MAX_LIGHT; i++)
	{ // ライトの向きクリア
		m_tempDirection[i] = { 0.0f, 0.0f, 0.0f };
	}

	// 操作番号リセット
	m_nID = 0;

	// 向きのテンプレをセット
	SetTempDirection();

	// ライト生成
	Create();

	// 初回反映
	SetLight();
}

//============================================================================
// デストラクタ
//============================================================================
CLight::~CLight()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CLight::Init()
{
	return S_OK;
}

//============================================================================
// 更新処理
//============================================================================
void CLight::Update()
{
#ifdef _DEBUG
	// 操作番号変更
	ChangeID();

	// 操作
	Control();

	// リセット
	Reset();

	// ライトをセット
	SetLight();
#endif	// _DEBUG
}

//============================================================================
// 向きのテンプレをセット
//============================================================================
void CLight::SetTempDirection()
{
	// ライトの向きのテンプレをセット
	m_tempDirection[0] = { 0.2f, -0.8f, 0.4f };
	m_tempDirection[1] = { -0.2f, 0.8f, -0.4f };
	m_tempDirection[2] = { 0.8f, 0.1f, 0.4f };
}

//============================================================================
// ライト生成
//============================================================================
void CLight::Create()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	for (int i = 0; i < MAX_LIGHT; i++)
	{ // ライト情報初期設定

		// ライトの種類を設定
		m_light[i].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの拡散光を設定
		m_light[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ライトの方向を設定
		m_light[i].Direction = m_tempDirection[i];

		// ライトを有効にする
		pDev->LightEnable(i, TRUE);
	}
}

//============================================================================
// 操作番号変更
//============================================================================
void CLight::ChangeID()
{
	// ライト番号変更
	if (CManager::GetKeyboard()->GetTrigger(DIK_LSHIFT))
	{
		m_nID < MAX_LIGHT ? m_nID++ : m_nID = 0;
	}
}

//============================================================================
// ライト操作
//============================================================================
void CLight::Control()
{
	// X方向変更
	if (CManager::GetKeyboard()->GetPress(DIK_5))
	{
		m_light[m_nID].Direction.x += 0.1f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_6))
	{
		m_light[m_nID].Direction.x -= 0.1f;
	}

	// Y方向変更
	if (CManager::GetKeyboard()->GetPress(DIK_7))
	{
		m_light[m_nID].Direction.y += 0.1f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_8))
	{
		m_light[m_nID].Direction.y -= 0.1f;
	}

	// Z方向変更
	if (CManager::GetKeyboard()->GetPress(DIK_9))
	{
		m_light[m_nID].Direction.z += 0.1f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_0))
	{
		m_light[m_nID].Direction.z -= 0.1f;
	}
}

//============================================================================
// リセット
//============================================================================
void CLight::Reset()
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_R))
	{
		// ライトの方向をリセット
		m_light[m_nID].Direction = m_tempDirection[m_nID];
	}
}

//============================================================================
// ライトをセット
//============================================================================
void CLight::SetLight()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// ベクトルをコピー
		D3DXVECTOR3 vecDir = m_light[i].Direction;

		// ベクトルを正規化
		D3DXVec3Normalize(&vecDir, &vecDir);

		// 正規化ベクトルを反映
		m_light[i].Direction = vecDir;

		// ライトを設定する
		pDev->SetLight(i, &m_light[i]);
	}
}