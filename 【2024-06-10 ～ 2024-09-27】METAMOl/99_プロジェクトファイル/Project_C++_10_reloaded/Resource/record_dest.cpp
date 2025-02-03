//=============================================================================
//
// 破壊記録 [record_dest.cpp]
// Author : 福田歩希
//
//=============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "record_dest.h"
#include "utility.h"

// デバッグ表示用
#include "renderer.h"

// テクスチャ取得用
#include "texture_manager.h"

// ゲームマネージャー取得
#include "game_manager.h"

// プレイヤーの状態取得用
#include "player.h"
#include "player_state.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CRecord_Dest::CRecord_Dest() :
	CObject_UI{ static_cast<int>(LAYER::UI) },
	m_nCntDest{ 0 },
	m_bTimeUp{ false },
	m_pDestText{ nullptr },
	m_pBestText{ nullptr },
	m_pFailed{ nullptr }
{
	// 初期座標用
	D3DXVECTOR3 InitPos{ (SCREEN_WIDTH * 0.5f), -100.0f, 0.0f };

	// テキストを生成
	m_pDestText = CText::Create(CTexture_Manager::TYPE::RECORDDEST);
	m_pDestText->SetPos(InitPos);
	m_pDestText->SetAppear(true);

	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 数字情報のポインタを初期化
		m_apDestNum[nCntNum] = nullptr;
		m_apBestNum[nCntNum] = nullptr;

		// 数字を生成
		m_apDestNum[nCntNum] = CNumber::Create();
		m_apDestNum[nCntNum]->SetPos(InitPos);
		m_apDestNum[nCntNum]->SetAppear(true);

		/* 数がピッタシなのでついでにこれも初期化 */
		m_apUI[nCntNum] = nullptr;
	}

	// 出現予約
	SetAppear(true);
}

