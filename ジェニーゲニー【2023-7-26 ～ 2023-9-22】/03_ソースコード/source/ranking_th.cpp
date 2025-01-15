//************************************************
//
//���ʂ̂��[ranking_th.cpp]
//Author�F���c����
//
//************************************************
#include "ranking_th.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Ranking_TH[AMOUNT_TEXTURE_RANKING_TH] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Ranking_TH = NULL;	//���_�o�b�t�@�̃|�C���^
RANKING_TH g_aRanking_TH[AMOUNT_POLYGON_RANKING_TH];	//�J�[�\���p�|���S���̏����i�[

//************************************************
//�����������֐�
//************************************************
void Init_Ranking_TH(int nMode)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_1ST,
		&g_pTexture_Ranking_TH[0]);

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_2ND,
		&g_pTexture_Ranking_TH[1]);

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_3RD,
		&g_pTexture_Ranking_TH[2]);

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_4TH,
		&g_pTexture_Ranking_TH[3]);

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_5TH,
		&g_pTexture_Ranking_TH[4]);

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_YOURS,
		&g_pTexture_Ranking_TH[5]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_RANKING_TH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Ranking_TH,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Ranking_TH;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Ranking_TH->Lock(0, 0, (void**)&pVtx_Ranking_TH, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_TH; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Ranking_TH[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_TH[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_TH[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_TH[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Ranking_TH[0].rhw = 1.0f;
		pVtx_Ranking_TH[1].rhw = 1.0f;
		pVtx_Ranking_TH[2].rhw = 1.0f;
		pVtx_Ranking_TH[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Ranking_TH[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_TH[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_TH[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_TH[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Ranking_TH[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Ranking_TH[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Ranking_TH[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Ranking_TH[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Ranking_TH += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Ranking_TH->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_TH; nCnt++)
	{
		g_aRanking_TH[nCnt].nStyle = 0;
		g_aRanking_TH[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_TH[nCnt].fSpanX = 0.0f;
		g_aRanking_TH[nCnt].fSpanY = 0.0f;
		g_aRanking_TH[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_TH[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_TH[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aRanking_TH[nCnt].fLength = 0.0f;
		g_aRanking_TH[nCnt].fAngle = 0.0f;
		g_aRanking_TH[nCnt].fSPD_X = 0.0f;
		g_aRanking_TH[nCnt].colA = 0.0f;
	}

	//����̂ݒ��_��W�J
	Setinfo_Ranking_TH(nMode);
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Ranking_TH(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_RANKING_TH; nCnt++)
	{
		if (g_pTexture_Ranking_TH[nCnt] != NULL)
		{
			g_pTexture_Ranking_TH[nCnt]->Release();
			g_pTexture_Ranking_TH[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Ranking_TH != NULL)
	{
		g_pVtxBuff_Ranking_TH->Release();
		g_pVtxBuff_Ranking_TH = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Ranking_TH(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Ranking_TH;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Ranking_TH->Lock(0, 0, (void**)&pVtx_Ranking_TH, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_TH; nCnt++)
	{
		//�ړ��Ȃǔ��f
		pVtx_Ranking_TH[0].pos.x = g_aRanking_TH[nCnt].pos.x + sinf(g_aRanking_TH[nCnt].rot.z - (D3DX_PI - g_aRanking_TH[nCnt].fAngle)) * g_aRanking_TH[nCnt].fLength;
		pVtx_Ranking_TH[0].pos.y = g_aRanking_TH[nCnt].pos.y + cosf(g_aRanking_TH[nCnt].rot.z - (D3DX_PI - g_aRanking_TH[nCnt].fAngle)) * g_aRanking_TH[nCnt].fLength;
		pVtx_Ranking_TH[1].pos.x = g_aRanking_TH[nCnt].pos.x + sinf(g_aRanking_TH[nCnt].rot.z + (D3DX_PI - g_aRanking_TH[nCnt].fAngle)) * g_aRanking_TH[nCnt].fLength;
		pVtx_Ranking_TH[1].pos.y = g_aRanking_TH[nCnt].pos.y + cosf(g_aRanking_TH[nCnt].rot.z + (D3DX_PI - g_aRanking_TH[nCnt].fAngle)) * g_aRanking_TH[nCnt].fLength;
		pVtx_Ranking_TH[2].pos.x = g_aRanking_TH[nCnt].pos.x + sinf(g_aRanking_TH[nCnt].rot.z - g_aRanking_TH[nCnt].fAngle) * g_aRanking_TH[nCnt].fLength;
		pVtx_Ranking_TH[2].pos.y = g_aRanking_TH[nCnt].pos.y + cosf(g_aRanking_TH[nCnt].rot.z - g_aRanking_TH[nCnt].fAngle) * g_aRanking_TH[nCnt].fLength;
		pVtx_Ranking_TH[3].pos.x = g_aRanking_TH[nCnt].pos.x + sinf(g_aRanking_TH[nCnt].rot.z + g_aRanking_TH[nCnt].fAngle) * g_aRanking_TH[nCnt].fLength;
		pVtx_Ranking_TH[3].pos.y = g_aRanking_TH[nCnt].pos.y + cosf(g_aRanking_TH[nCnt].rot.z + g_aRanking_TH[nCnt].fAngle) * g_aRanking_TH[nCnt].fLength;

		pVtx_Ranking_TH[0].col = g_aRanking_TH[nCnt].col;
		pVtx_Ranking_TH[1].col = g_aRanking_TH[nCnt].col;
		pVtx_Ranking_TH[2].col = g_aRanking_TH[nCnt].col;
		pVtx_Ranking_TH[3].col = g_aRanking_TH[nCnt].col;

		pVtx_Ranking_TH += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Ranking_TH->Unlock();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Ranking_TH(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Ranking_TH, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_TH; nCnt++)
	{
		switch (g_aRanking_TH[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Ranking_TH[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_Ranking_TH[1]);

			break;

		case 2:

			pDevice->SetTexture(0, g_pTexture_Ranking_TH[2]);

			break;

		case 3:

			pDevice->SetTexture(0, g_pTexture_Ranking_TH[3]);

			break;

		case 4:

			pDevice->SetTexture(0, g_pTexture_Ranking_TH[4]);

			break;
		
		case 5:

			pDevice->SetTexture(0, g_pTexture_Ranking_TH[5]);

			break;
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Ranking_TH(int nMode)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_TH; nCnt++)
	{
		g_aRanking_TH[nCnt].nStyle = nCnt;

		switch (nCnt)
		{
		case 0:

			g_aRanking_TH[nCnt].pos = D3DXVECTOR3(570.0f, 200.0f, 0.0f);
			g_aRanking_TH[nCnt].fSpanX = 187.5f;
			g_aRanking_TH[nCnt].fSpanY = 112.5f;

			break;

		case 1:

			g_aRanking_TH[nCnt].pos = D3DXVECTOR3(230.0f, 500.0f, 0.0f);
			g_aRanking_TH[nCnt].fSpanX = 125.0f;
			g_aRanking_TH[nCnt].fSpanY = 75.0f;

			break;

		case 2:

			g_aRanking_TH[nCnt].pos = D3DXVECTOR3(1230.0f, 500.0f, 0.0f);
			g_aRanking_TH[nCnt].fSpanX = 125.0f;
			g_aRanking_TH[nCnt].fSpanY = 75.0f;

			break;

		case 3:

			g_aRanking_TH[nCnt].pos = D3DXVECTOR3(230.0f, 720.0f, 0.0f);
			g_aRanking_TH[nCnt].fSpanX = 100.0f;
			g_aRanking_TH[nCnt].fSpanY = 50.0f;

			break;

		case 4:

			g_aRanking_TH[nCnt].pos = D3DXVECTOR3(1230.0f, 720.0f, 0.0f);
			g_aRanking_TH[nCnt].fSpanX = 100.0f;
			g_aRanking_TH[nCnt].fSpanY = 50.0f;

			break;

		case 5:

			if (nMode == 1)
			{
				g_aRanking_TH[nCnt].pos = D3DXVECTOR3(350.0f, 925.0f, 0.0f);
				g_aRanking_TH[nCnt].fSpanX = 250.0f;
				g_aRanking_TH[nCnt].fSpanY = 50.0f;
			}

			break;
		}

		g_aRanking_TH[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_TH[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_TH[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRanking_TH[nCnt].fLength = sqrtf((g_aRanking_TH[nCnt].fSpanX * g_aRanking_TH[nCnt].fSpanX) + (g_aRanking_TH[nCnt].fSpanY * g_aRanking_TH[nCnt].fSpanY));
		g_aRanking_TH[nCnt].fAngle = atan2f(g_aRanking_TH[nCnt].fSpanX * 2.0f, g_aRanking_TH[nCnt].fSpanY * 2.0f);
		g_aRanking_TH[nCnt].fSPD_X = 1.0f;
		g_aRanking_TH[nCnt].colA = 0.01f;
	}
}