//============================================================================
// 
// 背景、ヘッダファイル [bg.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _BG_H_
#define _BG_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_2D.h"

// テクスチャ取得用
#include "texture_manager.h"

//****************************************************
// 背景クラス
//****************************************************
class CBg : public CObject_2D
{
public:

	CBg();				// コンストラクタ
	~CBg() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CBg* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture_Manager::TYPE type);	// 生成

private:

	void PAKUPAKU();	// パクパクします

	int m_nCntPAKU;	// パクパク回数
	int m_nDelayPAKU;	// パクパク遅延
};

#endif // _BG_H_