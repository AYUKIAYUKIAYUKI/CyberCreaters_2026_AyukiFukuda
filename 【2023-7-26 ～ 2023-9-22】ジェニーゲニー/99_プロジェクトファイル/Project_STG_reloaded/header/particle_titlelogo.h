//************************************************
//
//タイトルロゴパーティクル処理、ヘッダファイル[particle_titlelogo.h]
//Author：福田歩希
//
//************************************************
#ifndef _PARTICLE_TITLELOGO_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _PARTICLE_TITLELOGO_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*デバッグ用*/
#define	TEXTURE_PARTICLE_TITLELOGO	"data\\TEX\\02_game\\effect0001.png"

#define AMOUNT_POLYGON_PARTICLE_TITLELOGO	(8)	//ポリゴン数

#define RADIUS_PARTICLE_TITLELOGO	(20.0f)		//半径用
#define REMAIN_TIME_PARTICLE_TITLELOGO	(180)	//残存時間


#define MOVE_SPD_POS_PARTICLE_TITLELOGO	(1.0f)			//移動速度
#define CHANGE_SPD_RADIUS_PARTICLE_TITLELOGO	(0.25f)	//縮小速度

//パーティクル構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報を格納
	D3DXVECTOR3 move;	//移動情報を格納
	D3DXCOLOR col;		//色情報を格納
	float fRadius;		//半径を格納
	int nRemain;		//残存時間を格納
	bool bUse;			//これが使われているか判別
}PARTICLE_TITLELOGO;

//プロトタイプ宣言
void Init_Particle_Titlelogo(void);
void Uninit_Particle_Titlelogo(void);
void Update_Particle_Titlelogo(void);
void Draw_Particle_Titlelogo(void);
void Setinfo_Particle_Titlelogo(D3DXVECTOR3 pos);

#endif