//============================================================================
// 
// プレイヤー [player.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "player.h"
#include "player_state.h"
#include "utility.h"
#include "sound.h"

// モード情報用
#include "manager.h"

// フェーズ情報用
#include "game_manager.h"

// デバッグ表示用
#include "renderer.h"

// オブジェクト情報用 
#include "achievement.h"
#include "barrier.h"
#include "barrier_anchor.h"
#include "block.h"
#include "block_destructible.h"
#include "block_destructible_big.h"
#include "block_spikes.h"
#include "block_spikes_move.h"
#include "enemy.h"
#include "fakescreen.h"
#include "goal.h"
#include "impact.h"
#include "smoke.h"
#include "start.h"

// 破壊記録用
#include "record_dest.h"

//============================================================================
// コンストラクタ
//============================================================================
CPlayer::CPlayer() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },	// 描画優先度を指定
	m_pStateManager{ nullptr },						// 状態マネージャーの初期化
	m_velocity{ 0.0f, 0.0f, 0.0f },					// 加速度の初期化
	m_velocityTarget{ 0.0f, 0.0f, 0.0f },			// 目標加速度の初期化
	m_posTarget{ 0.0f, 0.0f, 0.0f },				// 目標位置の初期化
	m_rotTarget{ 0.0f, 0.0f, 0.0f },				// 目標向きの初期化
	m_fAngleFlying{ 0.0f }							// 飛行向きの初期化
{
	
}

//============================================================================
// デストラクタ
//============================================================================
CPlayer::~CPlayer()
{
	m_pStateManager = nullptr;					// 状態マネージャーの初期化
	m_velocity = { 0.0f, 0.0f, 0.0f };			// 加速度の初期化
	m_velocityTarget = { 0.0f, 0.0f, 0.0f };	// 目標加速度の初期化
	m_posTarget = { 0.0f, 0.0f, 0.0f };			// 目標位置の初期化
	m_rotTarget = { 0.0f, 0.0f, 0.0f };			// 目標向きの初期化
	m_fAngleFlying = 0.0f;						// 飛行向きの初期化
	m_fDefaultScale = 0.0f;						// 規定縮尺の初期化
}

