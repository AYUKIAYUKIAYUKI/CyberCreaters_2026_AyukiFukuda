//============================================================================
// 
// アチーブ [achievement.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "achievement.h"
#include "utility.h"

// ステージ情報取得用
#include "game_manager.h"

// シーン情報取得用
#include "manager.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CAchieve::CAchieve() :
	CObject_X{ static_cast<int>(LAYER::MIDDLE) }	// 描画優先度を指定
{

}

//============================================================================
// プライオリティ指定コンストラクタ
//============================================================================
CAchieve::CAchieve(LAYER priority) :
	CObject_X{ static_cast<int>(priority) }	// 描画優先度を指定
{

}

//============================================================================
// デストラクタ
//============================================================================
CAchieve::~CAchieve()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CAchieve::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CAchieve::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CAchieve::Update()
{
	// 回転
	D3DXVECTOR3 rotTarget =  GetRot();
	rotTarget.y += 0.05f;
	SetRot(rotTarget);

	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CAchieve::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 生成
//============================================================================
CAchieve* CAchieve::Create(D3DXVECTOR3 pos)
{
	// インスタンスを生成
	CAchieve* pAchieve = DBG_NEW CAchieve{};

	if (pAchieve == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pAchieve->SetType(TYPE::ACHIEVE);

	// 基底クラスの初期設定
	pAchieve->Init();

	// 位置の設定
	pAchieve->SetPos(pos);

	// モデルの種類を設定
	CModel_X_Manager::TYPE Type{ CModel_X_Manager::TYPE::ACHIEVE };

	if (CManager::GetScene()->GetMode() == CScene::MODE::GAME)
	{
		// 現在選択しているレベルを取得
		int nSelectLevel{ CGameManager::GetInstance()->GetSelectLevel() };

		// アチーブメントの回収状態を取得
		std::vector<bool> vbCollectAchieve{ CGameManager::GetInstance()->GetCollectAchieve() };

		// このレベルのアチーブメントを回収していたら
		if (vbCollectAchieve.size() > 0)
		{
			if (vbCollectAchieve[nSelectLevel])
			{
				// 取得後モデルを設定
				Type = CModel_X_Manager::TYPE::ACHIEVE_LOST;
			}
		}
	}

	// モデルを取得
	auto Model{ CModel_X_Manager::GetInstance()->GetModel(Type) };

	// モデルを設定
	pAchieve->BindModel(Model);

	// サイズを設定
	pAchieve->SetSize(D3DXVECTOR3{ 10.0f, 10.0f, 0.0f });

	// 描画される前に一度更新しておく
	pAchieve->Update();

	return pAchieve;
}