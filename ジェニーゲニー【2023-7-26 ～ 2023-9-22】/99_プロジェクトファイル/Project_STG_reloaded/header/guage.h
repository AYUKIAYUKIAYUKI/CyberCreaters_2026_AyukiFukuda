//************************************************
//
//ゲージ表示処理、ヘッダファイル[guage.h]
//Author：福田歩希
//
//************************************************
#ifndef _GUAGE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _GUAGE_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*デバッグ用*/
#define	TEXTURE_GUAGE	"data\\TEX\\02_game\\guage000.png"

#define POS_X_LEFT_GUAGE	(130.0f)	//X座標の左用
#define POS_X_RIGHT_GUAGE	(843.0f)	//X座標の右用
#define POS_Y_UP_GUAGE	(890.0f)		//Y座標の上用
#define POS_Y_DOWN_GUAGE	(1034.0f)	//Y座標の下用

#define DIVIDE_POLYGON_GUAGE	(2.376666f)	//ポリゴン分割量
#define DIVIDE_TEXTURE_GUAGE	(0.003333f)	//テクスチャ分割量

//プロトタイプ宣言
void Init_Guage(void);
void Uninit_Guage(void);
void Update_Guage(void);
void Draw_Guage(void);
void SetPos_Vtx_Guage(void);

#endif
