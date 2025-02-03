//============================================================================
// 
// [KARIHAIKEI.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _KARIHAIKEI_H_
#define _KARIHAIKEI_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// 
//****************************************************
class KARIHAIKEI : public CObject_X
{
public:

	KARIHAIKEI();			// デフォルトコンストラクタ
	~KARIHAIKEI() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static KARIHAIKEI* Create();	// 生成
};

#endif // _KARIHAIKEI_H_