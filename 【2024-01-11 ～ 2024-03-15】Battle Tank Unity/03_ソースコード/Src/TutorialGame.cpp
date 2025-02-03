//==========================================================
//
//�`���[�g���A�����̃Q�[����ʂ̕`�揈��[game.cpp]
//Author:kasai keisuke, ���c����,satokurara
//
//==========================================================

/* �C���N���[�h�t�@�C�� */
#include "game.h"
// ����
#include "input.h"
#include "main.h"
#include "sound.h"
// ������
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
// �f�o�b�O��
#ifdef _DEBUG
#include "debugproc.h"
#include "editcamera.h"

#include "visible_sph.h"
#include "visible_box.h"
#include <assert.h>
#endif	// _DEBUG

/*/ �}�N����` /*/
#define JOIN_VERIFY 4	// �l���w��

/*/ �O���[�o���ϐ� /*/
int g_AmountPlayer_Tutorial = JOIN_VERIFY;	// �v���C�l���i�[
int g_nCnt_Tuto = 0;						//�f�o�b�N�p�ϐ�(�R���g���[�������m�F�p)
bool g_LayoutEdit_Tutorial = false;			// �z�u�ҏW���[�h�p�t���O


//=======================================================================
//�Q�[����ʂ̏���������
//=======================================================================
void InitTutorialGame(void)
{
#ifndef JOIN_VERIFY

	// �l���w�肪������ΌŒ�
	g_AmountPlayer_Tuto = 1;

#endif	// JOIN_VERIFY

	//�e��ϐ��̏�����
	g_LayoutEdit_Tutorial = false;	// �z�u�ҏW���[�h���I�t
	g_nCnt_Tuto = 0;				//�f�o�b�N�p�ϐ�(�R���g���[�������m�F�p)�̏�����
	g_AmountPlayer_Tutorial = 0;	// �v���C�l���̏�����
	//�v���C�l���̎擾
	g_AmountPlayer_Tutorial = ReturnSelectPlayerCount() + 1;

#ifdef _DEBUG

	// �l�������������ƏI��
	assert(g_AmountPlayer_Tutorial > 0 && g_AmountPlayer_Tutorial <= 4);

	// ���̔����������
	InitVisibleSph();

	//�l�p�̔����������
	InitVisibleBox();

#endif	// _DEBUG

	//UI�̏�����
	InitTutorial();

	// �e�̏���
	InitBullet();

	// �J�����̏���
	InitCamera(g_AmountPlayer_Tutorial);

	//�G�t�F�N�g�̏���������
	InitEffect();

	// ���̃G�t�F�N�g�̏���
	InitEffectSand();

	// ���̃G�t�F�N�g�̏���������
	InitEffect_Smoke();

	// �����̏���
	InitExplosion();

	// ���̏���������
	InitField();

	// �A�C�e���̏���
	InitItem();

	// ���C�g�̏���
	InitLight();

	// ���̏���
	InitObject();

	// �v���C���[�̏���
	InitPlayer(g_AmountPlayer_Tutorial);

	// �C�̏���
	InitSea();

	// ��̏���
	InitSky();
}

//=======================================================================
//�Q�[����ʂ̏I������
//=======================================================================
void UninitTutorialGame(void)
{
#ifdef _DEBUG


	// ���̔�������I��
	UninitVisibleSph();

	//�l�p�̔���̉����I��
	UninitVisibleBox();

#endif	// _DEBUG

	//UI�̏I��
	UninitTutorial();

	// �e�̏I��
	UninitBullet();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	// ���̃G�t�F�N�g�̏I��
	UninitEffectSand();

	// ���̃G�t�F�N�g�̏I������
	UninitEffect_Smoke();

	// �����̏I��
	UninitExplosion();

	// ���̏I������
	UninitField();

	// �A�C�e���̏I��
	UninitItem();

	// ���̏I��
	UninitObject();

	// �v���C���[�̏I��
	UninitPlayer();

	//UI�̏���
	UninitTutorial();

	// �C�̏I��
	UninitSea();

	// ��̏I��
	UninitSky();
}

