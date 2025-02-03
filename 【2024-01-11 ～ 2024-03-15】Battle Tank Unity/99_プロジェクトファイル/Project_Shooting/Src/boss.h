//************************************************
//
// ボス、ヘッダファイル[boss.h]
// Author：葛西敬介
//
//************************************************

#ifndef _BOSS_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BOSS_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル / */
#include "main.h"

/*/ マクロ定義 /*/
#define MAX_BOSS					(2)		// ボスの数
#define AMOUNT_BOSS_PARTS			(28)	// ボス最大モデル種類数
#define SPD_STOPMOVE_BOSS			(0.9f)	// ブレーキ力
#define NUM_MOTION					(12)	// モーションの種類数
#define STANTIME					(20)	// ボスが被弾したときのスタン時間
#define ADJUSTPOSY_MIDBOSS			(100.0f)// 弾の発射位置(Y)の調整用
#define ADJUSTPOSY_BIGBOSS			(30.0f)	// 弾の発射位置(Y)の調整用
#define NUM_ACT						(6)		// 中ボスの行動パターン
#define MAX_CHANGEFRAME				(500)	// 中ボスの行動を変えるフレーム数
#define BULLETMOVEY					(0.8f)	// 中ボスの弾のY座標方向への移動量
#define MIDBOSSMOVE					(1.5f)	// 中ボスの移動量
#define MIDBOSS_LATE				(60)	// 中ボスが死んでから爆発するまでの遅延時間
#define BIGBOSS_LATE				(40)	// 中ボスが死んでから爆発するまでの遅延時間

#define DATA_RANGE					(3800)	// randで生成したい数値の範囲
#define DATA_ADJUST					(1900)	// 負の整数も生成するための調整量

//******************************************************************
// ボスの行動パターンフレーム数のマクロ定義
//******************************************************************
#define PATTERN_ZERO	(500)	// 1パターン目
#define PATTERN_ONE		(1000)	// 2パターン目
#define PATTERN_TWO		(1500)	// 3パターン目
#define PATTERN_THREE	(2000)	// 4パターン目
#define PATTERN_FOUR	(2500)	// 5パターン目
#define PATTERN_FIVE	(3000)	// 6パターン目
#define PATTERN_SIX		(3500)	// 7パターン目
#define PATTERN_SEVEN	(4000)	// 8パターン目
#define PATTERN_EIGHT	(4500)	// 9パターン目
#define PATTERN_NINE	(5000)	// 10パターン目

// ボスの種類分け
typedef enum
{
	BOSSTYPE_MID = 0,	//中ボス
	BOSSTYPE_BIG,		//大ボス
	BOSSTYPE_MAX
}BOSSTYPE;

// ボス状態分け
typedef enum
{
	stateNormal_b = 0,	// 通常
	stateMove_b,		// 移動
	stateAtk_b,			// 攻撃
	stateDamage_b,		// 被弾
	stateDead_b,		// 死亡
	steteResurrect_b,	// 復活
	Max_bossstate,
}BOSSState;

//モーション種類分け
typedef enum
{
	motion_neutralMid = 0,		// ニュートラルモーション(中ボス)
	motion_moveMid,				// 移動モーション(中ボス)
	motion_actionMid,			// 攻撃モーション(中ボス)
	motion_jumpMid,				// ジャンプモーション(中ボス)
	motion_landingMid,			// 着地モーション(中ボス)
	motion_damageMid,			// 被弾モーション(中ボス)
	motion_deadMid,				// 死亡モーション(中ボス)
	motion_neutralBig,			// ニュートラルモーション(大ボス)
	motion_moveBig,				// 移動モーション(大ボス)
	motion_actionBig,			// 攻撃モーション(大ボス)
	motion_damageBig,			// 被弾モーション(大ボス)
	motion_deadBig,				// 死亡モーション(大ボス)
	motion_max,
}BossMotionType;

// ボスの弾の挙動分け
typedef enum
{
	BULLETPATTERN_ZERO = 0,	// 0種類目(randでの数値に対するマクロ定義で使っているのでBULLETPATTERN_ZEROは不使用)
	BULLETPATTERN_ONE,		// 1種類目
	BULLETPATTERN_TWO,		// 2種類目
	BULLETPATTERN_THREE,	// 3種類目
	BULLETPATTERN_FOUR,		// 4種類目
	BULLETPATTERN_FIVE,		// 5種類目
	BULLETPATTERN_SIX,		// 6種類目
	BULLETPATTERN_SEVEN,	// 7種類目
	BULLETPATTERN_EIGHT,	// 8種類目
	BULLETPATTERN_NINE,		// 9種類目
	BULLETPATTERN_TEN,		// 10種類目
	BULLETPATTERN_MAX
}BULLETPATTERN;

// ボスパラメータ情報
typedef struct
{
	int appear;			// 出現タイミング
	int style;			// スタイル
	int state;			// 状態
	int dur;			// 状態継続
	float HP;			// 体力
	D3DXVECTOR3 SPD;	// 速度
	//float Radius;		// 球の判定に必要な半径
	int motion_now;		// 再生モーション
	int motion_old;		// 過去モーション
	bool bMove;			// 移動しているかどうか

}BOSSParam;

