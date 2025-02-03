//************************************************
//
//�e����[shadow.cpp]
//Author�F���c����
//
//************************************************
#include "shadow.h"

#include "debugproc.h"

#include "player.h"

//�}�N����`
#define AMOUNT_SHADOW	(512)	//�e�̐�

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;	//�e�N�X�`���ւ̃|�C���^
Shadow g_aShadow[AMOUNT_SHADOW];	//�e���

//************************************************
//�e����
//************************************************
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e����������
	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		g_aShadow[i].nIdx = 0;
		g_aShadow[i].fSize = 0.0f;
		g_aShadow[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[i].pPos = NULL;
		g_aShadow[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[i].bUse = false;
	}

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\shadow000.jpg",
		&g_pTextureShadow);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̏����ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();
}

//************************************************
//�e�j��
//************************************************
void UninitShadow(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//************************************************
//�e�Z�b�g
//************************************************
void SetInfoShadow(float fSize, D3DXVECTOR3* pPos)
{
	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		if (!g_aShadow[i].bUse)
		{
			g_aShadow[i].nIdx = i;
			g_aShadow[i].bUse = true;
			g_aShadow[i].pPos = pPos;
			g_aShadow[i].fSize = fSize;

			//�T�C�Y�Z�b�g
			SetSizeShadow(i, MODE_GAME);

			break;
		}
	}
}

//************************************************
//�e�T�C�Y�Z�b�g
//************************************************
void SetSizeShadow(int nCnt, int mode)
{
	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX * nCnt;

	if (mode == MODE_GAME)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCnt].fSize, 0.0f, g_aShadow[nCnt].fSize);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCnt].fSize, 0.0f, g_aShadow[nCnt].fSize);
		pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nCnt].fSize, 0.0f, -g_aShadow[nCnt].fSize);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCnt].fSize, 0.0f, -g_aShadow[nCnt].fSize);
	}
	else
	{
		Player* pPlayer = GetInfoPlayer();

		g_aShadow[nCnt].fSize = pPlayer->aParts[0].mtxWorld._42;

		pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCnt].fSize, 0.0f, g_aShadow[nCnt].fSize);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCnt].fSize, 0.0f, g_aShadow[nCnt].fSize);
		pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nCnt].fSize, 0.0f, -g_aShadow[nCnt].fSize);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCnt].fSize, 0.0f, -g_aShadow[nCnt].fSize);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - pPlayer->aParts[0].mtxWorld._42 * 0.015f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - pPlayer->aParts[0].mtxWorld._42 * 0.015f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - pPlayer->aParts[0].mtxWorld._42 * 0.015f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - pPlayer->aParts[0].mtxWorld._42 * 0.015f);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();
}

//************************************************
//�e�X�V
//************************************************
void UpdateShadow(int mode)
{
	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		if (mode != MODE_TITLE)
		{
			if (g_aShadow[i].bUse)
			{
				//�e�͉��ɒǏ]
				g_aShadow[i].pos = *g_aShadow[i].pPos;
				g_aShadow[i].pos.y = 0.01f;
			}
		}
		else
		{
			if (g_aShadow[i].bUse)
			{
				Player* pPlayer = GetInfoPlayer();

				//�e�̓��f���p�[�c�ɒǏ]
				g_aShadow[i].pos.x = pPlayer->aParts[0].mtxWorld._41;
				g_aShadow[i].pos.z = pPlayer->aParts[0].mtxWorld._43;
				g_aShadow[i].pos.y = 0.01f;

				//���ʂɃT�C�Y�ύX
				SetSizeShadow(i, mode);
			}
		}
	}
}

//************************************************
//�e����
//************************************************
void DisappearShadow(D3DXVECTOR3* pPos)
{
	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		//�A�h���X����v����΂��̉e���폜
		if (g_aShadow[i].pPos == pPos)
		{
			g_aShadow[i].bUse = false;

			break;
		}
	}
}

//************************************************
//�e�`��
//************************************************
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int i = 0; i < AMOUNT_SHADOW; i++)
	{
		if (g_aShadow[i].bUse)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aShadow[i].mtxWorld);

			//�����𔽉f1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aShadow[i].rot.y,
				g_aShadow[i].rot.x,
				g_aShadow[i].rot.z);

			//�����𔽉f2
			D3DXMatrixMultiply(&g_aShadow[i].mtxWorld,
				&g_aShadow[i].mtxWorld,
				&mtxRot);

			//�ʒu�𔽉f1
			D3DXMatrixTranslation(&mtxTrans,
				g_aShadow[i].pos.x,
				g_aShadow[i].pos.y,
				g_aShadow[i].pos.z);

			//�ʒu�𔽉f2
			D3DXMatrixMultiply(&g_aShadow[i].mtxWorld,
				&g_aShadow[i].mtxWorld,
				&mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[i].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}

	//�A���t�@�e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//���Z�����̉���
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}