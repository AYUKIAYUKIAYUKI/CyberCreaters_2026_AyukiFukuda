//============================================================================
// 
// 家具、ヘッダファイル [furniture.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _FURNITURE_H_
#define _FURNITURE_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// 家具クラス
//****************************************************
class CFurniture : public CObject_X
{
public:

	CFurniture();			// デフォルトコンストラクタ
	~CFurniture() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CFurniture* Create(D3DXVECTOR3 pos, float fScale, CModel_X_Manager::TYPE type);	// 生成
};

#endif // _FURNITURE_H_