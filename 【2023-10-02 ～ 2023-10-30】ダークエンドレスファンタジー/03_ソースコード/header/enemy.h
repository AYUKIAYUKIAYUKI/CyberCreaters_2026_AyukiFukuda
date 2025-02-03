//************************************************
//
//敵処理、ヘッダファイル[enemy.h]
//Author：福田歩希
//
//************************************************
#ifndef _ENEMY_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _ENEMY_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_ENEMY_00_MOVE "data\\TEX\\e00_move.png"
#define	TEXTURE_ENEMY_00_ATK "data\\TEX\\e00_atk.png"
#define	TEXTURE_ENEMY_00_HURT "data\\TEX\\e00_hurt.png"
#define	TEXTURE_ENEMY_00_DEATH "data\\TEX\\e00_death.png"

#define	TEXTURE_ENEMY_01_IDLE "data\\TEX\\e01_idle.png"
#define	TEXTURE_ENEMY_01_MOVE "data\\TEX\\e01_move.png"
#define	TEXTURE_ENEMY_01_ATK "data\\TEX\\e01_atk.png"
#define	TEXTURE_ENEMY_01_HURT "data\\TEX\\e01_hurt.png"
#define	TEXTURE_ENEMY_01_DEATH "data\\TEX\\e01_death.png"

#define	TEXTURE_ENEMY_02_IDLE "data\\TEX\\e02_idle.png"
#define	TEXTURE_ENEMY_02_MOVE "data\\TEX\\e02_move.png"
#define	TEXTURE_ENEMY_02_ATK "data\\TEX\\e02_atk.png"
#define	TEXTURE_ENEMY_02_HURT "data\\TEX\\e02_hurt.png"
#define	TEXTURE_ENEMY_02_DEATH "data\\TEX\\e02_death.png"

#define	TEXTURE_ENEMY_03_IDLE "data\\TEX\\e03_idle.png"
#define	TEXTURE_ENEMY_03_MOVE "data\\TEX\\e03_move.png"
#define	TEXTURE_ENEMY_03_ATK "data\\TEX\\e03_atk.png"
#define	TEXTURE_ENEMY_03_HURT "data\\TEX\\e03_hurt.png"
#define	TEXTURE_ENEMY_03_DEATH "data\\TEX\\e03_death.png"

#define	TEXTURE_ENEMY_04_IDLE "data\\TEX\\e04_idle.png"
#define	TEXTURE_ENEMY_04_MOVE "data\\TEX\\e04_move.png"
#define	TEXTURE_ENEMY_04_ATK "data\\TEX\\e04_atk.png"
#define	TEXTURE_ENEMY_04_HURT "data\\TEX\\e04_hurt.png"
#define	TEXTURE_ENEMY_04_DEATH "data\\TEX\\e04_death.png"

#define AMOUNT_POLYGON_ENEMY	(6)	//敵のポリゴン総数
#define AMOUNT_TEX_ENEMY	(24)	//敵のテクスチャ総数

#define RADIUS_ENEMY_X	(30.0f)	//汎用横半幅(当たり判定に用います、見た目サイズ用ではない！)
#define RADIUS_ENEMY_Y	(30.0f)	//汎用縦半幅

#define AMOUN_RESPAWN_CT	(40)	//全体の敵のリスポーン間隔(フレーム)

#define AMOUNT_MAX_LIFE_ENEMY_00	(1)	//00ライフ
#define AMOUNT_MAX_LIFE_ENEMY_01	(2)	//01ライフ
#define AMOUNT_MAX_LIFE_ENEMY_02	(1)	//02ライフ
#define AMOUNT_MAX_LIFE_ENEMY_03	(3)	//03ライフ
#define AMOUNT_MAX_LIFE_ENEMY_04	(4)	//04ライフ

#define AMOUNT_CT_ATK_ENEMY_00	(30)	//00攻撃CT
#define AMOUNT_CT_ATK_ENEMY_01	(50)	//01攻撃CT
#define AMOUNT_CT_ATK_ENEMY_02	(20)	//02攻撃CT
#define AMOUNT_CT_ATK_ENEMY_03	(80)	//03攻撃CT
#define AMOUNT_CT_ATK_ENEMY_04	(80)	//04攻撃CT

