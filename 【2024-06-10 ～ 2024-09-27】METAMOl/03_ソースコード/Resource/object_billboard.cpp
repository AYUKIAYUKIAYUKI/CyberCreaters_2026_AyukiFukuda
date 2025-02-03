//============================================================================
// 
// ビルボードオブジェクト管理 [object_billboard.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "object_billboard.h"

// デバイス取得用
#include "renderer.h"

//============================================================================
// コンストラクタ
//============================================================================
CObject_billboard::CObject_billboard(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = nullptr;	// 頂点バッファのポインタを初期化
	m_pTex = nullptr;		// テクスチャのポインタを初期化

	m_pos = { 0.0f, 0.0f, 0.0f };		// 位置
	m_rot = { 0.0f, 0.0f, 0.0f };		// 向き
	m_size = { 0.0f, 0.0f, 0.0f };		// サイズ
	m_fLength = 0.0f;					// 展開用対角線
	m_fAngle = 0.0f;					// 対角線用角度
	m_fTexWidth = 1.0f;					// 横テクスチャ分割幅
	m_fTexHeight = 1.0f;				// 縦テクスチャ分縦幅
	m_nNowPatternU = 0;					// 現在の横テクスチャ種類
	m_nNowPatternV = 0;					// 現在の縦テクスチャ種類
	D3DXMatrixIdentity(&m_mtxWorld);	// ワールド行列
}

//============================================================================
// デストラクタ
//============================================================================
CObject_billboard::~CObject_billboard()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CObject_billboard::Init()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// 頂点バッファの生成
	pDev->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
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
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 位置の設定
	pVtx[0].pos = { 0.0f, 0.0f, 0.0f };
	pVtx[1].pos = { 0.0f, 0.0f, 0.0f };
	pVtx[2].pos = { 0.0f, 0.0f, 0.0f };
	pVtx[3].pos = { 0.0f, 0.0f, 0.0f };

	// 法線ベクトルの設定
	pVtx[0].nor = { 0.0f, 1.0f, 0.0f };
	pVtx[1].nor = { 0.0f, 1.0f, 0.0f };
	pVtx[2].nor = { 0.0f, 1.0f, 0.0f };
	pVtx[3].nor = { 0.0f, 1.0f, 0.0f };

	// 色の設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャの設定
	pVtx[0].tex = { 0.0f, 0.0f };
	pVtx[1].tex = { 1.0f, 0.0f };
	pVtx[2].tex = { 0.0f, 1.0f };
	pVtx[3].tex = { 1.0f, 1.0f };

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CObject_billboard::Uninit()
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//============================================================================
// 更新処理
//============================================================================
void CObject_billboard::Update()
{
	if (m_pVtxBuff == nullptr)
	{ // 頂点バッファが消失
		assert(false);
	}

	// 必要な数値を計算
	m_fAngle = atan2f(m_size.x, m_size.y);
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y);

	// 頂点情報へのポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	// 位置の設定
	pVtx[0].pos = {
		sinf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength,
		-cosf(m_rot.z - (D3DX_PI - m_fAngle)) * m_fLength,
		0.0f
	};

	pVtx[1].pos = {
		sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		-cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength,
		0.0f
	};

	pVtx[2].pos = {
		sinf(m_rot.z - m_fAngle) * m_fLength,
		-cosf(m_rot.z - m_fAngle) * m_fLength,
		0.0f
	};

	pVtx[3].pos = {
		sinf(m_rot.z + m_fAngle) * m_fLength,
		-cosf(m_rot.z + m_fAngle) * m_fLength,
		0.0f
	};

	// テクスチャの設定
	pVtx[0].tex = { m_fTexWidth * m_nNowPatternU, m_fTexHeight * m_nNowPatternV };
	pVtx[1].tex = { m_fTexWidth * (m_nNowPatternU + 1), m_fTexHeight * m_nNowPatternV };
	pVtx[2].tex = { m_fTexWidth * (m_nNowPatternU), m_fTexHeight * (m_nNowPatternV + 1) };
	pVtx[3].tex = { m_fTexWidth * (m_nNowPatternU + 1), m_fTexHeight * (m_nNowPatternV + 1) };

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// ワールド行列の設定
	SetMtxWorld();
}

