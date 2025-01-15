//************************************************
//
//ポーズテキスト処理、ヘッダファイル[text_game.h]
//Author：福田歩希
//
//************************************************
#ifndef _TEXT_GAME_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TEXT_GAME_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_TEXT_GAME_1	"data\\TEX\\continue.png"
#define	TEXTURE_TEXT_GAME_2	"data\\TEX\\retry.png"
#define	TEXTURE_TEXT_GAME_3	"data\\TEX\\retire.png"

#define AMOUNT_POLYGON_TEXT_GAME	(3)	//ポーズテキストのポリゴン最大数
#define AMOUNT_TEX_TEXT_GAME	(3)	//ポーズテキストのテクスチャ総数

#define RADIUS_TEXT_GAME_X	(225.0f)	//横半幅
#define RADIUS_TEXT_GAME_Y	(60.0f)	//縦半幅

//ポーズテキスト情報の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
}TEXT_GAME;

//プロトタイプ宣言

/*生成*/
void Init_Text_Game(void);

/*破棄*/
void Uninit_Text_Game(void);

/*更新*/
void Update_Text_Game(void);

/*描画*/
void Draw_Text_Game(void);

/*テキストにデータを付与*/
void SetInfo_Text_Game(void);

/*テキストのバーテックスを更新*/
void Update_Pos_Text_Game(void);

/*テキストのバーテックスカラーを更新*/
void Update_Col_Text_Game(void);

/*テキストの情報を取得*/
TEXT_GAME* GetInfo_Text_Game(void);

#endif