//************************************************
//
//弾のスタイル表示処理、ヘッダファイル)[style.h]
//Author：福田歩希
//
//************************************************
#ifndef _STYLE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _STYLE_H_	//(二重インクルード防止、マクロ定義する)

#include "bullet.h"

/*マクロ定義*/

/*画像パス*/
#define	TEXTURE_REUNION_ODD_BULLET	""

#define AMOUNT_TEXTURE_STYLE	(6)		//読込みテクスチャ数

typedef struct
{
	D3DXVECTOR3 pos;	//位置情報を格納
	float fMoveZ;		//回転量
	D3DXVECTOR3 rot;	//向きを格納
	BULLETSTYLE style;	//弾の種類
	float fLength;		//弾の対角線
	float fAngle;		//弾の角度
	int nPattern;		//アニメパターン
	float fTexX;		//テクスチャ座標X
	float fTexY;		//テクスチャ座標Y
}BULLETSTYLE_INDICATE;

//プロトタイプ宣言
void Init_Style(void);
void Uninit_Style(void);
void Update_Style(void);
void Draw_Style(void);

#endif