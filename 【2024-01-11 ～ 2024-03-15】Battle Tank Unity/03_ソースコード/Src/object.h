//************************************************
//
// オブジェクト、ヘッダファイル[object.h]
// Author：福田歩希
//
//************************************************
#ifndef _OBJECT_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _OBJECT_H_	//(二重インクルード防止、マクロ定義する)

/*---【インクルードファイル】---*/
#include "main.h"

/*---【マクロ定義】---*/
#define AMOUNT_OBJECT 512			// 物の最大数
#define AMOUNT_MODEL_OBJECT	33		// 物の保持できる最大モデル種数

/*---【オブジェクトの状態分類】---*/
typedef enum
{
	STATE_NORMAL_OBJECT = 0,	// 通常
	STATE_DAMAGE_OBJECT,		// 被ダメ
	STATE_DEAD_OBJECT,			// 死亡？
	STATE_RESURRECT_OBJECT,		// 復活
	STATE_OBJECT_MAX
} STATE_OBJECT;

/*---【オブジェクトパラメータ】---*/
typedef struct
{
	int state;	// 状態
	int dur;	// 継続期間
	int HP;		// 体力
	int DEF;	// 防御力
} ObjectParam;

/*---【オブジェクトモデル用】---*/
typedef struct
{
	LPD3DXMESH pMesh;						// メッシュ情報のポインタ
	LPD3DXBUFFER pBuffMat;					// マテリアルのポインタ
	DWORD NumMat;							// マテリアルの数
	LPDIRECT3DTEXTURE9 pTex[AMOUNT_MAT];	// テクスチャのポインタ
	COLLISION_AABB aabb;					// 箱の判定用
} ObjectModel;

/*---【オブジェクト情報用】---*/
typedef struct
{
	bool use;				// 使用判定
	int type;				// モデルの種類格納
	ObjectParam param;		// パラメータ
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 size;		// サイズ
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	ObjectModel model;		// モデル情報格納
	int id_bar;				// 体力ゲージの番号格納用
	int id_shadow;			// 一応影の番号格納用
	int id_box;				// 箱の識別番号
} Object;

/*---【プロトタイプ宣言】---*/
void InitObject(void);					// 初期
void UninitObject(void);				// 破棄
void UpdateObject(bool LayoutEdit);		// 更新
void DrawObject(bool LayoutEdit);		// 描画

void HitObject(int id);				// 被弾時の処理
Object* GetInfoObject(void);		// オブジェクトの情報を取得
Object* GetInfoGizmoObject(void);	// ギズモ情報を取得

#endif