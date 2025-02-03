//============================================================================
// 
// 2Dアクションゲーム、メイン [main.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "main.h"
#include "manager.h"

// デバッグ表示用
#include "renderer.h"

// メモリリーク検出用
#include <crtdbg.h>
#include <stdlib.h>

//****************************************************
// マクロ定義
//****************************************************
#define CLASS_NAME	"WindowClass"	// ウィンドウクラスの名前
#define WINDOW_NAME	"METAMOl"		// ウィンドウの名前

// メモリリーク検出用
#define _CRTDBG_MAP_ALLOC

//****************************************************
// グローバル宣言
//****************************************************
CManager* g_pManager = nullptr;	// マネージャー管理

//****************************************************
// プロトタイプ宣言
//****************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャ
void ChangeWindowSize(HWND hWnd);													// ウィンドウサイズの変更

//****************************************************************************
// メイン関数
//****************************************************************************
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// CRTメモリリーク検出用
	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				// WNDCLASSEXのメモリサイズ
		CS_CLASSDC,						// ウィンドウのスタイル
		WindowProc,						// ウィンドウプロシージャ
		0,								// 何かを0にする
		0,								// 何かを0にする
		hInstance,						// インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),	// タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),		// マウスカーソル
		(HBRUSH)(COLOR_WINDOW),			// クライアント領域の背景色
		NULL,							// メニューバー
		CLASS_NAME,						// ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)	// ファイルのアイコン
	};

	HWND hWnd;	// ウィンドウハンドル(識別子)
	MSG msg;	// メッセージを格納する変数

	// 画面サイズの設定用
	RECT rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウを生成
	hWnd = CreateWindowEx(0,	// 拡張ウィンドウのスタイル
		CLASS_NAME,				// ウィンドウクラスの名前
		WINDOW_NAME,			// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	// ウィンドウのスタイル
		125,					// ウィンドウの左上のX座標
		50,						// ウィンドウの左上のY座標
		SCREEN_WIDTH,			// ウィンドウの幅
		SCREEN_HEIGHT,			// ウィンドウの高さ
		NULL,					// 親ウィンドウのハンドル
		NULL,					// メニューバーまたは子ウィンドウID
		hInstance,				// インスタンスハンドル
		NULL);					// ウィンドウ作成データ

	// ウィンドウの表示
	ShowWindow(hWnd, SW_NORMAL);	// ウィンドウの表示状態を設定
	UpdateWindow(hWnd);				// クライアント領域を更新
	ChangeWindowSize(hWnd);			// ウィンドウサイズの変更

	// マネージャーの生成
	g_pManager = DBG_NEW CManager;

	if (g_pManager == nullptr)
	{ // 生成失敗
		return -1;
	}

	if (FAILED(g_pManager->Init(hInstance, hWnd, TRUE)))
	{ // 初期化処理が失敗した場合
		return -1;
	}

	// 分解能を設定
	timeBeginPeriod(1);

	// FPS計測用
	int nCountFPS = 0;						// 現在のFPS
	DWORD dwCurrentTime = 0;				// 現在時刻用
	DWORD dwFrameCount = 0;					// 最後に処理した時間
	DWORD dwExecLastTime = timeGetTime();	// フレームカウント格納
	DWORD dwFPSLastTime = timeGetTime();	// 最後にFPSを計測した時刻格納

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			// Windowsの処理
			if (msg.message == WM_QUIT)
			{
				// WM_QUITのメッセージを受け取ると、メッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);	// 仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);	// ウィンドウプロシージャへメッセージを創出
			}
		}
		else
		{
			// 現在時刻を取得
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				// FPSを計測
				nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				// FPSを計測した時間を保存
				dwFPSLastTime = dwCurrentTime;

				// フレームカウントをクリア
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				// 現在時刻を保存
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				g_pManager->Update();

#ifdef _DEBUG
				// FPS表示
				CRenderer::GetInstance()->SetDebugString("FPS:" + std::to_string(nCountFPS));
#endif	// _DEBUG

				// 描画処理
				g_pManager->Draw();

				// フレームカウントを加算
				dwFrameCount++;
			}
		}
	}

	// 分解能を戻す
	timeEndPeriod(1);

	// マネージャーの破棄
	if (g_pManager != nullptr)
	{
		g_pManager->Uninit();	// 終了処理
		delete g_pManager;		// メモリを解放
		g_pManager = nullptr;	// ポインタを初期化
	}

	// CRTメモリリーク箇所検出
	//_CrtSetBreakAlloc();

	return (int)msg.wParam;
}

//****************************************************************************
// ウィンドウプロシージャ関数
//****************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 返り値格納先
	int nID;

	switch (uMsg)
	{
		// ウィンドウ破棄のメッセージを送る
	case WM_DESTROY:

		PostQuitMessage(0);

		break;

		// ×マークを押しているメッセージを送る
	case WM_CLOSE:

		// メッセージボックスを表示
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION);

		if (nID == IDYES)
		{
			DestroyWindow(hWnd);	// 「WM_DESTROYというメッセージを送る」
		}
		else
		{
			return 0;
		}

		break;

		// キーが押されているメッセージを送る
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:

			// メッセージボックスを表示
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);	// 「WM_DESTROYというメッセージを送る」
			}

			break;

		case VK_F11:

			// ウィンドウサイズの変更
			ChangeWindowSize(hWnd);

			break;
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// 既定の処理を返す
}

//****************************************************************************
// ウィンドウサイズの変更
//****************************************************************************
void ChangeWindowSize(HWND hWnd)
{
	// モード変更フラグ
	static bool bSetFullScreen{ false };

	// ウィンドウサイズ保持用
	static RECT windowRectHold{ 0, 0, 0, 0 };

	// 現在のウィンドウスタイルを取得
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	// モード変更
	bSetFullScreen = !bSetFullScreen;

	if (bSetFullScreen)
	{ // フルスクリーンモードに切り替え

		// 現在のウィンドウサイズを保持する
		GetWindowRect(hWnd, &windowRectHold);

		// ウィンドウの表示スタイルを変更する
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);

		// ウィンドウのサイズを変更する
		SetWindowPos(hWnd, HWND_TOP,
			0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
	}
	else
	{ // ウィンドウモードに切り替え

		// ウィンドウの表示スタイルを変更する
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);

		// ウィンドウのサイズを変更する
		SetWindowPos(hWnd, HWND_TOP,
			windowRectHold.left, windowRectHold.top, windowRectHold.right - windowRectHold.left, windowRectHold.bottom - windowRectHold.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
	}
}