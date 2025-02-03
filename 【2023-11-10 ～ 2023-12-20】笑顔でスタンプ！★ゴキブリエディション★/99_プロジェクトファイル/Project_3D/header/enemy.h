//************************************************
//
//敵、ヘッダファイル[enemy.h]
//Author：福田歩希
//
//************************************************
#ifndef _ENEMY_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _ENEMY_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義
#define AMOUNT_ENEMY (64)
#define AMOUNT_ENEMY_PARTS	(16)	//エネミーモデル数
#define AMOUNT_ENEMY_MOTION	(3)	//エネミー最大モーション数
#define AMOUNT_ENEMY_KEY	(32)	//エネミー最大キー数

//敵のステータス一覧
typedef enum
{
	EnemyStateNormal = 0,
	EnemyStateDash,
	EnemyStateATK,
	EnemyStateEscape,
	EnemyStateDamage,
	EnemyStateDeath,
	EnemyStateMax
}EnemyState;

//敵のモーション一覧
typedef enum
{
	EnemyMotionStateNormal = 0,
	EnemyMotionStateDash,
	EnemyMotionStateATK,
	EnemyMotionStateMax
}EnemyMotionState;

//エネミーモデルパーツ用
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posM;	//モーション時の位置
	D3DXVECTOR3 rot;	//向き
	D3DXVECTOR3 rotM;	//モーション時の向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nIdxParent;	//親パーツのインデックス
}EnemyModel;

//エネミーパーツ管理
typedef struct
{
	D3DXVECTOR3 posGoal;	/* このパーツの目的位置 */
	D3DXVECTOR3 rotGoal;	/* このパーツの目的向き */
}EnemyPartsSet;

//エネミーキー管理
typedef struct
{
	int nFrame;	/* このキーのフレーム数 */
	EnemyPartsSet parts[AMOUNT_ENEMY_PARTS];	/* パーツごとの可動目的地 */
}EnemyKeySet;

//エネミーモーション管理
typedef struct
{
	int nLoop;	/* このモーションをループするかどうか */
	int nNumKey;	/* このモーションのキー数 */
	int nIdxKey;	/* 再生中のキー番号 */
	int nFrameCnt;	/* 現在のフレーム経過 */
	EnemyKeySet key[AMOUNT_ENEMY_KEY];	/* このモーションのキーの最大数 */
}EnemyMotionSet;

//敵構造体
struct Enemy
{
	bool bUse;	//使用判定
	int nState;	//状態
	bool bATK;	//攻撃判定
	D3DXCOLOR col;	//色
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き(仮想の進行方向などに)
	float fRadius;		//半径
	int nLife;			//体力
	int nCntState;		//状態継続時間
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	EnemyModel aParts[AMOUNT_ENEMY_PARTS];	//パーツ数
	EnemyMotionSet motion[EnemyStateMax];	//モーション管理用
	int nNowMotion;	//再生中のモーションの種類
	int nOldMotion;	//再生してたモーションの種類
	int nIdxShadow;
};

//プロトタイプ宣言
void InitEnemy(void);	//初期
void SetInfoPartsEnemy(void);	//モデルパーツ設定
void SetInfoMotionEnemy(void);	//モーション設定
void UninitEnemy(void);	//破棄
void SetInfoEnemy(void);	//設定
void UpdateEnemy(int mode);	//更新
void SpawnEnemy(void);	//出現
void StateEnemy(int nCnt, int mode);	//状態
void SetInfoATK(int nCnt);	//攻撃判定
void DisappearEnemy(int nCnt);	//消滅
void MotionEnemy(int nCnt);	//モーション管理
void MotionChangeEnemy(int nCnt);	//モーション変更
void MotionMoveEnemy(int nCnt, const EnemyMotionSet* Motion);	//モーション用移動
void MotionCountEnemy(int  nCnt, EnemyMotionSet* Motion);	//モーション用カウント
void DrawEnemy(void);	//描画
Enemy* GetInfoEnemy(void);	//敵情報を取得

#endif