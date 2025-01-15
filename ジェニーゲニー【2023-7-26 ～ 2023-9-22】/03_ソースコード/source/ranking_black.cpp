//************************************************
//
//�����L���O�ɍ��_���o��[ranking_black.cpp]
//Author�F���c����
//
//************************************************
#include "ranking_black.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Ranking_Black[AMOUNT_TEXTURE_RANKING_BLACK] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Ranking_Black = NULL;	//���_�o�b�t�@�̃|�C���^
RANKING_BLACK g_aRanking_Black[AMOUNT_POLYGON_RANKING_BLACK];	//�J�[�\���p�|���S���̏����i�[

//************************************************
//�����������֐�
//************************************************
void Init_Ranking_Black(int nMode)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_BLACK,
		&g_pTexture_Ranking_Black[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_RANKING_BLACK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Ranking_Black,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Ranking_Black;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Ranking_Black->Lock(0, 0, (void**)&pVtx_Ranking_Black, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BLACK; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Ranking_Black[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Black[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Black[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Black[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Ranking_Black[0].rhw = 1.0f;
		pVtx_Ranking_Black[1].rhw = 1.0f;
		pVtx_Ranking_Black[2].rhw = 1.0f;
		pVtx_Ranking_Black[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Ranking_Black[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Black[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Black[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Black[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Ranking_Black[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Ranking_Black[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Ranking_Black[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Ranking_Black[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Ranking_Black += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Ranking_Black->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BLACK; nCnt++)
	{
		g_aRanking_Black[nCnt].nStyle = 0;
		g_aRanking_Black[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Black[nCnt].fSpanX = 0.0f;
		g_aRanking_Black[nCnt].fSpanY = 0.0f;
		g_aRanking_Black[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Black[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Black[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aRanking_Black[nCnt].fLength = 0.0f;
		g_aRanking_Black[nCnt].fAngle = 0.0f;
		g_aRanking_Black[nCnt].fSPD_X = 0.0f;
		g_aRanking_Black[nCnt].colA = 0.0f;
	}

	//����̂ݒ��_��W�J
	Setinfo_Ranking_Black(nMode);
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Ranking_Black(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_RANKING_BLACK; nCnt++)
	{
		if (g_pTexture_Ranking_Black[nCnt] != NULL)
		{
			g_pTexture_Ranking_Black[nCnt]->Release();
			g_pTexture_Ranking_Black[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Ranking_Black != NULL)
	{
		g_pVtxBuff_Ranking_Black->Release();
		g_pVtxBuff_Ranking_Black = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Ranking_Black(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Ranking_Black;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Ranking_Black->Lock(0, 0, (void**)&pVtx_Ranking_Black, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BLACK; nCnt++)
	{
		//�ړ��Ȃǔ��f
		pVtx_Ranking_Black[0].pos.x = g_aRanking_Black[nCnt].pos.x + sinf(g_aRanking_Black[nCnt].rot.z - (D3DX_PI - g_aRanking_Black[nCnt].fAngle)) * g_aRanking_Black[nCnt].fLength;
		pVtx_Ranking_Black[0].pos.y = g_aRanking_Black[nCnt].pos.y + cosf(g_aRanking_Black[nCnt].rot.z - (D3DX_PI - g_aRanking_Black[nCnt].fAngle)) * g_aRanking_Black[nCnt].fLength;
		pVtx_Ranking_Black[1].pos.x = g_aRanking_Black[nCnt].pos.x + sinf(g_aRanking_Black[nCnt].rot.z + (D3DX_PI - g_aRanking_Black[nCnt].fAngle)) * g_aRanking_Black[nCnt].fLength + 30.0f;
		pVtx_Ranking_Black[1].pos.y = g_aRanking_Black[nCnt].pos.y + cosf(g_aRanking_Black[nCnt].rot.z + (D3DX_PI - g_aRanking_Black[nCnt].fAngle)) * g_aRanking_Black[nCnt].fLength;
		pVtx_Ranking_Black[2].pos.x = g_aRanking_Black[nCnt].pos.x + sinf(g_aRanking_Black[nCnt].rot.z - g_aRanking_Black[nCnt].fAngle) * g_aRanking_Black[nCnt].fLength - 30.0f;
		pVtx_Ranking_Black[2].pos.y = g_aRanking_Black[nCnt].pos.y + cosf(g_aRanking_Black[nCnt].rot.z - g_aRanking_Black[nCnt].fAngle) * g_aRanking_Black[nCnt].fLength;
		pVtx_Ranking_Black[3].pos.x = g_aRanking_Black[nCnt].pos.x + sinf(g_aRanking_Black[nCnt].rot.z + g_aRanking_Black[nCnt].fAngle) * g_aRanking_Black[nCnt].fLength;
		pVtx_Ranking_Black[3].pos.y = g_aRanking_Black[nCnt].pos.y + cosf(g_aRanking_Black[nCnt].rot.z + g_aRanking_Black[nCnt].fAngle) * g_aRanking_Black[nCnt].fLength;

		pVtx_Ranking_Black[0].col = g_aRanking_Black[nCnt].col;
		pVtx_Ranking_Black[1].col = g_aRanking_Black[nCnt].col;
		pVtx_Ranking_Black[2].col = g_aRanking_Black[nCnt].col;
		pVtx_Ranking_Black[3].col = g_aRanking_Black[nCnt].col;

		pVtx_Ranking_Black += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Ranking_Black->Unlock();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Ranking_Black(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Ranking_Black, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BLACK; nCnt++)
	{
		if (g_aRanking_Black[nCnt].nStyle == 0)
		{
			pDevice->SetTexture(0, g_pTexture_Ranking_Black[0]);
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Ranking_Black(int nMode)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BLACK; nCnt++)
	{
		g_aRanking_Black[nCnt].nStyle = 0;

		switch (nCnt)
		{
		case 0:

			g_aRanking_Black[nCnt].pos = D3DXVECTOR3(990.0f, 200.0f, 0.0f);
			g_aRanking_Black[nCnt].fSpanX = 650.0f;
			g_aRanking_Black[nCnt].fSpanY = 150.0f;

			break;

		case 1:

			g_aRanking_Black[nCnt].pos = D3DXVECTOR3(495.0f, 500.0f, 0.0f);
			g_aRanking_Black[nCnt].fSpanX = 435.0f;
			g_aRanking_Black[nCnt].fSpanY = 100.0f;

			break;

		case 2:

			g_aRanking_Black[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH - 495.0f, 500.0f, 0.0f);
			g_aRanking_Black[nCnt].fSpanX = 435.0f;
			g_aRanking_Black[nCnt].fSpanY = 100.0f;

			break;

		case 3:

			g_aRanking_Black[nCnt].pos = D3DXVECTOR3(495.0f, 720.0f, 0.0f);
			g_aRanking_Black[nCnt].fSpanX = 435.0f;
			g_aRanking_Black[nCnt].fSpanY = 75.0f;

			break;

		case 4:

			g_aRanking_Black[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH - 495.0f, 720.0f, 0.0f);
			g_aRanking_Black[nCnt].fSpanX = 435.0f;
			g_aRanking_Black[nCnt].fSpanY = 75.0f;

			break;

		case 5:

			if (nMode == 1)
			{
				g_aRanking_Black[nCnt].pos = D3DXVECTOR3(630.0f, 925.0f, 0.0f);
				g_aRanking_Black[nCnt].fSpanX = 560.0f;
				g_aRanking_Black[nCnt].fSpanY = 75.0f;
			}

			break;
		}

		g_aRanking_Black[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Black[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Black[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		g_aRanking_Black[nCnt].fLength = sqrtf((g_aRanking_Black[nCnt].fSpanX * g_aRanking_Black[nCnt].fSpanX) + (g_aRanking_Black[nCnt].fSpanY * g_aRanking_Black[nCnt].fSpanY));
		g_aRanking_Black[nCnt].fAngle = atan2f(g_aRanking_Black[nCnt].fSpanX * 2.0f, g_aRanking_Black[nCnt].fSpanY * 2.0f);
		g_aRanking_Black[nCnt].fSPD_X = 1.0f;
		g_aRanking_Black[nCnt].colA = 0.01f;
	}
}