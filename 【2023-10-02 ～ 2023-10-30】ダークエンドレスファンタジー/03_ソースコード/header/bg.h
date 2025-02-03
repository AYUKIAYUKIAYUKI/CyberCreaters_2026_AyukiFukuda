//************************************************
//
//背景処理、ヘッダファイル[bg.h]
//Author：福田歩希
//
//************************************************
#ifndef _BG_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BG_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_BG_1	"data\\TEX\\BG_0.png"
#define	TEXTURE_BG_2	"data\\TEX\\BG_1.png"
#define	TEXTURE_BG_3	"data\\TEX\\BG_2.png"
#define	TEXTURE_BG_4	"data\\TEX\\BG_3.png"
#define	TEXTURE_BG_5	"data\\TEX\\BG_4.png"
#define	TEXTURE_BG_6	"data\\TEX\\BG_5.png"
#define	TEXTURE_BG_7	"data\\TEX\\BG_6.png"
#define	TEXTURE_BG_8	"data\\TEX\\BG_7.png"
#define	TEXTURE_BG_9	"data\\TEX\\BG_8.png"
#define	TEXTURE_BG_10	"data\\TEX\\BG_EX.png"

#define AMOUNT_POLYGON_BG	(9)	//背景のポリゴン最大数
#define AMOUNT_TEX_BG	(9)	//背景のテクスチャ総数

#define RADIUS_BG_X	(1080.0f)	//横半幅
#define RADIUS_BG_Y	(540.0f)	//縦半幅

#define RADIUS_CLOUD_X	(100.0f)	//横半幅
#define RADIUS_CLOUD_Y	(75.0f)	//縦半幅

//背景用モード分け
typedef enum
{
	BG_TYPE_TITLE = 0,
	BG_TYPE_GAME,
	BG_TYPE_MAX,
}BG_TYPE;

//背景情報の列挙型
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
	int nLayer;			//
	float fTex[2];		//
}BG;

//プロトタイプ宣言

/*生成*/
void Init_BG(int nMode);

/*破棄*/
void Uninit_BG(void);

/*更新*/
void Update_BG(void);

/*描画*/
void Draw_BG(void);

/*背景にデータを付与*/
void SetInfo_BG(void);

/*背景のバーテックスを更新*/
void Update_Pos_BG(void);

/*背景のバーテックスカラーを更新*/
void Update_Col_BG(void);

/*背景のテクスチャアニメーション処理*/
void Update_Tex_BG(void);

/*背景のデータを取得*/
BG* GetInfo_BG(void);

#endif