//============================================================================
// 
// インプットUI、ヘッダファイル [input_ui.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _INPUT_UI_H_
#define _INPUT_UI_H_// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_3D.h"
#include "texture_manager.h"

//****************************************************
// インプットUIクラス
//****************************************************
class CInput_UI : public CObject_3D
{
public:

	CInput_UI();			// デフォルトコンストラクタ
	~CInput_UI() override;	// デストラクタ

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

	static CInput_UI* Create(CTexture_Manager::TYPE TexType);	// 生成

private:

	virtual void Appear();		// 出現
	virtual void Disappear();	// 消滅

	void UpdateCNT();	// CNTの更新
	void UpdateBoard();	// ボードの更新
	void UpdateSpeech();	// ふきだしの更新

	int m_nType;						// 種類
	CTexture_Manager::TYPE m_TexType;	// テクスチャタイプを保持
	int m_nDuration;					// 汎用カウント
	bool m_bAppear;						// 出現フラグ
	bool m_bDisappear;					// 消滅フラグ
	D3DXVECTOR3 m_posTarget;			// 目標座標
	D3DXVECTOR3 m_rotTarget;			// 目標向き
	D3DXVECTOR3 m_sizeTarget;			// 目標サイズ
	D3DXCOLOR m_colTarget;				// 目標色
};

#endif // _INPUT_UI_