//==========================================================
//
//ゲーム画面の描画処理[game.cpp]
//Author:kasai keisuke, 福田歩希
//
//==========================================================

/*---【インクルードファイル】---*/
#include "game.h"

// システム系
#include "input.h"
#include "main.h"
#include "sound.h"

// 諸処理
#include "bar.h"
#include "boss.h"
#include "boss_bullet.h"
#include "bullet.h"
#include "camera.h"
#include "effect.h"
#include "effect_burn.h"
#include "effect_heart.h"
#include "effect_sand.h"
#include "effect_smoke.h"
#include "effect_soul.h"
#include "effect_ring.h"
#include "enemy.h"
#include "explosion.h"
#include "field.h"
#include "item.h"
#include "life.h"
#include "light.h"
#include "object.h"
#include "object_bar.h"
#include "pause.h"
#include "phase.h"
#include "player.h"
#include "player_count.h"
#include "score.h"
#include "sea.h"
#include "shadow.h"
#include "sky.h"
#include "timer.h"
#include "weapon.h"
#include "fade.h"
#include "reload.h"
#include "result.h"
// デバッグ時のみ
#ifdef _DEBUG
#include "debugproc.h"
#include "editcamera.h"
#include "enemy_camera.h"
#include "enemy_layout.h"
#include "visible_box.h"
#include "visible_sph.h"
#include <assert.h>
#endif	// _DEBUG

/*---【グローバル変数】---*/
int g_AmountPlayer = 0;		// プレイ人数格納
bool g_LayoutEdit = false;	// 配置編集モード用フラグ
bool g_Layout_EN = false;	// 敵配置編集モード用フラグ
int g_nCnt = 0;				// デバック用変数(コントローラ分離確認用)
bool g_Pause = false;		// ポーズ判定用フラグ
int g_nTimer = 0;			// タイマー用変数
int g_nLateTime = 0;		// ボスを倒した後つける遅延時間
bool g_bGameEnd = false;	// ボスが死んでいるかどうか
int g_ScoreValue = 0;		// スコア

//=======================================================================
//ゲーム画面の初期化処理
//=======================================================================
void InitGame(void)
{
	PlaySound(SOUND_LABEL_GAME_BGM);
	//各種変数の初期化
	g_LayoutEdit = false;	// 配置編集モードをオフ
	g_Layout_EN = false;	// 敵配置編集モードをオフ
	g_nCnt = 0;				//デバック用変数(コントローラ分離確認用)の初期化
	g_Pause = false;		// ポーズフラグを無くす
	g_nTimer = 0;			// タイマー用変数の初期化
	g_bGameEnd = false;
	g_nLateTime = 0;
	g_ScoreValue = 0;	// スコア

	//プレイ人数の取得
	g_AmountPlayer = ReturnSelectPlayerCount() + 1;
	//g_AmountPlayer = 1;

#ifdef _DEBUG

	// 人数がおかしいと終了
	assert(g_AmountPlayer > 0 && g_AmountPlayer <= 4);

	// 編集カメラの初期
	InitEditCamera();

	// 敵の配置初期
	Init_EN();

	// 敵編集カメラ初期
	Init_ENC();

	// 箱の判定可視化初期
	InitVisibleBox();

	// 球の判定可視化初期
	InitVisibleSph();
	
#endif	// _DEBUG

	// リングエフェクト初期：先行
	InitEffect_Ring();

	// 影の初期：先行
	InitShadow();

	// 構造物の体力ゲージの初期：先行
	InitObject_Bar();

	// ゲージの初期
	InitBar(g_AmountPlayer);

	//ボスの初期化処理
	InitBoss();

	//ボスの弾の初期化処理
	InitBossBullet();

	// 弾の初期
	InitBullet();

	// カメラの初期
	InitCamera(g_AmountPlayer);

	//エフェクトの初期化処理
	InitEffect();

	// 爆破エフェクトの初期
	InitEffect_Burn();

	// ハートエフェクト初期
	InitEffect_Heart();

	// 砂のエフェクトの初期
	InitEffectSand();

	// 煙エフェクト初期
	InitEffect_Smoke();

	// 魂エフェクト初期
	InitEffect_Soul();

	// 敵の初期
	InitEnemy();

	// 爆発の初期
	InitExplosion();
	
	// 地面の初期
	InitField();

	// アイテムの初期
	InitItem();

	// ライフ表示の初期
	InitLife(g_AmountPlayer);

	// ライトの初期
	InitLight();

	// 物の初期
	InitObject();

	// プレイヤーの初期
	InitPlayer(g_AmountPlayer);

	// ポーズ画面の初期化処理
	InitPause();

	// フェーズ表示の初期
	InitPhase(g_AmountPlayer);

	// スコア表示の初期
	InitScore(g_AmountPlayer);

	// 海の初期
	InitSea();

	// 空の初期
	InitSky();

	// タイマー表示初期
	InitTimer(g_AmountPlayer);

	// 武器表示の初期
	InitWeapon(g_AmountPlayer);

	// リロード表示の初期
	InitReload(g_AmountPlayer);

	//フェードイン処理
	SetFade(FADE_IN, MODE_MAX);//フェードイン時は二個目の引数無視されるのでなんでもいい
}