// ボス用モデル情報
typedef struct
{
	int style;								// スタイル
	LPD3DXMESH pMesh;						// メッシュのポインタ
	LPD3DXBUFFER pBuffMat;					// マテリアルのポインタ
	DWORD NumMat;							// マテリアルの数
	LPDIRECT3DTEXTURE9 pTex[AMOUNT_MAT];	// テクスチャのポインタ
	D3DXVECTOR3 pos_offset;					// 位置オフセット
	D3DXVECTOR3 pos_moved;					// モーション時など変動位置
	D3DXVECTOR3 rot_offset;					// 向きオフセット
	D3DXVECTOR3 rot_moved;					// モーション時など変動向き
	D3DXMATRIX mtxWorld;					// ワールドマトリックス
	int IdxParent;							// 親パーツのインデックス
}BOSSModel;

// モーション時のパーツ目標動作用
typedef struct
{
	D3DXVECTOR3 pos;	// 目標位置格納
	D3DXVECTOR3 rot;	// 目標向き格納
}BossMotionDest;

// モーション時のキー用
typedef struct
{
	int amount_frame;							// キー単位の総フレーム数
	BossMotionDest dest[AMOUNT_BOSS_PARTS];		// パーツの動作情報格納
}BossMotionKey;

// ボスモーション用
typedef struct
{
	int loop;				// ループフラグ
	int amount_key;			// モーション単位の総キー数
	int id_key;				// 再生中のキー番号を格納
	int id_frame;			// 再生中のフレーム番号を格納
	BossMotionKey key[16];	// キー情報を格納
}BossMotion;

// ボス情報
typedef struct
{
	bool use;								// 使用判定 
	D3DXVECTOR3 pos;						// ワールド位置
	D3DXVECTOR3 pos_old;					// 過去の位置
	D3DXVECTOR3 move;						// 移動量
	D3DXVECTOR3 rot;						// 現在の向き
	D3DXVECTOR3 rot_goal;					// 目標の向き
	D3DXCOLOR col;							// 色変更用
	D3DXMATRIX mtxWorld;					// ワールドマトリックス
	BOSSModel parts[AMOUNT_BOSS_PARTS];		// エネミーのパーツ数
	float rad[AMOUNT_BOSS_PARTS];			// 各パーツの判定サイズ
	D3DXVECTOR3 pos_sph[AMOUNT_BOSS_PARTS];	// 各パーツの判定位置
	int id_shadow;							// 影識別番号格納
	int id_sph[AMOUNT_BOSS_PARTS];			// 判定識別番号格納
	BOSSTYPE type;							// ボスの種類
	BOSSState State;						// ボスの状態
	BOSSParam Param;						// ボスのパラメーター
	BossMotion motion[NUM_MOTION];			// モーション情報
}BOSS;

//プロトタイプ宣言
void InitBoss(void);									// 初期
void ImportModelBoss(void);								// モデル取得
void ImportOffsetBoss(FILE* pFile, int AmountModel);	// モデルオフセット取得
void ImportTexBoss(int AmountModel);					// モデルテクスチャを読込み
void ImportMotionBoss(void);							// モーション取得
//void GenerateBOSS(void);								// 出現設定
void AppearBoss(int id);								// 出現
void ImportParamBoss(void);								// パラメータ取得
void VerifyStyleBoss(int id);							// スタイル番号を照合
void UninitBoss(void);									// 破棄
void UpdateBoss(void);									// 更新
void RotateBoss(int id);								// 回転
void MoveBoss(void);									// 移動
void CalcMtxBoss(void);									// 行列計算
void DrawBoss(void);									// 描画
BOSS* GetInfoBoss(void);								// エネミー情報を取得
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
	int nStyle, float fLife);							// 敵のパラメーターを設定する
void MidBossBehavior(int id);							// 中ボスの挙動
void BigBossBehavior(int id);							// 大ボスの挙動
void HitBoss(int id);									// ボスと弾の当たり判定
void NeutralBoss(int id);								// ニュートラル状態
void DamageBoss(int id);								// 負傷
void DeadBoss(int id);									// 死亡
void ResurrectBoss(int id);								// 復活
void MotionBoss(int id);								// モーション管理
void ChangeMotionBoss(int id, int* pNow, int* pOld);		// モーション変更検知
void MoveMotionBoss(int id, BossMotion* pMotion);		// モーション動作用
void CntMotionBoss(int id, BossMotion* pMotion);			// モーションカウント用
void AdjustBullet(int id);								// 弾の挙動を決める
bool CheckBossUse(void);								// ボスが生きているかどうか
void CollisionBoss(int id);								// ボスと建物の当たり判定
void CollisionPlayer(int id);							// ボスとプレイヤーの当たり判定
void DeleteOldBoss(int id);								// フェーズが終了したボスの消去

//////////////////////////////////////////////////////////////////

bool GetInfoHP_MidBoss(void);	// 体力による生存判定 - 中ボス
bool GetInfoHP_BigBoss(void);	// 体力による生存判定 - 大ボス

#endif
