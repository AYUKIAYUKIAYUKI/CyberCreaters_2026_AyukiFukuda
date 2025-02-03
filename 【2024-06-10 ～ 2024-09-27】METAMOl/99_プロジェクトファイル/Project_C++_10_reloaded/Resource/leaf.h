//============================================================================
// 
// 葉っぱ、ヘッダファイル [leaf.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _LEAF_H_
#define _LEAF_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_billboard.h"

// テクスチャ取得用
#include "texture_manager.h"

//****************************************************
// 葉っぱクラス
//****************************************************
class CLeaf : public CObject_billboard
{
public:

	CLeaf();				// デフォルトコンストラクタ
	~CLeaf() override;		// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static void UpdateToCreate();	// 生成用更新
	static CLeaf* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, LPDIRECT3DTEXTURE9 tex);	// 生成

private:

	//****************************************************
	// 振動の種類
	//****************************************************
	enum class OSCILLATION
	{
		NONE = 0,	// 無し
		WEAK,		// 弱め
		MODERATE,	// 普通
		STRONG,		// 強い
		MAX
	};

	void Rotate();		// 回転
	void Translate();	// 移動
	
	static OSCILLATION GetRandomOscillation();		// ランダムな振動の種類を取得
	static LPDIRECT3DTEXTURE9 GetRandomTexture();	// ランダムな葉っぱテクスチャの種類を取得

	OSCILLATION m_type;		// 振動の種類
	D3DXVECTOR3 m_velocity;	// 加速度

	static int m_nCntSpawn;	// 生成間隔
};

#endif // _LEAF_H_