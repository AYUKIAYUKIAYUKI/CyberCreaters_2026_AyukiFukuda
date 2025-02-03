//************************************************
//
//ポーズフェード処理、ヘッダファイル[pause_fade.h]
//Author：福田歩希
//
//************************************************
#ifndef _PAUSE_FADE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _PAUSE_FADE_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_BLACK_PAUSE_FADE	"data\\TEX\\01_menu\\blackbase.png"

#define AMOUNT_POLYGON_PAUSE_FADE	(1)	//ポリゴン数
#define AMOUNT_TEXTURE_PAUSE_FADE	(1)	//読込みテクスチャ数

typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//色
	float fLength;		//対角線
	float fAngle;		//角度
}PAUSE_FADE;

//プロトタイプ宣言
void Init_Pause_Fade(void);
void Uninit_Pause_Fade(void);
void Update_Pause_Fade(void);
void Draw_Pause_Fade(void);
void Setinfo_Pause_Fade(void);
float* Getinfo_Pause_Fade(void);

#endif