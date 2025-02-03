//************************************************
//
//ゲーム処理、ヘッダファイル[game.h]
//Author：福田歩希
//
//************************************************
#ifndef _GAME_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _GAME_H_	//(二重インクルード防止、マクロ定義する)

//ポーズメニューの選択肢
typedef enum
{
	CONTINUE = 0,
	RETRY,
	RETIRE,
	RESULT,
	PAUSE_MENU_MAX,
}PAUSE_MENU;

//プロトタイプ宣言

/*生成*/
void Init_Game(void);

/*終了*/
void Uninit_Game(void);

/*更新*/
void Update_Game(void);

/*描画*/
void Draw_Game(void);

/*ポーズメニューの選択項目を引き渡す*/
int* Getinfo_Choose_Pause_Menu(void);

/*スコアを記録する*/
void Save_Score(void);

#endif