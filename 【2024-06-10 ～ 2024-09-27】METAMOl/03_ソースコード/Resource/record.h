//============================================================================
// 
// レコード、ヘッダファイル [record.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _RECORD_H_
#define _RECORD_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_UI.h"
#include "number.h"
#include "text.h"
#include "game_manager.h"

//****************************************************
// レコードクラス
//****************************************************
class CRecord : public CObject_UI
{
public:

	CRecord();				// デフォルトコンストラクタ
	~CRecord() override;	// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理
	void SetDisappearExtra();	// 特殊消去予約

	static CRecord* Create();	// 生成

private:

	static const int MAX_DIGIT = 3;	// 最大桁数
	static const int MAX_BACK = 2;	// 戻るマーク用最大数

	void Appear() override;			// 出現
	void Disappear() override;		// 消滅
	int ImportRecord(int nSelect);	// ベストタイムの読み込み
	void LayoutBackAtSquare();		// マス目に戻るマークを並べる

	CText* m_pText;					// テキスト情報
	CNumber* m_apNumber[MAX_DIGIT];	// 数字情報
	CText* m_apBack[MAX_BACK];		// 戻るマーク用テキスト情報
};

#endif	// _RECORD_H_