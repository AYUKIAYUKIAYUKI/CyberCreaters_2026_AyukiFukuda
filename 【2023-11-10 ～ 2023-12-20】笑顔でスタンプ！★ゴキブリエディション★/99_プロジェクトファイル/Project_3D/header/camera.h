//************************************************
//
//カメラ、ヘッダファイル[camera.h]
//Author：福田歩希
//
//************************************************
#ifndef _CAMERA_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _CAMERA_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//カメラ構造体
struct Camera
{
	D3DXVECTOR3 posV;	//位置
	D3DXVECTOR3 posR;	//注視点
	D3DXVECTOR3 rot;	//現在の向き
	D3DXVECTOR3 rotGoal;//目標の向き
	float fPA;			//現在の極角
	float fPAGoal;		//目標の極角
	float fDistance;	//視点と注視点の距離
	bool bTrack;		//対象物変更
	D3DXVECTOR3 vecU;	//上方向ベクトル
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
};

//プロトタイプ宣言
void InitCamera(void);	//初期
void UninitCamera(void);	//破棄
void UpdateCamera(int mode);	//更新
void CalcPosV(const D3DXVECTOR3 target);	//視点を算出
void CalcPosR(const D3DXVECTOR3 target);	//注視点を算出
void SetInfoCamera(int mode);	//カメラセット
Camera* GetInfoCamera(void);	//カメラ情報取得

#endif