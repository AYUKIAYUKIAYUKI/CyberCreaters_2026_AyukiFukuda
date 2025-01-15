//************************************************
//
//敵(移動)処理、ヘッダファイル[enemy_slide.h]
//Author：福田歩希
//
//************************************************
#ifndef _ENEMY_SLIDE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _ENEMY_SLIDE_H_	//(二重インクルード防止、マクロ定義する)

#include <stdio.h>
#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_ENEMY_SLIDE	"data\\TEX\\02_game\\enemy_slide.png"

/*ファイルパス系*/
#define	FILE_SET_ENEMY_SLIDE	"data\\csv\\EnemyInfo_Slide.csv"

#define AMOUNT_POLYGON_ENEMY_SLIDE	(64)	//敵のポリゴン数

#define AMOUNT_DATA_ENEMY_SLIDE	(15)	//敵一体当たりのデータ量

#define AMOUNT_CNT_STATE_ENEMY_SLIDE	(20)	//敵状態変化継続時間

//敵の状態分け列挙型
typedef enum
{
	ENEMYSTATE_SLIDE_NORMAL = 0,	//通常状態
	ENEMYSTATE_SLIDE_DAMAGE,		//ダメージ状態
	ENEMYSTATE_SLIDE_MAX,			//状態の総数
}ENEMYSTATE_SLIDE;

//敵構造体
typedef struct
{
	D3DXVECTOR3 pos;	//敵の位置情報を格納
	float fHalfSpanX;	//敵の半幅X
	float fHalfSpanY;	//敵の半幅Y
	D3DXVECTOR3 move;	//敵の移動情報を格納
	int nRute;			//どのルートを進むのか
	float fHoldmoveX;	//移動量を保持
	float fHoldmoveY;	//移動量を保持
	float fTurn1;		//移動をやめるタイミング1
	float fTurn2;		//移動をやめるタイミング2
	float fDecreaseSPD;	//移動量の減衰速度
	bool bTurning;		//方向転換
	D3DXVECTOR3 rot;	//敵の向き情報を格納
	int nColA;			//透明度調整
	ENEMYSTATE_SLIDE state;	//状態遷移
	int nCntState;		//状態変化時間管理
	int nLife;			//敵のHP
	bool bUse;			//仕様判定
	int nCntSpawn;		//いつ出現するか
	bool bUseEffect;	//エフェクトの使用判定
	bool bFinishEffect;	//エフェクト終了判定
	float fLength;		//敵の対角線を格納
	float fAngle;		//敵の対角線の角度を格納
}ENEMY_SLIDE;

//プロトタイプ宣言
void Init_Enemy_Slide(void);
void Uninit_Enemy_Slide(void);
void Update_Enemy_Slide(void);
void Draw_Enemy_Slide(void);
void Setinfo_Enemy_Slide(void);
void Hit_Slide_Enemy(int nCntEnemy, int nDamage);
ENEMY_SLIDE* Getinfo_Enemy_Slide(void);
void Disapper_Enemy_Slide(int nCntEnemy);

#endif