//************************************************
//
//影生成処理、ヘッダファイル[shadow.h]
//Author：福田歩希
//
//************************************************
#ifndef _SHADOW_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _SHADOW_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//ボツ影サイズプリセット
enum ShadowStyle
{
	ShadowStyleSmall = 0,
	ShadowStyleMiddle,
	ShadowStyleLarge,
	ShadowStyleMax
};

//影構造体
struct Shadow
{
	int nIdx;			//番号
	bool bUse;			//使用判定
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3* pPos;	//追従対象の位置
	D3DXVECTOR3 rot;	//向き(仮想の進行方向などに)
	float fSize;		//影サイズ
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
};

//プロトタイプ宣言
void InitShadow(void);	//初期
void UninitShadow(void);	//破棄
void SetInfoShadow(float fSize, D3DXVECTOR3* pPos);	//設定
void SetSizeShadow(int nCnt, int mode);	//サイズセット
void UpdateShadow(int mode);	//更新
void DisappearShadow(D3DXVECTOR3* pos);	//終了
void DrawShadow(void);	//描画

#endif