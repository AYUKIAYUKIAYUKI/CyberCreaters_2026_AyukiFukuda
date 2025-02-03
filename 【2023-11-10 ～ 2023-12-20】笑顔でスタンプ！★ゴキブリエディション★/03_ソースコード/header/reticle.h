//************************************************
//
//レティクル、ヘッダファイル[reticle.h]
//Author：福田歩希
//
//************************************************
#ifndef _RETICLE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _RETICLE_H_	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義
#define	TEXTURE_RETICLE	"data\\texture\\250.png"

//ビルボード構造体
struct Reticle
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 rot;	//向き(仮想の進行方向などに)
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
};

//プロトタイプ宣言
void InitReticle(void);	//初期
void UninitReticle(void);	//終了
void SizeSetReticle(void);	//展開
void UpdateReticle(void);	//更新
void DrawReticle(void);	//描画
Reticle* GetInfoReticle(void);	//取得

#endif