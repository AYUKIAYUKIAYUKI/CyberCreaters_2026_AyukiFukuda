//************************************************
//
//チュートリアル、ヘッダファイル[tutorial.h]
//Author：福田歩希
//
//************************************************
#ifndef _TUTORIAL_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TUTORIAL_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス*/
#define	TEXTURE_EXPLAIN_TUTORIAL	"data\\TEX\\01_menu\\tutorial.png"

#define AMOUNT_POLYGON_TUTORIAL	(1)

typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//色
	float fLength;		//対角線
	float fAngle;		//角度
}TUTORIAL;

//プロトタイプ宣言
void Init_Tutorial(void);
void Uninit_Tutorial(void);
void Update_Tutorial(void);
void Draw_Tutorial(void);
void Setinfo_Tutorial(void);
bool* Getinfo_Tutorial(void);

#endif