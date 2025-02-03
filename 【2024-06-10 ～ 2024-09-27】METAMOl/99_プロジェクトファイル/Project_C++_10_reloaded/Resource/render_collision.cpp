//============================================================================
// 
// 判定表示 [render_collision.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "render_collision.h"

// デバイス取得用
#include "renderer.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
const int CRender_Collision::m_nNumVtx = 8;			// 頂点数
const int CRender_Collision::m_nNumPrimitive = 12;	// 辺数
const int CRender_Collision::m_nNumIdx = 24;		// インデックス数

//============================================================================
// コンストラクタ
//============================================================================
CRender_Collision::CRender_Collision(D3DXVECTOR3& posRef, D3DXVECTOR3& sizeRef, int nPriority) :
	CObject{ nPriority },				// プライオリティ
	m_pVtxBuff{ nullptr },				// 頂点バッファのポインタ
	m_pIdxBuff{ nullptr },				// インデックスバッファのポインタ
	m_posRef{ posRef },					// 参照位置
	m_col{ 1.0f, 0.0f, 0.0f, 1.0f },	// 色
	m_size{ sizeRef }
{
	// ワールド行列の初期化
	D3DXMatrixIdentity(&m_mtxWorld);
}

//============================================================================
// デストラクタ
//============================================================================
CRender_Collision::~CRender_Collision()
{
	// 念のため終了処理
	Uninit();

	// ワールド行列の初期化
	D3DXMatrixIdentity(&m_mtxWorld);
}

//============================================================================
// 初期設定
//============================================================================
HRESULT CRender_Collision::Init()
{
	// 頂点バッファの生成
	if (FAILED(CreateVtxBuff()))
	{
		return E_FAIL;
	}

	// インデックスバッファの生成
	if (FAILED(CreateIdxBuff()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CRender_Collision::Uninit()
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// インデックスバッファの破棄
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
}

//============================================================================
// 更新処理
//============================================================================
void CRender_Collision::Update()
{
	// 頂点の設定
	SetVtx();

	// ワールド行列の設定
	SetMtxWorld();
}

//============================================================================
// 描画処理
//============================================================================
void CRender_Collision::Draw()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// ライトをオフ
	pDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 頂点バッファをデータストリームに設定
	pDev->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDev->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDev->SetFVF(FVF_VERTEX_3D);

	// ワールドマトリックスの設定
	pDev->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// テクスチャの設定
	pDev->SetTexture(0, nullptr);

	// ボックスの描画
	pDev->DrawIndexedPrimitive(D3DPT_LINELIST,
		0,
		0,
		m_nNumVtx,			// 頂点数
		0,
		m_nNumPrimitive);	// 辺の数
	
	// ライトをオン
	pDev->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================================================================
// 生成
//============================================================================
CRender_Collision* CRender_Collision::Create(D3DXVECTOR3& posRef, D3DXVECTOR3& sizeRef)
{
	// インスタンスを生成
	CRender_Collision* pRender_Collision = DBG_NEW CRender_Collision{ posRef, sizeRef, static_cast<int>(LAYER::FRONT) };

	// 生成出来ていたら初期設定
	if (pRender_Collision != nullptr)
	{
		pRender_Collision->Init();
	}

	return pRender_Collision;
}

//============================================================================
// 頂点バッファの生成
//============================================================================
HRESULT CRender_Collision::CreateVtxBuff()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// 頂点バッファの生成
	pDev->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	if (m_pVtxBuff == nullptr)
	{ // 生成失敗
		return E_FAIL;
	}

	// 頂点情報へのポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	for (int i = 0; i < m_nNumVtx; i++)
	{
		// 位置の設定
		pVtx[i].pos = { 0.0f, 0.0f, 0.0f };

		// 法線ベクトルの設定
		pVtx[i].nor = { 0.0f, 0.0f, 0.0f };

		// 色の設定
		pVtx[i].col = m_col;

		// テクスチャの設定
		pVtx[i].tex = { 0.0f, 0.0f };
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================================================
// インデックス情報の生成
//============================================================================
HRESULT CRender_Collision::CreateIdxBuff()
{
	// インデックスバッファの生成
	CRenderer::GetInstance()->GetDeviece()->CreateIndexBuffer(sizeof(WORD) * m_nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		nullptr);

	if (m_pIdxBuff == nullptr)
	{ // 生成失敗
		return E_FAIL;
	}

	// インデックス情報へのポインタ
	WORD* pIdx;

	// インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, reinterpret_cast<void**>(&pIdx), 0);

	// X軸に平行な線を引く
	for (int i = 0; i < 8; i++, pIdx++)
	{
		pIdx[0] = static_cast<WORD>(i);
	}

	// Y軸に平行な線を引く
	for (int i = 0, j = 0; i < 4; i++, pIdx += 2)
	{
		if (i == 2) j += 2;	// 0,1,4,5を辺の始点にするため3,4のインデックスを飛ばす

		pIdx[0] = static_cast<WORD>(i + j);
		pIdx[1] = static_cast<WORD>(i + 2 + j);
	}

	// Z軸に平行な線を引く
	for (int i = 0; i < 4; i++, pIdx += 2)
	{
		pIdx[0] = static_cast<WORD>(i);
		pIdx[1] = static_cast<WORD>(i + 4);
	}

	// インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}


//============================================================================
// 頂点の設定
//============================================================================
void CRender_Collision::SetVtx()
{
	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	pVtx[0].pos = { -m_size.x, +m_size.y, -m_size.z };
	pVtx[1].pos = { +m_size.x, +m_size.y, -m_size.z };
	pVtx[2].pos = { -m_size.x, -m_size.y, -m_size.z };
	pVtx[3].pos = { +m_size.x, -m_size.y, -m_size.z };
	pVtx[4].pos = { -m_size.x, +m_size.y, +m_size.z };
	pVtx[5].pos = { +m_size.x, +m_size.y, +m_size.z };
	pVtx[6].pos = { -m_size.x, -m_size.y, +m_size.z };
	pVtx[7].pos = { +m_size.x, -m_size.y, +m_size.z };

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//============================================================================
// ワールド行列設定
//============================================================================
void CRender_Collision::SetMtxWorld()
{
	// 計算用行列
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールド行列を初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 平行移動行列作成
	D3DXMatrixTranslation(&mtxTrans,
		m_posRef.x,
		m_posRef.y,
		m_posRef.z);

	// 平行移動行列との掛け算
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);
}