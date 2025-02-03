//************************************************
//
//守護対象処理、ヘッダファイル[tower.h]
//Author：福田歩希
//
//************************************************
#ifndef _TOWER_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TOWER_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_TOWER	"data\\TEX\\tower.png"

#define AMOUNT_TEX_TOWER	(1)	//守護対象のテクスチャ総数

#define RADIUS_TOWER_X	(100.0f)	//横半幅
#define RADIUS_TOWER_Y	(150.0f)	//縦半幅

#define AMOUNT_MAX_LIFE_TOWER	(7)	//守護対象のライフ最大

#define SPD_CHANGE_TEX_TOWER	(3)	//アニメーション速度
#define AMOUNT_STYLE_TEX_TOWER	(11)	//アニメーション用
#define SPAN_CHANGE_TEX_TOWER	(0.09090f)	//アニメーション用

//守護対象の情報の構造型
typedef struct
{
	int nState;			//守護対象の状態
	D3DXVECTOR3 pos;	//疑似位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//回転
	D3DXCOLOR col;		//色
	int nCntTex;		//テクスチャ変更
	int nCntPattern;	//テクスチャ変更
	float fTexSpan[2];	//テクスチャ幅
	float fRadius[2];	//半径
	float fLength[2];	//対角線
	float fAngle[2];	//角度
	int nLife;			//ライフ
	int nCT;			//キャストタイム
}TOWER;

//プロトタイプ宣言

/*生成*/
void Init_Tower(void);

/*破棄*/
void Uninit_Tower(void);

/*更新*/
void Update_Tower(void);

/*描画*/
void Draw_Tower(void);

/*守護対象にデータを付与*/
void SetInfo_Tower(void);

/*守護対象のバーテックスを更新*/
void Update_Pos_Tower(void);

/*守護対象のバーテックスカラーを更新*/
void Update_Col_Tower(void);

/*テクスチャアニメーション処理*/
void Update_Tex_Tower(void);

/*守護対象のデータを取得*/
TOWER* GetInfo_Tower(void);

#endif