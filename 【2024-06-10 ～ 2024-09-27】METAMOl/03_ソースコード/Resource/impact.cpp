//============================================================================
// 
// 衝突エフェクト [impact.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "impact.h"
#include "utility.h"

// デバイス取得用
#include "renderer.h"

// キル座標取得用
#include "barrier_manager.h"

//============================================================================
// コンストラクタ
//============================================================================
CImpact::CImpact() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },
	m_Velocity{ 0.0f, 0.0f, 0.0f }
{

}

//============================================================================
// デストラクタ
//============================================================================
CImpact::~CImpact()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CImpact::Init()
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
void CImpact::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CImpact::Update()
{
	// 基底クラスの更新処理
	CObject_X::Update();

	// 回転
	D3DXVECTOR3 NewRot{ GetRot() };
	NewRot = m_Velocity;
	SetRot(NewRot);

	// 重力加速
	//CUtility::GetInstance()->Gravity(m_Velocity);

	// 加速度が減衰
	m_Velocity = CUtility::GetInstance()->AdjustToTarget(m_Velocity, D3DXVECTOR3{ 0.0f, 0.0f, 0.0f }, 0.1f);

	// 移動
	D3DXVECTOR3 NewPos = GetPos();
	NewPos += m_Velocity;
	SetPos(NewPos);

	// 縮小
	if (CUtility::GetInstance()->DecrementUntilGone(GetScale(), -0.05f))
	{
		// 自身を破棄
		CObject::SetRelease();
	}

	// 消滅するかチェック
	//CheckDisappear();
}

//============================================================================
// 描画処理
//============================================================================
void CImpact::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 加速度を取得
//============================================================================
D3DXVECTOR3& CImpact::GetVelocity()
{
	return m_Velocity;
}

//============================================================================
// 加速度を設定
//============================================================================
void CImpact::SetVelocity(D3DXVECTOR3 Velocity)
{
	m_Velocity = Velocity;
}

//============================================================================
// 生成
//============================================================================
CImpact* CImpact::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Velocity)
{
	CImpact* pImpact = DBG_NEW CImpact{};

	// 生成失敗
	if (!pImpact)
	{
		assert(false);
	}

	// タイプを設定
	pImpact->SetType(CObject::TYPE::NONE);

	// 初期設定
	pImpact->Init();

	// 座標の設定
	pImpact->SetPos(Pos);

	// 加速度を設定
	pImpact->SetVelocity(Velocity);

	// モデル用ポインタ
	CModel_X_Manager::MODEL* Model{ nullptr };

	// モデルを取得
	Model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::IMPACT);

	// モデルを設定
	pImpact->BindModel(Model);

	// サイズを設定
	pImpact->SetSize(Model->size);

	// 描画される前に一度更新しておく
	pImpact->Update();

	return pImpact;
}

//============================================================================
// 消滅するかチェック
//============================================================================
void CImpact::CheckDisappear()
{
	// バリアの最も低い座標を下回ったら
	if (GetPos().y < CBarrier_Manager::GetCurrentMinPosY())
	{
		// 破棄
		SetRelease();
	}
}