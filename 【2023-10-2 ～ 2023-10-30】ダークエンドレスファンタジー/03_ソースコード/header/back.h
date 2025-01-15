//************************************************
//
//UIの後ろの処理、ヘッダファイル[back.h]
//Author：福田歩希
//
//************************************************
#ifndef _BACK_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BACK_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_BACK	"data\\TEX\\black.png"

#define AMOUNT_POLYGON_BACK	(2)	//ポリゴン数

//UIの後ろの情報の列挙型
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
}BACK;

//プロトタイプ宣言

/*生成*/
void Init_Back(void);

/*破棄*/
void Uninit_Back(void);

/*更新*/
void Update_Back(void);

/*描画*/
void Draw_Back(void);

/*ポーズウィンドウにデータを付与*/
void SetInfo_Back(void);

/*ポーズウィンドウのバーテックスを更新*/
void Update_Pos_Back(void);

/*ポーズウィンドウのデータを取得*/
BACK* GetInfo_Back(void);

#endif