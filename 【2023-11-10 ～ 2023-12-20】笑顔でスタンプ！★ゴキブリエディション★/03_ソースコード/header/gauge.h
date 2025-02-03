//************************************************
//
//ゲージ、ヘッダファイル[gauge.h]
//Author：福田歩希
//
//************************************************
#ifndef _GAUGE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _GAUGE_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//チュートリアル表示用
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	float sizeX;
	float sizeY;
	float F;
}Gauge;

//プロトタイプ宣言
void InitGauge(void);	//初期
void SetInfoGauge(void);	//設定
void UninitGauge(void);	//破棄
void UpdateGauge(void);	//更新
void SetSizeGauge(void);	//展開
void UpdateColGauge(void);	//色変更
void DrawGauge(void);	//描画

#endif