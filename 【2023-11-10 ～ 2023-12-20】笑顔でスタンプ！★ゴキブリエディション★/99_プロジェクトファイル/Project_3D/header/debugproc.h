//==========================================================
//
//デバッグ表示処理 [debugproc.h]
//Author Ibuki Okusada
//
//==========================================================
#ifndef _DEBUGPROC_H_		//このマクロが定義されていない場合
#define _DEBUGPROC_H_

//**********************************************************
//スイッチ列挙型の定義
//**********************************************************
typedef enum
{
	DEBUGTYPE_OFF = 0,	//対象機能が動作していない状態
	DEBUGTYPE_ON,		//対象機能が動作している状態
	DEBUGTYPE_MAX
}DEBUGTYPE;

//**********************************************************
//プロトタイプ宣言
//**********************************************************
void InitDebugProc(void);
void UninitDebugProc(void);
void UpdateDebugProc(void);
void DrawDebugProc(void);
void PrintDebugProc(const char *fmt, ...);

#endif