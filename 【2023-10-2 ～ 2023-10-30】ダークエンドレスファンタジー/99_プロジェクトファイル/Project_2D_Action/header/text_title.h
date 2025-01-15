//************************************************
//
//タイトルテキスト処理、ヘッダファイル[text_title.h]
//Author：福田歩希
//
//************************************************
#ifndef _TEXT_TITLE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TEXT_TITLE_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_TEXT_TITLE_1	"data\\TEX\\start.png"
#define	TEXTURE_TEXT_TITLE_2	"data\\TEX\\ranking.png"
#define	TEXTURE_TEXT_TITLE_3	"data\\TEX\\end.png"

#define AMOUNT_POLYGON_TEXT_TITLE	(3)	//タイトルテキストのポリゴン最大数
#define AMOUNT_TEX_TEXT_TITLE	(3)	//タイトルテキストのテクスチャ総数

#define RADIUS_TEXT_TITLE_X	(250.0f)	//横半幅
#define RADIUS_TEXT_TITLE_Y	(60.0f)	//縦半幅

//タイトルテキスト情報の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
}TEXT_TITLE;

//プロトタイプ宣言

/*生成*/
void Init_Text_Title(void);

/*破棄*/
void Uninit_Text_Title(void);

/*更新*/
void Update_Text_Title(void);

/*描画*/
void Draw_Text_Title(void);

/*テキストにデータを付与*/
void SetInfo_Text_Title(void);

/*テキストのバーテックスを更新*/
void Update_Pos_Text_Title(void);

/*テキストのバーテックスカラーを更新*/
void Update_Col_Text_Title(void);

/*テキストの情報を取得*/
TEXT_TITLE* GetInfo_Text_Title(void);

#endif