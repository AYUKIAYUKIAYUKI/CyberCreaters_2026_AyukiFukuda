//************************************************
//
//エフェクト生成処理、ヘッダファイル[billboard.h]
//Author：福田歩希
//
//************************************************
#ifndef _EFFECT_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _EFFECT_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//エフェクトの種類
enum EffectStyle
{
	EffectStyleBullet = 0,
	EffectStyleMax
};

//エフェクト構造体
struct Effect
{
	bool bUse;			//使用判定
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き(仮想の進行方向などに)
	D3DXCOLOR col;		//色
	float fDecrease;	//減少
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
};

//プロトタイプ宣言
void InitEffect(void);	//初期
void UninitEffect(void);	//破棄
void SetInfoEffect(int nStyle, D3DXVECTOR3 pos, D3DXCOLOR col);	//設定
void SetSizeEffect(int nCnt);	//サイズセット
void UpdateEffect(void);	//更新
void SetColEffect(int nCnt);	//カラーリング
void DisappearEffect(int nCnt);	//消滅
void DrawEffect(void);	//描画

#endif