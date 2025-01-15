//************************************************
//
//���@����[player.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "attack_box.h"
#include "bomb.h"
#include "camera.h"
#include "effect_jump.h"
#include "particle.h"
#include "player.h"
#include "stage.h"
#include "tower.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Player[AMOUNT_TEX_PLAYER] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Player = NULL;	//���_�o�b�t�@�̃|�C���^
PLAYER g_aPlayer;	//�v���C���[���
PLAYER_BOX g_aPlayer_Box[PLAYER_STATE_MAX];	//�v���C���[�{�b�N�X���

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Player()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_IDLE_PLAYER,
		&g_pTexture_Player[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_JUMP_PLAYER,
		&g_pTexture_Player[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_LAND_PLAYER,
		&g_pTexture_Player[2]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_RUN_PLAYER,
		&g_pTexture_Player[3]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_LIGHT1_PLAYER,
		&g_pTexture_Player[4]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_LIGHT2_PLAYER,
		&g_pTexture_Player[5]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_LIGHT3_PLAYER,
		&g_pTexture_Player[6]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_HEAVY1_PLAYER,
		&g_pTexture_Player[7]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_HEAVY2_PLAYER,
		&g_pTexture_Player[8]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_HEAVY3_PLAYER,
		&g_pTexture_Player[9]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_HURT1_PLAYER,
		&g_pTexture_Player[10]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_HURT2_PLAYER,
		&g_pTexture_Player[11]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Player,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Player;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Player->Lock(0, 0, (void**)&pVtx_Player, 0);

	//���_���W�̏����ݒ�
	pVtx_Player[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Player[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Player[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Player[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Player[0].rhw = 1.0f;
	pVtx_Player[1].rhw = 1.0f;
	pVtx_Player[2].rhw = 1.0f;
	pVtx_Player[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Player[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Player[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Player[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Player[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Player[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Player[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Player[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Player[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Player->Unlock();

	//�v���C���[�\���̂̏��̏������Q
	g_aPlayer.nState = PLAYER_STATE_IDLE;
	g_aPlayer.BGpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.lastland = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_aPlayer.LR = 0;
	g_aPlayer.nCntTex = 0;
	g_aPlayer.nCntPattern = 0;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aPlayer.fTexSpan[nCnt] = 0.0f;
		g_aPlayer.fRadius[nCnt] = 0.0f;
		g_aPlayer.fLength[nCnt] = 0.0f;
		g_aPlayer.fAngle[nCnt] = 0.0f;
	}
	g_aPlayer.bLanding = false;
	g_aPlayer.nJumpTimes = 0;
	//g_aPlayer.nLife = 0;
	g_aPlayer.bFell = false;
	g_aPlayer.nLastATK = 0;
	g_aPlayer.bAfterATK = false;
	g_aPlayer.nCntAfterATK = 0;

	//�v���C���[�{�b�N�X�̏�����
	for (int nCnt = 0; nCnt < PLAYER_STATE_MAX; nCnt++)
	{
		for (int nCntHold = 0; nCntHold < 2; nCntHold++)
		{
			g_aPlayer_Box[nCnt].fRadius_Hold[nCntHold];
			g_aPlayer_Box[nCnt].fLength_Hold[nCntHold];
			g_aPlayer_Box[nCnt].fAngle_Hold[nCntHold];
		}
	}

	//�v���C���[�{�b�N�X�̎Z�o
	CalcSize_Player_Box();

	//�v���C���[�\���̂ɏ���t�^
	SetInfo_Player();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Player(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEX_PLAYER; nCnt++)
	{
		if (g_pTexture_Player[nCnt] != NULL)
		{
			g_pTexture_Player[nCnt]->Release();
			g_pTexture_Player[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Player != NULL)
	{
		g_pVtxBuff_Player->Release();
		g_pVtxBuff_Player = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Player(void)
{
	//�L�[���͂ňړ�����
	Move_Pos_Player();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Player(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Player, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	switch (g_aPlayer.nState)
	{
	case PLAYER_STATE_IDLE:
		pDevice->SetTexture(0, g_pTexture_Player[0]);
		break;
	case PLAYER_STATE_JUMP:
		pDevice->SetTexture(0, g_pTexture_Player[1]);
		break;
	case PLAYER_STATE_FALL:
		pDevice->SetTexture(0, g_pTexture_Player[1]);
		break;
	case PLAYER_STATE_LAND:
		pDevice->SetTexture(0, g_pTexture_Player[2]);
		break;
	case PLAYER_STATE_RUN:
		pDevice->SetTexture(0, g_pTexture_Player[3]);
		break;
	case PLAYER_STATE_LIGHT1:
		pDevice->SetTexture(0, g_pTexture_Player[4]);
		break;
	case PLAYER_STATE_LIGHT2:
		pDevice->SetTexture(0, g_pTexture_Player[5]);
		break;
	case PLAYER_STATE_LIGHT3:
		pDevice->SetTexture(0, g_pTexture_Player[6]);
		break;
	case PLAYER_STATE_HEAVY1:
		pDevice->SetTexture(0, g_pTexture_Player[7]);
		break;
	case PLAYER_STATE_HEAVY2:
		pDevice->SetTexture(0, g_pTexture_Player[8]);
		break;
	case PLAYER_STATE_HEAVY3:
		pDevice->SetTexture(0, g_pTexture_Player[9]);
		break;
	case PLAYER_STATE_HURT1:
		pDevice->SetTexture(0, g_pTexture_Player[10]);
		break;
	case PLAYER_STATE_HURT2:
		pDevice->SetTexture(0, g_pTexture_Player[11]);
		break;
	}

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//�v���C���[�̒��_�T�C�Y���Z�o�֐�
//************************************************
void CalcSize_Player_Box(void)
{
	for (int nCnt = 0; nCnt < PLAYER_STATE_MAX; nCnt++)
	{
		switch (nCnt)
		{
		case PLAYER_STATE_IDLE:
			//�Ίp���̒���
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf((RADIUS_PLAYER_X * RADIUS_PLAYER_X) +
				((RADIUS_PLAYER_Y * 2.0f) * (RADIUS_PLAYER_Y * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf((RADIUS_PLAYER_X * RADIUS_PLAYER_X));

			//�Ίp���̊p�x
			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f(RADIUS_PLAYER_X * 2.0f, (RADIUS_PLAYER_Y * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f(RADIUS_PLAYER_X * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_JUMP:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 1.1875f) * (RADIUS_PLAYER_X * 1.1875f)) +
				(((RADIUS_PLAYER_Y * 1.1875f) * 2.0f) * ((RADIUS_PLAYER_Y * 1.1875f) * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 1.1875f) * (RADIUS_PLAYER_X * 1.1875f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 1.1875f) * 2.0f, ((RADIUS_PLAYER_Y * 1.1875f) * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 1.1875f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_LAND:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 1.1f) * (RADIUS_PLAYER_X * 1.1f)) +
				((RADIUS_PLAYER_Y * 2.0f) * (RADIUS_PLAYER_Y * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 1.1f) * (RADIUS_PLAYER_X * 1.1f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 1.1f) * 2.0f, (RADIUS_PLAYER_Y * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 1.1f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_RUN:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf((RADIUS_PLAYER_X * RADIUS_PLAYER_X) +
				(((RADIUS_PLAYER_Y * 1.15f) * 2.0f) * ((RADIUS_PLAYER_Y * 1.15f) * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf((RADIUS_PLAYER_X * RADIUS_PLAYER_X));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f(RADIUS_PLAYER_X * 2.0f, ((RADIUS_PLAYER_Y * 1.15f) * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f(RADIUS_PLAYER_X * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_LIGHT1:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 2.0f) * (RADIUS_PLAYER_X * 2.0f)) +
				((RADIUS_PLAYER_Y * 2.0f) * (RADIUS_PLAYER_Y * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 2.0f) * (RADIUS_PLAYER_X * 2.0f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 2.0f) * 2.0f, (RADIUS_PLAYER_Y * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 2.0f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_LIGHT2:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 1.75f) * (RADIUS_PLAYER_X * 1.75f)) +
				((RADIUS_PLAYER_Y * 2.0f) * (RADIUS_PLAYER_Y * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 1.75f) * (RADIUS_PLAYER_X * 1.75f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 1.75f) * 2.0f, (RADIUS_PLAYER_Y * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 1.75f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_LIGHT3:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 2.0f) * (RADIUS_PLAYER_X * 2.0f)) +
				((RADIUS_PLAYER_Y * 2.0f) * (RADIUS_PLAYER_Y * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 2.0f) * (RADIUS_PLAYER_X * 2.0f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 2.0f) * 2.0f, (RADIUS_PLAYER_Y * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 2.0f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_HEAVY1:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 2.3f) * (RADIUS_PLAYER_X * 2.3f)) +
				(((RADIUS_PLAYER_Y * 1.1f) * 2.0f) * ((RADIUS_PLAYER_Y * 1.1f) * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 2.3f) * (RADIUS_PLAYER_X * 2.3f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 2.3f) * 2.0f, ((RADIUS_PLAYER_Y * 1.1f) * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 2.3f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_HEAVY2:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 2.15f) * (RADIUS_PLAYER_X * 2.15f)) +
				(((RADIUS_PLAYER_Y) * 2.0f) * ((RADIUS_PLAYER_Y) * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 2.15f) * (RADIUS_PLAYER_X * 2.15f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 2.15f) * 2.0f, ((RADIUS_PLAYER_Y) * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 2.15f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_HEAVY3:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 3.0f) * (RADIUS_PLAYER_X * 3.0f)) +
				(((RADIUS_PLAYER_Y * 1.4f) * 2.0f) * ((RADIUS_PLAYER_Y * 1.4f) * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 3.0f) * (RADIUS_PLAYER_X * 3.0f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 3.0f) * 2.0f, ((RADIUS_PLAYER_Y * 1.4f) * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 3.0f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_HURT1:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf((RADIUS_PLAYER_X * RADIUS_PLAYER_X) +
				((RADIUS_PLAYER_Y * 2.0f) * (RADIUS_PLAYER_Y * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf((RADIUS_PLAYER_X * RADIUS_PLAYER_X));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f(RADIUS_PLAYER_X * 2.0f, (RADIUS_PLAYER_Y * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f(RADIUS_PLAYER_X * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_HURT2:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 1.1f) * (RADIUS_PLAYER_X * 1.1f)) +
				((RADIUS_PLAYER_Y * 2.0f) * (RADIUS_PLAYER_Y * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 1.1f) * (RADIUS_PLAYER_X * 1.1f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 1.1f) * 2.0f, (RADIUS_PLAYER_Y * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 1.1f) * 2.0f, 0.0f);
			break;
		}
	}
}

//************************************************
//�v���C���[�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Player(void)
{
	g_aPlayer.BGpos = D3DXVECTOR3(SCREEN_HALFWIDTH, SCREEN_HALFHEIGHT, 0.0f);
	g_aPlayer.pos = g_aPlayer.BGpos;
	g_aPlayer.oldpos = g_aPlayer.pos;
	g_aPlayer.fTexSpan[0] = 0.0f;
	g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
	g_aPlayer.fRadius[0] = RADIUS_PLAYER_X;
	g_aPlayer.fRadius[1] = RADIUS_PLAYER_Y;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aPlayer.fLength[nCnt] = g_aPlayer_Box[PLAYER_STATE_IDLE].fLength_Hold[nCnt];
		g_aPlayer.fAngle[nCnt] = g_aPlayer_Box[PLAYER_STATE_IDLE].fAngle_Hold[nCnt];
	}
	//g_aPlayer.nJumpTimes = AMOUNT_ABLE_JUMPS;
	//g_aPlayer.nLife = AMOUNT_MAX_LIFE_PLAYER;
}

//************************************************
//�L�[���͂ňړ�����֐�
//************************************************
void Move_Pos_Player(void)
{
	//�ߋ��̈ʒu���L�^
	g_aPlayer.oldpos = g_aPlayer.pos;

	//�U�����肪�o�Ă���ꍇ�A���Ԃ��v��
	if (g_aPlayer.bAfterATK)
	{
		g_aPlayer.nCntAfterATK++;

		if (g_aPlayer.nLastATK == PLAYER_STATE_LIGHT1 ||
			g_aPlayer.nLastATK == PLAYER_STATE_LIGHT2 ||
			g_aPlayer.nLastATK == PLAYER_STATE_LIGHT3)
		{
			//��莞�Ԍo�ƁA�U����̔���𖳂���
			if (g_aPlayer.nCntAfterATK > AMOUNT_CT_LIGHT_COMBO)
			{
				g_aPlayer.nLastATK = 0;
				g_aPlayer.bAfterATK = false;
				g_aPlayer.nCntAfterATK = 99;
			}
		}
		else
		{
			if (g_aPlayer.nCntAfterATK > AMOUNT_CT_HEAVY_COMBO)
			{
				g_aPlayer.nLastATK = 0;
				g_aPlayer.bAfterATK = false;
				g_aPlayer.nCntAfterATK = 99;
			}
		}
	}

	if (!g_aPlayer.bFell)
	{
		//��e���͈�؂̑�����󂯕t���Ȃ�
		if (g_aPlayer.nState != PLAYER_STATE_HURT1 &&
			g_aPlayer.nState != PLAYER_STATE_HURT2)
		{
			//�U��
			if (GetKeyboardTrigger(DIK_O) || GetJoypadTrigger(JOYKEY_B))
			{
				SetInfo_Bomb();
			}

			//�U����̔��肪�Ȃ����
			if (!g_aPlayer.bAfterATK)
			{
				//�U��
				if (GetKeyboardTrigger(DIK_I) || GetJoypadTrigger(JOYKEY_X))
				{
					//�{�b�N�X������
					g_aPlayer.nCntTex = 0;
					g_aPlayer.nCntPattern = 0;
					g_aPlayer.fTexSpan[0] = 0;
					g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_LIGHT1_PLAYER;

					//��1��Ԃ�
					g_aPlayer.nState = PLAYER_STATE_LIGHT1;
					g_aPlayer.nLastATK = PLAYER_STATE_LIGHT1;

					//�U��������X�V
					g_aPlayer.bAfterATK = true;
					g_aPlayer.nCntAfterATK = 0;

					//�U���{�b�N�X�𐶐�
					GiveInfo_Attack_Box(0);

					PlaySound(SOUND_LABEL_LIGHT1);
				}
			}
			//�U����̔��蒆�ɍčU���Ŏ�2�֔h��
			else if (g_aPlayer.nLastATK == PLAYER_STATE_LIGHT1 &&
				g_aPlayer.bAfterATK && g_aPlayer.nCntAfterATK >= AMOUNT_CT_LIGHT)
			{
				//�U��
				if (GetKeyboardTrigger(DIK_I) || GetJoypadTrigger(JOYKEY_X))
				{
					//�{�b�N�X������
					g_aPlayer.nCntTex = 0;
					g_aPlayer.nCntPattern = 0;
					g_aPlayer.fTexSpan[0] = 0;
					g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_LIGHT2_PLAYER;

					//��2��Ԃ�
					g_aPlayer.nState = PLAYER_STATE_LIGHT2;
					g_aPlayer.nLastATK = PLAYER_STATE_LIGHT2;

					//�U��������X�V
					g_aPlayer.bAfterATK = true;
					g_aPlayer.nCntAfterATK = 0;

					//�U���{�b�N�X�𐶐�
					GiveInfo_Attack_Box(0);

					PlaySound(SOUND_LABEL_LIGHT2);
				}
			}
			//�U����̔��蒆�ɍčU���Ŏ�3�֔h��
			else if (g_aPlayer.nLastATK == PLAYER_STATE_LIGHT2 &&
				g_aPlayer.bAfterATK && g_aPlayer.nCntAfterATK >= AMOUNT_CT_LIGHT)
			{
				//�U��
				if (GetKeyboardTrigger(DIK_I) || GetJoypadTrigger(JOYKEY_X))
				{
					//�{�b�N�X������
					g_aPlayer.nCntTex = 0;
					g_aPlayer.nCntPattern = 0;
					g_aPlayer.fTexSpan[0] = 0;
					g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_LIGHT3_PLAYER;

					//��3��Ԃ�
					g_aPlayer.nState = PLAYER_STATE_LIGHT3;
					g_aPlayer.nLastATK = PLAYER_STATE_LIGHT3;

					//�U��������X�V
					g_aPlayer.bAfterATK = true;
					g_aPlayer.nCntAfterATK = 0;

					//�U���{�b�N�X�𐶐�
					GiveInfo_Attack_Box(0);

					PlaySound(SOUND_LABEL_LIGHT3);
				}
			}
			//�U����̔��蒆�ɍčU���ŋ�1�֔h��
			else if (g_aPlayer.nLastATK == PLAYER_STATE_LIGHT3 &&
				g_aPlayer.bAfterATK && g_aPlayer.nCntAfterATK >= AMOUNT_CT_HEAVY)
			{
				//�U��
				if (GetKeyboardTrigger(DIK_I) || GetJoypadTrigger(JOYKEY_X))
				{
					//�{�b�N�X������
					g_aPlayer.nCntTex = 0;
					g_aPlayer.nCntPattern = 0;
					g_aPlayer.fTexSpan[0] = 0;
					g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_HEAVY1_PLAYER;

					//��1��Ԃ�
					g_aPlayer.nState = PLAYER_STATE_HEAVY1;
					g_aPlayer.nLastATK = PLAYER_STATE_HEAVY1;

					//�U��������X�V
					g_aPlayer.bAfterATK = true;
					g_aPlayer.nCntAfterATK = 0;

					//�U���{�b�N�X�𐶐�
					GiveInfo_Attack_Box(0);
				}
			}
			//�U����̔��蒆�ɍčU���ŋ�2�֔h��
			else if (g_aPlayer.nLastATK == PLAYER_STATE_HEAVY1 &&
				g_aPlayer.bAfterATK && g_aPlayer.nCntAfterATK >= AMOUNT_CT_HEAVY)
			{
				//�U��
				if (GetKeyboardTrigger(DIK_I) || GetJoypadTrigger(JOYKEY_X))
				{
					//�{�b�N�X������
					g_aPlayer.nCntTex = 0;
					g_aPlayer.nCntPattern = 0;
					g_aPlayer.fTexSpan[0] = 0;
					g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_HEAVY2_PLAYER;

					//��1��Ԃ�
					g_aPlayer.nState = PLAYER_STATE_HEAVY2;
					g_aPlayer.nLastATK = PLAYER_STATE_HEAVY2;

					//�U��������X�V
					g_aPlayer.bAfterATK = true;
					g_aPlayer.nCntAfterATK = 0;

					//�U���{�b�N�X�𐶐�
					GiveInfo_Attack_Box(0);
				}
			}
			//�U����̔��蒆�ɍčU���ŋ�3�֔h��
			else if (g_aPlayer.nLastATK == PLAYER_STATE_HEAVY2 &&
				g_aPlayer.bAfterATK && g_aPlayer.nCntAfterATK >= AMOUNT_CT_HEAVY)
			{
				//�U��
				if (GetKeyboardTrigger(DIK_I) || GetJoypadTrigger(JOYKEY_X))
				{
					//�{�b�N�X������
					g_aPlayer.nCntTex = 0;
					g_aPlayer.nCntPattern = 0;
					g_aPlayer.fTexSpan[0] = 0;
					g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_HEAVY3_PLAYER;

					//��1��Ԃ�
					g_aPlayer.nState = PLAYER_STATE_HEAVY3;
					g_aPlayer.nLastATK = PLAYER_STATE_HEAVY3;

					//�U��������X�V
					g_aPlayer.bAfterATK = true;
					g_aPlayer.nCntAfterATK = 0;

					//�U���{�b�N�X�𐶐�
					GiveInfo_Attack_Box(0);

					PlaySound(SOUND_LABEL_HEAVY3_1);
				}
			}

			//�W�����v�\�Ȏ�
			if (g_aPlayer.nJumpTimes > 0)
			{
				if (GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A))
				{
					//�U�����͂������D��
					if (g_aPlayer.nState != PLAYER_STATE_LIGHT1 &&
						g_aPlayer.nState != PLAYER_STATE_LIGHT2 &&
						g_aPlayer.nState != PLAYER_STATE_LIGHT3 &&
						g_aPlayer.nState != PLAYER_STATE_HEAVY1 &&
						g_aPlayer.nState != PLAYER_STATE_HEAVY2 &&
						g_aPlayer.nState != PLAYER_STATE_HEAVY3)
					{
						//�{�b�N�X������
						g_aPlayer.nCntTex = 0;
						g_aPlayer.nCntPattern = 0;
						g_aPlayer.fTexSpan[0] = 0.0f;
						g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_JUMP_PLAYER;
						//�W�����v��Ԃ�
						g_aPlayer.nState = PLAYER_STATE_JUMP;

						//�W�����v�\�񐔂�����
						g_aPlayer.nJumpTimes--;

						//�ړ��ʂ����Z
						g_aPlayer.move.y = -MOVE_SPD_PLAYER_Y;

						//�W�����v�񐔂ɉ����ē��ʂȏ���
						switch (g_aPlayer.nJumpTimes)
						{
						case AMOUNT_ABLE_JUMPS - 1:
							//���ʉ�
							PlaySound(SOUND_LABEL_JUMP00);
							break;
						default:
							//���ʉ�
							PlaySound(SOUND_LABEL_JUMP01);
							//�G�t�F�N�g
							SetInfo_Effect_Jump(g_aPlayer.pos);
							break;
						}
					}
				}
			}

			//���ֈړ�
			if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_LEFT))
			{
				//�U�����͂������D��
				if (g_aPlayer.nState != PLAYER_STATE_LIGHT1 &&
					g_aPlayer.nState != PLAYER_STATE_LIGHT2 &&
					g_aPlayer.nState != PLAYER_STATE_LIGHT3 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY1 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY2 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY3)
				{
					//�W�����v���͂������D��
					if (g_aPlayer.nState != PLAYER_STATE_JUMP)
					{
						//����܂ő��s��ԈȊO�Ȃ�{�b�N�X������
						if (g_aPlayer.nState != PLAYER_STATE_RUN)
						{
							g_aPlayer.nCntTex = 0;
							g_aPlayer.nCntPattern = 0;
							g_aPlayer.fTexSpan[0] = 0;
							g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_RUN_PLAYER;
						}
						//���s��Ԃ�
						g_aPlayer.nState = PLAYER_STATE_RUN;
					}

					//��������
					g_aPlayer.move.x = -MOVE_SPD_PLAYER_X;
					g_aPlayer.LR = 1;
				}
				//��U��+�ړ��ňړ��␳
				else if (g_aPlayer.nState == PLAYER_STATE_LIGHT1 ||
					g_aPlayer.nState == PLAYER_STATE_LIGHT2 ||
					g_aPlayer.nState == PLAYER_STATE_LIGHT3)
				{
					//�U��������Ԃ̂�
					if (g_aPlayer.nCntAfterATK < 2)
					{
						g_aPlayer.move.x = -MOVE_SPD_ATK_PLAYER_X;
						g_aPlayer.LR = 1;
					}
				}
				//���U��+�ړ��ňړ��␳
				else if (g_aPlayer.nState == PLAYER_STATE_HEAVY1 ||
					g_aPlayer.nState == PLAYER_STATE_HEAVY2)
				{
					//�U��������Ԃ̂�
					if (g_aPlayer.nCntAfterATK < 17)
					{
						g_aPlayer.move.x = -MOVE_SPD_ATK_PLAYER_X * 0.3f;
						g_aPlayer.LR = 1;
					}
				}
				//���U��+�ړ��ňړ��␳
				else if (g_aPlayer.nState == PLAYER_STATE_HEAVY3)
				{
					//�U��������Ԃ̂�
					if (g_aPlayer.nCntAfterATK < 25)
					{
						g_aPlayer.move.x = -MOVE_SPD_ATK_PLAYER_X * 0.3f;
						g_aPlayer.LR = 1;
					}
				}
			}
			//���Ɉړ�
			else if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_RIGHT))
			{
				//�U�����͂������D��
				if (g_aPlayer.nState != PLAYER_STATE_LIGHT1 &&
					g_aPlayer.nState != PLAYER_STATE_LIGHT2 &&
					g_aPlayer.nState != PLAYER_STATE_LIGHT3 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY1 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY2 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY3)
				{
					//�W�����v���͂������D��
					if (g_aPlayer.nState != PLAYER_STATE_JUMP)
					{
						//����܂ő��s��ԈȊO�Ȃ�{�b�N�X������
						if (g_aPlayer.nState != PLAYER_STATE_RUN)
						{
							g_aPlayer.nCntTex = 0;
							g_aPlayer.nCntPattern = 0;
							g_aPlayer.fTexSpan[0] = 0;
							g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_RUN_PLAYER;
						}
						//���s��Ԃ�
						g_aPlayer.nState = PLAYER_STATE_RUN;
					}

					//��������
					g_aPlayer.move.x = MOVE_SPD_PLAYER_X;
					g_aPlayer.LR = 0;
				}
				//��U��+�ړ��ňړ��␳
				else if (g_aPlayer.nState == PLAYER_STATE_LIGHT1 ||
					g_aPlayer.nState == PLAYER_STATE_LIGHT2 ||
					g_aPlayer.nState == PLAYER_STATE_LIGHT3)
				{
					//�U��������Ԃ̂�
					if (g_aPlayer.nCntAfterATK < 2)
					{
						g_aPlayer.move.x = MOVE_SPD_ATK_PLAYER_X;
						g_aPlayer.LR = 0;
					}
				}
				//���U��+�ړ��ňړ��␳
				else if (g_aPlayer.nState == PLAYER_STATE_HEAVY1 ||
					g_aPlayer.nState == PLAYER_STATE_HEAVY2)
				{
					//�U��������Ԃ̂�
					if (g_aPlayer.nCntAfterATK < 17)
					{
						g_aPlayer.move.x = MOVE_SPD_ATK_PLAYER_X * 0.3f;
						g_aPlayer.LR = 0;
					}
				}
				//���U��+�ړ��ňړ��␳
				else if (g_aPlayer.nState == PLAYER_STATE_HEAVY3)
				{
					//�U��������Ԃ̂�
					if (g_aPlayer.nCntAfterATK < 25)
					{
						g_aPlayer.move.x = MOVE_SPD_ATK_PLAYER_X * 0.3f;
						g_aPlayer.LR = 0;
					}
				}
			}
			//���E�̈ړ����͂�����
			else
			{
				//�W�����v��Ԃ⒅�n��Ԃ�D��
				if (g_aPlayer.nState != PLAYER_STATE_JUMP &&
					g_aPlayer.nState != PLAYER_STATE_LAND &&
					g_aPlayer.nState != PLAYER_STATE_LIGHT1 &&
					g_aPlayer.nState != PLAYER_STATE_LIGHT2 &&
					g_aPlayer.nState != PLAYER_STATE_LIGHT3 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY1 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY2 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY3)
				{
					//����܂őҋ@��ԈȊO�Ȃ�{�b�N�X������
					if (g_aPlayer.nState != PLAYER_STATE_IDLE)
					{
						g_aPlayer.nCntTex = 0;
						g_aPlayer.nCntPattern = 0;
						g_aPlayer.fTexSpan[0] = 0;
						g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
					}
					//�ҋ@��Ԃ�
					g_aPlayer.nState = PLAYER_STATE_IDLE;
				}
			}
		}

		//�U�����(�e�N�X�`���)�ɍ��킹�Ĕ�����t����
		switch (g_aPlayer.nState)
		{
		case PLAYER_STATE_HEAVY1:
			if(g_aPlayer.nCntPattern == 3)
			{
				g_aPlayer.move.y += -MOVE_SPD_GRAVITY_Y * 1.5f;
				g_aPlayer.LR == 0 ? g_aPlayer.move.x += MOVE_SPD_ATK_PLAYER_X * 0.25f : g_aPlayer.move.x += -MOVE_SPD_ATK_PLAYER_X * 0.25f;
				PlaySound(SOUND_LABEL_HEAVY1);
			}
			break;
		case PLAYER_STATE_HEAVY2:
			if (g_aPlayer.nCntPattern == 5)
			{
				 g_aPlayer.move.y += -MOVE_SPD_GRAVITY_Y * 1.5f;
				 g_aPlayer.LR == 0 ? g_aPlayer.move.x += MOVE_SPD_ATK_PLAYER_X * 0.25f : g_aPlayer.move.x += -MOVE_SPD_ATK_PLAYER_X * 0.25f;
				 PlaySound(SOUND_LABEL_HEAVY2);
			}
			break;
		case PLAYER_STATE_HEAVY3:
			if (g_aPlayer.nCntPattern == 9)
			{
				g_aPlayer.move.y += -MOVE_SPD_GRAVITY_Y * 2.0f;
				g_aPlayer.LR == 0 ? g_aPlayer.move.x += MOVE_SPD_ATK_PLAYER_X * 0.4f : g_aPlayer.move.x += -MOVE_SPD_ATK_PLAYER_X * 0.4f;
				PlaySound(SOUND_LABEL_HEAVY3_2);
			}
			break;
		}

		//���ړ�����
		g_aPlayer.move.x = g_aPlayer.move.x * MOVE_SPD_BRAKE_X;

		//�d��
		g_aPlayer.move.y = g_aPlayer.move.y + MOVE_SPD_GRAVITY_Y;
	}
	else
	{
		//�ړ��ʂ��N���A
		g_aPlayer.move.x = 0.0f;
		g_aPlayer.move.y = 0.0f;
	}

	//�v���C���[�̈ʒu�Ƃ��ݒ�
	Update_Pos_Player();
}

//************************************************
//�v���C���[�̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Player(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Player;

	//���̍��W�ύX
	g_aPlayer.BGpos += g_aPlayer.move;
	//�������̍��W�ύX
	g_aPlayer.pos.y += g_aPlayer.move.y;

	//�������̈ʒu�𒲐�����
	Adjust_Pos_Player();

	//�n�`�Ƃ̓����蔻��
	if (!g_aPlayer.bFell)
	{
		HitDetection_Stage(0, HIT_TYPE_PLAYER, &g_aPlayer.pos, &g_aPlayer.oldpos, &g_aPlayer.move, &g_aPlayer.fRadius[0]);
	}

	//�e�N�X�`���A�j���[�V����
	Update_Tex_Player();

	//��Ԃɍ��킹�ă{�b�N�X����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aPlayer.fLength[nCnt] = g_aPlayer_Box[g_aPlayer.nState].fLength_Hold[nCnt];
		g_aPlayer.fAngle[nCnt] = g_aPlayer_Box[g_aPlayer.nState].fAngle_Hold[nCnt];
	}

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Player->Lock(0, 0, (void**)&pVtx_Player, 0);

	pVtx_Player[0].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z - (D3DX_PI - g_aPlayer.fAngle[0])) * g_aPlayer.fLength[0];
	pVtx_Player[0].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z - (D3DX_PI - g_aPlayer.fAngle[0])) * g_aPlayer.fLength[0];
	pVtx_Player[1].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + (D3DX_PI - g_aPlayer.fAngle[0])) * g_aPlayer.fLength[0];
	pVtx_Player[1].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + (D3DX_PI - g_aPlayer.fAngle[0])) * g_aPlayer.fLength[0];
	pVtx_Player[2].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z - g_aPlayer.fAngle[1]) * g_aPlayer.fLength[1];
	pVtx_Player[2].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z - g_aPlayer.fAngle[1]) * g_aPlayer.fLength[1];
	pVtx_Player[3].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + g_aPlayer.fAngle[1]) * g_aPlayer.fLength[1];
	pVtx_Player[3].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + g_aPlayer.fAngle[1]) * g_aPlayer.fLength[1];

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Player->Unlock();
}

//************************************************
//�������̈ʒu�𒲐�����֐�
//************************************************
void Adjust_Pos_Player(void)
{
	//���̍��W���Z�J�C�́��[�ɓ��B���Ă����
	if (g_aPlayer.BGpos.x - g_aPlayer.fRadius[0] < 0.0f)
	{
		//�[�����ɖ߂�
		g_aPlayer.BGpos.x = g_aPlayer.fRadius[0];
		g_aPlayer.pos.x = g_aPlayer.BGpos.x;

		//�ړ��ʂ�������
		g_aPlayer.move.x = 0.0f;
	}
	//���̍��W���Z�J�C�́��[�ɂƂĂ��߂��Ȃ��
	else if (g_aPlayer.BGpos.x < SCREEN_HALFWIDTH)
	{
		//�������̍��W������
		g_aPlayer.pos.x = g_aPlayer.BGpos.x;
	}

	//���̍��W���Z�J�C�́��[�ɓ��B���Ă����
	if (g_aPlayer.BGpos.x + g_aPlayer.fRadius[0] > SCREEN_WIDTH)
	{
		//�[�����ɖ߂�
		g_aPlayer.BGpos.x = SCREEN_WIDTH - g_aPlayer.fRadius[0];
		g_aPlayer.pos.x = g_aPlayer.BGpos.x;

		//�ړ��ʂ�������
		g_aPlayer.move.x = 0.0f;
	}
	//���̍��W���Z�J�C�́��[�ɋ߂��Ȃ��
	else if (g_aPlayer.BGpos.x > SCREEN_HALFWIDTH)
	{
		//�������̍��W������
		g_aPlayer.pos.x = g_aPlayer.BGpos.x;
	}

	//���������
	if (g_aPlayer.pos.y >= SCREEN_HEIGHT + SCREEN_HALFHEIGHT)
	{
		//1�x�̂݃_���[�W�A�ړ��ʂ��N���A
		if (!g_aPlayer.bFell)
		{
			//g_aPlayer.nLife--;
			g_aPlayer.move.x = 0.0f;
			g_aPlayer.move.y = 0.0f;

			PlaySound(SOUND_LABEL_FALL);
		}

		//����������o��
		g_aPlayer.bFell = true;
	}

	//�������蒆�A�����ړ�
	if (g_aPlayer.bFell)
	{
		TOWER* pTower = GetInfo_Tower();

		//���ړ�
		if (g_aPlayer.BGpos.x > pTower->pos.x + FELL_RESET_AREA_X)
		{
			//���̂Ƃ��݈̂ړ��ʂ��Œ�
			g_aPlayer.move.x = -FELL_RESET_MOVE_X;
		}
		else if (g_aPlayer.BGpos.x < pTower->pos.x - FELL_RESET_AREA_X)
		{
			//���̂Ƃ��݈̂ړ��ʂ��Œ�
			g_aPlayer.move.x = FELL_RESET_MOVE_X;
		}
		else
		{
			g_aPlayer.move.x = 0.0f;
		}

		//�c�ړ�
		if (g_aPlayer.BGpos.y > pTower->pos.y - FELL_RESET_AREA_Y)
		{
			//���̂Ƃ��݈̂ړ��ʂ��Œ�
			g_aPlayer.move.y = FELL_RESET_MOVE_Y;
		}
		else
		{
			//�㏸��������h��
			//g_aPlayer.move.y = 0.0f;
			g_aPlayer.BGpos.y = pTower->pos.y - FELL_RESET_AREA_Y;

			if (g_aPlayer.BGpos.x <= pTower->pos.x + FELL_RESET_AREA_X &&
				g_aPlayer.BGpos.x >= pTower->pos.x - FELL_RESET_AREA_X)
			{
				//��������𖳂���
				g_aPlayer.bFell = false;
			}
		}

		//�����ړ�
		g_aPlayer.BGpos += g_aPlayer.move;
		g_aPlayer.pos = g_aPlayer.BGpos;
	}
}

//************************************************
//�v���C���[�̃e�N�X�`���𓮂����֐�
//************************************************
void Update_Tex_Player(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Player;

	//�e�N�X�`����ύX
	switch (g_aPlayer.nState)
	{
	case PLAYER_STATE_IDLE:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_IDLE_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_IDLE_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_IDLE_PLAYER;
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_IDLE_PLAYER)
			{
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_JUMP:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_JUMP_PLAYER)
		{
			//���ʂɒB����ƌŒ�
			if (g_aPlayer.nCntPattern < AMOUNT_STYLE_TEX_JUMP_PLAYER)
			{
				g_aPlayer.nCntTex = 0;
				g_aPlayer.nCntPattern++;
				g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_JUMP_PLAYER;
				g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_JUMP_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_LAND:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_LAND_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_LAND_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_LAND_PLAYER;
			//1���[�v�ŏI��
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_LAND_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_RUN:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_RUN_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_RUN_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_RUN_PLAYER;
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_RUN_PLAYER)
			{
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_RUN_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_LIGHT1:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_LIGHT1_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_LIGHT1_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_LIGHT1_PLAYER;
			//1���[�v�ŏI��
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_LIGHT1_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_LIGHT2:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_LIGHT2_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_LIGHT2_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_LIGHT2_PLAYER;
			//1���[�v�ŏI��
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_LIGHT2_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_LIGHT3:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_LIGHT3_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_LIGHT3_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_LIGHT3_PLAYER;
			//1���[�v�ŏI��
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_LIGHT3_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_HEAVY1:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_HEAVY1_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_HEAVY1_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_HEAVY1_PLAYER;
			//1���[�v�ŏI��
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_HEAVY1_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_HEAVY2:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_HEAVY2_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_HEAVY2_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_HEAVY2_PLAYER;
			//1���[�v�ŏI��
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_HEAVY2_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_HEAVY3:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_HEAVY3_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_HEAVY3_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_HEAVY3_PLAYER;
			//1���[�v�ŏI��
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_HEAVY3_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_HURT1:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_HURT1_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_HURT1_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_HURT1_PLAYER;
			//1���[�v�ŏI��
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_HURT1_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_HURT2:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_HURT2_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_HURT2_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_HURT2_PLAYER;
			//1���[�v�ŏI��
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_HURT2_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	}

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Player->Lock(0, 0, (void**)&pVtx_Player, 0);

	if (g_aPlayer.LR == 0)
	{
		pVtx_Player[0].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[0], 0.0f);
		pVtx_Player[1].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[1], 0.0f);
		pVtx_Player[2].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[0], 1.0f);
		pVtx_Player[3].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[1], 1.0f);
	}
	else
	{
		pVtx_Player[0].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[1], 0.0f);
		pVtx_Player[1].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[0], 0.0f);
		pVtx_Player[2].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[1], 1.0f);
		pVtx_Player[3].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[0], 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Player->Unlock();
}

//************************************************
//�v���C���[�\���̂̃A�h���X��n��
//************************************************
PLAYER *GetInfo_Player(void)
{
	return &g_aPlayer;
}

//************************************************
//�v���C���[�{�b�N�X�\���̂̃A�h���X��n��
//************************************************
PLAYER_BOX* GetInfo_Player_Box(void)
{
	return &g_aPlayer_Box[0];
}

//************************************************
//�v���C���[�ʒu���̃A�h���X��n��
//************************************************
D3DXVECTOR3 GetInfo_Pos_Player(void)
{
	return g_aPlayer.pos;
}