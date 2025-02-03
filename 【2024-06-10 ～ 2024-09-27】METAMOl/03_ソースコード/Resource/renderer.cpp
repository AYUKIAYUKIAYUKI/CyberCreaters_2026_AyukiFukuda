//============================================================================
// 
// レンダラー管理 [renderer.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "renderer.h"
#include "utility.h"

// 描画用
#include "manager.h"

// シングルトン管理用
#include "texture_manager.h"
#include "model_X_manager.h"

// オブジェクト情報
#include "fakescreen.h"
#include "monitor.h"
#include "furniture.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
CRenderer* CRenderer::m_pRenderer = nullptr;	// レンダラー

//============================================================================
// コンストラクタ
//============================================================================
CRenderer::CRenderer() :
	m_pD3D{ nullptr },				// Direct3D
	m_pD3DDevice{ nullptr },		// デバイス
	m_pFont{ nullptr },				// フォント
	m_pMonitorTex{ nullptr },		// モニター用テクスチャポインタ
	m_pMonitorSurface{ nullptr },	// モニター用サーフェイスポインタ
	m_debugStr{},					// 表示用文字列
	m_timeStr{}						// 時限式文字列
{

}

//============================================================================
// デストラクタ
//============================================================================
CRenderer::~CRenderer()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindiw)
{
	D3DDISPLAYMODE d3ddm;			// ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	// プレゼンテーションパラメータ

	// Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{ // 生成に失敗した場合
		return E_FAIL;
	}

	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{ // 現在のディスプレイモードを取得
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));	// パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲームサイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲームサイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						// バックバッファの形式
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindiw;									// ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

	// Direct3Dデバイスの生成行程①
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		// Direct3Dデバイスの生成行程②
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			// Direct3Dデバイスの生成行程③
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// ?
	//ID3DXAllocateHierarchy;

	// フォントを生成
	D3DXCreateFont(m_pD3DDevice, 22, 0, FW_HEAVY, 1,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &m_pFont);

	// 疑似スクリーン用テクスチャの生成
	if (FAILED(CreateTex()))
	{
		return E_FAIL;
	}

	// テクスチャマネージャー初期設定
	if (FAILED(CTexture_Manager::GetInstance()->Load()))
	{
		return E_FAIL;
	}

	// Xモデルマネージャー初期設定
	if (FAILED(CModel_X_Manager::GetInstance()->Load()))
	{
		return E_FAIL;
	}

	// 疑似スクリーンの初期設定
	CFakeScreen::GetInstance()->Init();

	// モニターの生成
	CMonitor::Create();

	// 家具の配置
	LayoutFurniture();

	return S_OK;
}

//============================================================================
// 解放
//============================================================================
void CRenderer::Release()
{
	if (m_pRenderer != nullptr)
	{
		// 終了処理
		m_pRenderer->Uninit();

		// メモリを解放
		delete m_pRenderer;

		// ポインタを初期化
		m_pRenderer = nullptr;
	}
}

//============================================================================
// 更新処理
//============================================================================
void CRenderer::Update()
{
	// 文字列クリア
	m_debugStr = {};

	// 全オブジェクト更新処理
	CObject::UpdateAll();

	// 全オブジェクト後更新処理
	CObject::LateUpdateAll();

	// 疑似スクリーンの更新
	CFakeScreen::GetInstance()->Update();
}

