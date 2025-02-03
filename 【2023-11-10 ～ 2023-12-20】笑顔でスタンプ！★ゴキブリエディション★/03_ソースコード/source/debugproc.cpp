//==========================================================
//
// デバッグ表示処理 [debugproc.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "main.h"
#include "debugproc.h"
#include <string.h>
#include <stdio.h>
#include "input.h"

//**********************************************************
//マクロ定義
//**********************************************************
#define MAX_DEBUGSTRING	(5096)	//デバッグ表示の最大文字数
#define MAX_FLOATNUM	(2)		//小数点以下の表示桁数

//**********************************************************
//グローバル変数
//**********************************************************
LPD3DXFONT g_pFont = NULL;	//フォントへのポインタ
char g_aStrDebug[MAX_DEBUGSTRING];	//デバッグ表示用の文字列
bool g_bDispDebug = false;	//デバッグ表示のON/OFF

//**********************************************************
//プロトタイプ宣言
//**********************************************************
void SetManual(void);

//**********************************************************
//デバッグONOFF表示メッセージ
//**********************************************************
const char *c_apOnOff[DEBUGTYPE_MAX] =
{
	"OFF",
	"ON",
};

//**********************************************************
//デバッグONOFF表示メッセージ
//**********************************************************
const char *c_apMode[MODE_MAX] =
{
	"タイトル",
	"メニュー",
	"チュートリアル",
	"ランキング",
	"ゲーム",
	"リザルト",
};

//==========================================================
//デバッグ表示の初期化処理
//==========================================================
void InitDebugProc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスへのポインタを取得

													//デバッグ表示用フォントの生成
	D3DXCreateFont(pDevice, 25, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Tarminal", &g_pFont);

	//デバッグ表示情報のクリア
	memset(&g_aStrDebug[0], NULL, sizeof(g_aStrDebug));

	//初期表示設定
#if _DEBUG
	g_bDispDebug = true;
#else NDEBUG
	g_bDispDebug = false;
#endif
}

//==========================================================
//デバッグ表示の終了処理
//==========================================================
void UninitDebugProc(void)
{
	//デバッグ表示用フォントの廃棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//==========================================================
//デバッグ表示の更新処理
//==========================================================
void UpdateDebugProc(void)
{
	//操作説明設定
	SetManual();

	if (GetKeyboardTrigger(DIK_F1) == true)
	{//F1キーが押されたとき
		g_bDispDebug = g_bDispDebug ? false : true;
	}
}

//==========================================================
//デバッグ表示の描画処理
//==========================================================
void DrawDebugProc(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	if (g_bDispDebug == true)
	{//デバックモードがオンの時
	 //テキストの描画
		g_pFont->DrawText(NULL, &g_aStrDebug[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(100, 255, 100, 255));
	}

	//デバッグ表示情報のクリア
	memset(&g_aStrDebug[0], NULL, sizeof(g_aStrDebug));
}

//==========================================================
//デバッグ表示の設定処理
//==========================================================
void PrintDebugProc(const char *fmt, ...)
{
	va_list args;
	char aString[MAX_DEBUGSTRING];
	char aSaveString[MAX_DEBUGSTRING];
	int nLength;
	int nStopLength;

	//文字列の代入
	strcpy(&aString[0], fmt);

	va_start(args, fmt);

	for (char *p = &aString[0]; *p != '\0'; p++)
	{
		if (*p == '%')
		{//確認文字がある場合
			p++;	//確認文字まで進める

			switch (*p)
			{
			case 'd':	//数字
				sprintf(&aSaveString[0], "%d", va_arg(args, int));

				//文字列の長さを取得
				nLength = (int)strlen(&aSaveString[0]);
				break;
			case 'f':	//小数
				sprintf(&aSaveString[0], "%f", va_arg(args, double));

				//文字列の長さを取得
				nLength = (int)strlen(&aSaveString[0]);

				//小数点以下の文字目まで確認
				for (int nCntlength = 0; aSaveString[nCntlength] != '\0'; nCntlength++)
				{
					if (aSaveString[nCntlength] == '.')
					{//小数点があった場合

					 //小数点以下の桁数を求める
						int nMin = (int)strlen(&aSaveString[nCntlength + 1]);

						//小数点より先の文字数と指定した値までの差分を求める
						nMin -= MAX_FLOATNUM;

						//文字列の長さを小数点以下第二位までに補正
						nLength -= nMin;
					}
				}

				break;
			case 'c':	//文字
				sprintf(&aSaveString[0], "%c", va_arg(args, char));

				//文字列の長さを取得
				nLength = (int)strlen(&aSaveString[0]);
				break;
			case 's':	//文字列
				sprintf(&aSaveString[0], "%s", va_arg(args, const char*));

				//文字列の長さを取得
				nLength = (int)strlen(&aSaveString[0]);
				break;
			}

			nStopLength = (int)strlen(p) + 1;
			//メモリ内の確認文字より後ろの文字列をずらす
			memmove(p + nLength - 2, p, nStopLength);

			p--;	//ポインタを%まで戻す

					//可変引数を指定された場所に挿入
			memcpy(p, &aSaveString[0], nLength);
		}
	}

	va_end(args);

	//文字列を連結する
	strcat(&g_aStrDebug[0], &aString[0]);

}

//==========================================================
//表示するテキスト設定
//==========================================================
void SetManual(void)
{
	//デバッグ変更とFPS
	PrintDebugProc("【デバッグ表示】【F1】【FPS】 %d\n", GetFPS());
	PrintDebugProc("【現在の画面】[%s]\n", c_apMode[GetInfoMode()]);
}