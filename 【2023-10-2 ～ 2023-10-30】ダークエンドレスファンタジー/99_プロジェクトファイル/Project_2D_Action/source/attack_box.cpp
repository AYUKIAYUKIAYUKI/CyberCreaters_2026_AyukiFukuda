//************************************************
//
//�U���{�b�N�X����[attack_box.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "attack_box.h"
#include "bomb.h"
#include "camera.h"
#include "enemy.h"
#include "particle.h"
#include "player.h"
#include "score.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Attack_Box = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Attack_Box = NULL;	//���_�o�b�t�@�̃|�C���^
ATTACK_BOX g_aAttack_Box[AMOUNT_POLYGON_ATTACK_BOX];	//�U���{�b�N�X

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Attack_Box()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"",
		&g_pTexture_Attack_Box);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_ATTACK_BOX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Attack_Box,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Attack_Box;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Attack_Box->Lock(0, 0, (void**)&pVtx_Attack_Box, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ATTACK_BOX; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Attack_Box[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Attack_Box[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Attack_Box[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Attack_Box[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Attack_Box[0].rhw = 1.0f;
		pVtx_Attack_Box[1].rhw = 1.0f;
		pVtx_Attack_Box[2].rhw = 1.0f;
		pVtx_Attack_Box[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Attack_Box[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.2f);
		pVtx_Attack_Box[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.2f);
		pVtx_Attack_Box[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.2f);
		pVtx_Attack_Box[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.2f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Attack_Box[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Attack_Box[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Attack_Box[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Attack_Box[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Attack_Box += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Attack_Box->Unlock();

	//�U���{�b�N�X�\���̂̏��̏������Q
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ATTACK_BOX; nCnt++)
	{
		g_aAttack_Box[nCnt].nMode = 0;
		g_aAttack_Box[nCnt].bUse = false;
		g_aAttack_Box[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aAttack_Box[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aAttack_Box[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aAttack_Box[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aAttack_Box[nCnt].fRadius[nCnt2] = 0.0f;
			g_aAttack_Box[nCnt].fLength[nCnt2] = 0.0f;
			g_aAttack_Box[nCnt].fAngle[nCnt2] = 0.0f;
		}
		g_aAttack_Box[nCnt].nRemain = 0;
	}
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Attack_Box(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Attack_Box != NULL)
	{
		g_pTexture_Attack_Box->Release();
		g_pTexture_Attack_Box = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Attack_Box != NULL)
	{
		g_pVtxBuff_Attack_Box->Release();
		g_pVtxBuff_Attack_Box = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Attack_Box(void)
{
	//�U���{�b�N�X��W�J
	Update_Pos_Attack_Box();

	//�U���{�b�N�X�̎c�����Ԃ�����
	Disapper_Attack_Box();
}

//************************************************
//�U���{�b�N�X�̏���ݒ肷��֐�
//************************************************
void GiveInfo_Attack_Box(int nMode)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ATTACK_BOX; nCnt++)
	{
		//1����
		if (!g_aAttack_Box[nCnt].bUse)
		{
			g_aAttack_Box[nCnt].nMode = nMode;
			g_aAttack_Box[nCnt].bUse = true;

			switch (g_aAttack_Box[nCnt].nMode)
			{
			case 0:
				Front_Player(nCnt);
				break;
			case 1:
				Front_Bomb(nCnt);
				break;
			}

			break;
		}
	}
}

//************************************************
//�v���C���[�U���{�b�N�X�̏���ݒ肷��֐�
//************************************************
void Front_Player(int nCnt)
{
	PLAYER* pPlayer = GetInfo_Player();

	//�U�����[�V�������Ƃɍ��ʉ�
	switch (pPlayer->nState)
	{
	case PLAYER_STATE_LIGHT1:

		//�o���ʒu
		switch (pPlayer->LR)
		{
			//��
		case 0:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 30.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
			//��
		case 1:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 30.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		}

		//�T�C�Y
		g_aAttack_Box[nCnt].fRadius[0] = 70.0f;
		g_aAttack_Box[nCnt].fRadius[1] = pPlayer->fRadius[1];

		//�Ίp���̒���
		g_aAttack_Box[nCnt].fLength[0] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]) +
			((g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * (g_aAttack_Box[nCnt].fRadius[1] * 2.0f)));
		g_aAttack_Box[nCnt].fLength[1] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]));

		//�Ίp���̊p�x
		g_aAttack_Box[nCnt].fAngle[0] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, (g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box[nCnt].fAngle[1] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, 0.0f);

		//�L���X�g����
		g_aAttack_Box[nCnt].nAppear = 2 * SPD_CHANGE_TEX_LIGHT1_PLAYER;

		//�c������
		g_aAttack_Box[nCnt].nRemain = 10;

		//�F
		g_aAttack_Box[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		/****************�ȉ����̃t�H�[�}�b�g�ŕ���**************/
		break;
	case PLAYER_STATE_LIGHT2:
		switch (pPlayer->LR)
		{
		case 0:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 30.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		case 1:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 30.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		}

		g_aAttack_Box[nCnt].fRadius[0] = 70.0f;
		g_aAttack_Box[nCnt].fRadius[1] = pPlayer->fRadius[1];

		g_aAttack_Box[nCnt].fLength[0] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]) +
			((g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * (g_aAttack_Box[nCnt].fRadius[1] * 2.0f)));
		g_aAttack_Box[nCnt].fLength[1] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]));

		g_aAttack_Box[nCnt].fAngle[0] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, (g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box[nCnt].fAngle[1] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box[nCnt].nAppear = 1 * SPD_CHANGE_TEX_LIGHT1_PLAYER;
		g_aAttack_Box[nCnt].nRemain = 10;

		g_aAttack_Box[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	case PLAYER_STATE_LIGHT3:
		switch (pPlayer->LR)
		{
		case 0:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 30.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		case 1:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 30.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		}

		g_aAttack_Box[nCnt].fRadius[0] = 60.0f;
		g_aAttack_Box[nCnt].fRadius[1] = pPlayer->fRadius[1];

		g_aAttack_Box[nCnt].fLength[0] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]) +
			((g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * (g_aAttack_Box[nCnt].fRadius[1] * 2.0f)));
		g_aAttack_Box[nCnt].fLength[1] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]));

		g_aAttack_Box[nCnt].fAngle[0] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, (g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box[nCnt].fAngle[1] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box[nCnt].nAppear = 1 * SPD_CHANGE_TEX_LIGHT1_PLAYER;
		g_aAttack_Box[nCnt].nRemain = 10;

		g_aAttack_Box[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	case PLAYER_STATE_HEAVY1:
		switch (pPlayer->LR)
		{
		case 0:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 50.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		case 1:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 50.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		}

		g_aAttack_Box[nCnt].fRadius[0] = 80.0f;
		g_aAttack_Box[nCnt].fRadius[1] = 60.0f;

		g_aAttack_Box[nCnt].fLength[0] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]) +
			((g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * (g_aAttack_Box[nCnt].fRadius[1] * 2.0f)));
		g_aAttack_Box[nCnt].fLength[1] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]));

		g_aAttack_Box[nCnt].fAngle[0] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, (g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box[nCnt].fAngle[1] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box[nCnt].nAppear = 4 * SPD_CHANGE_TEX_HEAVY1_PLAYER;
		g_aAttack_Box[nCnt].nRemain = 20;

		g_aAttack_Box[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	case PLAYER_STATE_HEAVY2:
		switch (pPlayer->LR)
		{
		case 0:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 50.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		case 1:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 50.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		}

		g_aAttack_Box[nCnt].fRadius[0] = 80.0f;
		g_aAttack_Box[nCnt].fRadius[1] = 60.0f;

		g_aAttack_Box[nCnt].fLength[0] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]) +
			((g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * (g_aAttack_Box[nCnt].fRadius[1] * 2.0f)));
		g_aAttack_Box[nCnt].fLength[1] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]));

		g_aAttack_Box[nCnt].fAngle[0] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, (g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box[nCnt].fAngle[1] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box[nCnt].nAppear = 7 * SPD_CHANGE_TEX_HEAVY2_PLAYER;
		g_aAttack_Box[nCnt].nRemain = 20;

		g_aAttack_Box[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	case PLAYER_STATE_HEAVY3:
		switch (pPlayer->LR)
		{
		case 0:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 60.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		case 1:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 60.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		}

		g_aAttack_Box[nCnt].fRadius[0] = 100.0f;
		g_aAttack_Box[nCnt].fRadius[1] = 80.0f;

		g_aAttack_Box[nCnt].fLength[0] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]) +
			((g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * (g_aAttack_Box[nCnt].fRadius[1] * 2.0f)));
		g_aAttack_Box[nCnt].fLength[1] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]));

		g_aAttack_Box[nCnt].fAngle[0] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, (g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box[nCnt].fAngle[1] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box[nCnt].nAppear = 11 * SPD_CHANGE_TEX_HEAVY3_PLAYER;
		g_aAttack_Box[nCnt].nRemain = 30;

		g_aAttack_Box[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	}
}

