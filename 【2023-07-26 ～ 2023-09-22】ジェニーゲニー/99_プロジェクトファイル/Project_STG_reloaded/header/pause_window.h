//************************************************
//
//ポーズウィンドウ処理、ヘッダファイル[pause_window.h]
//Author：福田歩希
//
//************************************************
#ifndef _PAUSE_WINDOW_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _PAUSE_WINDOW_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"
#include "pause.h"

//マクロ定義

/*画像パス*/
#define	TEXTURE_PAUSE_WINDOW	"data\\TEX\\01_menu\\tutorial_window.png"
#define	TEXTURE_PAUSE_TEXT	"data\\TEX\\02_game\\pause.png"

#define AMOUNT_POLYGON_PAUSE_WINDOW	(2)	//ポリゴン数
#define AMOUNT_TEXTURE_PAUSE_WINDOW	(2)	//テクスチャ数

typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	float fSpanX;		//サイズ
	float fSpanY;		//サイズ
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//色
	float fLength;		//対角線
	float fAngle;		//角度
	float fSPD_X;
	float colA;
}PAUSE_WINDOW;

//プロトタイプ宣言
void Init_Pause_Window(void);
void Uninit_Pause_Window(void);
void Update_Pause_Window(void);
void Draw_Pause_Window(void);
void Setinfo_Pause_Window(void);

#endif