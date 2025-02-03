//=============================================================================
//
// マス目 [square.cpp]
// Author : 福田歩希
//
//=============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "square.h"
#include "utility.h"

// ステージ数取得用
#include "game_manager.h"

// テクスチャ取得用
#include "texture_manager.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CSquare::CSquare() :
	CObject_UI{ static_cast<int>(LAYER::UI) },
	m_pCrown{ nullptr }
{
	// 数字を生成
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 数字のポインタを初期化
		m_apNumber[nCntNum] = nullptr;
	
		m_apNumber[nCntNum] = CNumber::Create();

		// 向きの設定
		m_apNumber[nCntNum]->SetRot({ 0.0f, 0.0f, D3DX_PI * 10.0f });

		// 目標サイズの設定
		m_apNumber[nCntNum]->SetSizeTarget({ 25.0f, 20.0f, 0.0f });

		// 数字の出現予約
		m_apNumber[nCntNum]->SetAppear(true);
	}

	// 出現予約
	SetAppear(true);
}

//============================================================================
// デストラクタ
//============================================================================
CSquare::~CSquare()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CSquare::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CSquare::Uninit()
{
	// 基底クラスの終了処理
	CObject_UI::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CSquare::Update()
{
	// 目標座標へ
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), GetPosTarget(), 0.065f));

	// 目標向きへ
	SetRot(CUtility::GetInstance()->AdjustToTarget(GetRot(), GetRotTarget(), 0.05f));

	// 目標サイズへ
	SetSize(CUtility::GetInstance()->AdjustToTarget(GetSize(), GetSizeTarget(), 0.03f));

	// 基底クラスの更新
	CObject_UI::Update();

	//////////////////////////////////////////////////
	//////////////////////////////////////////////////

	// 数字のみ
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// 目標座標へ
		m_apNumber[nCntNum]->SetPos(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetPos(), m_apNumber[nCntNum]->GetPosTarget(), 0.065f));
	
		// 目標向きへ
		m_apNumber[nCntNum]->SetRot(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetRot(), m_apNumber[nCntNum]->GetRotTarget(), 0.1f));

		// 目標サイズへ
		m_apNumber[nCntNum]->SetSize(CUtility::GetInstance()->AdjustToTarget(m_apNumber[nCntNum]->GetSize(), m_apNumber[nCntNum]->GetSizeTarget(), 0.03f));
	}
}

//============================================================================
// 描画処理
//============================================================================
void CSquare::Draw()
{
	// 基底クラスの描画処理
	CObject_UI::Draw();
}

