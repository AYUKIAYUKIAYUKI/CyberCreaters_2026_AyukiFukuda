//************************************************
//
//ランキング処理、ヘッダファイル[result.h]
//Author：福田歩希
//
//************************************************
#ifndef _RANKING_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RANKING_H_	//(二重インクルード防止、マクロ定義する)

//プロトタイプ宣言

/*生成*/
void Init_Ranking(void);

/*破棄*/
void Uninit_Ranking(void);

/*更新*/
void Update_Ranking(void);

/*描画*/
void Draw_Ranking(void);

#endif