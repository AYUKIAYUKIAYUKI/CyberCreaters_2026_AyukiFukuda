//************************************************
//
// フェーズ表示、ヘッダファイル[phase.h]
// Author：福田歩希
//
//************************************************
#ifndef _PHASE_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _PHASE_H_	// (二重インクルード防止、マクロ定義する)

/*---【インクルードファイル】---*/
#include "gameUI.h"

/*---【プロトタイプ宣言】---*/
void InitPhase(int joined);	// 初期
void UninitPhase(void);		// 終了
void UpdatePhase(void);		// 更新
void DrawPhase(void);		// 描画

UI* GetInfoPhaseUI(void);		// フェーズ表示の取得
bool* ChangePhasePlay(void);	// フェーズの変更を検出
bool* ChangeEnemyPlay(void);	// 出現数の変更を検出
bool* ChangeScorePlay(void);	// スコアの変更を検出

#endif