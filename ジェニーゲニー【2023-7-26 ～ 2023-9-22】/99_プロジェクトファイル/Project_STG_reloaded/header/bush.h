//************************************************
//
//草むら処理、ヘッダファイル[bush.h]
//Author：福田歩希
//
//************************************************
#ifndef _BUSH_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _BUSH_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス*/
#define	TEXTURE_BUSH_1	"data\\TEX\\02_game\\bush000.png"
#define	TEXTURE_BUSH_2	"data\\TEX\\02_game\\bush001.png"
#define	TEXTURE_BUSH_3	"data\\TEX\\02_game\\bush002.png"
#define	TEXTURE_BUSH_4	"data\\TEX\\02_game\\bush003.png"
#define	TEXTURE_BUSH_5	"data\\TEX\\02_game\\bush004.png"

#define AMOUNT_POLYGON_BUSH	(16)	//ポリゴン数
#define AMOUNT_TEXTURE_BUSH	(5)	//読込みテクスチャ数

#define HALFSPAN_X_BUSH	(300.0f)		//草むら横半幅
#define HALFSPAN_X_LONGBUSH	(450.0f)	//長い草むら横半幅
#define HALFSPAN_Y_BUSH	(300.0f)		//草むら縦半幅

//草むら用構造体
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
}BUSH;

//プロトタイプ宣言
void Init_Bush(void);
void Uninit_Bush(void);
void Update_Bush(void);
void Draw_Bush(void);
void SetSpan_Bush(void);
void Setinfo_Vtx_Bush(void);
void Disappear_Bush(int nCnt);

#endif