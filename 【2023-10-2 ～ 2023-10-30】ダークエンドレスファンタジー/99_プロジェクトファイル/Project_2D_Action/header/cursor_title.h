//************************************************
//
//タイトルカーソル処理、ヘッダファイル[cursor_title.h]
//Author：福田歩希
//
//************************************************
#ifndef _CURSOR_TITLE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _CURSOR_TITLE_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_CURSOR_TITLE_1	"data\\TEX\\dain.png"

#define RADIUS_CURSOR_TITLE_X	(50.0f)	//横半幅
#define RADIUS_CURSOR_TITLE_Y	(50.0f)	//縦半幅

//タイトルカーソル情報の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
}CURSOR_TITLE;

//プロトタイプ宣言

/*生成*/
void Init_Cursor_Title(void);

/*破棄*/
void Uninit_Cursor_Title(void);

/*更新*/
void Update_Cursor_Title(void);

/*描画*/
void Draw_Cursor_Title(void);

/*カーソルにデータを付与*/
void SetInfo_Cursor_Title(void);

/*カーソルのバーテックスを更新*/
void Update_Pos_Cursor_Title(void);

/*カーソルの情報を取得*/
CURSOR_TITLE* GetInfo_Cursor_Title(void);

#endif