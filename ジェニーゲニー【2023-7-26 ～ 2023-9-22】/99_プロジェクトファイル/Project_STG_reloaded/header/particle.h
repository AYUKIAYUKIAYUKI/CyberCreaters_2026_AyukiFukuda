//************************************************
//
//パーティクル処理(テンプレ)、ヘッダファイル[particle.h]
//Author：福田歩希
//
//************************************************
#ifndef _PARTICLE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _PARTICLE_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*デバッグ用*/
#define	TEXTURE_PARTICLE	"data\\TEX\\.png"

#define AMOUNT_POLYGON_PARTICLE	(128)	//ポリゴン数

#define RADIUS_PARTICLE	(50.0f)			//半径用
#define REMAIN_TIME_PARTICLE	(60)	//残存時間

#define MOVE_SPD_POS_PARTICLE	(5.0f)		//移動速度
#define CHANGE_SPD_RADIUS_PARTICLE	(1.0f)	//縮小速度

//パーティクル構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報を格納
	D3DXVECTOR3 move;	//移動情報を格納
	D3DXCOLOR col;		//色情報を格納
	float fRadius;		//半径を格納
	int nRemain;		//残存時間を格納
	bool bUse;			//これが使われているか判別
}PARTICLE;

//プロトタイプ宣言

/*生成*/
void Init_Particle(void);

/*終了*/
void Uninit_Particle(void);

/*更新*/
void Update_Particle(void);

/*描画*/
void Draw_Particle(void);

/*パーティクルにデータを付与*/
void Setinfo_Particle(D3DXVECTOR3 pos, D3DXCOLOR col);

#endif