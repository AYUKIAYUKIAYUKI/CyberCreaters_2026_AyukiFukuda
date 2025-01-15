//************************************************
//
//コメットエフェクト処理、ヘッダファイル[effect_comet.h]
//Author：福田歩希
//
//************************************************
#ifndef _EFFECT_COMET_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _EFFECT_COMET_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス*/
#define	TEXTURE_EFFECT_COMET	"data\\TEX\\02_game\\comet_explosion.png"

#define AMOUNT_POLYGON_EFFECT_COMET	(128)	//ポリゴン数

#define SPAN_X_EFFECT_COMET	(150.0f)	//X全幅
#define SPAN_Y_EFFECT_COMET	(150.0f)	//Y全幅
#define	HALFSPAN_X_EFFECT_COMET	(75.0f)	//X半幅
#define HALFSPAN_Y_EFFECT_COMET	(75.0f)	//Y半幅

#define ROTATE_SPD_EFFECT_COMET	(0.1f)	//エフェクト回転速度

//スポーンエフェクト構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報を格納
	D3DXVECTOR3 move;	//移動量を格納
	D3DXVECTOR3 rot;	//向き情報を格納
	bool bUse;			//これが使われているか判別
	float fLength;		//対角線を格納
	float fAngle;		//対角線の角度を格納
	int nPattern;		//アニメーション
	float fTexX;		//テクスチャ座標X
	float fTexY;		//テクスチャ座標Y
}COMET_EFFECT;

//プロトタイプ宣言
void Init_Effect_Comet(void);
void Uninit_Effect_Comet(void);
void Update_Effect_Comet(void);
void Draw_Effect_Comet(void);
void SetPos_Vtx_Effect_Comet(D3DXVECTOR3 pos, float moveX);

#endif