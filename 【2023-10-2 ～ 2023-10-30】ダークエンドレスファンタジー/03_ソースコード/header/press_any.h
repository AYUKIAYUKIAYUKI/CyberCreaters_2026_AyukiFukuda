//************************************************
//
//催促処理、ヘッダファイル[logo_title.h]
//Author：福田歩希
//
//************************************************
#ifndef _PRESS_ANY_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _PRESS_ANY_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_PRESS_ANY_MENU	"data\\TEX\\startgame.png"
#define	TEXTURE_PRESS_ANY_RESULT	"data\\TEX\\endgame.png"

#define AMOUNT_TEX_PRESS_ANY	(2)	//テクスチャ数

#define RADIUS_PRESS_ANY_X	(850.0f)	//横半幅
#define RADIUS_PRESS_ANY_Y	(100.0f)	//縦半幅

//催促の分類
typedef enum
{
	PRESS_TYPE_MENU = 0,
	PRESS_TYPE_RESULT,
	PRESS_TYPE_MAX,
}PRESS_ANY_TYPE;

//催促情報の構造体
typedef struct
{
	int nType;			//分類
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
}PRESS_ANY;

//プロトタイプ宣言

/*生成*/
void Init_Press_Any(int nMode);

/*破棄*/
void Uninit_Press_Any(void);

/*更新*/
void Update_Press_Any(void);

/*描画*/
void Draw_Press_Any(void);

/*催促にデータを付与*/
void SetInfo_Press_Any(void);

/*催促のバーテックスを更新*/
void Update_Pos_Press_Any(void);

/*催促のバーテックスカラーを更新*/
void Update_Col_Press_Any(void);

/*催促の情報を取得*/
PRESS_ANY* GetInfo_Press_Any(void);

#endif