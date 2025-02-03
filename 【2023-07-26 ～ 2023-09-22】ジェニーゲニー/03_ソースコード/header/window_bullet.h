//************************************************
//
//弾ウィンドウ表示処理、ヘッダファイル[window_bullet.h]
//Author：福田歩希
//
//************************************************
#ifndef _WINDOW_BULLET_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _WINDOW_BULLET_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*デバッグ用*/
#define	TEXTURE_WINDOW_BULLET	"data\\TEX\\02_game\\bulletwindow002.png"

#define POS_X_LEFT_WINDOW_BULLET	(20.0f)		//X座標の左用
#define POS_X_RIGHT_WINDOW_BULLET	(260.0f)	//X座標の右用
#define POS_Y_UP_WINDOW_BULLET	(810.0f)		//Y座標の上用
#define POS_Y_DOWN_WINDOW_BULLET	(1060.0f)	//Y座標の下用

//プロトタイプ宣言
void Init_Window_Bullet(void);
void Uninit_Window_Bullet(void);
void Draw_Window_Bullet(void);
void SetPos_Vtx_Window_Bullet(void);

#endif