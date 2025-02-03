////************************************************
////
////球形の当たり判定を可視化、ヘッダファイル[visible_sphere.h]
////Author：福田歩希
////
////************************************************
//#ifndef _VISIBLE_SPHERE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
//#define _VISIBLE_SPHERE_H_	//(二重インクルード防止、マクロ定義する)
//
//#include "main.h"
//
////スフィア構造体
//struct Sphere
//{
//	bool bUse;	//使用判定
//	D3DXVECTOR3 pos;	//位置
//	D3DXVECTOR3* pPos;	//追従対象の位置
//	D3DXCOLOR col;	//色
//	D3DXMATRIX mtxWorld;	//ワールドマトリックス
//};
//
////プロトタイプ宣言
//void InitVisible_Sphere(void);	//初期
//void SetSizeVisible_Sphere(const float fRadius, D3DXCOLOR col, D3DXVECTOR3* pPos);	//展開
//void UninitVisible_Sphere(void);	//破棄
//void UpdateVisible_Sphere(void);	//更新
//void DisappearVisible_Sphere(D3DXVECTOR3* pPos);	//消滅
//void DrawVisible_Sphere(void);	//描画
//
//#endif