//************************************************
//
//�Q�[�����쏈��[game.cpp]
//Author�F���c����
//
//************************************************
#include "input.h"
#include "main.h"
#include "sound.h"
#include "bg.h"
#include "block.h"
#include "breakblock.h"
#include "bullet.h"
#include "bush.h"
#include "effect_bullet.h"
#include "effect_comet.h"
#include "effect_spawn.h"
#include "enemy.h"
#include "enemy_glide.h"
#include "enemy_slide.h"
#include "enemy_spiral.h"
#include "fg.h"
#include "guage.h"
#include "guagebar.h"
#include "item.h"
#include "leaves.h"
#include "life.h"
#include "particle.h"
#include "particle_block.h"
#include "pause.h"
#include "player.h"
#include "score.h"
#include "slideblock.h"
#include "style.h"
#include "timer.h"
#include "window_bullet.h"
#include "wreath.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Game = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Game = NULL;	//���_�o�b�t�@�̃|�C���^
int g_nColorA_Fade_Gmae = 255;	//�t�F�[�h�p�A���t�@�l�i�[
bool g_bStart_Game = false;
int g_nFreeze_Game = 0;		//�Q�[�����~�߂�
bool g_bStop_Gmae = false;	//�|�[�Y��ʗp

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Game(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLACK_GAME,
		&g_pTexture_Game);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_GAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Game,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Game;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Game->Lock(0, 0, (void**)&pVtx_Game, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAME; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Game[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Game[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Game[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Game[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Game[0].rhw = 1.0f;
		pVtx_Game[1].rhw = 1.0f;
		pVtx_Game[2].rhw = 1.0f;
		pVtx_Game[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Game[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Game[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Game[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Game[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Game[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Game[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Game[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Game[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Game += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Game->Unlock();

	//�|���S���̏���������
	Init_BG();
	Init_Block();
	Init_BreakBlock();
	Init_Bullet();
	Init_Bush();
	Init_Effect_Bullet();
	Init_Effect_Comet();
	Init_Effect_Spawn();
	Init_Enemy();
	Init_Enemy_Glide();
	Init_Enemy_Slide();
	Init_Enemy_Spiral();
	Init_FG();
	Init_Guage();
	Init_GuageBar();
	Init_Item();
	Init_Leaves();
	Init_Life();
	Init_Particle();
	Init_Particle_Block();
	Init_Pause();
	Init_Player();
	Init_Score();
	Init_SlideBlock();
	Init_Style();
	Init_Timer();
	Init_Window_Bullet();
	Init_Wreath();

	//�t�F�[�h�����ݒ�
	g_nColorA_Fade_Gmae = 255;

	g_bStart_Game = false;

	//����d��������
	g_nFreeze_Game = 0;

	//�|�[�Y������
	g_bStop_Gmae = false;

	//����̂݃|���S����W�J
	SetPos_Vtx_Game();

	PlaySound(SOUND_LABEL_BGM001);
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Game(void)
{
	//�|���S���̏I������
	Uninit_BG();
	Uninit_Block();
	Uninit_BreakBlock();
	Uninit_Bullet();
	Uninit_Bush();
	Uninit_Effect_Bullet();
	Uninit_Effect_Comet();
	Uninit_Effect_Spawn();
	Uninit_Enemy();
	Uninit_Enemy_Glide();
	Uninit_Enemy_Slide();
	Uninit_Enemy_Spiral();
	Uninit_FG();
	Uninit_Guage();
	Uninit_GuageBar();
	Uninit_Item();
	Uninit_Leaves();
	Uninit_Life();
	Uninit_Particle();
	Uninit_Particle_Block();
	Uninit_Pause();
	Uninit_Player();
	Uninit_Score();
	Uninit_SlideBlock();
	Uninit_Style();
	Uninit_Timer();
	Uninit_Window_Bullet();
	Uninit_Wreath();

	//BGM���~�߂�
	StopSound();
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Game(void)
{
	if (g_nColorA_Fade_Gmae > 0 && !g_bStart_Game)
	{
		//�t�F�[�h�C���A�j���[�V����
		Fadein_Animation_Game();

		//�t�F�[�h�����n���ɓ����Ăė~�����f�ނ̊F����
		Update_BG();
		Update_Bush();
		Update_FG();
		Update_Leaves();
	}
	else
	{
		//�v���C���[���ւ̃|�C���^
		PLAYER* pPlayer;

		//�������ԏ��ւ̃|�C���^
		int* pTimer;

		//�v���C���[���̎擾
		pPlayer = Getinfo_Player();	//�v���C���[���n�̐擪�A�h���X����������

		//�c�莞�Ԃ̎擾
		pTimer = Getinfo_Timer();	//�A�h���X���

		//�v���C���[�������Ă���Ƃ��|�[�Y�\
		if (!g_bStop_Gmae && GetKeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true
			|| GetJoypadTrigger(JOYKEY_BACK) == true && pPlayer->nCntState != PLAYERSTATE_DEATH)
		{
			g_bStop_Gmae = true;

			//���ʉ���炷
			PlaySound(SOUND_LABEL_SE_PAUSE);

			//�|�[�Y����������x
			//Init_Pause();
		}
		else if (g_bStop_Gmae)
		{
			Update_Pause();
		}

		//�ʏ펞
		if (!g_bStop_Gmae)
		{
			//�v���C���[�����ʂ��A�^�C�}�[��0��
			if (pPlayer->state == PLAYERSTATE_DEATH || *pTimer <= 0)
			{
				//�x���J�E���g
				g_nFreeze_Game++;
			}
			//�Q�[���ʏ�i�s���̏���
			else
			{
				//�|���S���̍X�V����
				Update_BG();
				Update_Block();
				Update_BreakBlock();
				Update_Bullet();
				Update_Bush();
				Update_Effect_Bullet();
				Update_Effect_Comet();
				Update_Effect_Spawn();
				Update_Enemy();
				Update_Enemy_Glide();
				Update_Enemy_Slide();
				Update_Enemy_Spiral();
				Update_FG();
				Update_Guage();
				Update_Item();
				Update_Leaves();
				Update_Particle();
				Update_Particle_Block();
				Update_Score();
				Update_SlideBlock();
				Update_Style();
			}

			//0�ɂȂ�̂������邽��
			Update_Timer();

			//���C�t����ɂȂ�\���̂���
			Update_Life(pPlayer->nLife);

			//���S���̌����ڂɕύX���邽��
			Update_Player();

			//�x���I��
			if (g_nFreeze_Game >= AMOUNT_CNT_FINISH_GAME)
			{
				Fadeout_Animation_Game();

				if (g_nColorA_Fade_Gmae >= 255)
				{
					Setinfo_Mode(MODE_RANKING);	//�����L���O���[�h�ɐݒ�
				}
			}
		}
	}
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Game(void)
{
	Draw_BG();
	Draw_Block();
	Draw_SlideBlock();
	Draw_BreakBlock();
	Draw_Effect_Bullet();
	Draw_Effect_Comet();
	Draw_Effect_Spawn();
	Draw_Enemy();
	Draw_Enemy_Glide();
	Draw_Enemy_Slide();
	Draw_Enemy_Spiral();
	Draw_Bullet();
	Draw_Item();
	Draw_Particle();
	Draw_Particle_Block();
	Draw_Player();

	Draw_Leaves();

	Draw_Bush();
	Draw_FG();

	//���C���[����
	Draw_Wreath();
	Draw_Guage();
	Draw_GuageBar();
	Draw_Style();
	Draw_Window_Bullet();
	Draw_Life();
	
	//�|�[�Y����Ă���Ƃ���ʕ���
	if (g_bStop_Gmae)
	{
		Draw_Pause();
	}

	//�|�[�Y�\�������D��\��
	Draw_Score();
	Draw_Timer();

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Game, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Game);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//���_��W�J����֐�
//************************************************
void SetPos_Vtx_Game(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Game;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Game->Lock(0, 0, (void**)&pVtx_Game, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAME; nCnt++)
	{
		pVtx_Game[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Game[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx_Game[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx_Game[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		pVtx_Game[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
		pVtx_Game[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
		pVtx_Game[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
		pVtx_Game[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);

		pVtx_Game += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Game->Unlock();
}

//************************************************
//�t�F�[�h�C���֐�
//************************************************
void Fadein_Animation_Game(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Game;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Game->Lock(0, 0, (void**)&pVtx_Game, 0);

	g_nColorA_Fade_Gmae -= CHANGE_SPD_FADE_COLORA_GAME;

	//�F�ς�肷���h�~
	if (g_nColorA_Fade_Gmae <= 0)
	{
		g_bStart_Game = true;

		g_nColorA_Fade_Gmae = 0;
	}

	//�F�ύX
	pVtx_Game[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
	pVtx_Game[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
	pVtx_Game[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
	pVtx_Game[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Game->Unlock();
}

//************************************************
//�t�F�[�h�A�E�g�֐�
//************************************************
void Fadeout_Animation_Game(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Game;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Game->Lock(0, 0, (void**)&pVtx_Game, 0);

	g_nColorA_Fade_Gmae += CHANGE_SPD_FADE_COLORA_GAME;

	//�F�ς�肷���h�~
	if (g_nColorA_Fade_Gmae >= 255)
	{
		g_nColorA_Fade_Gmae = 255;
	}

	//�F�ύX
	pVtx_Game[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
	pVtx_Game[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
	pVtx_Game[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
	pVtx_Game[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Game->Unlock();
}

//************************************************
//�|�[�Y��cpp��bool�̃A�h���X�n�������̊֐�
//************************************************
bool* Getinfo_Pause(void)
{
	return &g_bStop_Gmae;	//�|�[�Y�̔��肷��ϐ��̃A�h���X��n��
}