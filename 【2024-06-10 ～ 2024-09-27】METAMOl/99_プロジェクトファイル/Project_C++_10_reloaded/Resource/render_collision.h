//============================================================================
// 
// 判定表示、ヘッダファイル [render_collision.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _RENDER_COLLISION_H_
#define _RENDER_COLLISION_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object.h"

//****************************************************
// 判定表示クラス
//****************************************************
class CRender_Collision : public CObject
{
public:

	CRender_Collision(D3DXVECTOR3& m_posRef, D3DXVECTOR3& sizeRef, int nPriority = static_cast<int>(LAYER::FRONT));	// コンストラクタ
	~CRender_Collision() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	// 箱型の作成
	static CRender_Collision* Create(D3DXVECTOR3& posRef, D3DXVECTOR3& sizeRef);	// 生成

private:

	// 箱型のみの定数
	static const int m_nNumVtx;			// 頂点数
	static const int m_nNumPrimitive;	// 辺数
	static const int m_nNumIdx;			// インデックス数

	HRESULT CreateVtxBuff();	// 頂点バッファの生成
	HRESULT CreateIdxBuff();	// インデックスバッファの生成
	void SetVtx();				// 頂点の設定
	void SetMtxWorld();			// ワールド行列設定

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// インデックスバッファのポインタ
	D3DXVECTOR3& m_posRef;				// 参照位置
	D3DXCOLOR m_col;					// 色
	D3DXMATRIX m_mtxWorld;				// ワールド行列

	// 箱型のみのメンバ
	D3DXVECTOR3& m_size;	// サイズ
};

#endif	// _RENDER_COLLISION_H_