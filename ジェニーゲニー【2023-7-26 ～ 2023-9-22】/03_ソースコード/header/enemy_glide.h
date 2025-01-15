//************************************************
//
//敵(飛翔)処理、ヘッダファイル[enemy_glide.h]
//Author：福田歩希
//
//************************************************
#ifndef _ENEMY_GLIDE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _ENEMY_GLIDE_H_	//(二重インクルード防止、マクロ定義する)

#include <stdio.h>
#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_ENEMY_GLIDE	"data\\TEX\\02_game\\enemy_glide.png"

/*ファイルパス系*/
#define	FILE_SET_ENEMY_GLIDE	"data\\csv\\EnemyInfo_Glide.csv"

#define AMOUNT_POLYGON_ENEMY_GLIDE	(64)	//敵のポリゴン数

#define AMOUNT_DATA_ENEMY_GLIDE	(15)	//敵一体当たりのデータ量

#define AMOUNT_CNT_STATE_ENEMY_GLIDE	(20)	//敵状態変化継続時間

//敵の状態分け列挙型
typedef enum
{
	ENEMYSTATE_GLIDE_NORMAL = 0,	//通常状態
	ENEMYSTATE_GLIDE_DAMAGE,		//ダメージ状態
	ENEMYSTATE_GLIDE_MAX,			//状態の総数
}ENEMYSTATE_GLIDE;

//敵構造体
typedef struct
{
	D3DXVECTOR3 pos;	//敵の位置情報を格納
	float fHalfSpanX;	//敵の半幅X
	float fHalfSpanY;	//敵の半幅Y
	D3DXVECTOR3 move;	//敵の移動情報を格納
	D3DXVECTOR3 rot;	//敵の向き情報を格納
	int nColA;			//透明度調整
	ENEMYSTATE_GLIDE state;	//状態遷移
	int nCntState;		//状態変化時間管理
	int nLife;			//敵のHP
	bool bUse;			//仕様判定
	int nCntSpawn;		//いつ出現するか
	int nCntChange;		//いつ進路変更するか
	bool bUseEffect;	//エフェクトの使用判定
	bool bFinishEffect;	//エフェクト終了判定
	float fDirection;	//方角
	float fTurningSPD;	//旋回速度
	float fSizeCircle;	//円周幅
	float fLength;		//敵の対角線を格納
	float fAngle;		//敵の対角線の角度を格納
}ENEMY_GLIDE;

//プロトタイプ宣言
void Init_Enemy_Glide(void);
void Uninit_Enemy_Glide(void);
void Update_Enemy_Glide(void);
void Draw_Enemy_Glide(void);
void Setinfo_Enemy_Glide(void);
void Hit_Glide_Enemy(int nCntEnemy, int nDamage);
ENEMY_GLIDE* Getinfo_Enemy_Glide(void);
void Disapper_Enemy_Glide(int nCntEnemy);

#endif