//************************************************
//
// テスト、ヘッダファイル[test.h]
// Author：福田歩希
//
//************************************************
#ifndef _TEST_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TEST_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル /*/
#include "main.h"

/*/ マクロ定義 /*/
#define TEST_POS_Y 90.0f	// テスト表示のY座標を指定

// テスト表示用構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 中心座標
	D3DXVECTOR3 move;	// 移動量
	D3DXVECTOR3 rot;	// 回転量
	D3DXVECTOR2 size;	// 横縦幅
	float angle;		// 角度
	float length;		// 対角線
	D3DXCOLOR col;		// 色情報
	float F;			// 汎用
}TEST;

/*/ プロトタイプ宣言 /*/
void InitTEST(int joined);				// 初期
void SetInfoTEST(int joined);			// 設定
void UninitTEST(void);					// 終了
void UpdateTEST(int joined);			// 更新
void SetSizeTEST(void);					// 展開
void SetColTEST(void);					// 色変更
void DrawTEST(void);					// 描画

#endif