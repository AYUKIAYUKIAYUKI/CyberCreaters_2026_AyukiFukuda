//============================================================================
// 
// モニター [monitor.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "monitor.h"
#include "utility.h"

// モニター画面描画用
#include "renderer.h"

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CMonitor::CMonitor() :
	CObject_X{ static_cast<int>(LAYER::BG) },	// 描画優先度を指定
	m_velocity{ 0.0f, 0.0f, 0.0f },				// 加速度
	m_bAppear{ false }							// 出現フラグ
{

}

//============================================================================
// デストラクタ
//============================================================================
CMonitor::~CMonitor()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CMonitor::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_X::Init();

	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::MONITOR);

	// モニターの画面部分に疑似スクリーンを描画する
	//model->ppTex[1] = CFakeScreen::GetInstance()->GetTexture();
	model->ppTex[0] = CRenderer::GetInstance()->GetTexture();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CMonitor::Uninit()
{
	// 基底クラスの終了処理
	CObject_X::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CMonitor::Update()
{
	//if (!m_bAppear)
	//{
	//	// 出現
	//	m_bAppear = Appear();
	//}

	// 基底クラスの更新
	CObject_X::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CMonitor::Draw()
{
	// 基底クラスの描画処理
	CObject_X::Draw();
}

//============================================================================
// 生成
//============================================================================
CMonitor* CMonitor::Create()
{
	// インスタンスを生成
	CMonitor* pMonitor = DBG_NEW CMonitor;

	if (pMonitor == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pMonitor->SetType(TYPE::NONE);

	// 基底クラスの初期設定
	pMonitor->Init();

	// 座標の設定
	pMonitor->SetPos({ 0.0f, 0.0f, 0.0f });

	// モデルを取得
	auto model = CModel_X_Manager::GetInstance()->GetModel(CModel_X_Manager::TYPE::MONITOR);

	// モデルを設定
	pMonitor->BindModel(model);

	// サイズを設定
	pMonitor->SetSize(model->size);

	// 描画される前に一度更新しておく
	pMonitor->Update();

	return pMonitor;
}

//============================================================================
// 出現
//============================================================================
bool CMonitor::Appear()
{
	// 重力加速
	m_velocity.y += -0.2f;
	//m_velocity.y *= 1.01f;
	
	// 座標を変更
	D3DXVECTOR3 posTarget = GetPos();
	posTarget += m_velocity;
	SetPos(posTarget);

	if (posTarget.y < 0.0f)
	{
		// 座標と加速度をリセット
		m_velocity = Recoil();
		//posTarget.y = 0.0f;

		// 座標を反映
		//SetPos(posTarget);
	
		// 出現終了
		//return true;
	}

	return false;
}

//============================================================================
// 反動
//============================================================================
D3DXVECTOR3 CMonitor::Recoil()
{
	// 落下方向の角度を算出
	float fDropAngle = atan2f(m_velocity.x, m_velocity.y);

#ifdef _DEBUG
	CRenderer::GetInstance()->SetTimeString("てすと" + std::to_string(fDropAngle), 800);
#endif	// _DEBUG

	// 反動の加速度を保持
	D3DXVECTOR3 recoilVelocity{ 0.0f, 0.0f, 0.0f };

	// 反動の加速度を算出
	//recoilVelocity.x = -sinf(fDropAngle) * 2.0f;
	recoilVelocity.y = -cosf(fDropAngle) * 4.0f;

#ifdef _DEBUG
	//CRenderer::GetInstance()->SetTimeString("さいん" + std::to_string(recoilVelocity.x), 800);
	CRenderer::GetInstance()->SetTimeString("こさいん" + std::to_string(recoilVelocity.y), 800);
#endif	// _DEBUG

	return recoilVelocity;
}