//=======================================================================
//ゲーム画面の終了処理
//=======================================================================
void UninitGame(void)
{
	StopSound();
#ifdef _DEBUG

	// 箱の判定可視化終了
	UninitVisibleBox();

	// 球の判定可視化終了
	UninitVisibleSph();

	// 敵の配置終了
	Uninit_EN();

#endif	// _DEBUG

	// ゲージの終了
	UninitBar();

	//ボスの終了処理
	UninitBoss();

	// 弾の終了
	UninitBullet();

	// ボスの弾の終了処理
	UninitBossBullet();

	//エフェクトの終了処理
	UninitEffect();

	// 爆破エフェクトの終了
	UninitEffect_Burn();

	// ハートエフェクト終了
	UninitEffect_Heart();

	// 砂のエフェクトの終了
	UninitEffectSand();

	// 煙エフェクト終了
	UninitEffect_Smoke();

	// 魂エフェクト終了
	UninitEffect_Soul();

	// リングエフェクト終了
	UninitEffect_Ring();

	// 敵の終了
	UninitEnemy();

	// 爆発の終了
	UninitExplosion();

	// 地面の終了
	UninitField();

	// アイテムの終了
	UninitItem();

	// ライフ表示の終了
	UninitLife();

	// 物の終了
	UninitObject();

	// 構造物の体力ゲージの終了
	UninitObject_Bar();

	//ポーズ画面の終了処理
	UninitPause();

	// フェーズ表示の終了
	UninitPhase();

	// プレイヤーの終了
	UninitPlayer();

	// スコア表示の終了
	UninitScore();

	// 海の終了
	UninitSea();

	// 影の終了
	UninitShadow();

	// 空の終了
	UninitSky();

	// タイマー表示終了
	UninitTimer();

	// 武器表示の終了
	UninitWeapon();

	// リロード表示の終了
	UninitReload();
}

