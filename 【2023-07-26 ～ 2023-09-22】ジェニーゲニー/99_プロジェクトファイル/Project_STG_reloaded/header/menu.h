//************************************************
//
//メニュー表示処理、ヘッダファイル[menu.h]
//Author：福田歩希
//
//************************************************
#ifndef _MENU_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _MENU_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_WHITE_MENU	"data\\TEX\\01_menu\\whitebase.png"

#define AMOUNT_POLYGON_MENU	(1)	//ポリゴン数
#define AMOUNT_TEXTURE_MENU	(1)	//読込みテクスチャ数

typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//色
	float fLength;		//対角線
	float fAngle;		//角度
}MENU_OBJECT;

//プロトタイプ宣言
void Init_Menu(void);
void Uninit_Menu(void);
void Update_Menu(void);
void Draw_Menu(void);
void Setinfo_Menu(void);
bool* Getinfo_Tutorial_Menu(void);
bool* Getinfo_Menu(void);

#endif