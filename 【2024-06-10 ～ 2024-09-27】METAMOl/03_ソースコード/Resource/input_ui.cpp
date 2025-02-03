//=============================================================================
//
// インプットUI [input_ui.cpp]
// Author : 福田歩希
//
//=============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "input_ui.h"
#include "utility.h"
#include "title.h"

// デバッグ表示用
#include "renderer.h"

// カメラ取得用
#include "manager.h"

// フェーズ取得用
#include "tutorial_manager.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CInput_UI::CInput_UI() :
	CObject_3D{ static_cast<int>(LAYER::BG) },
	m_nType{ 0 },
	m_TexType{ CTexture_Manager::TYPE::CROWN },
	m_nDuration{ 0 },
	m_bAppear{ false },
	m_bDisappear{ false },
	m_posTarget{ 0.0f, 0.0f, 0.0f },
	m_rotTarget{ 0.0f, 0.0f, 0.0f },
	m_sizeTarget{ 0.0f, 0.0f, 0.0f },
	m_colTarget{ 0.0f, 0.0f, 0.0f, 0.0f }
{

}

//============================================================================
// デストラクタ
//============================================================================
CInput_UI::~CInput_UI()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CInput_UI::Init()
{
	if (m_nType == 0)
	{
		// 座標設定
		SetPos({ -3.0f, -10.0f + -50.0f, -10.0f });
		SetPosTarget({ -3.0f, -10.0f, -10.0f });

		// サイズ設定
		SetSize({ 10.0f, 10.0f, 0.0f });
		SetSizeTarget({ 10.0f, 10.0f, 0.0f });
	}
	else if (m_nType == 1)
	{
		// 座標設定
		SetPos({ -16.5f, 3.0f + 50.0f, -10.0f });
		SetPosTarget({ -16.5f, 3.0f, -10.0f });

		// サイズ設定
		SetSize({ 5.5f, 5.5f, 0.0f });
		SetSizeTarget({ 5.5f, 5.5f, 0.0f });
	}
	else if (m_nType == 2)
	{
		// 座標設定
		SetPos({ 11.0f + 50.0f, 1.0f, -10.0f });
		SetPosTarget({ 11.f, 1.0f, -10.0f });

		// サイズ設定
		SetSize({ 5.5f, 5.5f, 0.0f });
		SetSizeTarget({ 5.5f, 5.5f, 0.0f });
	}
	else if (m_nType == 3)
	{
		// 座標設定
		SetPos({ -37.5f, 3.0f, -10.0f });
		SetPosTarget({ -17.5f, 3.0f, -10.0f });

		// サイズ設定
		SetSize({ 0.0f, 0.0f, 0.0f });
		SetSizeTarget({ 5.5f, 5.5f, 0.0f });
	}

	// 基底クラスの初期設定
	HRESULT hr = CObject_3D::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CInput_UI::Uninit()
{
	// 基底クラスの終了処理
	CObject_3D::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CInput_UI::Update()
{
	if (!m_bDisappear)
	{
		// 識別に応じて更新を変更
		if (m_nType == 0)
		{
			UpdateCNT();
		}
		else if (m_nType == 1)
		{
			UpdateBoard();
		}
		else if (m_nType == 2)
		{
			UpdateSpeech();
		}
		else if (m_nType == 3)
		{
			// 新しい情報を作成
			D3DXVECTOR3 NewPosTarget{ GetPosTarget() };

			// 増加量
			static float fAdder{ 0.0035f };

			// 少し動く
			NewPosTarget.y += fAdder;

			if (NewPosTarget.y >= 3.0f + 0.3f || NewPosTarget.y <= 3.0f + -0.3f)
			{
				fAdder *= -1.0f;
			}

			// 座標を反映
			SetPosTarget(NewPosTarget);
		}
	}

	// 出現
	Appear();

	// 消滅
	Disappear();

	// 目標座標へ
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), m_posTarget, 0.1f));

	// 目標向きへ
	SetRot(CUtility::GetInstance()->AdjustToTarget(GetRot(), m_rotTarget, 0.1f));

	// 目標サイズへ
	SetSize(CUtility::GetInstance()->AdjustToTarget(GetSize(), m_sizeTarget, 0.1f));

#ifdef _DEBUG

	// 向きを表示
	CRenderer::GetInstance()->SetDebugString(std::to_string(GetRot().z));

