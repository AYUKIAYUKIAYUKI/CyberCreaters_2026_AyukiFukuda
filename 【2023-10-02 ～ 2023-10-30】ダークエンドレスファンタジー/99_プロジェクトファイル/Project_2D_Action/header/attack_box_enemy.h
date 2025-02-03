//************************************************
//
//敵用攻撃ボックス処理、ヘッダファイル[attack_box_enemy.h]
//Author：福田歩希
//
//************************************************
#ifndef _ATTACK_BOX_ENEMY_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _ATTACK_BOX_ENEMY_H_	//(二重インクルード防止、マクロ定義する)

/*画像パス系*/
#define	TEXTURE_ENEMY_NONE "data\\TEX\\white.png"
#define	TEXTURE_ENEMY_04_BALL "data\\TEX\\e04_ball.png"
#define	TEXTURE_ENEMY_04_BALLEND "data\\TEX\\e04_ballend.png"

#define AMOUNT_TEX_BOX	(3)	//テクスチャ数

#define SPD_CHANGE_TEX_FIRE_ENEMY_04	(2)	//ぼっくスモードファイアのアニメーション速度
#define AMOUNT_STYLE_TEX_FIRE_ENEMY_04	(6)	//ぼっくスモードファイアのアニメーション用
#define SPAN_CHANGE_TEX_FIRE_ENEMY_04	(0.16666f)	//ぼっくスモードファイアアニメーション用

#define SPD_CHANGE_TEX_FIREEND_ENEMY_04	(2)	//ぼっくスモードファイアのアニメーション速度
#define AMOUNT_STYLE_TEX_FIREEND_ENEMY_04	(7)	//ぼっくスモードファイアのアニメーション用
#define SPAN_CHANGE_TEX_FIREEND_ENEMY_04	(0.14285f)	//ぼっくスモードファイアアニメーション用
	
typedef enum
{
	BOX_MODE_NONE = 0,
	BOX_MODE_FIRE,
	BOX_MODE_FIRE_END,
	BOX_MODE_MAX,
}BOX_MODE;

//敵攻撃ボックスの情報の構造型
typedef struct
{
	int nMode;			//ボックス可視モード
	bool bUse;			//使用判定
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	float fX;			//補正
	D3DXVECTOR3 rot;	//回転
	D3DXCOLOR col;		//色
	int LR;				//向き
	int nCntTex;		//テクスチャ変更
	int nCntPattern;	//テクスチャ変更
	float fTexSpan[2];	//テクスチャ幅
	float fRadius[2];	//半径
	float fLength[2];	//対角線
	float fAngle[2];	//角度
	int nAppear;		//生成時間
	int nRemain;		//残存時間
}ATTACK_BOX_ENEMY;

//プロトタイプ宣言

/*生成*/
void Init_Attack_Box_Enemy(void);

/*破棄*/
void Uninit_Attack_Box_Enemy(void);

/*更新*/
void Update_Attack_Box_Enemy(void);

/*攻撃ボックスにデータを付与*/
void GiveInfo_Attack_Box_Enemy(int i);

/*敵用の攻撃ボックスを調整*/
void Front_Enemy(int i);

/*攻撃ボックスのバーテックスを更新*/
void Update_Pos_Attack_Box_Enemy(void);

/*色*/
void Update_Col_Attack_Box_Enemy(int i);

/*テクスチャアニメーション処理*/
void Update_Tex_Attack_Box_Enemy(int i);

/*攻撃ボックスの残存時間が減少*/
void Disapper_Attack_Box_Enemy(void);

/*当たり判定*/
void HitDetection_Attack_Box_Enemy(int i);

/*敵攻撃ボックスのデータを取得*/
ATTACK_BOX_ENEMY* GetInfo_Attack_Box_Enemy(void);

/*デバッグ用攻撃ボックス可視化描画*/
void Draw_Attack_Box_Enemy_Debug(void);

#endif