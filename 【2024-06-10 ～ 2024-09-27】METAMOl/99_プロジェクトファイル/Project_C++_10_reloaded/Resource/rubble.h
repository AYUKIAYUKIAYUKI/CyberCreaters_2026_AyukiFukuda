//============================================================================
// 
// がれきエフェクト、ヘッダファイル [rubble.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _RUBBLE_H_
#define _RUBBLE_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// がれきエフェクトクラス
//****************************************************
class CRubble : public CObject_X
{
public:

	CRubble();	// コンストラクタ
	~CRubble();	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	D3DXVECTOR3& GetVelocity();				// 加速度を取得
	void SetVelocity(D3DXVECTOR3 Velocity);	// 加速度を設定

	static CRubble* Create(int nType, D3DXVECTOR3 Pos, D3DXVECTOR3 Velocity);	// 生成

private:

	void CheckDisappear();	// 消滅するかチェック

	D3DXVECTOR3 m_Velocity;	// 加速度
};

#endif	// _RUBBLE_H_