//************************************************
//
// 煙エフェクト、ヘッダファイル[effect_smoke.h]
// Author：福田歩希
//
//************************************************
#ifndef _EFFECT_SMOKE_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _EFFECT_SMOKE_H_	// (二重インクルード防止、マクロ定義する)

/*---【インクルードファイル】---*/
#include "main.h"

// 煙エフェクト用情報
typedef struct
{
	bool use;				// 使用フラグ
	int style;				// スタイル
	D3DXVECTOR3* pPos;		// 対象位置
	D3DXVECTOR3 pos_moved;	// 変動位置
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR2 span;		// 大きさ用
	float angle;			// 角度
	float length;			// 対角線用
	D3DXCOLOR col;			// 色
	int remain;				// 寿命
	TextureAnimation anima;	// アニメーション用
	D3DXMATRIX mtx;			// 行列用
} Effect_Smoke;

/*---【プロトタイプ宣言】---*/
void InitEffect_Smoke(void);	// 初期
void UninitEffect_Smoke(void);	// 終了
void UpdateEffect_Smoke(void);	// 更新
void DrawEffect_Smoke(void);	// 描画

int CreateEffect_Smoke(int type, D3DXVECTOR3* pPos);	// 生成

#endif