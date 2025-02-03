//************************************************
//
//�A�C�e������[item.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "enemy.h"
#include "item.h"
#include "player.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Item = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Item = NULL;	//���_�o�b�t�@�̃|�C���^
float g_fHoldRadius_Item = 0.0f;	//���a���R�s�[�p
ITEM g_aItem[AMOUNT_POLYGON_ITEM];	//�A�C�e���̊e���

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Item(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Item;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ITEM,
		&g_pTexture_Item);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Item,
		NULL);

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Item->Lock(0, 0, (void**)&pVtx_Item, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ITEM; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Item[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Item[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Item[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Item[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Item[0].rhw = 1.0f;
		pVtx_Item[1].rhw = 1.0f;
		pVtx_Item[2].rhw = 1.0f;
		pVtx_Item[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Item[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Item[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Item[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Item[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Item[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Item[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Item[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Item[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Item += AMOUNT_VTX;	//���_���̃|�C���^��4���i�߂�
	}

	//���a���R�s�[�p�ϐ�������
	g_fHoldRadius_Item = 0.0f;

	//�A�C�e�����̏�����
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ITEM; nCnt++)
	{
		g_aItem[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu����������
		g_aItem[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ�����������
		g_aItem[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F����������
		g_aItem[nCnt].nRemain = 0;				//�c�����Ԃ�������
		g_aItem[nCnt].bUse = false;				//�g�p�󋵔���𖳂���
		g_aItem[nCnt].style = ITEMSTYLE_TRACE;	//�A�C�e���̎�ނ��g���[�X��
		g_aItem[nCnt].state = ITEMSTATE_NORMAL;	//�A�C�e���̏�Ԃ�ʏ��
		g_aItem[nCnt].fColorA = 1.0;			//�����x�ύX�ϐ������ݒ�
		g_aItem[nCnt].fRadius = 0.0;			//���a�i�[�ϐ�������
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Item->Unlock();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Item(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Item != NULL)
	{
		g_pTexture_Item->Release();
		g_pTexture_Item = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Item != NULL)
	{
		g_pVtxBuff_Item->Release();
		g_pVtxBuff_Item = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Item(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Item;

	//�v���C���[���ւ̃|�C���^
	PLAYER* pPlayer;

	//�v���C���[���̎擾
	pPlayer = Getinfo_Player();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Item->Lock(0, 0, (void**)&pVtx_Item, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ITEM; nCnt++)
	{
		//�A�C�e�����g�p����Ă���Ƃ�
		if (g_aItem[nCnt].bUse)
		{
			//��Ԃɉ����ď�������
			switch (g_aItem[nCnt].state)
			{
			case ITEMSTATE_NORMAL:

				g_aItem[nCnt].nRemain--;

				if (g_aItem[nCnt].nRemain <= 0)
				{
					g_aItem[nCnt].state = ITEMSTATE_FLASHING;	//�_�ł��J�n

					g_aItem[nCnt].nRemain = FRASH_TIME_ITEM;	//����ŋ͂��Ɏc������
				}

				break;

			case ITEMSTATE_FLASHING:

				g_aItem[nCnt].nRemain--;

				//�_��
				g_aItem[nCnt].fColorA == 1.0f ? g_aItem[nCnt].fColorA = 0.0f : g_aItem[nCnt].fColorA = 1.0f;

				if (g_aItem[nCnt].nRemain <= 0)
				{
					g_aItem[nCnt].state = ITEMSTATE_DISAPPEAR;	//���Œv��
				}

				break;

			case ITEMSTATE_DISAPPEAR:

				Disappear_Item(nCnt);

				break;
			}

			//�A�C�e�����z���񂹂�
			if (g_aItem[nCnt].state != ITEMSTATE_DISAPPEAR)
			{
				//�A�C�e���̈ʒu���玩�@�̈ʒu�ւ̃x�N�g��
				D3DXVECTOR3 CollisionVector = pPlayer->pos - g_aItem[nCnt].pos;

				////���@�̈ʒu�ƃA�C�e���̈ʒu�̋���
				//float fDistance = sqrtf((CollisionVector.x * CollisionVector.x) + (CollisionVector.y * CollisionVector.y)) * 0.5f;

				////�A�C�e���̎��͈͓��ɓ�������
				//if (fDistance < g_aItem[nCnt].fRadius)
				//{
					//�z����
					g_aItem[nCnt].pos += CollisionVector * 0.01f;

					//�u��
					g_aItem[nCnt].move.x += sinf(g_aItem[nCnt].pos.x) * 0.035f;
					g_aItem[nCnt].move.y += cosf(g_aItem[nCnt].pos.y) * 0.035f;

					//�u�����f
					g_aItem[nCnt].pos.x += g_aItem[nCnt].move.x;
					g_aItem[nCnt].pos.y += g_aItem[nCnt].move.y;
				//}
			}

			//�A�C�e���ɐG���
			if (pPlayer->pos.x >= g_aItem[nCnt].pos.x - HALFSPAN_X_ITEM - HALFSPAN_X_PLAYER &&
				pPlayer->pos.x <= g_aItem[nCnt].pos.x + HALFSPAN_X_ITEM + HALFSPAN_X_PLAYER &&
				pPlayer->pos.y <= g_aItem[nCnt].pos.y + HALFSPAN_Y_ITEM + HALFSPAN_Y_PLAYER &&
				pPlayer->pos.y >= g_aItem[nCnt].pos.y - HALFSPAN_Y_ITEM - HALFSPAN_Y_PLAYER)
			{
				//�擾����
				GetItem_Player(AMOUNT_ADD_LIFE);

				g_aItem[nCnt].state = ITEMSTATE_DISAPPEAR;
			}

			pVtx_Item[0].pos.x = g_aItem[nCnt].pos.x - HALFSPAN_X_ITEM;
			pVtx_Item[0].pos.y = g_aItem[nCnt].pos.y - HALFSPAN_Y_ITEM;
			pVtx_Item[1].pos.x = g_aItem[nCnt].pos.x + HALFSPAN_X_ITEM;
			pVtx_Item[1].pos.y = g_aItem[nCnt].pos.y - HALFSPAN_Y_ITEM;
			pVtx_Item[2].pos.x = g_aItem[nCnt].pos.x - HALFSPAN_X_ITEM;
			pVtx_Item[2].pos.y = g_aItem[nCnt].pos.y + HALFSPAN_Y_ITEM;
			pVtx_Item[3].pos.x = g_aItem[nCnt].pos.x + HALFSPAN_X_ITEM;
			pVtx_Item[3].pos.y = g_aItem[nCnt].pos.y + HALFSPAN_Y_ITEM;

			pVtx_Item[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aItem[nCnt].fColorA);
			pVtx_Item[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aItem[nCnt].fColorA);
			pVtx_Item[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aItem[nCnt].fColorA);
			pVtx_Item[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aItem[nCnt].fColorA);

			pVtx_Item += AMOUNT_VTX;
		}
		//�g�p����Ă��Ȃ��Ƃ�(�o�O�h�~)
		else
		{
			g_aItem[nCnt].bUse = false;

			g_aItem[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			pVtx_Item[0].pos = g_aItem[nCnt].pos;
			pVtx_Item[1].pos = g_aItem[nCnt].pos;
			pVtx_Item[2].pos = g_aItem[nCnt].pos;
			pVtx_Item[3].pos = g_aItem[nCnt].pos;

			pVtx_Item += AMOUNT_VTX;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Item->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Item(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Item, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ITEM; nCnt++)
	{
		//�A�C�e�����g�p����Ă���ꍇ
		if (g_aItem[nCnt].bUse == true)
		{
			//�G�̎�ނɉ����ăe�N�X�`���𒣂�ւ�
			switch (g_aItem[nCnt].style)
			{
			case ITEMSTATE_NORMAL:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_Item);

				break;

			case 1:

				pDevice->SetTexture(0, g_pTexture_Item);

				break;
			}

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}

}

//************************************************
//�A�C�e���ݒ菈���֐�
//************************************************
void Setinfo_Item(D3DXVECTOR3 pos, int nStyle)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Item;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Item->Lock(0, 0, (void**)&pVtx_Item, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ITEM; nCnt++)
	{
		//�g�p����Ă��Ȃ��A�C�e�������m
		if (!g_aItem[nCnt].bUse)
		{
			g_aItem[nCnt].pos = pos;	//�ʒu������
			g_aItem[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ�����������
			g_aItem[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F��K���ɐݒ�
			g_aItem[nCnt].nRemain = REMAIN_TIME_ITEM;	//�c�����Ԃ�K���ɐݒ�
			g_aItem[nCnt].bUse = true;	//�g�p������o��

			//�A�C�e���̎�ނ�U�蕪��
			switch (nStyle)
			{
			case ITEMSTYLE_TRACE:

				g_aItem[nCnt].style = ITEMSTYLE_TRACE;

				//�z���񂹗p�͈̔͂��Z�b�g
				g_aItem[nCnt].fRadius = 600.0f;

				break;
			}

			g_aItem[nCnt].state = ITEMSTATE_NORMAL;	//�A�C�e���̏�Ԃ�ʏ��

			break;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Item->Unlock();
}

//************************************************
//�A�C�e�����ŏ����֐�
//************************************************
void Disappear_Item(int nCntItem)
{
	g_aItem[nCntItem].pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);//�ʒu����������
	g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ�����������
	g_aItem[nCntItem].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F����������
	g_aItem[nCntItem].nRemain = 0;				//�c�����Ԃ�������
	g_aItem[nCntItem].bUse = false;				//�g�p�󋵔���𖳂���
	g_aItem[nCntItem].style = ITEMSTYLE_TRACE;	//�A�C�e���̎�ނ��g���[�X��
	g_aItem[nCntItem].state = ITEMSTATE_NORMAL;	//�A�C�e���̏�Ԃ�ʏ��
	g_aItem[nCntItem].fColorA = 1.0;			//�����x�ύX�ϐ������ݒ�
	g_aItem[nCntItem].fRadius = 0.0;			//���a�i�[�ϐ�������
}