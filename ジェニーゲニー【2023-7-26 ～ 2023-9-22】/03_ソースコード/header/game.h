//************************************************
//
//ゲーム動作処理、ヘッダファイル[game.h]
//Author：福田歩希
//
//************************************************
#ifndef _GAME_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _GAME_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

/*画像パス*/
#define	TEXTURE_BLACK_GAME	"data\\TEX\\02_game\\blackbase.png"

#define AMOUNT_POLYGON_GAME	(1)	//ポリゴン数

#define CHANGE_SPD_FADE_COLORA_GAME	(25)	//フェードのcolA変更速度

#define AMOUNT_CNT_FINISH_GAME	(90)	//ゲーム終了時の遅延時間

//プロトタイプ宣言
void Init_Game(void);
void Uninit_Game(void);
void Update_Game(void);
void Draw_Game(void);
void SetPos_Vtx_Game(void);
void Fadein_Animation_Game(void);
void Fadeout_Animation_Game(void);
bool* Getinfo_Pause(void);	//ポーズのcppにポーズ判定してるboolのアドレス渡すだけ

#endif