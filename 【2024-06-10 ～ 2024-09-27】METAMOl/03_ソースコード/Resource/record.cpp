//=============================================================================
//
// レコード [record.cpp]
// Author : 福田歩希
//
//=============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "record.h"
#include "utility.h"

// デバッグ表示用
#include "renderer.h"

// テクスチャ取得用
#include "texture_manager.h"

// マス目情報取得用
#include "square.h"
#include "game_manager.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CRecord::CRecord() :
	CObject_UI{ static_cast<int>(LAYER::UI) },
	m_pText{ nullptr }
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 数字情報のポインタを初期化
		m_apNumber[nCntNum] = nullptr;

		// 数字を生成
		m_apNumber[nCntNum] = CNumber::Create();

		// ランダムな座標
		D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 5.0f, (SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 5.0f, 0.0f };

		// 初期座標の設定
		m_apNumber[nCntNum]->SetPos(pos);

		// 初期向きの設定
		m_apNumber[nCntNum]->SetRot({ 0.0f, 0.0f, CUtility::GetInstance()->GetRandomValue<float>() * 0.5f });

		// 数字の出現予約
		m_apNumber[nCntNum]->SetAppear(true);
	}

	for (int nCntBack = 0; nCntBack < MAX_BACK; nCntBack++)
	{
		// 戻るマーク情報のポインタを初期化
		m_apBack[nCntBack] = nullptr;

		// テキストを生成
		m_apBack[nCntBack] = CText::Create(CTexture_Manager::TYPE::BACK);

		// ランダムな座標
		D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 5.0f, (SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 5.0f, 0.0f };

		// 初期座標の設定
		m_apBack[nCntBack]->SetPos(pos);

		// 初期向きの設定
		m_apBack[nCntBack]->SetRot({ 0.0f, 0.0f, CUtility::GetInstance()->GetRandomValue<float>() * 0.5f });

		// 戻るマークの出現予約
		m_apBack[nCntBack]->SetAppear(true);
	}

	// 出現予約
	SetAppear(true);
}

//============================================================================
// デストラクタ
//============================================================================
CRecord::~CRecord()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CRecord::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CRecord::Uninit()
{
	// 基底クラスの終了処理
	CObject_UI::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CRecord::Update()
{
	// 目標座標を設定し、震わす
	SetPosTarget({ SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.25f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f, 0.0f, });

	// 目標座標へ
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), GetPosTarget(), 0.05f));

	// 基底クラスの更新
	CObject_UI::Update();

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	// 目標座標のコピーを作成
	D3DXVECTOR3 CopyPosTarget{ GetPosTarget() };

	// 共通横サイズを設定
	float fSizeX{ 24.75f };

	// ベストタイムの読み込み
	int nBestTime{ ImportRecord(CGameManager::GetInstance()->GetSelectLevel()) };

	// 数字のみ
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 消去予定でなければ
		if (!m_apNumber[nCntNum]->GetDisappear())
		{
			// 中心座標から、相対的な先頭の位置を設定
			CopyPosTarget.x = GetPosTarget().x + (fSizeX * MAX_DIGIT * 0.5f) - (fSizeX * 0.5f);

			// 先頭座標から数字が並ぶように調整
			CopyPosTarget.x += -fSizeX * nCntNum;
			m_apNumber[nCntNum]->SetPosTarget(CopyPosTarget);

			// 数字の目標サイズを設定
			m_apNumber[nCntNum]->SetSizeTarget({ fSizeX, 17.5f, 0.0f });
		}

		// 目標座標へ
		m_apNumber[nCntNum]->SetPos(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetPos(), m_apNumber[nCntNum]->GetPosTarget(), 0.075f));

		// 目標向きへ
		m_apNumber[nCntNum]->SetRot(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetRot(), m_apNumber[nCntNum]->GetRotTarget(), 0.075f));

		// 目標サイズへ
		m_apNumber[nCntNum]->SetSize(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetSize(), m_apNumber[nCntNum]->GetSizeTarget(), 0.05f));

		// 数字を設定
		m_apNumber[nCntNum]->SetNumber(nBestTime % 10);

		// 桁を減らす
		nBestTime /= 10;
	}

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////

	if (!m_pText)
	{
		// テキストが生成されていなければ生成
		m_pText = CText::Create(CTexture_Manager::TYPE::BESTTIME);

		// 目標サイズを設定
		m_pText->SetSizeTarget({ 159.75f, 22.5f, 0.0f });
	}

	// 消去予定でなければ
	if (!m_pText->GetDisappear())
	{
		// テキストを横に付ける
		CopyPosTarget.x += -195.0f;
		m_pText->SetPosTarget(CopyPosTarget);
	}

	// マス目に戻るマークを並べる
	LayoutBackAtSquare();
}

