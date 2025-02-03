//=============================================================================
//
// リミットタイム [limit_timer.cpp]
// Author : 福田歩希
//
//=============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "limit_timer.h"
#include "utility.h"

// デバッグ表示用
#include "renderer.h"

// テクスチャ取得用
#include "texture_manager.h"

// フェーズ切り替え用
#include "fakescreen.h"

// プレイヤーの状態取得用
#include "record_dest.h"
#include "player.h"
#include "player_state.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CLimit_Timer::CLimit_Timer() :
	CObject_UI{ static_cast<int>(LAYER::UI) },
	m_nCntFrame{ 0 },
	m_nTimer{ 30 },
	m_pText{ nullptr }
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 数字情報のポインタを初期化
		m_apNumber[nCntNum] = nullptr;

		// 数字を生成
		m_apNumber[nCntNum] = CNumber::Create();

		// 新しい座標を作成
		D3DXVECTOR3 NewPos{ SCREEN_WIDTH * 0.6f, 0.0f, 0.0f };

		// 初期座標の設定
		m_apNumber[nCntNum]->SetPos(NewPos);
		m_apNumber[nCntNum]->SetPosTarget(NewPos);

		// 初期向きの設定
		//m_apNumber[nCntNum]->SetRot({ 0.0f, 0.0f, D3DX_PI * 2.0f });

		// 数字の出現予約
		m_apNumber[nCntNum]->SetAppear(true);
	}

	// 出現予約
	SetAppear(true);
}

//============================================================================
// デストラクタ
//============================================================================
CLimit_Timer::~CLimit_Timer()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CLimit_Timer::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CLimit_Timer::Uninit()
{
	// 基底クラスの終了処理
	CObject_UI::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CLimit_Timer::Update()
{
	// 時間減少
	Decrement();

	// 目標座標へ
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), GetPosTarget(), 0.05f));

	// 基底クラスの更新
	CObject_UI::Update();

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	// 数字のみ
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 目標座標へ
		m_apNumber[nCntNum]->SetPos(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetPos(), m_apNumber[nCntNum]->GetPosTarget(), 0.075f));

		// 目標向きへ
		m_apNumber[nCntNum]->SetRot(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetRot(), m_apNumber[nCntNum]->GetRotTarget(), 0.075f));

		// 目標サイズへ
		m_apNumber[nCntNum]->SetSize(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetSize(), m_apNumber[nCntNum]->GetSizeTarget(), 0.05f));
	}

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	// 消去予定なら付属品も消去予定に
	if (GetDisappear())
	{
		m_pText->SetDisappear(true);

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// 目標座標へ
			m_apNumber[nCntNum]->SetDisappear(true);
		}
	}
}

//============================================================================
// 描画処理
//============================================================================
void CLimit_Timer::Draw()
{
	// 基底クラスの描画処理
	CObject_UI::Draw();
}

//============================================================================
// タイム情報を取得
//============================================================================
int CLimit_Timer::GetTimer()
{
	return m_nTimer;
}

