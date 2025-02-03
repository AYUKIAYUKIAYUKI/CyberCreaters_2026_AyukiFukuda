//============================================================================
// 
// ダミー、ヘッダファイル [dummy.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _DUMMY_H_
#define _DUMMY_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// ダミークラス
//****************************************************
class CDummy : public CObject_X
{
public:

	CDummy();				// コンストラクタ
	~CDummy() override;		// デストラクタ

	HRESULT Init() override;		// 初期設定
	void Uninit() override;			// 終了処理
	void Update() override;			// 更新処理
	void Draw() override;			// 描画処理
	void Control();					// 操作
	void ChangeModel(int nPattern);	// モデルを変更

	static CDummy* Create();	// 生成

private:

	void Translate();	// 移動
};

#endif // _DUMMY_H_