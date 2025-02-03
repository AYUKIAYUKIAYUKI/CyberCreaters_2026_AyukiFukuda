//============================================================================
// 
// スタート [start.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "start.h"
#include "utility.h"

// プレイヤー取得用
#include "player.h"
#include "player_state.h"

//============================================================================
// コンストラクタ
//============================================================================
CStart::CStart() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },
	m_ActualPos{ 0.0f, 0.0f, 0.0f },
	m_PosTarget{ 0.0f, 0.0f, 0.0f },
	m_RotTarget{ 0.0f, 0.0f, 0.0f },
	m_fScaleTarget{ 0.0f }
{

}

//============================================================================
// デストラクタ
//============================================================================
CStart::~CStart()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CStart::Init()
{
	// 目標座標を設定
	m_PosTarget = m_ActualPos;
	m_PosTarget.z = 40.0f;

	// 目標縮尺を設定
	m_fScaleTarget = 0.75f;

	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CStart::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CStart::Update()
{
	// プレイヤータグのオブジェクトを取得
	CObject* pObj{ CObject::FindObject(CObject::TYPE::PLAYER) };

	// オブジェクトを取得出来たら
	if (pObj)
	{
		// プレイヤーへダウンキャスト
		CPlayer* pPlayer{ CUtility::GetInstance()->DownCast<CPlayer, CObject>(pObj) };

		// プレイヤーが死亡状態なら
		if (typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateMistook))
		{
			// 激しく移動する
			m_PosTarget.x = m_ActualPos.x + CUtility::GetInstance()->GetRandomValue<float>() * 0.25f;
			m_PosTarget.y = m_ActualPos.y + CUtility::GetInstance()->GetRandomValue<float>() * 0.25f;

			// 座標を手前へ
			D3DXVECTOR3 NewPos{ GetPos() };
			NewPos.z = -40.0f;
			SetPos(NewPos);

			// モデルを拡大
			SetScale(1.5f);
		}
	}

	// 正面を向く
	m_RotTarget = {
		0.0f,
		0.0f,
		CUtility::GetInstance()->GetRandomValue<float>() * 0.005f };

	// 上下する
	m_PosTarget.x = m_ActualPos.x;
	m_PosTarget.y = m_ActualPos.y + CUtility::GetInstance()->GetRandomValue<float>() * 0.1f;

	// 目標向きへ
	SetRot(CUtility::GetInstance()->AdjustToTarget(GetRot(), m_RotTarget, 0.05f));

	// 目標座標へ
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), m_PosTarget, 0.05f));

	// 目標縮尺へ
	SetScale(CUtility::GetInstance()->AdjustToTarget(GetScale(), m_fScaleTarget, 0.035f));

	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CStart::Draw()
{
	// 基底クラスの描画
	CObject_X::Draw();
}

//============================================================================
// 実座標の取得
//============================================================================
D3DXVECTOR3 CStart::GetActualPos()
{
	return m_ActualPos;
}

//============================================================================
// 実座標の設定
//============================================================================
void CStart::SetActualPos(D3DXVECTOR3 Pos)
{
	m_ActualPos = Pos;
}

//============================================================================
// 生成
//============================================================================
CStart* CStart::Create(D3DXVECTOR3 Pos)
{
	// インスタンスを生成
	CStart* pStart{ DBG_NEW CStart };

	if (pStart == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pStart->SetType(TYPE::START);

	// 実座標の設定 (先行)
	pStart->SetActualPos(Pos);

	// 基底クラスの初期設定
	pStart->Init();

	// 座標の設定
	pStart->SetPos(Pos);

	// モデルを取得
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::START) };

	// モデルを設定
	pStart->BindModel(Model);

	// サイズを設定
	pStart->SetSize(Model->size);

	// 描画される前に一度更新しておく
	pStart->Update();

	return pStart;
}