#define SPD_CHANGE_TEX_MOVE_ENEMY_00	(3)	//00移動時のアニメーション速度
#define AMOUNT_STYLE_TEX_MOVE_ENEMY_00	(8)	//00移動時のアニメーション用
#define SPAN_CHANGE_TEX_MOVE_ENEMY_00	(0.125f)	//00移動時のアニメーション用

#define SPD_CHANGE_TEX_ATK_ENEMY_00	(2)	//00攻撃時のアニメーション速度
#define AMOUNT_STYLE_TEX_ATK_ENEMY_00	(8)	//00攻撃時のアニメーション用
#define SPAN_CHANGE_TEX_ATK_ENEMY_00	(0.125f)	//00攻撃時のアニメーション用

#define SPD_CHANGE_TEX_HURT_ENEMY_00	(3)	//00被弾時のアニメーション速度
#define AMOUNT_STYLE_TEX_HURT_ENEMY_00	(4)	//00被弾時のアニメーション用
#define SPAN_CHANGE_TEX_HURT_ENEMY_00	(0.25f)	//00被弾時のアニメーション用

#define SPD_CHANGE_TEX_DEATH_ENEMY_00	(4)	//00死亡時のアニメーション速度
#define AMOUNT_STYLE_TEX_DEATH_ENEMY_00	(4)	//00死亡時のアニメーション用
#define SPAN_CHANGE_TEX_DEATH_ENEMY_00	(0.25f)	//00死亡時のアニメーション用

#define SPD_CHANGE_TEX_IDLE_ENEMY_01	(7)	//01待機時のアニメーション速度
#define AMOUNT_STYLE_TEX_IDLE_ENEMY_01	(4)	//01待機時のアニメーション用
#define SPAN_CHANGE_TEX_IDLE_ENEMY_01	(0.25f)	//01待機時のアニメーション用

#define SPD_CHANGE_TEX_MOVE_ENEMY_01	(5)	//01移動時のアニメーション速度
#define AMOUNT_STYLE_TEX_MOVE_ENEMY_01	(8)	//01移動時のアニメーション用
#define SPAN_CHANGE_TEX_MOVE_ENEMY_01	(0.125f)	//01移動時のアニメーション用

#define SPD_CHANGE_TEX_ATK_ENEMY_01	(2)	//01攻撃時のアニメーション速度
#define AMOUNT_STYLE_TEX_ATK_ENEMY_01	(8)	//01攻撃時のアニメーション用
#define SPAN_CHANGE_TEX_ATK_ENEMY_01	(0.125f)	//01攻撃時のアニメーション用

#define SPD_CHANGE_TEX_HURT_ENEMY_01	(4)	//01被弾時のアニメーション速度
#define AMOUNT_STYLE_TEX_HURT_ENEMY_01	(4)	//01被弾時のアニメーション用
#define SPAN_CHANGE_TEX_HURT_ENEMY_01	(0.25f)	//01被弾時のアニメーション用

#define SPD_CHANGE_TEX_DEATH_ENEMY_01	(4)	//01死亡時のアニメーション速度
#define AMOUNT_STYLE_TEX_DEATH_ENEMY_01	(4)	//01死亡時のアニメーション用
#define SPAN_CHANGE_TEX_DEATH_ENEMY_01	(0.25f)	//01死亡時のアニメーション用

#define SPD_CHANGE_TEX_IDLE_ENEMY_02	(5)	//02待機時のアニメーション速度
#define AMOUNT_STYLE_TEX_IDLE_ENEMY_02	(4)	//02待機時のアニメーション用
#define SPAN_CHANGE_TEX_IDLE_ENEMY_02	(0.25f)	//02待機時のアニメーション用

#define SPD_CHANGE_TEX_MOVE_ENEMY_02	(3)	//02移動時のアニメーション速度
#define AMOUNT_STYLE_TEX_MOVE_ENEMY_02	(8)	//02移動時のアニメーション用
#define SPAN_CHANGE_TEX_MOVE_ENEMY_02	(0.125f)	//02移動時のアニメーション用

#define SPD_CHANGE_TEX_ATK_ENEMY_02	(3)	//02攻撃時のアニメーション速度
#define AMOUNT_STYLE_TEX_ATK_ENEMY_02	(8)	//02攻撃時のアニメーション用
#define SPAN_CHANGE_TEX_ATK_ENEMY_02	(0.125f)	//02攻撃時のアニメーション用

