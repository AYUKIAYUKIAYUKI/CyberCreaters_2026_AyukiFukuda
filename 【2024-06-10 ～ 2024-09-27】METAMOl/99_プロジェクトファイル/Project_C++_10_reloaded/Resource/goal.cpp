//============================================================================
// 
// ゴール [goal.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "goal.h"
#include "utility.h"

// スクリーンテクスチャ取得用
#include "renderer.h"

// カメラ取得用
#include "manager.h"

// チュートリアル情報取得用
#include "game_manager.h"

// プレイヤー取得用
#include "player.h"
#include "player_state.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CGoal::CGoal() :
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
CGoal::~CGoal()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CGoal::Init()
{
	// 目標座標を設定
	m_PosTarget = m_ActualPos;
	m_PosTarget.z = 0.0f;

	// 目標縮尺を設定
	m_fScaleTarget = 1.0f;

	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CGoal::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CGoal::Update()
{
	// プレイヤータグのオブジェクトを取得
	CObject* pObj{ CObject::FindObject(CObject::TYPE::PLAYER) };

	// オブジェクトを取得出来たら
	if (pObj)
	{
		// プレイヤーへダウンキャスト
		CPlayer* pPlayer{ CUtility::GetInstance()->DownCast<CPlayer, CObject>(pObj) };

		// プレイヤーがゴール状態なら
		if (typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateGoal))
		{
			// カメラの間距離をズームイン
			CManager::GetCamera()->SetDistance(CUtility::GetInstance()->AdjustToTarget(CManager::GetCamera()->GetDistance(), CCamera::DEFUALT_DISTANCE * 0.5f, 0.02f));
		
			// ゴールシンボルが上昇していく
			//m_ActualPos.y += 0.5f;

			// プレイヤーの座標をテレビに吸い寄せる
			pPlayer->SetPos(CUtility::GetInstance()->AdjustToTarget(pPlayer->GetPos(), GetPos(), 0.1f));
		}
		else
		{
			if (CGameManager::GetInstance()->GetEndTutorial())
			{
				// カメラの間距離をアウト
				CManager::GetCamera()->SetDistance(CUtility::GetInstance()->AdjustToTarget(CManager::GetCamera()->GetDistance(), CCamera::DEFUALT_DISTANCE, 0.05f));
			}
			else
			{
				// チュートリアルのときだけ寄せる
				CManager::GetCamera()->SetDistance(CUtility::GetInstance()->AdjustToTarget(CManager::GetCamera()->GetDistance(), CCamera::DEFUALT_DISTANCE * 0.75f, 0.05f));
			}
		}
	}

	// 正面を向く
	m_RotTarget = {
		0.0f,
		0.0f,
		CUtility::GetInstance()->GetRandomValue<float>() * 0.005f };

	// 上下する
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
void CGoal::Draw()
{
	// 基底クラスの描画
	CObject_X::Draw();
}

//============================================================================
// 実座標の取得
//============================================================================
D3DXVECTOR3 CGoal::GetActualPos()
{
	return m_ActualPos;
}

//============================================================================
// 実座標の設定
//============================================================================
void CGoal::SetActualPos(D3DXVECTOR3 Pos)
{
	m_ActualPos = Pos;
}

//============================================================================
// 生成
//============================================================================
CGoal* CGoal::Create(D3DXVECTOR3 Pos)
{
	// インスタンスを生成
	CGoal* pGoal{ DBG_NEW CGoal };

	if (pGoal == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pGoal->SetType(TYPE::GOAL);

	// 実座標の設定 (先行)
	pGoal->SetActualPos(Pos);

	// 基底クラスの初期設定
	pGoal->Init();

	// 位置の設定
	pGoal->SetPos(Pos);

	// モデルを取得
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::GOAL) };

	// モデルを設定
	pGoal->BindModel(Model);

	// サイズを設定
	pGoal->SetSize(D3DXVECTOR3{ 10.0f, 10.0f, 0.0f });

	// ゴールシンボルのモニター画面にテクスチャを設定
	//Model->ppTex[0] = CRenderer::GetInstance()->GetTexture();

	// 描画される前に一度更新しておく
	pGoal->Update();

	return pGoal;
}