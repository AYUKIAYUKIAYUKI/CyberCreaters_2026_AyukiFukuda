//************************************************
//
// ゲームUI表示用情報、ヘッダファイル[ui.h]
// Author：福田歩希
//
//************************************************
#ifndef _Phase_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _Phase_H_	// (二重インクルード防止、マクロ定義する)

/*---【インクルードファイル】---*/
#include "main.h"

/*---【アニメーション分類】---*/
typedef enum
{
	ANIMATION_TYPE_VIBSMALL = 0,	// 振動：小
	ANIMATION_TYPE_VIBBIG,			// 振動：大
	ANIMATION_TYPE_RED,				// 赤くなる
	ANIMATION_TYPE_FADE,			// 出現
	ANIMATION_TYPE_GUMMY,			// ブニョ
	ANIMATION_TYPE_APPEAL,			// チラチラ
	ANIMATION_TYPE_SLIDEUP,			// 上スライドイン
	ANIMATION_TYPE_SLIDEDOWN,		// 下
	ANIMATION_TYPE_SLIDELEFT,		// 左
	ANIMATION_TYPE_SLIDERIGHT,		// 右
	ANIMATION_TYPE_DISUP,			// 上スライドアウト
	ANIMATION_TYPE_DISDOWN,			// 下
	ANIMATION_TYPE_DISLEFT,			// 左
	ANIMATION_TYPE_DISRIGHT,		// 右
	ANIMATION_TYPE_MAX
} ANIMATION_TYPE;

/*---【アニメーション動作用】---*/
typedef struct
{
	bool use;			// 使用
	int dur;			// アニメーション継続時間
	D3DXVECTOR3 move;	// 中心座標
	D3DXVECTOR3 pos;	// 移動量
	D3DXVECTOR3 rot;	// 回転量
	D3DXVECTOR2 span;	// 大きさ
	D3DXCOLOR col;		// 色
} AnimationParam;

/*---【UI表示用】---*/
typedef struct
{
	bool use;									// 使用
	int textype;								// テクスチャ分類
	D3DXVECTOR3 pos;							// 中心座標
	D3DXVECTOR3 move;							// 移動量
	D3DXVECTOR3 rot;							// 回転量
	D3DXVECTOR2 span;							// 大きさ
	float angle;								// 頂点角度
	float length;								// 頂点距離
	D3DXCOLOR col;								// 色
	AnimationParam play[ANIMATION_TYPE_MAX];	// アニメーション時の情報
	D3DXMATRIX mtx;								// マトリックス
} UI;

#endif