//************************************************
//
//リザルトテキスト処理、ヘッダファイル[logo_title.h]
//Author：福田歩希
//
//************************************************
#ifndef _TEXT_RESULT_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TEXT_RESULT_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_TEXT_RESULT	"data\\TEX\\now_score.png"

#define RADIUS_TEXT_RESULT_X	(850.0f)	//横半幅
#define RADIUS_TEXT_RESULT_Y	(100.0f)	//縦半幅

//リザルトテキスト情報の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
}TEXT_RESULT;

//プロトタイプ宣言

/*生成*/
void Init_Text_Result(void);

/*破棄*/
void Uninit_Text_Result(void);

/*更新*/
void Update_Text_Result(void);

/*描画*/
void Draw_Text_Result(void);

/*テキストにデータを付与*/
void SetInfo_Text_Result(void);

/*テキストのバーテックスを更新*/
void Update_Pos_Text_Result(void);

/*テキストの情報を取得*/
TEXT_RESULT* GetInfo_Text_Result(void);

#endif