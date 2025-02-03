//============================================================================
// 
// 星エフェクト、ヘッダファイル [star.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _STAR_H_
#define _STAR_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// 星エフェクトクラス
//****************************************************
class CStar : public CObject_X
{
public:

	CStar();	// コンストラクタ
	~CStar();	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	D3DXVECTOR3& GetVelocity();				// 加速度を取得
	void SetVelocity(D3DXVECTOR3 velocity);	// 加速度を設定

	static CStar* Create(D3DXVECTOR3&& pos, D3DXVECTOR3 velocity);	// 生成

private:

	D3DXVECTOR3 m_velocity;	// 加速度
};

#endif	// _STAR_H_