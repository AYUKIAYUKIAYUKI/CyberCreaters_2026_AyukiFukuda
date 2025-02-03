//============================================================================
// 
// チュートリアル、ヘッダファイル [tutorial_manager.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _TUTORIAL_MANAGER_H_
#define _TUTORIAL_MANAGER_H	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "hand.h"
#include "input_ui.h"
#include "text.h"
#include "texture_manager.h"

//****************************************************
// チュートリアルマネージャークラス
//****************************************************
class CTutorial_Manager
{
public:

	static void UpdateTutorial();					// チュートリアルの更新
	static void DeleteInstance();					// 削除
	static CTexture_Manager::TYPE GetTexType();		// テクスチャタイプを取得

private:

	CTutorial_Manager();	// デフォルトコンストラクタ
	~CTutorial_Manager();	// デストラクタ

	void CreateText();		// テキストの生成
	void DeleteText();		// テキストの削除
	void CheckPlayerPos();	// プレイヤーの座標を確認
	
	static void CreateInstance();	// 生成

	int m_nCnt09;						// 09用カウント
	CText* m_pText;						// テキストのポインタ
	CHand* m_apHand[2];					// 手とかのポインタ
	CInput_UI* m_apInput_UI[3];			// インプットUIのポインタ
	CTexture_Manager::TYPE m_TexType;	// テクスチャタイプを保持

	static CTutorial_Manager* m_pInstance;	// 自クラスのポインタ
};

#endif	// _TUTORIAL_MANAGER_H