//************************************************
//
//ポーズ画面モード選択、ヘッダファイル[pause_select.h]
//Author：福田歩希
//
//************************************************
#ifndef _PAUSE_SELECT_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _PAUSE_SELECT_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_PAUSE_CONTINUE	"data\\TEX\\02_game\\continue.png"
#define	TEXTURE_PAUSE_RETRY	"data\\TEX\\02_game\\retry.png"
#define	TEXTURE_PAUSE_MENU	"data\\TEX\\02_game\\menu.png"
#define	TEXTURE_PAUSE_TITLE	"data\\TEX\\02_game\\title.png"

#define AMOUNT_POLYGON_PAUSE_SELECT	(4)	//ポリゴン数
#define AMOUNT_TEXTURE_PAUSE_SELECT	(4)	//読込みテクスチャ数

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
}PAUSE_SELECT;

//プロトタイプ宣言
void Init_Pause_Select(void);
void Uninit_Pause_Select(void);
void Update_Pause_Select(void);
void Draw_Pause_Select(void);
void Setinfo_Pause_Select(void);

#endif