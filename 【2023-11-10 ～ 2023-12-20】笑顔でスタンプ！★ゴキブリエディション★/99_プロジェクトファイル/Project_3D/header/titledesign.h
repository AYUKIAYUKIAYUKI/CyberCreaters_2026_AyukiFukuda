//************************************************
//
//タイトルデザイン、ヘッダファイル[titledesign.h]
//Author：福田歩希
//
//************************************************
#ifndef _TITLEDESIGN_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TITLEDESIGN_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//タイトル表示用
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	float sizeX;
	float sizeY;
	float F;
}TitleDesign;

//プロトタイプ宣言
void InitTitleDesign(void);	//初期
void SetInfoTitleDesign(void);	//設定
void UninitTitleDesign(void);	//破棄
void UpdateTitleDesign(void);	//更新
void SetSizeTitleDesign(void);	//展開
void UpdateColTitleDesign(void);	//色変更
void DrawTitleDesign(void);	//描画
MODE GetChooseMode(void);	//何選んでる

#endif