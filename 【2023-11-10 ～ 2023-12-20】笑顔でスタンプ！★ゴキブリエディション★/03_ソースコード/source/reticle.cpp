//************************************************
//
//���e�B�N��[reticle.cpp]
//Author�F���c����
//
//************************************************
#include "reticle.h"

#include "camera.h"
#include "shadow.h"

//�}�N����`
#define AMOUNT_RETICLE	(1)	//���e�B�N����
#define SPAN_RETICLE	(30.0f)	//���e�B�N���T�C�Y

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffReticle = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureReticle = NULL;	//�e�N�X�`���ւ̃|�C���^
Reticle g_aReticle[AMOUNT_RETICLE] = {};

//************************************************
//���e�B�N������
//************************************************
void InitReticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���e�B�N����񏉊���
	for (int i = 0; i < AMOUNT_RETICLE; i++)
	{
		g_aReticle[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aReticle[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\250.png",
		&g_pTextureReticle);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_RETICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffReticle,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffReticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_RETICLE; i++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	g_pVtxBuffReticle->Unlock();

	SizeSetReticle();
}

//************************************************
//���e�B�N���j��
//************************************************
void UninitReticle(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureReticle != NULL)
	{
		g_pTextureReticle->Release();
		g_pTextureReticle = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffReticle != NULL)
	{
		g_pVtxBuffReticle->Release();
		g_pVtxBuffReticle = NULL;
	}
}

//************************************************
//���e�B�N���W�J
//************************************************
void SizeSetReticle(void)
{
	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffReticle->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-SPAN_RETICLE, SPAN_RETICLE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SPAN_RETICLE, SPAN_RETICLE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-SPAN_RETICLE, -SPAN_RETICLE, -0.0f);
	pVtx[3].pos = D3DXVECTOR3(SPAN_RETICLE, -SPAN_RETICLE, -0.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffReticle->Unlock();
}

//************************************************
//���e�B�N���X�V
//************************************************
void UpdateReticle(void)
{
	Camera* pCamera = GetInfoCamera();

	//�����_�̎w����Ƀ��e�B�N����ݒu
	g_aReticle[0].pos = pCamera->posR;
}

//************************************************
//���e�B�N���`��
//************************************************
void DrawReticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���C�g���I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�r���[�}�g���b�N�X�擾
	D3DXMATRIX mtxView;

	for (int i = 0; i < AMOUNT_RETICLE; i++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aReticle[i].mtxWorld);

		//�r���[�}�g���b�N�X�擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����̐��ʂɌ���������
		D3DXMatrixInverse(&g_aReticle[i].mtxWorld, NULL, &mtxView);	//�t�s������߂�

		g_aReticle[i].mtxWorld._41 = 0.0f;
		g_aReticle[i].mtxWorld._42 = 0.0f;
		g_aReticle[i].mtxWorld._43 = 0.0f;

		//�ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_aReticle[i].pos.x,
			g_aReticle[i].pos.y,
			g_aReticle[i].pos.z);

		//�ʒu�𔽉f2
		D3DXMatrixMultiply(&g_aReticle[i].mtxWorld,
			&g_aReticle[i].mtxWorld,
			&mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aReticle[i].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffReticle, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureReticle);

		//���e�B�N���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//���C�g���I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//************************************************
//���e�B�N�������擾
//************************************************
Reticle* GetInfoReticle(void)
{
	return &g_aReticle[0];
}