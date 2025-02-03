//============================================================================
// 
// 波紋エフェクト [ripple.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "ripple.h"
#include "utility.h"

// デバイス取得用
#include "renderer.h"

//============================================================================
// コンストラクタ
//============================================================================
CRipple::CRipple() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },	// 描画優先度を指定
	m_velocity{ 0.0f, 0.0f, 0.0f }					// 加速度
{

}

//============================================================================
// デストラクタ
//============================================================================
CRipple::~CRipple()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CRipple::Init()
{
	// 基底クラスの初期設定
	if (FAILED(CObject_X::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CRipple::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CRipple::Update()
{
	// 基底クラスの更新処理
	CObject_X::Update();

	// 回転
	auto rot{ GetRot() };
#if 1
	rot.x += fabsf(CUtility::GetInstance()->GetRandomValue<float>()) * 0.001f;
	rot.y += fabsf(CUtility::GetInstance()->GetRandomValue<float>()) * 0.001f;
	rot.z = atan2f(m_velocity.y, m_velocity.x);
#else
	//rot.x += fabsf(CUtility::GetInstance()->GetRandomValue<float>()) * 0.01f;
	//rot.y += fabsf(CUtility::GetInstance()->GetRandomValue<float>()) * 0.01f;
	rot.x += CUtility::GetInstance()->GetRandomValue<float>() * 0.0001f;
	rot.y += CUtility::GetInstance()->GetRandomValue<float>() * 0.0001f;
	rot.z = atan2f(m_velocity.y, m_velocity.x) + (D3DX_PI * 0.5f);
#endif
	SetRot(rot);

	// 移動
	D3DXVECTOR3 pos = GetPos();
	pos += m_velocity;
	SetPos(pos);

	// 加速度を減少
	m_velocity *= 0.9f;

	// 縮小
	CUtility::GetInstance()->DecrementUntilGone(GetScale(), -0.01f);

	// アルファ値が減少
	if (CUtility::GetInstance()->DecrementUntilGone(GetAlpha(), -0.01f))
	{
		// 自身を破棄
		CObject::SetRelease();
	}
}

//============================================================================
// 描画処理
//============================================================================
void CRipple::Draw()
{
	//auto pDev{ CRenderer::GetInstance()->GetDeviece() };

	//// 深度バッファへの書き込みを無効に
	//pDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// 基底クラスの描画処理
	CObject_X::Draw();

	//// 深度バッファへの書き込みを無効に
	//pDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//============================================================================
// 加速度を取得
//============================================================================
D3DXVECTOR3& CRipple::GetVelocity()
{
	return m_velocity;
}

//============================================================================
// 加速度を設定
//============================================================================
void CRipple::SetVelocity(D3DXVECTOR3 velocity)
{
	m_velocity = velocity;
}

//============================================================================
// 生成
//============================================================================
CRipple* CRipple::Create(D3DXVECTOR3&& pos, D3DXVECTOR3 velocity)
{
	CRipple* pRipple = DBG_NEW CRipple{};

	// 生成失敗
	if (!pRipple)
	{
		assert(false);
	}

	// タイプを設定
	pRipple->SetType(CObject::TYPE::NONE);

	// 初期設定
	pRipple->Init();

	// 座標の設定
	pRipple->SetPos(pos);

	// 加速度を設定
	pRipple->SetVelocity(velocity);

	// モデルを取得
	CModel_X_Manager::MODEL* model{ nullptr };

	switch (rand() % 2)
	{
	case 0:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::RIPPLE01);
		break;

	case 1:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::RIPPLE03);
		break;

	default:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::RIPPLE01);
		break;
	}

	// モデルを設定
	pRipple->BindModel(model);

	// サイズを設定
	pRipple->SetSize(model->size);

	// 描画される前に一度更新しておく
	pRipple->Update();

	return pRipple;
}