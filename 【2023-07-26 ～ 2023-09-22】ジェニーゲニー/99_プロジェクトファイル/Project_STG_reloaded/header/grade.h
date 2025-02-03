//************************************************
//
//リザルトの順位表示処理、ヘッダファイル[grade.h]
//Author：福田歩希
//
//************************************************
#ifndef _GRADE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _GRADE_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_GRADE_1	"data\\TEX\\01_menu\\"

#define AMOUNT_POLYGON_GRADE	(5)	//ポリゴン数
#define AMOUNT_TEXTURE_GRADE	(1)	//読込みテクスチャ数

typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	float fSpanX;		//サイズ
	float fSpanY;		//サイズ
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//色
}GRADE;

//プロトタイプ宣言
void Init_Grade(void);
void Uninit_Grade(void);
void Update_Grade(void);
void Draw_Grade(void);
void Setinfo_Grade(void);

#endif