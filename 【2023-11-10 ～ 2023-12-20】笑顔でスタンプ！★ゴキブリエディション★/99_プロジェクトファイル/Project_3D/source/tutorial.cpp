//************************************************
//
//�`���[�g���A������[tutorial.cpp]
//Author�F���c����
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

/* ���K�V�[ */
#include "score.h"
#include "timer.h"

//************************************************
//�`���[�g���A������
//************************************************
void InitTutorial()
{
	//�t�F�[�h���p
	FADE* pFade = GetInfoFade();

	//�t�F�[�h�C���J�n
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	InitShadow();
	//InitVisible_Rect();
	//InitVisible_Sphere();
	/* �����̏����ŏ����Z�b�g����ꍇ�����邽�ߐ�s */
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
//�`���[�g���A���I��
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
//�`���[�g���A���X�V
//************************************************
void UpdateTutorial(void)
{
	//�t�F�[�h���p
	FADE* pFade = GetInfoFade();

	/* ���������l�� */
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

	//�t�F�[�h�A�E�g��
	if (pFade->col.a >= 1.1f)
	{
		SetInfoMode(MODE_GAME);
	}
}

//************************************************
//�`���[�g���A���`��
//************************************************
void DrawTutorial(void)
{
	//�J�����̃Z�b�g
	SetInfoCamera(MODE_TUTORIAL);

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
	DrawTutorialDesign();

	//DrawVisible_Rect();
	//DrawVisible_Sphere();
}