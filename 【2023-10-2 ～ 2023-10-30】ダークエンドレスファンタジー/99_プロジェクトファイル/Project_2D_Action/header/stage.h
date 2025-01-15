//************************************************
//
//ステージオブジェクト配置処理、ヘッダファイル[stage.h]
//Author：福田歩希
//
//************************************************
#ifndef _STAGE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _STAGE_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*ファイルパス系*/
#define DATA_STAGE_OBJECT	"data\\csv\\info_stage_object.csv"
#define POS_STAGE_OBJECT	"data\\csv\\posinfo_stage_object.csv"
#define DATA_STAGE_OBJECT_OLD	"data\\csv\\info_stage_object_old.csv"

#define AMOUNT_POLYGON_STAGE	(256)	//ステージオブジェクトのポリゴン最大数
#define AMOUNT_TEX_STAGE	(3)	//ステージオブジェクトのテクスチャ総数

#define SPAN_CUT_SIDE_SATAGE	(6.0f)	//横補正係数

/*画像パス*/
#define	TEXTURE_STAGE_OBJECT_BLOCK	"data\\TEX\\tile_0000.png"
#define	TEXTURE_STAGE_OBJECT_LEFT	"data\\TEX\\tile_0001.png"
#define	TEXTURE_STAGE_OBJECT_RIGHT	"data\\TEX\\tile_0002.png"

//ステージオブジェクト種類分け
typedef enum
{
	STAGE_OBJECT_STYLE_NONE = 0,
	STAGE_OBJECT_STYLE_BLOCK,
	STAGE_OBJECT_STYLE_LEFT,
	STAGE_OBJECT_STYLE_RIGHT,
	STAGE_OBJECT_STYLE_LEFT_J,	//絶対にジャンプする崖、2箇所存在する
	STAGE_OBJECT_STYLE_RIGHT_J,
	STAGE_OBJECT_STYLE_MAX,
}STAGE_OBJECT_STYLE;

//判定種類分け
typedef enum
{
	HIT_TYPE_PLAYER = 0,
	HIT_TYPE_ENEMY,
	HIT_TYPE_MAX,
}HIT_TYPE;

//プレイヤー情報の列挙型
typedef struct
{
	int nStyle;			//種類
	bool bUse;			//使用
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength[2];	//対角線
	float fAngle[2];	//角度
}STAGE;

//プロトタイプ宣言

/*生成*/
void Init_Stage(void);

/*破棄*/
void Uninit_Stage(void);

/*更新*/
void Update_Stage(void);

/*描画*/
void Draw_Stage(void);

/*数値データを読み取る(旧)*/
void ReadInfo_Stage_Old(void);

/*数値データを読み取る*/
void ReadInfo_Stage(void);

/*数値データを読み取る*/
void ReadPosInfo_Stage(void);

/*ステージオブジェクトにデータを付与*/
void SetInfo_Stage(void);

/*ステージオブジェクトのバーテックスを更新*/
void Update_Pos_Stage(void);

/*ステージオブジェクトとの当たり判定*/
bool HitDetection_Stage(int nEnemy, int nType, D3DXVECTOR3* pos, D3DXVECTOR3* oldpos, D3DXVECTOR3* move, float fRadius[2]);

/*ステージオブジェクトのデータを取得*/
STAGE* GetInfo_Stage(void);

#endif