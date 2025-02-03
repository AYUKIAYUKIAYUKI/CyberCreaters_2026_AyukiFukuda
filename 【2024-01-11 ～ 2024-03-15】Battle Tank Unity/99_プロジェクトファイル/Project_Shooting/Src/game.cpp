//==========================================================
//
//�Q�[����ʂ̕`�揈��[game.cpp]
//Author:kasai keisuke, ���c����
//
//==========================================================

/*---�y�C���N���[�h�t�@�C���z---*/
#include "game.h"

// �V�X�e���n
#include "input.h"
#include "main.h"
#include "sound.h"

// ������
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
// �f�o�b�O���̂�
#ifdef _DEBUG
#include "debugproc.h"
#include "editcamera.h"
#include "enemy_camera.h"
#include "enemy_layout.h"
#include "visible_box.h"
#include "visible_sph.h"
#include <assert.h>
#endif	// _DEBUG

/*---�y�O���[�o���ϐ��z---*/
int g_AmountPlayer = 0;		// �v���C�l���i�[
bool g_LayoutEdit = false;	// �z�u�ҏW���[�h�p�t���O
bool g_Layout_EN = false;	// �G�z�u�ҏW���[�h�p�t���O
int g_nCnt = 0;				// �f�o�b�N�p�ϐ�(�R���g���[�������m�F�p)
bool g_Pause = false;		// �|�[�Y����p�t���O
int g_nTimer = 0;			// �^�C�}�[�p�ϐ�
int g_nLateTime = 0;		// �{�X��|���������x������
bool g_bGameEnd = false;	// �{�X������ł��邩�ǂ���
int g_ScoreValue = 0;		// �X�R�A

//=======================================================================
//�Q�[����ʂ̏���������
//=======================================================================
void InitGame(void)
{
	PlaySound(SOUND_LABEL_GAME_BGM);
	//�e��ϐ��̏�����
	g_LayoutEdit = false;	// �z�u�ҏW���[�h���I�t
	g_Layout_EN = false;	// �G�z�u�ҏW���[�h���I�t
	g_nCnt = 0;				//�f�o�b�N�p�ϐ�(�R���g���[�������m�F�p)�̏�����
	g_Pause = false;		// �|�[�Y�t���O�𖳂���
	g_nTimer = 0;			// �^�C�}�[�p�ϐ��̏�����
	g_bGameEnd = false;
	g_nLateTime = 0;
	g_ScoreValue = 0;	// �X�R�A

	//�v���C�l���̎擾
	g_AmountPlayer = ReturnSelectPlayerCount() + 1;
	//g_AmountPlayer = 1;

#ifdef _DEBUG

	// �l�������������ƏI��
	assert(g_AmountPlayer > 0 && g_AmountPlayer <= 4);

	// �ҏW�J�����̏���
	InitEditCamera();

	// �G�̔z�u����
	Init_EN();

	// �G�ҏW�J��������
	Init_ENC();

	// ���̔����������
	InitVisibleBox();

	// ���̔����������
	InitVisibleSph();
	
#endif	// _DEBUG

	// �����O�G�t�F�N�g�����F��s
	InitEffect_Ring();

	// �e�̏����F��s
	InitShadow();

	// �\�����̗̑̓Q�[�W�̏����F��s
	InitObject_Bar();

	// �Q�[�W�̏���
	InitBar(g_AmountPlayer);

	//�{�X�̏���������
	InitBoss();

	//�{�X�̒e�̏���������
	InitBossBullet();

	// �e�̏���
	InitBullet();

	// �J�����̏���
	InitCamera(g_AmountPlayer);

	//�G�t�F�N�g�̏���������
	InitEffect();

	// ���j�G�t�F�N�g�̏���
	InitEffect_Burn();

	// �n�[�g�G�t�F�N�g����
	InitEffect_Heart();

	// ���̃G�t�F�N�g�̏���
	InitEffectSand();

	// ���G�t�F�N�g����
	InitEffect_Smoke();

	// ���G�t�F�N�g����
	InitEffect_Soul();

	// �G�̏���
	InitEnemy();

	// �����̏���
	InitExplosion();
	
	// �n�ʂ̏���
	InitField();

	// �A�C�e���̏���
	InitItem();

	// ���C�t�\���̏���
	InitLife(g_AmountPlayer);

	// ���C�g�̏���
	InitLight();

	// ���̏���
	InitObject();

	// �v���C���[�̏���
	InitPlayer(g_AmountPlayer);

	// �|�[�Y��ʂ̏���������
	InitPause();

	// �t�F�[�Y�\���̏���
	InitPhase(g_AmountPlayer);

	// �X�R�A�\���̏���
	InitScore(g_AmountPlayer);

	// �C�̏���
	InitSea();

	// ��̏���
	InitSky();

	// �^�C�}�[�\������
	InitTimer(g_AmountPlayer);

	// ����\���̏���
	InitWeapon(g_AmountPlayer);

	// �����[�h�\���̏���
	InitReload(g_AmountPlayer);

	//�t�F�[�h�C������
	SetFade(FADE_IN, MODE_MAX);//�t�F�[�h�C�����͓�ڂ̈������������̂łȂ�ł�����
}

