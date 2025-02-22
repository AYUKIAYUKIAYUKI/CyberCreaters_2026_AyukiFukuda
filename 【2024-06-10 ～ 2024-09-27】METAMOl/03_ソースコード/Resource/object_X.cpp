//============================================================================
// 
// Xオブジェクト管理 [object_X.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

// デバイス取得用
#include "renderer.h"

// 判定可視化用
#include "render_collision.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
const float CObject_X::DEFAULT_ALPHA_VALUE = 1.0f;	// デフォルトアルファ値

//============================================================================
// コンストラクタ
//============================================================================
CObject_X::CObject_X(int nPriority) : CObject(nPriority)
{
	m_pModel = nullptr;					// モデル情報
	m_pos = { 0.0f, 0.0f, 0.0f };		// 位置
	m_rot = { 0.0f, 0.0f, 0.0f };		// 向き
	m_size = { 0.0f, 0.0f, 0.0f };		// サイズ
	m_fScale = 1.0f;					// 縮尺
	m_fAlpha = DEFAULT_ALPHA_VALUE;		// アルファ値
	D3DXMatrixIdentity(&m_mtxWorld);	// ワールド行列

	// 判定表示の生成
	//CRender_Collision::Create(m_pos, m_size);
}

//============================================================================
// デストラクタ
//============================================================================
CObject_X::~CObject_X()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CObject_X::Init()
{
	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CObject_X::Uninit()
{

}

//============================================================================
// 更新処理
//============================================================================
void CObject_X::Update()
{
	// ワールド行列の設定
	SetMtxWorld();
}

//============================================================================
// 描画処理
//============================================================================
void CObject_X::Draw()
{
	// モデルが設定されていない
	if (m_pModel == nullptr)
	{
#ifdef _DEBUG
		CRenderer::GetInstance()->SetDebugString(static_cast<std::string>("【") + typeid(*this).name() + static_cast<std::string>("にモデル情報がありません！】"));
#endif	// _DEBUG
		return;
	}

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// 現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	// マテリアル情報へのポインタ
	D3DXMATERIAL* pMat = nullptr;

	// ワールドマトリックスの設定
	pDev->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDev->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pModel->pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < static_cast<int>(m_pModel->dwNumMat); nCntMat++)
	{
		// アルファ値の設定
		pMat[nCntMat].MatD3D.Diffuse.a = m_fAlpha;

		// マテリアルの設定
		pDev->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDev->SetTexture(0, m_pModel->ppTex[nCntMat]);

		// オブジェクトパーツの描画
		m_pModel->pMesh->DrawSubset(nCntMat);
	}

	// 保存していたマテリアルを戻す
	pDev->SetMaterial(&matDef);
}

//============================================================================
// モデル割当
//============================================================================
void CObject_X::BindModel(CModel_X_Manager::MODEL* pModel)
{
	if (pModel->pMesh == nullptr)
	{ // 取得失敗
		assert(false);
	}

	m_pModel = pModel;
}

//============================================================================
// 位置取得
//============================================================================
D3DXVECTOR3 CObject_X::GetPos()
{
	return m_pos;
}

//============================================================================
// 位置設定
//============================================================================
void CObject_X::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================================================
// 向き取得
//============================================================================
D3DXVECTOR3& CObject_X::GetRot()
{
	return m_rot;
}

//============================================================================
// 向き設定
//============================================================================
void CObject_X::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================================================================
// サイズ取得
//============================================================================
D3DXVECTOR3 CObject_X::GetSize()
{
	return m_size;
}

//============================================================================
// サイズ設定
//============================================================================
void CObject_X::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//============================================================================
// アルファ値取得
//============================================================================
float& CObject_X::GetAlpha()
{
	return m_fAlpha;
}

//============================================================================
// アルファ値設定
//============================================================================
void CObject_X::SetAlpha(float fAlpha)
{
	m_fAlpha = fAlpha;
}

//============================================================================
// 生成
//============================================================================
CObject_X* CObject_X::Create()
{
	CObject_X* pObjectX = DBG_NEW CObject_X;

	// 生成出来ていたら初期設定
	if (pObjectX != nullptr)
	{
		pObjectX->Init();
	}

	return pObjectX;
}

//============================================================================
// ワールド行列設定
//============================================================================
void CObject_X::SetMtxWorld()
{
	// 計算用行列
	D3DXMATRIX mtxScale{}, mtxRot{}, mtxTrans{};

	// ワールド行列を初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 拡縮行列作成
	D3DXMatrixScaling(&mtxScale,
		m_fScale,
		m_fScale,
		m_fScale);

	// 拡縮行列との掛け算
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxScale);

	// 回転行列作成
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);

	// 回転行列との掛け算
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// 平行移動行列作成
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	// 平行移動行列との掛け算
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);
}