//************************************************
//
//プレイヤー、ヘッダファイル[player.h]
//Author：福田歩希
//
//************************************************
#ifndef _PLAYER_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _PLAYER_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義
#define AMOUNT_PLAYER_PARTS	(15)	//プレイヤー最大モデル数
#define AMOUNT_PLAYER_KEY	(32)	//プレイヤー最大キー数
#define AMOUNT_CAPACITY (5000)	//キャパシティ
#define AMOUNT_USING_CAPACITY (500)	//キャパ消費
#define AMOUNT_ENEGY (100)	//反撃ゲージマックス

//プレイヤーの状態
typedef enum
{
	PlayerStateNormal = 0,
	PlayerStateMove,
	PlayerStateAtk,
	PlayerStateDamage,
	PlayerStateMax
}PlayerState;

//プレイヤーのモーション一覧
typedef enum
{
	PlayerMotionStateNormal = 0,
	PlayerMotionStateMove,
	PlayerMotionStateAtk,
	PlayerMotionStateJump,
	PlayerMotionStateLand,
	PlayerMotionStateMax
}PlayerMotionState;

//プレイヤーモデルパーツ用
typedef struct
{
	LPD3DXMESH pMeshPlayer;	//メッシュのポインタ
	LPD3DXBUFFER pBuffMatPlayer;	//マテリアルのポインタ
	DWORD dwNumMatPlayer;	//マテリアルの数
	LPDIRECT3DTEXTURE9 pTexture;	//テクスチャのポインタ
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posM;	//モーション時の位置
	D3DXVECTOR3 rot;	//向き
	D3DXVECTOR3 rotM;	//モーション時の向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nIdxParent;	//親パーツのインデックス
}PlayerModel;

//プレイヤーパーツ管理
typedef struct
{
	D3DXVECTOR3 posGoal;	/* このパーツの目的位置 */
	D3DXVECTOR3 rotGoal;	/* このパーツの目的向き */
}PlayerPartsSet;

//プレイヤーキー管理
typedef struct
{
	int nFrame;	/* このキーのフレーム数 */
	PlayerPartsSet parts[AMOUNT_PLAYER_PARTS];	/* パーツごとの可動目的地 */
}PlayerKeySet;

//プレイヤーモーション管理
typedef struct 
{
	int nLoop;	/* このモーションをループするかどうか */
	int nNumKey;	/* このモーションのキー数 */
	int nIdxKey;	/* 再生中のキー番号 */
	int nFrameCnt;	/* 現在のフレーム経過 */
	PlayerKeySet key[AMOUNT_PLAYER_KEY];	/* このモーションのキーの最大数 */
}PlayerMotionSet;

//プレイヤー構造体
typedef struct
{
	int nState;	//状態
	D3DXCOLOR col;	//色変更用
	bool bATK;	//攻撃判定
	bool bMUKIMUKI;	//ムキムキマックスモード
	int nCapacity;	//スプレーキャパ
	int nEnegy;	//反撃ゲージ
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posOld;	//過去の位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//現在の向き
	D3DXVECTOR3 rotGoal;	//目標の向き
	int nCntState;		//状態継続時間
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	PlayerModel aParts[AMOUNT_PLAYER_PARTS];	//プレイヤーのパーツ数
	PlayerMotionSet motion[PlayerStateMax];	//モーション管理用
	int nNowMotion;	//再生中のモーションの種類
	int nOldMotion;	//再生してたモーションの種類	
	COLLISION_AABB aabb;	//AABB
	int nIdxShadow;
}Player;

//プロトタイプ宣言
void InitPlayer(int mode);	//初期
void SetInfoParts(int mode);	//モデルパーツ設定
void SetInfoMotion(int mode);	//モーション設定
void UninitPlayer(void);	//破棄
void UpdatePlayer(int mode);	//更新
bool MovePlayer(void);	//移動
void MoveRotatePlayer(void);	//回転
bool JumpPlayer(void);	//ジャンプ
bool LandPlayer(void);	//着地
void TakesDamagePlayer(void);	//被弾
void UpdatePlayerAABB(D3DXVECTOR3 pos);	//AABB
void MotionPlayer(void);	//モーション管理
void MotionChangePlayer(void);	//モーション変更
void MotionMovePlayer(const PlayerMotionSet* Motion);	//モーション用移動
void MotionCountPlayer(PlayerMotionSet* Motion);	//モーション用カウント
void DrawPlayer(void);	//描画
Player* GetInfoPlayer(void);	//プレイヤー情報を取得

void MUKIMUKI_Colorful(void);	//ムキムキカラフルモード

#endif