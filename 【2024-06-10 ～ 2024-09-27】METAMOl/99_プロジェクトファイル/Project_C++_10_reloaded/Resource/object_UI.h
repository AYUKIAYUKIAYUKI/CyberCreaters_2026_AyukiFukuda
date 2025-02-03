//============================================================================
// 
// UIオブジェクト管理、ヘッダファイル [object_UI.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _OBJECT_UI_H_
#define _OBJECT_UI_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_2D.h"

//****************************************************
// UIオブジェクトクラス
//****************************************************
class CObject_UI : public CObject_2D
{
public:

	CObject_UI();												// デフォルトコンストラクタ
	CObject_UI(int nPriority = static_cast<int>(LAYER::UI));	// 描画優先度指定コンストラクタ
	~CObject_UI() override;										// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	bool GetAppear();				// 出現フラグ取得
	void SetAppear(bool bAppear);	// 出現フラグ設定

	bool GetDisappear();				// 消滅フラグ取得
	void SetDisappear(bool bDisappear);	// 消滅フラグ設定

	D3DXVECTOR3 GetPosTarget();					// 目標座標を取得
	void SetPosTarget(D3DXVECTOR3 posTarget);	// 目標座標を設定

	D3DXVECTOR3 GetRotTarget();					// 目標向きを取得
	void SetRotTarget(D3DXVECTOR3 rotTarget);	// 目標向きを設定

	D3DXVECTOR3 GetSizeTarget();				// 目標サイズを取得
	void SetSizeTarget(D3DXVECTOR3 sizeTarget);	// 目標サイズを設定

	D3DXCOLOR GetColTarget();			// 目標色
	void SetColTarget(D3DXCOLOR col);	// 目標色

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

#endif // _OBJECT_UI_H_