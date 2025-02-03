//************************************************
//
// ボスの弾、ヘッダファイル[boss_bullet.h]
// Author：葛西敬介
//
//************************************************
#ifndef _BOSS_BULLET_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BOSS_BULLET_H_	// (二重インクルード防止、マクロ定義する)

//include
#include "main.h"

//マクロ定義
#define MAX_BOSSBULLET (32)		// ボスの弾の最大数
#define MAX_BULLETSIZE	(20)		// 弾の大きさ
#define SHADOWSIZE	(40)			// 弾につく影の大きさ
#define MAX_VARTEX	(4)				// 頂点数

//ボスの弾の構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rot;		// 向き
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	float fWidth;			// 弾の幅
	float fHeight;			// 弾の高さ
	float fLife;			// 弾の寿命
	float rad;				// 球判定用のサイズ
	bool bUse;				// 使用しているかどうか
	int id_sph;				// 当たり判定可視化番号
	int id_shadow;			// 影の識別番号
	int nBulletIndex;		// 弾の番号
}BOSSBULLET;

// プロトタイプ宣言
void InitBossBullet(void);																			// 初期化処理
void UninitBossBullet(void);																		// 終了処理
void UpdateBossBullet(void);																		// 更新処理
void DrawBossBullet(void);																			// 描画処理
void MoveBossBullet(int id);																		// 弾の移動
void CheckUseBossBullet(int id);																	// 弾を使用しているかどうか
void SetBossBullet(D3DXVECTOR3 pos,D3DXVECTOR3 move,float fLife);									// 弾の設定処理
BOSSBULLET* GetBullet(void);																		// 弾の情報の取得
void CollisionBossBullet(int id);																	// ボスの弾と建物の当たり判定
void BossBulletPlayerCollision(int id);																// ボスの弾とプレイヤーの当たり判定
#endif