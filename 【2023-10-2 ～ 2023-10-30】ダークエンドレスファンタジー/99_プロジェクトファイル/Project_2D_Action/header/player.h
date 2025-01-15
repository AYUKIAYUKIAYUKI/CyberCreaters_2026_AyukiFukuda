//************************************************
//
//自機処理、ヘッダファイル[player.h]
//Author：福田歩希
//
//************************************************
#ifndef _PLEYER_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _PLEYER_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_CHARACTER_IDLE_PLAYER	"data\\TEX\\player_idle.png"
#define	TEXTURE_CHARACTER_JUMP_PLAYER	"data\\TEX\\player_only_jump.png"
#define	TEXTURE_CHARACTER_LAND_PLAYER	"data\\TEX\\player_only_land.png"
#define	TEXTURE_CHARACTER_RUN_PLAYER	"data\\TEX\\player_run1.png"
#define	TEXTURE_CHARACTER_LIGHT1_PLAYER	"data\\TEX\\player_light1.png"
#define	TEXTURE_CHARACTER_LIGHT2_PLAYER	"data\\TEX\\player_light2.png"
#define	TEXTURE_CHARACTER_LIGHT3_PLAYER	"data\\TEX\\player_light3.png"
#define	TEXTURE_CHARACTER_HEAVY1_PLAYER	"data\\TEX\\player_heavy1.png"
#define	TEXTURE_CHARACTER_HEAVY2_PLAYER	"data\\TEX\\player_heavy2.png"
#define	TEXTURE_CHARACTER_HEAVY3_PLAYER	"data\\TEX\\player_heavy3.png"
#define	TEXTURE_CHARACTER_HURT1_PLAYER	"data\\TEX\\player_hurt_1.png"
#define	TEXTURE_CHARACTER_HURT2_PLAYER	"data\\TEX\\player_hurt_2.png"

#define AMOUNT_TEX_PLAYER	(12)	//プレイヤーのテクスチャ総数

#define RADIUS_PLAYER_X	(35.0f)	//横半幅
#define RADIUS_PLAYER_Y	(50.0f)	//縦半幅

#define MOVE_SPD_PLAYER_X	(6.0f)	//横移動速度
#define MOVE_SPD_ATK_PLAYER_X	(8.0f)	//攻撃時横移動速度
#define MOVE_SPD_BRAKE_X	(0.75f)	//横移動ブレーキ速度
#define MOVE_SPD_PLAYER_Y	(40.0f)	//ジャンプ力
#define MOVE_SPD_GRAVITY_Y	(2.0f)	//重力加速度
#define ROTATE_SPD_PLAYER_Z	(-1.5625f)	//回転速度
#define ROTATE_SPD_BRAKE_Z	(0.8f)	//回転ブレーキ速度

#define AMOUNT_ABLE_JUMPS	(2)	//可能ジャンプ回数
//#define AMOUNT_MAX_LIFE_PLAYER	(7)	//ライフ数
#define AMOUNT_CT_LIGHT_COMBO	(40)	//弱攻撃コンボ猶予
#define AMOUNT_CT_HEAVY_COMBO	(60)	//強攻撃コンボ猶予
#define AMOUNT_CT_LIGHT	(10)	//弱攻撃CT
#define AMOUNT_CT_HEAVY	(25)	//強攻撃CT

#define FELL_RESET_MOVE_X	(50.0f)	//落下後復活横移動速度
#define FELL_RESET_MOVE_Y	(-50.0f)	//落下後復活縦移動速度
#define FELL_RESET_AREA_X	(100.0f)	//落下後復活横範囲
#define FELL_RESET_AREA_Y	(50.0f)	//落下後復活縦範囲

#define SPD_CHANGE_TEX_IDLE_PLAYER	(3)	//待機時のアニメーション速度
#define AMOUNT_STYLE_TEX_IDLE_PLAYER	(18)	//待機時のアニメーション用
#define SPAN_CHANGE_TEX_IDLE_PLAYER	(0.05555f)	//待機時のアニメーション用

#define SPD_CHANGE_TEX_JUMP_PLAYER	(2)	//ジャンプ時のアニメーション速度
#define AMOUNT_STYLE_TEX_JUMP_PLAYER	(14)	//ジャンプ時のアニメーション用
#define SPAN_CHANGE_TEX_JUMP_PLAYER	(0.06666f)	//ジャンプ時のアニメーション用

#define SPD_CHANGE_TEX_LAND_PLAYER	(2)	//着地時のアニメーション速度
#define AMOUNT_STYLE_TEX_LAND_PLAYER	(4)	//着地時のアニメーション用
#define SPAN_CHANGE_TEX_LAND_PLAYER	(0.25f)	//着地時のアニメーション用

#define SPD_CHANGE_TEX_RUN_PLAYER	(2)	//走行時のアニメーション速度
#define AMOUNT_STYLE_TEX_RUN_PLAYER	(24)	//走行時のアニメーション用
#define SPAN_CHANGE_TEX_RUN_PLAYER	(0.04166f)	//走行時のアニメーション用

#define SPD_CHANGE_TEX_LIGHT1_PLAYER	(2)	//弱1時のアニメーション速度
#define AMOUNT_STYLE_TEX_LIGHT1_PLAYER	(8)	//弱1時のアニメーション用
#define SPAN_CHANGE_TEX_LIGHT1_PLAYER	(0.125f)	//弱1時のアニメーション用

