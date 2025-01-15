//************************************************
//
//タイトルの線処理、ヘッダファイル[Line_title.h]
//Author：福田歩希
//
//************************************************
#ifndef _LINE_TITLE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _LINE_TITLE_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

#define AMOUNT_POLYGON_LINE_TITLE	(1024)	//ポリゴン数

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
}LINE_TITLE;

//プロトタイプ宣言
void Init_Line_title(void);
void Uninit_Line_title(void);
void Update_Line_title(void);
void Draw_Line_title(void);
void Setinfo_Line_title(void);

#endif