//************************************************
//
//ランキングテキスト処理、ヘッダファイル[text_title.h]
//Author：福田歩希
//
//************************************************
#ifndef _TEXT_RANKING_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TEXT_RANKING_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_TEXT_RANKING_1	"data\\TEX\\high_score.png"
#define	TEXTURE_TEXT_RANKING_2	"data\\TEX\\last_score.png"

#define AMOUNT_POLYGON_TEXT_RANKING	(2)	//ランキングテキストのポリゴン最大数
#define AMOUNT_TEX_TEXT_RANKING	(2)	//ランキングテキストのテクスチャ総数

#define RADIUS_TEXT_RANKING_X	(450.0f)	//横半幅
#define RADIUS_TEXT_RANKING_Y	(100.0f)	//縦半幅

//ランキングテキスト情報の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
}TEXT_RANKING;

//プロトタイプ宣言

/*生成*/
void Init_Text_Ranking(void);

/*破棄*/
void Uninit_Text_Ranking(void);

/*更新*/
void Update_Text_Ranking(void);

/*描画*/
void Draw_Text_Ranking(void);

/*テキストにデータを付与*/
void SetInfo_Text_Ranking(void);

/*テキストのバーテックスを更新*/
void Update_Pos_Text_Ranking(void);

/*テキストの情報を取得*/
TEXT_RANKING* GetInfo_Text_Ranking(void);

#endif