//************************************************
//
//スコア処理、ヘッダファイル[score.h]
//Author：福田歩希
//
//************************************************
#ifndef _SCORE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _SCORE_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス*/
#define	TEXTURE_SCORE	"data\\TEX\\number.png"

#define AMOUNT_POLYGON_SCORE	(8)	//ポリゴン数

#define SPAN_EACH_POLYGON_SCORE	(30.0f)	//ポリゴンを並べる間隔
#define MOVE_SPAN_TEX_SCORE	(0.1f)			//テクスチャ可動域

#define AMOUNT_MAX_SCORE	(999999)	//スコア上限

//スコア用モード分け
typedef enum
{
	SCORE_TYPE_GAME = 0,
	SCORE_TYPE_RESULT,
	SCORE_TYPE_MAX,
}SCORE_TYPE;

//スコアの分類
typedef enum
{
	SCORE_NEW = 0,
	SCORE_OLD,
	SCORE_STYLE_MAX
}SCORE_STYLE;

//スコア表示用構造体
typedef struct
{
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
}SCORE;

//プロトタイプ宣言

/*生成*/
void Init_Score(int nMode);

/*破棄*/
void Uninit_Score(void);

/*更新*/
void Update_Score(void);

/*描画*/
void Draw_Score(void);

/*スコア表示用にデータを付与*/
void SetInfo_Score(int nMode);

/*スコア表示用のバーテックスを更新*/
void Update_Pos_Score(void);

/*スコア表示用のテクスチャを更新*/
void Update_Tex_Score(void);

/*スコアからテクスチャ幅を計算*/
void Calc_Tex_Score(void);

/*乱*/
void Animation_Score(void);

/*スコア表示用のアドレスを取得*/
SCORE* GetInfo_SCORE(void);

/*スコアのアドレスを取得*/
int* GetInfo_Score(void);

/*アニメーション期間*/
int* GetInfo_S_A_CT(void);

#endif