//************************************************
//
//ゲーム処理[game.cpp]
//Author：福田歩希
//
//************************************************
#include "game.h"

#include "debugproc.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

#include "bullet.h"
#include "camera.h"
#include "collision.h"
#include "effect.h"
#include "enemy.h"
#include "field.h"
#include "gauge.h"
#include "light.h"
#include "model.h"
#include "particle.h"
#include "pause.h"
#include "player.h"
#include "rankingdesign.h"
#include "shadow.h"
#include "sky.h"
//#include "visible_rect.h"
//#include "visible_sphere.h"
#include "wall.h"

/* レガシー */
#include "score.h"
#include "timer.h"

//グローバル宣言
bool g_bPause = false;

//************************************************
//ゲーム初期
//************************************************
void InitGame()
{
	g_bPause = false;

	//フェード情報用
	FADE* pFade = GetInfoFade();

	//フェードイン開始
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	int* pLastMode = ChangeLastMode();
	*pLastMode = MODE_GAME;

	InitShadow();
	//InitVisible_Rect();
	//InitVisible_Sphere();
	/* ↑他の処理で初期セットする場合があるため先行 */
	InitBullet();
	InitCamera();
	InitEffect();
	InitEnemy();
	InitField();
	InitGauge();
	InitLight();
	InitModel(MODE_GAME);
	InitParticle();
	InitPause();
	InitPlayer(MODE_GAME);
	InitSky();

	Init_Score();
	Init_Timer();

	PlaySound(SOUND_LABEL_GAME);
}

//************************************************
//ゲーム終了
//************************************************
void UninitGame(void)
{
	UninitBullet();
	UninitCamera();
	UninitEffect();
	UninitEnemy();
	UninitField();
	UninitGauge();
	UninitLight();
	UninitModel();
	UninitParticle();
	UninitPause();
	UninitPlayer();
	UninitShadow();
	UninitSky();
	//UninitVisible_Rect();
	//UninitVisible_Sphere();
	//UninitWall();

	Uninit_Score();
	Uninit_Timer();
	
	StopSound();
}

//************************************************
//ゲーム更新
//************************************************
void UpdateGame(void)
{
	//フェード情報用
	FADE* pFade = GetInfoFade();

	//if (GetKeyboardTrigger(DIK_RETURN))
	//{
	//	//フェードアウト開始
	//	pFade->bFadeIn = false;
	//	pFade->bFadeOut = true;
	//}

	//ポーズ
	if (GetKeyboardTrigger(DIK_P) || GetJoypadTrigger(JOYKEY_START))
	{
		g_bPause = true;
		PlaySound(SOUND_LABEL_DEFINE);
	}

	/* 処理順を考慮 */
	if (g_bPause)
	{
		UpdatePause();
	}
	else
	{
		UpdateEffect();
		UpdateEnemy(MODE_GAME);
		UpdateShadow(MODE_GAME);
		UpdateField();
		UpdateLight();
		UpdateModel();
		UpdateParticle();
		UpdatePlayer(MODE_GAME);
		UpdateGauge();
		UpdateCamera(MODE_GAME);
		UpdateBullet();

		UpdateSky();
		//UpdateVisible_Rect();
		//UpdateVisible_Sphere();

		Update_Score();
		Update_Timer();
	}

	//フェードアウト後
	if (pFade->col.a >= 1.1f)
	{
		if (!g_bPause)
		{
			//スコアを記録
			SaveScore();
			SetInfoMode(MODE_RANKING);
		}
		else
		{
			SetInfoMode(GetInfoChoosePause());
		}
	}
}

//************************************************
//ゲーム描画
//************************************************
void DrawGame(void)
{
	//カメラのセット
	SetInfoCamera(MODE_GAME);

	DrawSky();
	DrawField();
	DrawModel();

	/* 地面と壁はなるべく先行 */
	DrawShadow();
	DrawBullet();
	DrawEffect();
	DrawParticle();
	DrawEnemy();
	DrawPlayer();
	//DrawVisible_Rect();
	//DrawVisible_Sphere();

	/* UI */
	DrawGauge();
	Draw_Score();
	Draw_Timer();

	if (g_bPause)
	{
		DrawPause();
	}
}

//************************************
//ポーズ情報を取得
//************************************
bool* GetInfoPause(void)
{
	return &g_bPause;
}