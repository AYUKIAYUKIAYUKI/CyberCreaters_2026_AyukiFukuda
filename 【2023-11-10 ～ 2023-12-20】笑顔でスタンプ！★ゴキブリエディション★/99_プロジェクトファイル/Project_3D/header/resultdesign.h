//************************************************
//
//リザルトデザイン、ヘッダファイル[result.h]
//Author：福田歩希
//
//************************************************
#ifndef _RESULTDESIGN_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RESULTDESIGN_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//リザルト表示用
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	float sizeX;
	float sizeY;
	float F;
}ResultDesign;

//プロトタイプ宣言
void InitResultDesign(void);	//初期
void SetInfoResultDesign(void);	//設定
void UninitResultDesign(void);	//破棄
void UpdateResultDesign(void);	//更新
void SetSizeResultDesign(void);	//展開
void UpdateColResultDesign(void);	//色変更
void DrawResultDesign(void);	//描画

#endif