//============================================================================
// 描画処理
//============================================================================
void CRecord::Draw()
{
	// 基底クラスの描画処理
	CObject_UI::Draw();
}

//============================================================================
// 特殊消去予約
//============================================================================
void CRecord::SetDisappearExtra()
{
	// 本体の消去予約
	SetDisappear(true);

	// 数字の消去予約
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// ランダムな座標
		D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>(), (SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>(), 0.0f };

		// 目標座標の設定
		m_apNumber[nCntNum]->SetPosTarget(pos);

		// 目標向きの設定
		m_apNumber[nCntNum]->SetRotTarget({ 0.0f, 0.0f, CUtility::GetInstance()->GetRandomValue<float>() * 0.1f });

		// 消去予約
		m_apNumber[nCntNum]->SetDisappear(true);
	}

	// 目標座標の設定
	m_pText->SetPosTarget({ SCREEN_WIDTH, 0.0f, 0.0f });

	// 目標サイズの設定
	m_pText->SetSizeTarget({ 0.0f, 0.0f, 0.0f });

	// テキストの消去予約
	m_pText->SetDisappear(true);

	// 戻るマークの消去予約
	for (int nCntBack = 0; nCntBack < MAX_BACK; nCntBack++)
	{
		// ランダムな座標
		D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>(), (SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>(), 0.0f };

		// 目標座標の設定
		m_apBack[nCntBack]->SetPosTarget(pos);

		// 目標向きの設定
		m_apBack[nCntBack]->SetRotTarget({ 0.0f, 0.0f, CUtility::GetInstance()->GetRandomValue<float>() * 0.1f });

		// 消去予約
		m_apBack[nCntBack]->SetDisappear(true);
	}
}

//============================================================================
// 生成
//============================================================================
CRecord* CRecord::Create()
{
	// インスタンスを生成
	CRecord* pRecord = DBG_NEW CRecord{};

	if (pRecord == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pRecord->SetType(TYPE::RECORD);

	// 基底クラスの初期設定
	pRecord->Init();

	// ランダムな座標を設定
	pRecord->SetPos({ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					0.0f });

	// サイズの設定
	pRecord->SetSize({ 0.0f, 0.0f, 0.0f });

	return pRecord;
}

//============================================================================
// 出現
//============================================================================
void CRecord::Appear()
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
void CRecord::Disappear()
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

//============================================================================
// タイムの読み込み
//============================================================================
int CRecord::ImportRecord(int nSelect)
{
	// 有効ステージを選択していない場合は無視
	if (nSelect < 0 || nSelect >= CGameManager::GetInstance()->GetMaxStage())
	{
		return 0;
	}

	// テキストを行ごとに保持する
	std::vector<std::string> vStr{};

	// レベルファイルを展開
	std::ifstream Import{ "Data\\TXT\\level.txt" };

	if (!Import)
	{ // 展開失敗
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("【警告】レベル情報・タイムの読み込み(3)に失敗しました", 300);
#endif	// _DEBUG

		return 0;
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

	// ベストタイム情報を抜き出す
	int nBestTime{ std::stoi(vStr[nSelect].substr(vStr[nSelect].find("b") + 2, vStr[nSelect].find(","))) };

	return nBestTime;
}

//============================================================================
// マス目に戻るマークを並べる
//============================================================================
void CRecord::LayoutBackAtSquare()
{
	// 消去予定なら無視
	if (m_apBack[0]->GetDisappear())
	{
		return;
	}

	// マス目タグのオブジェクトをすべて取得
	CObject** pObject = CObject::FindAllObject(CObject::TYPE::SQUARE);

	for (int nCntObj = -1, nCntBack = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj + 1] == nullptr)
		{
			break;
		}

		// 先頭・末尾のマスのみ
		if (nCntObj == -1 || nCntObj == CGameManager::GetInstance()->GetMaxStage())
		{
			// マス目クラスへダウンキャスト
			CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObject[nCntObj + 1]);

			// マス目と戻るマークの座標を同期
			m_apBack[nCntBack]->SetPosTarget(pSquare->GetPosTarget());

			// 新しい目標サイズを作成
			D3DXVECTOR3 NewSizeTarget{ 0.0f, 0.0f, 0.0f };

			if (nCntObj == CGameManager::GetInstance()->GetSelectLevel())
			{ // このマス目を選択していたら
				NewSizeTarget = { 40.0f, 40.0f, 0.0f };
			}
			else
			{ // 選択されていない
				NewSizeTarget = { 25.0f, 25.0f, 0.0f };
			}
			
			// 新しい目標サイズを反映
			m_apBack[nCntBack]->SetSizeTarget(NewSizeTarget);

			nCntBack++;
		}
	}
}