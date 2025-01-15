//************************************************
//
//メニューのモード選択処理、ヘッダファイル[select_mode.h]
//Author：福田歩希
//
//************************************************
#ifndef _SELECT_MODE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _SELECT_MODE_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_MODE_GAME	"data\\TEX\\01_menu\\gamemode.png"
#define	TEXTURE_MODE_RANK	"data\\TEX\\01_menu\\rankingmode.png"

#define AMOUNT_POLYGON_SELECT_MODE	(2)	//ポリゴン数
#define AMOUNT_TEXTURE_SELECT_MODE	(2)	//読込みテクスチャ数

typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	float fSpanX;		//サイズ
	float fSpanY;		//サイズ
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//色
}SELECT_MODE;

//プロトタイプ宣言
void Init_Select_Mode(void);
void Uninit_Select_Mode(void);
void Update_Select_Mode(void);
void Draw_Select_Mode(void);
void Setinfo_Select_Mode(void);

#endif