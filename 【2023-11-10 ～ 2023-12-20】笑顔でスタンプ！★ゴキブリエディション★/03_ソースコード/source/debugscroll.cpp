//************************************************
//
//�f�o�b�O�\���p�X�N���[���o�[[debugscroll.cpp]
//Author�F���c����
//
//************************************************
#include "debugscroll.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_DebugScroll = NULL;	//���_�o�b�t�@�̃|�C���^
DebugScroll g_aDebugScroll[AMOUNT_DEBUGSCROLL];	//�X�N���[���o�[���

//************************************************
//����
//************************************************
void InitDebugScroll(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < AMOUNT_DEBUGSCROLL; i++)
	{
		g_aDebugScroll[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDebugScroll[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_DEBUGSCROLL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_DebugScroll,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_DebugScroll->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_DEBUGSCROLL; i++)
	{
		//���_���W�̏����ݒ�
		switch (i)
		{
		case 0:
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, (float)SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(25.0f, (float)SCREEN_HEIGHT, 0.0f);
			break;
		case 1:
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(25.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(25.0f, 50.0f, 0.0f);
			break;
		}

		//������̊g�嗦(?)�̏����ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		switch (i)
		{
		case 0:
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			break;
		case 1:
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		//�e�N�X�`�����W�̏����ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_DebugScroll->Unlock();
}

//************************************************
//�j��
//************************************************
void UninitDebugScroll(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_DebugScroll != NULL)
	{
		g_pVtxBuff_DebugScroll->Release();
		g_pVtxBuff_DebugScroll = NULL;
	}
}

//************************************************
//�X�V
//************************************************
void UpdateDebugScroll(void)
{
	LONG* pRectUP = GetInfoRectUP();

	g_aDebugScroll[1].pos.y = -(float)*pRectUP * 1.03f;

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_DebugScroll->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX;

	pVtx[0].pos = D3DXVECTOR3(0.0f, g_aDebugScroll[1].pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(25.0f, g_aDebugScroll[1].pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, g_aDebugScroll[1].pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(25.0f, g_aDebugScroll[1].pos.y + 50.0f, 0.0f);
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_DebugScroll->Unlock();
}

//************************************************
//�`��
//************************************************
void DrawDebugScroll(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_DebugScroll, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_DEBUGSCROLL; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}