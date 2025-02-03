//============================================================================
// 
// 可壊でかブロック、ヘッダファイル [block_destructible_big.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _BLOCK_DESTRUCRTIBLE_BIG_H_
#define _BLOCK_DESTRUCRTIBLE_BIG_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"
#include "rubble.h"

//****************************************************
// 可壊でかブロッククラス
//****************************************************
class CBlockDestructibleBig : public CObject_X
{
public:

	CBlockDestructibleBig();				// デフォルトコンストラクタ
	CBlockDestructibleBig(LAYER priority);	// プライオリティ指定コンストラクタ
	~CBlockDestructibleBig() override;		// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理
	bool Damage(int nAtk = -1);	// ダメージ処理

	static CBlockDestructibleBig* Create(D3DXVECTOR3 pos);	// 生成

private:

	int m_nLife;	// ライフ
};

#endif // _BLOCK_DESTRUCTIBLE_BIG_H_