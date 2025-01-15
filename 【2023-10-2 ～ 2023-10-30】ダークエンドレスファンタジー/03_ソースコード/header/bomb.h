//************************************************
//
//ボム処理、ヘッダファイル[bomb.h]
//Author：福田歩希
//
//************************************************
#ifndef _BOMB_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BOMB_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_BOMB_1	"data\\TEX\\epic01.png"
#define	TEXTURE_BOMB_2	"data\\TEX\\epic02.png"

#define AMOUNT_POLYGON_BOMB	(1)	//タイトルボムのポリゴン最大数
#define AMOUNT_TEX_BOMB	(2)	//タイトルボムのテクスチャ総数

#define SPAN_CHANGE_TEX_BOMB (0.14285f)
#define SPAN_CHANGE_TEX_EXPLOSION (0.125f)

typedef enum
{
	BOMB_IDLE = 0,
	BOMB_EXPLOSION,
	BOMB_STATE_MAX,
}BOMB_STATE;

//タイトルボム情報の構造体
typedef struct
{
	bool bUse;			//出現判定
	int nState;			//BOMBの状態
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 oldpos;	//前の位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//回転
	D3DXCOLOR col;		//色
	int LR;				//向き
	int nCntTex;		//テクスチャ変更
	int nCntPattern;	//テクスチャ変更
	float fTexSpan[2];	//テクスチャ幅
	float fTexSpanY[2];	//テクスチャ幅
	float fRadius[2];	//半径
	float fLength[2];	//対角線
	float fAngle[2];	//角度
	float nCT;			//キャスト
	float nCharge;		//再使用まで
}BOMB;

//Bボックス情報の構造型
typedef struct
{
	float fRadius_Hold[2];	//半径
	float fLength_Hold[2];	//対角線
	float fAngle_Hold[2];	//角度
}BOMB_BOX;

//プロトタイプ宣言

/*生成*/
void Init_Bomb(void);

/*破棄*/
void Uninit_Bomb(void);

/*更新*/
void Update_Bomb(void);

/*描画*/
void Draw_Bomb(void);

void CalcSize_Bomb_Box(void);

/*ボムにデータを付与*/
void SetInfo_Bomb(void);

/*ボムのバーテックスを更新*/
void Update_Pos_Bomb(void);

/*ボムのバーテックスカラーを更新*/
void Update_Col_Bomb(void);

/*ボムのテクスチャを更新*/
void Update_Tex_Bomb(void);

/*ボムの情報を取得*/
BOMB* GetInfo_Bomb(void);

int* GetInfo_Bomb_aa(void);

#endif