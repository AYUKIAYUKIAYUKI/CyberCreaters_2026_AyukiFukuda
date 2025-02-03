//============================================================================
// 
// とげブロック、ヘッダファイル [block_spikes.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _BLOCK_SPIKES_H_
#define _BLOCK_SPIKES_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// とげブロッククラス
//****************************************************
class CBlockSpikes : public CObject_X
{
public:

	CBlockSpikes();					// デフォルトコンストラクタ
	CBlockSpikes(LAYER priority);	// プライオリティ指定コンストラクタ
	~CBlockSpikes() override;		// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CBlockSpikes* Create(D3DXVECTOR3 pos);		// 生成
};

#endif // _BLOCK_SPIKES_H_