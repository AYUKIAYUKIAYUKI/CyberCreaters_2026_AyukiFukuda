//============================================================================
// 
// とげ移動ブロック [block_spikes_move.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "block_spikes_move.h"
#include "utility.h"

// デバッグ表示
#include "renderer.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CBlockSpikesMove::CBlockSpikesMove() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) },
	m_posHold{ 0.0f, 0.0f, 0.0f },
	m_fAngle{ 0.0f },
	m_fAdder{ 0.0f },
	m_fCoeff{ 0.0f }
{

}

//============================================================================
// プライオリティ指定コンストラクタ
//============================================================================
CBlockSpikesMove::CBlockSpikesMove(LAYER priority) :
	CObject_X{ static_cast<int>(priority) },
	m_posHold{ 0.0f, 0.0f, 0.0f },
	m_fAngle{ 0.0f },
	m_fAngleInit{ 0.0f },
	m_fAdder{ 0.0f },
	m_fCoeff{ 0.0f }
{

}

//============================================================================
// デストラクタ
//============================================================================
CBlockSpikesMove::~CBlockSpikesMove()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CBlockSpikesMove::Init()
{
	// 初期角度を反映
	m_fAngle = m_fAngleInit;

	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CBlockSpikesMove::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CBlockSpikesMove::Update()
{
	// 移動
	Translate();

	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CBlockSpikesMove::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// ホールド座標を設定
//============================================================================
void CBlockSpikesMove::SetPosHold(D3DXVECTOR3 pos)
{
	m_posHold = pos;
}

//============================================================================
// ホールド座標を取得
//============================================================================
D3DXVECTOR3 CBlockSpikesMove::GetPosHold()
{
	return m_posHold;
}

//============================================================================
// 初期角度の取得
//============================================================================
float CBlockSpikesMove::GetAngleInit()
{
	return m_fAngleInit;
}

//============================================================================
// 初期角度の設定
//============================================================================
void CBlockSpikesMove::SetAngleInit(float fAngleInit)
{
	m_fAngleInit = fAngleInit;
}

//============================================================================
// 角度の取得
//============================================================================
float CBlockSpikesMove::GetAngle()
{
	return m_fAngle;
}

//============================================================================
// 角度の設定
//============================================================================
void CBlockSpikesMove::SetAngle(float fAngle)
{
	m_fAngle = fAngle;
}


//============================================================================
// 増加量の取得
//============================================================================
float CBlockSpikesMove::GetAdder()
{
	return m_fAdder;
}

//============================================================================
// 増加量の設定
//============================================================================
void CBlockSpikesMove::SetAdder(float fAdder)
{
	m_fAdder = fAdder;
}

//============================================================================
// 反映係数の取得
//============================================================================
float CBlockSpikesMove::GetCoeff()
{
	return m_fCoeff;
}

//============================================================================
// 反映係数の設定
//============================================================================
void CBlockSpikesMove::SetCoeff(float fCoeff)
{
	m_fCoeff = fCoeff;
}

//============================================================================
// 生成
//============================================================================
CBlockSpikesMove* CBlockSpikesMove::Create(D3DXVECTOR3 pos, float fAngle, float fAdder, float fCoeff)
{
	// インスタンスを生成
	CBlockSpikesMove* pBlockSpikesMove = DBG_NEW CBlockSpikesMove{ LAYER::MIDDLE };

	if (pBlockSpikesMove == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pBlockSpikesMove->SetType(TYPE::SPIKES_MOVE);

	// ホールド座標の設定 (先行)
	pBlockSpikesMove->SetPosHold(pos);

	// 初期角度の設定 (設定)
	pBlockSpikesMove->SetAngleInit(fAngle);

	// 増加量の設定
	pBlockSpikesMove->SetAdder(fAdder);

	// 反映係数の設定
	pBlockSpikesMove->SetCoeff(fCoeff);

	// 基底クラスの初期設定
	pBlockSpikesMove->Init();

	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::SPIKES_MOVE);

	// モデルを設定
	pBlockSpikesMove->BindModel(model);

	// サイズを設定
	pBlockSpikesMove->SetSize(model->size);

	// 描画される前に一度更新しておく
	pBlockSpikesMove->Update();

	return pBlockSpikesMove;
}

//============================================================================
// 移動
//============================================================================
void CBlockSpikesMove::Translate()
{
	// 新しい座標を作成
	D3DXVECTOR3 newPos{ GetPosHold() };

	// 角度を増加
	m_fAngle += m_fAdder;

	if (m_fAngle > D3DX_PI)
	{
		m_fAngle += -D3DX_PI * 2.0f;
	}
	else if (m_fAngle < -D3DX_PI)
	{
		m_fAngle += D3DX_PI * 2.0f;
	}

	// ずらされた座標を基点に弧を描くように移動
	newPos += {
		sinf(m_fAngle) * m_fCoeff,
		cosf(m_fAngle) * m_fCoeff,
		0.0f
	};

#ifdef _DEBUG
	CRenderer::GetInstance()->SetDebugString("移動とげ : " + std::to_string(newPos.x) + " : " + std::to_string(newPos.y) + " : " + std::to_string(m_fAngle));
#endif	// _DEBUG

	// 座標を反映
	SetPos(newPos);
}

//============================================================================
// 角度を一斉リセット
//============================================================================
void CBlockSpikesMove::ResetAngleAll()
{
	// ブロックタイプのオブジェクトをすべて取得
	CObject** pObject = CObject::FindAllObject(CObject::TYPE::SPIKES_MOVE);

	// とげ移動ブロックタイプのオブジェクトをすべて取得
	pObject = CObject::FindAllObject(CObject::TYPE::SPIKES_MOVE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// とげ移動ブロッククラスへダウンキャスト
		CBlockSpikesMove* pSpike_Move = CUtility::GetInstance()->DownCast<CBlockSpikesMove, CObject>(pObject[nCntObj]);

		// 角度をリセット
		pSpike_Move->SetAngle(pSpike_Move->GetAngleInit());
	}
}