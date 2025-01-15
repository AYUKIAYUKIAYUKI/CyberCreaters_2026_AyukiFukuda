//************************************************
//
//スライドブロック、ヘッダファイル[slideblock.h]
//Author：福田歩希
//
//************************************************
#ifndef _SLIDEBLOCK_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _SLIDEBLOCK_H_	//(二重インクルード防止、マクロ定義する)

#include <stdio.h>
#include "block.h"

//マクロ定義

/*ファイルパス系*/
#define	FILE_SET_SLIDEBLOCK	"data\\csv\\SlideBlockInfo.csv"

#define AMOUNT_POLYGON_SLIDEBLOCK	(64)	//スライドブロックの数

#define AMOUNT_DATA_SLIDEBLOCK	(13)	//スライドブロック1つ当たりのデータ量

//ブロックの種類分け列挙型
typedef enum
{
	SLIDEBLOCKSTYLE_SHROT_1 = 0,
	SLIDEBLOCKSTYLE_SHROT_2,
	SLIDEBLOCKSTYLE_MIDDLE_1,
	SLIDEBLOCKSTYLE_MIDDLE_2,
	SLIDEBLOCKSTYLE_TALL_1,
	SLIDEBLOCKSTYLE_TALL_2,
	SLIDEBLOCKSTYLE_MAX,
}SLIDEBLOCKSTYLE;

//ブロック構造体
typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置情報
	float fHalfSpanX;	//横幅
	float fHalfSpanY;	//横幅
	D3DXVECTOR3 move;	//移動情報
	float fStop;		//スライド停止
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//どんな色
	float fColChange;	//華羅変
	bool bUse;			//仕様判定
	int nCntSpawn;		//いつ出現するか
	float fLength;		//対角線を格納
	float fAngle;		//対角線の角度を格納
}SLIDEBLOCK;

//プロトタイプ宣言
void Init_SlideBlock(void);
void Uninit_SlideBlock(void);
void Update_SlideBlock(void);
void Draw_SlideBlock(void);
void Setinfo_SlideBlock(void);
SLIDEBLOCK* Getinfo_SlideBlock(void);
void Disapper_SlideBlock(int nCntSlideBlock);

#endif