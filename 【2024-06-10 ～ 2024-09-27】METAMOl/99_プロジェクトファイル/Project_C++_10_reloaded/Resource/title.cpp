//============================================================================
// 
// タイトル [title.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "title.h"
#include "fakescreen.h"
#include "sound.h"
#include "utility.h"

// インプット取得用
#include "manager.h"

// テクスチャ取得用
#include "texture_manager.h"

//============================================================================
// コンストラクタ
//============================================================================
CTitle::CTitle() : m_pBg { nullptr },
	m_pSpeech{ nullptr },
	m_nSelect{ 0 }
{
	for (int i = 0; i < static_cast<int>(UI_TYPE::MAX); i++)
	{
		m_pUI[i] = nullptr;
	}
}

//============================================================================
// デストラクタ
//============================================================================
CTitle::~CTitle()
{
	if (m_pSpeech)
	{
		m_pSpeech->SetDisappear();
		m_pSpeech = nullptr;
	}
}

//============================================================================
// 初期設定
//============================================================================
HRESULT CTitle::Init()
{
	// 背景の生成
	m_pBg = CBg::Create(
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// 位置
		{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f },	// サイズ
		CTexture_Manager::TYPE::BG_000);						// テクスチャ

	// タイトルロゴの生成
	m_pUI[3] = CText::Create(CTexture_Manager::TYPE::LOGO);
	m_pUI[3]->SetPos({ SCREEN_WIDTH * 0.5f, 0.0f, 0.0f });
	m_pUI[3]->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f });
	m_pUI[3]->SetSizeTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f });
	m_pUI[3]->SetAppear(true);

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CTitle::Uninit()
{
	// 基底クラスの終了処理
	CScene::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CTitle::Update()
{
	// パッドを取得
	CInputPad* pPad = CManager::GetPad();

	// 左右の入力情報
	static DWORD dwOldInput{ 0 };
	static bool bInputUp{ false };
	static bool bInputDown{ false };

	// 上疑似トリガー入力
	if (pPad->GetJoyStickL().Y > 0 && dwOldInput == 0)
	{
		bInputUp = true;
	}
	else
	{
		bInputUp = false;
	}

	// 下疑似トリガー入力
	if (pPad->GetJoyStickL().Y < 0 && dwOldInput == 0)
	{
		bInputDown = true;
	}
	else
	{
		bInputDown = false;
	}

	// 過去の入力情報を保持
	dwOldInput = pPad->GetJoyStickL().Y;

	// 応急処置
	if (m_nSelect == 0)
	{
		if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) ||
			pPad->GetTrigger(CInputPad::JOYKEY::START) ||
			pPad->GetTrigger(CInputPad::JOYKEY::A) ||
			pPad->GetTrigger(CInputPad::JOYKEY::B) ||
			pPad->GetTrigger(CInputPad::JOYKEY::X) ||
			pPad->GetTrigger(CInputPad::JOYKEY::Y))
		{
			m_nSelect = 1;

			if (!m_pUI[0])
			{
				m_pUI[0] = CText::Create(CTexture_Manager::TYPE::NORMAL);
				m_pUI[0]->SetPos({ 0.0f, SCREEN_HEIGHT * 0.55f, 0.0f });
				m_pUI[0]->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.55f, 0.0f });
				//m_pUI[0]->SetSize({ 0.0f, 0.0f, 0.0f });
				m_pUI[0]->SetSizeTarget({ 250.0f, 62.5f, 0.0f });
				m_pUI[0]->SetCol({ 0.5f, 0.5f, 0.5f, 0.0f });
				m_pUI[0]->SetAppear(true);
			}

			if (!m_pUI[1])
			{
				m_pUI[1] = CText::Create(CTexture_Manager::TYPE::CHALLENGE);
				m_pUI[1]->SetPos({ SCREEN_WIDTH, SCREEN_HEIGHT * 0.75f, 0.0f });
				m_pUI[1]->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.75f, 0.0f });
				//m_pUI[1]->SetSize({ 0.0f, 0.0f, 0.0f });
				m_pUI[1]->SetSizeTarget({ 250.0f, 62.5f, 0.0f });
				m_pUI[1]->SetCol({ 0.5f, 0.5f, 0.5f, 0.0f });
				m_pUI[1]->SetAppear(true);
			}

			if (!m_pUI[2])
			{
				m_pUI[2] = CText::Create(CTexture_Manager::TYPE::CURSOR);
				m_pUI[2]->SetPos({ 0.0f, SCREEN_HEIGHT * 0.55f, 0.0f });
				m_pUI[2]->SetPosTarget({ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.55f, 0.0f });
				m_pUI[2]->SetSize({ 0.0f, 0.0f, 0.0f });
				m_pUI[2]->SetSizeTarget({ 30.0f, 30.0f, 0.0f });
				m_pUI[2]->SetAppear(true);
			}

			m_pUI[3]->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f, 0.0f });
			m_pUI[3]->SetSizeTarget({ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f, 0.0f });
		
			// ふきだしの生成
			if (!m_pSpeech) 
			{
				m_pSpeech = CInput_UI::Create(CTexture_Manager::TYPE::SPEECH_N);
			}
		}
	}
	else
	{
		// BGカメラの間距離を設定
		CManager::GetCamera()->SetDistanceBG(CUtility::GetInstance()->AdjustToTarget(CManager::GetCamera()->GetDistanceBG(), 25.0f, 0.025f));

		if (m_nSelect == 1)
		{
			if (m_pUI[0])
			{
				m_pUI[0]->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.55f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
				m_pUI[0]->SetCol({ 1.0f, 1.0f, 1.0f, m_pUI[0]->GetAlpha() });
			}

			if (m_pUI[2])
			{
				m_pUI[2]->SetPosTarget({ SCREEN_WIDTH * 0.5f - 275.0f, SCREEN_HEIGHT * 0.55f, 0.0f });
			}

			// テクスチャを設定
			m_pSpeech->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::SPEECH_N));

			if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) ||
				pPad->GetTrigger(CInputPad::JOYKEY::START) ||
				pPad->GetTrigger(CInputPad::JOYKEY::A) ||
				pPad->GetTrigger(CInputPad::JOYKEY::B) ||
				pPad->GetTrigger(CInputPad::JOYKEY::X) ||
				pPad->GetTrigger(CInputPad::JOYKEY::Y))
			{
				// 決定音
				CSound::GetInstance()->Play(CSound::LABEL::DEFINE);

				// ノーマルゲームへ
				CFakeScreen::GetInstance()->SetFade(MODE::GAME);
			}
			else if (CManager::GetKeyboard()->GetTrigger(DIK_S) ||
				CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::DOWN) ||
				bInputDown)
			{
				// 選択音
				CSound::GetInstance()->Play(CSound::LABEL::SELECT);

				m_nSelect = 2;

				m_pUI[0]->SetCol({ 0.5f, 0.5f, 0.5f, m_pUI[0]->GetAlpha() });
			}
		}
		else if (m_nSelect == 2)
		{
			if (m_pUI[1])
			{
				m_pUI[1]->SetPosTarget({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.75f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
				m_pUI[1]->SetCol({ 1.0f, 1.0f, 1.0f, m_pUI[1]->GetAlpha() });
			}

			if (m_pUI[2])
			{
				m_pUI[2]->SetPosTarget({ SCREEN_WIDTH * 0.5f - 275.0f, SCREEN_HEIGHT * 0.75f, 0.0f });
			}

			// テクスチャを設定
			m_pSpeech->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::SPEECH_C));

			if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) ||
				pPad->GetTrigger(CInputPad::JOYKEY::START) ||
				pPad->GetTrigger(CInputPad::JOYKEY::A) ||
				pPad->GetTrigger(CInputPad::JOYKEY::B) ||
				pPad->GetTrigger(CInputPad::JOYKEY::X) ||
				pPad->GetTrigger(CInputPad::JOYKEY::Y))
			{
				// 決定音
				CSound::GetInstance()->Play(CSound::LABEL::DEFINE);

				// チャレンジゲームへ
				CFakeScreen::GetInstance()->SetFade(MODE::CHALLENGE);
			}
			else if (CManager::GetKeyboard()->GetTrigger(DIK_W) ||
				CManager::GetPad()->GetTrigger(CInputPad::JOYKEY::UP) ||
				bInputUp)
			{
				// 選択音
				CSound::GetInstance()->Play(CSound::LABEL::SELECT);

				m_nSelect = 1;

				m_pUI[1]->SetCol({ 0.5f, 0.5f, 0.5f, m_pUI[1]->GetAlpha() });
			}
		}
	}
}

//============================================================================
// 描画処理
//============================================================================
void CTitle::Draw()
{

}

//============================================================================
// モード選択情報取得
//============================================================================
int CTitle::GetSelect()
{
	// シーン情報を取得
	CScene* pScene{ CManager::GetScene() };

	if (!pScene)
	{
		return -1;
	}

	// タイトルクラスにダウンキャスト
	CTitle* pTitle{ CUtility::GetInstance()->DownCast<CTitle, CScene>(pScene) };

	return pTitle->m_nSelect;
}