#endif // _DEBUG

	// 基底クラスの更新
	CObject_3D::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CInput_UI::Draw()
{
	auto pDev{ CRenderer::GetInstance()->GetDeviece() };

	// 深度テストの比較方法の変更
	pDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// 深度バッファに描画しない
	pDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ライト反映を無効にする
	pDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 基底クラスの描画処理
	CObject_3D::Draw();

	// ライト反映を有効にする
	pDev->SetRenderState(D3DRS_LIGHTING, TRUE);

	// 深度テストの比較方法の変更
	pDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// 深度バッファに書き込む
	pDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//============================================================================
// 出現設定
//============================================================================
void CInput_UI::SetAppear()
{
	m_bAppear = true;
}

//============================================================================
// 消滅設定
//============================================================================
void CInput_UI::SetDisappear()
{
	m_bDisappear = true;
}

//============================================================================
// 目標座標取得
//============================================================================
D3DXVECTOR3 CInput_UI::GetPosTarget()
{
	return m_posTarget;
}

//============================================================================
// 目標座標設定
//============================================================================
void CInput_UI::SetPosTarget(D3DXVECTOR3 posTarget)
{
	m_posTarget = posTarget;
}

//============================================================================
// 目標向き取得
//============================================================================
D3DXVECTOR3 CInput_UI::GetRotTarget()
{
	return m_rotTarget;
}

//============================================================================
// 目標向き設定
//============================================================================
void CInput_UI::SetRotTarget(D3DXVECTOR3 rotTarget)
{
	m_rotTarget = rotTarget;
}

//============================================================================
// 目標サイズ取得
//============================================================================
D3DXVECTOR3 CInput_UI::GetSizeTarget()
{
	return m_sizeTarget;
}

//============================================================================
// 目標サイズ設定
//============================================================================
void CInput_UI::SetSizeTarget(D3DXVECTOR3 sizeTarget)
{
	m_sizeTarget = sizeTarget;
}

//============================================================================
// 生成
//============================================================================
CInput_UI* CInput_UI::Create(CTexture_Manager::TYPE TexType)
{
	// インスタンスを生成
	CInput_UI* pInput_UI = DBG_NEW CInput_UI{};

	if (pInput_UI == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// テクスチャタイプを保持
	pInput_UI->m_TexType = TexType;

	if (TexType == CTexture_Manager::TYPE::CNT)
	{
		pInput_UI->m_nType = 0;
	}
	else if (TexType == CTexture_Manager::TYPE::BOARD_0)
	{
		pInput_UI->m_nType = 1;
	}
	else if (TexType == CTexture_Manager::TYPE::SPEECH)
	{
		pInput_UI->m_nType = 2;
	}
	else if (TexType == CTexture_Manager::TYPE::SPEECH_N)
	{
		pInput_UI->m_nType = 3;
	}

	// タイプを設定
	pInput_UI->SetType(TYPE::NONE);

	// 基底クラスの初期設定
	pInput_UI->Init();

	// テクスチャを設定
	pInput_UI->BindTex(CTexture_Manager::GetInstance()->GetTexture(TexType));

	// アルファ値を設定
	pInput_UI->SetAlpha(0.0f);

	// 出現設定
	pInput_UI->SetAppear();

	return pInput_UI;
}

//============================================================================
// 出現
//============================================================================
void CInput_UI::Appear()
{
	if (!m_bAppear)
	{
		return;
	}

	// アルファ値を取得
	float& fAlpha{ GetAlpha() };

	// 徐々に登場
	fAlpha += 0.05f;

	// 最大値に到達で固定
	if (fAlpha > 1.0f)
	{
		fAlpha = 1.0f;

		// 出現終了
		m_bAppear = false;
	}
}

//============================================================================
// 消滅
//============================================================================
void CInput_UI::Disappear()
{
	if (!m_bDisappear)
	{
		return;
	}

	// アルファ値を取得
	float& fAlpha{ GetAlpha() };

	// 徐々に消滅
	fAlpha += -0.1f;

	// 最低値に到達で固定
	if (fAlpha < 0.0f)
	{
		fAlpha = 0.0f;

		// 出現終了
		m_bDisappear = false;

		// 破棄予約
		SetRelease();
	}
}

//============================================================================
// CNTの更新
//============================================================================
void CInput_UI::UpdateCNT()
{
	// BGカメラの間距離を設定
	CManager::GetCamera()->SetDistanceBG(CUtility::GetInstance()->AdjustToTarget(CManager::GetCamera()->GetDistanceBG(), 35.0f, 0.025f));

	// BGカメラの目標座標を設定
	CManager::GetCamera()->SetPosBG(CUtility::GetInstance()->AdjustToTarget(CManager::GetCamera()->GetPosBG(), D3DXVECTOR3{ -3.0f, -12.5f, 0.0f }, 0.025f));

	// テクスチャ反映
	if (m_nDuration < 5)
	{
		m_nDuration++;

	}
	else
	{
		m_nDuration = 0;

		// フェーズに応じて差し替え変更
		switch (CTutorial_Manager::GetTexType())
		{
		case CTexture_Manager::TYPE::TEXT00:
			if (m_TexType != CTexture_Manager::TYPE::CNT_M0)
			{
				m_TexType = CTexture_Manager::TYPE::CNT_M0;
				BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
			}
			else if (m_TexType != CTexture_Manager::TYPE::CNT_M1)
			{
				m_TexType = CTexture_Manager::TYPE::CNT_M1;
				BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
			}
			break;

		case CTexture_Manager::TYPE::TEXT01:
			if (m_TexType != CTexture_Manager::TYPE::CNT_B0)
			{
				m_TexType = CTexture_Manager::TYPE::CNT_B0;
				BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
			}
			else if (m_TexType != CTexture_Manager::TYPE::CNT_B1)
			{
				m_TexType = CTexture_Manager::TYPE::CNT_B1;
				BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
			}
			break;

		case CTexture_Manager::TYPE::TEXT05:
			if (m_TexType != CTexture_Manager::TYPE::CNT_M2)
			{
				m_TexType = CTexture_Manager::TYPE::CNT_M2;
				BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
			}
			else if (m_TexType != CTexture_Manager::TYPE::CNT_M3)
			{
				m_TexType = CTexture_Manager::TYPE::CNT_M3;
				BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
			}
			break;

		default:
			m_TexType = CTexture_Manager::TYPE::CNT;
			BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
			break;
		}
	}
}

//============================================================================
// ボードの更新
//============================================================================
void CInput_UI::UpdateBoard()
{
	// 新しい情報を作成
	D3DXVECTOR3 NewPosTarget{ GetPosTarget() };

	// 切り替えスイッチ
	static bool bSwitch{ false };

	if (bSwitch)
	{
		NewPosTarget.x = CUtility::GetInstance()->AdjustToTarget(NewPosTarget.x, -16.6f, 0.03f);
		
		if (NewPosTarget.x <= -16.59f)
		{
			bSwitch = !bSwitch;
		}
	}
	else
	{
		NewPosTarget.x = CUtility::GetInstance()->AdjustToTarget(NewPosTarget.x, -16.4f, 0.03f);

		if (NewPosTarget.x >= -16.41f)
		{
			bSwitch = !bSwitch;
		}
	}

	// 座標を反映
	SetPosTarget(NewPosTarget);

	// サイズ目標を固定
	SetSizeTarget({ 5.5f, 5.5f, 0.0f });

	if (CTutorial_Manager::GetTexType() == CTexture_Manager::TYPE::TEXT05 && m_TexType != CTexture_Manager::TYPE::BOARD_2)
	{
		m_TexType = CTexture_Manager::TYPE::BOARD_2;

		BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::BOARD_2));
		
		// 拡大
		SetSize(GetSize() * 1.25f);
	}
	
	if (CTutorial_Manager::GetTexType() == CTexture_Manager::TYPE::TEXT01 && m_TexType != CTexture_Manager::TYPE::BOARD_1)
	{
		m_TexType = CTexture_Manager::TYPE::BOARD_1;

		BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::BOARD_1));

		// 拡大
		SetSize(GetSize() * 1.25f);
	}
}

//============================================================================
// ふきだしの更新
//============================================================================
void CInput_UI::UpdateSpeech()
{
	// 新しい情報を作成
	D3DXVECTOR3 NewPosTarget{ GetPosTarget() };

	// 増加量
	static float fAdder{ 0.0035f };

	// 少し動く
	NewPosTarget.y += fAdder;

	if (NewPosTarget.y >= 1.0f + 0.2f || NewPosTarget.y <= 1.0f + -0.2f)
	{
		fAdder *= -1.0f;
	}

	// 座標を反映
	SetPosTarget(NewPosTarget);
}