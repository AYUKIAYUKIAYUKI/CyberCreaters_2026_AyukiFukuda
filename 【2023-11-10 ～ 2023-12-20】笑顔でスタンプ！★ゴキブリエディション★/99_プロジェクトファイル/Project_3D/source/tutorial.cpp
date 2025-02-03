//************************************************
//
//チュートリアル処理[tutorial.cpp]
//Author：福田歩希
//
//************************************************
#include "tutorial.h"

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
#include "light.h"
#include "model.h"
#include "particle.h"
#include "player.h"
#include "shadow.h"
#include "sky.h"
#include "tutorialdesign.h"
//#include "visible_rect.h"
//#include "visible_sphere.h"

/* レガシー */
#include "score.h"
#include "timer.h"

//************************************************
//チュートリアル初期
//************************************************
void InitTutorial()
{
	//フェード情報用
	FADE* pFade = GetInfoFade();

	//フェードイン開始
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	InitShadow();
	//InitVisible_Rect();
	//InitVisible_Sphere();
	/* ↑他の処理で初期セットする場合があるため先行 */
	InitBullet();
	InitCamera();
	InitEffect();
	InitEnemy();
	InitField();
	InitLight();
	InitModel(MODE_TUTORIAL);
	InitParticle();
	InitPlayer(MODE_TUTORIAL);
	InitSky();
	InitTutorialDesign();

	PlaySound(SOUND_LABEL_TUTORIAL);
}

//************************************************
//チュートリアル終了
//************************************************
void UninitTutorial(void)
{
	UninitBullet();
	UninitCamera();
	UninitEffect();
	UninitEnemy();
	UninitField();
	UninitLight();
	UninitModel();
	UninitParticle();
	UninitPlayer();
	//UninitRay();
	//UninitReticle();
	UninitShadow();
	UninitSky();
	UninitTutorialDesign();
	//UninitVisible_Rect();
	//UninitVisible_Sphere();
	//UninitWall();

	StopSound();
}

//************************************************
//チュートリアル更新
//************************************************
void UpdateTutorial(void)
{
	//フェード情報用
	FADE* pFade = GetInfoFade();

	/* 処理順を考慮 */
	UpdateEffect();
	UpdateEnemy(MODE_TUTORIAL);
	UpdateField();
	UpdateLight();
	UpdateModel();
	UpdateParticle();
	UpdatePlayer(MODE_TUTORIAL);
	UpdateCamera(MODE_TUTORIAL);
	UpdateBullet();
	UpdateShadow(MODE_TUTORIAL);
	UpdateSky();
	UpdateTutorialDesign();
	//UpdateVisible_Rect();
	//UpdateVisible_Sphere();

	//フェードアウト後
	if (pFade->col.a >= 1.1f)
	{
		SetInfoMode(MODE_GAME);
	}
}

//************************************************
//チュートリアル描画
//************************************************
void DrawTutorial(void)
{
	//カメラのセット
	SetInfoCamera(MODE_TUTORIAL);

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
	DrawTutorialDesign();

	//DrawVisible_Rect();
	//DrawVisible_Sphere();
}