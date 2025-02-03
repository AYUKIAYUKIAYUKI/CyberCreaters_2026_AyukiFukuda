//============================================================================
// 
// 煙エフェクト [smoke.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "smoke.h"
#include "utility.h"

// デバイス取得用
#include "renderer.h"

//============================================================================
// コンストラクタ
//============================================================================
CSmoke::CSmoke() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },	// 描画優先度を指定
	m_velocity{ 0.0f, 0.0f, 0.0f }					// 加速度
{

}

//============================================================================
// デストラクタ
//============================================================================
CSmoke::~CSmoke()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CSmoke::Init()
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
void CSmoke::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CSmoke::Update()
{
	// 基底クラスの更新処理
	CObject_X::Update();

	// 回転
	D3DXVECTOR3 NewRot{ GetRot() };
	//D3DXVECTOR3 NewRot{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>() };
	NewRot += m_velocity * 0.1f;
	NewRot.z += fabsf(CUtility::GetInstance()->GetRandomValue<float>()) * 0.0005f;
	SetRot(NewRot);

	// 加速度を減少
	m_velocity = CUtility::GetInstance()->AdjustToTarget(m_velocity, D3DXVECTOR3{ 0.0f, 0.0f, 0.0f }, 0.05f);

	// 上昇・回転ブレ
	//m_velocity.y += 0.025f;

	// 移動
	D3DXVECTOR3 pos = GetPos();
	pos += m_velocity;
	SetPos(pos);

	// 拡大
	float fNewSclae{ GetScale() };
	fNewSclae += 0.01f;
	SetScale(fNewSclae);

	// アルファ値が減少
	SetAlpha(CUtility::GetInstance()->AdjustToTarget(GetAlpha(), 0.0f, 0.05f));

	// 自身を破棄
	if (GetAlpha() < 0.01f)
	{
		CObject::SetRelease();
	}
}

//============================================================================
// 描画処理
//============================================================================
void CSmoke::Draw()
{
	auto pDev{ CRenderer::GetInstance()->GetDeviece() };

	// 深度バッファへの書き込みを無効に
	pDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// 頂点法線の自動正規化を有効に
	pDev->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// 基底クラスの描画処理
	CObject_X::Draw();

	// 頂点法線の自動正規化を無効に
	pDev->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	// 深度バッファへの書き込みを無効に
	pDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//============================================================================
// 加速度を取得
//============================================================================
D3DXVECTOR3& CSmoke::GetVelocity()
{
	return m_velocity;
}

//============================================================================
// 加速度を設定
//============================================================================
void CSmoke::SetVelocity(D3DXVECTOR3 velocity)
{
	m_velocity = velocity;
}

//============================================================================
// 生成
//============================================================================
CSmoke* CSmoke::Create(D3DXVECTOR3&& pos, D3DXVECTOR3 velocity)
{
	CSmoke* pSmoke = DBG_NEW CSmoke{};

	// 生成失敗
	if (!pSmoke)
	{
		assert(false);
	}

	// タイプを設定
	pSmoke->SetType(CObject::TYPE::NONE);

	// 初期設定
	pSmoke->Init();

	// 座標の設定
	pSmoke->SetPos(pos);

	// 加速度を設定
	pSmoke->SetVelocity(velocity);

	// モデルを取得
	auto model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::PARTICLE02) };

	// モデルを設定
	pSmoke->BindModel(model);

	// サイズを設定
	pSmoke->SetSize(model->size);

	// 透明感薄く
	//pSmoke->SetAlpha(0.8f);

	// 描画される前に一度更新しておく
	pSmoke->Update();

	return pSmoke;
}