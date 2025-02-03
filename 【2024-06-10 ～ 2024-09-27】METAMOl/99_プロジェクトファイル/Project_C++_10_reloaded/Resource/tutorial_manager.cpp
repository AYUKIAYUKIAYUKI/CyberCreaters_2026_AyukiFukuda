//============================================================================
// 
// チュートリアルマネージャー [tutorial_manager.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "tutorial_manager.h"
#include "utility.h"

// デバッグ表示用
#include "renderer.h"

// プレイヤー取得用
#include "player.h"
#include "player_state.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
CTutorial_Manager* CTutorial_Manager::m_pInstance = nullptr;	// 自クラスのポインタ

//============================================================================
// 更新
//============================================================================
void CTutorial_Manager::UpdateTutorial()
{
	if (!m_pInstance)
	{
		// 生成
		CTutorial_Manager::CreateInstance();
	}

	// プレイヤーの座標を確認
	m_pInstance->CheckPlayerPos();
}

//============================================================================
// 削除
//============================================================================
void CTutorial_Manager::DeleteInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

//============================================================================
// テクスチャタイプを取得
//============================================================================
CTexture_Manager::TYPE CTutorial_Manager::GetTexType()
{
	if (m_pInstance)
	{
		return m_pInstance->m_TexType;
	}

	return CTexture_Manager::TYPE::TEXT00;
}

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CTutorial_Manager::CTutorial_Manager() :
	m_nCnt09{ 0 },
	m_pText{ nullptr },
	m_apHand{ nullptr, nullptr },
	m_apInput_UI{ nullptr, nullptr, nullptr },
	m_TexType{ CTexture_Manager::TYPE::TEXT00 }
{
	// テキストを生成
	CreateText();

	// インプットUIを生成 (手より先行)
	m_apInput_UI[0] = CInput_UI::Create(CTexture_Manager::TYPE::CNT);
	m_apInput_UI[1] = CInput_UI::Create(CTexture_Manager::TYPE::BOARD_0);
	m_apInput_UI[2] = CInput_UI::Create(CTexture_Manager::TYPE::SPEECH);

	// 手とかを生成
	m_apHand[0] = CHand::Create(CTexture_Manager::TYPE::LHAND);
	m_apHand[1] = CHand::Create(CTexture_Manager::TYPE::RHAND);
}

//============================================================================
// デストラクタ
//============================================================================
CTutorial_Manager::~CTutorial_Manager()
{
	// 省略
	if (m_pText)
	{
		m_pText->SetDisappear(true);
		m_pText->SetPosTarget(D3DXVECTOR3{ 0.0f, SCREEN_HEIGHT + 100.0f, 0.0f });
		m_pText->SetSizeTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });
		m_pText = nullptr;
	}

	if (m_apHand[0])
	{
		m_apHand[0]->SetDisappear();
		m_apHand[0]->SetPosTarget({ -3.0f, -7.5f, -10.0f, });	// 値はCHand::Initより
		m_apHand[0]->SetSizeTarget(D3DXVECTOR3{ 10.0f, 10.0f, 0.0f });
		m_apHand[0] = nullptr;
	}

	if (m_apHand[1])
	{
		m_apHand[1]->SetDisappear();
		m_apHand[1]->SetPosTarget({ -3.0f, -7.5f, -10.0f, });	// 値はCHand::Initより
		m_apHand[1]->SetSizeTarget(D3DXVECTOR3{ 10.0f, 10.0f, 0.0f });
		m_apHand[1] = nullptr;
	}

	if (m_apInput_UI[0])
	{
		m_apInput_UI[0]->SetDisappear();
		m_apInput_UI[0]->SetPosTarget({ -3.0f, -7.5f, -10.0f, });	// 値はCInput_UI::Initより
		m_apInput_UI[0]->SetSizeTarget(D3DXVECTOR3{ 10.0f, 10.0f, 0.0f });
		m_apInput_UI[0] = nullptr;
	}

	if (m_apInput_UI[1])
	{
		m_apInput_UI[1]->SetDisappear();
		m_apInput_UI[1]->SetPosTarget({ -16.5f, 6.0f, -10.0f });	// 値はCInput_UI::Initより
		m_apInput_UI[1]->SetSizeTarget(D3DXVECTOR3{ 5.5f, 5.5f, 0.0f });
		m_apInput_UI[1] = nullptr;
	}

	if (m_apInput_UI[2])
	{
		m_apInput_UI[2]->SetDisappear();
		m_apInput_UI[2]->SetPosTarget({ 13.5f, 1.0f, -10.0f });	// 値はCInput_UI::Initより
		m_apInput_UI[2]->SetSizeTarget(D3DXVECTOR3{ 5.5f, 5.5f, 0.0f });
		m_apInput_UI[2] = nullptr;
	}
}

