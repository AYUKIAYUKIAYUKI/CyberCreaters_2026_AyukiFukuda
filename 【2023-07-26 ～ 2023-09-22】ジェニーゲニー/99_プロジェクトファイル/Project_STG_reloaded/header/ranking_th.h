//************************************************
//
//順位のやつ、ヘッダファイル[ranking_th.h]
//Author：福田歩希
//
//************************************************
#ifndef _RANKING_TH_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RANKING_TH_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"
#include "ranking.h"

//マクロ定義

/*画像パス*/
#define	TEXTURE_RANKING_1ST	"data\\TEX\\04_ranking\\1st.png"
#define	TEXTURE_RANKING_2ND	"data\\TEX\\04_ranking\\2nd.png"
#define	TEXTURE_RANKING_3RD	"data\\TEX\\04_ranking\\3rd.png"
#define	TEXTURE_RANKING_4TH	"data\\TEX\\04_ranking\\4th.png"
#define	TEXTURE_RANKING_5TH	"data\\TEX\\04_ranking\\5th.png"
#define	TEXTURE_RANKING_YOURS	"data\\TEX\\04_ranking\\yours.png"

#define AMOUNT_POLYGON_RANKING_TH	(6)	//ポリゴン数
#define AMOUNT_TEXTURE_RANKING_TH	(6)	//テクスチャ数

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
}RANKING_TH;

//プロトタイプ宣言
void Init_Ranking_TH(int nMode);
void Uninit_Ranking_TH(void);
void Update_Ranking_TH(void);
void Draw_Ranking_TH(void);
void Setinfo_Ranking_TH(int nMode);

#endif