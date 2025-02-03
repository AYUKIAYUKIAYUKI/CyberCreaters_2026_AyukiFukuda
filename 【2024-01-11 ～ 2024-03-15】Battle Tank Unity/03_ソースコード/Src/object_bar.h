//************************************************
//
// 構造物の体力ゲージ、ヘッダファイル[object_bar.h]
// Author：福田歩希
//
//************************************************
#ifndef _OBJECT_BAR_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _OBJECT_BAR_H_	// (二重インクルード防止、マクロ定義する)

/*---【インクルードファイル】---*/
#include "main.h"

/*---【構造物の体力ゲージの構造体】---*/
typedef struct
{
	bool use;			// 使用
	int dur;			// 継続期間
	D3DXVECTOR3 pos;	// 中心座標
	D3DXVECTOR3 move;	// 移動量
	D3DXVECTOR3 rot;	// 回転量
	D3DXVECTOR2 span;	// 大きさ
	float HPspan;		// 体力のサイズ割合
	float angle;		// 頂点角度
	float length;		// 頂点距離
	D3DXCOLOR col;		// 色
	float HPcol;		// 体力の色割合
	D3DXMATRIX mtx;		// マトリックス
} Object_Bar;

//プロトタイプ宣言
void InitObject_Bar(void);		// 初期
void UninitObject_Bar(void);	// 破棄
void UpdateObject_Bar(void);	// 更新
void DrawObject_Bar(void);		// 描画

int CreateObject_Bar(int HP);							// 生成
void EnableObject_Bar(int HP, int id, D3DXVECTOR3 pos);	// 表示

#endif