//============================================================================
// 初期設定
//============================================================================
HRESULT CPlayer::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	if (m_pStateManager == nullptr)
	{
		// 状態マネージャーの生成
		m_pStateManager = DBG_NEW CPlayerStateManager;

		// 初期設定
		m_pStateManager->Init(this);
	}

	// スタート地点を検索
	CObject* pObject = CObject::FindObject(CObject::TYPE::START);
	CStart* pStart = CUtility::GetInstance()->DownCast<CStart, CObject>(pObject);

	// 初期座標をスタート地点に
	SetPos(pStart->GetPos());

	// モードに応じてサイズ設定
	if (CManager::GetScene()->GetMode() == CScene::MODE::GAME)
	{
		SetSize(D3DXVECTOR3{ 10.0f, 10.0f, 10.0f });
		m_fDefaultScale = 1.0f;
	}
	else if (CManager::GetScene()->GetMode() == CScene::MODE::CHALLENGE)
	{
		SetSize(D3DXVECTOR3{ 15.0f, 15.0f, 15.0f });
		m_fDefaultScale = 1.5f;
	}

	// 初期縮尺を設定
	SetScale(0.0f);

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CPlayer::Uninit()
{
	// 状態マネージャーの破棄
	if (m_pStateManager != nullptr)
	{
		// 終了処理
		m_pStateManager->Uninit();
	
		// メモリを解放
		delete m_pStateManager;

		// ポインタを初期化
		m_pStateManager = nullptr;
	}

	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CPlayer::Update()
{
	// 現在座標をコピーし、以降このコピーを目標座標として変更を加えていく
	m_posTarget = CObject_X::GetPos();

	// 状態オブジェクトが生成されていれば
	if (m_pStateManager->GetState() != nullptr)
	{
		// 状態の更新
		m_pStateManager->GetState()->Update();

		// 状態の変更を確認する (メモリ解放を含む処理のため、更新の後に別途行う)
		m_pStateManager->CheckStateChange();
	}

	// 目標座標を反映
	SetPos(m_posTarget);

#ifdef _DEBUG
	// 座標をデバッグ表示
	CRenderer::GetInstance()->SetDebugString("【プレイヤー座標】");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(6) << "X:" << GetPos().x << "\nY:" << GetPos().y;
	CRenderer::GetInstance()->SetDebugString(oss.str().c_str());

	CRenderer::GetInstance()->SetDebugString("加速度X : " + std::to_string(m_velocity.x));
	CRenderer::GetInstance()->SetDebugString("加速度Y : " + std::to_string(m_velocity.y));
	CRenderer::GetInstance()->SetDebugString("向き : x " + std::to_string(GetRot().x) + " : y " + std::to_string(GetRot().y) + " : z " + std::to_string(GetRot().z));
	CRenderer::GetInstance()->SetDebugString("目標向き : x " + std::to_string(m_rotTarget.x) + " : y " + std::to_string(m_rotTarget.y) + " : z " + std::to_string(m_rotTarget.z));
	CRenderer::GetInstance()->SetDebugString("現在の飛行方向 : " + std::to_string(m_fAngleFlying));
#endif	// _DEBUG

	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CPlayer::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 当たり判定
//============================================================================
bool CPlayer::Collision()
{
	// 衝突検出用
	bool bDetected{ false };

	// オブジェクト取得用ポインタ
	CObject** pObject{ nullptr };

	// バリアタグを取得
	pObject = CObject::FindAllObject(CObject::TYPE::BARRIER);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// バリアクラスへダウンキャスト
		CBarrier* pBarrier = CUtility::GetInstance()->DownCast<CBarrier, CObject>(pObject[nCntObj]);

		// バリアと衝突する場合
		if (CUtility::GetInstance()->OnlyCube(pBarrier->GetPos(), pBarrier->GetSize(), m_posTarget, GetSize()))
		{
			// ミス状態に移行
			m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);

			// 衝突判定を出す
			bDetected = 1;

			// 死亡音
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}
	}

	// バリアアンカータグを取得
	pObject = CObject::FindAllObject(CObject::TYPE::BARRIER_ANCHOR);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// バリアアンカークラスへダウンキャスト
		CBarrier_Anchor* pAnchor = CUtility::GetInstance()->DownCast<CBarrier_Anchor, CObject>(pObject[nCntObj]);

		// バリアアンカーと衝突する場合
		if (CUtility::GetInstance()->OnlyCube(pAnchor->GetPos(), pAnchor->GetSize(), m_posTarget, GetSize()))
		{
			// ミス状態に移行
			m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);

			// 衝突判定を出す
			bDetected = 1;

			// 死亡音
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}
	}

	// ブロックタグを取得
	pObject = CObject::FindAllObject(CObject::TYPE::BLOCK);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// ブロックタグの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// ブロッククラスへダウンキャスト
		CBlock* pBlock = CUtility::GetInstance()->DownCast<CBlock, CObject>(pObject[nCntObj]);

		// ブロックと衝突する場合
		if (CUtility::GetInstance()->OnlyCube(pBlock->GetPos(), pBlock->GetSize(), m_posTarget, GetSize()))
		{
			// 飛行・突進・停止状態の場合のみ
			if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateFlying) ||
				typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateRushing) ||
				typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateStopping))
			{
				for (int i = 0; i < 3; i++)
				{
					// ランダムな加速度を作成
					D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, fabsf(CUtility::GetInstance()->GetRandomValue<float>()) * 0.01f, 0.0f };

					// 新しい加速度を作成
					D3DXVECTOR3 NewVelocity{ m_velocity * 0.25f };
					NewVelocity.z = -2.0f;

					// 衝撃を生成
					CImpact* pImpact{ CImpact::Create(GetPos() + (m_velocity * 3.0f) + (RandomVelocity * 3.0f),	// 座標
						NewVelocity) };																			// 加速度
				
					// 大きめに
					pImpact->SetScale(1.25f);
				}
			}

			// 押し出し処理
			CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pBlock->GetPos(), pBlock->GetSize());

			// 衝突判定を出す
			bDetected = 1;
		}
	}

	// 可壊タグを取得
	pObject = CObject::FindAllObject(CObject::TYPE::DESTRUCTIBLE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// 可壊タグの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// 可壊ブロックへダウンキャスト
		CBlockDestructible* pDestructible = CUtility::GetInstance()->DownCast<CBlockDestructible, CObject>(pObject[nCntObj]);

		// 可壊ブロックと衝突する場合
		if (CUtility::GetInstance()->OnlyCube(pDestructible->GetPos(), pDestructible->GetSize(), m_posTarget, GetSize()))
		{
			// 突進状態の場合のみ
			if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateRushing) ||
				CManager::GetScene()->GetMode() == CScene::MODE::CHALLENGE && typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateBeginning) ||
				CManager::GetScene()->GetMode() == CScene::MODE::CHALLENGE && typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateCharging) ||
				CManager::GetScene()->GetMode() == CScene::MODE::CHALLENGE && typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateStopping))
			{
				// 可壊ブロックを破棄
				pDestructible->SetRelease();

				if (CManager::GetScene()->GetMode() == CScene::MODE::CHALLENGE)
				{
					// 破壊記録を加算
					CRecord_Dest::AddDest();
				}

				// ランダムな加速度を生成
				D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

				// 煙を生成
				CSmoke::Create(
					pDestructible->GetPos() + RandomVelocity * 5.0f,	// 座標
					m_velocity * -0.5f);								// 加速度

				// 破壊音
				CSound::GetInstance()->Play(CSound::LABEL::BREAK);
			}
			else
			{
				// 衝突前の加速度を保持
				D3DXVECTOR3 OldVelocity{ m_velocity };

				// 押し出し処理
				CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pDestructible->GetPos(), pDestructible->GetSize());

				// 飛行状態の場合のみ
				if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateFlying) ||
					typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateStopping))
				{
					// 可壊ブロックを破棄
					pDestructible->SetRelease();

					if (CManager::GetScene()->GetMode() == CScene::MODE::CHALLENGE)
					{
						// 破壊記録を加算
						CRecord_Dest::AddDest();
					}

					// エフェクトを作成
					for (int i = 0; i < 3; i++)
					{
						// ランダムな加速度を生成
						D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

						// 煙を生成
						CSmoke* pSmoke{ CSmoke::Create(
							pDestructible->GetPos() + RandomVelocity * 2.0f,	// 座標
							OldVelocity * -0.5f) };								// 加速度

						// 小さめに
						pSmoke->SetScale(0.75f);
					}

					// 破壊音
					CSound::GetInstance()->Play(CSound::LABEL::BREAK);
				}

				// 衝突判定を出す
				bDetected = 1;
			}
		}
	}

	// 可壊でかタグを取得
	pObject = CObject::FindAllObject(CObject::TYPE::DEST_BIG);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// 可壊でかタグの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// 可壊でかブロックへダウンキャスト
		CBlockDestructibleBig* pDest_Big = CUtility::GetInstance()->DownCast<CBlockDestructibleBig, CObject>(pObject[nCntObj]);

		// 可壊でかブロックと衝突する場合
		if (CUtility::GetInstance()->OnlyCube(pDest_Big->GetPos(), pDest_Big->GetSize(), m_posTarget, GetSize()))
		{
			// 突進状態の場合のみ
			if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateRushing))
			{
				// ダメージ処理
				if (pDest_Big->Damage(-1))
				{
					// エフェクトを生成
					for (int i = 0; i < 5; i++)
					{
						// ランダムな加速度を作成
						D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, fabsf(CUtility::GetInstance()->GetRandomValue<float>()) * 0.01f, 0.0f };

						// 新しい加速度を作成
						D3DXVECTOR3 NewVelocity{ m_velocity * 0.25f };
						NewVelocity.z = -2.0f;

						// 衝撃を生成
						CImpact* pImpact{ CImpact::Create(GetPos() + (m_velocity * 3.0f) + (RandomVelocity * 3.0f),	// 座標
							NewVelocity) };																			// 加速度

						// 大きめに
						pImpact->SetScale(1.5f);
					}

					// 破壊仕切れない場合、押し出し処理
					CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pDest_Big->GetPos(), pDest_Big->GetSize());
				
					// 衝突判定を出す
					bDetected = 1;
				}
				else
				{
					if (CManager::GetScene()->GetMode() == CScene::MODE::CHALLENGE)
					{
						// 破壊記録を加算
						CRecord_Dest::AddDest();
					}

					// エフェクトを作成
					for (int i = 0; i < 10; i++)
					{
						// ランダムな加速度を生成
						D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), 0.0f };

						// 煙を生成
						CSmoke* pSmoke{ CSmoke::Create(
							pDest_Big->GetPos() + RandomVelocity * 0.1f,	// 座標
							m_velocity * -1.0f) };							// 加速度
					
						// 大きく
						pSmoke->SetScale(1.2f);
					}
				}

				// 破壊音
				CSound::GetInstance()->Play(CSound::LABEL::BREAK);
			}
			else
			{
				// 衝突前の加速度を保持
				D3DXVECTOR3 OldVelocity{ m_velocity };

				// 押し出し処理
				CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pDest_Big->GetPos(), pDest_Big->GetSize());

				// 飛行・停止状態の場合のみ
				if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateFlying) ||
					typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateStopping))
				{
					// ダメージ処理
					if (!pDest_Big->Damage(-1))
					{ // 破壊出来たら

						if (CManager::GetScene()->GetMode() == CScene::MODE::CHALLENGE)
						{
							// 破壊記録を加算
							CRecord_Dest::AddDest();
						}

						// エフェクトを作成
						for (int i = 0; i < 5; i++)
						{
							// ランダムな加速度を生成
							D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>(), CUtility::GetInstance()->GetRandomValue<float>(), 0.0f };
						
							// 煙を生成
							CSmoke* pSmoke{ CSmoke::Create(
								pDest_Big->GetPos() + RandomVelocity * 0.1f,	// 座標
								OldVelocity * -1.0f) };							// 加速度

							// 大きく
							pSmoke->SetScale(1.2f);
						}
					}
					else
					{
						// エフェクトを生成
						for (int i = 0; i < 5; i++)
						{
							// ランダムな加速度を作成
							D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, fabsf(CUtility::GetInstance()->GetRandomValue<float>()) * 0.01f, 0.0f };

							// 新しい加速度を作成
							D3DXVECTOR3 NewVelocity{ m_velocity * 0.25f };
							NewVelocity.z = -2.0f;

							// 衝撃を生成
							CImpact* pImpact{ CImpact::Create(GetPos() + (m_velocity * 3.0f) + (RandomVelocity * 3.0f),	// 座標
								NewVelocity) };																			// 加速度

							// 大きめに
							pImpact->SetScale(1.5f);
						}
					}

					// 破壊音
					CSound::GetInstance()->Play(CSound::LABEL::BREAK);
				}

				// 衝突判定を出す
				bDetected = 1;
			}
		}
	}

	// とげタグを取得
	pObject = CObject::FindAllObject(CObject::TYPE::SPIKES);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// とげタグの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// とげブロックへダウンキャスト
		CBlockSpikes* pBlockSpikes = CUtility::GetInstance()->DownCast<CBlockSpikes, CObject>(pObject[nCntObj]);

		// とげブロックと衝突する場合
		if (CUtility::GetInstance()->OnlyCube(pBlockSpikes->GetPos(), pBlockSpikes->GetSize(), m_posTarget, GetSize()))
		{
			// ミス状態に移行
			m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);

			// 衝突判定を出す
			bDetected = 1;

			// 死亡音
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}
	}

	// とげ移動タグを取得
	pObject = CObject::FindAllObject(CObject::TYPE::SPIKES_MOVE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// とげ移動タグの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// とげ移動ブロックへダウンキャスト
		CBlockSpikesMove* pBlockSpikesMove = CUtility::GetInstance()->DownCast<CBlockSpikesMove, CObject>(pObject[nCntObj]);

		// とげ移動ブロックと衝突する場合
		if (CUtility::GetInstance()->OnlyCube(pBlockSpikesMove->GetPos(), pBlockSpikesMove->GetSize(), m_posTarget, GetSize()))
		{
			// ミス状態に移行
			m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);

			// 衝突判定を出す
			bDetected = 1;

			// 死亡音
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}
	}
	
	// エネミータグを取得
	pObject = CObject::FindAllObject(CObject::TYPE::ENEMY);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// エネミータグの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// エネミーへダウンキャスト
		CEnemy* pEnemy = CUtility::GetInstance()->DownCast<CEnemy, CObject>(pObject[nCntObj]);

		// エネミーと衝突する場合
		if (CUtility::GetInstance()->OnlyCube(pEnemy->GetPos(), pEnemy->GetSize(), m_posTarget, GetSize()))
		{
			// 突進状態の場合のみ
			if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateRushing))
			{
				// ランダムな加速度を生成
				D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

				// 煙を生成
				CSmoke::Create(
					pEnemy->GetPos() + RandomVelocity * 5.0f,	// 座標
					m_velocity * -0.5f);						// 加速度

				// エネミーを破棄
				pEnemy->SetRelease();
			}
			else
			{
				if (typeid(*m_pStateManager->GetState()) == typeid(CPlayerStateFlying))
				{ // 飛行状態の場合

					// この時点での加速度を保持
					D3DXVECTOR3 OldVelocity{ m_velocity };

					// 押し出し処理
					CUtility::GetInstance()->OnlyCube(m_posTarget, m_velocity, GetPos(), GetSize(), pEnemy->GetPos(), pEnemy->GetSize());

					// エフェクトを作成
					for (int i = 0; i < 3; i++)
					{
						// ランダムな加速度を生成
						D3DXVECTOR3 RandomVelocity{ CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, 0.0f };

						// 煙を生成
						CSmoke* pSmoke{ CSmoke::Create(
							pEnemy->GetPos() + RandomVelocity * 2.0f,	// 座標
							OldVelocity * -0.5f) };						// 加速度

						// 小さめに
						pSmoke->SetScale(0.75f);
					}

					// エネミーを破棄
					pEnemy->SetRelease();
				}
				else
				{
					// ミス状態に移行
					m_pStateManager->SetPendingState(CPlayerState::STATE::MISS);
				}

				// 衝突判定を出す
				bDetected = 1;
			}

			// 死亡音
			CSound::GetInstance()->Play(CSound::LABEL::DIE);
		}
	}

	// ミス状態に移行予定であればゴール・アチーブとの接触は認めない
	if (m_pStateManager->GetPendingState() == CPlayerState::STATE::MISS)
	{
		return bDetected;
	}

	// アチーブオブジェクトを取得
	if (CObject::FindObject(CObject::TYPE::ACHIEVE))
	{
		CAchieve* pAchieve = CUtility::GetInstance()->DownCast<CAchieve, CObject>(CObject::FindObject(CObject::TYPE::ACHIEVE));

		// アチーブと衝突する場合
		if (CUtility::GetInstance()->SphereAndCube(pAchieve->GetPos(), pAchieve->GetSize().x, m_posTarget, GetSize()))
		{
			// 破棄予約
			pAchieve->SetRelease();

			// 取得音
			CSound::GetInstance()->Play(CSound::LABEL::GET);
		}
	}

	// ゴールオブジェクトを取得
	CGoal* pGoal = CUtility::GetInstance()->DownCast<CGoal, CObject>(CObject::FindObject(CObject::TYPE::GOAL));

	// ゴールと衝突する場合
	if (CUtility::GetInstance()->SphereAndCube(pGoal->GetActualPos(), pGoal->GetSize().x, m_posTarget, GetSize()))
	{
		// ゴール状態に移行
		m_pStateManager->SetPendingState(CPlayerState::STATE::GOAL);

		// ウェーブを強制終了
		CFakeScreen::GetInstance()->StopWave();

		// 現在のモードを取得
		CScene::MODE Mode{ CManager::GetScene()->GetMode() };

		if (Mode == CScene::MODE::GAME)
		{
			// レベル終了フェーズへ移行
			CFakeScreen::GetInstance()->SetWave(CGameManager::PHASE::FINISH);
		}
		else if (Mode == CScene::MODE::CHALLENGE)
		{
			// チャレンジ終了フェーズへ移行
			CFakeScreen::GetInstance()->SetWave(CGameManager::PHASE::C_FINISH);

			// 記録を書き出す
			CRecord_Dest::ExportRecord();
		}

		// ゴール音
		CSound::GetInstance()->Play(CSound::LABEL::GOAL);
	}

	return bDetected;
}

