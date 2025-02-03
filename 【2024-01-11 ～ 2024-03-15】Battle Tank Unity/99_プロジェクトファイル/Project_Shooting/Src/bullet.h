//************************************************
//
// 弾、ヘッダファイル[bullet.h]
// Author：福田歩希
//
//************************************************
#ifndef _BULLET_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BULLET_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル /*/
#include "main.h"

/*/ マクロ定義 /*/
#define AMOUNT_BULLET 256	// 弾数
#define SPAN_BULLET 10.0f	// 弾の大きさ
#define SPD_BULLET 7.5f		// 弾の速さ

// 弾の種類分け
typedef enum
{
	bulletPlayer = 0,	// プレイヤー
	bulletEnemy,		// エネミー
	bulletBoss,			// ボス
	Max_bullettype
} BulletType;

// 弾用情報
typedef struct
{
	bool use;				// 使用フラグ
	int type;				// タイプ識別
	int style;				// スタイル識別
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rot;		// 向き
	float rad;				// 球判定サイズ
	int remain;				// 寿命
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	int id_shadow;			// 影識別番号格納
	int id_sph;				// 判定識別番号格納
	float RPG_Speed;		//ロケランの弾速
	float RPGBulletSpeed;	//弾の加速
	bool startRPGfall;		//落下を開始するまでのインターバル
	int RPGammofallcount;	//ロケランの落下するタイミング決める用
	bool ShotRPG;			//発射したかどうか
} Bullet;

//プロトタイプ宣言
void InitBullet(void);			// 初期
void UninitBullet(void);		// 破棄
void CreateBullet(int type,
	int id);					// 生成
void UpdateBullet(void);		// 更新
void MoveBullet(int id);		// 移動
void DeleteBullet(int id);		// 消去
void SetVtxBullet(void);		// 展開
void DrawBullet(void);			// 描画
void CollisionBullet(int id);	// 当たり判定
Bullet* GetInfoBullet(void);	// 弾情報を取得

#endif