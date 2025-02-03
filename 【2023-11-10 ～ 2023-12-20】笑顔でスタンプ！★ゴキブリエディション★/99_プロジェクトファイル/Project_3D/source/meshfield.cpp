//************************************************
//
//���b�V���t�B�[���h����[meshfield.cpp]
//Author�F���c����
//
//************************************************
#include "meshfield.h"

//�}�N����`
#define AMOUNT_MESHFIELD	(1)	//���b�V���t�B�[���h�̐�
#define SPAN_MESHFIELD	(40.0f)	//���b�V���t�B�[���h�̑傫��

#define COLUMN_MESHFIELD	(5)	//��(���̕�)
#define LINE_MESHFIELD	(5)	//�s(��������)

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Meshfield g_aMeshfield[AMOUNT_MESHFIELD] = {};
static const float g_F = 1.0f;	//�萔1.0f
/* 1�|���S�������� */
static const int g_nAmountVtx = (COLUMN_MESHFIELD * LINE_MESHFIELD);	//���_�̐�
static const int g_nAmountPrimitive = (((COLUMN_MESHFIELD - 1) * (LINE_MESHFIELD - 1)) * 2) + ((LINE_MESHFIELD - 2) * 4);	//�ʂ̐�
static const int g_nAmountIdx = g_nAmountPrimitive + 2;	//�C���f�b�N�X�̐�
static const float g_COLUMN = g_F / (COLUMN_MESHFIELD - 1);	//���񕪂�1
static const float g_LINE = g_F / (LINE_MESHFIELD - 1);	//���s����1

//************************************************
//���b�V���t�B�[���h����
//************************************************
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	for (int i = 0; i < AMOUNT_MESHFIELD; i++)
	{
		g_aMeshfield[i].pos = D3DXVECTOR3(0.0f, 10.0f, 30.0f);
		g_aMeshfield[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\UV.jpg",
		&g_pTextureMeshfield);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nAmountVtx * AMOUNT_MESHFIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	float fP[2] = {};	/* [0]����A[1]���s */
	for (int i = 0, j = 0; i < g_nAmountVtx; i++, j++)
	{
		//1�񕪃��[�v���������ꍇ
		if (j >= COLUMN_MESHFIELD)
		{
			fP[1] += g_LINE;	/* ���s����1���� */
			j = 0;	/* ��J�E���g���Z�b�g */
		}

		fP[0] = g_COLUMN * (float)j;	/* ��J�E���g���A���񕪂�1���� */

		//���_���W�̐ݒ�
		pVtx[i].pos = D3DXVECTOR3((fP[0] * SPAN_MESHFIELD) - (SPAN_MESHFIELD * 0.5f),
			0.0f,
			(-fP[1] * SPAN_MESHFIELD) + (SPAN_MESHFIELD * 0.5f));

		/* ������Ŋ�Ԓ��_���㏸ */
		if (i != 0 && i % 2 != 0) pVtx[i].pos.y = 5.0f;

		//�@���x�N�g���̐ݒ�
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̏����ݒ�
		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx[i].tex = D3DXVECTOR2(fP[0], fP[1]);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMeshfield->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nAmountIdx * AMOUNT_MESHFIELD,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshfield,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̃|�C���^
	WORD* pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	int Z = 0;	//�s���J�E���g�p
	while (1)	/* ���[�v�񐔂͏k�ރ��[�v�� */
	{
		//�s�̋N�_������W�J����
		for (int X = 0; X < COLUMN_MESHFIELD; X++, pIdx += 2)	/* 2���_�Z�b�g�ŗ񂪂���Ă��� */
		{
			pIdx[0] = (WORD)(COLUMN_MESHFIELD + X + (Z * COLUMN_MESHFIELD));	/* �񐔎��̂��N�_�̃C���f�b�N�X�ɂȂ� */
			pIdx[1] = (WORD)(X + (Z * COLUMN_MESHFIELD));
		}

		//�k�ރ��[�v���o���Ȃ��Ȃ�΃��[�v�𔲂���
		if (Z >= LINE_MESHFIELD - 2) break;

		pIdx[0] = (WORD)((COLUMN_MESHFIELD * (Z + 1)) - 1);	/* (�� * (�Y���s + 1)) - 1�ł��̍s�̉E��̊p */
		pIdx[1] = (WORD)((Z + 2) * COLUMN_MESHFIELD);	/* (�Y���s + 2) * �񐔂ŋN�_�̂����1�s���� */

		pIdx += 2;
		Z++;	/* �s�̋N�_��1�i������ */
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshfield->Unlock();
}

//************************************************
//���b�V���t�B�[���h�j��
//************************************************
void UninitMeshfield(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshfield != NULL)
	{
		g_pIdxBuffMeshfield->Release();
		g_pIdxBuffMeshfield = NULL;
	}
}

//************************************************
//���b�V���t�B�[���h�X�V
//************************************************
void UpdateMeshfield(void)
{

}

//************************************************
//���b�V���t�B�[���h�`��
//************************************************
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int i = 0; i < AMOUNT_MESHFIELD; i++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aMeshfield[i].mtxWorld);

		//�����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aMeshfield[i].rot.y,
			g_aMeshfield[i].rot.x,
			g_aMeshfield[i].rot.z);

		//�����𔽉f2
		D3DXMatrixMultiply(&g_aMeshfield[i].mtxWorld,
			&g_aMeshfield[i].mtxWorld,
			&mtxRot);

		//�ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_aMeshfield[i].pos.x,
			g_aMeshfield[i].pos.y,
			g_aMeshfield[i].pos.z);

		//�ʒu�𔽉f2
		D3DXMatrixMultiply(&g_aMeshfield[i].mtxWorld,
			&g_aMeshfield[i].mtxWorld,
			&mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aMeshfield[i].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffMeshfield);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshfield);

		//���b�V���t�B�[���h�̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_nAmountVtx,
			0, g_nAmountPrimitive);
	}
}