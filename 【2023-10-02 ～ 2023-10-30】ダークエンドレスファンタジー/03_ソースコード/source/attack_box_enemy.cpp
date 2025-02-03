//************************************************
//
//�G�p�U���{�b�N�X����[attack_box_enemy.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "sound.h"
#include "attack_box_enemy.h"
#include "camera.h"
#include "enemy.h"
#include "player.h"
#include "tower.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Attack_Box_Enemy[AMOUNT_TEX_BOX] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Attack_Box_Enemy = NULL;	//���_�o�b�t�@�̃|�C���^
ATTACK_BOX_ENEMY g_aAttack_Box_Enemy[AMOUNT_POLYGON_ENEMY];	//�G�U���{�b�N�X

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Attack_Box_Enemy()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_NONE,
		&g_pTexture_Attack_Box_Enemy[BOX_MODE_NONE]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_04_BALL,
		&g_pTexture_Attack_Box_Enemy[BOX_MODE_FIRE]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_04_BALLEND,
		&g_pTexture_Attack_Box_Enemy[BOX_MODE_FIRE_END]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Attack_Box_Enemy,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Attack_Box_Enemy;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Attack_Box_Enemy->Lock(0, 0, (void**)&pVtx_Attack_Box_Enemy, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Attack_Box_Enemy[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Attack_Box_Enemy[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Attack_Box_Enemy[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Attack_Box_Enemy[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Attack_Box_Enemy[0].rhw = 1.0f;
		pVtx_Attack_Box_Enemy[1].rhw = 1.0f;
		pVtx_Attack_Box_Enemy[2].rhw = 1.0f;
		pVtx_Attack_Box_Enemy[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Attack_Box_Enemy[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.2f);
		pVtx_Attack_Box_Enemy[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.2f);
		pVtx_Attack_Box_Enemy[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.2f);
		pVtx_Attack_Box_Enemy[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.2f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Attack_Box_Enemy[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Attack_Box_Enemy[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Attack_Box_Enemy[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Attack_Box_Enemy[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Attack_Box_Enemy += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Attack_Box_Enemy->Unlock();

	//�G�U���{�b�N�X�\���̂̏��̏������Q
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		g_aAttack_Box_Enemy[nCnt].nMode = BOX_MODE_NONE;
		g_aAttack_Box_Enemy[nCnt].bUse = false;
		g_aAttack_Box_Enemy[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aAttack_Box_Enemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aAttack_Box_Enemy[nCnt].fX = 0.0f;
		g_aAttack_Box_Enemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aAttack_Box_Enemy[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aAttack_Box_Enemy[nCnt].LR = 0;
		g_aAttack_Box_Enemy[nCnt].nCntTex = 0;
		g_aAttack_Box_Enemy[nCnt].nCntPattern = 0;
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aAttack_Box_Enemy[nCnt].fTexSpan[nCnt] = 0.0f;
			g_aAttack_Box_Enemy[nCnt].fRadius[nCnt2] = 0.0f;
			g_aAttack_Box_Enemy[nCnt].fLength[nCnt2] = 0.0f;
			g_aAttack_Box_Enemy[nCnt].fAngle[nCnt2] = 0.0f;
		}
		g_aAttack_Box_Enemy[nCnt].nRemain = 0;
	}
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Attack_Box_Enemy(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEX_BOX; nCnt++)
	{
		if (g_pTexture_Attack_Box_Enemy[nCnt] != NULL)
		{
			g_pTexture_Attack_Box_Enemy[nCnt]->Release();
			g_pTexture_Attack_Box_Enemy[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Attack_Box_Enemy != NULL)
	{
		g_pVtxBuff_Attack_Box_Enemy->Release();
		g_pVtxBuff_Attack_Box_Enemy = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Attack_Box_Enemy(void)
{
	//�U���{�b�N�X��W�J
	Update_Pos_Attack_Box_Enemy();

	//�U���{�b�N�X�̎c�����Ԃ�����
	Disapper_Attack_Box_Enemy();
}

//************************************************
//�U���{�b�N�X�̏���ݒ肷��֐�
//************************************************
void GiveInfo_Attack_Box_Enemy(int i)
{
	//1����
	if (!g_aAttack_Box_Enemy[i].bUse)
	{
		g_aAttack_Box_Enemy[i].bUse = true;

		Front_Enemy(i);
	}
}

//************************************************
//�G�U���{�b�N�X�̏���ݒ肷��֐�
//************************************************
void Front_Enemy(int i)
{
	ENEMY* pEnemy = GetInfo_Enemy();

	//�G���Ƃɍ��ʉ�
	switch (pEnemy[i].nStyle)
	{
	case ENEMY_00:
		//�o���ʒu
		switch (pEnemy[i].LR)
		{
			//��
		case 0:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x + 20.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y + 30.0f;
			break;
			//��
		case 1:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x - 20.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y + 30.0f;
			break;
		}

		//�T�C�Y
		g_aAttack_Box_Enemy[i].fRadius[0] = 30.0f;
		g_aAttack_Box_Enemy[i].fRadius[1] = 30.0f;

		//�Ίp���̒���
		g_aAttack_Box_Enemy[i].fLength[0] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]) +
			((g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f)));
		g_aAttack_Box_Enemy[i].fLength[1] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]));

		//�Ίp���̊p�x
		g_aAttack_Box_Enemy[i].fAngle[0] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box_Enemy[i].fAngle[1] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, 0.0f);

		//�L���X�g����
		//g_aAttack_Box_Enemy[i].nAppear = 6 * SPD_CHANGE_TEX_ATK_ENEMY_00;
		g_aAttack_Box_Enemy[i].nAppear = 0;

		//�c������
		g_aAttack_Box_Enemy[i].nRemain = 10;

		//�U���L���X�g�^�C���ݒ�
		pEnemy[i].nCT = AMOUNT_CT_ATK_ENEMY_00;

		/****************�ȉ����̃t�H�[�}�b�g�ŕ���**************/
		break;
	case ENEMY_01:
		switch (pEnemy[i].LR)
		{
		case 0:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x + 40.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		case 1:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x - 40.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		}

		g_aAttack_Box_Enemy[i].fRadius[0] = 30.0f;
		g_aAttack_Box_Enemy[i].fRadius[1] = 40.0f;

		g_aAttack_Box_Enemy[i].fLength[0] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]) +
			((g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f)));
		g_aAttack_Box_Enemy[i].fLength[1] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]));

		g_aAttack_Box_Enemy[i].fAngle[0] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box_Enemy[i].fAngle[1] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box_Enemy[i].nRemain = 10;

		pEnemy[i].nCT = AMOUNT_CT_ATK_ENEMY_01;

		break;
	case ENEMY_02:
		switch (pEnemy[i].LR)
		{
		case 0:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x + 30.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		case 1:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x - 30.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		}

		g_aAttack_Box_Enemy[i].fRadius[0] = 50.0f;
		g_aAttack_Box_Enemy[i].fRadius[1] = 40.0f;

		g_aAttack_Box_Enemy[i].fLength[0] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]) +
			((g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f)));
		g_aAttack_Box_Enemy[i].fLength[1] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]));

		g_aAttack_Box_Enemy[i].fAngle[0] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box_Enemy[i].fAngle[1] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box_Enemy[i].nRemain = 10;

		pEnemy[i].nCT = AMOUNT_CT_ATK_ENEMY_02;

		break;
	case ENEMY_03:
		switch (pEnemy[i].LR)
		{
		case 0:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x + 75.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		case 1:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x - 75.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		}

		g_aAttack_Box_Enemy[i].fRadius[0] = 80.0f;
		g_aAttack_Box_Enemy[i].fRadius[1] = 60.0f;

		g_aAttack_Box_Enemy[i].fLength[0] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]) +
			((g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f)));
		g_aAttack_Box_Enemy[i].fLength[1] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]));

		g_aAttack_Box_Enemy[i].fAngle[0] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box_Enemy[i].fAngle[1] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box_Enemy[i].nRemain = 10;

		pEnemy[i].nCT = AMOUNT_CT_ATK_ENEMY_03;

		break;
	case ENEMY_04:

		//�����[�h��
		g_aAttack_Box_Enemy[i].nMode = BOX_MODE_FIRE;

		//��������
		g_aAttack_Box_Enemy[i].LR = pEnemy[i].LR;

		switch (pEnemy[i].LR)
		{
		case 0:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x + 90.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		case 1:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x - 90.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		}

		g_aAttack_Box_Enemy[i].move.x = 6.0f;

		g_aAttack_Box_Enemy[i].nCntTex = 0;
		g_aAttack_Box_Enemy[i].nCntPattern = 0;

		g_aAttack_Box_Enemy[i].fTexSpan[0] = 0.0f;
		g_aAttack_Box_Enemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_FIRE_ENEMY_04;

		g_aAttack_Box_Enemy[i].fRadius[0] = 30.0f;
		g_aAttack_Box_Enemy[i].fRadius[1] = 30.0f;

		g_aAttack_Box_Enemy[i].fLength[0] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]) +
			((g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f)));
		g_aAttack_Box_Enemy[i].fLength[1] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]));

		g_aAttack_Box_Enemy[i].fAngle[0] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box_Enemy[i].fAngle[1] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box_Enemy[i].nAppear = 25;

		g_aAttack_Box_Enemy[i].nRemain = 35;

		pEnemy[i].nCT = AMOUNT_CT_ATK_ENEMY_04;

		break;
	}
}

