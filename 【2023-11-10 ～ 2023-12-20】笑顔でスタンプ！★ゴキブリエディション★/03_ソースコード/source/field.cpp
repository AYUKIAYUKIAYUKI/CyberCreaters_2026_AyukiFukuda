//************************************************
//
//�n�ʐ���[field.cpp]
//Author�F���c����
//
//************************************************
#include "field.h"

//�}�N����`
#define AMOUNT_FIELD	(1)	//���̐�
#define SPAN_FIELD	(250.0f)	//���̃T�C�Y

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureField = NULL;	//�e�N�X�`���ւ̃|�C���^
Field g_aField[AMOUNT_FIELD] = {};

//************************************************
//�n�ʏ���
//************************************************
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	for (int i = 0; i < AMOUNT_FIELD; i++)
	{
		g_aField[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\soil_circle.png",
		&g_pTextureField);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_FIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_FIELD; i++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-SPAN_FIELD, 0.0f, SPAN_FIELD);
		pVtx[1].pos = D3DXVECTOR3(SPAN_FIELD, 0.0f, SPAN_FIELD);
		pVtx[2].pos = D3DXVECTOR3(-SPAN_FIELD, 0.0f, -SPAN_FIELD);
		pVtx[3].pos = D3DXVECTOR3(SPAN_FIELD, 0.0f, -SPAN_FIELD);

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
	g_pVtxBuffField->Unlock();
}

//************************************************
//�n�ʔj��
//************************************************
void UninitField(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//************************************************
//�n�ʍX�V
//************************************************
void UpdateField(void)
{

}

//************************************************
//�n�ʕ`��
//************************************************
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	for (int i = 0; i < AMOUNT_FIELD; i++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aField[i].mtxWorld);

		//�����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aField[i].rot.y,
			g_aField[i].rot.x,
			g_aField[i].rot.z);

		//�����𔽉f2
		D3DXMatrixMultiply(&g_aField[i].mtxWorld,
			&g_aField[i].mtxWorld,
			&mtxRot);

		//�ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_aField[i].pos.x,
			g_aField[i].pos.y,
			g_aField[i].pos.z);

		//�ʒu�𔽉f2
		D3DXMatrixMultiply(&g_aField[i].mtxWorld,
			&g_aField[i].mtxWorld,
			&mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aField[i].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureField);

		//�n�ʂ̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}