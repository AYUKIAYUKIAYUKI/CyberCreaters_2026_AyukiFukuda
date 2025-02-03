//============================================================================
// 
// 可壊ブロック、ヘッダファイル [block_destructible.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _BLOCK_DESTRUCRTIBLE_H_
#define _BLOCK_DESTRUCRTIBLE_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"
#include "rubble.h"

//****************************************************
// 可壊ブロッククラス
//****************************************************
class CBlockDestructible : public CObject_X
{
public:

	CBlockDestructible();				// デフォルトコンストラクタ
	CBlockDestructible(LAYER priority);	// プライオリティ指定コンストラクタ
	~CBlockDestructible() override;		// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CBlockDestructible* Create(D3DXVECTOR3 pos);	// 生成
};

#endif // _BLOCK_DESTRUCTIBLE_H_