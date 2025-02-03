//************************************************
//
//自機処理、ヘッダファイル[player.h]
//Author：福田歩希
//
//************************************************
#ifndef _PLEYER_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _PLEYER_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス*/
#define	TEXTURE_CHARACTER_PLAYER	"data\\TEX\\02_game\\player000.png"

#define POS_X_SPAWN_PLAYER	(300.0f)	//スポーン地点X座標
#define POS_Y_SPAWN_PLAYER	(540.0f)	//スポーン地点Y座標

#define SPAN_X_PLAYER	(180.0f)	//X全幅
#define SPAN_Y_PLAYER	(150.0f)	//Y全幅
#define HALFSPAN_X_PLAYER	(90.0f)	//X半幅
#define HALFSPAN_Y_PLAYER	(75.0f)	//Y半幅

#define MOVE_SPD_POS_PLAYER	(1.0f)			//移動速度
#define ATTENUATION_SPD_POS_PLAYER	(0.1f)	//移動量の減少速度
#define AMOUNT_CNT_CAST_VULKAN_PLAYER	(3)	//バルカンキャストカウント
#define AMOUNT_LIFE_PLAYER	(5)				//ライフ数
#define AMOUNT_CNT_STATE_PLAYER	(60)		//状態変化継続時間
#define AMOUNT_CAPACITY_PLAYER	(300)		//キャパ量
#define AMOUNT_CNT_CAPACITY_PLAYER	(3)		//キャパ回復キャスト時間

#define PUSHBACK_WALL_PLAYER	(0.1f)	//壁の反発量

//敵の状態分け列挙型
typedef enum
{
	PLAYERSTATE_NORMAL = 0,	//通常状態
	PLAYERSTATE_DAMAGE,		//ダメージ状態
	PLAYERSTATE_DEATH,		//死亡状態
	PLAYERSTATE_MAX,		//状態の総数
}PLAYERSTATE;

//プレイヤー情報の列挙型
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報格納
	D3DXVECTOR3 move;	//移動量格納
	PLAYERSTATE state;	//状態区別
	int nCntState;		//状態変化時間管理
	int nLife;			//ライフを格納
	int nCapacity;		//キャパシティを格納
}PLAYER;

//プロトタイプ宣言
void Init_Player(void);
void Uninit_Player(void);
void Update_Player(void);
void Draw_Player(void);
PLAYER* Getinfo_Player(void);
void Hit_Player(int nDamage);
void GetItem_Player(int nIncreaseCapacity);
int* Getinfo_BulletStyle(void);
void Animation_Player(void);

#endif