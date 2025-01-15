//************************************************
//
//���j���[�̃��[�h�I������[select_mode.cpp]
//Author�F���c����
//
//************************************************
#include "cursorh.h"
#include "select_mode.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Select_Mode[AMOUNT_TEXTURE_SELECT_MODE] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Select_Mode = NULL;	//���_�o�b�t�@�̃|�C���^
SELECT_MODE g_aSelect_Mode[AMOUNT_POLYGON_SELECT_MODE];	//���j���[�p�|���S���̏����i�[

//************************************************
//�����������֐�
//************************************************
void Init_Select_Mode(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MODE_GAME,
		&g_pTexture_Select_Mode[0]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MODE_RANK,
		&g_pTexture_Select_Mode[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_SELECT_MODE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Select_Mode,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Select_Mode;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Select_Mode->Lock(0, 0, (void**)&pVtx_Select_Mode, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SELECT_MODE; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Select_Mode[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Select_Mode[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Select_Mode[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Select_Mode[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Select_Mode[0].rhw = 1.0f;
		pVtx_Select_Mode[1].rhw = 1.0f;
		pVtx_Select_Mode[2].rhw = 1.0f;
		pVtx_Select_Mode[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Select_Mode[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Select_Mode[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Select_Mode[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Select_Mode[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Select_Mode[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Select_Mode[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Select_Mode[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Select_Mode[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Select_Mode += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Select_Mode->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SELECT_MODE; nCnt++)
	{
		g_aSelect_Mode[nCnt].nStyle = 0;
		g_aSelect_Mode[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSelect_Mode[nCnt].fSpanX = 0.0f;
		g_aSelect_Mode[nCnt].fSpanY = 0.0f;
		g_aSelect_Mode[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSelect_Mode[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSelect_Mode[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//����̂ݒ��_��W�J
	Setinfo_Select_Mode();
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Select_Mode(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_SELECT_MODE; nCnt++)
	{
		if (g_pTexture_Select_Mode[nCnt] != NULL)
		{
			g_pTexture_Select_Mode[nCnt]->Release();
			g_pTexture_Select_Mode[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Select_Mode != NULL)
	{
		g_pVtxBuff_Select_Mode->Release();
		g_pVtxBuff_Select_Mode = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Select_Mode(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Select_Mode;

	//�I��ł���̂ւ̃|�C���^
	int* pChoose;

	pChoose = Getinfo_Choose();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Select_Mode->Lock(0, 0, (void**)&pVtx_Select_Mode, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SELECT_MODE; nCnt++)
	{
		//�I��ł���̂ɉ����ĐF�ύX
		if (*pChoose == 0)
		{
			g_aSelect_Mode[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_aSelect_Mode[1].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		}
		else
		{
			g_aSelect_Mode[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			g_aSelect_Mode[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//�ړ��A��]�𔽉f
		pVtx_Select_Mode[0].pos.x = g_aSelect_Mode[nCnt].pos.x - g_aSelect_Mode[nCnt].fSpanX;
		pVtx_Select_Mode[0].pos.y = g_aSelect_Mode[nCnt].pos.y - g_aSelect_Mode[nCnt].fSpanY;
		pVtx_Select_Mode[1].pos.x = g_aSelect_Mode[nCnt].pos.x + g_aSelect_Mode[nCnt].fSpanX;
		pVtx_Select_Mode[1].pos.y = g_aSelect_Mode[nCnt].pos.y - g_aSelect_Mode[nCnt].fSpanY;
		pVtx_Select_Mode[2].pos.x = g_aSelect_Mode[nCnt].pos.x - g_aSelect_Mode[nCnt].fSpanX;
		pVtx_Select_Mode[2].pos.y = g_aSelect_Mode[nCnt].pos.y + g_aSelect_Mode[nCnt].fSpanY;
		pVtx_Select_Mode[3].pos.x = g_aSelect_Mode[nCnt].pos.x + g_aSelect_Mode[nCnt].fSpanX;
		pVtx_Select_Mode[3].pos.y = g_aSelect_Mode[nCnt].pos.y + g_aSelect_Mode[nCnt].fSpanY;

		pVtx_Select_Mode[0].col = g_aSelect_Mode[nCnt].col;
		pVtx_Select_Mode[1].col = g_aSelect_Mode[nCnt].col;
		pVtx_Select_Mode[2].col = g_aSelect_Mode[nCnt].col;
		pVtx_Select_Mode[3].col = g_aSelect_Mode[nCnt].col;

		pVtx_Select_Mode += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Select_Mode->Unlock();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Select_Mode(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Select_Mode, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SELECT_MODE; nCnt++)
	{
		switch (g_aSelect_Mode[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Select_Mode[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_Select_Mode[1]);

			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Select_Mode(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SELECT_MODE; nCnt++)
	{
		g_aSelect_Mode[nCnt].nStyle = nCnt;

		switch (g_aSelect_Mode[nCnt].nStyle)
		{
		case 0:

			g_aSelect_Mode[nCnt].pos = D3DXVECTOR3(570.0f, 650.0f, 0.0f);
			g_aSelect_Mode[nCnt].fSpanX = 350.0f;
			g_aSelect_Mode[nCnt].fSpanY = 250.0f;
			g_aSelect_Mode[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aSelect_Mode[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aSelect_Mode[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;

		case 1:

			g_aSelect_Mode[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH - 570.0f, 650.0f, 0.0f);
			g_aSelect_Mode[nCnt].fSpanX = 350.0f;
			g_aSelect_Mode[nCnt].fSpanY = 250.0f;
			g_aSelect_Mode[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aSelect_Mode[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aSelect_Mode[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;
		}
	}
}