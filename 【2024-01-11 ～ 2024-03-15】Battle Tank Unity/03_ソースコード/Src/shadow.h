//************************************************
//
// 影、ヘッダファイル[shadow.h]
// Author：福田歩希
//
//************************************************
#ifndef _SHADOW_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _SHADOW_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル /*/
#include "main.h"

// 影用情報
typedef struct
{
	bool use;				// 使用フラグ
	//D3DXVECTOR3* pPos;		// 対象位置
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR2 span;		// 大きさ用
	float angle;			// 角度
	float length;			// 対角線用
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	float colA;				// 透明度
}Shadow;

//プロトタイプ宣言
void InitShadow(void);					// 初期
void ImportTexShadow(void);				// テクスチャ取得
void CreateVtxBufferShadow(void);		// 頂点情報を生成
void UninitShadow(void);				// 破棄
int CreateShadow(/*D3DXVECTOR3* pPos,*/
	float rad);							// 生成
void UpdateShadow(void);				// 更新
void TrackShadow(int id,
	D3DXVECTOR3 pos);					// 新しい影の追従
void SetVtxShadow(void);				// 展開
void DeleteShadow(int id);				// 消去
void CalcMatrixShadow(void);			// 行列計算
void DrawShadow(void);					// 描画


#endif