//=======================================================================
//ゲーム画面の更新処理
//=======================================================================
void UpdateGame(void)
{
	if (g_ScoreValue > 99999999)
	{ // 上限を越えると固定
		g_ScoreValue = 99999999;
	}

	if (g_ScoreValue < 0)
	{// マイナス値になるのを防ぐ
		g_ScoreValue = 0;
	}
	if (GetJoypadTrigger(JOYKEY_START, 0) || GetKeyboardTrigger(DIK_P))
	{
		g_Pause = !g_Pause;
	}

	if (g_Pause)
	{ // ポーズ中のみ

		/*---【ここでUIの処理】---*/
		UpdatePause();	// ポーズ画面の更新処理

		return;	// 以下の処理は行わない
	}

	// モードに関わらす状況に応じて物の更新
	UpdateObject(g_LayoutEdit);

#ifdef _DEBUG

	// デバッグ表示の更新(配布)
	UpdateDebugProc();

	// 配置編集モード切り替え
	if (GetKeyboardTrigger(DIK_F2) && !g_Layout_EN)
	{
		g_LayoutEdit = !g_LayoutEdit;
	}
	
	if (GetKeyboardTrigger(DIK_LCONTROL) && !g_LayoutEdit)
	{
		g_Layout_EN = !g_Layout_EN;
	}

	if (g_LayoutEdit)
	{
		// 編集カメラの更新
		UpdateEditCamera();
	}
	else if (g_Layout_EN)
	{
		// 敵の配置更新
		Update_EN();

		// 敵編集カメラの更新
		Update_ENC();
	}
	else
	{
		// 通常カメラの更新
		UpdateCamera(g_AmountPlayer);
	}

#else 

	// 通常カメラの更新
	UpdateCamera(g_AmountPlayer);

#endif // _DEBUG

	if (!g_LayoutEdit && !g_Layout_EN)
	{
		g_nTimer++;	// タイマー用変数の加算

		// 構造物の体力ゲージの更新
		UpdateObject_Bar();

		// ゲージの更新
		UpdateBar();

		//アイテムの更新
		UpdateItem();

		// ライフ表示の更新
		UpdateLife();

		// ライトの更新
		UpdateLight();

		// フェーズ表示の更新
		UpdatePhase();
		if (!g_bGameEnd)
		{

			// ボスの弾の更新処理
			UpdateBossBullet();


			// プレイヤーの更新
			UpdatePlayer(g_AmountPlayer);

			// 弾の更新
			UpdateBullet();

			// 敵の更新
			UpdateEnemy();

		}


		//ボスの更新処理
		UpdateBoss();

		//エフェクトの更新処理
		UpdateEffect();

		// 爆発の更新
		UpdateExplosion();

		// 爆破エフェクトの更新
		UpdateEffect_Burn();

		// ハートエフェクト更新
		UpdateEffect_Heart();

		// 砂のエフェクトの更新
		UpdateEffectSand();

		// 煙エフェクト更新
		UpdateEffect_Smoke();

		// 魂エフェクト更新
		UpdateEffect_Soul();

		// リングエフェクト更新
		UpdateEffect_Ring();

		// 地面の更新
		UpdateField();

		// スコア表示の更新
		UpdateScore();

		// 海の更新
		UpdateSea();

		// 影の更新
		UpdateShadow();

		// 空の更新
		UpdateSky();

		// タイマー表示更新
		UpdateTimer();

		// 武器表示の更新
		UpdateWeapon(g_AmountPlayer);

		// リロード表示の更新
		UpdateReload();

#ifdef _DEBUG	

		// 球の判定可視化更新
		UpdateVisibleSph();

#endif // _DEBUG
	}

#ifdef _DEBUG	

	// 箱の判定可視化更新
	UpdateVisibleBox();

#endif // _DEBUG：オブジェクトエディット中でも判定を同期するため


	//******************************************************************
	// ゲームの終了条件
	//******************************************************************
	if (CheckBossUse())
	{// ボスが死んでいたらフラグを切り替える
		g_bGameEnd = true;
	}

	if (CheckGameEnd())
	{
		//PlaySound(SOUND_LABEL_EXPLOSION_1);
		//フェードアウト処理
		SetFade(FADE_OUT, MODE_RESULT_GAMECLEAR);//二つ目に移行先
	}
	if (!g_LayoutEdit && !g_Layout_EN)
	{ // いずれかの編集モードでは無い場合のみ

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			//フェードアウト処理
			SetFade(FADE_OUT, MODE_RESULT_GAMECLEAR);//二つ目に移行先
		}
	}
}

