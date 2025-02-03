//============================================================================
// 
// テクスチャマネージャー [texture_manager.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "texture_manager.h"

// デバイス取得用
#include "renderer.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
CTexture_Manager* CTexture_Manager::m_pInstance = nullptr;	// テクスチャマネージャー

//============================================================================
// 初期設定
//============================================================================
HRESULT CTexture_Manager::Load()
{
	// テクスチャリストを展開
	std::ifstream file{ "data\\TXT\\texture_path.txt" };

	if (!file)
	{ // 展開に失敗
		assert(false);
	}

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	for (int i = 0; i < static_cast<int>(TYPE::MAX); i++)
	{
		// テクスチャ名格納先
		std::string filename{};

		// テクスチャ名を取得する
		std::getline(file, filename);

		// テクスチャの生成
		HRESULT hr = D3DXCreateTextureFromFileA(pDev,
			filename.c_str(),
			&m_apTexTemp[i]);

		if (FAILED(hr))
		{ // テクスチャ生成失敗
#if 0
			// ファイルを閉じる
			file.close();

			assert(false);
#else

#ifdef _DEBUG
			CRenderer::GetInstance()->SetTimeString("【警告】テクスチャ[" + filename + "]は生成に失敗しました", 300);
#endif	// _DEBUG

#endif
		}
	}

	// ファイルを閉じる
	file.close();

	return S_OK;
}

//============================================================================
// 解放
//============================================================================
void CTexture_Manager::Release()
{
	if (m_pInstance != nullptr)
	{
		// テクスチャを破棄
		m_pInstance->Unload();

		// メモリを解放
		delete m_pInstance;
	
		// ポインタを初期化
		m_pInstance = nullptr;
	}
}

//============================================================================
// テクスチャを取得
//============================================================================
LPDIRECT3DTEXTURE9 CTexture_Manager::GetTexture(TYPE type)
{
	if (m_apTexTemp[static_cast<int>(type)] == nullptr)
	{ // テクスチャ取得不能
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("【警告】テクスチャ取得エラー", 300);
#endif	// _DEBUG

#endif
	}

	return m_apTexTemp[static_cast<int>(type)];
}

//============================================================================
// テクスチャマネージャーを取得
//============================================================================
CTexture_Manager* CTexture_Manager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// 生成
		m_pInstance->Create();
	}

	return m_pInstance;
}

//============================================================================
// コンストラクタ
//============================================================================
CTexture_Manager::CTexture_Manager()
{
	for (int i = 0; i < static_cast<int>(TYPE::MAX); i++)
	{
		m_apTexTemp[i] = nullptr;	// テクスチャ情報の初期化
	}
}

//============================================================================
// デストラクタ
//============================================================================
CTexture_Manager::~CTexture_Manager()
{

}

//============================================================================
// 生成
//============================================================================
void CTexture_Manager::Create()
{
	if (m_pInstance != nullptr)
	{ // 二重生成禁止
		assert(false);
	}

	// インスタンスを生成
	m_pInstance = DBG_NEW CTexture_Manager{};
}

//============================================================================
// 終了処理
//============================================================================
void CTexture_Manager::Unload()
{
	for (int i = 0; i < static_cast<int>(TYPE::MAX); i++)
	{
		// テクスチャの破棄
		if (m_apTexTemp[i] != nullptr)
		{
			m_apTexTemp[i]->Release();
			m_apTexTemp[i] = nullptr;
		}
	}
}