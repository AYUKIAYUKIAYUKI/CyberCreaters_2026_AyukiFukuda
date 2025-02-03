////============================================================================
//// 
//// 箱型の判定表示、ヘッダファイル [render_collision_box.h]
//// Author : 福田歩希
//// 
////============================================================================
//
//#ifndef _RENDER_COLLISION_BOX_H_
//#define _RENDER_COLLISION_BOX_H_	// 二重インクルード防止
//
////****************************************************
//// インクルードファイル
////****************************************************
//#include "render_collision.h"
//
////****************************************************
//// 箱型の判定表示クラス
////****************************************************
//class CRender_Collision_Box final : public CRender_Collision
//{
//public:
//
//	CRender_Collision_Box();	// コンストラクタ
//	~CRender_Collision_Box();	// デストラクタ
//
//	HRESULT Init() override;	// 初期設定
//	void Uninit() override;		// 終了処理
//	void Update() override;		// 更新処理
//	void Draw() override;		// 描画処理
//
//	static CRender_Collision_Box* Create();	// 生成
//};
//
//#endif	// _RENDER_COLLISION_BOX_