//************************************************
//
//�r���{�[�h����[billboard.cpp]
//Author�F���c����
//
//************************************************
#include "billboard.h"

#include "shadow.h"

//�}�N����`
#define AMOUNT_BILLBOARD	(1)

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;	//�e�N�X�`���ւ̃|�C���^
Billboard g_aBillboard[AMOUNT_BILLBOARD] = {};

//************************************************
//�r���{�[�h����
//************************************************
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�r���{�[�h��񏉊���
	for (int i = 0; i < AMOUNT_BILLBOARD; i++)
	{
		g_aBillboard[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Rozalia.png",
		&g_pTextureBillboard);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_BILLBOARD; i++)
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
	g_pVtxBuffBillboard->Unlock();
}

//************************************************
//�r���{�[�h�j��
//************************************************
void UninitBillboard(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//************************************************
//�r���{�[�h�X�V
//************************************************
void UpdateBillboard(void)
{

}

//************************************************
//�r���{�[�h�`��
//************************************************
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���C�g���I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�r���[�}�g���b�N�X�擾
	D3DXMATRIX mtxView;
	
	for (int i = 0; i < AMOUNT_BILLBOARD; i++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBillboard[i].mtxWorld);

		//�r���[�}�g���b�N�X�擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����̐��ʂɌ���������
		D3DXMatrixInverse(&g_aBillboard[i].mtxWorld, NULL, &mtxView);	//�t�s������߂�

		g_aBillboard[i].mtxWorld._41 = 0.0f;
		g_aBillboard[i].mtxWorld._42 = 0.0f;
		g_aBillboard[i].mtxWorld._43 = 0.0f;

		//�ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_aBillboard[i].pos.x,
			g_aBillboard[i].pos.y,
			g_aBillboard[i].pos.z);

		//�ʒu�𔽉f2
		D3DXMatrixMultiply(&g_aBillboard[i].mtxWorld,
			&g_aBillboard[i].mtxWorld,
			&mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[i].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBillboard);

		//�r���{�[�h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//���C�g���I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}