#define SPD_CHANGE_TEX_HURT_ENEMY_02	(3)	//02被弾時のアニメーション速度
#define AMOUNT_STYLE_TEX_HURT_ENEMY_02	(4)	//02被弾時のアニメーション用
#define SPAN_CHANGE_TEX_HURT_ENEMY_02	(0.25f)	//02被弾時のアニメーション用

#define SPD_CHANGE_TEX_DEATH_ENEMY_02	(4)	//02死亡時のアニメーション速度
#define AMOUNT_STYLE_TEX_DEATH_ENEMY_02	(4)	//02死亡時のアニメーション用
#define SPAN_CHANGE_TEX_DEATH_ENEMY_02	(0.25f)	//02死亡時のアニメーション用

#define SPD_CHANGE_TEX_IDLE_ENEMY_03	(6)	//03待機時のアニメーション速度
#define AMOUNT_STYLE_TEX_IDLE_ENEMY_03	(4)	//03待機時のアニメーション用
#define SPAN_CHANGE_TEX_IDLE_ENEMY_03	(0.25f)	//03待機時のアニメーション用

#define SPD_CHANGE_TEX_MOVE_ENEMY_03	(4)	//03移動時のアニメーション速度
#define AMOUNT_STYLE_TEX_MOVE_ENEMY_03	(4)	//03移動時のアニメーション用
#define SPAN_CHANGE_TEX_MOVE_ENEMY_03	(0.25f)	//03移動時のアニメーション用

#define SPD_CHANGE_TEX_ATK_ENEMY_03	(5)	//03攻撃時のアニメーション速度
#define AMOUNT_STYLE_TEX_ATK_ENEMY_03	(8)	//03攻撃時のアニメーション用
#define SPAN_CHANGE_TEX_ATK_ENEMY_03	(0.125f)	//03攻撃時のアニメーション用

#define SPD_CHANGE_TEX_HURT_ENEMY_03	(3)	//03被弾時のアニメーション速度
#define AMOUNT_STYLE_TEX_HURT_ENEMY_03	(4)	//03被弾時のアニメーション用
#define SPAN_CHANGE_TEX_HURT_ENEMY_03	(0.25f)	//03被弾時のアニメーション用

#define SPD_CHANGE_TEX_DEATH_ENEMY_03	(4)	//03死亡時のアニメーション速度
#define AMOUNT_STYLE_TEX_DEATH_ENEMY_03	(4)	//03死亡時のアニメーション用
#define SPAN_CHANGE_TEX_DEATH_ENEMY_03	(0.25f)	//03死亡時のアニメーション用

#define SPD_CHANGE_TEX_IDLE_ENEMY_04	(3)	//04待機時のアニメーション速度
#define AMOUNT_STYLE_TEX_IDLE_ENEMY_04	(9)	//04待機時のアニメーション用
#define SPAN_CHANGE_TEX_IDLE_ENEMY_04	(0.11111f)	//04待機時のアニメーション用

#define SPD_CHANGE_TEX_MOVE_ENEMY_04	(3)	//04移動時のアニメーション速度
#define AMOUNT_STYLE_TEX_MOVE_ENEMY_04	(9)	//04移動時のアニメーション用
#define SPAN_CHANGE_TEX_MOVE_ENEMY_04	(0.11111f)	//04移動時のアニメーション用

#define SPD_CHANGE_TEX_ATK_ENEMY_04	(3)	//04攻撃時のアニメーション速度
#define AMOUNT_STYLE_TEX_ATK_ENEMY_04	(16)	//04攻撃時のアニメーション用
#define SPAN_CHANGE_TEX_ATK_ENEMY_04	(0.0625f)	//04攻撃時のアニメーション用

#define SPD_CHANGE_TEX_HURT_ENEMY_04	(4)	//04被弾時のアニメーション速度
#define AMOUNT_STYLE_TEX_HURT_ENEMY_04	(3)	//04被弾時のアニメーション用
#define SPAN_CHANGE_TEX_HURT_ENEMY_04	(0.33333f)	//04被弾時のアニメーション用

