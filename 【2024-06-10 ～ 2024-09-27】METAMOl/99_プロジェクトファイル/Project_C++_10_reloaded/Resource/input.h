//============================================================================
// 
// 入力処理管理、ヘッダファイル [input.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _INPUT_H_
#define _INPUT_H_	// 二重インクルード防止

//****************************************************
// マクロ定義
//****************************************************
#define MAX_KEY	256	// キー最大数

// プリプロセッサディレクティブ
#define LEFT_JOYSTICK_CONVERT 0	// 左スティック入力を変換

//****************************************************
// インプットクラス
//****************************************************
class CInput
{
public:

	CInput();	// デフォルトコンストラクタ
	~CInput();	// デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期設定
	virtual void Uninit();		// 終了処理
	virtual void Update() = 0;	// 更新処理

protected:

	static LPDIRECTINPUT8 m_Input;	// DirectInputオブジェクト
	LPDIRECTINPUTDEVICE8 m_pDevice;	// 入力デバイス情報
};

//****************************************************
// キーボードクラス
//****************************************************
class CInputKeyboard : public CInput
{
public:

	CInputKeyboard();	// デフォルトコンストラクタ
	~CInputKeyboard();	// デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;	// 初期設定
	void Uninit() override;	// 終了処理
	void Update() override;	// 更新処理

	bool GetPress(int nKey);	// プレス情報取得
	bool GetTrigger(int nKey);	// トリガー情報取得

private:

	BYTE m_aKeyState[MAX_KEY];			// プレス情報
	BYTE m_aKeyStateTrigger[MAX_KEY];	// トリガー情報
};

//****************************************************
// パッドクラス
//****************************************************
class CInputPad : public CInput
{
public:

	//****************************************************
	// パッドのキー識別
	//****************************************************
	enum class JOYKEY
	{
		UP = 0,	// 十字上
		DOWN,	// 十字下
		LEFT,	// 十字左
		RIGHT,	// 十字右
		START,	// スタートボタン
		BACK,	// バックボタン
		L3,		// 左スティック押し込み
		R3,		// 右スティック押し込み
		L,		// Lボタン
		R,		// Rボタン
		NONE1,
		NONE2,
		A,		// Aボタン
		B,		// Bボタン
		X,		// Xボタン
		Y,		// Yボタン
		MAX,
	};

	//****************************************************
	// スティック情報の構造体
	//****************************************************
	typedef struct
	{
		SHORT X;
		SHORT Y;
	} JOYSTICK;

	CInputPad();	// デフォルトコンストラクタ
	~CInputPad();	// デストラクタ

	HRESULT Init();			// 初期設定
	void Uninit() override;	// 終了処理
	void Update() override;	// 更新処理

	bool GetPress(JOYKEY Key);		// プレス情報取得
	bool GetTrigger(JOYKEY Key);	// トリガー情報取得
	JOYSTICK GetJoyStickL();		// 左スティックの傾き取得
	JOYSTICK GetJoyStickR();		// 右スティックの傾き取得

private:

	void AdjustJoyStick();	// スティックの調整

	XINPUT_STATE m_aKeyState;			// プレス情報
	XINPUT_STATE m_aKeyStateTrigger;	// トリガー情報
};

#endif // _INPUT_H_