//************************************************
//�U���{�b�N�X�̃|���S����W�J����֐�
//************************************************
void Update_Pos_Attack_Box_Enemy(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Attack_Box_Enemy;

	ENEMY* pEnemy = GetInfo_Enemy();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Attack_Box_Enemy->Lock(0, 0, (void**)&pVtx_Attack_Box_Enemy, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		//�L���X�g�ς݂��g�p���肪�łĂ�����̂̂ݏo��
		if (g_aAttack_Box_Enemy[nCnt].bUse && g_aAttack_Box_Enemy[nCnt].nAppear <= 0)
		{
			//��ނ��ƂɈʒu����
			switch (pEnemy[nCnt].nStyle)
			{
			case ENEMY_00:
				switch (pEnemy[nCnt].LR)
				{
				case 0:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x + 20.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y + 30.0f;
					break;
				case 1:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x - 20.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y + 30.0f;
					break;
				}
				break;
			case ENEMY_01:
				switch (pEnemy[nCnt].LR)
				{
				case 0:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x + 40.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				case 1:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x - 40.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				}
				break;
			case ENEMY_02:
				switch (pEnemy[nCnt].LR)
				{
				case 0:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x + 30.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				case 1:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x - 30.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				}
				break;
			case ENEMY_03:
				switch (pEnemy[nCnt].LR)
				{
				case 0:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x + 75.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				case 1:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x - 75.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				}
				break;
			case ENEMY_04:
				g_aAttack_Box_Enemy[nCnt].fX += g_aAttack_Box_Enemy[nCnt].move.x;
				switch (pEnemy[nCnt].LR)
				{
				case 0:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x + 90.0f + g_aAttack_Box_Enemy[nCnt].fX;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				case 1:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x - 90.0f - g_aAttack_Box_Enemy[nCnt].fX;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				}
				break;
			}

			//�F
			Update_Col_Attack_Box_Enemy(nCnt);

			//�e�N
			Update_Tex_Attack_Box_Enemy(nCnt);

			//�^���X�N���[��
			ConvertInfo_Screen(&g_aAttack_Box_Enemy[nCnt].pos);

			//�����蔻��
			HitDetection_Attack_Box_Enemy(nCnt);

			pVtx_Attack_Box_Enemy[0].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z - (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
			pVtx_Attack_Box_Enemy[0].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z - (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
			pVtx_Attack_Box_Enemy[1].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z + (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
			pVtx_Attack_Box_Enemy[1].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z + (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
			pVtx_Attack_Box_Enemy[2].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z - g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];
			pVtx_Attack_Box_Enemy[2].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z - g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];
			pVtx_Attack_Box_Enemy[3].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z + g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];
			pVtx_Attack_Box_Enemy[3].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z + g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];
		}
		//�L���X�g�o��
		else if (g_aAttack_Box_Enemy[nCnt].bUse)
		{
			g_aAttack_Box_Enemy[nCnt].nAppear--;
		}

		pVtx_Attack_Box_Enemy += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Attack_Box_Enemy->Unlock();
}

//************************************************
//�U���{�b�N�X�F�Ԑ�
//************************************************
void Update_Col_Attack_Box_Enemy(int i)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Attack_Box_Enemy;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Attack_Box_Enemy->Lock(0, 0, (void**)&pVtx_Attack_Box_Enemy, 0);

	pVtx_Attack_Box_Enemy += AMOUNT_VTX * i;

	//���������\�����邩�ǂ���
	if (g_aAttack_Box_Enemy[i].nMode != BOX_MODE_FIRE &&
		g_aAttack_Box_Enemy[i].nMode != BOX_MODE_FIRE_END)
	{
		pVtx_Attack_Box_Enemy[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.0f);
		pVtx_Attack_Box_Enemy[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.0f);
		pVtx_Attack_Box_Enemy[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.0f);
		pVtx_Attack_Box_Enemy[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		pVtx_Attack_Box_Enemy[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Attack_Box_Enemy[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Attack_Box_Enemy[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Attack_Box_Enemy[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Attack_Box_Enemy->Unlock();
}

//************************************************
//�G�̃e�N�X�`���𓮂����֐�
//************************************************
void Update_Tex_Attack_Box_Enemy(int i)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Attack_Box_Enemy;

	//�e�N�X�`����ύX
	switch (g_aAttack_Box_Enemy[i].nMode)
	{
	case BOX_MODE_FIRE:
		g_aAttack_Box_Enemy[i].nCntTex++;
		if (g_aAttack_Box_Enemy[i].nCntTex > SPD_CHANGE_TEX_FIRE_ENEMY_04)
		{
			g_aAttack_Box_Enemy[i].nCntTex = 0;
			g_aAttack_Box_Enemy[i].nCntPattern++;
			g_aAttack_Box_Enemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_FIRE_ENEMY_04;
			g_aAttack_Box_Enemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_FIRE_ENEMY_04;
			//1��
			if (g_aAttack_Box_Enemy[i].nCntPattern >= AMOUNT_STYLE_TEX_FIRE_ENEMY_04)
			{
				g_aAttack_Box_Enemy[i].nCntPattern = 0;
				g_aAttack_Box_Enemy[i].fTexSpan[0] = 0;
				g_aAttack_Box_Enemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_FIREEND_ENEMY_04;

				g_aAttack_Box_Enemy[i].nMode = BOX_MODE_FIRE_END;
			}
		}
		break;
	case BOX_MODE_FIRE_END:
		g_aAttack_Box_Enemy[i].nCntTex++;
		if (g_aAttack_Box_Enemy[i].nCntTex > SPD_CHANGE_TEX_FIREEND_ENEMY_04)
		{
			g_aAttack_Box_Enemy[i].nCntTex = 0;
			g_aAttack_Box_Enemy[i].nCntPattern++;
			g_aAttack_Box_Enemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_FIREEND_ENEMY_04;
			g_aAttack_Box_Enemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_FIREEND_ENEMY_04;
			//1��
			if (g_aAttack_Box_Enemy[i].nCntPattern >= AMOUNT_STYLE_TEX_FIREEND_ENEMY_04)
			{
				g_aAttack_Box_Enemy[i].nCntPattern = 0;
				g_aAttack_Box_Enemy[i].fTexSpan[0] = 0;
				g_aAttack_Box_Enemy[i].fTexSpan[1] = 0;

				g_aAttack_Box_Enemy[i].nMode = BOX_MODE_NONE;
			}
		}
		break;
	}
	
	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Attack_Box_Enemy->Lock(0, 0, (void**)&pVtx_Attack_Box_Enemy, 0);

	pVtx_Attack_Box_Enemy += AMOUNT_VTX * i;

	if (g_aAttack_Box_Enemy[i].LR == 0)
	{
		pVtx_Attack_Box_Enemy[0].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[0], 0.0f);
		pVtx_Attack_Box_Enemy[1].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[1], 0.0f);
		pVtx_Attack_Box_Enemy[2].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[0], 1.0f);
		pVtx_Attack_Box_Enemy[3].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[1], 1.0f);
	}
	else
	{
		pVtx_Attack_Box_Enemy[0].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[1], 0.0f);
		pVtx_Attack_Box_Enemy[1].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[0], 0.0f);
		pVtx_Attack_Box_Enemy[2].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[1], 1.0f);
		pVtx_Attack_Box_Enemy[3].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[0], 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Attack_Box_Enemy->Unlock();
}

