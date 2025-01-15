//************************************************
//
//ライフ表記、ヘッダファイル[life.h]
//Author：福田歩希
//
//************************************************
#ifndef _LIFE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _LIFE_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス*/
#define	TEXTURE_HEARTS_LIFE	"data\\TEX\\02_game\\life000.png"

#define POS_X_LEFT_LIFE	(270.0f)		//X座標の左用
#define POS_X_RIGHT_LIFE	(670.0f)	//X座標の右用
#define POS_Y_UP_LIFE	(875.0f)		//Y座標の上用
#define POS_Y_DOWN_LIFE	(945.0f)		//Y座標の下用

#define TEX_U_RIGHT_LIFE	(1.0f)	//U座標の右用
#define TEX_V_DOWN_LIFE	(0.16f)		//V座標の下用

#define MOVE_SPAN_TEX_LIFE	(0.168f)	//テクスチャ可動域

//ライフ数列挙型
typedef enum
{
	AMOUNT_LIFE_0 = 0,
	AMOUNT_LIFE_1,
	AMOUNT_LIFE_2,
	AMOUNT_LIFE_3,
	AMOUNT_LIFE_4,
	AMOUNT_LIFE_MAX,
}AMOUNT_LIFE;

//プロトタイプ宣言
void Init_Life(void);
void Uninit_Life(void);
void Update_Life(int nLife);
void Draw_Life(void);
void SetPos_Vtx_Life(void);

#endif