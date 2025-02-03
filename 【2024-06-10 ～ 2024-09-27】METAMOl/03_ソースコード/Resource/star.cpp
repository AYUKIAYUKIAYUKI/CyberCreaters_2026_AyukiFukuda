//============================================================================
// 
// 星エフェクト [star.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "star.h"
#include "utility.h"

// デバイス取得用
#include "renderer.h"

//============================================================================
// コンストラクタ
//============================================================================
CStar::CStar() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },	// 描画優先度を指定
	m_velocity{ 0.0f, 0.0f, 0.0f }					// 加速度
{

}

//============================================================================
// デストラクタ
//============================================================================
CStar::~CStar()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CStar::Init()
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
void CStar::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CStar::Update()
{
	// 基底クラスの更新処理
	CObject_X::Update();

	// 回転
	//auto rot{ GetRot() };
	//rot = m_velocity * 0.1f;
	//SetRot(rot);

	// 移動
	D3DXVECTOR3 pos = GetPos();
	pos += m_velocity;
	m_velocity.x += CUtility::GetInstance()->GetRandomValue<float>() * 0.01f;
	m_velocity.y += CUtility::GetInstance()->GetRandomValue<float>() * 0.01f;
	SetPos(pos);

	// 加速度を減少
	m_velocity *= 0.5f;

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
void CStar::Draw()
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
D3DXVECTOR3& CStar::GetVelocity()
{
	return m_velocity;
}

//============================================================================
// 加速度を設定
//============================================================================
void CStar::SetVelocity(D3DXVECTOR3 velocity)
{
	m_velocity = velocity;
}

//============================================================================
// 生成
//============================================================================
CStar* CStar::Create(D3DXVECTOR3&& pos, D3DXVECTOR3 velocity)
{
	CStar* pStar = DBG_NEW CStar{};

	// 生成失敗
	if (!pStar)
	{
		assert(false);
	}

	// タイプを設定
	pStar->SetType(CObject::TYPE::NONE);

	// 初期設定
	pStar->Init();

	// 座標の設定
	pStar->SetPos(pos);

	// 向きの設定
	switch (rand() % 4)
	{
	case 0:
		pStar->SetRot(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });
		break;

	case 1:
		pStar->SetRot(D3DXVECTOR3{ 0.0f, 0.0f, D3DX_PI * 0.5f });
		break;

	case 2:
		pStar->SetRot(D3DXVECTOR3{ 0.0f, 0.0f, D3DX_PI });
		break;

	case 3:
		pStar->SetRot(D3DXVECTOR3{ 0.0f, 0.0f, D3DX_PI * -0.5f });
		break;

	default:
		pStar->SetRot(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });
		break;
	}

	// 加速度を設定
	pStar->SetVelocity(velocity);

	// モデルを取得
	CModel_X_Manager::MODEL* model{ nullptr };

	switch (rand() % 2)
	{
	case 0:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::STAR00);
		break;

	case 1:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::STAR01);
		break;

	default:
		model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::STAR00);
		break;
	}

	// モデルを設定
	pStar->BindModel(model);

	// サイズを設定
	pStar->SetSize(model->size);

	// 描画される前に一度更新しておく
	pStar->Update();

	return pStar;
}