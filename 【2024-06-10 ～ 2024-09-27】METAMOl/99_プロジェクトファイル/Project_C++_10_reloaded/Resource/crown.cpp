//=============================================================================
//
// 王冠 [crown.cpp]
// Author : 福田歩希
//
//=============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "crown.h"
#include "utility.h"

// テクスチャ取得用
#include "texture_manager.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CCrown::CCrown() :
	CObject_UI{ static_cast<int>(LAYER::UI) }
{
	// 出現予約
	SetAppear(true);
}

//============================================================================
// デストラクタ
//============================================================================
CCrown::~CCrown()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CCrown::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_UI::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CCrown::Uninit()
{
	// 基底クラスの終了処理
	CObject_UI::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CCrown::Update()
{
	// 目標座標へ
	SetPos(CUtility::GetInstance()->AdjustToTarget(GetPos(), GetPosTarget(), 0.065f));

	// 目標向きへ
	SetRot(CUtility::GetInstance()->AdjustToTarget(GetRot(), GetRotTarget(), 0.05f));

	// 目標サイズへ
	SetSize(CUtility::GetInstance()->AdjustToTarget(GetSize(), GetSizeTarget(), 0.05f));

	// 基底クラスの更新
	CObject_UI::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CCrown::Draw()
{
	// 基底クラスの描画処理
	CObject_UI::Draw();
}

//============================================================================
// 生成
//============================================================================
CCrown* CCrown::Create()
{
	// インスタンスを生成
	CCrown* pCrown = DBG_NEW CCrown{};

	if (pCrown == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pCrown->SetType(TYPE::NONE);

	// 基底クラスの初期設定
	pCrown->Init();

	// ランダムな座標を設定
	pCrown->SetPos({ (SCREEN_WIDTH * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					(SCREEN_HEIGHT * 0.5f) + CUtility::GetInstance()->GetRandomValue<float>() * 10.0f,
					0.0f });

	// サイズの設定
	pCrown->SetSize({ 0.0f, 0.0f, 0.0f });

	// テクスチャを設定
	pCrown->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::CROWN));

	// UIオブジェクトにダウンキャスト
	CObject_UI* pObjUI = CUtility::GetInstance()->DownCast<CObject_UI, CObject>(pCrown);

	// アルファ値を設定
	pObjUI->SetAlpha(0.0f);

	return pCrown;
}

//============================================================================
// 出現
//============================================================================
void CCrown::Appear()
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
void CCrown::Disappear()
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