//=======================================================================
//�Q�[����ʂ̏I������
//=======================================================================
void UninitGame(void)
{
	StopSound();
#ifdef _DEBUG

	// ���̔�������I��
	UninitVisibleBox();

	// ���̔�������I��
	UninitVisibleSph();

	// �G�̔z�u�I��
	Uninit_EN();

#endif	// _DEBUG

	// �Q�[�W�̏I��
	UninitBar();

	//�{�X�̏I������
	UninitBoss();

	// �e�̏I��
	UninitBullet();

	// �{�X�̒e�̏I������
	UninitBossBullet();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	// ���j�G�t�F�N�g�̏I��
	UninitEffect_Burn();

	// �n�[�g�G�t�F�N�g�I��
	UninitEffect_Heart();

	// ���̃G�t�F�N�g�̏I��
	UninitEffectSand();

	// ���G�t�F�N�g�I��
	UninitEffect_Smoke();

	// ���G�t�F�N�g�I��
	UninitEffect_Soul();

	// �����O�G�t�F�N�g�I��
	UninitEffect_Ring();

	// �G�̏I��
	UninitEnemy();

	// �����̏I��
	UninitExplosion();

	// �n�ʂ̏I��
	UninitField();

	// �A�C�e���̏I��
	UninitItem();

	// ���C�t�\���̏I��
	UninitLife();

	// ���̏I��
	UninitObject();

	// �\�����̗̑̓Q�[�W�̏I��
	UninitObject_Bar();

	//�|�[�Y��ʂ̏I������
	UninitPause();

	// �t�F�[�Y�\���̏I��
	UninitPhase();

	// �v���C���[�̏I��
	UninitPlayer();

	// �X�R�A�\���̏I��
	UninitScore();

	// �C�̏I��
	UninitSea();

	// �e�̏I��
	UninitShadow();

	// ��̏I��
	UninitSky();

	// �^�C�}�[�\���I��
	UninitTimer();

	// ����\���̏I��
	UninitWeapon();

	// �����[�h�\���̏I��
	UninitReload();
}

//=======================================================================
//�Q�[����ʂ̍X�V����
//=======================================================================
void UpdateGame(void)
{
	if (g_ScoreValue > 99999999)
	{ // ������z����ƌŒ�
		g_ScoreValue = 99999999;
	}

	if (g_ScoreValue < 0)
	{// �}�C�i�X�l�ɂȂ�̂�h��
		g_ScoreValue = 0;
	}
	if (GetJoypadTrigger(JOYKEY_START, 0) || GetKeyboardTrigger(DIK_P))
	{
		g_Pause = !g_Pause;
	}

	if (g_Pause)
	{ // �|�[�Y���̂�

		/*---�y������UI�̏����z---*/
		UpdatePause();	// �|�[�Y��ʂ̍X�V����

		return;	// �ȉ��̏����͍s��Ȃ�
	}

	// ���[�h�Ɋւ�炷�󋵂ɉ����ĕ��̍X�V
	UpdateObject(g_LayoutEdit);

#ifdef _DEBUG

	// �f�o�b�O�\���̍X�V(�z�z)
	UpdateDebugProc();

	// �z�u�ҏW���[�h�؂�ւ�
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
		// �ҏW�J�����̍X�V
		UpdateEditCamera();
	}
	else if (g_Layout_EN)
	{
		// �G�̔z�u�X�V
		Update_EN();

		// �G�ҏW�J�����̍X�V
		Update_ENC();
	}
	else
	{
		// �ʏ�J�����̍X�V
		UpdateCamera(g_AmountPlayer);
	}

