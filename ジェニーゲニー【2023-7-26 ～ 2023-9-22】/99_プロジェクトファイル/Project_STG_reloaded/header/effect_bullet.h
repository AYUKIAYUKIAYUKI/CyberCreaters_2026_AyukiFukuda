//************************************************
//
//弾道エフェクト処理、ヘッダファイル[effect_bullet.h]
//Author：福田歩希
//
//************************************************
#ifndef _EFFECT_BULLET_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _EFFECT_BULLET_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス*/
#define	TEXTURE_EFFECT_BULLET	"data\\TEX\\02_game\\effect0001.png"

#define AMOUNT_POLYGON_EFFECT_BULLET	(512)	//ポリゴン数

#define RADIUS_EFFECT_BULLET	(15.0f)		//半径用
#define REMAIN_TIME_EFFECT_BULLET	(15)	//残存時間(尾とか長くなる)

#define CHANGE_SPD_RADIUS_EFFECT_BULLET	(1.0f)	//縮む速度(すぼみ方変わる)

//弾の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報を格納
	D3DXVECTOR3 move;	//クソコード乙
	D3DXCOLOR col;
	float fRadius;		//半径を格納
	int nRemain;		//弾の残存設定
	bool bUse;			//使用状況判定
}EFFECT_BULLET;

//プロトタイプ宣言
void Init_Effect_Bullet(void);
void Uninit_Effect_Bullet(void);
void Update_Effect_Bullet(void);
void Draw_Effect_Bullet(void);
void Setinfo_Effect_Bullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col);

#endif