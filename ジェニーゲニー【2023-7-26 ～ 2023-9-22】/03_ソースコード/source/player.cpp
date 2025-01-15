//************************************************
//
//���@����[player.cpp]
//Author�F���c����
//
//************************************************
#include "input.h"
#include "main.h"
#include "sound.h"
#include "bullet.h"
#include "life.h"
#include "particle.h"
#include "player.h"
#include "timer.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Player = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Player = NULL;	//���_�o�b�t�@�̃|�C���^
PLAYER g_aPlayer;	//�\���̂̒��̏��������n���p
int g_nChoosingBulletStyle_Player = 0;	//�I�����Ă���e�̎��
int g_nCnt_Shot_Vulkan = 0;	//�o���J�����˗p�L���X�g�^�C��
int g_nColorR_Player = 0;	//�F�ύX�p
int g_nColorG_Player = 0;
int g_nColorB_Player = 0;
int g_nColorA_Player = 0;
int g_nCntIncreaseCapacity_Player = 0;	//�L���p�񕜗p�L���X�g����

float g_texLine = 0.0f;
int g_nCntLine = 0;
float g_texRow = 0.0f;
int g_nCntRow = 0;

bool g_bShooting = false;
int g_nCntShooting = 0;
int g_nCntShootingLine = 0;

