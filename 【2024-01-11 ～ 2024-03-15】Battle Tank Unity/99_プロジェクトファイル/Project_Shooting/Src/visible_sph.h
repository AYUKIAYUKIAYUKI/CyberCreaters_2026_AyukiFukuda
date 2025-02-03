//************************************************
//
// 球形の当たり判定を可視化、ヘッダファイル[visible_sph.h]
// Author：福田歩希
//
//************************************************
#ifndef _VISIBLE_SPH_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _VISIBLE_SPH_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル /*/
#include "main.h"

// スフィア構造体
typedef struct
{
	bool use;				// 使用判定
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3* pPos;		// 追従対象の位置
	D3DXCOLOR col;			// 色
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	int dur;				// 使用期間：簡易生成用
}Sph;

/*/ プロトタイプ宣言 /*/
void InitVisibleSph(void);						// 初期
int CreateVisibleSph(const float rad,
	D3DXCOLOR col, D3DXVECTOR3* pPos);			// 生成
void UninitVisibleSph(void);					// 破棄
void UpdateVisibleSph(void);					// 更新
void DeleteVisibleSph(int id);					// 消去
void CreateInstantVisibleSph(float rad,
	D3DXCOLOR col, D3DXVECTOR3* pPos, int dur);	// 簡易生成
void ManageInstantVisibleSph(int id);			// 簡易スフィア管理
void CalcMtxVisibleSph(void);					// 行列計算
void DrawVisibleSph(void);						// 描画

#endif