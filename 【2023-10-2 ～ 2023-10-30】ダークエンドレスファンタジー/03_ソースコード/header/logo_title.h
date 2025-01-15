//************************************************
//
//タイトルロゴ処理、ヘッダファイル[logo_title.h]
//Author：福田歩希
//
//************************************************
#ifndef _LOGO_TITLE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _LOGO_TITLE_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_LOGO_TITLE	"data\\TEX\\logo_title.png"

#define RADIUS_LOGO_TITLE_X	(850.0f)	//横半幅
#define RADIUS_LOGO_TITLE_Y	(100.0f)	//縦半幅

//タイトルロゴ情報の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
}LOGO_TITLE;

//プロトタイプ宣言

/*生成*/
void Init_Logo_Title(void);

/*破棄*/
void Uninit_Logo_Title(void);

/*更新*/
void Update_Logo_Title(void);

/*描画*/
void Draw_Logo_Title(void);

/*ロゴにデータを付与*/
void SetInfo_Logo_Title(void);

/*ロゴのバーテックスを更新*/
void Update_Pos_Logo_Title(void);

/*ロゴの情報を取得*/
LOGO_TITLE* GetInfo_Logo_Title(void);

#endif