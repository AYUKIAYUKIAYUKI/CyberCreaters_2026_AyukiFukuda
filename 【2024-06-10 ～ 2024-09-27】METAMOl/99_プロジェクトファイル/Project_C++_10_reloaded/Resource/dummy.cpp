//============================================================================
// 
// ダミー [dummy.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "dummy.h"

// キーボード取得用
#include "manager.h"

// デバッグ表示用
#include "renderer.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CDummy::CDummy() :
	CObject_X{ static_cast<int>(LAYER::FRONT) }	// 描画優先度を指定
{

}

//============================================================================
// デストラクタ
//============================================================================
CDummy::~CDummy()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CDummy::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CDummy::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CDummy::Update()
{
	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CDummy::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 操作
//============================================================================
void CDummy::Control()
{
	// 移動
	Translate();

#ifdef _DEBUG
	// 位置をデバッグ表示
	CRenderer::GetInstance()->SetDebugString("【ダミー位置】");
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(1) << "X:" << GetPos().x << "\nY:" << GetPos().y;
	CRenderer::GetInstance()->SetDebugString(oss.str().c_str());
#endif	// _DEBUG
}

//============================================================================
// モデルを変更
//============================================================================
void CDummy::ChangeModel(int nPattern)
{
	switch (nPattern)
	{
	case -1:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::CURSOR));
		break;

	case 0:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::BLOCK_000));
		break;

	case 1:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::DESTRUCTIBLE));
		break;

	case 2:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::DEST_BIG));
		break;

	case 3:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::SPIKES));
		break;

	case 4:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::SPIKES_MOVE));
		break;

	case 5:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::ENEMY));
		break;

	case 6:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::START));
		break;

	case 7:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::GOAL));
		break;

	case 8:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::ACHIEVE));
		break;

	case 9:
		BindModel(CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::BARRIER_ANCHOR));
		break;

	default:
		assert(false);
		break;
	}
}

//============================================================================
// 生成
//============================================================================
CDummy* CDummy::Create()
{
	// インスタンスを生成
	CDummy* pDummy = DBG_NEW CDummy{};

	if (pDummy == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pDummy->SetType(TYPE::DUMMY);

	// 基底クラスの初期設定
	pDummy->Init();
	
	// アルファ値の設定
	pDummy->SetAlpha(0.5f);

	return pDummy;
}

//============================================================================
// 移動
//============================================================================
void CDummy::Translate()
{
	// 位置を取得
	D3DXVECTOR3 pos = GetPos();

	if (CManager::GetKeyboard()->GetPress(DIK_RSHIFT))
	{
		// Y軸方向に移動
		if (CManager::GetKeyboard()->GetPress(DIK_W))
		{
			pos.y += 5.0f;
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_S))
		{
			pos.y += -5.0f;
		}

		// X方向に移動
		if (CManager::GetKeyboard()->GetPress(DIK_A))
		{
			pos.x += -5.0f;
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_D))
		{
			pos.x += 5.0f;
		}
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_RCONTROL))
	{
		// Y軸方向にグリッド移動
		if (CManager::GetKeyboard()->GetTrigger(DIK_W))
		{
			pos.y += 20.0f;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_S))
		{
			pos.y += -20.0f;
		}

		// X方向にグリッド移動
		if (CManager::GetKeyboard()->GetTrigger(DIK_A))
		{
			pos.x += -20.0f;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_D))
		{
			pos.x += 20.0f;
		}
	}
	else
	{
		// Y軸方向にグリッド移動
		if (CManager::GetKeyboard()->GetTrigger(DIK_W))
		{
			pos.y += 5.0f;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_S))
		{
			pos.y += -5.0f;
		}

		// X方向にグリッド移動
		if (CManager::GetKeyboard()->GetTrigger(DIK_A))
		{
			pos.x += -5.0f;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_D))
		{
			pos.x += 5.0f;
		}
	}

	// 最終的な位置を反映
	SetPos(pos);
}