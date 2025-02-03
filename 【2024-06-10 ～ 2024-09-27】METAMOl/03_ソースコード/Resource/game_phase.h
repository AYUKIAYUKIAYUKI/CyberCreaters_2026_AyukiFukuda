////============================================================================
//// 
//// ゲームフェーズ、ヘッダファイル [game_phase.h]
//// Author : 福田歩希
//// 
////============================================================================
//
//#ifndef _GAME_PHASE_H_
//#define _GAME_PHASE_H_	// 二重インクルード防止
//
////****************************************************
//// インクルードファイル
////****************************************************
//#include "game_manager.h"
//
////****************************************************
//// ゲームフェーズクラス
////****************************************************
//class CGamePhase
//{
//public:
//
//	CGamePhase();			// コンストラクタ
//	virtual ~CGamePhase();	// デストラクタ
//
//	virtual void Enter() = 0;	// 変更開始
//	virtual void Update() = 0;	// 更新
//	virtual void Exit() = 0;	// 変更終了
//};
//
////****************************************************
//// レベル開始フェーズクラス
////****************************************************
//class CGamePhase_Start : public CGamePhase
//{
//public:
//
//	CGamePhase_Start();				// コンストラクタ
//	virtual ~CGamePhase_Start();	// デストラクタ
//
//	void Enter() override;	// 変更開始
//	void Update() override;	// 更新
//	void Exit() override;	// 変更終了
//};
//
////****************************************************
//// ゲーム進行フェーズクラス
////****************************************************
//class CGamePhase_Ingame : public CGamePhase
//{
//public:
//
//	CGamePhase_Ingame();			// コンストラクタ
//	virtual ~CGamePhase_Ingame();	// デストラクタ
//
//	void Enter() override;	// 変更開始
//	void Update() override;	// 更新
//	void Exit() override;	// 変更終了
//};
//
////****************************************************
//// レベル終了フェーズクラス
////****************************************************
//class CGamePhase_Finish : public CGamePhase
//{
//public:
//
//	CGamePhase_Finish();			// コンストラクタ
//	virtual ~CGamePhase_Finish();	// デストラクタ
//
//	void Enter() override;	// 変更開始
//	void Update() override;	// 更新
//	void Exit() override;	// 変更終了
//};
//
////****************************************************
//// ゲームフェーズマネージャークラス
////****************************************************
//class CGamePhaseManager
//{
//public:
//
//	CGamePhaseManager();	// コンストラクタ
//	~CGamePhaseManager();	// デストラクタ
//
//	void CheckPhaseChange();	// フェーズの変更を確認
//	void Init();				// 初期設定
//	void Uninit();				// 終了処理
//
//	CGameManager::PHASE GetPendingPhase();				// 変更予定のフェーズを取得
//	void SetPendingPhase(CGameManager::PHASE phase);	// 変更予定のフェーズを設定
//
//private:
//
//	void Create(CGameManager::PHASE phase);	// 新たなフェーズを生成
//
//	CGamePhase* m_pPhase;				// フェーズのポインタ
//	CGameManager::PHASE m_PendingPhase;	// 変更予定のフェーズ
//};
//
//#endif // _GAME_PHASE_H_