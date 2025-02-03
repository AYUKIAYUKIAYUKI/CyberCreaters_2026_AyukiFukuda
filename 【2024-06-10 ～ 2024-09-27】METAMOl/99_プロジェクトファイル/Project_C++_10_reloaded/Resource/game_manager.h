//============================================================================
// 
// ゲームマネージャー、ヘッダファイル [game_manager.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "text.h"

//****************************************************
// ゲームマネージャークラス
//****************************************************
class CGameManager final
{
public:

	//****************************************************
	// ゲームフェーズ識別
	//****************************************************
	enum class PHASE
	{
		NONE = 0,	// 無し
		SELECT,		// レベル選択
		START,		// レベル開始
		INGAME,		// レベル進行
		FINISH,		// レベル終了
		RETIRE,		// レベルリタイア
		C_START,	// チャレンジ開始
		C_INGAME,	// チャレンジ進行
		C_FINISH,	// チャレンジ終了
		MAX,
	};

	void Create();			// 生成
	void Init();			// 初期設定
	void Init(PHASE phase);	// 初期設定とフェーズ設定
	void Release();			// 解放
	void Uninit();			// 終了処理
	void Update();			// 更新処理

	PHASE GetPhase();			// フェーズ取得
	void SetPhase(PHASE phase);	// フェーズ設定

	bool GetEndTutorial();					// チュートリアル終了フラグを取得
	int GetMaxStage();						// ステージ数を取得
	int GetSelectLevel();					// 選択レベル番号を取得
	std::vector<bool> GetCollectAchieve();	// アチーブ回収状態
	int GetSelectChallenge();				// チャレンジ選択

	static CGameManager* GetInstance();	// ゲームマネージャーを取得

private:

	//****************************************************
	// プレビューフェーズ識別
	//****************************************************
	enum class PREVIEW
	{
		NONE = 0,	// 無し
		BIGEN,		// 開始
		SHOWING,	// 見せつけ
		END,		// 終了
		MAX,
	};

	CGameManager();		// デフォルトコンストラクタ
	~CGameManager();	// デストラクタ

	void ImportLevel();		// レベル読み込み
	void StartPreview();	// プレビュー開始
	void StagePreview();	// ステージプレビュー
	void ChallengeResult();	// チャレンジリザルト

	bool m_bEndTutorial;					// チュートリアル確認
	PHASE m_phase;							// フェーズ識別
	int m_nMaxStage;						// ステージ数
	int m_nSelectLevel;						// レベル選択
	int m_nOldSelectLevel;					// 過去のレベル選択
	std::vector<std::string> m_stagePath;	// ステージパス
	std::vector<bool> m_vbCollectAchieve;	// アチーブ回収状態
	int m_nSelectChallenge;					// チャレンジ選択
	PREVIEW m_Preview;						// プレビュー状態
	int m_nCntPreview;						// プレビュー待機カウント

	static CGameManager* m_pInstance;	// ゲームマネージャー
};

#endif // _GAME_MANAGER_H_