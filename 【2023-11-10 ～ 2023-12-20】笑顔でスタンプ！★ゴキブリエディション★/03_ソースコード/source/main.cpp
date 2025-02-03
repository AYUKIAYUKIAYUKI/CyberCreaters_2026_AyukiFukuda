//************************************************
//
//メイン[main.cpp]
//Author：福田歩希
//
//************************************************

//インクルード
#include "main.h"
#include <assert.h>

#include "debugproc.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

#include "title.h"
#include "tutorial.h"
#include "ranking.h"
#include "game.h"
#include "result.h"

//マクロ定義
#define CLASS_NAME	"WindowClass"		//ウインドウクラスの名前
#define WINDOW_NAME	"笑顔でスタンプ！★ゴキブリエディション★"	//ウインドウの名前
#define MAX_WORD	(1024)				//文字の最大数

//グローバル宣言
LPDIRECT3D9 g_pD3D = NULL;				//Direct3Dオブジェクトのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3Dデバイスのポインタ
int g_nCountFPS = 0;		//FPSカウンタ
LONG g_rectUP = 0;			//レクトの上
bool g_WireFrame = false;	//ワイヤーフレーム描画のスイッチ
MODE g_mode = MODE_TITLE;	//現在のモード
bool g_bExit = false;		//終了判定

//************************************************
//メイン
//************************************************
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DWORD dwCurrentTime;	//現在時刻用
	DWORD dwExecLastTime;	//最後に処理した時間
	DWORD dwFrameCount;		//フレームカウント格納
	DWORD dwFPSLastTime;	//最後にFPSを計測した時刻格納

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,						//ウインドウのスタイル
		WindowProc,						//ウインドウプロシージャ
		0,								//何かを0にする
		0,								//何かを0にする
		hInstance,						//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),	//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),		//マウスカーソル
		(HBRUSH)(COLOR_WINDOW),			//クライアント領域の背景色
		NULL,							//メニューバー
		CLASS_NAME,						//ウインドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)	//ファイルのアイコン
	};

	HWND hWnd;	//ウインドウハンドル(識別子)
	MSG msg;	//メッセージを格納する変数

	//画面サイズの構造体
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウインドウを生成
	hWnd = CreateWindowEx(0,		//拡張ウインドウのスタイル
		CLASS_NAME,					//ウインドウクラスの名前
		WINDOW_NAME,				//ウインドウの名前
		WS_OVERLAPPEDWINDOW,		//ウインドウのスタイル
		CW_USEDEFAULT,				//ウインドウの左上のX座標
		CW_USEDEFAULT,				//ウインドウの左上のY座標
		(rect.right - rect.left),	//ウインドウの左上の幅
		(rect.bottom - rect.top),	//ウインドウの左上の高さ
		NULL,						//親ウインドウのハンドル
		NULL,						//メニューバーまたは子ウインドウID
		hInstance,					//インスタンスハンドル
		NULL);						//ウインドウ作成データ

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		//初期化処理が失敗した場合
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);

	//初期化
	dwCurrentTime = 0;
	dwFrameCount = 0;

	//現在時刻を取得
	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();

	//ウインドウの表示
	ShowWindow(hWnd, SW_MAXIMIZE);	//ウインドウの表示状態を設定
	UpdateWindow(hWnd);				//クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			//Windowsの処理
			if (msg.message == WM_QUIT)
			{
				//WM_QUITのメッセージを受け取ると、メッセージループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);	//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);	//ウインドウプロシージャへメッセージを創出
			}
		}
		else
		{
			//現在時刻を取得
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				//FPSを計測した時間を保存
				dwFPSLastTime = dwCurrentTime;

				//フレームカウントをクリア
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				//現在時刻を保存
				dwExecLastTime = dwCurrentTime;

				Draw();		//描画処理

				Update();	//更新処理

				if (g_bExit) break;

				//フレームカウントを加算
				dwFrameCount++;
			}
		}
	}

	//終了処理
	UnInit();

	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//************************************************
//ウインドウプロシージャ
//************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*宣言*/
	int nID;			//返り値受け皿
	switch (uMsg)
	{
	case WM_CREATE:	//ウインドウ生成のメッセージを送る

		break;

	case WM_DESTROY:	//ウインドウ破棄のメッセージを送る

		PostQuitMessage(0);	//「WM_QUIT」というメッセージを送る

		break;

	case WM_KEYDOWN:	//キーが押されているメッセージを送る

		switch (wParam)
		{
		case VK_ESCAPE:	//ESCキーが押されると

			//メッセージボックスを表示
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);	//「WM_DESTROYというメッセージを送る」
			}

			break;
		}

		break;

	case WM_COMMAND:

		break;

	case WM_LBUTTONDOWN:

		SetFocus(hWnd);

		break;

	case WM_CLOSE:

		//メッセージボックスを表示
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION);

		if (nID == IDYES)
		{
			DestroyWindow(hWnd);	//「WM_DESTROYというメッセージを送る」
		}
		else
		{
			return 0;
		}

		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//既定の処理を返す
}

