//=========================================================
//ポーズの処理・ヘッダファイル[pause.h]
//Author:Yumika Matsushita
//
//=========================================================

//=====================================
//マクロ定義
//=====================================
#ifndef _PAUSE_H_	//このマクロ定義がされてなかったら
#define _PAUSE_H_	//2重インクルード防止のマクロ定義

//=====================================
//インクルード
//=====================================
#include "main.h"

//ポーズ画面のテクスチャの列挙型
typedef enum
{
	TEXTYPE_RETRY = 0,	// リトライ
	TEXTYPE_CONTINUE,	// コンティニュー
	TEXTYPE_QUIT,		// エンド
	TEXTYPE_MAX
}TEXTURETYPE;

//ポーズのモードの列挙型
typedef enum
{
	PAUSEMODE_RETRY = 0,	// リトライ
	PAUSEMODE_CONTINUE,		// コンティニュー
	PAUSEMODE_QUIT,			// エンド
	PAUSEMODE_MAX
}PAUSEMODE;

//=====================================
//ポーズ画面のモード選択(MD == Mode)ポリゴンの構造体
//=====================================
typedef struct
{
	D3DXVECTOR3 pos;	//動き(普通)
	int nType;			//モードの種類
	bool bUse;			//使用の有無
	bool bColUse;		//ポリゴンのカラーの有無
}PauseMD;

//=====================================
//ポーズ画面の操作方法(OI == OperationInstructions)ポリゴンの構造体
//=====================================
typedef struct
{
	D3DXVECTOR3 pos;	//動き(普通)
	bool bUse;			//使用の有無
}PauseOI;

//=====================================
//ポーズ画面の矢印(MA == MovingArrow)ポリゴンの構造体
//=====================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置(普通)
	D3DXVECTOR3 move;	//動き(普通)
	int nType;			//モードの種類
	bool bUse;			//使用の有無
	bool bColUse;		//ポリゴンのカラーの有無
}PauseMA;

//=====================================
//マクロ定義
//=====================================


//=====================================
//プロトタイプ宣言(処理)
//=====================================
void InitPause(void);									// 統合されてるInitの処理
void UninitPause(void);									// 統合されてるUninitの処理
void UpdatePause(void);									// 統合されてるUpdateの処理
void DrawPause(void);									// 統合されてるDrawの処理

void InitPauseBackGroundPolygon(void);					// 背景のポリゴンの初期化処理
void InitPauseOperationInstructionsPolygon(void);		// 操作方法のポリゴンの初期化処理
void InitPauseModePolygon(void);						// モード選択のポリゴンの初期化処理
void InitPauseMovingArrowPolygon(void);					// 動く矢印のポリゴンの初期化処理

void UninitPauseBackGroundPolygon(void);				// 背景のポリゴンの終了処理
void UninitPauseOperationInstructionsPolygon(void);		// 操作方法のポリゴンの終了処理
void UninitPauseModePolygon(void);						// モード選択のポリゴンの終了処理
void UninitPauseMovingArrowPolygon(void);				// 動く矢印のポリゴンの終了処理

void UpdatePauseBackGroundPolygon(void);				// 背景のポリゴンの更新処理
void UpdatePauseOperationInstructionsPolygon(void);		// 操作方法のポリゴンの更新処理
void UpdatePauseModePolygon(void);						// モード選択のポリゴンの更新処理
void UpdatePauseMovingArrowPolygon(void);				// 動く矢印のポリゴンの更新処理

void DrawPauseBackGroundPolygon(void);					// 背景のポリゴンの描画処理
void DrawPauseOperationInstructionsPolygon(void);		// 操作方法のポリゴンの描画処理
void DrawPauseModePolygon(void);						// モード選択のポリゴンの描画処理
void DrawPauseMovingArrowPolygon(void);					// 動く矢印のポリゴンの描画処理

void SetPauseMode(D3DXVECTOR3 pos);						// モード選択のポリゴンの設置処理
void SetPauseOperationInstructions(D3DXVECTOR3 pos);	// 操作方法のポリゴンの設置処理
void SetPauseMovingArrow(D3DXVECTOR3 pos);				// 動く矢印のポリゴンの設置処理

void SelectMode(void);									// ポーズ中のモード選択
#endif