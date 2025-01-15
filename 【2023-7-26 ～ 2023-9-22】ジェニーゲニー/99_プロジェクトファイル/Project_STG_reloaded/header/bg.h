//************************************************
//
//背景処理、ヘッダファイル[bg.h]
//Author：福田歩希
//
//************************************************
#ifndef _BG_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BG_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス用*/
#define	TEXTURE_DEMO_BG	"data\\TEX\\02_game\\BG.png"

#define MOVE_SPD_TEX_BG	(0.0005f)	//テクスチャ系の移動速度

#define AMOUNT_POLYGON_BG	(1)	//ポリゴン数
#define AMOUNT_TEXTURE_BG	(1)	//読込みテクスチャ数

typedef struct
{
	float texL;
	float texR;
	float moveSPD;
}BG;

//プロトタイプ宣言
void Init_BG(void);
void Uninit_BG(void);
void Update_BG(void);
void Draw_BG(void);
void SetPos_Vtx_BG(void);

#endif