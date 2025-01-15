//************************************************
//
//�`���[�g���A���Ñ����[�h�I��[tutorial_select.cpp]
//Author�F���c����
//
//************************************************
#include "tutorial_cursor.h"
#include "tutorial_select.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Tutorial_Select[AMOUNT_TEXTURE_TUTORIAL_SELECT] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Tutorial_Select = NULL;	//���_�o�b�t�@�̃|�C���^
TUTORIAL_SELECT g_aTutorial_Select[AMOUNT_POLYGON_TUTORIAL_SELECT];	//�|���S���̏����i�[

//************************************************
//�����������֐�
//************************************************
void Init_Tutorial_Select(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TUTORIAL_SELECT_YES,
		&g_pTexture_Tutorial_Select[0]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TUTORIAL_SELECT_NO,
		&g_pTexture_Tutorial_Select[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TUTORIAL_SELECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Tutorial_Select,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Tutorial_Select;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Tutorial_Select->Lock(0, 0, (void**)&pVtx_Tutorial_Select, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_SELECT; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Tutorial_Select[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Select[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Select[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Select[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Tutorial_Select[0].rhw = 1.0f;
		pVtx_Tutorial_Select[1].rhw = 1.0f;
		pVtx_Tutorial_Select[2].rhw = 1.0f;
		pVtx_Tutorial_Select[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Tutorial_Select[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Select[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Select[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Select[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Tutorial_Select[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Tutorial_Select[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Tutorial_Select[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Tutorial_Select[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Tutorial_Select += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Tutorial_Select->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_SELECT; nCnt++)
	{
		g_aTutorial_Select[nCnt].nStyle = 0;
		g_aTutorial_Select[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Select[nCnt].fSpanX = 0.0f;
		g_aTutorial_Select[nCnt].fSpanY = 0.0f;
		g_aTutorial_Select[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Select[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Select[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aTutorial_Select[nCnt].colA = 0.0f;
	}

	//����̂ݒ��_��W�J
	Setinfo_Tutorial_Select();
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Tutorial_Select(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_TUTORIAL_SELECT; nCnt++)
	{
		if (g_pTexture_Tutorial_Select[nCnt] != NULL)
		{
			g_pTexture_Tutorial_Select[nCnt]->Release();
			g_pTexture_Tutorial_Select[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Tutorial_Select != NULL)
	{
		g_pVtxBuff_Tutorial_Select->Release();
		g_pVtxBuff_Tutorial_Select = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Tutorial_Select(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Tutorial_Select;

	//�I��ł���̂ւ̃|�C���^
	int *pChoose_YesNo;
	pChoose_YesNo = Getinfo_Choose_YesNo();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Tutorial_Select->Lock(0, 0, (void**)&pVtx_Tutorial_Select, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_SELECT; nCnt++)
	{
		if (g_aTutorial_Select[0].col.a < 1.0f)
		{
			g_aTutorial_Select[0].colA *= 1.05f;
			g_aTutorial_Select[1].colA *= 1.05f;
		}
		else
		{
			g_aTutorial_Select[0].colA = 1.0f;
			g_aTutorial_Select[1].colA = 1.0f;
		}

		//�I��ł���̂ɉ����ĐF�ύX
		if (*pChoose_YesNo == 0)
		{
			g_aTutorial_Select[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTutorial_Select[0].colA);
			g_aTutorial_Select[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aTutorial_Select[0].colA);
		}
		else
		{
			g_aTutorial_Select[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, g_aTutorial_Select[0].colA);
			g_aTutorial_Select[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTutorial_Select[0].colA);
		}

		//�ړ��A��]�𔽉f
		pVtx_Tutorial_Select[0].pos.x = g_aTutorial_Select[nCnt].pos.x - g_aTutorial_Select[nCnt].fSpanX;
		pVtx_Tutorial_Select[0].pos.y = g_aTutorial_Select[nCnt].pos.y - g_aTutorial_Select[nCnt].fSpanY;
		pVtx_Tutorial_Select[1].pos.x = g_aTutorial_Select[nCnt].pos.x + g_aTutorial_Select[nCnt].fSpanX;
		pVtx_Tutorial_Select[1].pos.y = g_aTutorial_Select[nCnt].pos.y - g_aTutorial_Select[nCnt].fSpanY;
		pVtx_Tutorial_Select[2].pos.x = g_aTutorial_Select[nCnt].pos.x - g_aTutorial_Select[nCnt].fSpanX;
		pVtx_Tutorial_Select[2].pos.y = g_aTutorial_Select[nCnt].pos.y + g_aTutorial_Select[nCnt].fSpanY;
		pVtx_Tutorial_Select[3].pos.x = g_aTutorial_Select[nCnt].pos.x + g_aTutorial_Select[nCnt].fSpanX;
		pVtx_Tutorial_Select[3].pos.y = g_aTutorial_Select[nCnt].pos.y + g_aTutorial_Select[nCnt].fSpanY;

		pVtx_Tutorial_Select[0].col = g_aTutorial_Select[nCnt].col;
		pVtx_Tutorial_Select[1].col = g_aTutorial_Select[nCnt].col;
		pVtx_Tutorial_Select[2].col = g_aTutorial_Select[nCnt].col;
		pVtx_Tutorial_Select[3].col = g_aTutorial_Select[nCnt].col;

		pVtx_Tutorial_Select += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Tutorial_Select->Unlock();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Tutorial_Select(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Tutorial_Select, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_SELECT; nCnt++)
	{
		switch (g_aTutorial_Select[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Tutorial_Select[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_Tutorial_Select[1]);

			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Tutorial_Select(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_SELECT; nCnt++)
	{
		g_aTutorial_Select[nCnt].nStyle = nCnt;

		switch (g_aTutorial_Select[nCnt].nStyle)
		{
		case 0:

			g_aTutorial_Select[nCnt].pos = D3DXVECTOR3(750.0f, 600.0f, 0.0f);
			g_aTutorial_Select[nCnt].fSpanX = 100.0f;
			g_aTutorial_Select[nCnt].fSpanY = 50.0f;
			g_aTutorial_Select[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aTutorial_Select[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aTutorial_Select[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

			break;

		case 1:

			g_aTutorial_Select[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH - 750.0f, 600.0f, 0.0f);
			g_aTutorial_Select[nCnt].fSpanX = 150.0f;
			g_aTutorial_Select[nCnt].fSpanY = 50.0f;
			g_aTutorial_Select[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aTutorial_Select[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aTutorial_Select[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

			break;
		}

		g_aTutorial_Select[nCnt].colA = 0.01f;
	}
}