//======================================================================
//�`���[�g���A�����̃Q�[���X�V����
//======================================================================
void UpdateTutorialGame(void)
{

#if defined (_DEBUG)

	// �z�u�ҏW���[�h�؂�ւ�
	if (GetKeyboardTrigger(DIK_F2))
	{
		g_LayoutEdit_Tutorial = !g_LayoutEdit_Tutorial;
	}

	if (!g_LayoutEdit_Tutorial)
	{ // �z�u�ҏW���[�h�łȂ��Ƃ��̂�
		// �Q���l���𒼐ڕύX
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
	// �f�o�b�O�\���̍X�V(�z�z)
	UpdateDebugProc();

#endif // DEBUG


	// �J���� or �ҏW�J�����̍X�V
	g_LayoutEdit_Tutorial ? UpdateEditCamera() : UpdateCamera(g_AmountPlayer_Tutorial);



#endif	// _DEBUG

#ifndef _DEBUG

	// �J�����̍X�V
	UpdateCamera(g_AmountPlayer_Tutorial);

#endif // _DEBUG �����[�X

	// �󋵂ɉ����ĕ��̍X�V
	UpdateObject(g_LayoutEdit_Tutorial);

	if (!g_LayoutEdit_Tutorial)
	{
		//�A�C�e���̍X�V
		UpdateItem();

		// ���C�g�̍X�V
		UpdateLight();

		// �v���C���[�̍X�V
		UpdatePlayer(g_AmountPlayer_Tutorial);

		// �e�̍X�V
		UpdateBullet();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//UI�̍X�V
		UpdateTutorial();

		// �����̍X�V
		UpdateExplosion();

		// ���̃G�t�F�N�g�̍X�V
		UpdateEffectSand();

		// ���̃G�t�F�N�g�̍X�V����
		UpdateEffect_Smoke();

		// ���̍X�V����
		UpdateField();

		// �C�̍X�V
		UpdateSea();

		// ��̍X�V
		UpdateSky();

#ifdef _DEBUG	

		// ���̔�������X�V
		UpdateVisibleSph();

		// �l�p�̔�������X�V
		UpdateVisibleBox();

#endif // _DEBUG �����ꂱ���ɒu������
	}
}

//=======================================================================
//�`���[�g���A�����̃Q�[����ʂ̕`�揈��
//=======================================================================
void DrawTutorialGame(void)
{
	// ���[�v��
	int Loop = 0;

	// �z�u�ҏW���[�h�ł���Η]���ȕ`���}��
	g_LayoutEdit_Tutorial ? Loop = 1 : Loop = g_AmountPlayer_Tutorial;

	for (int i = 0; i < Loop; i++)
	{
#ifdef _DEBUG

		// �J���� or �ҏW�J�����̐ݒ�
		g_LayoutEdit_Tutorial ? SetInfoEditCamera() : SetInfoCamera(i, g_AmountPlayer_Tutorial);

#else

		// �J�����̐ݒ�
		SetInfoCamera(i, g_AmountPlayer_Tutorial);

#endif	// _DEBUG �����[�X

		// ��̕`��
		DrawSky();

		// �C�̕`��
		DrawSea();

		// �󋵂ɉ����ĕ��̕`��
		DrawObject(g_LayoutEdit_Tutorial);

		// �A�C�e���̕`��
		DrawItem();

		// ���̕`�揈��
		DrawField();

		// ���̃G�t�F�N�g�̕`��
		DrawEffectSand();

		// �����̕`��
		DrawExplosion();

		// ���̃G�t�F�N�g�̕`�揈��
		DrawEffect_Smoke();

		//�G�t�F�N�g�̕`��
		DrawEffect();

		// �e�̕`��
		DrawBullet();

		// �v���C���[�̕`��
		DrawPlayer();

#ifdef _DEBUG

		// ���̔�������`��
		DrawVisibleSph();

		// �l�p�̔�������`��
		DrawVisibleBox();

#endif	// _DEBUG
	}

	// UI�p�|�[�g�̐ݒ�
	SetInfoUIport();

	//UI�̕`��
	DrawTutorial();

	/*---�y�Q�[����UI�̕\���͂������牺�ōs���܂��z---*/

#ifdef _DEBUG

	// �e�X�g�p�̕`��
	if (!g_LayoutEdit_Tutorial)
	{
		//DrawTEST();	//!< UI�n�̓|�[�g�ݒ肳��Ă��Ȃ��͈͂̕`��͍s���܂���B�͂ݏo��悤�Ȃ�V���Ƀ|�[�g�ݒ��ǉ����Ă��������B
	}

	// �f�o�b�O�p�\���̕`��(�z�z)
	DrawDebugProc();

#endif	// _DEBUG
}

/*---�y�ȉ��Q�[�����[�v�O�z---*/

