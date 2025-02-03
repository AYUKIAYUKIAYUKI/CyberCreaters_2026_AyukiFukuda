//============================================================================
// 
// ゴール、ヘッダファイル [goal.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _GOAL_H_
#define _GOAL_H_// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// ゴールクラス
//****************************************************
class CGoal : public CObject_X
{
public:

	CGoal();			// デフォルトコンストラクタ
	~CGoal() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	D3DXVECTOR3 GetActualPos();			// 実座標を取得
	void SetActualPos(D3DXVECTOR3 Pos);	// 実座標を設定

	static CGoal* Create(D3DXVECTOR3 Pos);	// 生成

private:

	D3DXVECTOR3 m_ActualPos;	// 実座標
	D3DXVECTOR3 m_PosTarget;	// 目標座標
	D3DXVECTOR3 m_RotTarget;	// 目標向き
	float m_fScaleTarget;		// 目標縮尺
};

#endif // _GOAL_H_