//============================================================================
// 
// リミットタイム、ヘッダファイル [limit_timer.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _LIMIT_TIMER_H_
#define _LIMIT_TIMER_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_UI.h"
#include "number.h"
#include "text.h"
#include "game_manager.h"

//****************************************************
// リミットタイムクラス
//****************************************************
class CLimit_Timer : public CObject_UI
{
public:

	CLimit_Timer();				// デフォルトコンストラクタ
	~CLimit_Timer() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	int GetTimer();	// タイム情報を取得

	static CLimit_Timer* Create();	// 生成

private:

	static const int MAX_DIGIT = 2;	// 最大桁数

	void Decrement();				// 時間減少
	void TimerReset();				// 時間リセット
	void Appear() override;			// 出現
	void Disappear() override;		// 消滅

	int m_nCntFrame;				// フレームカウント
	int m_nTimer;					// タイム情報
	CText* m_pText;					// テキスト情報
	CNumber* m_apNumber[MAX_DIGIT];	// 数字情報
};

#endif	// _LIMIT_TIMER_H_