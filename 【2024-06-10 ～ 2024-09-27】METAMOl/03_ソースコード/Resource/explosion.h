////============================================================================
//// 
//// 爆発、ヘッダファイル [explosion.h]
//// Author : 福田歩希
//// 
////============================================================================
//
//#ifndef _EXPLOSION_H_
//#define _EXPLOSION_H_	// 二重インクルード防止
//
////****************************************************
//// インクルードファイル
////****************************************************
//#include "object_billboard.h"
//
////****************************************************
//// 爆発クラス
////****************************************************
//class CExplosion : public CObject_billboard
//{
//public:
//
//	CExplosion();			// デフォルトコンストラクタ
//	~CExplosion() override;	// デストラクタ
//
//	HRESULT Init() override;	// 初期設定
//	void Uninit() override;		// 終了処理
//	void Update() override;		// 更新処理
//	void Draw() override;		// 描画処理
//
//	static CExplosion* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 生成
//
//private:
//
//	bool Animation();	// アニメーション
//
//	int m_nCntTexChange;	// テクスチャ変更管理
//};
//
//#endif // _EXPLOSION_H_