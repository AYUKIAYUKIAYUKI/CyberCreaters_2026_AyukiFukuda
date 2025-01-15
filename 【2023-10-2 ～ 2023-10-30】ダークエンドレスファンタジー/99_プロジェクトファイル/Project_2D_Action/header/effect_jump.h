//************************************************
//
//ジャンプエフェクト処理、ヘッダファイル[effect_jump.h]
//Author：福田歩希
//
//************************************************
#ifndef _EFFECT_JUMP_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _EFFECT_JUMP_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス*/
#define	TEXTURE_EFFECT_JUMP	"data\\TEX\\effect_jump00.png"

#define RADIUS_EFFECT_JUMP_X	(100.0f)	//横半幅
#define RADIUS_EFFECT_JUMP_Y	(20.0f)		//縦半幅

//プレイヤー情報の列挙型
typedef struct
{
	bool bUse;			//使用
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength;		//対角線
	float fAngle;		//角度
}EFFECT_JUMP;

//プロトタイプ宣言

/*生成*/
void Init_Effect_Jump(void);

/*破棄*/
void Uninit_Effect_Jump(void);

/*更新*/
void Update_Effect_Jump(void);

/*描画*/
void Draw_Effect_Jump(void);

/*ジャンプエフェクトのバーテックスを更新*/
void Update_Pos_Effect_Jump(void);

/*ジャンプエフェクトにデータを付与*/
void SetInfo_Effect_Jump(D3DXVECTOR3 pos);

/*ジャンプエフェクトのデータを取得*/
EFFECT_JUMP* Getinfo_Effect_Jump(void);

#endif