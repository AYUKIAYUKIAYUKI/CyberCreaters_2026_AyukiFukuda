//************************************************
//
//���C[ray.cpp]
//Author�F���c����
//
//************************************************
#include "ray.h"

#include "camera.h"
#include "player.h"

//�}�N����`
#define AMOUNT_RAY	(1)	//���C�̐�
#define SPAN_RAY	(1.0f)	//���C�̍L��
#define HEIGHT_RAY	(1000.0f)	//���C�̍���

#define COLUMN_RAY	(31)	//��(���̕�)
#define LINE_RAY	(100)	//�s(��������)

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRay = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRay = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffRay = NULL;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Ray g_aRay[AMOUNT_RAY] = {};	//���C���
static const float g_F = 1.0f;	//�萔1.0f
/* 1�|���S�������� */
static const int g_nAmountVtx = (COLUMN_RAY * LINE_RAY);	//���_�̐�
static const int g_nAmountPrimitive = (((COLUMN_RAY - 1) * (LINE_RAY - 1)) * 2) + ((LINE_RAY - 2) * 4);	//�ʂ̐�
static const int g_nAmountIdx = g_nAmountPrimitive + 2;	//�C���f�b�N�X�̐�
static const float g_COLUMN = g_F / (COLUMN_RAY - 1);	//���񕪂�1
static const float g_LINE = g_F / (LINE_RAY - 1);	//���s����1

//************************************************
//���C����
//************************************************
void InitRay(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	for (int i = 0; i < AMOUNT_RAY; i++)
	{
		g_aRay[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRay[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRay[i].fPA = 0.0f;
	}

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\",
		&g_pTextureRay);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nAmountVtx * AMOUNT_RAY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRay,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffRay->Lock(0, 0, (void**)&pVtx, 0);

	float fP[3] = {};	/* [0]����A[1]���s�A[2]��texX (���W�p��tex�p���K�v�ȗ��R�v����) */
	for (int i = 0, j = 0; i < g_nAmountVtx; i++, j++)
	{
		//1�񕪃��[�v���������ꍇ
		if (j >= COLUMN_RAY)
		{
			fP[1] += g_LINE;	/* ���s����1���� */
			j = 0;	/* ��J�E���g���Z�b�g */
			fP[0] = 0.0f;	/* �~���Ȃ̂ŗ�ʒu�����Z�b�g */
		}

		fP[2] = g_COLUMN * (float)j;	/* ��J�E���g���A���񕪂�1���� */

		//���_���W�̐ݒ�
		pVtx[i].pos = D3DXVECTOR3(-cosf(fP[0]) * SPAN_RAY,
			HEIGHT_RAY * (fP[1]),
			sinf(fP[0]) * SPAN_RAY);

		//������c�H(�v����)
		fP[0] += D3DX_PI * (2.0f / (COLUMN_RAY - 1));

		//�@���x�N�g���̐ݒ�
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̏����ݒ�
		pVtx[i].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx[i].tex = D3DXVECTOR2(-fP[2] * 2.0f, -fP[1]);
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRay->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nAmountIdx * AMOUNT_RAY,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffRay,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̃|�C���^
	WORD* pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffRay->Lock(0, 0, (void**)&pIdx, 0);

	int Z = 0;	//�s���J�E���g
	while (1)	/* ���[�v�񐔂͏k�ރ��[�v�� */
	{
		//�s�̋N�_������W�J����
		for (int X = 0; X < COLUMN_RAY; X++, pIdx += 2)	/* 2���_�Z�b�g�ŗ񂪂���Ă��� */
		{
			pIdx[0] = (WORD)(COLUMN_RAY + X + (Z * COLUMN_RAY));	/* �񐔎��̂��N�_�̃C���f�b�N�X�ɂȂ� */
			pIdx[1] = (WORD)(X + (Z * COLUMN_RAY));
		}

		//�k�ރ��[�v���o���Ȃ��Ȃ�΃��[�v�𔲂���
		if (Z >= LINE_RAY - 2) break;

		pIdx[0] = (WORD)((COLUMN_RAY * (Z + 1)) - 1);	/* (�� * (�Y���s + 1)) - 1�ł��̍s�̉E��̊p */
		pIdx[1] = (WORD)((Z + 2) * COLUMN_RAY);	/* (�Y���s + 2) * �񐔂ŋN�_�̂����1�s���� */

		pIdx += 2;
		Z++;	/* �s�̋N�_��1�i������ */
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffRay->Unlock();
}

//************************************************
//���C�j��
//************************************************
void UninitRay(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRay != NULL)
	{
		g_pTextureRay->Release();
		g_pTextureRay = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRay != NULL)
	{
		g_pVtxBuffRay->Release();
		g_pVtxBuffRay = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffRay != NULL)
	{
		g_pIdxBuffRay->Release();
		g_pIdxBuffRay = NULL;
	}
}

//************************************************
//���C�X�V(������)
//************************************************
void UpdateRay(void)
{
	/* �e�X�g��� */
	const Player* pPlayer = GetInfoPlayer();
	const Camera* pCamera = GetInfoCamera();

	for (int i = 0; i < AMOUNT_RAY; i++)
	{
		//�����̃s�{�b�g���v���C���[�̈ʒu��
		g_aRay[i].pos = pPlayer->pos;

		//�����̌������J�����������_�̕�����
		g_aRay[i].rot.x = -pCamera->fPA + D3DX_PI * 0.5f;
		g_aRay[i].rot.y = pCamera->rot.y;
		g_aRay[i].rot.z;
	}
}

//************************************************
//���C�`��
//************************************************
void DrawRay(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���C�g���I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���C���[�t���[���`��J�n
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int i = 0; i < AMOUNT_RAY; i++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aRay[i].mtxWorld);

		//�����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aRay[i].rot.y,
			g_aRay[i].rot.x,
			g_aRay[i].rot.z);

		//�����𔽉f2
		D3DXMatrixMultiply(&g_aRay[i].mtxWorld,
			&g_aRay[i].mtxWorld,
			&mtxRot);

		//�ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_aRay[i].pos.x,
			g_aRay[i].pos.y,
			g_aRay[i].pos.z);

		//�ʒu�𔽉f2
		D3DXMatrixMultiply(&g_aRay[i].mtxWorld,
			&g_aRay[i].mtxWorld,
			&mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aRay[i].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffRay, 0, sizeof(VERTEX_3D));

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffRay);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRay);

		//���C�̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_nAmountVtx,
			0, g_nAmountPrimitive);

		//���C�g���I��
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	//���C���[�t���[���`��I��
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}