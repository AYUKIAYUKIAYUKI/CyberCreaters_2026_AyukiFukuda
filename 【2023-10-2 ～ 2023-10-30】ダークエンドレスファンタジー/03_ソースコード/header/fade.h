//************************************************
//
//フェード処理、ヘッダファイル[fade.h]
//Author：福田歩希
//
//************************************************
#ifndef _FADE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _FADE_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_FADE	"data\\TEX\\black.png"

#define RADIUS_FADE_X	(990.0f)	//横半幅
#define RADIUS_FADE_Y	(540.0f)	//縦半幅

#define SPD_CHANGE_COL_FADE (0.05f)	//フェード速度

//フェード情報の構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
	bool bFadeIn;
	bool bFadeOut;
}FADE;

//プロトタイプ宣言

/*生成*/
void Init_Fade(void);

/*破棄*/
void Uninit_Fade(void);

/*更新*/
void Update_Fade(void);

/*描画*/
void Draw_Fade(void);

/*フェードにデータを付与*/
void SetInfo_Fade(void);

/*フェードのバーテックスを更新*/
void Update_Pos_Fade(void);

/*フェードのバーテックスカラーを更新*/
void Update_Col_Fade(void);

/*フェードのデータを取得*/
FADE* GetInfo_Fade(void);

#endif