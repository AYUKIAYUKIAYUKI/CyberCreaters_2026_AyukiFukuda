//************************************************
//
// カメラ、ヘッダファイル[camera.h]
// Author：福田歩希
//
//************************************************
#ifndef _CAMERA_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _CAMERA_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル /*/
#include "main.h"

/*/ マクロ定義 /*/
#define AMOUNT_CAMERA 4			// カメラの数
#define UP_ADJUST_POSR 0.35f	// 上方リファレンス係数
#define MIN_POSR 0.3927f		// 下方リファレンス最低値

// カメラ情報用
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
	int durVib;					// 振動の継続時間
}Camera;

// ビューポートサイズ用
typedef struct
{
	DWORD Width;	// 横幅
	DWORD Height;	// 縦幅
}viewportSize;

// UIポート
typedef struct
{
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	D3DVIEWPORT9 viewport;		// ビューポート
}UIport;

/*---【プロトタイプ宣言】---*/
void InitCamera(int joined);							// 初期
viewportSize SetSizeViewport(int joined);				// ビューポートサイズを設定
void InitUIport(void);									// UIポート初期
void UpdateCamera(int joined);							// 更新
void VibCamera(int id);									// 画面の振動
void CalcPosV(int id, const D3DXVECTOR3 target);		// 視点を算出
void CalcPosR(int id, const D3DXVECTOR3 target);		// 注視点を算出
void SetInfoCamera(int id, int joined);					// カメラセット
void CalcMatrixProjectionCamera(int id, int joined);	// プロジェクションマトリックス計算
void CalcMatrixViewCamera(int id);						// ビューマトリックス計算
void SetInfoUIport(void);								// UIポートの設定
Camera* GetInfoCamera(void);							// カメラ情報取得

#endif