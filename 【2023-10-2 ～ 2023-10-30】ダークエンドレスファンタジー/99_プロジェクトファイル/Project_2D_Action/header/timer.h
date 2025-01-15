//************************************************
//
//制限時間処理、ヘッダファイル[timer.h]
//Author：福田歩希
//
//************************************************
#ifndef _TIMER_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TIMER_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス*/
#define	TEXTURE_TIMER	"data\\TEX\\number.png"

#define AMOUNT_POLYGON_TIMER	(4)	//ポリゴン数

//タイマー表示用構造体
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
}TIMER;

//プロトタイプ宣言

/*生成*/
void Init_Timer(void);

/*破棄*/
void Uninit_Timer(void);

/*更新*/
void Update_Timer(void);

/*描画*/
void Draw_Timer(void);

/*タイマーにデータを付与*/
void SetInfo_Timer(void);

/*タイマーのバーテックスを更新*/
void Update_Pos_Timer(void);

/*タイマーのテクスチャを更新*/
void Update_Tex_Timer(void);

/*タイマーからテクスチャ幅を計算*/
void Calc_Tex_Timer(void);

/*タイマー表示用のアドレスを取得*/
TIMER* GetInfo_TIMER(void);

/*タイマーのアドレスを取得*/
int* GetInfo_Timer(void);

#endif