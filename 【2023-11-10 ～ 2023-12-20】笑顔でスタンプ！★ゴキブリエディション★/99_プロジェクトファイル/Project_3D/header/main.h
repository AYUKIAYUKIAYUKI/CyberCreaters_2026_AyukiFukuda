//************************************************
//
//メイン、ヘッダファイル[main.h]
//Author：福田歩希
//
//************************************************
#ifndef _MAIN_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _MAIN_H_	//(二重インクルード防止、マクロ定義する)

#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <Mmsystem.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	//下のやつのビルド時警告用マクロ
#include <dinput.h>
#include "Xinput.h"
#include "xaudio2.h"

//ライブラリのリンク
#pragma	comment(lib,"d3d9.lib")		//描画処理用
#pragma	comment(lib,"d3dx9.lib")	//[d3d9.lib]の拡張ライブラリ
#pragma	comment(lib,"dxguid.lib")	//DirectXのコーポネント使用のため
#pragma comment(lib,"Winmm.lib")	//システム時間取得用
#pragma comment(lib,"dinput8.lib")	//入力処理用
#pragma comment(lib,"xinput.lib")	//コントローラ入力用

//マクロ定義
#define SCREEN_WIDTH	(1980)		//ウインドウの横幅
#define SCREEN_HALFWIDTH	(990)	//ウインドウの横半幅
#define SCREEN_HEIGHT	(1080)		//ウインドウの縦幅
#define SCREEN_HALFHEIGHT	(540)	//ウインドウの縦半幅

#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//2D用頂点フォーマット
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//3D用頂点フォーマット

#define AMOUNT_VTX	(4)				//板ポリゴン1枚あたりのバーテックス数
#define AMOUNT_COMBINEPOLYGON	(2)	//板ポリゴン1枚あたりのプリミティブ数

//2Dポリゴン用構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//座標変化用係数
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標用
}VERTEX_2D;

//3Dポリゴン用構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標用
}VERTEX_3D;

//AABB衝突判定用
typedef struct
{
	D3DXVECTOR3 min;	//最小
	D3DXVECTOR3 max;	//最大
}COLLISION_AABB;

//モード識別の列挙型
typedef enum
{
	MODE_TITLE = 0, //タイトルモード
	MODE_MENU,		//メニューモード
	MODE_TUTORIAL,	//チュートリアルモード
	MODE_RANKING,	//ランキングモード
	MODE_GAME,		//ゲームモード
	MODE_RESULT,	//リザルトモード
	MODE_END,	//エンドモード
	MODE_MAX,		//モードの総数
}MODE;

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	//ウインドウプロシージャ
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindiw);	//初期
void UnInit(void);	//終了
void Update(void);	//更新
void Draw(void);	//描画
void DrawDebug(void);	//デバッグ用表示
LPDIRECT3DDEVICE9 GetDevice(void);	//デバイスの取得
LONG* GetInfoRectUP(void);	//レクトの上端取得
int GetFPS(void);	//FPSを取得
void SetInfoMode(MODE mode);	//モード変更
MODE GetInfoMode(void);	//モード取得
bool* GetInfoEnd(void);	//終了

#endif