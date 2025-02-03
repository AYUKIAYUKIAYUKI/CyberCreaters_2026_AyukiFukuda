//============================================================================
// 
// マネージャー、ヘッダファイル [managaer.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _MANAGER_H_
#define _MANAGER_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "camera.h"
#include "light.h"
#include "input.h"
#include "scene.h"

//****************************************************
// マネージャークラス
//****************************************************
class CManager final
{
public:

	CManager();		// デフォルトコンストラクタ
	~CManager();	// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);	// 初期設定
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Draw();	// 描画処理

	static CCamera* GetCamera();				// カメラ取得
	static CLight* GetLight();					// ライト取得
	static CInputKeyboard* GetKeyboard();		// キーボード取得
	static CInputPad* GetPad();					// パッド取得
	static CScene* GetScene();					// シーン取得
	static void SetScene(CScene::MODE mode);	// シーン設定

private:

	static CCamera* m_pCamera;			// カメラ管理
	static CLight* m_pLight;			// ライト管理
	static CInputKeyboard* m_pKeyboard;	// キーボード管理
	static CInputPad* m_pPad;			// パッド管理
	static CScene* m_pScene;			// シーン管理
};

#endif // _MANAGER_H_
