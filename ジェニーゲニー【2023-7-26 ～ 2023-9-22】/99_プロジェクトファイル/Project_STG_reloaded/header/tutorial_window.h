//************************************************
//
//チュートリアル催促ウィンドウ処理、ヘッダファイル[tutorial_window.h]
//Author：福田歩希
//
//************************************************
#ifndef _TUTORIAL_WINDOW_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TUTORIAL_WINDOW_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"
#include "menu.h"

//マクロ定義

/*画像パス*/
#define	TEXTURE_BLACK_EX	"data\\TEX\\01_menu\\blackbase.png"
#define	TEXTURE_TUTORIAL_WINDOW	"data\\TEX\\01_menu\\tutorial_window.png"
#define	TEXTURE_TUTORIAL_TEXT	"data\\TEX\\01_menu\\wouldu.png"

#define AMOUNT_POLYGON_TUTORIAL_WINDOW	(3)	//ポリゴン数
#define AMOUNT_TEXTURE_TUTORIAL_WINDOW	(3)	//テクスチャ数

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
}TUTORIAL_WINDOW;

//プロトタイプ宣言
void Init_Tutorial_Window(void);
void Uninit_Tutorial_Window(void);
void Update_Tutorial_Window(void);
void Draw_Tutorial_Window(void);
void Setinfo_Tutorial_Window(void);

#endif