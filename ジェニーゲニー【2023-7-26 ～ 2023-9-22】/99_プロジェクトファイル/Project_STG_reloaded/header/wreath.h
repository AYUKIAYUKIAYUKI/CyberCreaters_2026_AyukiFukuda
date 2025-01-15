//************************************************
//
//リース表示処理、ヘッダファイル[wreath.h]
//Author：福田歩希
//
//************************************************
#ifndef _WREATH_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _WREATH_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*デバッグ用*/
#define	TEXTURE_WREATH	"data\\TEX\\02_game\\bulletwindow000.png"
#define	TEXTURE_WOOD	"data\\TEX\\99_nonuse\\stump000.png"

#define AMOUNT_POLYGON_WREATH	(2)	//ポリゴン数
#define AMOUNT_TEXTURE_WREATH	(2)		//読込みテクスチャ数

#define POS_X_LEFT_WREATH	(20.0f)		//X座標の左用
#define POS_X_RIGHT_WREATH	(260.0f)	//X座標の右用
#define POS_Y_UP_WREATH	(810.0f)		//Y座標の上用
#define POS_Y_DOWN_WREATH	(1060.0f)	//Y座標の下用

#define POS_WOOD	(55.0f)	//木皿用

//プロトタイプ宣言
void Init_Wreath(void);
void Uninit_Wreath(void);
void Draw_Wreath(void);
void SetPos_Vtx_Wreath(void);

#endif