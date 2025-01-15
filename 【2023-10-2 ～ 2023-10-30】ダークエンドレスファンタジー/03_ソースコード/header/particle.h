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
#define	TEXTURE_ATKED	"data\\TEX\\atked.png"
#define	TEXTURE_BLOOD	"data\\TEX\\blood.png"

#define AMOUNT_POLYGON_PARTICLE	(256)	//ポリゴン数
#define AMOUNT_TEX_PARTICLE	(2)	//テクスチャ数

#define RADIUS_PARTICLE	(20.0f)			//半径用
#define REMAIN_TIME_PARTICLE	(30)	//残存時間

#define MOVE_SPD_POS_PARTICLE	(2.0f)		//移動速度
#define CHANGE_SPD_RADIUS_PARTICLE	(0.9f)	//縮小速度

#define SPD_CHANGE_TEX_PARTICLE	(1)	//アニメーション速度
#define AMOUNT_STYLE_TEX_PARTICLE	(8)	//アニメーション用
#define SPAN_CHANGE_TEX_PARTICLE	(0.125f)	//アニメーション用

typedef enum
{
	PARTICLE_ATKED = 0,
	PARTICLE_BLOOD,
	PARTICLE_STYLE_MAX,
}PARTICLE_STYLE;

//パーティクル構造体
typedef struct
{
	int nStyle;
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
	int nRemain;		//残存時間
	bool bUse;			//使用判定
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
void Setinfo_Particle(int nStyle, D3DXVECTOR3 pos, D3DXCOLOR col);

/*パーティクルバーテックスを更新*/
void Update_Pos_Particle(void);

/*テクスチャアニメーション処理*/
void Update_Tex_Particle(int nCnt);

#endif