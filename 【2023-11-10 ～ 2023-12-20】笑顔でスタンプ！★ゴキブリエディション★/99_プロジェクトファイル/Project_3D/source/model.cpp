//************************************************
//
//���f��[model.cpp]
//Author�F���c����
//
//************************************************
#include "model.h"

#include "debugproc.h"

#include "collision.h"
#include "player.h"
#include "visible_rect.h"

//�}�N����`
#define AMOUNT_MODEL	(4)	//���f����

//�O���[�o���ϐ�
LPD3DXMESH g_pMeshModel = NULL;	//���b�V���c���_���̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;	//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatModel = 0;	//�}�e���A���̐�
Model g_aModel[AMOUNT_MODEL];	//���f�����

//************************************************
//���f������
//************************************************
void InitModel(int mode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	g_dwNumMatModel = 0;	//�}�e���A���̐����N���A

	//�ǂ����悤
	if (mode != MODE_TUTORIAL)
	{
		g_aModel[0].pos = D3DXVECTOR3(150.0f, 0.0f, 150.0f);
		g_aModel[1].pos = D3DXVECTOR3(-150.0f, 0.0f, 150.0f);
		g_aModel[2].pos = D3DXVECTOR3(150.0f, 0.0f, -150.0f);
		g_aModel[3].pos = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
	}
	else
	{
		g_aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
		g_aModel[1].pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
		g_aModel[2].pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
		g_aModel[3].pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
	}

	//���f���̏���
	for (int i = 0; i < AMOUNT_MODEL; i++)
	{
		g_aModel[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[i].aabb = {};
	}

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\model\\roach_home.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_dwNumMatModel,
		&g_pMeshModel);

	UpdateModelAABB();
	for (int i = 0; i < AMOUNT_MODEL; i++)
	{
		//SetSizeVisible_Rect(g_aModel[i].aabb, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), &g_aModel[i].pos);
	}
}

//************************************************
//���f���j��
//************************************************
void UninitModel(void)
{
	//���b�V���̔j��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//************************************************
//���f���X�V
//************************************************
void UpdateModel(void)
{

}

//************************************************
//���f��AABB�X�V
//************************************************
void UpdateModelAABB(void)
{
	for (int i = 0; i < AMOUNT_MODEL; i++)
	{
		g_aModel[i].aabb.min =
		{
			g_aModel[i].pos.x - 15.0f,
			g_aModel[i].pos.y,
			g_aModel[i].pos.z - 15.0f
		};

		g_aModel[i].aabb.max =
		{
			g_aModel[i].pos.x + 15.0f,
			g_aModel[i].pos.y + 5.0f,
			g_aModel[i].pos.z + 15.0f
		};
	}
}

//************************************************
//���f���̓����蔻��
//************************************************
void CollisionModel(void)
{
	int HitIdx = -1;

	Player* pPlayer = GetInfoPlayer();

	for (int i = 0; i < AMOUNT_MODEL; i++)
	{
		if (CollisionAABB(pPlayer->aabb, g_aModel[i].aabb))
		{
			HitIdx = i;

			PrintDebugProc("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

			/* ����ɁA�ǂ̕ӂ��������Ă���̂����� */
			int Type = CollisionAABB_Vtx(pPlayer->aabb, g_aModel[HitIdx].aabb);

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
				//pPlayer->pos = pPlayer->posOld;
				pPlayer->move =
				{
					-sinf(atan2f(pPlayer->move.x, pPlayer->move.z)),
					0.0f,
					-cosf(atan2f(pPlayer->move.x, pPlayer->move.z))
				};
			}
		}
	}
}

//************************************************
//���f���`��
//************************************************
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;	//�}�e���A���f�[�^�ւ̃|�C���^

	for (int i = 0; i < AMOUNT_MODEL; i++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aModel[i].mtxWorld);

		//�����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aModel[i].rot.y,
			g_aModel[i].rot.x,
			g_aModel[i].rot.z);

		//�����𔽉f2
		D3DXMatrixMultiply(&g_aModel[i].mtxWorld,
			&g_aModel[i].mtxWorld,
			&mtxRot);

		//�ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_aModel[i].pos.x,
			g_aModel[i].pos.y,
			g_aModel[i].pos.z);

		//�ʒu�𔽉f2
		D3DXMatrixMultiply(&g_aModel[i].mtxWorld,
			&g_aModel[i].mtxWorld,
			&mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aModel[i].mtxWorld);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//���f���p�[�c�̕`��
			g_pMeshModel->DrawSubset(nCntMat);
		}

		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

Model* GetInfoModel(void)
{
	return &g_aModel[0];
}