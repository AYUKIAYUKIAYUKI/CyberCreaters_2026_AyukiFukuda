//************************************************
//
//アイテム処理、ヘッダファイル[item.h]
//Author：福田歩希
//
//************************************************
#ifndef _ITEM_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _ITEM_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_ITEM	"data\\TEX\\02_game\\item000.png"

#define AMOUNT_POLYGON_ITEM	(64)	//ポリゴン数

#define SPAN_X_ITEM	(50.0f)	//X全幅
#define SPAN_Y_ITEM	(50.0f)	//Y全幅
#define	HALFSPAN_X_ITEM	(25.0f)	//X半幅
#define HALFSPAN_Y_ITEM	(25.0f)	//Y半幅

#define REMAIN_TIME_ITEM	(60)	//待機時間
#define FRASH_TIME_ITEM	(30)		//点滅時間

#define AMOUNT_ADD_LIFE	(30)	//キャパ回復量

//アイテムの種類の列挙型
typedef enum
{
	ITEMSTYLE_TRACE = 0,	//キャパ回復アイテム
	ITEMSTYLE_MAX,			//アイテムの種類総数
}ITEMSTYLE;

//アイテムの状態分け列挙型
typedef enum
{
	ITEMSTATE_NORMAL = 0,	//通常状態
	ITEMSTATE_FLASHING,		//点滅状態
	ITEMSTATE_DISAPPEAR,	//消滅状態
	ITEMSTATE_MAX,			//状態の総数
}ITEMSTATE;

//アイテムの構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置情報を格納
	D3DXVECTOR3 move;	//移動量情報を格納
	D3DCOLOR col;		//色情報を格納
	int nRemain;		//残存時間
	bool bUse;			//使用状況判定
	ITEMSTYLE style;	//アイテムの種類
	ITEMSTATE state;	//アイテムの状態
	float fColorA;		//透明度変更用
	float fRadius;		//半径を格納
}ITEM;

//プロトタイプ宣言
void Init_Item(void);
void Uninit_Item(void);
void Update_Item(void);
void Draw_Item(void);
void Setinfo_Item(D3DXVECTOR3 pos, int nStyle);
void Disappear_Item(int nCntItem);

#endif