//************************************************
//
//守護対象ゲージ処理、ヘッダファイル[gauge_tower.h]
//Author：福田歩希
//
//************************************************
#ifndef _GAUGE_TOWER_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _GAUGE_TOWER_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_GAUGE_TOWER	"data\\TEX\\gage_life_f.png"
#define	TEXTURE_GAUGE_HEART	"data\\TEX\\heart.png"

#define AMOUNT_POLYGON_GAUGE_TOWER	(2)	//ライフゲージのポリゴン最大数
#define AMOUNT_TEX_GAUGE_TOWER	(2)	//ライフゲージのテクスチャ総数

#define RADIUS_GAUGE_TOWER_X	(200.0f)	//横半幅
#define RADIUS_GAUGE_TOWER_Y	(35.0f)	//縦半幅

#define RADIUS_GAUGE_HEART_X	(70.0f)	//横半幅
#define RADIUS_GAUGE_HEART_Y	(70.0f)	//縦半幅

#define SPAN_EACH_GAUGE_TOWER_X	(225.0f)	//ハートとゲージの位置ずれ
#define SPAN_EACH_GAUGE_TOWER_Y	(15.0f)	//ハートとゲージの位置ずれ

#define SPAN_CHANGE_TEX_GAUGE_TOWER	(0.125f)	//アニメーション用

//守護対象ゲージのパーツ分け
typedef enum
{
	GAUGE_TOWER_STYLE_GAUGE = 0,
	GAUGE_TOWER_STYLE_HEART,
	GAUGE_TOWER_STYLE_MAX,
}GAUGE_TOWER_STYLE;

//ライフゲージ情報の列挙型
typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	int nCntTex;		//テクスチャ変更
	float fTexSpan[2];	//テクスチャ幅
	float fRadius[2];	//半径
	float fLength[2];	//対角線
	float fAngle[2];	//角度
}GAUGE_TOWER;

//プロトタイプ宣言

/*生成*/
void Init_Gauge_Tower(void);

/*破棄*/
void Uninit_Gauge_Tower(void);

/*更新*/
void Update_Gauge_Tower(void);

/*描画*/
void Draw_Gauge_Tower(void);

/*守護対象ゲージにデータを付与*/
void SetInfo_Gauge_Tower(void);

/*守護対象ゲージのバーテックスを更新*/
void Update_Pos_Gauge_Tower(void);

/*守護対象ゲージのバーテックスカラーを更新*/
void Update_Col_Gauge_Tower(void);

/*守護対象ゲージのテクスチャアニメーション処理*/
void Update_Tex_Gauge_Tower(void);

/*守護対象ゲージのデータを取得*/
GAUGE_TOWER* GetInfo_Gauge_Tower(void);

#endif