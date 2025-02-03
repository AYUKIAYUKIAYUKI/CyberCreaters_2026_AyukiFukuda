//============================================================================
// 
// 波紋エフェクト、ヘッダファイル [ripple.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _RIPPLE_H_
#define _RIPPLE_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// 波紋エフェクトクラス
//****************************************************
class CRipple : public CObject_X
{
public:

	CRipple();	// コンストラクタ
	~CRipple();	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	D3DXVECTOR3& GetVelocity();				// 加速度を取得
	void SetVelocity(D3DXVECTOR3 velocity);	// 加速度を設定

	static CRipple* Create(D3DXVECTOR3&& pos, D3DXVECTOR3 velocity);	// 生成

private:

	D3DXVECTOR3 m_velocity;	// 加速度
};

#endif	// _RIPPLE_H_