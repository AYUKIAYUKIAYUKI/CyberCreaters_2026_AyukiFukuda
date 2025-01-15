//************************************************
//
//ポーズ画面、ヘッダファイル[pause.h]
//Author：福田歩希
//
//************************************************
#ifndef _PAUSE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _PAUSE_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス*/
#define	TEXTURE_WHITE_PAUSE	"data\\TEX\\01_menu\\blackbase.png"

//プロトタイプ宣言
void Init_Pause(void);
void Uninit_Pause(void);
void Update_Pause(void);
void Draw_Pause(void);
bool* Getinfo_Return_Pause(void);

#endif