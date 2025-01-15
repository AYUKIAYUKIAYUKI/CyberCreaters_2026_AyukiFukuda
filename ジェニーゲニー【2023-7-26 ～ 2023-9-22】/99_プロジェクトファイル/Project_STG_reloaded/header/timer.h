//************************************************
//
//制限時間処理、ヘッダファイル[timer.h]
//Author：福田歩希
//
//************************************************
#ifndef _TIMER_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TIMER_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス*/
#define	TEXTURE_BLACK_TIMER	"data\\TEX\\02_game\\blackbase.png"
#define	TEXTURE_NUMBER_TIMER	"data\\TEX\\02_game\\number001.png"
#define TEXTURE_NUMBER_SUB_TIMER	"data\\TEX\\02_game\\number_sub000.png"
#define TEXTURE_CLOCK_TIMER	"data\\TEX\\02_game\\timer000.png"

#define AMOUNT_POLYGON_TIMER	(10)	//ポリゴン数
#define AMOUNT_TEXTURE_TIMER	(4)		//読込みテクスチャ数

#define AMOUNT_USING_POLYGON_NUMBER_TIMER	(6)	//数字に使ってるポリゴン数
#define AMOUNT_USING_POLYGON_SYMBOL_TIMER	(2)	//記号に使ってるポリゴン数

#define TEX_U_RIGHT_TIMER	(0.1f)	//U座標の右用

#define DISTANCESPAN_POLYGON_TIMER	(30.0f)		//数字ポリゴンを並べる間隔
#define MORE_DISTANCESPAN_POLYGON_TIMER	(20.0f)	//さらに間隔調整

#define DISTANCESPAN_POLYGON_SYMBOL_TIMER	(82.5f)	//記号のポリゴン間隔

#define MOVE_SPAN_TEX_TIMER	(0.1f)	//テクスチャ可動域

#define REMAIN_TIMER	(95)			//ゲームの残り時間
#define AMOUNT_CNT_MAX_TIMER	(60)	//1秒減らすのに必要なカウント(フレーム)数
#define INVERSION_TIMER	(44)			//反転にかかる時間
#define REINVERSION_TIMER	(73)		//再反転にかかる時間

//プロトタイプ宣言
void Init_Timer(void);
void Uninit_Timer(void);
void Update_Timer(void);
void Draw_Timer(void);
void SetPos_Vtx_Timer(void);
int* Getinfo_Timer(void);
bool* Getinfo_Inversion_Timer(void);
bool* Getinfo_ReInversion_Timer(void);

#endif