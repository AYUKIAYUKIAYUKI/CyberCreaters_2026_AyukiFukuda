//============================================================================
// 
// バリアマネージャー、ヘッダファイル [barrier_manager.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _BARRIER_MANAGER_H_
#define _BARRIER_MANAGER_H	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "barrier.h"
#include "barrier_anchor.h"

//****************************************************
// バリアマネージャークラス
//****************************************************
class CBarrier_Manager
{
public:

	CBarrier_Manager();		// デフォルトコンストラクタ
	~CBarrier_Manager();	// デストラクタ

	static void CreateStageBarrier();	// ステージにバリアを生成する
	static float GetCurrentMinPosY();	// 現在のバリアの最も低い座標を取得

private:

	static float m_fCurrentMinPosY;	// 最新のバリアの最も低い座標
};

#endif	// _BARRIER_MANAGER_H