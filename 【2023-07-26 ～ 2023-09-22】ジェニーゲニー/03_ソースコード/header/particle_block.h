//************************************************
//
//ブロックパーティクル処理、ヘッダファイル[particle_Block.h]
//Author：福田歩希
//
//************************************************
#ifndef _PARTICLE_BLOCK_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _PARTICLE_BLOCK_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*デバッグ用*/
#define	TEXTURE_PARTICLE_BLOCK	"data\\TEX\\02_game\\blocks_particle.png"

#define AMOUNT_POLYGON_PARTICLE_BLOCK	(256)	//ポリゴン数

#define RADIUS_PARTICLE_BLOCK	(50.0f)		//半径用
#define REMAIN_TIME_PARTICLE_BLOCK	(60)	//残存時間

#define MOVE_SPD_POS_PARTICLE_BLOCK	(2.5f)		//移動速度
#define CHANGE_SPD_RADIUS_PARTICLE_BLOCK	(1.0f)	//縮小速度

//パーティクル構造体
typedef struct
{
	int nStyle;			//どのブロック
	D3DXVECTOR3 pos;	//位置情報を格納
	D3DXVECTOR3 move;	//移動情報を格納
	D3DXVECTOR3 moveB;	//ブロック移動情報を格納
	D3DXVECTOR3 rot;	//向き情報を取得
	D3DXCOLOR col;		//色情報を格納
	float fRadius;		//半径を格納
	int nRemain;		//残存時間を格納
	bool bUse;			//これが使われているか判別
	float fAngle;		//角度格納
}PARTICLE_BLOCK;

//プロトタイプ宣言
void Init_Particle_Block(void);
void Uninit_Particle_Block(void);
void Update_Particle_Block(void);
void Draw_Particle_Block(void);
void Setinfo_Particle_Block(D3DXVECTOR3 pos, D3DXVECTOR3 moveBlock);

#endif