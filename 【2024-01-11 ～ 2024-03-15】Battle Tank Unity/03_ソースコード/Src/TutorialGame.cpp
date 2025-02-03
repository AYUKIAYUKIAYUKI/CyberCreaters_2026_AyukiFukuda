//==========================================================
//
//チュートリアル時のゲーム画面の描画処理[game.cpp]
//Author:kasai keisuke, 福田歩希,satokurara
//
//==========================================================

/* インクルードファイル */
#include "game.h"
// 中枢
#include "input.h"
#include "main.h"
#include "sound.h"
// 諸処理
#include "boss.h"
#include "bullet.h"
#include "camera.h"
#include "effect.h"
//#include "effect_hayu.h"
#include "effect_sand.h"
#include "effect_smoke.h"
#include "enemy.h"
#include "explosion.h"
#include "field.h"
#include "item.h"
#include "light.h"
#include "object.h"
#include "player.h"
#include "reticle.h"
#include "sea.h"
#include "sky.h"
#include "tutorial.h"
#include "TutorialGame.h"

#include "player_count.h"
#include "shadow.h"
// デバッグ時
#ifdef _DEBUG
#include "debugproc.h"
#include "editcamera.h"

#include "visible_sph.h"
#include "visible_box.h"
#include <assert.h>
#endif	// _DEBUG

/*/ マクロ定義 /*/
#define JOIN_VERIFY 4	// 人数指定

/*/ グローバル変数 /*/
int g_AmountPlayer_Tutorial = JOIN_VERIFY;	// プレイ人数格納
int g_nCnt_Tuto = 0;						//デバック用変数(コントローラ分離確認用)
bool g_LayoutEdit_Tutorial = false;			// 配置編集モード用フラグ


//=======================================================================
//ゲーム画面の初期化処理
//=======================================================================
void InitTutorialGame(void)
{
#ifndef JOIN_VERIFY

	// 人数指定が無ければ固定
	g_AmountPlayer_Tuto = 1;

#endif	// JOIN_VERIFY

	//各種変数の初期化
	g_LayoutEdit_Tutorial = false;	// 配置編集モードをオフ
	g_nCnt_Tuto = 0;				//デバック用変数(コントローラ分離確認用)の初期化
	g_AmountPlayer_Tutorial = 0;	// プレイ人数の初期化
	//プレイ人数の取得
	g_AmountPlayer_Tutorial = ReturnSelectPlayerCount() + 1;

#ifdef _DEBUG

	// 人数がおかしいと終了
	assert(g_AmountPlayer_Tutorial > 0 && g_AmountPlayer_Tutorial <= 4);

	// 球の判定可視化初期
	InitVisibleSph();

	//四角の判定可視化初期
	InitVisibleBox();

#endif	// _DEBUG

	//UIの初期化
	InitTutorial();

	// 弾の初期
	InitBullet();

	// カメラの初期
	InitCamera(g_AmountPlayer_Tutorial);

	//エフェクトの初期化処理
	InitEffect();

	// 砂のエフェクトの初期
	InitEffectSand();

	// 煙のエフェクトの初期化処理
	InitEffect_Smoke();

	// 爆発の初期
	InitExplosion();

	// 床の初期化処理
	InitField();

	// アイテムの初期
	InitItem();

	// ライトの初期
	InitLight();

	// 物の初期
	InitObject();

	// プレイヤーの初期
	InitPlayer(g_AmountPlayer_Tutorial);

	// 海の初期
	InitSea();

	// 空の初期
	InitSky();
}

//=======================================================================
//ゲーム画面の終了処理
//=======================================================================
void UninitTutorialGame(void)
{
#ifdef _DEBUG


	// 球の判定可視化終了
	UninitVisibleSph();

	//四角の判定の可視化終了
	UninitVisibleBox();

#endif	// _DEBUG

	//UIの終了
	UninitTutorial();

	// 弾の終了
	UninitBullet();

	//エフェクトの終了処理
	UninitEffect();

	// 砂のエフェクトの終了
	UninitEffectSand();

	// 煙のエフェクトの終了処理
	UninitEffect_Smoke();

	// 爆発の終了
	UninitExplosion();

	// 床の終了処理
	UninitField();

	// アイテムの終了
	UninitItem();

	// 物の終了
	UninitObject();

	// プレイヤーの終了
	UninitPlayer();

	//UIの初期
	UninitTutorial();

	// 海の終了
	UninitSea();

	// 空の終了
	UninitSky();
}