//============================================================================
// 加速度を取得
//============================================================================
D3DXVECTOR3 CPlayer::GetVelocity()
{
	return m_velocity;
}

//============================================================================
// 加速度を設定
//============================================================================
void CPlayer::SetVelocity(D3DXVECTOR3 velocity)
{
	m_velocity = velocity;
}

//============================================================================
// 目標加速度を取得
//============================================================================
D3DXVECTOR3 CPlayer::GetVelocityTarget()
{
	return m_velocityTarget;
}

//============================================================================
// 目標加速度を設定
//============================================================================
void CPlayer::SetVelocityTarget(D3DXVECTOR3 velocityTarget)
{
	m_velocityTarget = velocityTarget;
}

//============================================================================
// 飛行方向を取得
//============================================================================
float CPlayer::GetAngleFlying()
{
	return m_fAngleFlying;
}

//============================================================================
// 飛行方向を設定
//============================================================================
void CPlayer::SetAngleFlying(float fAngleFlying)
{
	m_fAngleFlying = fAngleFlying;
}

//============================================================================
// 目標位置を取得
//============================================================================
D3DXVECTOR3 CPlayer::GetPosTarget()
{
	return m_posTarget;
}

//============================================================================
// 目標位置を設定
//============================================================================
void CPlayer::SetPosTarget(D3DXVECTOR3 posTarget)
{
	m_posTarget = posTarget;
}

//============================================================================
// 目標向きを取得
//============================================================================
D3DXVECTOR3 CPlayer::GetRotTarget()
{
	return m_rotTarget;
}

//============================================================================
// 目標向きを設定
//============================================================================
void CPlayer::SetRotTarget(D3DXVECTOR3 rotTarget)
{
	m_rotTarget = rotTarget;
}

//============================================================================
// 規定縮尺を取得
//============================================================================
float CPlayer::GetDefScale()
{
	return m_fDefaultScale;
}

//============================================================================
// 状態管理取得
//============================================================================
CPlayerStateManager* CPlayer::GetStateManager()
{
	return m_pStateManager;
}

//============================================================================
// 生成
//============================================================================
CPlayer* CPlayer::Create()
{
	// インスタンスを生成
	CPlayer* pPlayer = DBG_NEW CPlayer;

	if (pPlayer == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pPlayer->SetType(TYPE::PLAYER);

	// 基底クラスの初期設定
	pPlayer->Init();

	// 先行して更新しておく
	pPlayer->Update();

	return pPlayer;
}