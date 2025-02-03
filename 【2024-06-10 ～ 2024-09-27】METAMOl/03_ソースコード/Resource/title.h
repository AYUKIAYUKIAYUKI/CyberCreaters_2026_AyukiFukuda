//============================================================================
// 
// タイトル、ヘッダファイル [title.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _TITLE_H_
#define _TITLE_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "scene.h"

// タイトル表示用
#include "bg.h"
#include "text.h"
#include "input_ui.h"

//****************************************************
// タイトルクラス
//****************************************************
class CTitle : public CScene
{
public:

	CTitle();			// コンストラクタ
	~CTitle() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static int GetSelect();	// モード選択情報取得

private:

	//****************************************************
	// UIタイプ
	//****************************************************
	enum class UI_TYPE
	{
		NORMAL = 0,
		CHALLENGE,
		CURSOR,
		TITLE,
		MAX
	};

	CBg* m_pBg;										// 背景情報のポインタ
	CText* m_pUI[static_cast<int>(UI_TYPE::MAX)];	// UI用
	CInput_UI* m_pSpeech;							// ふきだし表示用
	int m_nSelect;									// モード選択情報
};

#endif // _TITLE_H_