//============================================================================
// マス目を動作
//============================================================================
void CSquare::ControlAll(int nSelect)
{
	// マス目タグのオブジェクトを全て取得
	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);

	// マス数カウント
	/* 終了マスの追加により、カウントは1つ手前の範囲から行う*/
	int nSquareCnt{ -1 };

	// オブジェクトがなくなるまで
	while (pObj[nSquareCnt + 1])
	{
		// マス目クラスへダウンキャスト
		CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt + 1]);

		// 新規座標情報
		D3DXVECTOR3 posNew{ 0.0f, 0.0f, 0.0f };

		// 新規向き情報
		D3DXVECTOR3 rotNew{ 0.0f, 0.0f, 0.0f };

		// 新規サイズ情報
		D3DXVECTOR3 sizeNew{ 0.0f, 0.0f, 0.0f };

		if (nSquareCnt == nSelect)
		{ // 選択しているマスを拡大

			posNew = {
				(SCREEN_WIDTH * 0.5f),
				(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f,
				0.0f };

			rotNew = { 0.0f, 0.0f, D3DX_PI };

			sizeNew = { 60.0f, 60.0f, 0.0f };
		}
		else
		{ // 通常マスを縮小

			posNew = { 
				(SCREEN_WIDTH * 0.5f) + (150.0f * (nSquareCnt)) - (nSelect * 150.0f),
				SCREEN_HEIGHT * 0.75f + CUtility::GetInstance()->GetRandomValue<float>() * 0.2f,
				0.0f };

			sizeNew = { 40.0f, 40.0f, 0.0f };
		}

		// 目標座標を新しいものに
		pSquare->SetPosTarget(posNew);

		// 目標向きを新しいものに
		pSquare->SetRotTarget(rotNew);

		// 目標サイズを新しいものに
		pSquare->SetSizeTarget(sizeNew);
		
		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////

		// カウント数のコピー
		int nCopy{ nSquareCnt + 1 };

		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			// 新しいサイズを作成
			sizeNew = { 0.0f, 0.0f, 0.0f };

			if (nSquareCnt == -1 || nSquareCnt == CGameManager::GetInstance()->GetMaxStage())
			{ // 終了マスの数字を表示しない
				sizeNew = { 0.0f, 0.0f, 0.0f };
			}
			else if (nSquareCnt == nSelect)
			{ // 選択しているマスの数字を拡大
				sizeNew = { 37.5f, 30.0f, 0.0f };
			}
			else
			{ // 通常マスの数字を縮小
				sizeNew = { 25.0f, 20.0f, 0.0f };
			}

			// 中心座標から、相対的な先頭の位置を設定
			posNew.x = pSquare->GetPosTarget().x + (sizeNew.x * MAX_DIGIT * 0.5f) - (sizeNew.x * 0.5f);

			// 先頭座標から数字が並ぶように調整
			posNew.x += -sizeNew.x * nCntNum;
			pSquare->m_apNumber[nCntNum]->SetPosTarget(posNew);

			// 目標サイズを設定
			pSquare->m_apNumber[nCntNum]->SetSizeTarget(sizeNew);

			// 数字を設定
			pSquare->m_apNumber[nCntNum]->SetNumber(nCopy % 10);

			// 桁を減らす
			nCopy /= 10;
		}

		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////

		if (nSquareCnt == -1 || nSquareCnt == CGameManager::GetInstance()->GetMaxStage())
		{
			nSquareCnt++;
			continue;
		}

		if (!pSquare->m_pCrown)
		{ // 王冠が作成されていなければ

			// 新規作成
			pSquare->m_pCrown = CCrown::Create();

			// アチーブ回収状態を取得
			std::vector<bool> CollectAchieve{ CGameManager::GetInstance()->GetCollectAchieve() };
	
			// どんな王冠を付けるのか判定
			if (CollectAchieve[nSquareCnt])
			{ // アチーブを取得している

				// 好みの色に
				pSquare->m_pCrown->SetCol(D3DXCOLOR{ 1.0f, 1.0f, 1.0f, pSquare->m_pCrown->GetAlpha() });
			}
			else
			{ // アチーブを取得していない

				// 黒っぽく
				pSquare->m_pCrown->SetCol(D3DXCOLOR{ 0.15f, 0.15f, 0.15f, pSquare->m_pCrown->GetAlpha() });
			}

			// 出現設定
			pSquare->m_pCrown->SetAppear(true);
		}
		else
		{
			if (nSelect == nSquareCnt)
			{
				// 目標向きを設定
				pSquare->m_pCrown->SetRotTarget(D3DXVECTOR3{ 0.0f, 0.0f, D3DX_PI * -4.0f });

				// 目標座標を設定
				D3DXVECTOR3 NewPosTarget{ pSquare->GetPosTarget() };
				NewPosTarget.y += -100.0f;
				pSquare->m_pCrown->SetPosTarget(NewPosTarget);

				// 目標サイズを設定
				pSquare->m_pCrown->SetSizeTarget(D3DXVECTOR3{ 35.0f, 35.0f, 0.0f });
			}
			else
			{
				// 目標向きを設定
				pSquare->m_pCrown->SetRotTarget(D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });

				// 目標座標を設定
				D3DXVECTOR3 NewPosTarget{ pSquare->GetPosTarget() };
				NewPosTarget.y += -75.0f;
				pSquare->m_pCrown->SetPosTarget(NewPosTarget);

				// 目標サイズを設定
				pSquare->m_pCrown->SetSizeTarget(D3DXVECTOR3{ 20.0f, 20.0f, 0.0f });
			}
		}

		// 次へ進める
		nSquareCnt++;
	}
}

//============================================================================
// マス目を一斉消去
//============================================================================
void CSquare::SetDisappearAll()
{
	// マス目タグのオブジェクトを全て取得
	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);

	// マス数カウント
	int nSquareCnt{ 0 };

	// オブジェクトがなくなるまで
	while (pObj[nSquareCnt])
	{
		// マス目クラスへダウンキャスト
		CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt]);

		// 目標向きを設定
		pSquare->SetRotTarget({ 0.0f, 0.0f, -D3DX_PI * 3.0f });

		// 目標サイズを設定
		pSquare->SetSizeTarget(pSquare->GetSize() * 3.0f);

		// 消去予約
		pSquare->SetDisappear(true);

		/////////////////////////////////////////////////////
		/////////////////////////////////////////////////////

		// 数字を消去予約
		pSquare->DisappearNumber();

		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////
		
		if (pSquare->m_pCrown)
		{ // 王冠が作成されていれば
			
			// 目標座標を設定
			D3DXVECTOR3 NewPos{ pSquare->m_pCrown->GetPos() };
			NewPos.y = SCREEN_HEIGHT;
			pSquare->m_pCrown->SetPosTarget(NewPos);
			
			// 消去予約
			pSquare->m_pCrown->SetDisappear(true);
		}

		nSquareCnt++;
	}
}

