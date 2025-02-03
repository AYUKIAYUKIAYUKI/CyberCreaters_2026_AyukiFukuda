//============================================================================
// 
// アチーブ、ヘッダファイル [achievement.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _ACHIEVEMENT_H_
#define _ACHIEVEMENT_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// アチーブクラス
//****************************************************
class CAchieve : public CObject_X
{
public:

	CAchieve();					// デフォルトコンストラクタ
	CAchieve(LAYER priority);	// プライオリティ指定コンストラクタ
	~CAchieve() override;		// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CAchieve* Create(D3DXVECTOR3 pos);	// 生成
};

#endif // _ACHIEVEMENT_H_