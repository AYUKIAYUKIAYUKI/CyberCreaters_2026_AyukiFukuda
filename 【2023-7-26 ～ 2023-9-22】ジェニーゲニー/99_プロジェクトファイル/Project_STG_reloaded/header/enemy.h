//************************************************
//
//敵(もや)処理、ヘッダファイル[enemy.h]
//Author：福田歩希
//
//************************************************
#ifndef _ENEMY_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _ENEMY_H_	//(二重インクルード防止、マクロ定義する)

#include <stdio.h>
#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_CLOUD_ENEMY	"data\\TEX\\02_game\\enemy000.png"

/*ファイルパス系*/
#define	FILE_SET_ENEMY	"data\\csv\\EnemyInfo_Cloud.csv"

#define AMOUNT_POLYGON_ENEMY	(64)	//敵のポリゴン数

#define AMOUNT_DATA_ENEMY	(11)	//敵一体当たりのデータ量

#define AMOUNT_CNT_STATE_ENEMY	(20)	//敵状態変化継続時間

//敵の状態分け列挙型
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//通常状態
	ENEMYSTATE_DAMAGE,		//ダメージ状態
	ENEMYSTATE_MAX,			//状態の総数
}ENEMYSTATE;

//敵構造体
typedef struct
{
	D3DXVECTOR3 pos;	//敵の位置情報を格納
	float fHalfSpanX;	//敵の半幅X
	float fHalfSpanY;	//敵の半幅Y
	D3DXVECTOR3 move;	//敵の移動情報を格納
	D3DXVECTOR3 rot;	//敵の向き情報を格納
	int nColA;			//透明度調整
	ENEMYSTATE state;	//状態遷移
	int nCntState;		//状態変化時間管理
	int nLife;			//敵のHP
	bool bUse;			//仕様判定
	int nCntSpawn;		//いつ出現するか
	bool bUseEffect;	//エフェクトの使用判定
	bool bFinishEffect;	//エフェクト終了判定
	float fLength;		//敵の対角線を格納
	float fAngle;		//敵の対角線の角度を格納
}ENEMY;

//プロトタイプ宣言
void Init_Enemy(void);
void Uninit_Enemy(void);
void Update_Enemy(void);
void Draw_Enemy(void);
void Setinfo_Enemy(void);
void Hit_Cloud_Enemy(int nCntEnemy, int nDamage);
ENEMY* Getinfo_Enemy(void);
void Disapper_Enemy(int nCntEnemy);

#endif