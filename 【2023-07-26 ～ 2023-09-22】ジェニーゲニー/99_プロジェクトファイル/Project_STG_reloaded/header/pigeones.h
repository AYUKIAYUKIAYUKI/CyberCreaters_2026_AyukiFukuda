////************************************************
////
////タイトルのハト処理、ヘッダファイル[pegions.h]
////Author：福田歩希
////
////************************************************
//#ifndef _PEGIONS_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
//#define _PEGIONS_H_	//(二重インクルード防止、マクロ定義する)
//
//#include "main.h"
//#include "title.h"
//
//#define AMOUNT_POLYGON_PEGIONS	(2)	//ポリゴン数
//
//typedef struct
//{
//	int nStyle;			//種類
//	D3DXVECTOR3 pos;	//位置
//	float fSpanX;		//サイズ
//	float fSpanY;		//サイズ
//	D3DXVECTOR3 move;	//移動情報
//	D3DXVECTOR3 rot;	//向き情報
//	D3DXCOLOR col;		//色
//	float fLength;		//対角線
//	float fAngle;		//角度
//	int nCntStop;		//止まる時間
//	bool bTurn;			//戻る判定
//}PEGIONS;
//
////プロトタイプ宣言
//void Animation_Pegions(void);
//
//#endif