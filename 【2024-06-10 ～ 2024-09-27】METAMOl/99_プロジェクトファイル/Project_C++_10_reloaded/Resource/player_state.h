//============================================================================
// 
// プレイヤー状態管理、ヘッダファイル [player_state.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "player.h"

//****************************************************
// 前方宣言
//****************************************************
class CArrow;
class CRing;

//****************************************************
// プレイヤー状態クラス
//****************************************************
class CPlayerState
{
public:

	//****************************************************
	// 状態を識別
	//****************************************************
	enum class STATE
	{
		NONE = 0,	// 無し
		DEFAULT,	// 通常状態
		BEGINNING,	// 変身開始
		FLYING,		// 飛行状態
		CHARGING,	// 溜め状態
		RUSHING,	// 突撃状態
		STOPPING,	// 変身停止
		MISS,		// 失敗状態
		GOAL,		// ゴール後
		MAX,
	};

	CPlayerState();				// コンストラクタ
	virtual ~CPlayerState();	// デストラクタ

	virtual void Enter() = 0;				// 変更開始
	void RegisterPlayer(CPlayer* pPlayer);	// プレイヤーを登録
	virtual void Update() = 0;				// 更新
	virtual void Exit() = 0;				// 変更終了

protected:

	CPlayer* m_pPlayer;	// プレイヤーのポインタ
};

//****************************************************
// プレイヤー通常状態クラス
//****************************************************
class CPlayerStateDefault : public CPlayerState
{
public:

	CPlayerStateDefault();				// コンストラクタ
	~CPlayerStateDefault() override;	// デストラクタ

	void Enter() override;	// 変更開始
	void Update() override;	// 更新
	void Exit() override;	// 変更終了

private:

	static const float MAX_WALK_VELOCITY;	// 歩行時の最大加速度
	static const float BRAKING_WALK_SPEED;	// 歩行時の制動力

	D3DXVECTOR3 m_OldRotTarget;	// 過去の目標向き

	bool Control();		// 操作
	void Rotation();	// 回転
	void Braking();		// 制動調整
	void Recoil();		// 反動
};

//****************************************************
// プレイヤー変身開始クラス
//****************************************************
class CPlayerStateBeginning : public CPlayerState
{
public:

	CPlayerStateBeginning();			// コンストラクタ
	~CPlayerStateBeginning() override;	// デストラクタ

	void Enter() override;	// 変更開始
	void Update() override;	// 更新
	void Exit() override;	// 変更終了

private:

	static const int BEGIN_CNT_MAX;		// 変身必要時間
	static const float BEGIN_FLOATING;	// 変身時上昇量
	static const float BEGIN_SPINNING;	// 変身時回転量

	int m_nCntMetamorphose;	// 変身時間カウント
};

//****************************************************
// プレイヤー飛行状態クラス
//****************************************************
class CPlayerStateFlying : public CPlayerState
{
public:

	static const float FLY_SPEED;	// 飛行速度

	CPlayerStateFlying();			// コンストラクタ
	~CPlayerStateFlying() override;	// デストラクタ

	void Enter() override;	// 変更開始
	void Update() override;	// 更新
	void Exit() override;	// 変更終了

private:

	static const float MAX_FLY_VELOCITY;	// 飛行時の最大加速度

	D3DXVECTOR3 m_OldRotTarget;	// 過去の目標向き

	bool Control();		// 操縦
	void Rotation();	// 回転
	void Braking();		// 制動調整
};

//****************************************************
// プレイヤー溜め状態クラス
//****************************************************
class CPlayerStateCharging : public CPlayerState
{
public:

	CPlayerStateCharging();				// コンストラクタ
	~CPlayerStateCharging() override;	// デストラクタ

	void Enter() override;	// 変更開始
	void Update() override;	// 更新
	void Exit() override;	// 変更終了

private:

	static const int MAX_LIMITCHARGE;	// 最大チャージ猶予

	void Rotation();	// 回転
	void UpdateArrow();	// 矢印の更新を行う

