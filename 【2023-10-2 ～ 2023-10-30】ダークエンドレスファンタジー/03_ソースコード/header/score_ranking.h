//************************************************
//
//スコア(ランキング)処理、ヘッダファイル[score_ranking.h]
//Author：福田歩希
//
//************************************************
#ifndef _SCORE_RANKING_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _SCORE_RANKING_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス*/
#define	TEXTURE_SCORE_RANKING	"data\\TEX\\number.png"

#define AMOUNT_POLYGON_SCORE_RANKING	(16)	//ポリゴン数

#define SPAN_EACH_POLYGON_SCORE_RANKING	(30.0f)	//ポリゴンを並べる間隔
#define MOVE_SPAN_TEX_SCORE_RANKING	(0.1f)			//テクスチャ可動域

//スコアの分類
typedef enum
{
	SCORE_RANKING_HIGH = 0,
	SCORE_RANKING_LAST,
	SCORE_RANKING_STYLE_MAX
}SCORE_RANKING_STYLE;

//スコア表示用構造体
typedef struct
{
	int nStyle;
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動
	D3DXVECTOR3 rot;	//回転
	D3DXCOLOR col;		//色
	int nCntTex;		//テクスチャ変更
	int nCntPattern;	//テクスチャ変更
	float fTexSpan[2];	//テクスチャ幅
	float fRadius[2];	//半径
	float fLength[2];	//対角線
	float fAngle[2];	//角度
}SCORE_RANKING;

//プロトタイプ宣言

/*生成*/
void Init_Score_Ranking(void);

/*破棄*/
void Uninit_Score_Ranking(void);

/*更新*/
void Update_Score_Ranking(void);

/*描画*/
void Draw_Score_Ranking(void);

/*スコア表示用にデータを付与*/
void SetInfo_Score_Ranking(void);

/*過去のスコアを読み取る*/
void ReadInfo_Score_Ranking(void);

/*スコア表示用のバーテックスを更新*/
void Update_Pos_Score_Ranking(void);

/*スコア表示用のテクスチャを更新*/
void Update_Tex_Score_Ranking(void);

/*スコアからテクスチャ幅を計算*/
void Calc_Tex_Score_Ranking(void);

/*スコア表示用(らんきんぐ)のアドレスを取得*/
SCORE_RANKING* GetInfo_Score_Ranking(void);

#endif