//============================================================================
// 描画処理
//============================================================================
void CObject_billboard::Draw()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	//// 深度テストの比較方法の変更
	//pDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//// 深度バッファに描画しない
	//pDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// アルファテストを有効にする
	pDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDev->SetRenderState(D3DRS_ALPHAREF, 0);
	pDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ライト反映を無効にする
	pDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールド行列の設定
	pDev->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDev->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDev->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDev->SetTexture(0, m_pTex);

	// ポリゴンの描画
	pDev->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// プリミティブの種類
		0,										// 頂点情報の先頭アドレス
		2);										// プリミティブ数

	// ライト反映を有効にする
	pDev->SetRenderState(D3DRS_LIGHTING, TRUE);

	//// 深度テストの比較方法の変更
	//pDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//// 深度バッファに書き込む
	//pDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファテストを無効にする
	pDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//============================================================================
// テクスチャ割当
//============================================================================
void CObject_billboard::BindTex(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}

//============================================================================
// 位置取得
//============================================================================
D3DXVECTOR3 CObject_billboard::GetPos()
{
	return m_pos;
}

//============================================================================
// 位置設定
//============================================================================
void CObject_billboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================================================
// 向き取得
//============================================================================
D3DXVECTOR3 CObject_billboard::GetRot()
{
	return m_rot;
}

//============================================================================
// 向き設定
//============================================================================
void CObject_billboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================================================================
// サイズ取得
//============================================================================
D3DXVECTOR3 CObject_billboard::GetSize()
{
	return m_size;
}

//============================================================================
// サイズ設定
//============================================================================
void CObject_billboard::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//============================================================================
// 展開用対角線取得
//============================================================================
float CObject_billboard::GetLength()
{
	return m_fLength;
}

//============================================================================
// 横テクスチャ分割幅設定
//============================================================================
void CObject_billboard::SetTexWidth(float fWidth)
{
	m_fTexWidth = fWidth;
}

//============================================================================
// 縦テクスチャ分割幅設定
//============================================================================
void CObject_billboard::SetTexHeight(float fHeight)
{
	m_fTexHeight = fHeight;
}

//============================================================================
// 現在のテクスチャ横分割幅取得
//============================================================================
int CObject_billboard::GetNowPatternU()
{
	return m_nNowPatternU;
}

//============================================================================
// 現在のテクスチャ横分割幅設定
//============================================================================
void CObject_billboard::SetNowPatternU(int nNowPatternU)
{
	m_nNowPatternU = nNowPatternU;
}

//============================================================================
// 現在のテクスチャ縦分割幅取得
//============================================================================
int CObject_billboard::GetNowPatternV()
{
	return m_nNowPatternV;
}

//============================================================================
// 現在のテクスチャ縦分割幅設定
//============================================================================
void CObject_billboard::SetNowPatternV(int nNowPatternV)
{
	m_nNowPatternV = nNowPatternV;
}

//============================================================================
// 生成
//============================================================================
CObject_billboard* CObject_billboard::Create()
{
	CObject_billboard* pObject3D = DBG_NEW CObject_billboard;

	// 生成出来ていたら初期設定
	if (pObject3D != nullptr)
	{
		pObject3D->Init();
	}

	return pObject3D;
}

//============================================================================
// ワールド行列設定
//============================================================================
void CObject_billboard::SetMtxWorld()
{
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// 計算用行列
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	// ワールド行列を初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// ビュー行列取得
	pDev->GetTransform(D3DTS_VIEW, &mtxView);

	// ポリゴンをカメラの正面に向け続ける
	D3DXMatrixInverse(&m_mtxWorld, nullptr, &mtxView);

	// 逆行列を求める
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

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