//************************************************
//
//弾、ヘッダファイル[bullet.h]
//Author：福田歩希
//
//************************************************
#ifndef _BULLET_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BULLET_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義
#define AMOUNT_BULLET	(256)	//弾数
#define SPAN_BULLET	(2.0f)	//弾の大きさ
#define SPD_BULLET	(7.0f)	//弾の速さ

//弾が何に当たったのか種類分け
enum CollisionMode
{
	CollisionModeEnemy = 0,
	CollisionModeWall,
	CollisionModeMax
};

//弾構造体
struct Bullet
{
	bool bUse;			//使用判定
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き
	float fPA;			//極角
	float fRadius;		//半径
	int nRemain;		//残存
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nIdxShadow;
};

//プロトタイプ宣言
void InitBullet(void);		//初期
void UninitBullet(void);	//破棄
void SetInfoBullet(void);	//設定
void UpdateBullet(void);	//更新
void DisappearBullet(int nCnt);	//消滅
void DrawBullet(void);		//描画
void CollisionBullet(int nMode, int nCnt);	//当たり判定
Bullet* GetInfoBullet(void);	//弾情報を取得

#endif