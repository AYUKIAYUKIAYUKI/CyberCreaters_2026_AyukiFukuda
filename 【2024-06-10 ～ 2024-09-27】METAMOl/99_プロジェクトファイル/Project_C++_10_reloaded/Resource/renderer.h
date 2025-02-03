//============================================================================
// 
// レンダラー管理、ヘッダファイル [renderer.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _RENDERER_H_
#define _RENDERER_H_	// 二重インクルード防止

//****************************************************
// レンダラークラス
//****************************************************
class CRenderer final
{
public:

	CRenderer();	// コンストラクタ
	~CRenderer();	// デストラクタ

	HRESULT Init(HWND hWnd, BOOL bWindiw);	// 初期設定
	void Release();							// 解放
	void Update();							// 更新処理
	void Draw();							// 描画処理
	void PrintDebug();						// デバッグ表示

	static CRenderer* GetInstance();	// レンダラーを取得

	LPDIRECT3DDEVICE9 GetDeviece();		// デバイスの取得
	LPDIRECT3DTEXTURE9 GetTexture();	// テクスチャ情報を取得
	LPDIRECT3DSURFACE9 GetSurface();	// サーフェイス情報を取得

	void SetDebugString(std::string str);			// デバッグ文字列に追加
	void SetTimeString(std::string str, int nCnt);	// 時限式デバッグ文字列に追加

private:

	void LayoutFurniture();	// 家具の配置
	void Create();			// 生成
	HRESULT CreateTex();	// モニター用テクスチャの生成
	void Uninit();			// 終了処理

	static CRenderer* m_pRenderer;	// レンダラー

	LPDIRECT3D9 m_pD3D;									// Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;						// デバイス
	LPD3DXFONT m_pFont;									// フォント
	LPDIRECT3DTEXTURE9 m_pMonitorTex;					// モニター用テクスチャポインタ
	LPDIRECT3DSURFACE9 m_pMonitorSurface;				// モニター用サーフェイスポインタ
	std::string m_debugStr;								// 表示用文字列
	std::vector<std::pair<std::string, int>> m_timeStr;	// 時限式文字列
};

#endif // _RENDERER_H_