//============================================================================
// 生成
//============================================================================
void CTutorial_Manager::CreateInstance()
{
	if (m_pInstance != nullptr)
	{ // 二重生成禁止
		assert(false);
	}

	// チュートリアルマネージャーを生成
	m_pInstance = DBG_NEW CTutorial_Manager{};
}

//============================================================================
// テキストの生成
//============================================================================
void CTutorial_Manager::CreateText()
{
	if (!m_pText)
	{
		// テキストの生成
		m_pText = CText::Create(CTexture_Manager::TYPE::TEXT00);

		// タイプの保持
		m_TexType = CTexture_Manager::TYPE::TEXT00;

		// 出現設定
		m_pText->SetAppear(true);

		// 初期座標を設定
		m_pText->SetPos(D3DXVECTOR3{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT + 100.0f, 0.0f });
		m_pText->SetPosTarget(D3DXVECTOR3{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT + 100.0f, 0.0f });

		// 初期目標サイズを設定
		m_pText->SetSizeTarget(D3DXVECTOR3{ 200.0f * 1.4f, 50.0f * 1.4f, 0.0f });
	}
}

//============================================================================
// テキストの削除
//============================================================================
void CTutorial_Manager::DeleteText()
{
	// 省略
	if (m_pText)
	{
		m_pText->SetDisappear(true);
		m_pText->SetPosTarget(D3DXVECTOR3{ 0.0f, SCREEN_HEIGHT + 100.0f, 0.0f });
		m_pText->SetSizeTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });
		m_pText = nullptr;
	}
}

