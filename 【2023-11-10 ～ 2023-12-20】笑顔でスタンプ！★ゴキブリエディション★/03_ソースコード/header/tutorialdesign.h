//************************************************
//
//チュートリアルデザイン、ヘッダファイル[tutorialdesign.h]
//Author：福田歩希
//
//************************************************
#ifndef _TUTORIALDESIGN_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TUTORIALDESIGN_H_	//(二重インクルード防止、マクロ定義する)

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
}TutorialDesign;

//プロトタイプ宣言
void InitTutorialDesign(void);	//初期
void SetInfoTutorialDesign(void);	//設定
void UninitTutorialDesign(void);	//破棄
void UpdateTutorialDesign(void);	//更新
void SetSizeTutorialDesign(void);	//展開
void UpdateColTutorialDesign(void);	//色変更
void DrawTutorialDesign(void);	//描画1
bool* GetInfoSpawnEnemy(void);	//敵がわくかどうか判定
bool* GetInfoStampEnemy(void);	//敵をつぶしたか判定

#endif