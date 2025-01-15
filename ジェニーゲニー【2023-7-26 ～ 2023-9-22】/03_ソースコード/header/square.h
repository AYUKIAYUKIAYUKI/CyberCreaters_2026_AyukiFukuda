//************************************************
//
//メニューの四角処理、ヘッダファイル[square.h]
//Author：福田歩希
//
//************************************************
#ifndef _SQUARE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _SQUARE_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_SUQUARE_SMALL	"data\\TEX\\01_menu\\square000.png"
#define	TEXTURE_SUQUARE_MIDDLE	"data\\TEX\\01_menu\\square001.png"

#define AMOUNT_POLYGON_SQUARE	(16)	//ポリゴン数
#define AMOUNT_TEXTURE_SQUARE	(2)		//読込みテクスチャ数

#define HALFSPAN_SMALL_SQUARE	(100.0f)
#define HALFSPAN_MIDDLE_SQUARE	(200.0f)

typedef struct
{
	int nStyle;			//種類
	int nRute;			//軌道
	D3DXVECTOR3 pos;	//位置
	float fSpan;		//サイズ
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//色
	int nCntSpawn;		//出現タイミング
}SQUARE;

//プロトタイプ宣言
void Init_Square(void);
void Uninit_Square(void);
void Update_Square(void);
void Draw_Square(void);
void Setinfo_Square(void);
void Disappear_Square(int nCnt);

#endif