//============================================================================
// 
// テキスト、ヘッダファイル [text.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _TEXT_H_
#define _TEXT_H_// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_UI.h"
#include "texture_manager.h"

//****************************************************
// テキストクラス
//****************************************************
class CText : public CObject_UI
{
public:

	CText();			// デフォルトコンストラクタ
	~CText() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CText* Create(CTexture_Manager::TYPE tex);	// 生成

private:

	void Appear() override;		// 出現
	void Disappear() override;	// 消滅
};

#endif // _TEXT_H_