//************************************************
//�U���{�b�N�X�I���֐�
//************************************************
void Disapper_Attack_Box_Enemy(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		//�L���X�g�ς݃{�b�N�X���o�Ă�Ƃ�
		if (g_aAttack_Box_Enemy[nCnt].bUse && g_aAttack_Box_Enemy[nCnt].nAppear <= 0)
		{
			//�c������
			if (g_aAttack_Box_Enemy[nCnt].nRemain > 0)
			{
				g_aAttack_Box_Enemy[nCnt].nRemain--;
			}
			//����
			else
			{
				g_aAttack_Box_Enemy[nCnt].nMode = BOX_MODE_NONE;
				g_aAttack_Box_Enemy[nCnt].bUse = false;
				g_aAttack_Box_Enemy[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aAttack_Box_Enemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aAttack_Box_Enemy[nCnt].fX = 0.0f;
				g_aAttack_Box_Enemy[nCnt].LR = 0;
				g_aAttack_Box_Enemy[nCnt].nCntTex = 0;
				g_aAttack_Box_Enemy[nCnt].nCntPattern = 0;
				for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
				{
					g_aAttack_Box_Enemy[nCnt].fTexSpan[nCnt] = 0.0f;
					g_aAttack_Box_Enemy[nCnt].fRadius[nCnt2] = 0.0f;
					g_aAttack_Box_Enemy[nCnt].fLength[nCnt2] = 0.0f;
					g_aAttack_Box_Enemy[nCnt].fAngle[nCnt2] = 0.0f;
				}
				g_aAttack_Box_Enemy[nCnt].nRemain = 0;

				//���_���ւ̃|�C���^
				VERTEX_2D* pVtx_Attack_Box_Enemy;

				//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
				g_pVtxBuff_Attack_Box_Enemy->Lock(0, 0, (void**)&pVtx_Attack_Box_Enemy, 0);

				pVtx_Attack_Box_Enemy += AMOUNT_VTX * nCnt;

				pVtx_Attack_Box_Enemy[0].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z - (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
				pVtx_Attack_Box_Enemy[0].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z - (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
				pVtx_Attack_Box_Enemy[1].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z + (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
				pVtx_Attack_Box_Enemy[1].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z + (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
				pVtx_Attack_Box_Enemy[2].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z - g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];
				pVtx_Attack_Box_Enemy[2].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z - g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];
				pVtx_Attack_Box_Enemy[3].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z + g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];
				pVtx_Attack_Box_Enemy[3].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z + g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];

				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuff_Attack_Box_Enemy->Unlock();
			}
		}
	}
}

