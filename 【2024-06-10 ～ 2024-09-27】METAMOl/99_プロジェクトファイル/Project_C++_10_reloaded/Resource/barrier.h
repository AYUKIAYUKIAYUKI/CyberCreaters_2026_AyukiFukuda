//============================================================================
// 
// バリア、ヘッダファイル [barrier.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _BARRIER_H_
#define _BARRIER_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// バリアクラス
//****************************************************
class CBarrier : public CObject_X
{
public:

	CBarrier();		// デフォルトコンストラクタ
	~CBarrier();	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CBarrier* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot);	// 生成
};

#endif	// _BARRIER_H_