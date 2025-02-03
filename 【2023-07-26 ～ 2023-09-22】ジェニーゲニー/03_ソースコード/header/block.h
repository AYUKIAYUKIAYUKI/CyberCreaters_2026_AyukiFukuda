//************************************************
//
//ブロック、ヘッダファイル[block.h]
//Author：福田歩希
//
//************************************************
#ifndef _BLOCK_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BLOCK_H_	//(二重インクルード防止、マクロ定義する)

#include <stdio.h>

//マクロ定義

/*画像パス系*/
#define	TEXTURE_SHROT_1_BLOCK	"data\\TEX\\02_game\\block_short000.png"
#define	TEXTURE_SHROT_2_BLOCK	"data\\TEX\\02_game\\block_short001.png"
#define	TEXTURE_MIDDLE_1_BLOCK	"data\\TEX\\02_game\\block_MIDDLE000.png"
#define	TEXTURE_MIDDLE_2_BLOCK	"data\\TEX\\02_game\\block_MIDDLE001.png"
#define	TEXTURE_TALL_1_BLOCK	"data\\TEX\\02_game\\block_tall000.png"
#define	TEXTURE_TALL_2_BLOCK	"data\\TEX\\02_game\\block_tall001.png"

/*ファイルパス系*/
#define	FILE_SET_BLOCK	"data\\csv\\BlockInfo.csv"

#define AMOUNT_POLYGON_BLOCK	(64)	//ブロックの数
#define AMOUNT_TEXTURE_BLOCK	(6)		//読込みテクスチャ数

#define AMOUNT_DATA_BLOCK	(11)	//ブロック1つ当たりのデータ量

//ブロックの種類分け列挙型
typedef enum
{
	BLOCKSTYLE_SHROT_1 = 0,
	BLOCKSTYLE_SHROT_2,
	BLOCKSTYLE_MIDDLE_1,
	BLOCKSTYLE_MIDDLE_2,
	BLOCKSTYLE_TALL_1,
	BLOCKSTYLE_TALL_2,
	BLOCKSTYLE_MAX,
}BLOCKSTYLE;

//ブロック構造体
typedef struct
{
	int nStyle;			//ブロックの種類
	D3DXVECTOR3 pos;	//ブロックの位置情報を格納
	float fHalfSpanX;	//ブロックの横幅
	float fHalfSpanY;	//ブロックの横幅
	D3DXVECTOR3 move;	//ブロックの移動情報を格納
	D3DXVECTOR3 rot;	//ブロックの向き情報を格納
	bool bUse;			//仕様判定
	int nCntSpawn;		//いつ出現するか
	float fLength;		//対角線を格納
	float fAngle;		//対角線の角度を格納
}BLOCK;

//プロトタイプ宣言
void Init_Block(void);
void Uninit_Block(void);
void Update_Block(void);
void Draw_Block(void);
void Setinfo_Block(void);
BLOCK* Getinfo_Block(void);

#endif