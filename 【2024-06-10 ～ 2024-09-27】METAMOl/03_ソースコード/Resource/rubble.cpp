//============================================================================
// 
// がれきエフェクト [rubble.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "rubble.h"
#include "utility.h"

// デバイス取得用
#include "renderer.h"

// キル座標取得用
#include "barrier_manager.h"

//============================================================================
// コンストラクタ
//============================================================================
CRubble::CRubble() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },
	m_Velocity{ 0.0f, 0.0f, 0.0f }
{

}

//============================================================================
// デストラクタ
//============================================================================
CRubble::~CRubble()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CRubble::Init()
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
void CRubble::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CRubble::Update()
{
	// 基底クラスの更新処理
	CObject_X::Update();

	// 回転
	D3DXVECTOR3 NewRot{ GetRot() };
	NewRot = m_Velocity;
	SetRot(NewRot);

	// 重力加速
	CUtility::GetInstance()->Gravity(m_Velocity);

	// 移動
	D3DXVECTOR3 NewPos = GetPos();
	NewPos += m_Velocity;
	SetPos(NewPos);

	// 消滅するかチェック
	CheckDisappear();
}

//============================================================================
// 描画処理
//============================================================================
void CRubble::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 加速度を取得
//============================================================================
D3DXVECTOR3& CRubble::GetVelocity()
{
	return m_Velocity;
}

//============================================================================
// 加速度を設定
//============================================================================
void CRubble::SetVelocity(D3DXVECTOR3 Velocity)
{
	m_Velocity = Velocity;
}

//============================================================================
// 生成
//============================================================================
CRubble* CRubble::Create(int nType, D3DXVECTOR3 Pos, D3DXVECTOR3 Velocity)
{
	CRubble* pRubble = DBG_NEW CRubble{};

	// 生成失敗
	if (!pRubble)
	{
		assert(false);
	}

	// タイプを設定
	pRubble->SetType(CObject::TYPE::NONE);

	// 初期設定
	pRubble->Init();

	// 座標の設定
	pRubble->SetPos(Pos);

	// 加速度を設定
	pRubble->SetVelocity(Velocity);

	// モデル用ポインタ
	CModel_X_Manager::MODEL* Model{ nullptr };
	
	// モデルを取得
	switch (rand() % 2)
	{
	case 0:

		if (nType == 0)
		{
			Model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::RUBBLE_00);
		}
		else
		{
			Model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::RUBBLE_BIG_00);
		}

		break;

	case 1:

		if (nType == 0)
		{
			Model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::RUBBLE_01);
		}
		else
		{
			Model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::RUBBLE_BIG_01);
		}

		break;

	default:

		if (nType == 0)
		{
			Model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::RUBBLE_00);
		}
		else
		{
			Model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::RUBBLE_BIG_00);
		}

		break;
	}

	// モデルを設定
	pRubble->BindModel(Model);

	// サイズを設定
	pRubble->SetSize(Model->size);

	// 描画される前に一度更新しておく
	pRubble->Update();

	return pRubble;
}

//============================================================================
// 消滅するかチェック
//============================================================================
void CRubble::CheckDisappear() 
{
	// バリアの最も低い座標を下回ったら
	if (GetPos().y < CBarrier_Manager::GetCurrentMinPosY())
	{
		// 破棄
		SetRelease();
	}
}