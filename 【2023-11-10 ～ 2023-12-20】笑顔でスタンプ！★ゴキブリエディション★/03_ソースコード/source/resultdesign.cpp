//************************************************
//
//���U���g�f�U�C��[resultdesign.cpp]
//Author�F���c����
//
//************************************************
#include "resultdesign.h"

#include "fade.h"
#include "input.h"

typedef enum
{
	TexLogo = 0,
	TexMax
}TexType;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResultDesign[TexMax] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultDesign = NULL;	//���_�o�b�t�@�̃|�C���^
ResultDesign g_aResultDesign[TexMax];	//���

//************************************************
//���U���g�f�U�C������
//************************************************
void InitResultDesign(void)
{
	//�\���̂̏��̏������Q
	for (int i = 0; i < TexMax; i++)
	{
		g_aResultDesign[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResultDesign[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResultDesign[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResultDesign[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aResultDesign[i].sizeX = 0.0f;
		g_aResultDesign[i].sizeY = 0.0f;
		g_aResultDesign[i].F = 1.0f;	//�ėp
	}

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	const char* pFileName[TexMax] =
	{
		"data\\texture\\roachrank.png",
	};

	for (int i = 0; i < TexMax; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureResultDesign[i]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * TexMax,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultDesign,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffResultDesign->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffResultDesign->Unlock();

	//����t�^
	SetInfoResultDesign();

	//�W�J
	SetSizeResultDesign();
}

//************************************************
//���U���g�f�U�C���I�������֐�
//************************************************
void UninitResultDesign(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < TexMax; i++)
	{
		if (g_pTextureResultDesign[i] != NULL)
		{
			g_pTextureResultDesign[i]->Release();
			g_pTextureResultDesign[i] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResultDesign != NULL)
	{
		g_pVtxBuffResultDesign->Release();
		g_pVtxBuffResultDesign = NULL;
	}
}

//************************************************
//���U���g�f�U�C���X�V
//************************************************
void UpdateResultDesign(void)
{
	//�W�J
	SetSizeResultDesign();
}

//************************************************
//���U���g�f�U�C���W�J
//************************************************
void SetSizeResultDesign(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffResultDesign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		//���_���W�̏����ݒ�
		pVtx[0].pos =
		{
			g_aResultDesign[i].pos.x - g_aResultDesign[i].sizeX,
			g_aResultDesign[i].pos.y - g_aResultDesign[i].sizeY,
			0.0f
		};

		pVtx[1].pos =
		{
			g_aResultDesign[i].pos.x + g_aResultDesign[i].sizeX,
			g_aResultDesign[i].pos.y - g_aResultDesign[i].sizeY,
			0.0f
		};

		pVtx[2].pos =
		{
			g_aResultDesign[i].pos.x - g_aResultDesign[i].sizeX,
			g_aResultDesign[i].pos.y + g_aResultDesign[i].sizeY,
			0.0f
		};

		pVtx[3].pos =
		{
			g_aResultDesign[i].pos.x + g_aResultDesign[i].sizeX,
			g_aResultDesign[i].pos.y + g_aResultDesign[i].sizeY,
			0.0f
		};
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultDesign->Unlock();
}

//************************************************
//���U���g�f�U�C���`��
//************************************************
void DrawResultDesign(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultDesign, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TexMax; i++)
	{
		pDevice->SetTexture(0, g_pTextureResultDesign[i]);

		//���U���g�f�U�C���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfoResultDesign(void)
{
	for (int i = 0; i < TexMax; i++)
	{
		if (i == TexLogo)
		{
			g_aResultDesign[i].pos = D3DXVECTOR3((float)SCREEN_HALFWIDTH, (float)SCREEN_HALFHEIGHT, 0.0f);
			g_aResultDesign[i].sizeX = (float)SCREEN_HALFWIDTH;
			g_aResultDesign[i].sizeY = (float)SCREEN_HALFHEIGHT;
		}
		g_aResultDesign[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResultDesign[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResultDesign[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aResultDesign[i].F = 1.0f;	//�ėp
	}
}