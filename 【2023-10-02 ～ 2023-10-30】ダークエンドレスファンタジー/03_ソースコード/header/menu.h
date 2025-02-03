//************************************************
//
//メニュー処理、ヘッダファイル[menu.h]
//Author：福田歩希
//
//************************************************
#ifndef _MENU_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _MENU_H_	//(二重インクルード防止、マクロ定義する)

//プロトタイプ宣言

/*生成*/
void Init_Menu(void);

/*破棄*/
void Uninit_Menu(void);

/*更新*/
void Update_Menu(void);

/*描画*/
void Draw_Menu(void);

#endif