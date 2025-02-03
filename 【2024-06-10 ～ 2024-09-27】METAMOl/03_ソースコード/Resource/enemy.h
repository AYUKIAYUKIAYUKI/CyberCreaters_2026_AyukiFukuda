//============================================================================
// 
// 敵、ヘッダファイル [enemy.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _ENEMY_H_
#define _ENEMY_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// エネミークラス
//****************************************************
class CEnemy : public CObject_X
{
public:

	CEnemy();				// デフォルトコンストラクタ
	CEnemy(LAYER priority);	// プライオリティ指定コンストラクタ
	~CEnemy() override;		// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理
	bool Collision();			// 当たり判定

	static CEnemy* Create(D3DXVECTOR3 pos);		// 生成

private:

	int m_nCast;	// 攻撃間隔
};

#endif // _ENEMY_H_