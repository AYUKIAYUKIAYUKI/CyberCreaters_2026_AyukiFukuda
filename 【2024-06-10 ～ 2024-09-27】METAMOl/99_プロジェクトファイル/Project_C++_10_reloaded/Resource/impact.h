//============================================================================
// 
// 衝撃エフェクト、ヘッダファイル [impact.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _IMPACT_H_
#define _IMPACT_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// 衝撃エフェクトクラス
//****************************************************
class CImpact : public CObject_X
{
public:

	CImpact();	// コンストラクタ
	~CImpact();	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	D3DXVECTOR3& GetVelocity();				// 加速度を取得
	void SetVelocity(D3DXVECTOR3 Velocity);	// 加速度を設定

	static CImpact* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Velocity);	// 生成

private:

	void CheckDisappear();	// 消滅するかチェック

	D3DXVECTOR3 m_Velocity;	// 加速度
};

#endif	// _RUBBLE_H_