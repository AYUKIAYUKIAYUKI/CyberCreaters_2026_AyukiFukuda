//============================================================================
// 
// タイム、ヘッダファイル [timer.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _TIMER_H_
#define _TIMER_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_UI.h"
#include "number.h"
#include "text.h"
#include "game_manager.h"

//****************************************************
// タイムクラス
//****************************************************
class CTimer : public CObject_UI
{
public:

	CTimer();			// デフォルトコンストラクタ
	~CTimer() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	static CTimer* Create();						// 生成
	static void SwitchControlByPahse(int nSelect);	// フェーズによる動作切替
	static void TimerReset();						// 時間リセット
	static void ExportTimer(int nSelect);			// タイムの書き出し

private:

	static const int MAX_DIGIT = 3;	// 最大桁数

	void Appear() override;			// 出現
	void Disappear() override;		// 消滅
	int ImportTimer(int nSelect);	// タイムの読み込み

	int m_nCntFrame;				// フレームカウント
	int m_nTimer;					// タイム情報
	CText* m_pText;					// テキスト情報
	CNumber* m_apNumber[MAX_DIGIT];	// 数字情報
};

#endif	// _TIMER_H_