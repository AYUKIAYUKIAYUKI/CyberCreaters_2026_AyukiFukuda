////************************************************
////
//// オリジナルエフェクト、ヘッダファイル[effect_hayu.h]
//// Author：福田歩希
////
////************************************************
//#ifndef _EFFECT_HAYU_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
//#define _EFFECT_HAYU_H_	// (二重インクルード防止、マクロ定義する)
//
///*/ インクルードファイル /*/
//#include "main.h"
//
//// エフェクトの種類分け
//typedef enum
//{
//	styleHeart = 0,		// ハート：ダメージ的な
//	styleSoul,			// 魂：昇天する
//	styleRing,			// リング：床に
//	styleHaze,			// 煙：まとう
//	styleSmoke,			// 煙：視界遮るレベル
//	Max_effectstyle
//}EffectStyle;
//
//// テクスチャサイズ管理用
//typedef struct
//{
//	D3DXVECTOR2 size[4];	// サイズ情報格納用
//}TextureSize;
//
//// テクスチャアニメーション用
//typedef struct
//{
//	int row;		// 行総数
//	int column;		// 列総数
//	int id_pattern;	// 現在のパターン
//	int dur_cnt;	// パターン遷移間隔
//	int id_cnt;		// 遷移カウンター
//}TextureAnimation;
//
//// エフェクト用情報
//typedef struct
//{
//	bool use;				// 使用フラグ
//	int style;				// スタイル
//	int type;				// タイプ
//	D3DXVECTOR3* pPos;		// 対象位置
//	D3DXVECTOR3 pos_moved;	// 変動位置
//	D3DXVECTOR3 pos;		// 位置
//	D3DXVECTOR3 rot;		// 向き
//	D3DXVECTOR2 span;		// 大きさ用
//	float angle;			// 角度
//	float length;			// 対角線用
//	D3DXCOLOR col;			// 色
//	int remain;				// 寿命
//	TextureAnimation anima;	// アニメーション用
//	D3DXMATRIX mtxWorld;	// ワールドマトリックス
//}Effect_Hayu;
//
////プロトタイプ宣言
//void InitEffect_Hayu(void);				// 初期
//void ImportTexEffect_Hayu(void);		// テクスチャ取得
//void CreateVtxBufferEffect_Hayu(void);	// 頂点情報を生成
//
//void UninitEffect_Hayu(void);	// 破棄
//
//int CreateEffect_Hayu(int type, D3DXVECTOR3* pPos);	// 生成
//void UpdateEffect_Hayu(void);						// 更新
//void SetVtxEffect_Hayu(void);						// 展開
//
//void AnimationManager_Hayu(int id);	// アニメーション動作管理用
//void Animation_Heart_Hayu(int id);	// ハート：アニメーション動作用
//void Animation_Soul_Hayu(int id);	// 魂：アニメーション動作用
//void Animation_Haze_Hayu(int id);	// 煙：アニメーション動作用
//void Animation_Smoke_Hayu(int id);	// 煙：アニメーション動作用
//
//TextureSize SetTexEffect_Hayu(int id);	// テクスチャ管理用
//TextureSize SetTexEffect_Hayu(int id);	// テクスチャ管理用
//void AnimationCnt_Heart_Hayu(int id);	// ハート：テクスチャカウント用
//void AnimationCnt_Ring_Hayu(int id);	// リング：テクスチャカウント用
//
//void DeleteEffect_Hayu(int id);	// 消去
//
//void DrawEffect_Hayu(void);	// 描画
//
//#endif