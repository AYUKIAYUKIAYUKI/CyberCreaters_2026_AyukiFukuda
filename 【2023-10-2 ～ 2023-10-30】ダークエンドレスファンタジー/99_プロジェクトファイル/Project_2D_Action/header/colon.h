//************************************************
//
//コロン処理、ヘッダファイル[logo_title.h]
//Author：福田歩希
//
//************************************************
#ifndef _COLON_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _COLON_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_COLON	"data\\TEX\\colon.png"

//コロン情報の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
}COLON;

//プロトタイプ宣言

/*生成*/
void Init_Colon(void);

/*破棄*/
void Uninit_Colon(void);

/*更新*/
void Update_Colon(void);

/*描画*/
void Draw_Colon(void);

/*コロンにデータを付与*/
void SetInfo_Colon(void);

/*コロンのバーテックスを更新*/
void Update_Pos_Colon(void);

/*コロンの情報を取得*/
COLON* GetInfo_Colon(void);

#endif