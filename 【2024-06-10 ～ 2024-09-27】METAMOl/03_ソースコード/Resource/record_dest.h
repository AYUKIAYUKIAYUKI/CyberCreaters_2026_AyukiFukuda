//============================================================================
// 
// 破壊記録、ヘッダファイル [record_dest.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _RECORD_DEST_H_
#define _RECORD_DEST_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_UI.h"
#include "number.h"
#include "text.h"

//****************************************************
// 破壊記録クラス
//****************************************************
class CRecord_Dest : public CObject_UI
{
public:

	CRecord_Dest();				// デフォルトコンストラクタ
	~CRecord_Dest() override;	// デストラクタ

	HRESULT Init() override;		// 初期設定
	void Uninit() override;			// 終了処理
	void Update() override;			// 更新処理
	void Draw() override;			// 描画処理
	void ResetCntDest();			// 破壊記録をリセット
	void SetDisappearBestAndUI();	// 最高記録表示・選択肢を消去

	void SetTimeUp();	// 時間切れ判定設定
	bool GetTimeUp();	// 時間切れ判定取得

	static CRecord_Dest* Create();	// 生成
	static void AddDest();			// 破壊記録の増加
	static void ExportRecord();		// 破壊記録の書き出し

private:

	static const int MAX_DIGIT = 3;	// 最大桁数

	void Appear() override;			// 出現
	void Disappear() override;		// 消滅
	int ImportBestRecord();			// 最高記録の読み込み

	int m_nCntDest;						// 破壊記録
	bool m_bTimeUp;						// 時間切れ判定
	CText* m_pDestText;					// 今回テキスト
	CNumber* m_apDestNum[MAX_DIGIT];	// 今回数字情報
	CText* m_pBestText;					// 最高テキスト
	CNumber* m_apBestNum[MAX_DIGIT];	// 最高数字情報
	CText* m_apUI[3];					// リザルト用UI
	CText* m_pFailed;					// 失敗時用テキスト
};

#endif	// _RECORD_DEST_H_