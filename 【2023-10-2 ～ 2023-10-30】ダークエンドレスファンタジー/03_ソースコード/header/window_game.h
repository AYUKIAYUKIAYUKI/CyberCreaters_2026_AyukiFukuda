//************************************************
//
//ポーズウィンドウ処理、ヘッダファイル[window_game.h]
//Author：福田歩希
//
//************************************************
#ifndef _WINDOW_GAME_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _WINDOW_GAME_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_WHTITE_PAUSE	"data\\TEX\\white.png"
#define	TEXTURE_WINDOW_GAME	"data\\TEX\\window.png"
#define	TEXTURE_TEXT_PAUSE	"data\\TEX\\pause.png"

#define AMOUNT_POLYGON_WINDOW_GAME	(3)	//ポーズウィンドウのポリゴン最大数
#define AMOUNT_TEX_WINDOW_GAME	(3)	//ポーズウィンドウのテクスチャ総数

#define RADIUS_TEXT_PAUSE_X	(250.0f)	//ポーズテキストの横幅
#define RADIUS_TEXT_PAUSE_Y	(80.0f)	//ポーズテキストの縦幅

//ポーズウィンドウ情報の列挙型
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
}WINDOW_GAME;

//プロトタイプ宣言

/*生成*/
void Init_Window_Game(void);

/*破棄*/
void Uninit_Window_Game(void);

/*更新*/
void Update_Window_Game(void);

/*描画*/
void Draw_Window_Game(void);

/*ポーズウィンドウにデータを付与*/
void SetInfo_Window_Game(void);

/*ポーズウィンドウのバーテックスを更新*/
void Update_Pos_Window_Game(void);

/*ポーズウィンドウのデータを取得*/
WINDOW_GAME* GetInfo_Window_Game(void);

#endif