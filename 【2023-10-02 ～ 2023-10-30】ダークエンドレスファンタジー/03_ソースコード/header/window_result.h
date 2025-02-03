//************************************************
//
//ウィンドウリザルト処理、ヘッダファイル[window_result.h]
//Author：福田歩希
//
//************************************************
#ifndef _WINDOW_RESULT_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _WINDOW_RESULT_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_WINDOW_RESULT1	"data\\TEX\\success.png"
#define	TEXTURE_WINDOW_RESULT2	"data\\TEX\\fail.png"

#define AMOUNT_TEX_WINDOW_RESULT	(2)	//テクスチャ数

#define RADIUS_WINDOW_RESULT_X	(600.0f)	//横半幅
#define RADIUS_WINDOW_RESULT_Y	(200.0f)	//縦半幅

//テスト情報の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength[2];	//対角線
	float fAngle[2];	//角度
}WINDOW_RESULT;

//プロトタイプ宣言

/*生成*/
void Init_Window_Result(void);

/*破棄*/
void Uninit_Window_Result(void);

/*更新*/
void Update_Window_Result(void);

/*描画*/
void Draw_Window_Result(void);

/*ウィンドウにデータを付与*/
void SetInfo_Window_Result(void);

/*ウィンドウのバーテックスを更新*/
void Update_Pos_Window_Result(void);

/*ウィンドウのデータを取得*/
WINDOW_RESULT* GetInfo_Window_Result(void);

#endif