#define SPD_CHANGE_TEX_LIGHT2_PLAYER	(2)	//弱2時のアニメーション速度
#define AMOUNT_STYLE_TEX_LIGHT2_PLAYER	(7)	//弱2時のアニメーション用
#define SPAN_CHANGE_TEX_LIGHT2_PLAYER	(0.14285f)	//弱2時のアニメーション用

#define SPD_CHANGE_TEX_LIGHT3_PLAYER	(2)	//弱3時のアニメーション速度
#define AMOUNT_STYLE_TEX_LIGHT3_PLAYER	(10)	//弱3時のアニメーション用
#define SPAN_CHANGE_TEX_LIGHT3_PLAYER	(0.09090f)	//弱3時のアニメーション用

#define SPD_CHANGE_TEX_HEAVY1_PLAYER	(3)	//強1時のアニメーション速度
#define AMOUNT_STYLE_TEX_HEAVY1_PLAYER	(12)	//強1時のアニメーション用
#define SPAN_CHANGE_TEX_HEAVY1_PLAYER	(0.08333f)	//強1時のアニメーション用

#define SPD_CHANGE_TEX_HEAVY2_PLAYER	(3)	//強2時のアニメーション速度
#define AMOUNT_STYLE_TEX_HEAVY2_PLAYER	(12)	//強2時のアニメーション用
#define SPAN_CHANGE_TEX_HEAVY2_PLAYER	(0.08333f)	//強2時のアニメーション用

#define SPD_CHANGE_TEX_HEAVY3_PLAYER	(3)	//強3時のアニメーション速度
#define AMOUNT_STYLE_TEX_HEAVY3_PLAYER	(16)	//強3時のアニメーション用
#define SPAN_CHANGE_TEX_HEAVY3_PLAYER	(0.0625f)	//強3時のアニメーション用

#define SPD_CHANGE_TEX_HURT1_PLAYER	(3)	//被弾1時のアニメーション速度
#define AMOUNT_STYLE_TEX_HURT1_PLAYER	(7)	//被弾1時のアニメーション用
#define SPAN_CHANGE_TEX_HURT1_PLAYER	(0.14285f)	//被弾1時のアニメーション用

#define SPD_CHANGE_TEX_HURT2_PLAYER	(3)	//被弾2時のアニメーション速度
#define AMOUNT_STYLE_TEX_HURT2_PLAYER	(7)	//被弾2時のアニメーション用
#define SPAN_CHANGE_TEX_HURT2_PLAYER	(0.14285f)	//被弾2時のアニメーション用

//プレイヤー状態の列挙型
typedef enum
{
	PLAYER_STATE_IDLE = 0,	//待機
	PLAYER_STATE_JUMP,		//ジャンプ
	PLAYER_STATE_FALL,		//落下
	PLAYER_STATE_LAND,		//着地
	PLAYER_STATE_RUN,		//走行
	PLAYER_STATE_TURN,		//振りむき
	PLAYER_STATE_SLIDE,		//スライディング
	PLAYER_STATE_LIGHT1,	//弱1
	PLAYER_STATE_LIGHT2,	//弱2
	PLAYER_STATE_LIGHT3,	//弱3
	PLAYER_STATE_HEAVY1,	//強1
	PLAYER_STATE_HEAVY2,	//強2
	PLAYER_STATE_HEAVY3,	//強3
	PLAYER_STATE_BOW,		//弓
	PLAYER_STATE_HURT1,		//被弾1
	PLAYER_STATE_HURT2,		//被弾2
	PLAYER_STATE_CLIMB,		//壁
	PLAYER_STATE_MAX,
}PLAYER_STATE;

//プレイヤー情報の構造型
typedef struct
{
	int nState;			//プレイヤーの状態
	D3DXVECTOR3 BGpos;	//実際位置
	D3DXVECTOR3 pos;	//疑似位置
	D3DXVECTOR3 oldpos;	//前の位置
	D3DXVECTOR3 lastland;//最後の着地位置
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
	bool bLanding;		//着地判定
	int nJumpTimes;		//ジャンプ回数
	//int nLife;			//ライフ数
	bool bFell;			//落下判定
	int nLastATK;		//最終攻撃タイプ
	bool bAfterATK;		//攻撃後判定
	int nCntAfterATK;	//攻撃後カウント
}PLAYER;

//プレイヤーボックス情報の構造型
typedef struct
{
	float fRadius_Hold[2];	//半径
	float fLength_Hold[2];	//対角線
	float fAngle_Hold[2];	//角度
}PLAYER_BOX;

//プロトタイプ宣言

/*生成*/
void Init_Player(void);

/*破棄*/
void Uninit_Player(void);

/*更新*/
void Update_Player(void);

/*描画*/
void Draw_Player(void);

/*見かけ上のプレイヤーボックスサイズを算出(テクスチャ用)*/
void CalcSize_Player_Box(void);

/*プレイヤーにデータを付与*/
void SetInfo_Player(void);

/*プレイヤーを移動させる*/
void Move_Pos_Player(void);

/*プレイヤーのバーテックスを更新*/
void Update_Pos_Player(void);

/*見かけの位置と本来の位置を調整*/
void Adjust_Pos_Player(void);

/*テクスチャアニメーション処理*/
void Update_Tex_Player(void);

/*プレイヤーのデータを取得*/
PLAYER* GetInfo_Player(void);

/*プレイヤーボックスのデータを取得*/
PLAYER_BOX* GetInfo_Player_Box(void);

/*プレイヤーの位置を取得*/
D3DXVECTOR3 GetInfo_Pos_Player(void);

#endif