//************************************************
//
//前景処理、ヘッダファイル[fg.h]
//Author：福田歩希
//
//************************************************
#ifndef _FG_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _FG_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス*/
#define	TEXTURE_IVY_1	"data\\TEX\\02_game\\ivy000.png"
#define	TEXTURE_IVY_2	"data\\TEX\\02_game\\ivy002.png"
#define	TEXTURE_IVY_3	"data\\TEX\\02_game\\ivy003.png"
//#define	TEXTURE_BUSH_1	"data\\TEX\\02_game\\bush000.png"

#define AMOUNT_POLYGON_FG	(8)	//ポリゴン数
#define AMOUNT_TEXTURE_FG	(3)	//読込みテクスチャ数

#define HALFSPAN_X_IVY	(300.0f)		//ツタ横半幅
#define HALFSPAN_X_LONGIVY	(600.0f)	//長いツタ横半幅
#define HALFSPAN_Y_IVY	(300.0f)		//ツタ縦半幅
#define HALFSPAN_Y_LONGIVY	(150.0f)	//長いツタ縦半幅

//#define HALFSPAN_X_BUSH	(300.0f)		//草むら横半幅
//#define HALFSPAN_X_LONGBUSH	(450.0f)	//長い草むら横半幅
//#define HALFSPAN_Y_BUSH	(300.0f)		//草むら縦半幅

//前景ポリゴン用構造体
typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	bool bUse;			//仕様判定
	int nCntSpawn;		//いつ出現するか
	float fLength;		//対角線を格納
	float fAngle;		//対角線の角度を格納
}FG_OBJECT;

//プロトタイプ宣言
void Init_FG(void);
void Uninit_FG(void);
void Update_FG(void);
void Draw_FG(void);
void SetSpan_FG(void);
void Setinfo_Vtx_FG(void);
void Disappear_FG(int nCnt);

#endif