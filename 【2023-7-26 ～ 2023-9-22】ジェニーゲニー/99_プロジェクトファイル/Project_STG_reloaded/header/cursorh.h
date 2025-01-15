//************************************************
//
//メニューのカーソル処理、ヘッダファイル[cursor.h]
//Author：福田歩希
//
//************************************************
#ifndef _CURSOR_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _CURSOR_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_CURSOR	"data\\TEX\\01_menu\\cursor.png"

#define AMOUNT_POLYGON_CURSOR	(1)	//ポリゴン数
#define AMOUNT_TEXTURE_CURSOR	(1)	//読込みテクスチャ数

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
	int nCntStop;		//止まる時間
	bool bTurn;			//戻る判定
}CURSOR;

//プロトタイプ宣言
void Init_Cursor(void);
void Uninit_Cursor(void);
void Update_Cursor(void);
void Draw_Cursor(void);
void Setinfo_Cursor(void);
void Animation_Cursor(void);
int* Getinfo_Choose(void);

#endif