//============================================================================
// プレイヤーの座標を確認
//============================================================================
void CTutorial_Manager::CheckPlayerPos()
{
	// プレイヤータグを取得
	CObject* pObj{ CObject::FindObject(CObject::TYPE::PLAYER) };

	// 取得失敗
	if (!pObj)
	{
		return;
	}

	// プレイヤークラスにダウンキャスト
	CPlayer* pPlayer{ CUtility::GetInstance()->DownCast<CPlayer, CObject>(pObj) };

	// 状態に応じてテキスト操作
	if (typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateGoal))
	{
		// テキストを削除
		DeleteText();

		// 以降テキストをいじらない
		return;
	}

	// テキストの目標座標を設定
	m_pText->SetPosTarget(D3DXVECTOR3{ SCREEN_WIDTH * 0.5f, (SCREEN_HEIGHT * 0.75f) + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });

	// プレイヤーの座標をコピー
	D3DXVECTOR3 Pos{ pPlayer->GetPos() };

	//===== 以下無法地帯 =====//

	// 「移動してみよう」から
	if (m_TexType == CTexture_Manager::TYPE::TEXT00 && Pos.y < -60.0f)
	{
		// テキスト変更
		m_TexType = CTexture_Manager::TYPE::TEXT01;	// とんでみよう
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT00 && typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateFlying) && Pos.y > -20.0f ||
		m_TexType == CTexture_Manager::TYPE::TEXT00 && typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateRushing) && Pos.y > -20.0f ||
		m_TexType == CTexture_Manager::TYPE::TEXT01 && typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateFlying) && Pos.y > -20.0f ||
		m_TexType == CTexture_Manager::TYPE::TEXT01 && typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateRushing) && Pos.y > -20.0f)
	{
		// テキスト変更
		m_TexType = CTexture_Manager::TYPE::TEXT02;	// ブロックにぶつかろう
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}

	//if (m_TexType < CTexture_Manager::TYPE::TEXT05 && typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateRushing) && Pos.x > 280.0f)
	//{
	//	m_nCnt09 = 90;

	//	// テキスト変更
	//	m_TexType = CTexture_Manager::TYPE::TEXT09;	// 何をしてんの！？
	//	m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	//	m_pText->SetSizeTarget(D3DXVECTOR3{ 200.0f * 1.65f, 50.0f * 1.65f, 0.0f });
	//}
	//else 
	//	if (m_TexType == CTexture_Manager::TYPE::TEXT09 && typeid(*pPlayer->GetStateManager()->GetState()) != typeid(CPlayerStateRushing))
	//{
	//	if (m_nCnt09 > 0)
	//	{
	//		m_nCnt09--;
	//	}
	//	else
	//	{
	//		// ここを抜けるとマイナスに
	//		m_nCnt09 = -1;

	//		m_TexType = CTexture_Manager::TYPE::TEXT03;	// 右へ進んでみよう
	//		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	//		m_pText->SetRotTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });
	//	}
	//}

	if (m_TexType == CTexture_Manager::TYPE::TEXT02 && Pos.x > 300.0f)
	{
		// テキスト変更
		m_TexType = CTexture_Manager::TYPE::TEXT03;	// 右へ進んでみよう
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}

	// 一度も無視していなければ
	if (m_TexType == CTexture_Manager::TYPE::TEXT03 && Pos.x > 520.0f && m_nCnt09 >= 0)
	{
		// テキスト変更
		m_TexType = CTexture_Manager::TYPE::TEXT04;	// 大変そうですね
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
		m_pText->SetSizeTarget(D3DXVECTOR3{ 200.0f * 1.65f, 50.0f * 1.65f, 0.0f });
	}

	// 煽りブルブル
	if (m_TexType == CTexture_Manager::TYPE::TEXT04 || m_TexType == CTexture_Manager::TYPE::TEXT09)
	{
		m_pText->SetRotTarget(D3DXVECTOR3{ 0.0f, 0.0f, CUtility::GetInstance()->GetRandomValue<float>() * 0.005f });
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT03  && Pos.x > 580.0f ||
		m_TexType == CTexture_Manager::TYPE::TEXT04  && Pos.x > 580.0f)
	{
		// テキスト変更
		m_TexType = CTexture_Manager::TYPE::TEXT05;	// 突進してみよう
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
		m_pText->SetSizeTarget(D3DXVECTOR3{ 200.0f * 1.4f, 50.0f * 1.4f, 0.0f });
		m_pText->SetRotTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT05 && typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateMistook) && Pos.x > 1000.0f)
	{
		// テキスト変更
		m_TexType = CTexture_Manager::TYPE::TEXT06;	// 残念！ざまーみろ
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
		m_pText->SetSizeTarget(D3DXVECTOR3{ 200.0f * 0.9f, 50.0f * 0.9f, 0.0f });
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT05 && typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateDefault) && Pos.x > 760.0f)
	{
		// テキスト変更
		m_TexType = CTexture_Manager::TYPE::TEXT10;	// 強情だね…
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT06 && typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateMistook) && Pos.x < 260.0f ||
		m_TexType == CTexture_Manager::TYPE::TEXT09 && typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateMistook) && Pos.x < 260.0f ||
		m_TexType == CTexture_Manager::TYPE::TEXT10 && typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateMistook) && Pos.x < 260.0f)
	{
		// テキスト変更
		m_TexType = CTexture_Manager::TYPE::TEXT07;	// おっと！大丈夫そうだね
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
		m_pText->SetSizeTarget(D3DXVECTOR3{ 200.0f * 1.4f, 50.0f * 1.4f, 0.0f });
		m_pText->SetRotTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT07 && Pos.x > 260.0f)
	{
		// テキスト変更
		m_TexType = CTexture_Manager::TYPE::TEXT08;	// もう一度突進してみよう
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT08 && typeid(*pPlayer->GetStateManager()->GetState()) != typeid(CPlayerStateRushing) && Pos.x > 1090.0f)
	{
		// テキスト変更
		m_TexType = CTexture_Manager::TYPE::TEXT11;	// おっと
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
	}

	if (m_TexType == CTexture_Manager::TYPE::TEXT11 && Pos.y > 65.0f)
	{
		// テキスト変更
		m_TexType = CTexture_Manager::TYPE::TEXT12;	// おみごと！
		m_pText->BindTex(CTexture_Manager::GetInstance()->GetTexture(m_TexType));
		m_pText->SetSizeTarget(D3DXVECTOR3{ 200.0f * 2.0f, 50.0f * 2.0f, 0.0f });
	}
}