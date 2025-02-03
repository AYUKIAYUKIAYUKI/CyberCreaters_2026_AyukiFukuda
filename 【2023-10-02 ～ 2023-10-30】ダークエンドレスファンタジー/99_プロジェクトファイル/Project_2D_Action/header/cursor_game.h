//************************************************
//
//ポーズカーソル処理、ヘッダファイル[cursor_game.h]
//Author：福田歩希
//
//************************************************
#ifndef _CURSOR_GAME_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _CURSOR_GAME_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_CURSOR_GAME_1	"data\\TEX\\dain.png"

#define RADIUS_CURSOR_GAME_X	(50.0f)	//横半幅
#define RADIUS_CURSOR_GAME_Y	(50.0f)	//縦半幅

//ポーズカーソル情報の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
}CURSOR_GAME;

//プロトタイプ宣言

/*生成*/
void Init_Cursor_Game(void);

/*破棄*/
void Uninit_Cursor_Game(void);

/*更新*/
void Update_Cursor_Game(void);

/*描画*/
void Draw_Cursor_Game(void);

/*カーソルにデータを付与*/
void SetInfo_Cursor_Game(void);

/*カーソルのバーテックスを更新*/
void Update_Pos_Cursor_Game(void);

/*カーソルの情報を取得*/
CURSOR_GAME* GetInfo_Cursor_Game(void);

#endif