//=======================================================================
//ゲーム画面の描画処理
//=======================================================================
void DrawGame(void)
{
	int Loop = 0;	// ループ回数

	// 人数に応じて描画回数を変更
	g_LayoutEdit ? Loop = 1 : Loop = g_AmountPlayer;

	for (int i = 0; i < Loop; i++)
	{
#ifdef _DEBUG

		if (g_LayoutEdit)
		{
			// 編集カメラを設定
			SetInfoEditCamera();
		}
		else if (g_Layout_EN)
		{
			// 敵編集カメラを設定
			SetInfo_ENC();
		}
		else
		{
			// 通常のカメラを設定
			SetInfoCamera(i, g_AmountPlayer);
		}

#else

		// 通常のカメラを設定
		SetInfoCamera(i, g_AmountPlayer);

#endif // _DEBUG


		// 空の描画
		DrawSky();

		// 海の描画
		DrawSea();

		// 地面の描画
		DrawField();

		// 砂のエフェクトの描画
		DrawEffectSand();

		// 影の描画
		DrawShadow();

		// リングエフェクト描画
		DrawEffect_Ring();

		// 爆破エフェクトの描画
		DrawEffect_Burn();

		//エフェクトの描画
		DrawEffect();

		// 状況に応じて物の描画
		DrawObject(g_LayoutEdit);

#ifdef _DEBUG


		if (g_Layout_EN)
		{
			// 敵の配置描画
			Draw_EN();
		}
		else
		{
			// 敵の描画
			DrawEnemy();
		}

#else

		// 敵の描画
		DrawEnemy();

#endif // _DEBUG

		// ボスの描画処理
		DrawBoss();

		// アイテムの描画
		DrawItem();

		// 爆発の描画
		DrawExplosion();

		// 煙エフェクトの描画
		DrawEffect_Smoke();

		// 弾の描画
		DrawBullet();

		// ボスの弾の描画処理
		DrawBossBullet();

		// ハートエフェクト描画
		DrawEffect_Heart();

		// 魂エフェクト描画
		DrawEffect_Soul();

		// プレイヤーの描画
		DrawPlayer();

		// 構造物の体力ゲージの描画
		DrawObject_Bar();

#ifdef _DEBUG

		// 箱の判定可視化描画
		DrawVisibleBox();

		// 球の判定可視化描画
		DrawVisibleSph();

#endif	// _DEBUG
	}

	// UI用ポートの設定
	SetInfoUIport();

	/*---【ゲーム内UIの表示はここから下で行います】---*/

	if (!g_LayoutEdit && !g_Layout_EN)
	{ // エディット示は描画しない

		// ライフ表示の描画
		DrawLife();

		// 武器表示の描画
		DrawWeapon();

		// リロード表示の描画
		DrawReload();

		// ゲージの更新
		DrawBar();

		// フェーズ表示の描画
		DrawPhase();

		// スコア表示の描画
		DrawScore();

		// タイマー表示描画
		DrawTimer();
	}

	if (g_Pause)
	{// ポーズ中なら
		DrawPause();
	}

#ifdef _DEBUG

	// デバッグ用表示の描画(配布)
	DrawDebugProc();

#endif	// _DEBUG
}

//=======================================================================
//ポーズの有効無効設定
//=======================================================================
void SetEnablePause(bool bPause)
{
	g_Pause = bPause;
}

//=======================================================================
//ボスが死んだ後の遅延時間
//=======================================================================
bool CheckGameEnd(void)
{
	if (g_bGameEnd)
	{// ボスが死んだあと遅延時間用の変数を加算
		g_nLateTime++;
	}

	if (g_nLateTime >= MAX_LATE)
	{// 一定時間が経過したらtrueを返す
		return true;
	}
	else
	{// 一定時間が経過していなかったらfalseを返す
		return false;
	}
}

/*---【以下ゲームループ外】---*/

//************************************************
// 編集モードのフラグ取得
//************************************************
bool GetLayoutEdit(void)
{
	return g_LayoutEdit;
}

//************************************************
// 敵編集モードのフラグ取得
//************************************************
bool GetLayout_EN(void)
{
	return g_Layout_EN;
}

//************************************************
// スコア取得
//************************************************
int* GetInfoScore(void)
{
	return &g_ScoreValue;
}

//************************************************
// 状態継続カウント用
//************************************************
bool CntDuration(int* dur)
{
	bool finish = false;

	if (*dur > 0)
	{ // 継続時間減少
		*dur -= 1;	// なぜデクリメント非対応？
	}
	else
	{ // 継続時間が無くなると

		// 完了を返す
		finish = true;
	}

	return finish;
}

/*--------------------------------------------------------*/

//************************************************
// インゲーム終了フラグアクセス用
//************************************************
bool* GetInfoEndGame(void)
{
	return &g_bGameEnd;
}