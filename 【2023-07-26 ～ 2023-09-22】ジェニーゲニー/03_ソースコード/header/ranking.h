//************************************************
//
//ランキング、ヘッダファイル[ranking.h]
//Author：福田歩希
//
//************************************************
#ifndef _RANKING_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RANKING_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

/*画像パス*/
#define	TEXTURE_RANKING_BG	"data\\TEX\\04_ranking\\BG_demo000.png"

#define AMOUNT_POLYGON_RANKING	(1)	//ポリゴン数
#define AMOUNT_TEXTURE_RANKING	(1)	//テクスチャ数

typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//色
	float fLength;		//対角線
	float fAngle;		//角度
}RANKING;

//プロトタイプ宣言
void Init_Ranking(int nMode);
void Uninit_Ranking(void);
void Update_Ranking(void);
void Draw_Ranking(void);
void Setinfo_Ranking(void);
bool* Getinfo_Ranking(void);

#endif