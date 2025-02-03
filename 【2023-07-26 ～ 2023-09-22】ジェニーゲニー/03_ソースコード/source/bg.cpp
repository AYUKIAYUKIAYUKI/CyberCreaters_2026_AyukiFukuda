//************************************************
//
//�w�i����[bg.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "bg.h"
#include "timer.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_BG[AMOUNT_TEXTURE_BG] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_BG = NULL;	//���_�o�b�t�@�̃|�C���^
BG g_aBG[AMOUNT_POLYGON_BG];	//�w�i�p�\����

//************************************************
//�|���S�������������֐�
//************************************************
void Init_BG(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_DEMO_BG,
		&g_pTexture_BG[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_BG,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_BG;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_BG->Lock(0, 0, (void**)&pVtx_BG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_BG[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_BG[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_BG[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_BG[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_BG[0].rhw = 1.0f;
		pVtx_BG[1].rhw = 1.0f;
		pVtx_BG[2].rhw = 1.0f;
		pVtx_BG[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_BG[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_BG[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_BG[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_BG[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_BG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_BG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_BG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_BG[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_BG += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_BG->Unlock();

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		g_aBG[nCnt].texL = 0.0f;
		g_aBG[nCnt].texR = 1.0f;
		g_aBG[nCnt].moveSPD = 0.002f;
	}

	//����Ɉ�x�|���S����W�J����
	SetPos_Vtx_BG();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_BG(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_BG; nCnt++)
	{
		if (g_pTexture_BG[nCnt] != NULL)
		{
			g_pTexture_BG[nCnt]->Release();
			g_pTexture_BG[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_BG != NULL)
	{
		g_pVtxBuff_BG->Release();
		g_pVtxBuff_BG = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_BG(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_BG;

	//�^�C�}�[���̃|�C���^
	bool* pInversion;
	bool* pReInversion;

	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_BG->Lock(0, 0, (void**)&pVtx_BG, 0);

	//�e�N�X�`�������������̑����ŗ���
	g_aBG[0].texL += g_aBG[0].moveSPD;
	g_aBG[0].texR += g_aBG[0].moveSPD;

	if (*pInversion == true &&
		g_aBG[0].moveSPD >= -0.0025f &&
		*pReInversion == false)
	{
		g_aBG[0].moveSPD -= 0.00005f;
	}
	if (*pInversion == true &&
		g_aBG[0].moveSPD <= 0.0035f &&
		*pReInversion == true)
	{
		g_aBG[0].moveSPD += 0.000025f;
	}

	//���f
	pVtx_BG[0].tex = D3DXVECTOR2(g_aBG[0].texL, 0.0f);
	pVtx_BG[1].tex = D3DXVECTOR2(g_aBG[0].texR, 0.0f);
	pVtx_BG[2].tex = D3DXVECTOR2(g_aBG[0].texL, 1.0f);
	pVtx_BG[3].tex = D3DXVECTOR2(g_aBG[0].texR, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_BG->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_BG(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_BG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_BG; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_BG[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//���_��W�J����֐�
//************************************************
void SetPos_Vtx_BG(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_BG;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_BG->Lock(0, 0, (void**)&pVtx_BG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		pVtx_BG[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_BG[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx_BG[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx_BG[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		pVtx_BG += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_BG->Unlock();
}