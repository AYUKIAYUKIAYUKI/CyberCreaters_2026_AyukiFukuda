//************************************************
//
//ランキングに黒棒を出す、ヘッダファイル[ranking_black.h]
//Author：福田歩希
//
//************************************************
#ifndef _RANKING_BLACK_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RANKING_BLACK_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"
#include "ranking.h"

//マクロ定義

/*画像パス*/
#define	TEXTURE_RANKING_BLACK	"data\\TEX\\01_menu\\blackbase.png"

#define AMOUNT_POLYGON_RANKING_BLACK	(6)	//ポリゴン数
#define AMOUNT_TEXTURE_RANKING_BLACK	(1)	//テクスチャ数

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
}RANKING_BLACK;

//プロトタイプ宣言
void Init_Ranking_Black(int nMode);
void Uninit_Ranking_Black(void);
void Update_Ranking_Black(void);
void Draw_Ranking_Black(void);
void Setinfo_Ranking_Black(int nmode);

#endif