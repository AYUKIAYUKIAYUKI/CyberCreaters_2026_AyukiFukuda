//============================================================================
// 
// 弾、ヘッダファイル [bullet.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _BULLET_H_
#define _BULLET_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// 弾クラス
//****************************************************
class CBullet : public CObject_X
{
public:

	CBullet();				// デフォルトコンストラクタ
	CBullet(int nDuration);	// 寿命設定コンストラクタ
	~CBullet() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成

private:

	void Translate();	// 移動
	bool Collision();	// 当たり判定

	D3DXVECTOR3 m_posTarget;	// 目標座標
	D3DXVECTOR3 m_velocity;		// 加速度
	int m_nDuration;			// 寿命
};

#endif // _BULLET_H_