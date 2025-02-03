//************************************************
//
//ブレイクスライドブロック、ヘッダファイル[breakblock.h]
//Author：福田歩希
//
//************************************************
#ifndef _BREAKBLOCK_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BREAKBLOCK_H_	//(二重インクルード防止、マクロ定義する)

#include <stdio.h>
#include "block.h"

//マクロ定義

/*ファイルパス系*/
#define	FILE_SET_BREAKBLOCK	"data\\csv\\BreakBlockInfo.csv"

#define AMOUNT_POLYGON_BREAKBLOCK	(64)	//スライドブロックの数

#define AMOUNT_DATA_BREAKBLOCK	(12)	//スライドブロック1つ当たりのデータ量

//ブロックの種類分け列挙型
typedef enum
{
	BREAKBLOCKSTYLE_SHROT_1 = 0,
	BREAKBLOCKSTYLE_SHROT_2,
	BREAKBLOCKSTYLE_MIDDLE_1,
	BREAKBLOCKSTYLE_MIDDLE_2,
	BREAKBLOCKSTYLE_TALL_1,
	BREAKBLOCKSTYLE_TALL_2,
	BREAKBLOCKSTYLE_MAX,
}BREAKBLOCKSTYLE;

//ブロックの状態分け
typedef enum
{
	BREAKBLOCKSTATE_BROKEN = 0,
	BREAKBLOCKSTATE_LIFE1,
	BREAKBLOCKSTATE_LIFE2,
	BREAKBLOCKSTATE_LIFE3,
	BREAKBLOCKSTATE_MAX,
}BREAKBLOCKSTATE;

//ブロック構造体
typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置情報
	float fHalfSpanX;	//横幅
	float fHalfSpanY;	//横幅
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//どんな色
	bool bUse;			//仕様判定
	int nCntSpawn;		//いつ出現するか
	int nLife;			//何発で壊れる？
	float fLength;		//対角線を格納
	float fAngle;		//対角線の角度を格納
}BREAKBLOCK;

//プロトタイプ宣言
void Init_BreakBlock(void);
void Uninit_BreakBlock(void);
void Update_BreakBlock(void);
void Draw_BreakBlock(void);
void Setinfo_BreakBlock(void);
void Hit_BreakBlock(int nCntBreakBlock, int nDamage);
BREAKBLOCK* Getinfo_BreakBlock(void);

#endif