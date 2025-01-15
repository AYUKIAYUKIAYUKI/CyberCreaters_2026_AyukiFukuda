//************************************************
//
//ゲージバー表示処理、ヘッダファイル[guagebar.h]
//Author：福田歩希
//
//************************************************
#ifndef _GUAGEBAR_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _GUAGEBAR_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*デバッグ用*/
#define	TEXTURE_GUAGEBAR	"data\\TEX\\02_game\\bulletwindow001.png"

#define POS_X_LEFT_GUAGEBAR	(130.0f)		//X座標の左用
#define POS_X_RIGHT_GUAGEBAR	(843.0f)	//X座標の右用
#define POS_Y_UP_GUAGEBAR	(890.0f)		//Y座標の上用
#define POS_Y_DOWN_GUAGEBAR	(1034.0f)		//Y座標の下用

//プロトタイプ宣言
void Init_GuageBar(void);
void Uninit_GuageBar(void);
void Draw_GuageBar(void);
void SetPos_Vtx_GuageBar(void);

#endif