//============================================================================
// 描画処理
//============================================================================
void CRenderer::Draw()
{
	if (CManager::GetScene()->GetMode() != CScene::MODE::STAGE)
	{
		// レンダリングターゲット保持用
		LPDIRECT3DSURFACE9 oldRenderTarget = nullptr;

		// バックバッファの情報をコピー
		m_pD3DDevice->GetRenderTarget(0, &oldRenderTarget);

		// レンダリングターゲットに疑似スクリーンのサーフェイスを指定
		m_pD3DDevice->SetRenderTarget(0, CFakeScreen::GetInstance()->GetSurface());

		// 疑似スクリーンのテクスチャ内へ描画開始
		if (SUCCEEDED(m_pD3DDevice->BeginScene()))
		{
			// カメラをセット
			CManager::GetCamera()->SetCamera();

			// スクリーン画面内の描画
			CObject::DrawScreen();

			// シーンの専用描画
			CManager::GetScene()->Draw();

			// 描画終了
			m_pD3DDevice->EndScene();
		}

		// レンダリングターゲットにモニター用のサーフェイスを指定
		m_pD3DDevice->SetRenderTarget(0, m_pMonitorSurface);

		// 色情報をランダムに設定
		//auto p{ CUtility::GetInstance() };
		//D3DXCOLOR col{ p->GetRandomValue<float>(), p->GetRandomValue<float>(), p->GetRandomValue<float>(), 0 };
		D3DXCOLOR col{ 255, 255, 255, 0 };

		// 画面バッファクリア
		m_pD3DDevice->Clear(0, nullptr,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			col, 1.0f, 0);

		// モニター用のテクスチャ内へ描画開始
		if (SUCCEEDED(m_pD3DDevice->BeginScene()))
		{
			// 疑似スクリーンを描画
			CFakeScreen::GetInstance()->Draw();

			// UIの描画
			CObject::DrawUI();

			// 描画終了
			m_pD3DDevice->EndScene();
		}

		// レンダリングターゲットをバックバッファに戻す
		m_pD3DDevice->SetRenderTarget(0, oldRenderTarget);

		// 保持していたレンダリングターゲットの破棄
		if (oldRenderTarget != nullptr)
		{
			oldRenderTarget->Release();
			oldRenderTarget = nullptr;
		}

		// 通常の3D空間内へ描画開始
		if (SUCCEEDED(m_pD3DDevice->BeginScene()))
		{
			/* ワイヤー描画 */
			//m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

			// カメラをセット
			CManager::GetCamera()->SetCameraBG();

			// 背景の描画
			CObject::DrawBG();

			// デバッグ表示
			PrintDebug();

			// 描画終了
			m_pD3DDevice->EndScene();
		}

		// バックバッファとフロントバッファの入れ替え
		m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
	}
	else
	{
		// 画面バッファクリア
		m_pD3DDevice->Clear(0, nullptr,
			(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0), 1.0f, 0);

		// 疑似スクリーンのテクスチャ内へ描画開始
		if (SUCCEEDED(m_pD3DDevice->BeginScene()))
		{
			// カメラをセット
			CManager::GetCamera()->SetCamera();

			// スクリーン画面内の描画
			CObject::DrawScreen();

			// シーンの専用描画
			CManager::GetScene()->Draw();

			// デバッグ表示
			PrintDebug();

			// 描画終了
			m_pD3DDevice->EndScene();
		}

		// バックバッファとフロントバッファの入れ替え
		m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
	}
}

