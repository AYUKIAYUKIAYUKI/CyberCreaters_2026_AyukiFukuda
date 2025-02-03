//************************************************
//
//�Q�[������[game.cpp]
//Author�F���c����
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

/* ���K�V�[ */
#include "score.h"
#include "timer.h"

//�O���[�o���錾
bool g_bPause = false;

//************************************************
//�Q�[������
//************************************************
void InitGame()
{
	g_bPause = false;

	//�t�F�[�h���p
	FADE* pFade = GetInfoFade();

	//�t�F�[�h�C���J�n
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	int* pLastMode = ChangeLastMode();
	*pLastMode = MODE_GAME;

	InitShadow();
	//InitVisible_Rect();
	//InitVisible_Sphere();
	/* �����̏����ŏ����Z�b�g����ꍇ�����邽�ߐ�s */
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
//�Q�[���I��
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
//�Q�[���X�V
//************************************************
void UpdateGame(void)
{
	//�t�F�[�h���p
	FADE* pFade = GetInfoFade();

	//if (GetKeyboardTrigger(DIK_RETURN))
	//{
	//	//�t�F�[�h�A�E�g�J�n
	//	pFade->bFadeIn = false;
	//	pFade->bFadeOut = true;
	//}

	//�|�[�Y
	if (GetKeyboardTrigger(DIK_P) || GetJoypadTrigger(JOYKEY_START))
	{
		g_bPause = true;
		PlaySound(SOUND_LABEL_DEFINE);
	}

	/* ���������l�� */
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

	//�t�F�[�h�A�E�g��
	if (pFade->col.a >= 1.1f)
	{
		if (!g_bPause)
		{
			//�X�R�A���L�^
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
//�Q�[���`��
//************************************************
void DrawGame(void)
{
	//�J�����̃Z�b�g
	SetInfoCamera(MODE_GAME);

	DrawSky();
	DrawField();
	DrawModel();

	/* �n�ʂƕǂ͂Ȃ�ׂ���s */
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
//�|�[�Y�����擾
//************************************
bool* GetInfoPause(void)
{
	return &g_bPause;
}