#else 

	// �ʏ�J�����̍X�V
	UpdateCamera(g_AmountPlayer);

#endif // _DEBUG

	if (!g_LayoutEdit && !g_Layout_EN)
	{
		g_nTimer++;	// �^�C�}�[�p�ϐ��̉��Z

		// �\�����̗̑̓Q�[�W�̍X�V
		UpdateObject_Bar();

		// �Q�[�W�̍X�V
		UpdateBar();

		//�A�C�e���̍X�V
		UpdateItem();

		// ���C�t�\���̍X�V
		UpdateLife();

		// ���C�g�̍X�V
		UpdateLight();

		// �t�F�[�Y�\���̍X�V
		UpdatePhase();
		if (!g_bGameEnd)
		{

			// �{�X�̒e�̍X�V����
			UpdateBossBullet();


			// �v���C���[�̍X�V
			UpdatePlayer(g_AmountPlayer);

			// �e�̍X�V
			UpdateBullet();

			// �G�̍X�V
			UpdateEnemy();

		}


		//�{�X�̍X�V����
		UpdateBoss();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		// �����̍X�V
		UpdateExplosion();

		// ���j�G�t�F�N�g�̍X�V
		UpdateEffect_Burn();

		// �n�[�g�G�t�F�N�g�X�V
		UpdateEffect_Heart();

		// ���̃G�t�F�N�g�̍X�V
		UpdateEffectSand();

		// ���G�t�F�N�g�X�V
		UpdateEffect_Smoke();

		// ���G�t�F�N�g�X�V
		UpdateEffect_Soul();

		// �����O�G�t�F�N�g�X�V
		UpdateEffect_Ring();

		// �n�ʂ̍X�V
		UpdateField();

		// �X�R�A�\���̍X�V
		UpdateScore();

		// �C�̍X�V
		UpdateSea();

		// �e�̍X�V
		UpdateShadow();

		// ��̍X�V
		UpdateSky();

		// �^�C�}�[�\���X�V
		UpdateTimer();

		// ����\���̍X�V
		UpdateWeapon(g_AmountPlayer);

		// �����[�h�\���̍X�V
		UpdateReload();

#ifdef _DEBUG	

		// ���̔�������X�V
		UpdateVisibleSph();

#endif // _DEBUG
	}

#ifdef _DEBUG	

	// ���̔�������X�V
	UpdateVisibleBox();

#endif // _DEBUG�F�I�u�W�F�N�g�G�f�B�b�g���ł�����𓯊����邽��


	//******************************************************************
	// �Q�[���̏I������
	//******************************************************************
	if (CheckBossUse())
	{// �{�X������ł�����t���O��؂�ւ���
		g_bGameEnd = true;
	}

	if (CheckGameEnd())
	{
		//PlaySound(SOUND_LABEL_EXPLOSION_1);
		//�t�F�[�h�A�E�g����
		SetFade(FADE_OUT, MODE_RESULT_GAMECLEAR);//��ڂɈڍs��
	}
	if (!g_LayoutEdit && !g_Layout_EN)
	{ // �����ꂩ�̕ҏW���[�h�ł͖����ꍇ�̂�

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			//�t�F�[�h�A�E�g����
			SetFade(FADE_OUT, MODE_RESULT_GAMECLEAR);//��ڂɈڍs��
		}
	}
}

