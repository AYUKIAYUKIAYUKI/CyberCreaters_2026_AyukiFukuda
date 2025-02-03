//============================================================================
// 
// バリアマネージャー [barrier_manager.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "barrier_manager.h"
#include "utility.h"

// デバッグ表示用
#include "renderer.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
float CBarrier_Manager::m_fCurrentMinPosY = 0.0f;	// 現在のバリアの最も低い座標

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CBarrier_Manager::CBarrier_Manager()
{

}

//============================================================================
// デストラクタ
//============================================================================
CBarrier_Manager::~CBarrier_Manager()
{

}

//============================================================================
// ステージにバリアを生成する
//============================================================================
void CBarrier_Manager::CreateStageBarrier()
{
	// バリアの最も低い座標をリセット
	m_fCurrentMinPosY = 0.0f;

	// バリアアンカータグをすべて取得
	CObject** pObject{ CObject::FindAllObject(CObject::TYPE::BARRIER_ANCHOR) };

	// バリアアンカーのポインタ
	CBarrier_Anchor* pAnchor[2] = { nullptr, nullptr };

	// オブジェクト数をカウント
	int nCntObj{ 0 };

	for (nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// バリアアンカーへダウンキャスト
		pAnchor[nCntObj] = CUtility::GetInstance()->DownCast<CBarrier_Anchor, CObject>(pObject[nCntObj]);
	}

	// バリアアンカーの不足
	if (nCntObj < 2)
	{
#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("【バリアアンカーの数が不足しています！】", 120);
#endif // _DEBUG
		return;
	}

	// 2つの座標の延長線上の交点にさらにアンカーをさらに2つ作成する
	CBarrier_Anchor::Create(D3DXVECTOR3{ pAnchor[0]->GetPos().x, pAnchor[1]->GetPos().y, 0.0f });
	CBarrier_Anchor::Create(D3DXVECTOR3{ pAnchor[1]->GetPos().x, pAnchor[0]->GetPos().y, 0.0f });

	// 4つの座標を頂点とする矩形の辺を描くようにバリアを生成する
	float fBeginX{ 0.0f }, fBeginY{ 0.0f }, fEndX{ 0.0f }, fEndY{ 0.0f };

	// 数値の小さい方から大きい方めがけてラインを引くため、始点と終点を決める
	if (pAnchor[0]->GetPos().x < pAnchor[1]->GetPos().x)
	{
		fBeginX = pAnchor[0]->GetPos().x;
		fEndX = pAnchor[1]->GetPos().x;
	}
	else
	{
		fBeginX = pAnchor[1]->GetPos().x;
		fEndX = pAnchor[0]->GetPos().x;
	}

	// 同上
	if (pAnchor[0]->GetPos().y < pAnchor[1]->GetPos().y)
	{
		fBeginY = pAnchor[0]->GetPos().y;
		fEndY = pAnchor[1]->GetPos().y;

		// バリアの最も低い座標を保存しておく
		m_fCurrentMinPosY = pAnchor[0]->GetPos().y;
	}
	else
	{
		fBeginY = pAnchor[1]->GetPos().y;
		fEndY = pAnchor[0]->GetPos().y;

		// バリアの最も低い座標を保存しておく
		m_fCurrentMinPosY = pAnchor[1]->GetPos().y;
	}

	// 横のラインを2本引く
	while (fBeginX <= fEndX)
	{
		for (int nCntAnchor = 0; nCntAnchor < 2; nCntAnchor++)
		{
			CBarrier::Create(D3DXVECTOR3{ fBeginX, pAnchor[nCntAnchor]->GetPos().y, 0.0f }, D3DXVECTOR3{ 0.0f, 0.0f, D3DX_PI * 0.5f });
		}

		fBeginX += 20.0f;
	}

	// 縦のラインを2本引く
	while (fBeginY <= fEndY)
	{
		for (int nCntAnchor = 0; nCntAnchor < 2; nCntAnchor++)
		{
			CBarrier::Create(D3DXVECTOR3{ pAnchor[nCntAnchor]->GetPos().x, fBeginY, 0.0f }, D3DXVECTOR3{ 0.0f, 0.0f, 0.0f });
		}

		fBeginY += 20.0f;
	}
}

//============================================================================
// 現在のバリアの最も低い座標を取得
//============================================================================
float CBarrier_Manager::GetCurrentMinPosY()
{
	return m_fCurrentMinPosY;
}