#define SPD_CHANGE_TEX_DEATH_ENEMY_04	(4)	//04死亡時のアニメーション速度
#define AMOUNT_STYLE_TEX_DEATH_ENEMY_04	(8)	//04死亡時のアニメーション用
#define SPAN_CHANGE_TEX_DEATH_ENEMY_04	(0.125)	//04死亡時のアニメーション用

//敵列挙型
typedef enum
{
	ENEMY_00 = 0,
	ENEMY_01,
	ENEMY_02,
	ENEMY_03,
	ENEMY_04,
	ENEMY_MAX
}ENEMY_STYLE;

//敵00の状態の列挙型
typedef enum
{
	ENEMY_00_STATE_MOVE,	//移動
	ENEMY_00_STATE_ATK,		//攻撃
	ENEMY_00_STATE_HURT,	//被弾
	ENEMY_00_STATE_DEATH,	//死亡
}ENEMY_00_STATE;

//敵01の状態の列挙型
typedef enum
{
	ENEMY_01_STATE_IDLE,	//待機
	ENEMY_01_STATE_MOVE,	//移動
	ENEMY_01_STATE_ATK,		//攻撃
	ENEMY_01_STATE_HURT,	//被弾
	ENEMY_01_STATE_DEATH,	//死亡
}ENEMY_01_STATE;

//敵02の状態の列挙型
typedef enum
{
	ENEMY_02_STATE_IDLE,	//待機
	ENEMY_02_STATE_MOVE,	//移動
	ENEMY_02_STATE_ATK,		//攻撃
	ENEMY_02_STATE_HURT,	//被弾
	ENEMY_02_STATE_DEATH,	//死亡
}ENEMY_02_STATE;

//敵03の状態の列挙型
typedef enum
{
	ENEMY_03_STATE_IDLE,	//待機
	ENEMY_03_STATE_MOVE,	//移動
	ENEMY_03_STATE_ATK,		//攻撃
	ENEMY_03_STATE_HURT,	//被弾
	ENEMY_03_STATE_DEATH,	//死亡
}ENEMY_03_STATE;

//敵04の状態の列挙型
typedef enum
{
	ENEMY_04_STATE_IDLE,	//待機
	ENEMY_04_STATE_MOVE,	//移動
	ENEMY_04_STATE_ATK,		//攻撃
	ENEMY_04_STATE_HURT,	//被弾
	ENEMY_04_STATE_DEATH,	//死亡
}ENEMY_04_STATE;

//プレイヤー情報の構造型
typedef struct
{
	bool bUse;			//出現判定
	int nStyle;			//敵の種類
	int nState;			//敵の状態
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 oldpos;	//前の位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//回転
	D3DXCOLOR col;		//色
	int LR;				//向き
	int nCntTex;		//テクスチャ変更
	int nCntPattern;	//テクスチャ変更
	float fTexSpan[2];	//テクスチャ幅
	float fRadius[2];	//半径
	float fLength[2];	//対角線
	float fAngle[2];	//角度
	float fDisappear;	//チジミ
	int nLife;			//ライフ数
	int nCT;			//キャストタイム
	bool bLockonP;		//プレイヤー索敵
}ENEMY;

//t敵ボックス情報の構造型
typedef struct
{
	float fRadius_Hold[2];	//半径
	float fLength_Hold[2];	//対角線
	float fAngle_Hold[2];	//角度
}ENEMY_BOX;

//プロトタイプ宣言

/*生成*/
void Init_Enemy(void);

/*破棄*/
void Uninit_Enemy(void);

/*更新*/
void Update_Enemy(void);

/*描画*/
void Draw_Enemy(void);

/*見かけ上のエネミーボックスサイズを算出(テクスチャ用)*/
void CalcSize_Enemy_Box(void);

/*敵にデータを付与*/
void SetInfo_Enemy(void);

/*敵のバーテックスを更新*/
void Update_Pos_Enemy(int i);

/*敵を倒したときの消滅処理*/
void Disapper_Enemy(int i);

/*見かけの位置と本来の位置を調整*/
void Adjust_Pos_Enemy(int i);

/*テクスチャアニメーション処理*/
void Update_Tex_Enemy(int i);

/*敵との当たり判定*/
//void Hit_Detection_Enemy(int i);

/*敵のデータを取得*/
ENEMY* GetInfo_Enemy(void);

#endif