/*�f�o�b�O�p���G*/
bool STAR = false;
bool GOD = false;

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
		TEXTURE_CHARACTER_PLAYER,
		&g_pTexture_Player);

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
	pVtx_Player[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Player[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Player[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Player[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Player[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Player[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Player[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Player[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Player->Unlock();

	//�\���̓�����������
	g_aPlayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���W������
	g_aPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʏ�����
	g_aPlayer.state = PLAYERSTATE_NORMAL;			//������Ԃ͒ʏ�
	g_aPlayer.nCntState = 0;						//��Ԍp�����ԏ�����
	g_aPlayer.nLife = AMOUNT_LIFE_PLAYER;			//�̗͏����ݒ�
	g_aPlayer.nCapacity = AMOUNT_CAPACITY_PLAYER;	//�L���p�V�e�B�����ݒ�

	//�I�����Ă���e�̎�ނ�������
	g_nChoosingBulletStyle_Player = 0;

	//�}�V���K���p�̃L���X�g��������
	g_nCnt_Shot_Vulkan = 0;

	//�F�ύX�p�ϐ��̏�����
	g_nColorR_Player = 255;
	g_nColorG_Player = 255;
	g_nColorB_Player = 255;
	g_nColorA_Player = 255;
	
	//�L���p�񕜗p�L���X�g������
	g_nCntIncreaseCapacity_Player = 0;

	//�X�|�[���n�_�̐ݒ�
	g_aPlayer.pos = D3DXVECTOR3(POS_X_SPAWN_PLAYER, POS_Y_SPAWN_PLAYER, 0.0f);

	g_texLine = 0.0f;
	g_nCntLine = 0;
	g_texRow = 0.0f;
	g_nCntRow = 0;

	g_bShooting = false;
	g_nCntShooting = 0;
	g_nCntShootingLine = 0;

	//��x�����W�J���Ă���
	Update_Player();
	Draw_Player();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Player(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Player != NULL)
	{
		g_pTexture_Player->Release();
		g_pTexture_Player = NULL;
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
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Player;

	//�������ԏ��ւ̃|�C���^
	int* pTimer;

	//�������Ԃ���
	pTimer = Getinfo_Timer();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Player->Lock(0, 0, (void**)&pVtx_Player, 0);

	/**********�f�o�b�O�p��������***********/
	if (g_aPlayer.nCapacity <= AMOUNT_CAPACITY_PLAYER && !GOD)
	{
		g_nCntIncreaseCapacity_Player++;

		if (g_nCntIncreaseCapacity_Player >= AMOUNT_CNT_CAPACITY_PLAYER)
		{
			g_aPlayer.nCapacity++;

			g_nCntIncreaseCapacity_Player = 0;
		}

		if (g_aPlayer.nCapacity >= AMOUNT_CAPACITY_PLAYER)
		{
			g_aPlayer.nCapacity = AMOUNT_CAPACITY_PLAYER;
		}
	}

	/**********�f�o�b�O�p��������***********/
	if (GOD)
	{
		g_aPlayer.nCapacity = AMOUNT_CAPACITY_PLAYER;
	}

	//�v���C���[�������Ă���Ƃ��A�܂��͎��Ԑ���(�v���P����)
	if (g_aPlayer.state != PLAYERSTATE_DEATH && *pTimer > 0)
	{
		//����
		if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
		{
			if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
			{
				//������͂����ꂽ��
				g_aPlayer.move.x += sinf(-D3DX_PI * 0.75f) * MOVE_SPD_POS_PLAYER;
				g_aPlayer.move.y += cosf(-D3DX_PI * 0.75f) * MOVE_SPD_POS_PLAYER;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
			{
				//�������͂����ꂽ��
				g_aPlayer.move.x += sinf(-D3DX_PI * 0.25f) * MOVE_SPD_POS_PLAYER;
				g_aPlayer.move.y += cosf(-D3DX_PI * 0.25f) * MOVE_SPD_POS_PLAYER;
			}
			else
			{
				//���̂ݓ��͂��ꂽ��
				g_aPlayer.move.x += sinf(-D3DX_PI * 0.5f) * MOVE_SPD_POS_PLAYER;
				g_aPlayer.move.y += cosf(-D3DX_PI * 0.5f) * MOVE_SPD_POS_PLAYER;
			}
		}
		//�E��
		else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true)
		{
			if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
			{
				//�E����͂����ꂽ��
				g_aPlayer.move.x += sinf(D3DX_PI * 0.75f) * MOVE_SPD_POS_PLAYER;
				g_aPlayer.move.y += cosf(D3DX_PI * 0.75f) * MOVE_SPD_POS_PLAYER;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
			{
				//�E�����͂����ꂽ��
				g_aPlayer.move.x += sinf(D3DX_PI * 0.25f) * MOVE_SPD_POS_PLAYER;
				g_aPlayer.move.y += cosf(D3DX_PI * 0.25f) * MOVE_SPD_POS_PLAYER;
			}
			else
			{
				//�E�̂ݓ��͂��ꂽ��
				g_aPlayer.move.x += sinf(D3DX_PI * 0.5f) * MOVE_SPD_POS_PLAYER;
				g_aPlayer.move.y += cosf(D3DX_PI * 0.5f) * MOVE_SPD_POS_PLAYER;
			}
		}
		//���~
		else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
		{
			g_aPlayer.move.x += sinf(D3DX_PI * 0.0f) * MOVE_SPD_POS_PLAYER;
			g_aPlayer.move.y += cosf(D3DX_PI * 0.0f) * MOVE_SPD_POS_PLAYER;
		}
		//�㏸
		else if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
		{
			g_aPlayer.move.x += sinf(D3DX_PI * 0.0f) * MOVE_SPD_POS_PLAYER;
			g_aPlayer.move.y += cosf(D3DX_PI * 1.0f) * MOVE_SPD_POS_PLAYER;
		}

		/*���R�ɕύX�ł��Ȃ��Ȃ�c*/
		////�e�̎�ޕύX
		//if (GetKeyboardTrigger(DIK_LEFT) == true)
		//{
		//	g_nChoosingBulletStyle_Player--;
		//}
		//else if (GetKeyboardTrigger(DIK_RIGHT) == true)
		//{
		//	g_nChoosingBulletStyle_Player++;
		//}

		////�ύX�������̎�
		//if (g_nChoosingBulletStyle_Player < 0)
		//{
		//	//��ԍ��ɍs���ƈ�ԉE�ɖ߂�
		//	g_nChoosingBulletStyle_Player = BULLETSTYLE_WONDER;
		//}
		//else if (g_nChoosingBulletStyle_Player > BULLETSTYLE_WONDER)
		//{
		//	//��ԉE�ɍs���ƈ�ԍ��ɖ߂�
		//	g_nChoosingBulletStyle_Player = 0;
		//}

		//�e����
		switch (g_nChoosingBulletStyle_Player)
		{
		case BULLETSTYLE_COMET:

			if (GetKeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_X) == true)
			{
				g_bShooting = true;

				g_nCntLine = 0;
				g_texRow = 2;

				//�v���C���[���W�ƑI�����Ă���e�̎�ނ𑗂�
				Setinfo_Bullet(g_aPlayer.pos, g_nChoosingBulletStyle_Player);
			}

			break;

		case BULLETSTYLE_REUNION:

			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{
				//�v���C���[���W�ƑI�����Ă���e�̎�ނ𑗂�
				Setinfo_Bullet(g_aPlayer.pos, g_nChoosingBulletStyle_Player);
			}

			break;

		case BULLETSTYLE_KING:

			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{
				//�v���C���[���W�ƑI�����Ă���e�̎�ނ𑗂�
				Setinfo_Bullet(g_aPlayer.pos, g_nChoosingBulletStyle_Player);
			}

			break;
		}
	}

	//X��������
	if (g_aPlayer.pos.x - HALFSPAN_X_PLAYER - g_aPlayer.move.x >= SPAN_OUTSIDE_BORDER &&
		g_aPlayer.pos.x + HALFSPAN_X_PLAYER + g_aPlayer.move.x <= SCREEN_WIDTH - SPAN_OUTSIDE_BORDER)
	{
		//��ʓ��Ƀv���C���[������Ƃ����ړ�����
		g_aPlayer.move.x += (0.0f - g_aPlayer.move.x) * ATTENUATION_SPD_POS_PLAYER;
	}
	else if (g_aPlayer.pos.x - HALFSPAN_X_PLAYER <= SPAN_OUTSIDE_BORDER)
	{
		//���[�ɂԂ������u�ԁA��������
		g_aPlayer.move.x = PUSHBACK_WALL_PLAYER;
	}
	else if (g_aPlayer.pos.x + HALFSPAN_X_PLAYER >= SCREEN_WIDTH - SPAN_OUTSIDE_BORDER)
	{
		//�E�[��
		g_aPlayer.move.x = -PUSHBACK_WALL_PLAYER;
	}

	//Y��������
	if (g_aPlayer.pos.y - HALFSPAN_Y_PLAYER >= SPAN_OUTSIDE_BORDER &&
		g_aPlayer.pos.y + HALFSPAN_Y_PLAYER <= SCREEN_HEIGHT - SPAN_OUTSIDE_BORDER)
	{
		//��ʓ��Ƀv���C���[������Ƃ��c�ړ�����
		g_aPlayer.move.y += (0.0f - g_aPlayer.move.y) * ATTENUATION_SPD_POS_PLAYER;
	}
	else if (g_aPlayer.pos.y - HALFSPAN_Y_PLAYER <= SPAN_OUTSIDE_BORDER)
	{
		//��[�ɂԂ������u�ԁA��������
		g_aPlayer.move.y = PUSHBACK_WALL_PLAYER;
	}
	else if (g_aPlayer.pos.y + HALFSPAN_Y_PLAYER >= SCREEN_HEIGHT - SPAN_OUTSIDE_BORDER)
	{
		//���[�ɂԂ������u�ԁA��������
		g_aPlayer.move.y = -PUSHBACK_WALL_PLAYER;
	}

	//�ʒu���𐏎��X�V
	g_aPlayer.pos.x += g_aPlayer.move.x;
	g_aPlayer.pos.y += g_aPlayer.move.y;

	//���W�̍X�V
	pVtx_Player[0].pos.x = g_aPlayer.pos.x - HALFSPAN_X_PLAYER;
	pVtx_Player[0].pos.y = g_aPlayer.pos.y - HALFSPAN_Y_PLAYER;
	pVtx_Player[1].pos.x = g_aPlayer.pos.x + HALFSPAN_X_PLAYER;
	pVtx_Player[1].pos.y = g_aPlayer.pos.y - HALFSPAN_Y_PLAYER;
	pVtx_Player[2].pos.x = g_aPlayer.pos.x - HALFSPAN_X_PLAYER;
	pVtx_Player[2].pos.y = g_aPlayer.pos.y + HALFSPAN_Y_PLAYER;
	pVtx_Player[3].pos.x = g_aPlayer.pos.x + HALFSPAN_X_PLAYER;
	pVtx_Player[3].pos.y = g_aPlayer.pos.y + HALFSPAN_Y_PLAYER;

	//�v���C���[�̏�Ԃɍ��킹�ď�������
	switch (g_aPlayer.state)
	{
		//�ʏ펞
	case PLAYERSTATE_NORMAL:

		//�F��ʏ�ɃZ�b�g
		g_nColorG_Player = 255;
		g_nColorB_Player = 255;
		g_nColorA_Player = 255;

		break;

		//��e��
	case PLAYERSTATE_DAMAGE:

		//��Ԏ��������炷
		g_aPlayer.nCntState--;

		//�o�߂�����
		if (g_aPlayer.nCntState <= 0)
		{
			//�ʏ��ԂɕύX
			g_aPlayer.state = PLAYERSTATE_NORMAL;
		}

		//�F�ύX
		g_nColorG_Player *= -1;
		g_nColorB_Player *= -1;
		g_nColorA_Player *= -1;

		break;

	case PLAYERSTATE_DEATH:

		//�F�ύX
		g_nColorR_Player -= 25;
		g_nColorG_Player -= 25;
		g_nColorB_Player -= 25;
		g_nColorA_Player -= 25;

		if (g_nColorR_Player < 30)
		{
			g_nColorR_Player = 30;
			g_nColorG_Player = 30;
			g_nColorB_Player = 30;
			g_nColorA_Player = 30;
		}

		break;
	}

	//�F���̍X�V
	pVtx_Player[0].col = D3DCOLOR_RGBA(g_nColorR_Player, g_nColorG_Player, g_nColorB_Player, g_nColorA_Player);
	pVtx_Player[1].col = D3DCOLOR_RGBA(g_nColorR_Player, g_nColorG_Player, g_nColorB_Player, g_nColorA_Player);
	pVtx_Player[2].col = D3DCOLOR_RGBA(g_nColorR_Player, g_nColorG_Player, g_nColorB_Player, g_nColorA_Player);
	pVtx_Player[3].col = D3DCOLOR_RGBA(g_nColorR_Player, g_nColorG_Player, g_nColorB_Player, g_nColorA_Player);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Player->Unlock();

	Animation_Player();

	///********�f�o�b�O�p*******/
	//if (GetKeyboardTrigger(DIK_4) == true)
	//{
	//	//���C�t����
	//	g_aPlayer.nLife--;
	//}
	//if (GetKeyboardTrigger(DIK_5) == true && g_aPlayer.nLife < AMOUNT_LIFE_MAX)
	//{
	//	//���C�t����
	//	g_aPlayer.nLife++;
	//}
	//if (GetKeyboardTrigger(DIK_6) == true)
	//{
	//	//���G
	//	STAR = STAR ? false : true;
	//}
	//if (GetKeyboardTrigger(DIK_X) == true)
	//{
	//	//�L���p�V�e�B����
	//	GOD = GOD ? false : true;
	//}
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
	pDevice->SetTexture(0, g_pTexture_Player);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//�v���C���[���̃A�h���X��n���֐�
//************************************************
PLAYER *Getinfo_Player(void)
{
	return &g_aPlayer;	//PLAYER���̏��������n��
}

//************************************************
//�v���C���[�ւ̖��������֐�
//************************************************
void Hit_Player(int nDamage)
{
	//���ʉ���炷
	PlaySound(SOUND_LABEL_SE_DAMAGE);

	//�o�C�u
	SetVibration(AMOUNT_CNT_STATE_PLAYER, 65535);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Player;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Player->Lock(0, 0, (void**)&pVtx_Player, 0);

	//�����ɔ������C�t�����炷
	/********�f�o�b�O�p*********/
	if (!STAR)
	{
		g_aPlayer.nLife -= nDamage;
	}

	//�v���C���[���܂������Ă���ꍇ
	if (g_aPlayer.nLife > 0)
	{
		//�v���C���[���_���[�W��Ԃ�
		g_aPlayer.state = PLAYERSTATE_DAMAGE;

		//�_���[�W��Ԍp�����Ԑݒ�
		g_aPlayer.nCntState = AMOUNT_CNT_STATE_PLAYER;
	}
	//����ł��܂����Ƃ�
	else
	{
		//�v���C���[�����S��Ԃ�
		g_aPlayer.state = PLAYERSTATE_DEATH;

		//���S��Ԍp�����Ԑݒ�
		g_aPlayer.nCntState = AMOUNT_CNT_STATE_PLAYER;

		g_nColorR_Player = 255;
		g_nColorG_Player = 255;
		g_nColorB_Player = 255;
		g_nColorA_Player = 255;
	}
}

//************************************************
//�A�C�e���̎擾���������֐�
//************************************************
void GetItem_Player(int nIncreaseCapacity)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Player;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Player->Lock(0, 0, (void**)&pVtx_Player, 0);

	//�L���p�V�e�B����
	g_aPlayer.nCapacity += nIncreaseCapacity;

	//�I�[�o�[�؂�̂�
	g_aPlayer.nCapacity >= AMOUNT_CAPACITY_PLAYER ? g_aPlayer.nCapacity = AMOUNT_CAPACITY_PLAYER : 0;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Player->Unlock();
}

//************************************************
//�e�̎�ޑI�����̃A�h���X��n���֐�
//************************************************
int* Getinfo_BulletStyle(void)
{
	return &g_nChoosingBulletStyle_Player;	//���݂̒e�̎�ޏ��������n��
}

//************************************************
//�e�N�X�`���A�j���[�V�����֐�
//************************************************
void Animation_Player(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Player;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Player->Lock(0, 0, (void**)&pVtx_Player, 0);

	//�e�N�X�`�����W�̏����ݒ�
	if (!g_bShooting)
	{
		pVtx_Player[0].tex = D3DXVECTOR2(0.0f + (0.14285f * g_texLine), 0.0f + (0.33333f * g_texRow));
		pVtx_Player[1].tex = D3DXVECTOR2(0.14285f + (0.14285f * g_texLine), 0.0f + (0.33333f * g_texRow));
		pVtx_Player[2].tex = D3DXVECTOR2(0.0f + (0.14285f * g_texLine), 0.33333f + (0.33333f * g_texRow));
		pVtx_Player[3].tex = D3DXVECTOR2(0.14285f + (0.14285f * g_texLine), 0.33333f + (0.33333f * g_texRow));
	}
	else
	{
		//�|���S���T�C�Y�̒���
		pVtx_Player[0].pos.x = g_aPlayer.pos.x - HALFSPAN_X_PLAYER;
		pVtx_Player[0].pos.y = g_aPlayer.pos.y - HALFSPAN_Y_PLAYER * 1.05f;
		pVtx_Player[1].pos.x = g_aPlayer.pos.x + HALFSPAN_X_PLAYER * 1.45f;
		pVtx_Player[1].pos.y = g_aPlayer.pos.y - HALFSPAN_Y_PLAYER * 1.05f;
		pVtx_Player[2].pos.x = g_aPlayer.pos.x - HALFSPAN_X_PLAYER;
		pVtx_Player[2].pos.y = g_aPlayer.pos.y + HALFSPAN_Y_PLAYER * 1.05f;
		pVtx_Player[3].pos.x = g_aPlayer.pos.x + HALFSPAN_X_PLAYER * 1.45f;
		pVtx_Player[3].pos.y = g_aPlayer.pos.y + HALFSPAN_Y_PLAYER * 1.05f;

		pVtx_Player[0].tex = D3DXVECTOR2(0.0f + (0.14285f * g_nCntShootingLine), 0.0f + (0.33333f * g_texRow));
		pVtx_Player[1].tex = D3DXVECTOR2(0.14285f + (0.14285f * g_nCntShootingLine), 0.0f + (0.33333f * g_texRow));
		pVtx_Player[2].tex = D3DXVECTOR2(0.0f + (0.14285f * g_nCntShootingLine), 0.33333f + (0.33333f * g_texRow));
		pVtx_Player[3].tex = D3DXVECTOR2(0.14285f + (0.14285f * g_nCntShootingLine), 0.33333f + (0.33333f * g_texRow));
	}

	if (g_bShooting)
	{
		g_nCntShooting++;

		if (g_nCntShooting > 2)
		{
			g_nCntShooting = 0;
			g_nCntShootingLine++;

			if (g_nCntShootingLine > 6)
			{
				g_bShooting = false;
				g_nCntShooting = 0;
				g_nCntShootingLine = 0;
				g_nCntLine = 0;
				g_texRow = 0;
			}
		}
	}
	else
	{
		g_nCntLine++;

		if (g_nCntLine > 5)
		{
			g_nCntLine = 0;

			g_texLine++;

			if (g_texLine > 7)
			{
				g_texLine = 0;

				g_texRow = (float)(rand() % 2);
			}
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Player->Unlock();
}