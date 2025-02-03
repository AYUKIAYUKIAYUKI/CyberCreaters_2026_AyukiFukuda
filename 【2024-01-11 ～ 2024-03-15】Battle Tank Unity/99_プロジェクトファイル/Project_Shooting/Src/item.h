//************************************************
//
// アイテム、ヘッダファイル[item.h]
// Author：福田歩希
//
//************************************************
#ifndef _ITEM_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _ITEM_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル /*/
#include "main.h"

/*/ マクロ定義 /*/
#define AMOUNT_ITEM 64			// 物の最大数
#define AMOUNT_MODEL_ITEM	4	// 物の保持できる最大モデル種数

// アイテムの識別
typedef enum
{
	styleGun = 0,	// トンプソン
	styleRPG,		// RPG
	styleGut,		// ガトリング
	styleShot,		// 散弾銃
	Max_itemstyle
}ItemStyle;

// アイテム用モデル情報
typedef struct
{
	int style;								// スタイル
	LPD3DXMESH pMesh;						// メッシュのポインタ
	LPD3DXBUFFER pBuffMat;					// マテリアルのポインタ
	DWORD NumMat;							// マテリアルの数
	D3DXCOLOR ColMat_offset[AMOUNT_MAT];	// マテリアルの色オフセット
	LPDIRECT3DTEXTURE9 pTex[AMOUNT_MAT];	// テクスチャのポインタ
	D3DXVECTOR3 pos_offset;					// 位置オフセット
	D3DXVECTOR3 pos_moved;					// モーション後の変動位置
	D3DXVECTOR3 rot_offset;					// 向きオフセット
	D3DXVECTOR3 rot_moved;					// モーション後の変動向き
	D3DXMATRIX mtxWorld;					// ワールドマトリックス
	float rad;								// ひな形における判定サイズ
}ItemModel;

// アイテム用情報
typedef struct
{
	bool use;				// 使用しているかどうか
	int style;				// スタイル
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動量
	D3DXVECTOR3 rot;		// 向き
	ItemModel model;		// モデル情報
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	int id_effect;			// エフェクト識別番号格納
	int id_sph;				// 判定識別番号格納
}Item;

/*/ プロトタイプ宣言 /*/
void InitItem(void);					// 初期
void ImportModelItem(void);				// モデル取得
void ImportParamItem(FILE* pFile,
	int AmountModel);					// パラメータ取得
void ImportTexItem(int AmountModel);	// モデルテクスチャ取得
void CreateItem(int style, 
	D3DXVECTOR3 pos);					// 生成
void VerifyStyleItem(int id);			// スタイル番号を照合
void UninitItem(void);					// 終了
void UpdateItem(void);					// 更新
void RotateItem(int id);				// 回転
void MoveItem(int id);					// 移動
void CollisionItem(int id);				// 当たり判定
void CalcMtxItem(void);					// 行列計算
int GetItem(int id);					// 取得
void DrawItem(void);					// 描画
Item* GetInfoItem(void);				// 情報を取得

#endif