void Front_Bomb(int nCnt)
{
	BOMB* pBomb = GetInfo_Bomb();

	g_aAttack_Box[nCnt].pos.x = pBomb->pos.x;
	g_aAttack_Box[nCnt].pos.y = pBomb->pos.y;

	g_aAttack_Box[nCnt].fRadius[0] = 110.0f;
	g_aAttack_Box[nCnt].fRadius[1] = 60.0f;

	g_aAttack_Box[nCnt].fLength[0] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]) +
		((g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * (g_aAttack_Box[nCnt].fRadius[1] * 2.0f)));
	g_aAttack_Box[nCnt].fLength[1] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]));

	g_aAttack_Box[nCnt].fAngle[0] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, (g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * 2.0f);
	g_aAttack_Box[nCnt].fAngle[1] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, 0.0f);

	g_aAttack_Box[nCnt].nAppear = 0;
	g_aAttack_Box[nCnt].nRemain = 10;

	g_aAttack_Box[nCnt].nMode = 1;
}

//************************************************
//�U���{�b�N�X�̃|���S����W�J����֐�
//************************************************
void Update_Pos_Attack_Box(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Attack_Box;

	PLAYER* pPlayer = GetInfo_Player();
	BOMB* pBomb = GetInfo_Bomb();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Attack_Box->Lock(0, 0, (void**)&pVtx_Attack_Box, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ATTACK_BOX; nCnt++)
	{
		//�L���X�g�ς݂��g�p���肪�łĂ�����̂̂ݏo��
		if (g_aAttack_Box[nCnt].bUse && g_aAttack_Box[nCnt].nAppear <= 0)
		{
			//���[�h����
			switch (g_aAttack_Box[nCnt].nMode)
			{
			case 0:
				//�U�����[�V�������ƂɈʒu����
				switch (pPlayer->nState)
				{
				case PLAYER_STATE_LIGHT1:
					switch (pPlayer->LR)
					{
						//��
					case 0:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 30.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
						//��
					case 1:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 30.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					}
					break;
				case PLAYER_STATE_LIGHT2:
					switch (pPlayer->LR)
					{
					case 0:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 30.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					case 1:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 30.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					}
					break;
				case PLAYER_STATE_LIGHT3:
					switch (pPlayer->LR)
					{
					case 0:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 30.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					case 1:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 30.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					}
					break;
				case PLAYER_STATE_HEAVY1:
					switch (pPlayer->LR)
					{
					case 0:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 50.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					case 1:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 50.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					}
					break;
				case PLAYER_STATE_HEAVY2:
					switch (pPlayer->LR)
					{
					case 0:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 50.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					case 1:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 50.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					}
					break;
				case PLAYER_STATE_HEAVY3:
					switch (pPlayer->LR)
					{
					case 0:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 60.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					case 1:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 60.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					}
					break;
				}
				break;
			case 1:
				g_aAttack_Box[nCnt].pos.x = pBomb->pos.x;
				g_aAttack_Box[nCnt].pos.y = pBomb->pos.y;
				break;
			}

			//�p�[�e�B�N�����΂�
			Setinfo_Particle(PARTICLE_ATKED, g_aAttack_Box[nCnt].pos, g_aAttack_Box[nCnt].col);

			//�^���X�N���[��
			ConvertInfo_Screen(&g_aAttack_Box[nCnt].pos);

			//�����蔻��
			HitDetection_Attack_Box(nCnt);

			pVtx_Attack_Box[0].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z - (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
			pVtx_Attack_Box[0].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z - (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
			pVtx_Attack_Box[1].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z + (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
			pVtx_Attack_Box[1].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z + (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
			pVtx_Attack_Box[2].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z - g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
			pVtx_Attack_Box[2].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z - g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
			pVtx_Attack_Box[3].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z + g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
			pVtx_Attack_Box[3].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z + g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
		}
		//�L���X�g�o��
		else if (g_aAttack_Box[nCnt].bUse)
		{
			g_aAttack_Box[nCnt].nAppear--;
		}

		pVtx_Attack_Box += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Attack_Box->Unlock();
}

//************************************************
//�U���{�b�N�X�I���֐�
//************************************************
void Disapper_Attack_Box(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Attack_Box;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Attack_Box->Lock(0, 0, (void**)&pVtx_Attack_Box, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ATTACK_BOX; nCnt++)
	{
		//�L���X�g�ς݃{�b�N�X���o�Ă�Ƃ�
		if (g_aAttack_Box[nCnt].bUse && g_aAttack_Box[nCnt].nAppear <= 0)
		{
			//�c������
			if (g_aAttack_Box[nCnt].nRemain > 0)
			{
				g_aAttack_Box[nCnt].nRemain--;
			}
			//����
			else
			{
				g_aAttack_Box[nCnt].bUse = false;
				g_aAttack_Box[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
				{
					g_aAttack_Box[nCnt].fRadius[nCnt2] = 0.0f;
					g_aAttack_Box[nCnt].fLength[nCnt2] = 0.0f;
					g_aAttack_Box[nCnt].fAngle[nCnt2] = 0.0f;
				}
				g_aAttack_Box[nCnt].nRemain = 0;
				g_aAttack_Box[nCnt].nAppear = 0;

				pVtx_Attack_Box[0].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z - (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
				pVtx_Attack_Box[0].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z - (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
				pVtx_Attack_Box[1].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z + (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
				pVtx_Attack_Box[1].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z + (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
				pVtx_Attack_Box[2].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z - g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
				pVtx_Attack_Box[2].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z - g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
				pVtx_Attack_Box[3].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z + g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
				pVtx_Attack_Box[3].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z + g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
			}
		}

		pVtx_Attack_Box += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Attack_Box->Unlock();
}

//************************************************
//�����蔻��֐�
//************************************************
void HitDetection_Attack_Box(int nCnt)
{
	PLAYER* pPlayer = GetInfo_Player();
	ENEMY* pEnemy = GetInfo_Enemy();

	//�U���{�b�N�X�Ƃ̓����蔻��
	//�v���C���[�����̃{�b�N�X�̂��߁A�G�ƃ{�b�N�X�Ŕ���
	for (int i = 0; i < AMOUNT_POLYGON_ENEMY; i++)
	{
		if (pEnemy[i].bUse)
		{
			//��ނɍ��킹�Ĕ���A��ԕ���
			switch (pEnemy[i].nStyle)
			{
			case ENEMY_00:
				//��e��ԂŖ��������Ă���ꍇ�̂�
				if (pEnemy[i].nState != ENEMY_00_STATE_HURT && pEnemy[i].nState != ENEMY_00_STATE_DEATH)
				{
					//�G�ɍU���{�b�N�X(�{���̓����蔻��)���G��Ă���
					if (pEnemy[i].pos.x - pEnemy[i].fRadius[0] < g_aAttack_Box[nCnt].pos.x + g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.x + pEnemy[i].fRadius[0] > g_aAttack_Box[nCnt].pos.x - g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.y - pEnemy[i].fRadius[1] < g_aAttack_Box[nCnt].pos.y &&
						pEnemy[i].pos.y + pEnemy[i].fRadius[1] > g_aAttack_Box[nCnt].pos.y - (g_aAttack_Box[nCnt].fRadius[1] * 2.0f))
					{
						//���C�t�����炷
						pEnemy[i].nLife--;

						if (pPlayer->nState == PLAYER_STATE_HEAVY1 ||
							pPlayer->nState == PLAYER_STATE_HEAVY2 ||
							pPlayer->nState == PLAYER_STATE_HEAVY3)
						{
							//���܂�
							pEnemy[i].nLife--;
						}

						//�����ڃ{�b�N�X������
						pEnemy[i].nCntTex = 0;
						pEnemy[i].nCntPattern = 0;
						pEnemy[i].fTexSpan[0] = 0.0f;
						pEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_HURT_ENEMY_00;

						//��e��Ԃɍ����ւ��āA�A����e��h�~
						pEnemy[i].nState = ENEMY_00_STATE_HURT;

						switch (g_aAttack_Box[nCnt].nMode)
						{
						case 0:
							//�v���C���[�̌����ɍ��킹�ăm�b�N�o�b�N
							pPlayer->LR == 0 ? pEnemy[i].move.x = 8.0f : pEnemy[i].move.x = -8.0f;
							break;
						case 1:
							//���܂�
							pEnemy[i].nLife--;

							if (pEnemy[i].pos.x < g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = -15.0f;
								pEnemy[i].move.y = -6.0f;
							}
							else if (pEnemy[i].pos.x > g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = 15.0f;
								pEnemy[i].move.y = -6.0f;
							}
							break;
						}

						//�X�R�A���Z
						int* pScore = GetInfo_Score();
						pScore[SCORE_NEW] += 2;

						PlaySound(SOUND_LABEL_HURT);
					}
				}
				break;
			case ENEMY_01:
				//��e��ԂŖ��������Ă���ꍇ�̂�
				if (pEnemy[i].nState != ENEMY_01_STATE_HURT && pEnemy[i].nState != ENEMY_01_STATE_DEATH)
				{
					if (pEnemy[i].pos.x - pEnemy[i].fRadius[0] < g_aAttack_Box[nCnt].pos.x + g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.x + pEnemy[i].fRadius[0] > g_aAttack_Box[nCnt].pos.x - g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.y - (pEnemy[i].fRadius[1] * 2.0f) < g_aAttack_Box[nCnt].pos.y + g_aAttack_Box[nCnt].fRadius[1] &&
						pEnemy[i].pos.y > g_aAttack_Box[nCnt].pos.y - g_aAttack_Box[nCnt].fRadius[1])
					{
						//���C�t�����炷
						pEnemy[i].nLife--;

						if (pPlayer->nState == PLAYER_STATE_HEAVY1 ||
							pPlayer->nState == PLAYER_STATE_HEAVY2 ||
							pPlayer->nState == PLAYER_STATE_HEAVY3)
						{
							//���܂�
							pEnemy[i].nLife--;
						}

						//�����ڃ{�b�N�X������
						pEnemy[i].nCntTex = 0;
						pEnemy[i].nCntPattern = 0;
						pEnemy[i].fTexSpan[0] = 0.0f;
						pEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_HURT_ENEMY_01;

						//��e��Ԃɍ����ւ��āA�A����e��h�~
						pEnemy[i].nState = ENEMY_01_STATE_HURT;

						switch (g_aAttack_Box[nCnt].nMode)
						{
						case 0:
							//�v���C���[�̌����ɍ��킹�ăm�b�N�o�b�N
							pPlayer->LR == 0 ? pEnemy[i].move.x = 8.0f : pEnemy[i].move.x = -8.0f;
							break;
						case 1:
							//���܂�
							pEnemy[i].nLife--;

							if (pEnemy[i].pos.x < g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = -15.0f;
								pEnemy[i].move.y = -6.0f;
							}
							else if (pEnemy[i].pos.x > g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = 15.0f;
								pEnemy[i].move.y = -6.0f;
							}
						}

						//�X�R�A���Z
						int* pScore = GetInfo_Score();
						pScore[SCORE_NEW] += 1;

						PlaySound(SOUND_LABEL_HURT);
					}
				}
				break;
			case ENEMY_02:
				//��e��ԂŖ��������Ă���ꍇ�̂�
				if (pEnemy[i].nState != ENEMY_02_STATE_HURT && pEnemy[i].nState != ENEMY_02_STATE_DEATH)
				{
					if (pEnemy[i].pos.x - pEnemy[i].fRadius[0] < g_aAttack_Box[nCnt].pos.x + g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.x + pEnemy[i].fRadius[0] > g_aAttack_Box[nCnt].pos.x - g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.y - (pEnemy[i].fRadius[1] * 2.0f) < g_aAttack_Box[nCnt].pos.y + g_aAttack_Box[nCnt].fRadius[1] &&
						pEnemy[i].pos.y > g_aAttack_Box[nCnt].pos.y - g_aAttack_Box[nCnt].fRadius[1])
					{
						//���C�t�����炷
						pEnemy[i].nLife--;

						if (pPlayer->nState == PLAYER_STATE_HEAVY1 ||
							pPlayer->nState == PLAYER_STATE_HEAVY2 ||
							pPlayer->nState == PLAYER_STATE_HEAVY3)
						{
							//���܂�
							pEnemy[i].nLife--;
						}

						//�����ڃ{�b�N�X������
						pEnemy[i].nCntTex = 0;
						pEnemy[i].nCntPattern = 0;
						pEnemy[i].fTexSpan[0] = 0.0f;
						pEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_HURT_ENEMY_02;

						//��e��Ԃɍ����ւ��āA�A����e��h�~
						pEnemy[i].nState = ENEMY_02_STATE_HURT;

						switch (g_aAttack_Box[nCnt].nMode)
						{
						case 0:
							//�v���C���[�̌����ɍ��킹�ăm�b�N�o�b�N
							pPlayer->LR == 0 ? pEnemy[i].move.x = 8.0f : pEnemy[i].move.x = -8.0f;
							break;
						case 1:
							//���܂�
							pEnemy[i].nLife--;

							if (pEnemy[i].pos.x < g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = -15.0f;
								pEnemy[i].move.y = -6.0f;
							}
							else if (pEnemy[i].pos.x > g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = 15.0f;
								pEnemy[i].move.y = -6.0f;
							}
						}

						//�X�R�A���Z
						int* pScore = GetInfo_Score();
						pScore[SCORE_NEW] += 2;

						PlaySound(SOUND_LABEL_HURT);
					}
				}
				break;
			case ENEMY_03:
				//��e��ԂŖ��������Ă���ꍇ�̂�
				if (pEnemy[i].nState != ENEMY_03_STATE_HURT && pEnemy[i].nState != ENEMY_03_STATE_DEATH)
				{
					if (pEnemy[i].pos.x - pEnemy[i].fRadius[0] < g_aAttack_Box[nCnt].pos.x + g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.x + pEnemy[i].fRadius[0] > g_aAttack_Box[nCnt].pos.x - g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.y - (pEnemy[i].fRadius[1] * 2.0f) < g_aAttack_Box[nCnt].pos.y + g_aAttack_Box[nCnt].fRadius[1] &&
						pEnemy[i].pos.y > g_aAttack_Box[nCnt].pos.y - g_aAttack_Box[nCnt].fRadius[1])
					{
						//���C�t�����炷
						pEnemy[i].nLife--;

						if (pPlayer->nState == PLAYER_STATE_HEAVY1 ||
							pPlayer->nState == PLAYER_STATE_HEAVY2 ||
							pPlayer->nState == PLAYER_STATE_HEAVY3)
						{
							//���܂�
							pEnemy[i].nLife--;
						}

						//�����ڃ{�b�N�X������
						pEnemy[i].nCntTex = 0;
						pEnemy[i].nCntPattern = 0;
						pEnemy[i].fTexSpan[0] = 0.0f;
						pEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_HURT_ENEMY_03;

						//��e��Ԃɍ����ւ��āA�A����e��h�~
						pEnemy[i].nState = ENEMY_03_STATE_HURT;

						switch (g_aAttack_Box[nCnt].nMode)
						{
						case 0:
							//�v���C���[�̌����ɍ��킹�ăm�b�N�o�b�N
							pPlayer->LR == 0 ? pEnemy[i].move.x = 8.0f : pEnemy[i].move.x = -8.0f;
							break;
						case 1:
							//���܂�
							pEnemy[i].nLife--;

							if (pEnemy[i].pos.x < g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = -15.0f;
								pEnemy[i].move.y = -6.0f;
							}
							else if (pEnemy[i].pos.x > g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = 15.0f;
								pEnemy[i].move.y = -6.0f;
							}
						}

						//�X�R�A���Z
						int* pScore = GetInfo_Score();
						pScore[SCORE_NEW] += 2;

						PlaySound(SOUND_LABEL_HURT);
					}
				}
				break;
			case ENEMY_04:
				//��e��ԂŖ��������Ă���ꍇ�̂�
				if (pEnemy[i].nState != ENEMY_04_STATE_HURT && pEnemy[i].nState != ENEMY_04_STATE_DEATH)
				{
					if (pEnemy[i].pos.x - pEnemy[i].fRadius[0] < g_aAttack_Box[nCnt].pos.x + g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.x + pEnemy[i].fRadius[0] > g_aAttack_Box[nCnt].pos.x - g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.y - (pEnemy[i].fRadius[1] * 2.0f) < g_aAttack_Box[nCnt].pos.y + g_aAttack_Box[nCnt].fRadius[1] &&
						pEnemy[i].pos.y > g_aAttack_Box[nCnt].pos.y - g_aAttack_Box[nCnt].fRadius[1])
					{
						//���C�t�����炷
						pEnemy[i].nLife--;

						if (pPlayer->nState == PLAYER_STATE_HEAVY1 ||
							pPlayer->nState == PLAYER_STATE_HEAVY2 ||
							pPlayer->nState == PLAYER_STATE_HEAVY3)
						{
							//���܂�
							pEnemy[i].nLife--;
						}

						//�����ڃ{�b�N�X������
						pEnemy[i].nCntTex = 0;
						pEnemy[i].nCntPattern = 0;
						pEnemy[i].fTexSpan[0] = 0.0f;
						pEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_HURT_ENEMY_04;

						//��e��Ԃɍ����ւ��āA�A����e��h�~
						pEnemy[i].nState = ENEMY_04_STATE_HURT;

						switch (g_aAttack_Box[nCnt].nMode)
						{
						case 0:
							//�v���C���[�̌����ɍ��킹�ăm�b�N�o�b�N
							pPlayer->LR == 0 ? pEnemy[i].move.x = 8.0f : pEnemy[i].move.x = -8.0f;
							break;
						case 1:
							//���܂�
							pEnemy[i].nLife--;

							if (pEnemy[i].pos.x < g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = -15.0f;
								pEnemy[i].move.y = -6.0f;
							}
							else if (pEnemy[i].pos.x > g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = 15.0f;
								pEnemy[i].move.y = -6.0f;
							}
						}

						//�X�R�A���Z
						int* pScore = GetInfo_Score();
						pScore[SCORE_NEW] += 3;

						PlaySound(SOUND_LABEL_HURT);
					}
				}
				break;
			}
		}
	}
}

//************************************************
//�U���{�b�N�X�̃A�h���X��n��
//************************************************
ATTACK_BOX* GetInfo_Attack_Box(void)
{
	return &g_aAttack_Box[0];
}

//************************************************
//�f�o�b�O�p�̍U���{�b�N�X�̉���
//************************************************
void Draw_Attack_Box_Debug(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Attack_Box, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ATTACK_BOX; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexture_Attack_Box);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}