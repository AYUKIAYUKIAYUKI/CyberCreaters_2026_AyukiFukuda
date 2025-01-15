//************************************************
//
//スポーンエフェクト処理、ヘッダファイル[effect_spawn.h]
//Author：福田歩希
//
//************************************************
#ifndef _EFFECT_SPAWN_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _EFFECT_SPAWN_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス*/
#define	TEXTURE_GENERATOR_EFFECT_SPAWN	"data\\TEX\\02_game\\generator000.png"

#define AMOUNT_POLYGON_EFFECT_SPAWN	(64)	//ポリゴン数

#define SPAN_X_EFFECT_SPAWN	(100.0f)	//X全幅
#define SPAN_Y_EFFECT_SPAWN	(100.0f)	//Y全幅
#define	HALFSPAN_X_EFFECT_SPAWN	(50.0f)	//X半幅
#define HALFSPAN_Y_EFFECT_SPAWN	(50.0f)	//Y半幅

#define ROTATE_SPD_EFFECT_SPAWN	(0.05f)	//エフェクト回転速度

#define CHANGE_SPD_COLORA_EFFECT_SPAWN	(10)	//エフェクトのcolA変更速度

//スポーンエフェクト構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報を格納
	D3DXVECTOR3 move;	//移動量情報を格納
	D3DXVECTOR3 rot;	//向き情報を格納
	bool bUse;			//これが使われているか判別
	float fLength;		//対角線を格納
	float fAngle;		//対角線の角度を格納
	int nColorA;		//透明度変更用
}SPAWN_EFFECT;

//プロトタイプ宣言
void Init_Effect_Spawn(void);
void Uninit_Effect_Spawn(void);
void Update_Effect_Spawn(void);
void Draw_Effect_Spawn(void);
void SetPos_Vtx_Effect_Spawn(int nCntEnemy, D3DXVECTOR3 pos, D3DXVECTOR3 move);

#endif