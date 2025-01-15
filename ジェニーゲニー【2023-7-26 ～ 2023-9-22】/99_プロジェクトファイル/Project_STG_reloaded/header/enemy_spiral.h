//************************************************
//
//敵(貫通)処理、ヘッダファイル[enemy_spiral.h]
//Author：福田歩希
//
//************************************************
#ifndef _ENEMY_SPIRAL_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _ENEMY_SPIRAL_H_	//(二重インクルード防止、マクロ定義する)

#include <stdio.h>
#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_ENEMY_SPIRAL	"data\\TEX\\02_game\\enemy_spiral.png"

/*ファイルパス系*/
#define	FILE_SET_ENEMY_SPIRAL	"data\\csv\\EnemyInfo_Spiral.csv"

#define AMOUNT_POLYGON_ENEMY_SPIRAL	(64)	//敵のポリゴン数

#define AMOUNT_DATA_ENEMY_SPIRAL	(13)	//敵一体当たりのデータ量

#define AMOUNT_CNT_STATE_ENEMY_SPIRAL	(20)	//敵状態変化継続時間

//敵の状態分け列挙型
typedef enum
{
	ENEMYSTATE_SPIRAL_NORMAL = 0,	//通常状態
	ENEMYSTATE_SPIRAL_DAMAGE,		//ダメージ状態
	ENEMYSTATE_SPIRAL_MAX,			//状態の総数
}ENEMYSTATE_SPIRAL;

//敵構造体
typedef struct
{
	D3DXVECTOR3 pos;	//敵の位置情報を格納
	float fHalfSpanX;	//敵の半幅X
	float fHalfSpanY;	//敵の半幅Y
	D3DXVECTOR3 move;	//敵の移動情報を格納
	float fHoldmoveX;	//移動量を保持
	float fHoldmoveY;	//移動量を保持
	float fStop;		//移動をやめるタイミング1
	bool bReMove;
	float fDecreaseSPD;	//移動量の減衰速度
	D3DXVECTOR3 rot;	//敵の向き情報を格納
	int nColA;			//透明度調整
	ENEMYSTATE_SPIRAL state;	//状態遷移
	int nCntState;		//状態変化時間管理
	int nLife;			//敵のHP
	bool bUse;			//使用判定
	int nCntSpawn;		//いつ出現するか
	float fLength;		//敵の対角線を格納
	float fAngle;		//敵の対角線の角度を格納
}ENEMY_SPIRAL;

//プロトタイプ宣言
void Init_Enemy_Spiral(void);
void Uninit_Enemy_Spiral(void);
void Update_Enemy_Spiral(void);
void Draw_Enemy_Spiral(void);
void Setinfo_Enemy_Spiral(void);
void Hit_Spiral_Enemy(int nCntEnemy, int nDamage);
ENEMY_SPIRAL* Getinfo_Enemy_Spiral(void);
void Disapper_Enemy_Spiral(int nCntEnemy);

#endif