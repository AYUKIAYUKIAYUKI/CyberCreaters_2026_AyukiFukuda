//============================================================================
// 
// とげ移動ブロック、ヘッダファイル [block_spikes_move.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _BLOCK_SPIKES_MOVE_H_
#define _BLOCK_SPIKES_MOVE_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "object_X.h"

//****************************************************
// とげ移動ブロッククラス
//****************************************************
class CBlockSpikesMove : public CObject_X
{
public:

	CBlockSpikesMove();					// デフォルトコンストラクタ
	CBlockSpikesMove(LAYER priority);	// プライオリティ指定コンストラクタ
	~CBlockSpikesMove() override;		// デストラクタ

	HRESULT Init() override;	// 初期設定
	void Uninit() override;		// 終了処理
	void Update() override;		// 更新処理
	void Draw() override;		// 描画処理

	D3DXVECTOR3 GetPosHold();			// ホールド座標を取得
	void SetPosHold(D3DXVECTOR3 pos);	// ホールド座標を設定

	float GetAngleInit();					// 初期角度を取得
	void SetAngleInit(float fAngleInit);	// 初期角度を設定

	float GetAngle();				// 角度を取得
	void SetAngle(float fAngle);	// 角度を設定

	float GetAdder();				// 増加量を取得
	void SetAdder(float fAdder);	// 増加量を設定

	float GetCoeff();				// 反映係数を取得
	void SetCoeff(float fCoeff);	// 反映係数を設定

	static CBlockSpikesMove* Create(D3DXVECTOR3 pos, float fAngle, float fAdder, float fCoeff);		// 生成
	static void ResetAngleAll();																	// 角度を一斉リセット

private:

	void Translate();	// 移動

	D3DXVECTOR3 m_posHold;	// ホールド座標
	float m_fAngle;			// 角度
	float m_fAngleInit;		// 初期角度
	float m_fAdder;			// 増加量
	float m_fCoeff;			// 反映係数
};

#endif // _BLOCK_SPIKES_MOVE_H_