//************************************************
//初期
//************************************************
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindiw)
{
	D3DDISPLAYMODE d3ddm;			//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));	//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						//ゲームサイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						//ゲームサイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						//バックバッファの形式
	d3dpp.BackBufferCount = 1;									//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;						//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindiw;									//ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//インターバル

	//Direct3Dデバイスの生成1
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成2
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3Dデバイスの生成3
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャステージステートの設定？(コピペ)
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//キーボードの初期
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//コントローラの初期
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//デバッグ表示の初期(配布)
	InitDebugProc();

	//フェードの初期
	InitFade();

	//サウンドの初期化処理
	InitSound(hWnd);

	//モードの初回初期
	SetInfoMode(g_mode);

	return S_OK;
}

//************************************************
//破棄
//************************************************
void UnInit(void)
{
	//分解能を戻す(これはUninit内で一番上に)
	timeEndPeriod(1);

	//デバッグ表示の終了(配布)
	UninitDebugProc();

	//フェードの終了
	UninitFade();

	//キーボードの破棄
	UnInitKeyboard();

	//コントローラの破棄
	UninitJoypad();

	//サウンドの終了
	UninitSound();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//************************************************
//更新
//************************************************
void Update(void)
{
	//デバッグ表示の更新(配布)
	UpdateDebugProc();

	//世界をワイヤーフレーム描画
	if (GetKeyboardTrigger(DIK_F4)) g_WireFrame = !g_WireFrame;

	//キーボードの更新
	UpdateKeyboard();

	//コントローラの更新
	UpdateJoypad();

	//フェードの更新
	UpdateFade();

	//モードに合わせて更新
	switch (g_mode)
	{
		//タイトルモード
	case MODE_TITLE:
		UpdateTitle();
		break;

		//チュートリアルモード
	case MODE_TUTORIAL:
		UpdateTutorial();
		break;

		//ランキングモード
	case MODE_RANKING:
		UpdateRanking();
		break;

		//ゲームモード
	case MODE_GAME:
		UpdateGame();
		break;

		//リザルトモード
	case MODE_RESULT:
		UpdateResult();
		break;

		//モード外アクセス
	default:
		assert(false);
		break;
	}
}

//************************************************
//描画
//************************************************
void Draw(void)
{
	//画面クリア
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		g_WireFrame ? g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME) :
			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		//モードに合わせて描画
		switch (g_mode)
		{
			//タイトルモード
		case MODE_TITLE:
			DrawTitle();
			break;

			//チュートリアルモード
		case MODE_TUTORIAL:
			DrawTutorial();
			break;

			//ランキングモード
		case MODE_RANKING:
			DrawRanking();
			break;

			//ゲームモード
		case MODE_GAME:
			DrawGame();
			break;

			//リザルトモード
		case MODE_RESULT:
			DrawResult();
			break;

			//モード外アクセス
		default:
			assert(false);
			break;
		}

		//フェードの描画
		DrawFade();

		//デバッグ用表示の描画(配布)
		DrawDebugProc();

		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//************************************************
//デバイスの取得
//************************************************
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//************************************************
//レクトの上端取得
//************************************************
LONG* GetInfoRectUP(void)
{
	return &g_rectUP;
}

//************************************************
//FPSの取得
//************************************************
int GetFPS(void)
{
	return g_nCountFPS;
}

//************************************************
//モード変更処理関数
//************************************************
void SetInfoMode(MODE mode)
{
	//まずは現在のモード終了
	switch (g_mode)
	{
		//タイトルモード
	case MODE_TITLE:
		UninitTitle();
		break;

		//チュートリアルモード
	case MODE_TUTORIAL:
		UninitTutorial();
		break;

		//ランキングモード
	case MODE_RANKING:
		UninitRanking();
		break;

		//ゲームモード
	case MODE_GAME:
		UninitGame();
		break;

		//リザルトモード
	case MODE_RESULT:
		UninitResult();
		break;

		//モード外アクセス
	default:
		assert(false);
		break;
	}

	//次に変更先のモード初期
	switch (mode)
	{
		//タイトルモード
	case MODE_TITLE:
		InitTitle();
		break;

		//チュートリアルモード
	case MODE_TUTORIAL:
		InitTutorial();
		break;

		//ランキングモード
	case MODE_RANKING:
		InitRanking();
		break;

		//ゲームモード
	case MODE_GAME:
		InitGame();
		break;

		//リザルトモード
	case MODE_RESULT:
		InitResult();
		break;

		//エンドモード
	case MODE_END:
		g_bExit = true;
		break;

		//モード外アクセス
	default:
		assert(false);
		break;
	}

	g_mode = mode;	//現在のモードを上書き
}

//************************************************
//現在のモードの取得
//************************************************
MODE GetInfoMode(void)
{
	return g_mode;
}

//************************************************
//ゲーム終了処理
//************************************************
bool* GetInfoEnd(void)
{
	return &g_bExit;
}