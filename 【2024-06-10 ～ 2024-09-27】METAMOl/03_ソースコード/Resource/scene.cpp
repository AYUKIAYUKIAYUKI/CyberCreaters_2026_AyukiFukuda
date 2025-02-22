//============================================================================
// 
// シーン管理 [scene.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "scene.h"

// シーン用
#include "challenge.h"
#include "fakescreen.h"
#include "game.h"
#include "result.h"
#include "stage_debug.h"
#include "title.h"

// オブジェクト管理用
#include "object.h"

//============================================================================
// コンストラクタ
//============================================================================
CScene::CScene() : m_mode(MODE::NONE)
{

}

//============================================================================
// デストラクタ
//============================================================================
CScene::~CScene()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CScene::Init()
{
	return S_OK;
}

//============================================================================
// 終了処理
//============================================================================
void CScene::Uninit()
{
	// ウェーブの強制終了
	CFakeScreen::GetInstance()->StopWave();

	// スクリーン画面内の解放処理
	CObject::ReleaseScreen();

	// UIのみの解放処理
	CObject::ReleaseUI();
}

//============================================================================
// 更新処理
//============================================================================
void CScene::Update()
{

}

//============================================================================
// 描画処理
//============================================================================
void CScene::Draw()
{

}

//============================================================================
// モードを取得
//============================================================================
CScene::MODE CScene::GetMode()
{
	return m_mode;
}

//============================================================================
// 生成
//============================================================================
CScene* CScene::Create(MODE mode)
{
	// 基底クラスのポインタを用意
	CScene* pScene = nullptr;

	switch (mode)
	{
	case CScene::MODE::TITLE:
		pScene = DBG_NEW CTitle;
		pScene->m_mode = MODE::TITLE;
		break;

	case CScene::MODE::GAME:
		pScene = DBG_NEW CGame;
		pScene->m_mode = MODE::GAME;
		break;

	case CScene::MODE::STAGE:
		pScene = DBG_NEW CStage_Debug;
		pScene->m_mode = MODE::STAGE;
		break;

	//case CScene::MODE::RESULT:
	//	pScene = DBG_NEW CResult;
	//	pScene->m_mode = MODE::RESULT;
	//	break;

	case CScene::MODE::CHALLENGE:
		pScene = DBG_NEW CChallenge;
		pScene->m_mode = MODE::CHALLENGE;
		break;

	default:
		assert(false);
		break;
	}

	if (pScene == nullptr)
	{ // 生成失敗
		assert(false);
	}

	// 初期設定
	/* ここで初期化をする -> シーンのInitでモードに応じた生成のために、ダングリングしたシーンポインタにアクセスする -> エラー */
	//pScene->Init();

	return pScene;
}