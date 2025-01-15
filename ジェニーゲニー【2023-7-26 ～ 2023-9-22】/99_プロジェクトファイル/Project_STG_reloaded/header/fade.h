//************************************************
//
//メニューフェード処理、ヘッダファイル[fade.h]
//Author：福田歩希
//
//************************************************
#ifndef _FADE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _FADE_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_BLACK_FADE_MENU	"data\\TEX\\01_menu\\blackbase.png"

#define AMOUNT_POLYGON_FADE_MENU	(1)	//ポリゴン数
#define AMOUNT_TEXTURE_FADE_MENU	(1)	//読込みテクスチャ数

typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//色
	float fLength;		//対角線
	float fAngle;		//角度
}FADE_MENU_OBJECT;

//プロトタイプ宣言
void Init_Fade_Menu(void);
void Uninit_Fade_Menu(void);
void Update_Fade_Menu(void);
void Draw_Fade_Menu(void);
void Setinfo_Fade_Menu(void);
float* Getinfo_Fade_Menu(void);

#endif