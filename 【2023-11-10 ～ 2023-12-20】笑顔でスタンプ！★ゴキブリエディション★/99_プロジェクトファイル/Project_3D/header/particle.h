//************************************************
//
//パーティクル生成処理、ヘッダファイル[billboard.h]
//Author：福田歩希
//
//************************************************
#ifndef _PARTICLE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _PARTICLE_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

////パーティクルの種類
//enum ParticleStyle
//{
//	ParticleStyleBullet = 0,
//	ParticleStyleEnemy,
//	ParticleStyleMax
//};

//パーティクル構造体
struct Particle
{
	bool bUse;			//使用判定
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き(仮想の進行方向などに)
	D3DXCOLOR col;		//色
	float fSize;		//サイズ
	float fDecrease;	//減少
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
};

//プロトタイプ宣言
void InitParticle(void);	//初期
void UninitParticle(void);	//破棄
void SetInfoParticle(D3DXVECTOR3 pos, D3DXCOLOR col, float fSize);	//設定
void SetSizeParticle(int nCnt);	//サイズセット
void UpdateParticle(void);	//更新
void SetColParticle(int nCnt);	//カラーリング
void DisappearParticle(int nCnt);	//消滅
void DrawParticle(void);	//描画

#endif