//************************************************
//
//ジェニーゲニー[main.cpp]
//Author：福田歩希
//
//************************************************
#include "input.h"
#include "main.h"
#include "sound.h"
#include "player.h"

//マクロ定義
#define CLASS_NAME	"WindowClass"		//ウインドウクラスの名前
#define WINDOW_NAME	"ジェニーゲニー"	//ウインドウの名前
#define MAX_WORD	(512)				//表示文字数の最大

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
/*DirectX描画用*/
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindiw);	//初期化処理
void UnInit(void);	//終了処理
void Update(void);	//更新処理
void Draw(void);	//描画処理
void DrawFPS(void);	//FPS表示処理

//グローバル変数を定義
LPDIRECT3D9 g_pD3D = NULL;				//Direct3Dオブジェクトのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3Dデバイスのポインタ
MODE g_mode;							//現在のモードが入る
bool bExit = false;						//終了判定
int g_nMode = 0;
int g_nHoldLastScore = 0;

/*デバッグ表示用*/
LPD3DXFONT g_pFont = NULL;	//フォントのポインタ
int g_nCountFPS = 0;		//FPSカウンタ

//デバイスの取得
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//************************************************
//メイン関数
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

		case VK_RETURN:	//ENTERキーが押されると

			if (bExit == true)
			{
				DestroyWindow(hWnd);
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
//初期化処理関数
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

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャステージステートの設定？(コピペ)
    g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//コントローラの初期化処理
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//デバッグ表示用フォントの生成
	    D3DXCreateFont(g_pD3DDevice, 25, 0, 0, 0,
        FALSE, SHIFTJIS_CHARSET,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
        "Terminal", &g_pFont);

	g_mode = MODE_TITLE;

	//サウンドの初期化処理
	InitSound(hWnd);

	//モードの初回設定
	Setinfo_Mode(g_mode);

	return S_OK;
}

//************************************************
//終了処理関数
//************************************************
void UnInit(void)
{
	//分解能を戻す(これはUninit内で一番上に)
	timeEndPeriod(1);

	//処理群の初期化
	Uninit_Title();
	Uninit_Menu();
	Uninit_Tutorial();
	Uninit_Ranking();
	Uninit_Game();
	Uninit_Result();

	//キーボードの終了処理
	UnInitKeyboard();

	//コントローラの終了処理
	UninitJoypad();

	//サウンドの終了処理
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

	//デバッグ表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update(void)
{
	//キーボードの更新処理
	UpdateKeyboard();

	//コントローラの更新処理
	UpdateJoypad();

	//モードに合わせて画面更新処理
	switch (g_mode)
	{
		//タイトルモードの時
	case MODE_TITLE:

		Update_Title();

		break;

		//メニューモードの時
	case MODE_MENU:

		Update_Menu();

		break;

		//チュートリアルモードの時
	case MODE_TUTORIAL:

		Update_Tutorial();

		break;

		//ランキングモードの時
	case MODE_RANKING:

		Update_Ranking();

		break;

		//ゲームモードの時
	case MODE_GAME:

		Update_Game();

		break;

		//リザルトモードの時
	case MODE_RESULT:

		Update_Result();

		break;
	}
}

//************************************************
//描画処理関数
//************************************************
void Draw(void)
{
	//画面クリア(バックバッファとなんかバッファのクリア)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//モードに合わせて画面描画処理
		switch (g_mode)
		{
			//タイトルモードの時
		case MODE_TITLE:

			Draw_Title();

			break;

			//メニューモードの時
		case MODE_MENU:

			Draw_Menu();

			break;

			//チュートリアルモードの時
		case MODE_TUTORIAL:

			Draw_Tutorial();

			break;

			//ランキングモードの時
		case MODE_RANKING:

			Draw_Ranking();

			break;

			//ゲームモードの時
		case MODE_GAME:

			Draw_Game();

			break;

			//リザルトモードの時
		case MODE_RESULT:

			Draw_Result();

			break;
		}

//#ifdef _DEBUG
//
//		//FPSの描画
//		DrawFPS();
//
//#endif // DEBUG

		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//************************************************
//FPS表示処理関数
//************************************************
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[MAX_WORD];

	//プレイヤー情報へのポインタ
	PLAYER* pPlayer;

	//プレイヤー情報の取得
	pPlayer = Getinfo_Player();	//プレイヤー情報系の先頭アドレスが代入される

	//文字列に代入
	wsprintf(&aStr[0], "FPS：%d\n\n[W]：上移動\n[A]：左移動\n[S]：下移動\n[D]：右移動\n\n[← / →]：射撃スタイル変更\n\n[1]：スコア + 1点\n[2]：スコア + 20点\n[3]：スコア + 300点\n\n[4]：ライフ - 1\n[5]：ライフ + 1\n[6]：無敵 / 無敵解除\n\n[7]：タイマー - 1秒\n[8]：タイマー + 1秒\n[9]：タイマーストップ / ストップ解除\n\n[0]：タイトルで即ゲーム開始\n\n[SPACE]：射撃\n\n[P]：ポーズメニュー\n\n[ESC]：終了\n\nキャパシティ：%d\n\n[X]：キャパシティ無限 / 無限解除", g_nCountFPS, pPlayer->nCapacity);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//************************************************
//モード変更処理関数
//************************************************
void Setinfo_Mode(MODE mode)
{
	//まずは現在のモードの終了処理
	switch (g_mode)
	{
		//タイトルモードの時
	case MODE_TITLE:

		Uninit_Title();

		break;

		//メニューモードの時
	case MODE_MENU:

		Uninit_Menu();

		g_nMode = 0;

		break;

		//チュートリアルモードの時
	case MODE_TUTORIAL:

		Uninit_Tutorial();

		break;

		//ランキングモードの時
	case MODE_RANKING:

		Init_Ranking(g_nMode);

		break;

		//ゲームモードの時
	case MODE_GAME:

		Uninit_Game();

		g_nMode = 1;

		break;

		//リザルトモードの時
	case MODE_RESULT:

		Uninit_Result();

		break;
	}

	//次に変更先のモードを初期化
	switch (mode)
	{
		//タイトルモードの時
	case MODE_TITLE:

		Init_Title();

		break;

		//メニューモードの時
	case MODE_MENU:

		Init_Menu();

		break;

		//チュートリアルモードの時
	case MODE_TUTORIAL:

		Init_Tutorial();

		break;

		//ランキングモードの時
	case MODE_RANKING:

		Init_Ranking(g_nMode);

		break;

		//ゲームモードの時
	case MODE_GAME:

		Init_Game();

		break;

		//リザルトモードの時
	case MODE_RESULT:

		Init_Result();

		break;
	}

	g_mode = mode;	//現在のモードを上書き
}

//************************************************
//現在のモードを取得する関数(未使用)
//************************************************
MODE Getinfo_Mode(void)
{
	return g_mode;	//現在のモードを引き渡す
}

//************************************************
//ゲーム終了処理
//************************************************
bool* Getinfo_End(void)
{
	return &bExit;	//現在のモードを引き渡す
}

//************************************************
//スコア記録処理
//************************************************
int* Getinfo_HoldLastScore(void)
{
	return &g_nHoldLastScore;
}

/*やること*/
//先輩よりすごいもの作れ