//************************************************
//
// レティクル、ヘッダファイル[reticle.h]
// Author：福田歩希
//
//************************************************
#ifndef _RETICLE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RETICLE_H_	//(二重インクルード防止、マクロ定義する)

/*/ インクルードファイル /*/
#include "main.h"

// レティクル用情報
typedef struct
{
	bool use;				// 使用フラグ
	D3DXVECTOR3 pos_moved;	// 変動位置
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR2 span;		// 大きさ用
	float angle;			// 角度
	float length;			// 対角線用
	int remain;				// 寿命
	D3DXCOLOR col;			// 色
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
}Reticle;

//プロトタイプ宣言
void InitReticle(void);				// 初期
void CreateReticle(int joined);		// 生成
void UninitReticle(void);			// 終了
void UpdateReticle(int joined);		// 更新
void SetVtxReticle(int joined);		// 展開
void DrawReticle(int id);			// 描画
Reticle* GetInfoReticle(void);		// 取得

#endif