////============================================================================
//// マス目を即座に一斉消去予約
////============================================================================
//void CSquare::InstantDisappearAll()
//{
//	// マス目タグのオブジェクトを全て取得
//	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);
//
//	// マス数カウント
//	int nSquareCnt{ 0 };
//
//	// オブジェクトがなくなるまで
//	while (pObj[nSquareCnt])
//	{
//		// マス目クラスへダウンキャスト
//		CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt]);
//
//		// 破棄予約
//		pSquare->Release();
//
//		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
//		{
//			// 破棄予約
//			pSquare->m_apNumber[nCntNum]->Release();
//		}
//
//		nSquareCnt++;
//	}
//}

////============================================================================
//// マス目を並べる (不必要)
////============================================================================
//void CSquare::LineUpAll(int nSelect)
//{
//	// マス目タグのオブジェクトを全て取得
//	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);
//
//	// マス数カウント
//	int nSquareCnt{ 0 };
//
//	// オブジェクトがなくなるまで
//	while (pObj[nSquareCnt])
//	{
//		// マス目クラスにダウンキャスト
//		CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt]);
//
//		// 目標座標を設定
//		pSquare->SetPosTarget({ (SCREEN_WIDTH * 0.5f) + (150.0f * nSquareCnt) - (nSelect * 150.0f), SCREEN_HEIGHT * 0.5f, 0.0f });
//
//		// 次へ進める
//		nSquareCnt++;
//	}
//}

//============================================================================
// 先頭・末尾の色を設定する
//============================================================================
void CSquare::SetColorFrontAndBack()
{
	// マス目タグのオブジェクトを全て取得
	CObject** pObj = CObject::FindAllObject(CObject::TYPE::SQUARE);

	// マス数カウント
	/* 終了マスの追加により、カウントは1つ手前の範囲から行う*/
	int nSquareCnt{ -1 };

	// オブジェクトがなくなるまで
	while (pObj[nSquareCnt + 1])
	{
		if (nSquareCnt == -1 || nSquareCnt == CGameManager::GetInstance()->GetMaxStage())
		{ // 先頭・末尾のオブジェクトのみ
			
			// マス目クラスへダウンキャスト
			CSquare* pSquare = CUtility::GetInstance()->DownCast<CSquare, CObject>(pObj[nSquareCnt + 1]);

			// 好きな色に
			pSquare->SetCol(D3DXCOLOR{ 0.0f, 1.0f, 1.0f, 0.0f });
		}

		nSquareCnt++;
	}
}

//============================================================================
// 生成
//============================================================================
CSquare* CSquare::Create()
{
	// インスタンスを生成
	CSquare* pSquare = DBG_NEW CSquare{};

	if (pSquare == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pSquare->SetType(TYPE::SQUARE);

	// 基底クラスの初期設定
	pSquare->Init();

	// ランダムな座標を設定
	pSquare->SetPos({ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					0.0f });

	// サイズの設定
	pSquare->SetSize({ 0.0f, 0.0f, 0.0f });

	// テクスチャを設定
	pSquare->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::SQUARE_00));

	// UIオブジェクトにダウンキャスト
	CObject_UI* pObjUI = CUtility::GetInstance()->DownCast<CObject_UI, CObject>(pSquare);

	// アルファ値を設定
	pObjUI->SetAlpha(0.0f);

	return pSquare;
}

//============================================================================
// 出現
//============================================================================
void CSquare::Appear()
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
void CSquare::Disappear()
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
// 数字を消去
//============================================================================
void CSquare::DisappearNumber()
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		// ランダムな座標
		D3DXVECTOR3 pos{ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 1.5f, (SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 1.5f, 0.0f };

		// 数字の目標座標を設定
		m_apNumber[nCntNum]->SetPosTarget(pos);

		// 数字の目標向きを設定
		m_apNumber[nCntNum]->SetRotTarget({ 0.0f, 0.0f, -D3DX_PI * 2.0f });

		// 数字の目標サイズを設定
		m_apNumber[nCntNum]->SetSizeTarget({ 0.0f, 0.0f, 0.0f });
	
		// 消去予約
		m_apNumber[nCntNum]->SetDisappear(true);
	}
}