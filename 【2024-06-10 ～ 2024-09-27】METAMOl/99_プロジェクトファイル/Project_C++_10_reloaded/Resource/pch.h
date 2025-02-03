//============================================================================
// 
// プリコンパイル済みヘッダー [pch.h]
// Author : 福田歩希
// 
//============================================================================

#pragma once	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include <stdio.h>
#include <assert.h>
#include <windows.h>	// Windowsアプリケーション動作用

// DirectX9
#include <d3dx9.h>					// DirectX9動作用
#define DIRECTINPUT_VERSION	0x0800	// DirectInputのバージョン
#include <dinput.h>					// DirectInput動作用
#include <xinput.h>					// コントローラー動作用
#include <xaudio2.h>				// サウンド動作用

// 標準ライブラリ
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <list>
#include <sstream>
#include <utility>
#include <iomanip>
#include <vector>

//****************************************************
// ライブラリのリンク
//****************************************************
#pragma comment(lib, "winmm.lib")
#pragma	comment(lib,"d3d9.lib")		// 描画処理用
#pragma	comment(lib,"d3dx9.lib")	// [d3d9.lib]の拡張ライブラリ
#pragma	comment(lib,"dxguid.lib")	// DirectXのコーポネント使用のため
#pragma	comment(lib,"dinput8.lib")	// DirectInput動作用
#pragma comment(lib,"xinput.lib")	// コントローラ動作用

//****************************************************
// マクロ定義
//****************************************************

// メモリリーク検出用
#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

// 頂点フォーマット
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// ウィンドウサイズ
#define SCREEN_WIDTH	1280	// ウインドウの幅
#define SCREEN_HEIGHT	720		// ウインドウの高さ

//****************************************************
// 2Dポリゴン頂点フォーマットの定義
//****************************************************
struct VERTEX_2D
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 除算数
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
};

//****************************************************
// 3Dポリゴン頂点フォーマットの定義
//****************************************************
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標用
};