	D3DXVECTOR3 m_OldRotTarget;	// 過去の目標向き
	D3DXVECTOR3 m_rotHold;		// 向きを保持
	int m_nLimitCharge;			// チャージ猶予
	CArrow* m_pArrow;			// 矢印情報
	float m_fArrowSize;			// 矢印サイズ
	CRing* m_pRing;				// リング情報
	float m_fRingSize;			// リングサイズ
};

//****************************************************
// プレイヤー突撃状態クラス
//****************************************************
class CPlayerStateRushing : public CPlayerState
{
public:

	CPlayerStateRushing();				// コンストラクタ
	~CPlayerStateRushing() override;	// デストラクタ

	void Enter() override;	// 変更開始
	void Update() override;	// 更新
	void Exit() override;	// 変更終了

private:

	void L_Update();	// レベル更新
	void C_Update();	// チャレンジ更新
	void Rotation();	// 回転

	D3DXVECTOR3 m_OldRotTarget;	// 過去の目標向き
	D3DXVECTOR3 m_WaveVelocity;	// ウェーブ加速度
	float m_fCoeff;				// ウェーブ変化量
};

//****************************************************
// プレイヤー変身停止クラス
//****************************************************
class CPlayerStateStopping : public CPlayerState
{
public:

	CPlayerStateStopping();				// コンストラクタ
	~CPlayerStateStopping() override;	// デストラクタ

	void Enter() override;	// 変更開始
	void Update() override;	// 更新
	void Exit() override;	// 変更終了

private:

	static const int STOP_CNT_MAX;		// 変身停止必要時間
	static const float RECOIL_SPEED;	// 反動移動速度

	void Rotation();	// 回転
	void Recoil();		// 反動

	D3DXVECTOR3 m_OldRotTarget;	// 過去の目標向き
	int m_nCntStopMetamorphose;	// 変身時間カウント
};

//****************************************************
// プレイヤー失敗状態クラス
//****************************************************
class CPlayerStateMistook : public CPlayerState
{
public:

	CPlayerStateMistook();				// コンストラクタ
	~CPlayerStateMistook() override;	// デストラクタ

	void Enter() override;	// 初回変更
	void Update() override;	// 更新
	void Exit() override;	// 変更終了

private:

	static const float MAX_WARP_SPEED;	// 強制移動速度の上限

	void FindStartObject();	// スタートオブジェクトの位置を検索
	void Respawn();			// リスポーン

	D3DXVECTOR3 m_PosStartObject;	// スタートオブジェクトの位置
};

//****************************************************
// プレイヤーゴール後クラス
//****************************************************
class CPlayerStateGoal : public CPlayerState
{
public:

	CPlayerStateGoal();				// コンストラクタ
	~CPlayerStateGoal() override;	// デストラクタ

	void Enter() override;	// 初回変更
	void Update() override;	// 更新
	void Exit() override;	// 変更終了
};

//****************************************************
// プレイヤー状態マネージャークラス
//****************************************************
class CPlayerStateManager
{
public:

	CPlayerStateManager();	// コンストラクタ
	~CPlayerStateManager();	// デストラクタ

	void CheckStateChange();				// 状態の変更を確認
	void Init(CPlayer* pPlayer);			// 初期設定
	void RegisterPlayer(CPlayer* pPlayer);	// プレイヤーを登録
	void Uninit();							// 終了処理

	CPlayer* GetPlayer();								// プレイヤーを取得
	CPlayerState* GetState();							// 状態を取得
	CPlayerState::STATE GetPendingState();				// 変更予定の状態を取得
	void SetPendingState(CPlayerState::STATE state);	// 変更予定の状態を設定

private:

	void Create(CPlayerState::STATE state);	// 新たな状態を生成

	CPlayer* m_pPlayer;					// プレイヤーのポインタ
	CPlayerState* m_pState;				// 状態のポインタ
	CPlayerState::STATE m_PendingState;	// 変更予定の状態
};

#endif // _PLAYER_STATE_H_