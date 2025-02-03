//************************************************
//
// 箱型の判定を可視化、ヘッダファイル[visible_box.h]
// Author：福田歩希
//
//************************************************
#ifndef _VISIBLE_BOX_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _VISIBLE_BOX_H_	// (二重インクルード防止、マクロ定義する)

/*---【インクルードファイル】---*/
#include "main.h"

/*---【ボックス構造体】-- - */
typedef struct
{
	bool use;				// 使用判定
	D3DXVECTOR3 pos;		// 位置
	COLLISION_AABB* aabb;	// 判定情報を格納
	D3DXCOLOR col;			// 表示カラー
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
} Box;

/*---【プロトタイプ宣言】---*/
void InitVisibleBox(void);				// 初期
int CreateVisibleBox(COLLISION_AABB* obj,
	D3DXCOLOR col);						// 生成
void UninitVisibleBox(void);			// 破棄
void UpdateVisibleBox(void);			// 更新
void DeleteVisibleBox(int id);			// 消去
void CalcMtxVisibleBox(void);			// 行列計算
void DrawVisibleBox(void);				// 描画

#endif