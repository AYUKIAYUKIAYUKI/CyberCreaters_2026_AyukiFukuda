//************************************************
//
//���[�X�\������[wreath.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "wreath.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Wreath[AMOUNT_TEXTURE_WREATH] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Wreath = NULL;	//���_�o�b�t�@�̃|�C���^

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Wreath()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WREATH,
		&g_pTexture_Wreath[0]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WOOD,
		&g_pTexture_Wreath[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_WREATH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Wreath,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Wreath;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Wreath->Lock(0, 0, (void**)&pVtx_Wreath, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_WREATH; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Wreath[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Wreath[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Wreath[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Wreath[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Wreath[0].rhw = 1.0f;
		pVtx_Wreath[1].rhw = 1.0f;
		pVtx_Wreath[2].rhw = 1.0f;
		pVtx_Wreath[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Wreath[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Wreath[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Wreath[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Wreath[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Wreath[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Wreath[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Wreath[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Wreath[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Wreath += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Wreath->Unlock();

	//����Ɉ�x�|���S����W�J����
	SetPos_Vtx_Wreath();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Wreath(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_WREATH; nCnt++)
	{
		if (g_pTexture_Wreath[nCnt] != NULL)
		{
			g_pTexture_Wreath[nCnt]->Release();
			g_pTexture_Wreath[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Wreath != NULL)
	{
		g_pVtxBuff_Wreath->Release();
		g_pVtxBuff_Wreath = NULL;
	}
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Wreath(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Wreath, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_WREATH; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Wreath[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//���_��W�J����֐�
//************************************************
void SetPos_Vtx_Wreath(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Wreath;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Wreath->Lock(0, 0, (void**)&pVtx_Wreath, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_WREATH; nCnt++)
	{
		pVtx_Wreath[0].pos = D3DXVECTOR3(POS_X_LEFT_WREATH + (POS_WOOD * nCnt), POS_Y_UP_WREATH + (POS_WOOD * nCnt), 0.0f);
		pVtx_Wreath[1].pos = D3DXVECTOR3(POS_X_RIGHT_WREATH - (POS_WOOD * nCnt), POS_Y_UP_WREATH + (POS_WOOD * nCnt), 0.0f);
		pVtx_Wreath[2].pos = D3DXVECTOR3(POS_X_LEFT_WREATH + (POS_WOOD * nCnt), POS_Y_DOWN_WREATH - (POS_WOOD * nCnt), 0.0f);
		pVtx_Wreath[3].pos = D3DXVECTOR3(POS_X_RIGHT_WREATH - (POS_WOOD * nCnt), POS_Y_DOWN_WREATH - (POS_WOOD * nCnt), 0.0f);

		pVtx_Wreath += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Wreath->Unlock();
}