//============================================================================
// デストラクタ
//============================================================================
CRecord_Dest::~CRecord_Dest()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CRecord_Dest::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CRecord_Dest::Uninit()
{
	// 基底クラスの終了処理
	CObject_UI::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CRecord_Dest::Update()
{
	// 基底クラスの更新
	CObject_UI::Update();

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	/* 設定系統 */

	// フェーズによるUI動作分岐
	if (CGameManager::GetInstance()->GetPhase() == CGameManager::PHASE::C_FINISH)
	{ // 最高記録・選択肢を生成、通常記録を拡大

		// プレイヤーを検索
		CObject* pFind = CObject::FindObject(CObject::TYPE::PLAYER);

		// プレイヤーが見つかれば
		if (pFind)
		{
			// プレイヤーの加速度を無くす
			CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(pFind);
			pPlayer->SetVelocity({ 0.0f, 0.0f, 0.0f });
		}

		// タイムアップしている時
		if (m_bTimeUp)
		{
			if (!m_pFailed)
			{
				// 失敗表示が出現
				m_pFailed = CText::Create(CTexture_Manager::TYPE::FAILED);

				// 初期設定
				m_pFailed->SetPos({ SCREEN_WIDTH,  SCREEN_HEIGHT * 0.5f, 0.0f});
				m_pFailed->SetSizeTarget({ 100.0f, 20.0f, 0.0f });
			}
			else
			{
				// 目標座標を設定
				m_pFailed->SetPosTarget({ SCREEN_WIDTH * 0.675f,  SCREEN_HEIGHT * 0.5f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
			}
		}

		///////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////

		m_pDestText->SetPosTarget({ SCREEN_WIDTH * 0.425f, SCREEN_HEIGHT * 0.5f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
		m_pDestText->SetSizeTarget({ 200.0f, 40.0f, 0.0f });

		// 設定用共通情報
		D3DXVECTOR3 CopyPosTarget{ m_pDestText->GetPosTarget() };
		float fSizeX{ 55.0f };	// 共通横サイズ

		// 数字を並べる
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// 中心座標から、相対的な先頭の位置を設定
			CopyPosTarget.x = m_pDestText->GetPosTarget().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f) + 300.0f;

			// 先頭座標から数字が並ぶように調整
			CopyPosTarget.x += -fSizeX * nCntNum;
			m_apDestNum[nCntNum]->SetPosTarget(CopyPosTarget);

			// 数字の目標サイズを設定
			m_apDestNum[nCntNum]->SetSizeTarget({ fSizeX, 40.0f, 0.0f });
		}

		// カウント数のコピー
		int nCopy{ m_nCntDest };

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// 数字を設定
			m_apDestNum[nCntNum]->SetNumber(nCopy % 10);

			// 桁を減らす
			nCopy /= 10;
		}
		
		/////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////
		
		if (!m_pBestText)
		{
			// 初期座標用
			D3DXVECTOR3 InitPos{ (SCREEN_WIDTH * 0.5f), -100.0f, 0.0f };

			// テキストを生成
			m_pBestText = CText::Create(CTexture_Manager::TYPE::RECORDBEST);
			m_pBestText->SetPos(InitPos);
			m_pBestText->SetAppear(true);

			// 数字を生成
			for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
			{
				m_apBestNum[nCntNum] = CNumber::Create();
				m_apBestNum[nCntNum]->SetPos(InitPos);
				m_apBestNum[nCntNum]->SetAppear(true);
			}

			// 選択肢を生成
			m_apUI[0] = CText::Create(CTexture_Manager::TYPE::QUIT);
			m_apUI[1] = CText::Create(CTexture_Manager::TYPE::RETRY);
			m_apUI[2] = CText::Create(CTexture_Manager::TYPE::CURSOR);
			for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
			{
				m_apUI[nCntNum]->SetPos(InitPos);
				m_apUI[nCntNum]->SetAppear(true);
			}
		}
		else
		{ // 生成済みの場合は目標値設定

			m_pBestText->SetPosTarget({ SCREEN_WIDTH * 0.425f, SCREEN_HEIGHT * 0.25f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
			m_pBestText->SetSizeTarget({ 200.0f, 40.0f, 0.0f });

			// 設定用共通情報
			CopyPosTarget = m_pBestText->GetPosTarget();
			fSizeX = 55.0f;	// 共通横サイズ

			// カウント数のコピー
			nCopy = CRecord_Dest::ImportBestRecord();

			// 数字を並べる
			for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
			{
				// 中心座標から、相対的な先頭の位置を設定
				CopyPosTarget.x = m_pBestText->GetPosTarget().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f) + 300.0f;

				// 先頭座標から数字が並ぶように調整
				CopyPosTarget.x += -fSizeX * nCntNum;
				m_apBestNum[nCntNum]->SetPosTarget(CopyPosTarget);

				// 数字の目標サイズを設定
				m_apBestNum[nCntNum]->SetSizeTarget({ fSizeX, 40.0f, 0.0f });

				// 数字を設定
				m_apBestNum[nCntNum]->SetNumber(nCopy % 10);

				// 桁を減らす
				nCopy /= 10;
			}

			// 選択肢に目標座標を設定
			m_apUI[0]->SetPosTarget({ SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.75f, 0.0f });
			m_apUI[1]->SetPosTarget({ SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.75f, 0.0f });
			
			// 選択肢に目標サイズを設定
			m_apUI[0]->SetSizeTarget({ 100.0f, 30.0f, 0.0f });
			m_apUI[1]->SetSizeTarget({ 125.0f, 30.0f, 0.0f });
			m_apUI[2]->SetSizeTarget({ 30.0f, 30.0f, 0.0f });

			// 選択に応じてさらに変化
			/* カーソル座標はテキスト横幅強のサイズがぴったし */
			if (CGameManager::GetInstance()->GetSelectChallenge() == 0)
			{
				m_apUI[0]->SetCol({ 1.0f, 1.0f, 1.0f, m_apUI[1]->GetCol().a });
				m_apUI[0]->SetPosTarget({ SCREEN_WIDTH * 0.35f, SCREEN_HEIGHT * 0.75f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
				m_apUI[1]->SetCol({ 0.5f, 0.5f, 0.5f, m_apUI[1]->GetCol().a });
				m_apUI[2]->SetPosTarget({ SCREEN_WIDTH * 0.35f - 150.0f, SCREEN_HEIGHT * 0.75f, 0.0f });
			}
			else
			{
				m_apUI[0]->SetCol({ 0.5f, 0.5f, 0.5f, m_apUI[0]->GetCol().a });
				m_apUI[1]->SetCol({ 1.0f, 1.0f, 1.0f, m_apUI[0]->GetCol().a });
				m_apUI[1]->SetPosTarget({ SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.75f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
				m_apUI[2]->SetPosTarget({ SCREEN_WIDTH * 0.65f - 175.0f, SCREEN_HEIGHT * 0.75f, 0.0f });
			}
		}
	}
	else
	{ // 通常記録を縮小

		m_pDestText->SetPosTarget({ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.15f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f });
		m_pDestText->SetSizeTarget({ 140.0f, 30.0f, 0.0f });

		// 設定用共通情報
		D3DXVECTOR3 CopyPosTarget{ m_pDestText->GetPosTarget() };
		float fSizeX{ 42.5f };	// 共通横サイズ

		// 数字を並べる
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// 中心座標から、相対的な先頭の位置を設定
			CopyPosTarget.x = m_pDestText->GetPosTarget().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f) + 210.0f;

			// 先頭座標から数字が並ぶように調整
			CopyPosTarget.x += -fSizeX * nCntNum;
			m_apDestNum[nCntNum]->SetPosTarget(CopyPosTarget);

			// 数字の目標サイズを設定
			m_apDestNum[nCntNum]->SetSizeTarget({ fSizeX, 30.0f, 0.0f });
		}

		// カウント数のコピー
		int nCopy{ m_nCntDest };

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// 数字を設定
			m_apDestNum[nCntNum]->SetNumber(nCopy % 10);

			// 桁を減らす
			nCopy /= 10;
		}
	}

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	/* 反映系統 */

	// 数字系統
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		if (m_apDestNum[nCntNum])
		{
			m_apDestNum[nCntNum]->SetPos(CUtility::GetInstance()->AdjustToTarget(m_apDestNum[nCntNum]->GetPos(), m_apDestNum[nCntNum]->GetPosTarget(), 0.075f));
			m_apDestNum[nCntNum]->SetRot(CUtility::GetInstance()->AdjustToTarget(m_apDestNum[nCntNum]->GetRot(), m_apDestNum[nCntNum]->GetRotTarget(), 0.075f));
			m_apDestNum[nCntNum]->SetSize(CUtility::GetInstance()->AdjustToTarget(m_apDestNum[nCntNum]->GetSize(), m_apDestNum[nCntNum]->GetSizeTarget(), 0.05f));
		}

		if (m_apBestNum[nCntNum])
		{
			m_apBestNum[nCntNum]->SetPos(CUtility::GetInstance()->AdjustToTarget(m_apBestNum[nCntNum]->GetPos(), m_apBestNum[nCntNum]->GetPosTarget(), 0.075f));
			m_apBestNum[nCntNum]->SetRot(CUtility::GetInstance()->AdjustToTarget(m_apBestNum[nCntNum]->GetRot(), m_apBestNum[nCntNum]->GetRotTarget(), 0.075f));
			m_apBestNum[nCntNum]->SetSize(CUtility::GetInstance()->AdjustToTarget(m_apBestNum[nCntNum]->GetSize(), m_apBestNum[nCntNum]->GetSizeTarget(), 0.05f));
		}
	}
}

//============================================================================
// 描画処理
//============================================================================
void CRecord_Dest::Draw()
{
	// 基底クラスの描画処理
	CObject_UI::Draw();
}

//============================================================================
// 破壊記録をリセット
//============================================================================
void CRecord_Dest::ResetCntDest()
{
	m_nCntDest = 0;
}

//============================================================================
// 最高記録表記・選択肢を消去予定
//============================================================================
void CRecord_Dest::SetDisappearBestAndUI()
{
	// 応急処置
	if (m_pBestText) {
		m_pBestText->SetDisappear(true);
		m_pBestText = nullptr;
	}

	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++) {
		if (m_apBestNum[nCntNum]) {
			m_apBestNum[nCntNum]->SetDisappear(true);
			m_apBestNum[nCntNum] = nullptr;
		}
	}

	for (int nCntUI = 0; nCntUI < 3; nCntUI++) {
		if (m_apUI[nCntUI]) {
			m_apUI[nCntUI]->SetDisappear(true);
			m_apUI[nCntUI] = nullptr;
		}
	}

	if (m_pFailed) {
		m_pFailed->SetDisappear(true);
		m_pFailed = nullptr;
	}

	// タイムアップ判定をリセット
	m_bTimeUp = false;
}

//============================================================================
// タイムアップ判定を出す
//============================================================================
void CRecord_Dest::SetTimeUp()
{
	m_bTimeUp = true;
}

//============================================================================
// タイムアップ判定取得
//============================================================================
bool CRecord_Dest::GetTimeUp()
{
	return m_bTimeUp;
}

//============================================================================
// 生成
//============================================================================
CRecord_Dest* CRecord_Dest::Create()
{
	// インスタンスを生成
	CRecord_Dest* pRecord{ DBG_NEW CRecord_Dest() };

	if (pRecord == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pRecord->SetType(TYPE::RECORD);

	// 初期設定
	pRecord->Init();

	return pRecord;
}

//============================================================================
// 破壊記録の増加
//============================================================================
void CRecord_Dest::AddDest()
{
	// 破壊記録を取得
	CObject* pFind{ CObject::FindObject(CObject::TYPE::RECORD) };
	CRecord_Dest* pRecord{ CUtility::GetInstance()->DownCast<CRecord_Dest, CObject>(pFind) };

	// 増加
	pRecord->m_nCntDest++;

	// 表示拡大率
	float fScaleCoeff{ 1.2f };

	// 表示が拡大
	pRecord->m_pDestText->SetSize({ 140.0f * fScaleCoeff, 30.0f * fScaleCoeff, 0.0f });

	// 設定用共通情報
	D3DXVECTOR3 CopyPos{ pRecord->m_pDestText->GetPos() };
	float fSizeX{ 42.5f * fScaleCoeff };	// 共通横サイズ

	// 数字を広く並べる
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 中心座標から、相対的な先頭の位置を設定
		CopyPos.x = pRecord->m_pDestText->GetPos().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f) + (210.0f * fScaleCoeff);

		// 先頭座標から数字が並ぶように調整
		CopyPos.x += -fSizeX * nCntNum;
		pRecord->m_apDestNum[nCntNum]->SetPos(CopyPos);

		// 数字のサイズを設定
		pRecord->m_apDestNum[nCntNum]->SetSize({ fSizeX, 30.0f * fScaleCoeff, 0.0f });
	}
}

//============================================================================
// 破壊記録の書き出し
//============================================================================
void CRecord_Dest::ExportRecord()
{
	// テキストを行ごとに保持する
	std::vector<std::string> vStr;

	// レベルファイルを展開
	std::ifstream Import{ "Data\\TXT\\dest_record.txt" };

	if (!Import)
	{ // 展開失敗
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("【警告】破壊記録に失敗しました", 300);
#endif	// _DEBUG

		return;
#endif
	}

	// テキストを格納
	std::string str;

	// ファイルを一行ずつ、情報を全て取得する
	while (std::getline(Import, str))
	{
		vStr.push_back(str);
	}

	// ファイルを閉じる
	Import.close();

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	// 破壊記録を取得
	CObject* pFind{ CObject::FindObject(CObject::TYPE::RECORD) };
	CRecord_Dest* pRecord{ CUtility::GetInstance()->DownCast<CRecord_Dest, CObject>(pFind) };

	// ベスト情報を抜き出す
	int nBest{ std::stoi(vStr.front().substr(vStr.front().find("b") + 2, vStr.front().find(","))) };

	// ベスト情報とラスト情報を比べる
	if (pRecord->m_nCntDest > nBest)
	{
		// ベストを上回っていたなら更新
		nBest = pRecord->m_nCntDest;
	}

	// ラスト情報を書き換える
	vStr.front() = "b:" + std::to_string(nBest) + ",";

	// レベルファイルを展開
	std::ofstream Export{ "Data\\TXT\\dest_record.txt" };

	if (!Export)
	{ // 展開失敗
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("【警告】破壊記録の書き出しに失敗しました", 300);
#endif	// _DEBUG

		return;
#endif
	}

	// 変更を加えた情報でもとのファイルを更新する
	for (auto&& it : vStr)
	{
		Export << it.c_str() << std::endl;
	}

	// ファイルを閉じる
	Export.close();
}

//============================================================================
// 破壊記録の読み込み
//============================================================================
int CRecord_Dest::ImportBestRecord()
{
	// 破壊記録ファイルを展開
	std::ifstream Import{ "Data\\TXT\\dest_record.txt" };

	if (!Import)
	{ // 展開失敗
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("破壊記録の読み込みに失敗しました", 300);
#endif	// _DEBUG

		return 0;
#endif
	}

	// 文章格納先
	std::string str{ };

	// テキストを読み取る
	std::getline(Import, str);

	// ファイルのベスト部分を抽出
	std::string best = str.substr(str.find("b:") + 2, str.find(","));

	// 整数値に変換
	return std::stoi(best);
}

//============================================================================
// 出現
//============================================================================
void CRecord_Dest::Appear()
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
void CRecord_Dest::Disappear()
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