//************************************************
//
//メニューのテキスト表示処理、ヘッダファイル[text_mode.h]
//Author：福田歩希
//
//************************************************
#ifndef _TEXT_MODE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TEXT_MODE_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_CHOOSE_MODE	"data\\TEX\\01_menu\\choosingmode.png"
#define	TEXTURE_WINDOW_MODE	"data\\TEX\\01_menu\\window.png"

#define AMOUNT_POLYGON_TEXT_MODE	(2)	//ポリゴン数
#define AMOUNT_TEXTURE_TEXT_MODE	(2)	//読込みテクスチャ数

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
}TEXT_MODE;

//プロトタイプ宣言
void Init_Text_Mode(void);
void Uninit_Text_Mode(void);
void Update_Text_Mode(void);
void Draw_Text_Mode(void);
void Setinfo_Text_Mode(void);

#endif