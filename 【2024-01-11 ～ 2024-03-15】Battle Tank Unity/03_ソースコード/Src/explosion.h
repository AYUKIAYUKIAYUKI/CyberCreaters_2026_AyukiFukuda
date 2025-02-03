//************************************************
//
// 爆発処理、ヘッダファイル[explosion.h]
// Author：葛西敬介
//
//************************************************

#ifndef _EXPLOSION_H_     //このマクロ定義がされていなかったら
#define _EXPLOSION_H_    //2重インクルード防止のマクロ定義

//include
#include "main.h"

//マクロ定義
#define MAX_EXPLOSION	(1024)	//爆発エフェクトの最大数

//爆発エフェクトの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nCounterAnim;		//アニメーションカウンター
	int nPatternAnim;		//アニメーションパターンNo.
	float fWidth;			//幅
	float fHeight;			//高さ
	float fLength;			//対角線の長さ
	bool bUse;				//使用しているかどうか
}Explosion;

//プロトタイプ宣言
void InitExplosion(void);														//爆発の初期化処理
void UninitExplosion(void);														//爆発の終了処理
void UpdateExplosion(void);														//爆発の更新処理
void DrawExplosion(void);														//爆発の描画処理
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);	//爆発の設定処理
Explosion* GetExplosion(void);													//爆発の情報を取得
#endif