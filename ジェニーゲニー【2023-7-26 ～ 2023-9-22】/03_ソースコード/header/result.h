//************************************************
//
//リザルト表示処理、ヘッダファイル(荒れ地)[result.h]
//Author：福田歩希
//
//************************************************
#ifndef _RESULT_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RESULT_H _	//(二重インクルード防止、マクロ定義する)

#include "../header/main.h"

//マクロ定義
#define AMT_PLG_RESULT	(4)				//ポリゴンの頂点数	
#define AMT_TRI_RESULT	(2)				//ポリゴンの数
#define RELATIVE_X_RESULT	(990.0f)	//X相対幅
#define RELATIVE_Y_RESULT	(540.0f)	//Y相対幅
#define SPAN_X_RESULT	(1980.0f)		//X全幅
#define SPAN_Y_RESULT	(1080.0f)		//Y全幅
#define	TEX_1_RESULT	"data\\TEX\\03_result\\GAMECLEAR000.png"//画像ファイル1
#define	TEX_2_RESULT	"data\\TEX\\03_result\\GAMEOVER000.png"	//画像ファイル2
#define	TEX_3_RESULT	"data\\TEX\\03_result\\menu000.png"		//画像ファイル3
#define	TEX_4_RESULT	"data\\TEX\\03_result\\menu001.png"		//画像ファイル4
#define	TEX_5_RESULT	"data\\TEX\\03_result\\retry000.png"	//画像ファイル5
#define	TEX_6_RESULT	"data\\TEX\\03_result\\retry001.png"	//画像ファイル6
#define	TEX_7_RESULT	"data\\TEX\\03_result\\exit000.png"		//画像ファイル7
#define	TEX_8_RESULT	"data\\TEX\\03_result\\exit001.png"		//画像ファイル8
#define	TEX_9_RESULT	"data\\TEX\\03_result\\cursor000.png"	//画像ファイル9
#define	TEX_10_RESULT	"data\\TEX\\03_result\\blackbase.png"	//画像ファイル10

//プロトタイプ宣言
void Init_Result(void);
void Uninit_Result(void);
void Update_Result(void);
void Draw_Result(void);
void Setcursor_MENU(void);
void Setcursor_RETRY_R(void);
void Setcursor_EXIT_R(void);
void Setcursor_Anim_R(void);

#endif