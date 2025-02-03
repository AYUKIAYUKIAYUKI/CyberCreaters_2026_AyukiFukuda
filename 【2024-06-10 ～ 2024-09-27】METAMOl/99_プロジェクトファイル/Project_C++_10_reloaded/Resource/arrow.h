//============================================================================
// 
// 矢印、ヘッダファイル [arrow.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _ARROW_H_
#define _ARROW_H_// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_3D.h"

//****************************************************
// 矢印クラス
//****************************************************
class CArrow : public CObject_3D
{
public:

	CArrow();			// デフォルトコンストラクタ
	~CArrow() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	void SetAppear();		// 出現設定
	void SetDisappear();	// 消滅設定

	D3DXVECTOR3 GetPosTarget();					// 目標座標を取得
	void SetPosTarget(D3DXVECTOR3 posTarget);	// 目標座標を設定

	D3DXVECTOR3 GetRotTarget();					// 目標向きを取得
	void SetRotTarget(D3DXVECTOR3 rotTarget);	// 目標向きを設定

	D3DXVECTOR3 GetSizeTarget();				// 目標サイズを取得
	void SetSizeTarget(D3DXVECTOR3 sizeTarget);	// 目標サイズを設定

	static CArrow* Create();	// 生成

private:

	virtual void Appear();		// 出現
	virtual void Disappear();	// 消滅

	bool m_bAppear;				// 出現フラグ
	bool m_bDisappear;			// 消滅フラグ
	D3DXVECTOR3 m_posTarget;	// 目標座標
	D3DXVECTOR3 m_rotTarget;	// 目標向き
	D3DXVECTOR3 m_sizeTarget;	// 目標サイズ
	D3DXCOLOR m_colTarget;		// 目標色
};

#endif // _ARROW_H_