//=======================================================================
//�Q�[����ʂ̕`�揈��
//=======================================================================
void DrawGame(void)
{
	int Loop = 0;	// ���[�v��

	// �l���ɉ����ĕ`��񐔂�ύX
	g_LayoutEdit ? Loop = 1 : Loop = g_AmountPlayer;

	for (int i = 0; i < Loop; i++)
	{
#ifdef _DEBUG

		if (g_LayoutEdit)
		{
			// �ҏW�J������ݒ�
			SetInfoEditCamera();
		}
		else if (g_Layout_EN)
		{
			// �G�ҏW�J������ݒ�
			SetInfo_ENC();
		}
		else
		{
			// �ʏ�̃J������ݒ�
			SetInfoCamera(i, g_AmountPlayer);
		}

#else

		// �ʏ�̃J������ݒ�
		SetInfoCamera(i, g_AmountPlayer);

#endif // _DEBUG


		// ��̕`��
		DrawSky();

		// �C�̕`��
		DrawSea();

		// �n�ʂ̕`��
		DrawField();

		// ���̃G�t�F�N�g�̕`��
		DrawEffectSand();

		// �e�̕`��
		DrawShadow();

		// �����O�G�t�F�N�g�`��
		DrawEffect_Ring();

		// ���j�G�t�F�N�g�̕`��
		DrawEffect_Burn();

		//�G�t�F�N�g�̕`��
		DrawEffect();

		// �󋵂ɉ����ĕ��̕`��
		DrawObject(g_LayoutEdit);

#ifdef _DEBUG


		if (g_Layout_EN)
		{
			// �G�̔z�u�`��
			Draw_EN();
		}
		else
		{
			// �G�̕`��
			DrawEnemy();
		}

#else

		// �G�̕`��
		DrawEnemy();

#endif // _DEBUG

		// �{�X�̕`�揈��
		DrawBoss();

		// �A�C�e���̕`��
		DrawItem();

		// �����̕`��
		DrawExplosion();

		// ���G�t�F�N�g�̕`��
		DrawEffect_Smoke();

		// �e�̕`��
		DrawBullet();

		// �{�X�̒e�̕`�揈��
		DrawBossBullet();

		// �n�[�g�G�t�F�N�g�`��
		DrawEffect_Heart();

		// ���G�t�F�N�g�`��
		DrawEffect_Soul();

		// �v���C���[�̕`��
		DrawPlayer();

		// �\�����̗̑̓Q�[�W�̕`��
		DrawObject_Bar();

#ifdef _DEBUG

		// ���̔�������`��
		DrawVisibleBox();

		// ���̔�������`��
		DrawVisibleSph();

#endif	// _DEBUG
	}

	// UI�p�|�[�g�̐ݒ�
	SetInfoUIport();

	/*---�y�Q�[����UI�̕\���͂������牺�ōs���܂��z---*/

	if (!g_LayoutEdit && !g_Layout_EN)
	{ // �G�f�B�b�g���͕`�悵�Ȃ�

		// ���C�t�\���̕`��
		DrawLife();

		// ����\���̕`��
		DrawWeapon();

		// �����[�h�\���̕`��
		DrawReload();

		// �Q�[�W�̍X�V
		DrawBar();

		// �t�F�[�Y�\���̕`��
		DrawPhase();

		// �X�R�A�\���̕`��
		DrawScore();

		// �^�C�}�[�\���`��
		DrawTimer();
	}

	if (g_Pause)
	{// �|�[�Y���Ȃ�
		DrawPause();
	}

#ifdef _DEBUG

	// �f�o�b�O�p�\���̕`��(�z�z)
	DrawDebugProc();

#endif	// _DEBUG
}

//=======================================================================
//�|�[�Y�̗L�������ݒ�
//=======================================================================
void SetEnablePause(bool bPause)
{
	g_Pause = bPause;
}

//=======================================================================
//�{�X�����񂾌�̒x������
//=======================================================================
bool CheckGameEnd(void)
{
	if (g_bGameEnd)
	{// �{�X�����񂾂��ƒx�����ԗp�̕ϐ������Z
		g_nLateTime++;
	}

	if (g_nLateTime >= MAX_LATE)
	{// ��莞�Ԃ��o�߂�����true��Ԃ�
		return true;
	}
	else
	{// ��莞�Ԃ��o�߂��Ă��Ȃ�������false��Ԃ�
		return false;
	}
}

/*---�y�ȉ��Q�[�����[�v�O�z---*/

//************************************************
// �ҏW���[�h�̃t���O�擾
//************************************************
bool GetLayoutEdit(void)
{
	return g_LayoutEdit;
}

//************************************************
// �G�ҏW���[�h�̃t���O�擾
//************************************************
bool GetLayout_EN(void)
{
	return g_Layout_EN;
}

//************************************************
// �X�R�A�擾
//************************************************
int* GetInfoScore(void)
{
	return &g_ScoreValue;
}

//************************************************
// ��Ԍp���J�E���g�p
//************************************************
bool CntDuration(int* dur)
{
	bool finish = false;

	if (*dur > 0)
	{ // �p�����Ԍ���
		*dur -= 1;	// �Ȃ��f�N�������g��Ή��H
	}
	else
	{ // �p�����Ԃ������Ȃ��

		// ������Ԃ�
		finish = true;
	}

	return finish;
}

/*--------------------------------------------------------*/

//************************************************
// �C���Q�[���I���t���O�A�N�Z�X�p
//************************************************
bool* GetInfoEndGame(void)
{
	return &g_bGameEnd;
}