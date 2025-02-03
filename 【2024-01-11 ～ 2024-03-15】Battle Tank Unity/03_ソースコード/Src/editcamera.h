//************************************************
//
// 編集カメラ、ヘッダファイル[editcamera.h]
// Author：福田歩希
//
//************************************************
#ifndef _EDITCAMERA_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _EDITCAMERA_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル /*/
#include "main.h"

// 編集カメラ情報用
typedef struct
{
	D3DXVECTOR3 posV;			// カメラの座標
	D3DXVECTOR3 posR;			// 注視点の座標
	D3DXVECTOR3 rot;			// 現在の向き
	D3DXVECTOR3 rot_goal;		// 目標の向き
	float distance;				// 視点と注視点の距離
	D3DXVECTOR3 vecU;			// 上方向ベクトル
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX mtxView;			// ビューマトリックス
	D3DVIEWPORT9 viewport;		// ビューポート
}EditCamera;

/*/ プロトタイプ宣言 /*/
void InitEditCamera(void);						// 初期
void UpdateEditCamera(void);					// 更新
void CalcEditPosV(const D3DXVECTOR3 target);	// 視点を算出
void CalcEditPosR(const D3DXVECTOR3 target);	// 注視点を算出
void SetInfoEditCamera(void);					// カメラセット
EditCamera* GetInfoEditCamera(void);			// カメラ情報取得

#endif