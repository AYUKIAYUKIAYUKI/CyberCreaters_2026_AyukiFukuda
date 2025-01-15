//************************************************
//
//�|�[�Y��ʃ��[�h�I��[pause_select.cpp]
//Author�F���c����
//
//************************************************
#include "pause_cursor.h"
#include "pause_select.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Pause_Select[AMOUNT_TEXTURE_PAUSE_SELECT] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Pause_Select = NULL;	//���_�o�b�t�@�̃|�C���^
PAUSE_SELECT g_aPause_Select[AMOUNT_POLYGON_PAUSE_SELECT];	//�|���S���̏����i�[

//************************************************
//�����������֐�
//************************************************
void Init_Pause_Select(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PAUSE_CONTINUE,
		&g_pTexture_Pause_Select[0]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PAUSE_RETRY,
		&g_pTexture_Pause_Select[1]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PAUSE_MENU,
		&g_pTexture_Pause_Select[2]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PAUSE_TITLE,
		&g_pTexture_Pause_Select[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_PAUSE_SELECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Pause_Select,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Pause_Select;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Pause_Select->Lock(0, 0, (void**)&pVtx_Pause_Select, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_SELECT; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Pause_Select[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Pause_Select[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Pause_Select[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Pause_Select[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Pause_Select[0].rhw = 1.0f;
		pVtx_Pause_Select[1].rhw = 1.0f;
		pVtx_Pause_Select[2].rhw = 1.0f;
		pVtx_Pause_Select[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Pause_Select[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Pause_Select[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Pause_Select[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Pause_Select[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Pause_Select[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Pause_Select[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Pause_Select[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Pause_Select[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Pause_Select += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Pause_Select->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_SELECT; nCnt++)
	{
		g_aPause_Select[nCnt].nStyle = 0;
		g_aPause_Select[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Select[nCnt].fSpanX = 0.0f;
		g_aPause_Select[nCnt].fSpanY = 0.0f;
		g_aPause_Select[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Select[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Select[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aPause_Select[nCnt].colA = 0.0f;
	}

	//����̂ݒ��_��W�J
	Setinfo_Pause_Select();
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Pause_Select(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_PAUSE_SELECT; nCnt++)
	{
		if (g_pTexture_Pause_Select[nCnt] != NULL)
		{
			g_pTexture_Pause_Select[nCnt]->Release();
			g_pTexture_Pause_Select[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Pause_Select != NULL)
	{
		g_pVtxBuff_Pause_Select->Release();
		g_pVtxBuff_Pause_Select = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Pause_Select(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Pause_Select;

	//�I��ł���̂ւ̃|�C���^
	int* pChoose_Pause;
	pChoose_Pause = Getinfo_Choose_Pause();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Pause_Select->Lock(0, 0, (void**)&pVtx_Pause_Select, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_SELECT; nCnt++)
	{
		if (g_aPause_Select[nCnt].col.a < 1.0f)
		{
			g_aPause_Select[nCnt].colA *= 1.2f;
		}
		else
		{
			g_aPause_Select[nCnt].colA = 1.0f;
		}

		//�I��ł���̂ɉ����ĐF�ύX
		switch(*pChoose_Pause)
		{
		case 0:

			g_aPause_Select[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aPause_Select[0].colA);
			g_aPause_Select[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[1].colA);
			g_aPause_Select[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[2].colA);
			g_aPause_Select[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[3].colA);

			break;

		case 1:

			g_aPause_Select[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[0].colA);
			g_aPause_Select[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aPause_Select[1].colA);
			g_aPause_Select[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[2].colA);
			g_aPause_Select[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[3].colA);

			break;

		case 2:

			g_aPause_Select[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[0].colA);
			g_aPause_Select[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[1].colA);
			g_aPause_Select[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aPause_Select[2].colA);
			g_aPause_Select[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[3].colA);

			break;

		case 3:

			g_aPause_Select[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[0].colA);
			g_aPause_Select[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[1].colA);
			g_aPause_Select[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aPause_Select[2].colA);
			g_aPause_Select[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aPause_Select[3].colA);

			break;
		}

		//�ړ��A��]�𔽉f
		pVtx_Pause_Select[0].pos.x = g_aPause_Select[nCnt].pos.x - g_aPause_Select[nCnt].fSpanX;
		pVtx_Pause_Select[0].pos.y = g_aPause_Select[nCnt].pos.y - g_aPause_Select[nCnt].fSpanY;
		pVtx_Pause_Select[1].pos.x = g_aPause_Select[nCnt].pos.x + g_aPause_Select[nCnt].fSpanX;
		pVtx_Pause_Select[1].pos.y = g_aPause_Select[nCnt].pos.y - g_aPause_Select[nCnt].fSpanY;
		pVtx_Pause_Select[2].pos.x = g_aPause_Select[nCnt].pos.x - g_aPause_Select[nCnt].fSpanX;
		pVtx_Pause_Select[2].pos.y = g_aPause_Select[nCnt].pos.y + g_aPause_Select[nCnt].fSpanY;
		pVtx_Pause_Select[3].pos.x = g_aPause_Select[nCnt].pos.x + g_aPause_Select[nCnt].fSpanX;
		pVtx_Pause_Select[3].pos.y = g_aPause_Select[nCnt].pos.y + g_aPause_Select[nCnt].fSpanY;

		pVtx_Pause_Select[0].col = g_aPause_Select[nCnt].col;
		pVtx_Pause_Select[1].col = g_aPause_Select[nCnt].col;
		pVtx_Pause_Select[2].col = g_aPause_Select[nCnt].col;
		pVtx_Pause_Select[3].col = g_aPause_Select[nCnt].col;

		pVtx_Pause_Select += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Pause_Select->Unlock();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Pause_Select(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Pause_Select, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_SELECT; nCnt++)
	{
		switch (g_aPause_Select[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Pause_Select[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_Pause_Select[1]);

			break;

		case 2:

			pDevice->SetTexture(0, g_pTexture_Pause_Select[2]);

			break;

		case 3:

			pDevice->SetTexture(0, g_pTexture_Pause_Select[3]);

			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Pause_Select(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_SELECT; nCnt++)
	{
		g_aPause_Select[nCnt].nStyle = nCnt;

		switch (g_aPause_Select[nCnt].nStyle)
		{
		case 0:

			g_aPause_Select[nCnt].pos = D3DXVECTOR3(700.0f, 450.0f, 0.0f);
			g_aPause_Select[nCnt].fSpanX = 300.0f;
			g_aPause_Select[nCnt].fSpanY = 50.0f;

			break;

		case 1:

			g_aPause_Select[nCnt].pos = D3DXVECTOR3(1280.0f, 450.0f, 0.0f);
			g_aPause_Select[nCnt].fSpanX = 150.0f;
			g_aPause_Select[nCnt].fSpanY = 50.0f;

			break;

		case 2:

			g_aPause_Select[nCnt].pos = D3DXVECTOR3(700.0f, 650.0f, 0.0f);
			g_aPause_Select[nCnt].fSpanX = 200.0f;
			g_aPause_Select[nCnt].fSpanY = 50.0f;

			break;

		case 3:

			g_aPause_Select[nCnt].pos = D3DXVECTOR3(1280.0f, 650.0f, 0.0f);
			g_aPause_Select[nCnt].fSpanX = 200.0f;
			g_aPause_Select[nCnt].fSpanY = 50.0f;

			break;
		}

		g_aPause_Select[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Select[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Select[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		g_aPause_Select[nCnt].colA = 0.01f;
	}
}