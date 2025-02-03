//************************************************
//
// エネミー処理、ヘッダファイル[enemy.h]
// Author：福田歩希
//
//************************************************
#ifndef _ENEMY_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _ENEMY_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル / */
#include "main.h"

/*/ マクロ定義 /*/
#define AMOUNT_ENEMY 256			// エネミーの最大数
#define AMOUNT_ENEMY_PARTS	42		// エネミー最大モデル種数
#define AMOUNT_ENEMY_MOTION	12		// モーション最大数
#define SPD_STOPMOVE_ENEMY	0.9f	// ブレーキ力

// エネミーの種類分け
typedef enum
{
	Dragonfly = 0,	// 蜻蛉
	Ant,			// 蟻
	Scorpion,		// 蠍
	Max_enemystyle,
}EnemyStyle;

// エネミー状態分け
typedef enum
{
	stateNormal_e = 0,	// 通常
	stateMove_e,		// 移動
	stateAtk_e,			// 攻撃
	stateCharge_e,		// 溜め
	stateRotate_e,		// 回転
	stateDamage_e,		// 負傷
	stateDead_e,		// 死亡
	stateResurrect_e,	// 復活
	//stateFind_e,		// 索敵
	Max_enemystate,
}EnemyState;

// エネミーパラメータ情報
typedef struct
{
	int phase;			// 出現フェーズ
	int appear;			// 出現タイミング
	int style;			// スタイル
	int state;			// 状態
	int dur;			// 状態継続
	int target;			// 対象
	int HP;				// 体力
	float SPD;			// 速度
	float rad;			// 球判定サイズ
	D3DXVECTOR3 atkpos;	// 攻撃判定の生成位置
	int motion_now;		// 再生モーション
	int motion_old;		// 過去モーション
}EnemyParam;

// エネミー用モデル情報
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
}EnemyModel;

// モーション時のパーツ目標動作用
typedef struct
{
	D3DXVECTOR3 pos;	// 目標位置格納
	D3DXVECTOR3 rot;	// 目標向き格納
}EnemyMotionDest;

// モーション時のキー用
typedef struct
{
	int amount_frame;							// キー単位の総フレーム数
	EnemyMotionDest dest[AMOUNT_ENEMY_PARTS];	// パーツの動作情報格納
}EnemyMotionKey;

// エネミーモーション用
typedef struct
{
	int loop;				// ループフラグ
	int amount_key;			// モーション単位の総キー数
	int id_key;				// 再生中のキー番号を格納
	int id_frame;			// 再生中のフレーム番号を格納
	EnemyMotionKey key[16];	// キー情報を格納
}EnemyMotion;

// エネミー情報
typedef struct
{
	bool use;								// 使用判定
	EnemyParam param;						// パラメータ
	D3DXVECTOR3 pos;						// ワールド位置
	D3DXVECTOR3 pos_old;					// 過去の位置
	D3DXVECTOR3 move;						// 移動量
	D3DXVECTOR3 rot;						// 現在の向き
	D3DXVECTOR3 rot_goal;					// 目標の向き
	D3DXVECTOR3 size;						// 大きさ
	D3DXCOLOR col;							// 色変更用
	D3DXMATRIX mtxWorld;					// ワールドマトリックス
	EnemyModel parts[AMOUNT_ENEMY_PARTS];	// エネミーのパーツ数
	EnemyMotion motion[AMOUNT_ENEMY_MOTION];// モーション情報
	int id_shadow;							// 影識別番号格納
	int id_sph;								// 判定識別番号格納
}Enemy;

//プロトタイプ宣言
void InitEnemy(void);					// 初期
void ImportModelEnemy(void);			// モデル取得
void ImportOffsetEnemy(FILE* pFile,
	int AmountModel);					// モデルオフセット取得
void ImportTexEnemy(int AmountModel);	// モデルテクスチャ取得
void VerifyStyleEnemy(int id);			// スタイル番号を照合
void ImportMotionEnemy(void);			// モーション取得
void ImportParamEnemy(void);			// パラメータ取得
void UninitEnemy(void);					// 破棄

void UpdateEnemy(void);					// 更新
int CntAppearedEnemy(void);				// 出現数をカウント
void AppearEnemy(int id);				// 出現
void RotateEnemy(int id);				// 回転
void MoveEnemy(int id);					// 移動
int SetTargetEnemy(int id);				// 対象を決める
void AtkEnemy(int id);					// 攻撃
void HitEnemy(int id);					// 被弾時
void DamageEnemy(int id);				// 負傷
void DeadEnemy(int id);					// 死亡
void ResurrectEnemy(int id);			// 復活
void MotionEnemy(int id);				// モーション管理
void ChangeMotionEnemy(int id,
	int* pNow, int* pOld);				// モーション変更検知
void MoveMotionEnemy(int id,
	EnemyMotion* pMotion);				// モーション動作用
void CntMotionEnemy(int id,
	EnemyMotion* pMotion);				// モーションカウント用
void DeleteEnemy(int id);				// 消去
void AddScoreEnemy(int id);				// エネミーによるスコア加算
void CalcMtxEnemy(void);				// 行列計算
void PhaseManagerEnemy(void);			// フェーズ管理

void DrawEnemy(void);			// 描画
Enemy* GetInfoEnemy(void);		// エネミー情報を取得
void PrintDebugEnemy(void);		// デバッグ表示

int* GetInfoPhase(void);		// フェーズ情報を取得
int GetInfoMaxEnemy(void);		// 敵の総数情報を取得
int GetInfoPhaseTimer(void);	// フェーズタイマー情報を取得

#endif