//============================================================================
// デバッグ表示
//============================================================================
void CRenderer::PrintDebug()
{
	// 表示位置
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	for (unsigned int i = 0; i < m_timeStr.size(); i++)
	{
		if (m_timeStr[i].second > 0)
		{
			// 表示時間をカウントダウン
			m_timeStr[i].second--;

			// 文章をつなげる
			m_debugStr += m_timeStr[i].first + "\n";
		}
		else
		{
			// 文章を消去
			m_timeStr.erase(m_timeStr.begin() + i);
		}
	}

	//テキストの描画
	m_pFont->DrawText(NULL, m_debugStr.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//============================================================================
// レンダラーの取得
//============================================================================
CRenderer* CRenderer::GetInstance()
{
	if (m_pRenderer == nullptr)
	{
		// 生成
		m_pRenderer->Create();
	}

	return m_pRenderer;
}

//============================================================================
// デバイスの取得
//============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDeviece()
{
	return m_pD3DDevice;
}

//============================================================================
// テクスチャ情報を取得
//============================================================================
LPDIRECT3DTEXTURE9 CRenderer::GetTexture()
{
	return m_pMonitorTex;
}

//============================================================================
// サーフェイス情報を取得
//============================================================================
LPDIRECT3DSURFACE9 CRenderer::GetSurface()
{
	return m_pMonitorSurface;
}

//============================================================================
// デバッグ用文字列に追加
//============================================================================
void CRenderer::SetDebugString(std::string str)
{
	m_debugStr += str + "\n";
}

//============================================================================
// 時限式デバッグ文字列に追加
//============================================================================
void CRenderer::SetTimeString(std::string str, int nCnt)
{
	m_timeStr.push_back({ str, nCnt });
}

//============================================================================
// 家具の配置
//============================================================================
void CRenderer::LayoutFurniture()
{
	// ROOMの生成
	//CFurniture::Create({ 0.0f, 157.5f, -189.0f }, 20.0f, CModel_X_Manager::TYPE::ROOM);
	CFurniture::Create({ 0.0f, 57.5f, -89.0f }, 10.0f, CModel_X_Manager::TYPE::ROOM);

	// VHSの生成
	CFurniture::Create({ 0.0f, -14.75f, 3.0f }, 2.0f, CModel_X_Manager::TYPE::VHS);

	// 本棚の生成
	CFurniture::Create({ -38.5f, 7.5f, 8.0f }, 5.0f, CModel_X_Manager::TYPE::BOOKSELF);

	// スピーカーの生成
	CFurniture::Create({ 30.0f, -10.0f, 4.0f }, 1.25f, CModel_X_Manager::TYPE::SPEAKER);

	// でかスピーカーの生成
	CFurniture::Create({ 51.0f, -18.0f, 0.0f }, 2.5f, CModel_X_Manager::TYPE::SPEAKER_BIG);

	// 蓄音機の生成
	CFurniture::Create({ -29.f, -10.0f, -5.0f }, 1.0f, CModel_X_Manager::TYPE::GRAMOPHONE);

	// 観葉植物の生成
	CFurniture::Create({ -52.5f, -22.5f, -8.0f }, 2.0f, CModel_X_Manager::TYPE::INDOOR_PLANTS);

	// ポスターの生成
	CFurniture::Create({ 0.0f, 32.5f, 10.0f }, 1.75f, CModel_X_Manager::TYPE::POSTER);

	// メモの生成
	CFurniture::Create({ 30.0f, 37.5f, 10.0f }, 1.0f, CModel_X_Manager::TYPE::MEMO_01);

	// メモの生成
	CFurniture::Create({ 52.5f, 27.5f, 10.0f }, 1.0f, CModel_X_Manager::TYPE::MEMO_00);

	// ランプの生成
	CFurniture::Create({ 0.0f, 55.0f, -10.0f }, 2.0f, CModel_X_Manager::TYPE::LAMP);

	// テレビ台の生成
	CFurniture::Create({ 0.0f, -31.0f, 0.0f }, 4.0f, CModel_X_Manager::TYPE::TV_STAND);
}

//============================================================================
// 生成
//============================================================================
void CRenderer::Create()
{
	if (m_pRenderer != nullptr)
	{ // 二重生成禁止
		assert(false);
	}

	// インスタンスを生成
	m_pRenderer = DBG_NEW CRenderer{};
}

//============================================================================
// 疑似スクリーン用テクスチャの生成
//============================================================================
HRESULT CRenderer::CreateTex()
{
	// テクスチャを作成
	HRESULT hr =  CRenderer::GetInstance()->GetDeviece()->CreateTexture(
		SCREEN_WIDTH,			// U
		SCREEN_HEIGHT,			// V
		0,						// ミップマップレベル
		D3DUSAGE_RENDERTARGET,	// テクスチャの性質
		D3DFMT_A8R8G8B8,		// ピクセルフォーマット
		D3DPOOL_DEFAULT,		// メモリ管理フラグ
		&m_pMonitorTex,			// テクスチャ保存先
		nullptr);				// ハンドル

	// テクスチャのサーフェイスを取得
	m_pMonitorTex->GetSurfaceLevel(0, &m_pMonitorSurface);

	return hr;
}

//============================================================================
// 終了処理
//============================================================================
void CRenderer::Uninit()
{
	// 全オブジェクト解放処理
	CObject::ReleaseAll();

	// 疑似スクリーンの破棄
	CFakeScreen::GetInstance()->Release();

	// Xモデルマネージャー破棄
	CModel_X_Manager::GetInstance()->Release();

	// テクスチャマネージャー破棄
	CTexture_Manager::GetInstance()->Release();

	// サーフェイス情報の破棄
	if (m_pMonitorSurface != nullptr)
	{
		m_pMonitorSurface->Release();
		m_pMonitorSurface = nullptr;
	}

	// テクスチャ情報の破棄
	if (m_pMonitorTex != nullptr)
	{
		m_pMonitorTex->Release();
		m_pMonitorTex = nullptr;
	}

	// フォントの破棄
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}

	// Direct3Dデバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}