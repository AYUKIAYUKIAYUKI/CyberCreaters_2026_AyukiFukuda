//************************************************
//
//チュートリアルフェード処理、ヘッダファイル[tutorial_fade.h]
//Author：福田歩希
//
//************************************************
#ifndef _TUTORIAL_FADE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TUTORIAL_FADE_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_BLACK_TUTORIAL_FADE	"data\\TEX\\01_menu\\blackbase.png"

#define AMOUNT_POLYGON_TUTORIAL_FADE	(1)	//ポリゴン数
#define AMOUNT_TEXTURE_TUTORIAL_FADE	(1)	//読込みテクスチャ数

typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//色
	float fLength;		//対角線
	float fAngle;		//角度
}TUTORIAL_FADE;

//プロトタイプ宣言
void Init_Tutorial_Fade(void);
void Uninit_Tutorial_Fade(void);
void Update_Tutorial_Fade(void);
void Draw_Tutorial_Fade(void);
void Setinfo_Tutorial_Fade(void);
float* Getinfo_Tutorial_Fade(void);

#endif