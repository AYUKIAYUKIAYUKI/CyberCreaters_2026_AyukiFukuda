//************************************************
//
//�^�C�g���̐�����[line_title.cpp]
//Author�F���c����
//
//************************************************
#include "line_titleh.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Line_title = NULL;	//���_�o�b�t�@�̃|�C���^
LINE_TITLE g_aLine_title[AMOUNT_POLYGON_LINE_TITLE];	//�J�[�\���p�|���S���̏����i�[

//************************************************
//�����������֐�
//************************************************
void Init_Line_title(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_LINE_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Line_title,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Line_title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Line_title->Lock(0, 0, (void**)&pVtx_Line_title, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LINE_TITLE; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Line_title[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Line_title[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Line_title[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Line_title[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Line_title[0].rhw = 1.0f;
		pVtx_Line_title[1].rhw = 1.0f;
		pVtx_Line_title[2].rhw = 1.0f;
		pVtx_Line_title[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Line_title[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Line_title[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Line_title[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Line_title[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Line_title[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Line_title[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Line_title[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Line_title[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Line_title += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Line_title->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LINE_TITLE; nCnt++)
	{
		g_aLine_title[nCnt].nStyle = 0;
		g_aLine_title[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine_title[nCnt].fSpanX = 0.0f;
		g_aLine_title[nCnt].fSpanY = 0.0f;
		g_aLine_title[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine_title[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine_title[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aLine_title[nCnt].fLength = 0.0f;
		g_aLine_title[nCnt].fAngle = 0.0f;
	}

	//����̂ݒ��_��W�J
	Setinfo_Line_title();
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Line_title(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Line_title != NULL)
	{
		g_pVtxBuff_Line_title->Release();
		g_pVtxBuff_Line_title = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Line_title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Line_title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Line_title->Lock(0, 0, (void**)&pVtx_Line_title, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LINE_TITLE; nCnt++)
	{
		//�ړ��Ȃǔ��f
		pVtx_Line_title[0].pos.x = g_aLine_title[nCnt].pos.x + sinf(g_aLine_title[nCnt].rot.z - (D3DX_PI - g_aLine_title[nCnt].fAngle)) * g_aLine_title[nCnt].fLength;
		pVtx_Line_title[0].pos.y = g_aLine_title[nCnt].pos.y + cosf(g_aLine_title[nCnt].rot.z - (D3DX_PI - g_aLine_title[nCnt].fAngle)) * g_aLine_title[nCnt].fLength;
		pVtx_Line_title[1].pos.x = g_aLine_title[nCnt].pos.x + sinf(g_aLine_title[nCnt].rot.z + (D3DX_PI - g_aLine_title[nCnt].fAngle)) * g_aLine_title[nCnt].fLength;
		pVtx_Line_title[1].pos.y = g_aLine_title[nCnt].pos.y + cosf(g_aLine_title[nCnt].rot.z + (D3DX_PI - g_aLine_title[nCnt].fAngle)) * g_aLine_title[nCnt].fLength;
		pVtx_Line_title[2].pos.x = g_aLine_title[nCnt].pos.x + sinf(g_aLine_title[nCnt].rot.z - g_aLine_title[nCnt].fAngle) * g_aLine_title[nCnt].fLength;
		pVtx_Line_title[2].pos.y = g_aLine_title[nCnt].pos.y + cosf(g_aLine_title[nCnt].rot.z - g_aLine_title[nCnt].fAngle) * g_aLine_title[nCnt].fLength;
		pVtx_Line_title[3].pos.x = g_aLine_title[nCnt].pos.x + sinf(g_aLine_title[nCnt].rot.z + g_aLine_title[nCnt].fAngle) * g_aLine_title[nCnt].fLength;
		pVtx_Line_title[3].pos.y = g_aLine_title[nCnt].pos.y + cosf(g_aLine_title[nCnt].rot.z + g_aLine_title[nCnt].fAngle) * g_aLine_title[nCnt].fLength;

		pVtx_Line_title += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Line_title->Unlock();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Line_title(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Line_title, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LINE_TITLE; nCnt++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Line_title(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LINE_TITLE; nCnt++)
	{
		g_aLine_title[nCnt].nStyle = nCnt;
		g_aLine_title[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
		g_aLine_title[nCnt].fSpanX = 60.0f;
		g_aLine_title[nCnt].fSpanY = 60.0f;
		g_aLine_title[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine_title[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLine_title[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aLine_title[nCnt].fLength = sqrtf((g_aLine_title[nCnt].fSpanX * g_aLine_title[nCnt].fSpanX) + (g_aLine_title[nCnt].fSpanY * g_aLine_title[nCnt].fSpanY));
		g_aLine_title[nCnt].fAngle = atan2f(g_aLine_title[nCnt].fSpanX * 2.0f, g_aLine_title[nCnt].fSpanX * 2.0f);
	}
}