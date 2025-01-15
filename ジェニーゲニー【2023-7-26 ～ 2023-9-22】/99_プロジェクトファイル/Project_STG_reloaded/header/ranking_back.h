//************************************************
//
//もどる、ヘッダファイル[ranking_back.h]
//Author：福田歩希
//
//************************************************
#ifndef _RANKING_BACK_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RANKING_BACK_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"
#include "ranking.h"

//マクロ定義

/*画像パス*/
#define	TEXTURE_RANKING_BACK	"data\\TEX\\04_ranking\\back.png"

#define AMOUNT_POLYGON_RANKING_BACK	(1)	//ポリゴン数
#define AMOUNT_TEXTURE_RANKING_BACK	(1)	//テクスチャ数

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
}RANKING_BACK;

//プロトタイプ宣言
void Init_Ranking_Back(void);
void Uninit_Ranking_Back(void);
void Update_Ranking_Back(void);
void Draw_Ranking_Back(void);
void Setinfo_Ranking_Back(void);

#endif