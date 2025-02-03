////************************************************
////
////矩形の当たり判定を可視化、ヘッダファイル[visible_rect.h]
////Author：福田歩希
////
////************************************************
//#ifndef _VISIBLE_RECT_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
//#define _VISIBLE_RECT_H_	//(二重インクルード防止、マクロ定義する)
//
//#include "main.h"
//
////レクト構造体
//struct Rect
//{
//	bool bUse;	//使用判定
//	D3DXVECTOR3 pos;	//位置
//	D3DXVECTOR3* pPos;	//追従対象の位置
//	D3DXCOLOR col;	//色
//	D3DXMATRIX mtxWorld;	//ワールドマトリックス
//};
//
////プロトタイプ宣言
//void InitVisible_Rect(void);	//初期
//void SetSizeVisible_Rect(const COLLISION_AABB obj, D3DXCOLOR col, D3DXVECTOR3* pPos);	//展開
//void UninitVisible_Rect(void);	//破棄
//void UpdateVisible_Rect(void);	//更新
//void DrawVisible_Rect(void);	//描画
//
//#endif