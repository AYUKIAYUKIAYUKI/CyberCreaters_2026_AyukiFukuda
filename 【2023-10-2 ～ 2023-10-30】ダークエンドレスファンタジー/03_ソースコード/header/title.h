//************************************************
//
//タイトル処理、ヘッダファイル[title.h]
//Author：福田歩希
//
//************************************************
#ifndef _TITLE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TITLE_H_	//(二重インクルード防止、マクロ定義する)

//タイトルメニューの選択肢
typedef enum
{
	START = 0,
	RANKING,
	END,
	TITLE_MENU_MAX,
}TITLE_MENU;

/*生成*/
void Init_Title(void);

/*破棄*/
void Uninit_Title(void);

/*更新*/
void Update_Title(void);

/*描画*/
void Draw_Title(void);

/*タイトルメニューの選択項目を引き渡す*/
int* Getinfo_Choose_Title_Menu(void);

#endif