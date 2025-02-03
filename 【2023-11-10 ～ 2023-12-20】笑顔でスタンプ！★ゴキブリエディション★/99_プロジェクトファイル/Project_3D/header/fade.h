//************************************************
//
//フェード処理、ヘッダファイル[fade.h]
//Author：福田歩希
//
//************************************************
#ifndef _FADE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _FADE_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

/*画像パス系*/
#define	TEXTURE_FADE	"data\\TEX\\black.png"

#define RADIUS_FADE_X	(990.0f)	//横半幅
#define RADIUS_FADE_Y	(540.0f)	//縦半幅

#define SPD_CHANGE_COL_FADE (0.05f)	//フェード速度

//フェード情報の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
	bool bFadeIn;
	bool bFadeOut;
}FADE;

//プロトタイプ宣言
void InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetInfoFade(void);
void UpdatePosFade(void);
void UpdateColFade(void);
FADE* GetInfoFade(void);

#endif