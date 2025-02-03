////============================================================================
//// 
//// スコア、ヘッダファイル [score.h]
//// Author : 福田歩希
//// 
////============================================================================
//
//#ifndef _SCORE_H_
//#define _SCORE_H_	// 二重インクルード防止
//
////****************************************************
//// インクルードファイル
////****************************************************
//#include "object.h"
//#include "number.h"
//
////****************************************************
//// スコアクラス
////****************************************************
//class CScore : public CObject
//{
//public:
//
//	CScore();			// コンストラクタ
//	~CScore() override;	// デストラクタ
//
//	HRESULT Init() override;	// 初期設定
//	void Uninit() override;		// 終了処理
//	void Update() override;		// 更新処理
//	void Draw() override;		// 描画処理
//
//	int GetScore();				// 現在のスコア取得
//	void SetScore(int nScore);	// 現在のスコア設定
//
//	static CScore* Create(D3DXVECTOR3 pos, float fSpan);	// 生成
//
//private:
//
//	void Adjust();		// 変動制限
//	void Animation();	// アニメーション
//
//	static const int MAX_DIGIT = 6;			// 桁数
//	static const int MAX_SCORE = 999999;	// 上限値
//
//	static CNumber* m_apNumber[MAX_DIGIT];	// 数字管理
//
//	int m_nScore;		// 現在のスコア
//	int m_nScore_old;	// 過去のスコア
//	D3DXVECTOR3 m_pos;	// 数列の先頭位置
//	float m_fSpan;		// 数列の配置間隔
//};
//
//#endif // _SCORE_H_