//============================================================================
// 時間減少
//============================================================================
void CLimit_Timer::Decrement()
{
	// チャレンジ中に動作
	if (CGameManager::GetInstance()->GetPhase() == CGameManager::PHASE::C_INGAME)
	{
		if (!m_pText)
		{
			// テキストが生成されていなければ生成
			m_pText = CText::Create(CTexture_Manager::TYPE::LIMITTIME);

			// 新しい座標を作成
			D3DXVECTOR3 NewPos{ SCREEN_WIDTH * 0.6f, 0.0f, 0.0f };

			// 初期座標の設定
			m_pText->SetPos(NewPos);
			m_pText->SetPosTarget(NewPos);

			// 初期サイズを設定
			m_pText->SetSizeTarget({ 130.0f, 30.0f, 0.0f });
		}

		// 全体の目標座標を設定し、震わす
		SetPosTarget({ SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.15f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f, });

		// 数字用の目標座標のコピーを作成
		D3DXVECTOR3 CopyPosTarget{ GetPosTarget() };

		// 共通横サイズを設定
		float fSizeX{ 42.5f };

		// 数字を並べる
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// 中心座標から、相対的な先頭の位置を設定
			CopyPosTarget.x = GetPosTarget().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f);

			// 先頭座標から数字が並ぶように調整
			CopyPosTarget.x += -fSizeX * nCntNum;
			m_apNumber[nCntNum]->SetPosTarget(CopyPosTarget);

			// 数字の目標サイズを設定
			m_apNumber[nCntNum]->SetSizeTarget({ fSizeX, 30.0f, 0.0f });
		}

		// テキスト用の目標座標のコピーを作成
		CopyPosTarget = GetPosTarget();

		// テキストを数字の横に付ける
		CopyPosTarget.x += -195.0f;
		m_pText->SetPosTarget(CopyPosTarget);

		// プレイヤーを検索
		CObject* pFind = CObject::FindObject(CObject::TYPE::PLAYER);

		// プレイヤーが見つかれば
		if (pFind)
		{
			CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(pFind);

			if (m_nTimer > 0)
			{
				// ゴール状態でなければ
				if (typeid(*pPlayer->GetStateManager()->GetState()) != typeid(CPlayerStateGoal))
				{
					// フレームカウント
					m_nCntFrame++;

					if (m_nCntFrame > 60)
					{
						// カウントリセット
						m_nCntFrame = 0;

						// タイマー減少
						m_nTimer--;
					}
				}
			}
			else
			{ // 時間切れで

				if (!GetDisappear())
				{ // リミットタイムに削除フラグが出る前なら

					// 削除フラグを出しておく
					SetDisappear(true);

					// ウェーブを強制終了
					CFakeScreen::GetInstance()->StopWave();

					// チャレンジ終了フェーズへ移行
					CFakeScreen::GetInstance()->SetWave(CGameManager::PHASE::C_FINISH);

					// 強制ミス状態へ
					pPlayer->GetStateManager()->SetPendingState(CPlayerState::STATE::MISS);

					// タイムアップ判定を出す
					CRecord_Dest* pRecord{ CUtility::GetInstance()->DownCast<CRecord_Dest, CObject>(CObject::FindObject(CObject::TYPE::RECORD)) };
					pRecord->SetTimeUp();
				}
			}
		}

		// カウント数のコピー
		int nCopy{ m_nTimer };

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// 数字を設定
			m_apNumber[nCntNum]->SetNumber(nCopy % 10);

			// 桁を減らす
			nCopy /= 10;
		}
	}
}

//============================================================================
// 時間リセット
//============================================================================
void CLimit_Timer::TimerReset()
{
	// タイムを検索
	CObject* pObj = CObject::FindObject(CObject::TYPE::TIMER);
	CLimit_Timer* pTimer = CUtility::GetInstance()->DownCast<CLimit_Timer, CObject>(pObj);

	// 時間をリセット
	pTimer->m_nCntFrame = 0;
	pTimer->m_nTimer = 0;
}

//============================================================================
// 生成
//============================================================================
CLimit_Timer* CLimit_Timer::Create()
{
	// インスタンスを生成
	CLimit_Timer* pLimit_Timer = DBG_NEW CLimit_Timer;

	if (pLimit_Timer == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pLimit_Timer->SetType(TYPE::TIMER);

	// 基底クラスの初期設定
	pLimit_Timer->Init();

	// 新しい座標を設定
	pLimit_Timer->SetPos({ 0.0f, 0.0f, 0.0f });

	// サイズの設定
	pLimit_Timer->SetSize({ 0.0f, 0.0f, 0.0f });

	return pLimit_Timer;
}

//============================================================================
// 出現
//============================================================================
void CLimit_Timer::Appear()
{
	if (!GetAppear())
	{
		return;
	}

	// アルファ値を取得
	float& fAlpha{ GetAlpha() };

	// 徐々に登場
	fAlpha += 0.025f;

	// 最大値に到達で固定
	if (fAlpha > 1.0f)
	{
		fAlpha = 1.0f;

		// 出現終了
		SetAppear(false);
	}
}

//============================================================================
// 消滅
//============================================================================
void CLimit_Timer::Disappear()
{
	if (!GetDisappear())
	{
		return;
	}

	// アルファ値を取得
	float& fAlpha{ GetAlpha() };

	// 徐々に消滅
	fAlpha += -0.05f;

	// 最低値に到達で固定
	if (fAlpha < 0.0f)
	{
		fAlpha = 0.0f;

		// 出現終了
		SetDisappear(false);

		// 破棄予約
		SetRelease();
	}
}