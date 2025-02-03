//************************************************
//
//�Q�[�W[gauge.cpp]
//Author�F���c����
//
//************************************************
#include "gauge.h"

#include "debugproc.h"
#include "fade.h"
#include "input.h"

#include "player.h"

//�Q�[�W�p
typedef enum
{
	TexGauge00 = 0,
	TexGaugeFrame00,
	TexRoachJet,
	TexGauge01,
	TexGaugeFrame01,
	TexEnegy,
	TexMax,
}TexType;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureGauge[TexMax] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;	//���_�o�b�t�@�̃|�C���^
Gauge g_aGauge[TexMax];	//���

//************************************************
//�Q�[�W����
//************************************************
void InitGauge(void)
{
	//�\���̂̏��̏������Q
	for (int i = 0; i < TexMax; i++)
	{
		g_aGauge[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aGauge[i].sizeX = 0.0f;
		g_aGauge[i].sizeY = 0.0f;
		g_aGauge[i].F = 1.0f;	//�ėp
	}

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	const char* pFileName[TexMax] =
	{
		"data\\texture\\gauge_00.png",
		"data\\texture\\guage_frame.png",
		"data\\texture\\roach_JET.png",
		"data\\texture\\gauge_01.png",
		"data\\texture\\guage_frame.png",
		"data\\texture\\enegy.png",
	};

	for (int i = 0; i < TexMax; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureGauge[i]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * TexMax,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGauge,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++)
	{
		//���_���W�̏����ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGauge->Unlock();

	//����t�^
	SetInfoGauge();

	//�W�J
	SetSizeGauge();
}

//************************************************
//�Q�[�W�I�������֐�
//************************************************
void UninitGauge(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < TexMax; i++)
	{
		if (g_pTextureGauge[i] != NULL)
		{
			g_pTextureGauge[i]->Release();
			g_pTextureGauge[i] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}
}

//************************************************
//�Q�[�W�X�V
//************************************************
void UpdateGauge(void)
{
	//�W�J
	SetSizeGauge();

	//�F�ύX
	//UpdateColGauge();
}

//************************************************
//�Q�[�W�W�J
//************************************************
void SetSizeGauge(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	Player* pPlayer = GetInfoPlayer();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos =
		{
			g_aGauge[i].pos.x - g_aGauge[i].sizeX,
			g_aGauge[i].pos.y - g_aGauge[i].sizeY,
			0.0f
		};

		pVtx[1].pos =
		{
			g_aGauge[i].pos.x + g_aGauge[i].sizeX,
			g_aGauge[i].pos.y - g_aGauge[i].sizeY,
			0.0f
		};

		pVtx[2].pos =
		{
			g_aGauge[i].pos.x - g_aGauge[i].sizeX,
			g_aGauge[i].pos.y + g_aGauge[i].sizeY,
			0.0f
		};

		pVtx[3].pos =
		{
			g_aGauge[i].pos.x + g_aGauge[i].sizeX,
			g_aGauge[i].pos.y + g_aGauge[i].sizeY,
			0.0f
		};
	
		if (i == TexGauge00)
		{
			//�L���p�ʓ�����̃Q�[�W���ʂ��Z�o(�N�\)
			if (pPlayer->nCapacity > AMOUNT_CAPACITY)
			{
				pPlayer->nCapacity = AMOUNT_CAPACITY;
			}

			float fNowCapacityPolygon = (pPlayer->nCapacity - AMOUNT_CAPACITY) * ((g_aGauge[i].sizeX * 2.0f) / AMOUNT_CAPACITY);	//�|���S���̒������L���p�̗ʁ��W��
			float fNowCapacityTexture = (pPlayer->nCapacity - AMOUNT_CAPACITY) * (1.0f / AMOUNT_CAPACITY);	//�e�N�X�`���̒������L���p�̗ʁ��W��

			//�|���S���L�k
			pVtx[0].pos.x = g_aGauge[i].pos.x - g_aGauge[i].sizeX;
			pVtx[1].pos.x = g_aGauge[i].pos.x + g_aGauge[i].sizeX + fNowCapacityPolygon;
			pVtx[2].pos.x = g_aGauge[i].pos.x - g_aGauge[i].sizeX;
			pVtx[3].pos.x = g_aGauge[i].pos.x + g_aGauge[i].sizeX + fNowCapacityPolygon;

			//�e�N�X�`���L�k
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f + fNowCapacityTexture, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f + fNowCapacityTexture, 1.0f);
		}

		if (i == TexGauge01)
		{
			//�L���p�ʓ�����̃Q�[�W���ʂ��Z�o(�N�\)
			if (pPlayer->nEnegy > AMOUNT_ENEGY)
			{
				pPlayer->nEnegy = AMOUNT_ENEGY;
			}

			float fNowCapacityPolygon = (pPlayer->nEnegy - AMOUNT_ENEGY) * ((g_aGauge[i].sizeX * 2.0f) / AMOUNT_ENEGY);	//�|���S���̒������L���p�̗ʁ��W��
			float fNowCapacityTexture = (pPlayer->nEnegy - AMOUNT_ENEGY) * (1.0f / AMOUNT_ENEGY);	//�e�N�X�`���̒������L���p�̗ʁ��W��

			//�|���S���L�k
			pVtx[0].pos.x = g_aGauge[i].pos.x - g_aGauge[i].sizeX;
			pVtx[1].pos.x = g_aGauge[i].pos.x + g_aGauge[i].sizeX + fNowCapacityPolygon;
			pVtx[2].pos.x = g_aGauge[i].pos.x - g_aGauge[i].sizeX;
			pVtx[3].pos.x = g_aGauge[i].pos.x + g_aGauge[i].sizeX + fNowCapacityPolygon;

			//�e�N�X�`���L�k
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f + fNowCapacityTexture, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f + fNowCapacityTexture, 1.0f);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGauge->Unlock();
}

//************************************************
//�Q�[�W�F�ύX
//************************************************
void UpdateColGauge(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		//���ɂȂ�
		pVtx[0].col = g_aGauge[i].col;
		pVtx[1].col = g_aGauge[i].col;
		pVtx[2].col = g_aGauge[i].col;
		pVtx[3].col = g_aGauge[i].col;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGauge->Unlock();
}

//************************************************
//�Q�[�W�`��
//************************************************
void DrawGauge(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TexMax; i++)
	{
		pDevice->SetTexture(0, g_pTextureGauge[i]);

		//�Q�[�W�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfoGauge(void)
{
	for (int i = 0; i < TexMax; i++)
	{
		g_aGauge[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aGauge[i].F = 1.0f;	//�ėp

		if (i == TexGauge00 || i == TexGaugeFrame00)
		{
			g_aGauge[i].pos = D3DXVECTOR3(1100.0f, 75.0f, 0.0f);
			g_aGauge[i].sizeX = 250.0f;
			g_aGauge[i].sizeY = 30.0f;
		}
		else if (i == TexRoachJet)
		{
			g_aGauge[i].pos = D3DXVECTOR3(g_aGauge[TexGauge00].pos.x - g_aGauge[TexGauge00].sizeX, g_aGauge[TexGauge00].pos.y - 5.0f, 0.0f);
			g_aGauge[i].sizeX = 18.0f;
			g_aGauge[i].sizeY = 56.25f;
		}
		else if (i == TexGauge01 || i == TexGaugeFrame01)
		{
			g_aGauge[i].pos = D3DXVECTOR3(1700.0f, 75.0f, 0.0f);
			g_aGauge[i].sizeX = 250.0f;
			g_aGauge[i].sizeY = 30.0f;
		}
		else if (i == TexEnegy)
		{
			g_aGauge[i].pos = D3DXVECTOR3(g_aGauge[TexGauge01].pos.x - g_aGauge[TexGauge01].sizeX - 15.0f, g_aGauge[TexGauge01].pos.y - 5.0f, 0.0f);
			g_aGauge[i].sizeX = 50.0f;
			g_aGauge[i].sizeY = 50.0f;
		}
	}
}
