//============================================================================
// 
// Xオブジェクト、ヘッダファイル [object_X.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _OBJECT_X_H_
#define _OBJECT_X_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object.h"

// Xモデル情報用
#include "model_X_manager.h"

//****************************************************
// Xオブジェクトクラス
//****************************************************
class CObject_X : public CObject
{
public:

	CObject_X(int nPriority = static_cast<int>(LAYER::NONE));	// コンストラクタ
	~CObject_X() override;										// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	void BindModel(CModel_X_Manager::MODEL* pModel);	// モデル割当

	D3DXVECTOR3 GetPos();			// 位置取得
	void SetPos(D3DXVECTOR3 pos);	// 位置設定

	D3DXVECTOR3& GetRot();			// 向き取得
	void SetRot(D3DXVECTOR3 rot);	// 向き設定

	D3DXVECTOR3 GetSize();			// サイズ取得
	void SetSize(D3DXVECTOR3 size);	// サイズ設定

	float& GetScale() { return m_fScale; }				// 縮尺取得
	void SetScale(float scale) { m_fScale = scale; }	// 縮尺設定

	float& GetAlpha();				// アルファ値取得
	void SetAlpha(float fAlpha);	// アルファ値設定

	virtual CObject_X* Create();	// 生成

private:

	static const float DEFAULT_ALPHA_VALUE;	// デフォルトアルファ値

	void SetMtxWorld();	// ワールド行列設定

	CModel_X_Manager::MODEL* m_pModel;	// モデル情報
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_rot;					// 向き
	D3DXVECTOR3 m_size;					// サイズ
	float m_fScale;						// 縮尺
	float m_fAlpha;						// アルファ値
	D3DXMATRIX m_mtxWorld;				// ワールド行列
};

#endif // _OBJECT_X_H_