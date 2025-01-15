//************************************************
//
//チュートリアル催促モード選択、ヘッダファイル[tutorial_select.h]
//Author：福田歩希
//
//************************************************
#ifndef _TUTORIAL_SELECT_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TUTORIAL_SELECT_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_TUTORIAL_SELECT_YES	"data\\TEX\\01_menu\\yes.png"
#define	TEXTURE_TUTORIAL_SELECT_NO	"data\\TEX\\01_menu\\no.png"

#define AMOUNT_POLYGON_TUTORIAL_SELECT	(2)	//ポリゴン数
#define AMOUNT_TEXTURE_TUTORIAL_SELECT	(2)	//読込みテクスチャ数

typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	float fSpanX;		//サイズ
	float fSpanY;		//サイズ
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//色
	float colA;
}TUTORIAL_SELECT;

//プロトタイプ宣言
void Init_Tutorial_Select(void);
void Uninit_Tutorial_Select(void);
void Update_Tutorial_Select(void);
void Draw_Tutorial_Select(void);
void Setinfo_Tutorial_Select(void);

#endif