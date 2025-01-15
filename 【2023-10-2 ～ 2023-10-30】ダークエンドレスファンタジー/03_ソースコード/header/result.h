//************************************************
//
//リザルト処理、ヘッダファイル[result.h]
//Author：福田歩希
//
//************************************************
#ifndef _RESULT_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RESULT_H_	//(二重インクルード防止、マクロ定義する)

//プロトタイプ宣言

/*生成*/
void Init_Result(void);

/*破棄*/
void Uninit_Result(void);

/*更新*/
void Update_Result(void);

/*描画*/
void Draw_Result(void);

/*クリア判定を取得*/
bool* GetInfo_CLEAR(void);

#endif