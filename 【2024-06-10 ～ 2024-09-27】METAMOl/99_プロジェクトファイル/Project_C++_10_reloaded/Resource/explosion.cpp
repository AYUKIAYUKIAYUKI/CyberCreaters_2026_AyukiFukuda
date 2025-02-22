////============================================================================
//// 
//// 爆発 [explosion.cpp]
//// Author : 福田歩希
//// 
////============================================================================
//
////****************************************************
//// インクルードファイル
////****************************************************
//#include "explosion.h"
//
//// テクスチャ取得用
//#include "texture_manager.h"
//
////============================================================================
//// デフォルトコンストラクタ
////============================================================================
//CExplosion::CExplosion() :
//	CObject_billboard{ static_cast<int>(LAYER::FRONT_MIDDLE) },	// 基底クラスのコンストラクタ
//	m_nCntTexChange{ 0 }										// テクスチャ変更管理
//{
//
//}
//
////============================================================================
//// デストラクタ
////============================================================================
//CExplosion::~CExplosion()
//{
//
//}
//
////============================================================================
//// 初期設定
////============================================================================
//HRESULT CExplosion::Init()
//{
//	// 基底クラスの初期設定
//	HRESULT hr = CObject_billboard::Init();
//
//	return hr;
//}
//
////============================================================================
//// 終了処理
////============================================================================
//void CExplosion::Uninit()
//{
//	// 基底クラスの終了処理
//	CObject_billboard::Uninit();
//}
//
////============================================================================
//// 更新処理
////============================================================================
//void CExplosion::Update()
//{
//	// アニメーション
//	if (!Animation())
//	{ // 破棄されていたら更新終了
//		return;
//	}
//
//	// 基底クラスの更新
//	CObject_billboard::Update();
//}
//
////============================================================================
//// 描画処理
////============================================================================
//void CExplosion::Draw()
//{
//	// 基底クラスの描画処理
//	CObject_billboard::Draw();
//}
//
////============================================================================
//// 生成
////============================================================================
//CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
//{
//	// インスタンスを生成
//	CExplosion* pExplosion = DBG_NEW CExplosion;
//
//	if (pExplosion == nullptr)
//	{ // 生成失敗
//		assert(false);
//	}
//
//	pExplosion->SetType(TYPE::NONE);	// タイプを設定
//
//	pExplosion->Init();			// 基底クラスの初期設定
//	pExplosion->SetPos(pos);	// 位置の設定
//	pExplosion->SetSize(size);	// サイズの設定
//
//	pExplosion->SetTexWidth(1.0f / 8.0f);	// 横テクスチャ分割幅
//	pExplosion->SetTexHeight(1.0f);			// 縦テクスチャ分縦幅
//
//	// テクスチャを設定
//	pExplosion->BindTex(CTexture_Manager::GetInstance()->GetTexture(CTexture_Manager::TYPE::BG_000));
//
//	return pExplosion;
//}
//
////============================================================================
//// アニメーション
////============================================================================
//bool CExplosion::Animation()
//{
//	// テクスチャ変更管理カウントアップ
//	m_nCntTexChange++;
//
//	if (m_nCntTexChange >= 5)
//	{
//		// 横テクスチャ種類情報取得
//		int nTexPatternU = GetNowPatternU();
//
//		// 横テクスチャ種類変更
//		nTexPatternU++;
//
//		if (nTexPatternU >= 8)
//		{
//			// 自身を破棄
//			CObject::SetRelease();
//
//			// 終了
//			return false;
//		}
//
//		// 横テクスチャ種類情報設定
//		SetNowPatternU(nTexPatternU);
//
//		// 変更管理カウントをリセット
//		m_nCntTexChange = 0;
//	}
//
//	return true;
//}