//************************************************
//�����蔻��֐�
//************************************************
void HitDetection_Attack_Box_Enemy(int nCnt)
{
	ENEMY* pEnemy = GetInfo_Enemy();
	PLAYER* pPlayer = GetInfo_Player();
	TOWER* pTower = GetInfo_Tower();

	//�U���{�b�N�X�Ƃ̓����蔻��
	//�G�����̃{�b�N�X�̂��߁A�v���C���[�ƃ{�b�N�X�A�^���[�ƃ{�b�N�X�Ŕ���

	//�v���C���[�ɂ��̔ԍ��̍U���{�b�N�X���G��Ă���
	if (pPlayer->pos.x - pPlayer->fRadius[0] < g_aAttack_Box_Enemy[nCnt].pos.x + g_aAttack_Box_Enemy[nCnt].fRadius[0] &&
		pPlayer->pos.x + pPlayer->fRadius[0] > g_aAttack_Box_Enemy[nCnt].pos.x - g_aAttack_Box_Enemy[nCnt].fRadius[0] &&
		pPlayer->pos.y - (pPlayer->fRadius[1] * 2.0f) < g_aAttack_Box_Enemy[nCnt].pos.y &&
		pPlayer->pos.y > g_aAttack_Box_Enemy[nCnt].pos.y - (g_aAttack_Box_Enemy[nCnt].fRadius[1] * 2.0f) &&
		pPlayer->nState != PLAYER_STATE_HURT1 && pPlayer->nState != PLAYER_STATE_HURT2)
	{
		//���C�t�����炷
		//pPlayer->nLife--;

		//�����ڃ{�b�N�X������
		pPlayer->nCntTex = 0;
		pPlayer->nCntPattern = 0;
		pPlayer->fTexSpan[0] = 0.0f;
		pPlayer->fTexSpan[1] = SPAN_CHANGE_TEX_HURT1_PLAYER;

		//��e��Ԃɍ����ւ��āA�A����e��h�~
		int n = rand() % 2;
		n == 0 ?
			pPlayer->nState = PLAYER_STATE_HURT1 :
			pPlayer->nState = PLAYER_STATE_HURT2;

		//���̓G�̌����ɍ��킹�ăm�b�N�o�b�N
		pEnemy[nCnt].LR == 0 ? pPlayer->move.x = 5.0f : pPlayer->move.x = -5.0f;
		pPlayer->move.y = -1.0f;

		PlaySound(SOUND_LABEL_PHURT);

		//�ђʂ��Ȃ�
		if (g_aAttack_Box_Enemy[nCnt].nMode == BOX_MODE_FIRE)
		{
			g_aAttack_Box_Enemy[nCnt].nCntPattern = 0;
			g_aAttack_Box_Enemy[nCnt].fTexSpan[0] = 0;
			g_aAttack_Box_Enemy[nCnt].fTexSpan[1] = SPAN_CHANGE_TEX_FIREEND_ENEMY_04;

			g_aAttack_Box_Enemy[nCnt].nMode = BOX_MODE_FIRE_END;

			g_aAttack_Box_Enemy[nCnt].nRemain = 5;
		}
	}

	//�^���[�ɂ��̔ԍ��̍U���{�b�N�X���G��Ă���
	if (pTower->pos.x - pTower->fRadius[0] < g_aAttack_Box_Enemy[nCnt].pos.x + g_aAttack_Box_Enemy[nCnt].fRadius[0] &&
		pTower->pos.x + pTower->fRadius[0] > g_aAttack_Box_Enemy[nCnt].pos.x - g_aAttack_Box_Enemy[nCnt].fRadius[0] &&
		pTower->pos.y - (pTower->fRadius[1] * 2.0f) < g_aAttack_Box_Enemy[nCnt].pos.y &&
		pTower->pos.y > g_aAttack_Box_Enemy[nCnt].pos.y - (g_aAttack_Box_Enemy[nCnt].fRadius[1] * 2.0f) &&
		pTower->nCT <= 0)
	{
		//���C�t�����炷
		pTower->nLife--;

		//�L���X�g�^�C���ݒ�
		pTower->nCT = 90;

		PlaySound(SOUND_LABEL_THURT);
	}
}

//************************************************
//�U���{�b�N�X�̃A�h���X��n��
//************************************************
ATTACK_BOX_ENEMY* GetInfo_Attack_Box_Enemy(void)
{
	return &g_aAttack_Box_Enemy[0];
}

//************************************************
//�f�o�b�O�p�̍U���{�b�N�X�̉���
//************************************************
void Draw_Attack_Box_Enemy_Debug(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Attack_Box_Enemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		switch (g_aAttack_Box_Enemy[nCnt].nMode)
		{
		case BOX_MODE_NONE:
			pDevice->SetTexture(0, g_pTexture_Attack_Box_Enemy[BOX_MODE_NONE]);
			break;
		case BOX_MODE_FIRE:
			pDevice->SetTexture(0, g_pTexture_Attack_Box_Enemy[BOX_MODE_FIRE]);
			break;
		case BOX_MODE_FIRE_END:
			pDevice->SetTexture(0, g_pTexture_Attack_Box_Enemy[BOX_MODE_FIRE_END]);
			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}