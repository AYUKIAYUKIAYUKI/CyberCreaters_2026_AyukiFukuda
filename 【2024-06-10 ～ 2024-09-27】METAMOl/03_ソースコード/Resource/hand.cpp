//=============================================================================
//
// 手とか [hand.cpp]
// Author : 福田歩希
//
//=============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "hand.h"
#include "utility.h"

// デバッグ表示用
#include "renderer.h"

// インプット取得用
#include "manager.h"

// フェーズ取得用
#include "tutorial_manager.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CHand::CHand() :
	CObject_3D{ static_cast<int>(LAYER::BG) },
	m_nLR{ 0 },
	m_nDuration{ 0 },
	m_TexType{ CTexture_Manager::TYPE::CROWN },
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
CHand::~CHand()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CHand::Init()
{
	if (m_nLR == 0)
	{
		// 座標設定
		SetPos({ -3.0f + -50.0f, -10.0f + -50.0f, -10.0f });
		SetPosTarget({ -3.0f, -10.0f, -10.0f });

		// サイズ設定
		SetSize({ 10.0f, 10.0f, 0.0f });
		SetSizeTarget({ 10.0f, 10.0f, 0.0f });
	}
	else if (m_nLR == 1)
	{
		// 座標設定
		SetPos({ -3.0f + 50.0f, -10.0f + -50.0f, -10.0f });
		SetPosTarget({ -3.0f, -10.0f, -10.0f });

		// サイズ設定
		SetSize({ 10.0f, 10.0f, 0.0f });
		SetSizeTarget({ 10.0f, 10.0f, 0.0f });
	}

	// 基底クラスの初期設定
	HRESULT hr = CObject_3D::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CHand::Uninit()
{
	// 基底クラスの終了処理
	CObject_3D::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CHand::Update()
{
//#ifdef _DEBUG
//	CRenderer::GetInstance()->SetDebugString("【手座標】");
//	std::ostringstream oss;
//	oss << std::fixed << std::setprecision(6) << "X:" << GetPos().x << "\nY:" << GetPos().y << "\nY:" << GetPos().z;
//	CRenderer::GetInstance()->SetDebugString(oss.str().c_str());
//#endif // _DEBUG

	if (!m_bDisappear)
	{
		if (m_nLR == 0)
		{
			UpdateL();
		}
		else if (m_nLR == 1)
		{
			UpdateR();
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
void CHand::Draw()
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
void CHand::SetAppear()
{
	m_bAppear = true;
}

//============================================================================
// 消滅設定
//============================================================================
void CHand::SetDisappear()
{
	m_bDisappear = true;
}

//============================================================================
// 目標座標取得
//============================================================================
D3DXVECTOR3 CHand::GetPosTarget()
{
	return m_posTarget;
}

//============================================================================
// 目標座標設定
//============================================================================
void CHand::SetPosTarget(D3DXVECTOR3 posTarget)
{
	m_posTarget = posTarget;
}

//============================================================================
// 目標向き取得
//============================================================================
D3DXVECTOR3 CHand::GetRotTarget()
{
	return m_rotTarget;
}

//============================================================================
// 目標向き設定
//============================================================================
void CHand::SetRotTarget(D3DXVECTOR3 rotTarget)
{
	m_rotTarget = rotTarget;
}

//============================================================================
// 目標サイズ取得
//============================================================================
D3DXVECTOR3 CHand::GetSizeTarget()
{
	return m_sizeTarget;
}

//============================================================================
// 目標サイズ設定
//============================================================================
void CHand::SetSizeTarget(D3DXVECTOR3 sizeTarget)
{
	m_sizeTarget = sizeTarget;
}

//============================================================================
// 生成
//============================================================================
CHand* CHand::Create(CTexture_Manager::TYPE TexType)
{
	// インスタンスを生成
	CHand* pHand = DBG_NEW CHand{};

	if (pHand == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// テクスチャタイプを保持
	pHand->m_TexType = TexType;

	if (TexType == CTexture_Manager::TYPE::LHAND)
	{
		pHand->m_nLR = 0;
	}
	else if (TexType == CTexture_Manager::TYPE::RHAND)
	{
		pHand->m_nLR = 1;
	}

	// タイプを設定
	pHand->SetType(TYPE::NONE);

	// 基底クラスの初期設定
	pHand->Init();

	// テクスチャを設定
	pHand->BindTex(CTexture_Manager::GetInstance()->GetTexture(TexType));

	// アルファ値を設定
	pHand->SetAlpha(0.0f);

	// 出現設定
	pHand->SetAppear();
	
	return pHand;
}

//============================================================================
// 出現
//============================================================================
void CHand::Appear()
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
void CHand::Disappear()
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
// 左の更新
//============================================================================
void CHand::UpdateL()
{
	//if (CTutorial_Manager::GetTexType() == CTexture_Manager::TYPE::TEXT00 || 
	//	CTutorial_Manager::GetTexType() == CTexture_Manager::TYPE::TEXT02)
	//{
	//	// ランダムな座標
	//	D3DXVECTOR3 RandomPos{ CUtility::GetInstance()->GetRandomValue<float>() * 0.001f ,CUtility::GetInstance()->GetRandomValue<float>() * 0.001f, 0.0f };

	//	// 目標座標の設定
	//	SetPosTarget(D3DXVECTOR3{ -3.0f, -10.0f, -10.0f, } + RandomPos * 2.0f);

	//	// 一定間隔でテクスチャを変更する
	//	if (m_nDuration < 5)
	//	{
	//		m_nDuration++;
	//	}
	//	else
	//	{
	//		m_nDuration = 0;

	//		if (m_TexType == CTexture_Manager::TYPE::LHAND)
	//		{
	//			m_TexType = CTexture_Manager::TYPE::LHAND_ALT;
	//			BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	//		}
	//		else if (m_TexType == CTexture_Manager::TYPE::LHAND_ALT)
	//		{
	//			m_TexType = CTexture_Manager::TYPE::LHAND;
	//			BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	//		}
	//	}
	//}
	//else
	//{

	// キーボードを取得
	CInputKeyboard* pKeyboard{ CManager::GetKeyboard() };

	// コントローラを取得
	CInputPad* pPad{ CManager::GetPad() };

	// スティック入力をコピー
	SHORT StickX{ pPad->GetJoyStickL().X }, StickY{ pPad->GetJoyStickL().Y };

	// 方向の種類を格納
	int nTypeRot{ -1 };

	// 方向の種類を決定
	float fAngle{ atan2f(StickY, StickX) };

#ifdef _DEBUG
	CRenderer::GetInstance()->SetDebugString("Lスティッくの傾き : " + std::to_string(fAngle));
#endif // _DEBUG

	// 入力がされていれば
	if (StickX != 0 || StickY != 0)
	{
		// 傾きに応じてテクスチャ指定
		if (fAngle >= D3DX_PI * -0.25f && fAngle <= D3DX_PI * 0.25f)
		{
			nTypeRot = 1;
		}
		else if (fAngle >= D3DX_PI * 0.25f && fAngle <= D3DX_PI * 0.75f)
		{
			nTypeRot = 2;
		}
		else if (fAngle <= D3DX_PI * -0.25f && fAngle >= D3DX_PI * -0.75f)
		{
			nTypeRot = 3;
		}
		else
		{
			nTypeRot = 0;
		}
	}

	// ランダムな座標
	D3DXVECTOR3 RandomPos{ CUtility::GetInstance()->GetRandomValue<float>() * 0.001f ,CUtility::GetInstance()->GetRandomValue<float>() * 0.001f, 0.0f };

	// 目標座標の設定
	SetPosTarget(D3DXVECTOR3{ -3.0f, -10.0f, -10.0f, } + RandomPos * 3.0f);
	
	// テクスチャ反映
	if (nTypeRot == 0 ||
		nTypeRot == -1 && pKeyboard->GetPress(DIK_A))
	{
		m_TexType = CTexture_Manager::TYPE::LHAND_SL;
		BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}
	else if (nTypeRot == 1 ||
		nTypeRot == -1 && pKeyboard->GetPress(DIK_D))
	{
		m_TexType = CTexture_Manager::TYPE::LHAND_SR;
		BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}
	else if (nTypeRot == 2 ||
		nTypeRot == -1 && pKeyboard->GetPress(DIK_W))
	{
		m_TexType = CTexture_Manager::TYPE::LHAND_SU;
		BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}
	else if (nTypeRot == 3 ||
		nTypeRot == -1 && pKeyboard->GetPress(DIK_S))
	{
		m_TexType = CTexture_Manager::TYPE::LHAND_SD;
		BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}
	else if (nTypeRot == -1 && pPad->GetPress(CInputPad::JOYKEY::LEFT))
	{
		m_TexType = CTexture_Manager::TYPE::LHAND_JL;
		BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}
	else if (nTypeRot == -1 && pPad->GetPress(CInputPad::JOYKEY::RIGHT))
	{
		m_TexType = CTexture_Manager::TYPE::LHAND_JR;
		BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}
	else if (nTypeRot == -1 && pPad->GetPress(CInputPad::JOYKEY::UP))
	{
		m_TexType = CTexture_Manager::TYPE::LHAND_JU;
		BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}
	else if (nTypeRot == -1 && pPad->GetPress(CInputPad::JOYKEY::DOWN))
	{
		m_TexType = CTexture_Manager::TYPE::LHAND_JD;
		BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}
	else
	{
		// 目標座標の設定
		SetPosTarget({ -3.0f, -10.0f, -10.0f, });

		m_TexType = CTexture_Manager::TYPE::LHAND;
		BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}

	//}
}

//============================================================================
// 右の更新
//============================================================================
void CHand::UpdateR()
{
	//if (CTutorial_Manager::GetTexType() == CTexture_Manager::TYPE::TEXT01 ||
	//	CTutorial_Manager::GetTexType() == CTexture_Manager::TYPE::TEXT02)
	//{
	//	// ランダムな座標
	//	D3DXVECTOR3 RandomPos{ CUtility::GetInstance()->GetRandomValue<float>() * 0.001f ,CUtility::GetInstance()->GetRandomValue<float>() * 0.001f, 0.0f };

	//	// 目標座標の設定
	//	SetPosTarget(D3DXVECTOR3{ -3.0f, -10.0f, -10.0f, } + RandomPos * 2.0f);

	//	// 一定間隔でテクスチャを変更する
	//	if (m_nDuration < 5)
	//	{
	//		m_nDuration++;
	//	}
	//	else
	//	{
	//		m_nDuration = 0;

	//		if (m_TexType == CTexture_Manager::TYPE::RHAND_B)
	//		{
	//			m_TexType = CTexture_Manager::TYPE::RHAND_A;
	//			BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	//		}
	//		else if (m_TexType == CTexture_Manager::TYPE::RHAND_A)
	//		{
	//			m_TexType = CTexture_Manager::TYPE::RHAND_X;
	//			BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	//		}
	//		else if (m_TexType == CTexture_Manager::TYPE::RHAND_X)
	//		{
	//			m_TexType = CTexture_Manager::TYPE::RHAND_Y;
	//			BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	//		}
	//		else if (m_TexType == CTexture_Manager::TYPE::RHAND_Y)
	//		{
	//			m_TexType = CTexture_Manager::TYPE::RHAND_B;
	//			BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	//		}
	//	}
	//}
	//else
	//{ 

	// キーボードを取得
	CInputKeyboard* pKeyboard{ CManager::GetKeyboard() };

	// コントローラを取得
	CInputPad* pPad{ CManager::GetPad() };

	// ランダムな座標
	D3DXVECTOR3 RandomPos{ CUtility::GetInstance()->GetRandomValue<float>() * 0.001f ,CUtility::GetInstance()->GetRandomValue<float>() * 0.001f, 0.0f };

	// 目標座標の設定
	SetPosTarget(D3DXVECTOR3{ -3.0f, -10.0f, -10.0f, } + RandomPos * 3.0f);

	if (pPad->GetPress(CInputPad::JOYKEY::A))
	{
		m_TexType = CTexture_Manager::TYPE::RHAND_A;
		BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}
	else if (pPad->GetPress(CInputPad::JOYKEY::B))
	{
		m_TexType = CTexture_Manager::TYPE::RHAND_B;
		BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}
	else if (pPad->GetPress(CInputPad::JOYKEY::X) ||
		pKeyboard->GetPress(DIK_SPACE))
	{
		m_TexType = CTexture_Manager::TYPE::RHAND_X;
		BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}
	else if (pPad->GetPress(CInputPad::JOYKEY::Y))
	{
		m_TexType = CTexture_Manager::TYPE::RHAND_Y;
		BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}
	else
	{
		// 目標座標の設定
		SetPosTarget({ -3.0f, -10.0f, -10.0f, });

		m_TexType = CTexture_Manager::TYPE::RHAND;
		BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}

	//}
}