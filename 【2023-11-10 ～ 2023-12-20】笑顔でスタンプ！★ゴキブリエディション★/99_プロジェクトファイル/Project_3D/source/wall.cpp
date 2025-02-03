//************************************************
//
//�ǐ���[wall.cpp]
//Author�F���c����
//
//************************************************
#include "wall.h"

#include "debugproc.h"

#include "bullet.h"
#include "player.h"
#include "visible_rect.h"

//�}�N����`
#define	AMOUNT_WALL	(4)	//�ǂ̐�
#define SPAN_WALL	(100.0f)	//�ǂ̃T�C�Y

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall;	//�e�N�X�`���ւ̃|�C���^
Wall g_aWall[AMOUNT_WALL];	//�Ǐ��

//************************************************
//�Ǐ���
//************************************************
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�O���[�o���ϐ��̏����ݒ�
	g_pVtxBuffWall = NULL;
	g_pTextureWall = NULL;

	/* ReadInfo�̕ς�� */
	for (int i = 0; i < AMOUNT_WALL; i++)
	{
		switch (i)
		{
		case 0:
			g_aWall[i].pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
			break;
		case 1:
			g_aWall[i].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
			break;
		case 2:
			g_aWall[i].pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
			break;
		case 3:
			g_aWall[i].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
			break;
		}
	
		g_aWall[i].rot = D3DXVECTOR3(0.0f, 0.0f + ((D3DX_PI * 0.5f) * i), 0.0f);
	
		g_aWall[i].aabb.min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[i].aabb.max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}


	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\KabeTex.bmp",
		&g_pTextureWall);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_WALL; i++)
	{
		//���_���W�̐ݒ�
		/* �e�X�g�p */
		pVtx[0].pos = D3DXVECTOR3(-SPAN_WALL, SPAN_WALL * 0.5f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SPAN_WALL, SPAN_WALL * 0.5f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SPAN_WALL, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SPAN_WALL, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffWall->Unlock();

	//�����蔻�������
	UpdateWallAABB();
	for (int i = 0; i < AMOUNT_WALL; i++)
	{
		//SetSizeVisible_Rect(g_aWall[i].aabb, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), &g_aWall[i].pos);
	}
}

//************************************************
//�ǔj��
//************************************************
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//************************************************
//�ǍX�V
//************************************************
void UpdateWall(void)
{
	g_aWall[0].pos.x += 0.1f;

	//��AABB�X�V
	UpdateWallAABB();
}

//************************************************
//��AABB�X�V
//************************************************
void UpdateWallAABB(void)
{
	for (int i = 0; i < AMOUNT_WALL; i++)
	{
		g_aWall[i].aabb.min =
		{
			g_aWall[i].pos.x - (SPAN_WALL * fabsf(cosf(g_aWall[i].rot.y))),
			g_aWall[i].pos.y,
			g_aWall[i].pos.z - (SPAN_WALL * fabsf(sinf(g_aWall[i].rot.y)))
		};

		g_aWall[i].aabb.max =
		{
			g_aWall[i].pos.x + (SPAN_WALL * fabsf(cosf(g_aWall[i].rot.y))),
			g_aWall[i].pos.y + SPAN_WALL * 0.5f,
			g_aWall[i].pos.z + (SPAN_WALL * fabsf(sinf(g_aWall[i].rot.y)))
		};

		//PrintDebugProc("��[%d]��AABB�F( %f ~ %f, %f ~ %f, %f ~ %f, )\n", i, g_aWall[i].aabb.min.x, g_aWall[i].aabb.max.x, g_aWall[i].aabb.min.y, g_aWall[i].aabb.max.y, g_aWall[i].aabb.min.z, g_aWall[i].aabb.max.z);
	}
}

//************************************************
//�ǂ̓����蔻��
//************************************************
void CollisionWall(void)
{
	int HitIdx = -1;

	Player* pPlayer = GetInfoPlayer();

	for (int i = 0; i < AMOUNT_WALL; i++)
	{
		PrintDebugProc("%d�Ԗڂ̕����F[%f]\n", i, atan2f(g_aWall[i].pos.x - pPlayer->pos.x, g_aWall[i].pos.z - pPlayer->pos.z));

		if (CollisionAABB(pPlayer->aabb, g_aWall[i].aabb))
		{
			HitIdx = i;

			PrintDebugProc("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

			/* ����ɁA�ǂ̕ӂ��������Ă���̂����� */
			int Type = CollisionAABB_Vtx(pPlayer->aabb, g_aWall[HitIdx].aabb);

			if (Type == Xside)
			{
				pPlayer->pos.x = pPlayer->posOld.x;
				pPlayer->move.x = 0.0f;
			}
			else if (Type == Zside)
			{
				pPlayer->pos.z = pPlayer->posOld.z;
				pPlayer->move.z = 0.0f;
			}
			else if (Type == OnlyVtx)
			{
				bool Xside = false;

				if (atan2f(g_aWall[HitIdx].pos.x - pPlayer->pos.x, g_aWall[HitIdx].pos.z - pPlayer->pos.z) < -0.7853975f &&
					atan2f(g_aWall[HitIdx].pos.x - pPlayer->pos.x, g_aWall[HitIdx].pos.z - pPlayer->pos.z) > -2.3561925f)
				{
					pPlayer->pos.x = pPlayer->posOld.x;
					pPlayer->move.x = 0.0f;

					Xside = true;
				}

				//if (atan2f(g_aWall[HitIdx].pos.x - pPlayer->pos.x, g_aWall[HitIdx].pos.z - pPlayer->pos.z) > 0.7853975f &&
				//	atan2f(g_aWall[HitIdx].pos.x - pPlayer->pos.x, g_aWall[HitIdx].pos.z - pPlayer->pos.z) < 2.3561925f)
				//{
				//	pPlayer->pos.x = pPlayer->posOld.x;
				//	pPlayer->move.x = 0.0f;
				//
				//	Xside = true;
				//}

				if (!Xside)
				{
					pPlayer->pos.z = pPlayer->posOld.z;
					pPlayer->move.z = 0.0f;
				}
			}
		}
	}
}

//************************************************
//�Ǖ`��
//************************************************
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int i = 0; i < AMOUNT_WALL; i++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aWall[i].mtxWorld);

		//�����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aWall[i].rot.y,
			g_aWall[i].rot.x,
			g_aWall[i].rot.z);

		//�����𔽉f2
		D3DXMatrixMultiply(&g_aWall[i].mtxWorld,
			&g_aWall[i].mtxWorld,
			&mtxRot);

		//�ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_aWall[i].pos.x,
			g_aWall[i].pos.y,
			g_aWall[i].pos.z);

		//�ʒu�𔽉f2
		D3DXMatrixMultiply(&g_aWall[i].mtxWorld,
			&g_aWall[i].mtxWorld,
			&mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aWall[i].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureWall);

		//�ǂ̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}