//======================================================================
//チュートリアル中のゲーム更新処理
//======================================================================
void UpdateTutorialGame(void)
{

#if defined (_DEBUG)

	// 配置編集モード切り替え
	if (GetKeyboardTrigger(DIK_F2))
	{
		g_LayoutEdit_Tutorial = !g_LayoutEdit_Tutorial;
	}

	if (!g_LayoutEdit_Tutorial)
	{ // 配置編集モードでないときのみ
		// 参加人数を直接変更
		if (GetKeyboardTrigger(DIK_LBRACKET))
		{
			g_AmountPlayer_Tutorial < 4 ? g_AmountPlayer_Tutorial++ : g_AmountPlayer_Tutorial = 1;
		}
		else if (GetKeyboardTrigger(DIK_RBRACKET))
		{
			g_AmountPlayer_Tutorial > 1 ? g_AmountPlayer_Tutorial-- : g_AmountPlayer_Tutorial = 4;
		}
	}
#ifdef _DEBUG
	// デバッグ表示の更新(配布)
	UpdateDebugProc();

#endif // DEBUG


	// カメラ or 編集カメラの更新
	g_LayoutEdit_Tutorial ? UpdateEditCamera() : UpdateCamera(g_AmountPlayer_Tutorial);



#endif	// _DEBUG

#ifndef _DEBUG

	// カメラの更新
	UpdateCamera(g_AmountPlayer_Tutorial);

#endif // _DEBUG リリース

	// 状況に応じて物の更新
	UpdateObject(g_LayoutEdit_Tutorial);

	if (!g_LayoutEdit_Tutorial)
	{
		//アイテムの更新
		UpdateItem();

		// ライトの更新
		UpdateLight();

		// プレイヤーの更新
		UpdatePlayer(g_AmountPlayer_Tutorial);

		// 弾の更新
		UpdateBullet();

		//エフェクトの更新処理
		UpdateEffect();

		//UIの更新
		UpdateTutorial();

		// 爆発の更新
		UpdateExplosion();

		// 砂のエフェクトの更新
		UpdateEffectSand();

		// 煙のエフェクトの更新処理
		UpdateEffect_Smoke();

		// 床の更新処理
		UpdateField();

		// 海の更新
		UpdateSea();

		// 空の更新
		UpdateSky();

#ifdef _DEBUG	

		// 球の判定可視化更新
		UpdateVisibleSph();

		// 四角の判定可視化更新
		UpdateVisibleBox();

#endif // _DEBUG ↑これここに置きたい
	}
}

//=======================================================================
//チュートリアル時のゲーム画面の描画処理
//=======================================================================
void DrawTutorialGame(void)
{
	// ループ回数
	int Loop = 0;

	// 配置編集モードであれば余分な描画を抑制
	g_LayoutEdit_Tutorial ? Loop = 1 : Loop = g_AmountPlayer_Tutorial;

	for (int i = 0; i < Loop; i++)
	{
#ifdef _DEBUG

		// カメラ or 編集カメラの設定
		g_LayoutEdit_Tutorial ? SetInfoEditCamera() : SetInfoCamera(i, g_AmountPlayer_Tutorial);

#else

		// カメラの設定
		SetInfoCamera(i, g_AmountPlayer_Tutorial);

#endif	// _DEBUG リリース

		// 空の描画
		DrawSky();

		// 海の描画
		DrawSea();

		// 状況に応じて物の描画
		DrawObject(g_LayoutEdit_Tutorial);

		// アイテムの描画
		DrawItem();

		// 床の描画処理
		DrawField();

		// 砂のエフェクトの描画
		DrawEffectSand();

		// 爆発の描画
		DrawExplosion();

		// 煙のエフェクトの描画処理
		DrawEffect_Smoke();

		//エフェクトの描画
		DrawEffect();

		// 弾の描画
		DrawBullet();

		// プレイヤーの描画
		DrawPlayer();

#ifdef _DEBUG

		// 球の判定可視化描画
		DrawVisibleSph();

		// 四角の判定可視化描画
		DrawVisibleBox();

#endif	// _DEBUG
	}

	// UI用ポートの設定
	SetInfoUIport();

	//UIの描画
	DrawTutorial();

	/*---【ゲーム内UIの表示はここから下で行います】---*/

#ifdef _DEBUG

	// テスト用の描画
	if (!g_LayoutEdit_Tutorial)
	{
		//DrawTEST();	//!< UI系はポート設定されていない範囲の描画は行われません。はみ出るようなら新たにポート設定を追加してください。
	}

	// デバッグ用表示の描画(配布)
	DrawDebugProc();

#endif	// _DEBUG
}

/*---【以下ゲームループ外】---*/

