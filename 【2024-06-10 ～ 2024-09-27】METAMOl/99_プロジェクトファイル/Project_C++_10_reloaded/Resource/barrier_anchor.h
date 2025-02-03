//============================================================================
// 
// バリアアンカー、ヘッダファイル [barrier_anchor.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _BARRIER_ANCHOR_H_
#define _BARRIER_ANCHOR_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// バリアアンカークラス
//****************************************************
class CBarrier_Anchor : public CObject_X
{
public:

	CBarrier_Anchor();	// デフォルトコンストラクタ
	~CBarrier_Anchor();	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CBarrier_Anchor* Create(D3DXVECTOR3 Pos);	// 生成
};

#endif	// _BARRIER_ANCHOR_H_