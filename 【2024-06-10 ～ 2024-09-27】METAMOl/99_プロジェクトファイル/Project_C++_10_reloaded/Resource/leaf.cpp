//============================================================================
// 
// 葉っぱ [leaf.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "leaf.h"
#include "utility.h"

// オブジェクト用
#include "player.h"

//****************************************************
// 静的メンバの初期化
//****************************************************
int CLeaf::m_nCntSpawn = 0;	// 生成間隔

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CLeaf::CLeaf() :
	CObject_billboard{ static_cast<int>(LAYER::MIDDLE) },	// 描画優先度を指定
	m_type{ CLeaf::OSCILLATION::NONE },						// 振動の種類
	m_velocity{ 0.0f, 0.0f, 0.0f }							// 加速度
{
	// ランダムなタイプを設定
	m_type = GetRandomOscillation();

	// 向きを取得
	D3DXVECTOR3 rotTarget = GetRot();

	// 目標向きをランダムに設定
	rotTarget.z = CUtility::GetInstance()->GetRandomValue<float>();

	// 目標向きを反映
	SetRot(rotTarget);
}

//============================================================================
// デストラクタ
//============================================================================
CLeaf::~CLeaf()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CLeaf::Init()
{
	// 基底クラスの初期設定
	HRESULT hr = CObject_billboard::Init();

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CLeaf::Uninit()
{
	// 基底クラスの終了処理
	CObject_billboard::Uninit();
}

//============================================================================
// 更新処理
//============================================================================
void CLeaf::Update()
{
	// 回転
	Rotate();

	// 移動
	Translate();

	// 縮小
	D3DXVECTOR3 size = GetSize();
	size *= 0.99f;
	SetSize(size);

	if (size.x <= 0.1f || size.y <= 0.11f)
	{
		// 破棄予約
		SetRelease();
	}

	// 基底クラスの更新
	CObject_billboard::Update();
}

//============================================================================
// 描画処理
//============================================================================
void CLeaf::Draw()
{
	// 基底クラスの描画処理
	CObject_billboard::Draw();
}

//============================================================================
// 生成用更新
//============================================================================
void CLeaf::UpdateToCreate()
{
	m_nCntSpawn++;

	if (m_nCntSpawn > 10)
	{
		m_nCntSpawn = 0;

		// プレイヤーを取得
		CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(CObject::FindObject(CObject::TYPE::PLAYER));

		// 出現座標を設定する
		D3DXVECTOR3 posTarget{ 0.0f, 0.0f, 0.0f };

		if (rand() % 2 == 0)
		{
			posTarget.x = pPlayer->GetPos().x + 100.0f + (rand() % 50);
		}
		else
		{
			posTarget.x = pPlayer->GetPos().x + - 100.0f - (rand() % 50);
		}

		posTarget.y = pPlayer->GetPos().y + 250.0f;


		// 生成
		auto p = Create(posTarget, pPlayer->GetSize(), GetRandomTexture());
		p->m_velocity.y = -1.0f;

		p->m_velocity = { CUtility::GetInstance()->GetRandomValue<float>() * 0.01f, -3.0f, CUtility::GetInstance()->GetRandomValue<float>() * 0.01f };
	}
}

//============================================================================
// 生成
//============================================================================
CLeaf* CLeaf::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex)
{
	// インスタンスを生成
	CLeaf* pLeaf = DBG_NEW CLeaf{};

	if (pLeaf == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// タイプを設定
	pLeaf->SetType(TYPE::NONE);

	// 基底クラスの初期設定
	pLeaf->Init();

	// 位置の設定
	pLeaf->SetPos(pos);

	// サイズの設定
	pLeaf->SetSize(size);

	// テクスチャを設定
	pLeaf->BindTex(tex);

	return pLeaf;
}

//============================================================================
// 回転
//============================================================================
void CLeaf::Rotate()
{
	// 向きを取得
	D3DXVECTOR3 rotTarget = GetRot();

	// 目標向きに加速度を加算
	rotTarget.z += CUtility::GetInstance()->GetRandomValue<float>() * 0.0001f;

	// 目標向きを反映
	SetRot(rotTarget);
}

//============================================================================
// 移動
//============================================================================
void CLeaf::Translate()
{
	// 座標を取得
	D3DXVECTOR3 posTarget = GetPos();

	// 目標座標に加速度を加算
	posTarget += m_velocity;

	// 目標座標を反映
	SetPos(posTarget);
}

//============================================================================
// ランダムな葉っぱテクスチャの種類を取得
//============================================================================
LPDIRECT3DTEXTURE9 CLeaf::GetRandomTexture()
{
	LPDIRECT3DTEXTURE9 tex{ nullptr };

	switch (rand() % 5)
	{
	case 0:
		tex = CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::LEAF_00);
		break;

	case 1:
		tex = CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::LEAF_01);
		break;

	case 2:
		tex = CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::LEAF_02);
		break;

	case 3:
		tex = CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::LEAF_03);
		break;

	case 4:
		tex = CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::LEAF_04);
		break;

	default:
		tex = CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::LEAF_00);
		break;
	}

	return tex;
}

//============================================================================
// ランダムな振動の種類を取得
//============================================================================
CLeaf::OSCILLATION CLeaf::GetRandomOscillation()
{
	return static_cast<OSCILLATION>(rand() % static_cast<int>(OSCILLATION::MAX));
}