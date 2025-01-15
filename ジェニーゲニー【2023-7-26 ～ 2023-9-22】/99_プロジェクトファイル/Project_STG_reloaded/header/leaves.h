//************************************************
//
//葉っぱが舞う処理、ヘッダファイル[leaves.h]
//Author：福田歩希
//
//************************************************
#ifndef _LEAVES_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _LEAVES_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_LEAF_1	"data\\TEX\\02_game\\leaf000.png"
#define	TEXTURE_LEAF_2	"data\\TEX\\02_game\\leaf001.png"
#define	TEXTURE_LEAF_3	"data\\TEX\\02_game\\leaf002.png"
#define	TEXTURE_LEAF_4	"data\\TEX\\02_game\\leaf003.png"
#define	TEXTURE_LEAF_5	"data\\TEX\\02_game\\leaf004.png"

#define AMOUNT_POLYGON_LEAVES	(16)//ポリゴン数
#define AMOUNT_TEXTURE_LEAVES	(5)	//読込みテクスチャ数

#define HALFSPAN_X_TINYLEAF_1	(20)	//細い葉っぱの横幅
#define HALFSPAN_X_LEAF_1	(40)	//普通の葉っぱの横幅
#define HALFSPAN_Y_LEAF_1	(40)	//葉っぱ共通の縦幅

//葉っぱ構造体
typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置情報を格納
	float fHalfSpanX;	//横幅
	float fHalfSpanY;	//縦幅
	int nRute;			//どう落ちる
	int nKeepTime;		//その動きをし続ける期間
	D3DXVECTOR3 move;	//移動情報を格納
	D3DXVECTOR3 rot;	//向き情報を格納
	bool bUse;			//仕様判定
	int nCntSpawn;		//いつ出現するか
	float fLength;		//対角線を格納
	float fAngle;		//対角線の角度を格納
}LEAVES;


//プロトタイプ宣言
void Init_Leaves(void);
void Uninit_Leaves(void);
void Update_Leaves(void);
void Draw_Leaves(void);
void SetSpan_Leaves(void);
void Setinfo_Leaves(void);
void Disappear_Leaves(int nCnt);

#endif