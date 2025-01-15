//************************************************
//
//弾の処理、ヘッダファイル[bullet.h]
//Author：福田歩希
//
//************************************************
#ifndef _BULLET_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BULLET_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義n

/*画像パス系*/
#define	TEXTURE_COMET_BULLET	"data\\TEX\\02_game\\comet_effect.png"
#define	TEXTURE_REUNION_1_BULLET	"data\\TEX\\02_game\\bullet003.png"
#define	TEXTURE_REUNION_2_BULLET	"data\\TEX\\02_game\\bullet002.png"
#define	TEXTURE_KING_BULLET	"data\\TEX\\02_game\\knife000.png"

#define AMOUNT_POLYGON_BULLET	(128)	//ポリゴン数
#define AMOUNT_TEXTURE_BULLET	(4)		//読込みテクスチャ数

#define SPAN_X_BULLET	(150.0f)	//平均的な弾丸X全幅
#define SPAN_Y_BULLET	(150.0f)	//平均的な弾丸Y全幅
#define	HALFSPAN_X_BULLET	(75.0f)	//平均的な弾丸X半幅
#define HALFSPAN_Y_BULLET	(75.0f)	//平均的な弾丸Y半幅

#define MOVE_SPD_POS_BULLET	(15.0f)	//平均的な弾速
#define ROTATE_SPD_BULLET	(0.1f)	//平均的な弾回転速度
#define REMAIN_TIME_BULLET	(60)	//平均的な弾の残存時間
#define AMOUNT_DAMAGE_BULLET	(1)	//平均的な弾の持つダメージ量

#define APPARENTSPAN_RADIUS_BULLET	(0.5f)	//見た目と実際の当たり判定を整合する係数

#define PER_ONE_TEX_X_COMET_BULLET	(0.2f)	//テクスチャ1つあたりの横幅
#define PER_ONE_TEX_Y_COMET_BULLET	(0.5f)	//縦幅
#define CHEANGE_SPD_TEX_COMET_BULLET	(3)	//コメット変化キャスト時間

#define AMOUNT_USING_POLYGON_REUNION_BULLET	(2)	//リユニオンに発射に使う弾数
#define ANGLE_REUNION_BULLET	(3.0f)			//リユニオンの射出角度
#define MOVE_ANGLE_REUNION_BULLET	(0.025f)	//リユニオンの角度変動量
#define REMAIN_REUNION_TIME_BULLET	(42)		//リユニオンの残存時間

#define HALFSPAN_KNIFE_X_BULLET	(75.0f)		//ナイフX半幅
#define HALFSPAN_KNIFE_Y_BULLET	(15.0f)		//ナイフY半幅
#define AMOUNT_KNIFE_DAMAGE_BULLET	(999)	//ナイフダメージ量

#define AMOUNT_DECREASE_CAPACITY_COMET_BULLET	(25)	//各キャパ減少量
#define AMOUNT_DECREASE_CAPACITY_REUNION_BULLET	(30)
#define AMOUNT_DECREASE_CAPACITY_KING_BULLET	(200)

#define AMOUNT_ADD_SCORE_BULLET	(10)	//スコア加算量

#define DUMMY_POS_BULLET	(-100.0f)	//ダミー

//弾の種類分け列挙型
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//プレイヤーの弾
	BULLETTYPE_ENEMY,		//敵の弾
	BULLETTYPE_NONE,		//どれにも付属しない弾
	BULLETTYPE_MAX,			//種類の数
}BULLETTYPE;

//弾の種類の列挙型
typedef enum
{
	BULLETSTYLE_COMET = 0,	//通常弾
	BULLETSTYLE_REUNION,	//強化弾
	BULLETSTYLE_KING,		//一撃必殺
	BULLETSTYLE_MAX,		//弾の種類総数
}BULLETSTYLE;

//弾道分岐の列挙型
typedef enum
{
	BULLETRUTE_UP = 0,	//上分岐
	BULLETRUTE_DOWN,	//下分岐
	BULLETRUTE_NONE,	//分岐無し
	BULLETRUTE_MAX,		//分岐の総数
}BULLETRUTE;

//弾の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報を格納
	D3DXVECTOR3 move;	//移動量を格納
	D3DXVECTOR3 rot;	//向きを格納
	int nRemain;		//弾の残存設定
	bool bUse;			//使用状況判定
	BULLETTYPE type;	//弾が何に付属するものか
	BULLETSTYLE style;	//弾の種類
	BULLETRUTE rute;	//弾道の分岐
	float fLength;		//弾の対角線
	float fAngle;		//弾の角度
	int nDamage;		//弾の攻撃力
	int nPattern;		//アニメパターン
	float fTexX;		//テクスチャ座標X
	float fTexY;		//テクスチャ座標Y
}BULLET;

//プロトタイプ宣言
void Init_Bullet(void);
void Uninit_Bullet(void);
void Update_Bullet(void);
void Draw_Bullet(void);
void Setinfo_Bullet(D3DXVECTOR3 pos, int nSetBulletStyle);
//void CalcNearlyVector_Bullet(int nCntBullet);
void Sort_BulletStyle(int nCnt);
void Updateinfo_Comet(int nCnt);
void Updateinfo_Reunion(int nCnt);
void Updateinfo_King(int nCnt);
void HitDetection_Cloud_Enemy(int nCnt);
void HitDetection_Glide_Enemy(int nCnt);
void HitDetection_Slide_Enemy(int nCnt);
void HitDetection_Block(int nCnt);
void HitDetection_SlideBlock(int nCnt);
void HitDetection_BreakBlock(int nCnt);
void HitDetection_Spiral_Enemy(int nCnt);

#endif