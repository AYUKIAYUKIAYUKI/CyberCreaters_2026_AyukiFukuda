//************************************************
//
//ジェニーゲニー、ヘッダファイル[main.h]
//Author：福田歩希
//
//************************************************
#ifndef _MAIN_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _MAIN_H_	//(二重インクルード防止、マクロ定義する)

#include <windows.h>
#include <Mmsystem.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	//下のやつのビルド時警告用マクロ
#include <dinput.h>
#include "Xinput.h"
#include "xaudio2.h"
#include "title.h"
#include "tutorial.h"
#include "ranking.h"
#include "menu.h"
#include "game.h"
#include "result.h"

//ライブラリのリンク
#pragma	comment(lib,"d3d9.lib")		//描画処理用
#pragma	comment(lib,"d3dx9.lib")	//[d3d9.lib]の拡張ライブラリ
#pragma	comment(lib,"dxguid.lib")	//DirectXのコーポネント使用のため
#pragma comment(lib,"Winmm.lib")	//システム時間取得用
#pragma comment(lib,"dinput8.lib")	//入力処理用
#pragma comment(lib,"xinput.lib")	//コントローラ入力用

//マクロ定義
#define SCREEN_WIDTH	(1980)	//ウインドウの幅
#define SCREEN_HEIGHT	(1080)	//ウインドウの高さ

#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//頂点フォーマット

#define AMOUNT_VTX	(4)				//平均的なポリゴン1つあたりの頂点数
#define AMOUNT_COMBINEPOLYGON	(2)	//平均的なポリゴンの組み合わせた数

#define SCREENCENTER_X	(990.0f)	//X中心
#define SCREENCENTER_Y	(540.0f)	//Y中心

#define SPAN_OUTSIDE_BORDER	(20.0f)	//画面の縁の長さ

//モード識別の列挙型
typedef enum
{
	MODE_TITLE = 0, //タイトルモード
	MODE_MENU,		//メニューモード
	MODE_TUTORIAL,	//チュートリアルモード
	MODE_RANKING,	//ランキングモード
	MODE_GAME,		//ゲームモード
	MODE_RESULT,	//リザルトモード
	MODE_MAX,		//モードの総数
}MODE;

//ポリゴン用構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//座標変化用係数
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標用
}VERTEX_2D;

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
void Setinfo_Mode(MODE mode);
MODE Getinfo_Mode(void);
bool* Getinfo_End(void);
int* Getinfo_HoldLastScore(void);

#endif