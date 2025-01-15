//************************************************
//
//���U���g�̏��ʕ\������[grade.cpp]
//Author�F���c����
//
//************************************************
#include "grade.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Grade[AMOUNT_TEXTURE_GRADE] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Grade = NULL;	//���_�o�b�t�@�̃|�C���^
GRADE g_aGrade[AMOUNT_POLYGON_GRADE];	//���j���[�p�|���S���̏����i�[

//************************************************
//�����������֐�
//************************************************
void Init_Grade(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GRADE_1,
		&g_pTexture_Grade[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_GRADE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Grade,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Grade;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Grade->Lock(0, 0, (void**)&pVtx_Grade, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GRADE; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Grade[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Grade[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Grade[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Grade[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Grade[0].rhw = 1.0f;
		pVtx_Grade[1].rhw = 1.0f;
		pVtx_Grade[2].rhw = 1.0f;
		pVtx_Grade[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Grade[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Grade[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Grade[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Grade[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Grade[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Grade[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Grade[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Grade[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Grade += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Grade->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GRADE; nCnt++)
	{
		g_aGrade[nCnt].nStyle = 0;
		g_aGrade[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGrade[nCnt].fSpanX = 0.0f;
		g_aGrade[nCnt].fSpanY = 0.0f;
		g_aGrade[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGrade[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGrade[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//����̂ݒ��_��W�J
	Setinfo_Grade();
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Grade(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_GRADE; nCnt++)
	{
		if (g_pTexture_Grade[nCnt] != NULL)
		{
			g_pTexture_Grade[nCnt]->Release();
			g_pTexture_Grade[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Grade != NULL)
	{
		g_pVtxBuff_Grade->Release();
		g_pVtxBuff_Grade = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Grade(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Grade;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Grade->Lock(0, 0, (void**)&pVtx_Grade, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GRADE; nCnt++)
	{
		//�ړ��A��]�𔽉f
		pVtx_Grade[0].pos.x = g_aGrade[nCnt].pos.x - g_aGrade[nCnt].fSpanX;
		pVtx_Grade[0].pos.y = g_aGrade[nCnt].pos.y - g_aGrade[nCnt].fSpanY;
		pVtx_Grade[1].pos.x = g_aGrade[nCnt].pos.x + g_aGrade[nCnt].fSpanX;
		pVtx_Grade[1].pos.y = g_aGrade[nCnt].pos.y - g_aGrade[nCnt].fSpanY;
		pVtx_Grade[2].pos.x = g_aGrade[nCnt].pos.x - g_aGrade[nCnt].fSpanX;
		pVtx_Grade[2].pos.y = g_aGrade[nCnt].pos.y + g_aGrade[nCnt].fSpanY;
		pVtx_Grade[3].pos.x = g_aGrade[nCnt].pos.x + g_aGrade[nCnt].fSpanX;
		pVtx_Grade[3].pos.y = g_aGrade[nCnt].pos.y + g_aGrade[nCnt].fSpanY;

		pVtx_Grade[0].col = g_aGrade[nCnt].col;
		pVtx_Grade[1].col = g_aGrade[nCnt].col;
		pVtx_Grade[2].col = g_aGrade[nCnt].col;
		pVtx_Grade[3].col = g_aGrade[nCnt].col;

		pVtx_Grade += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Grade->Unlock();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Grade(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Grade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GRADE; nCnt++)
	{
		switch (g_aGrade[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Grade[0]);

			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Grade(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GRADE; nCnt++)
	{
		g_aGrade[nCnt].nStyle = nCnt;
		g_aGrade[nCnt].pos = D3DXVECTOR3(300.0f, 300.0f + (150.0f * nCnt), 0.0f);
		g_aGrade[nCnt].fSpanX = 50.0f;
		g_aGrade[nCnt].fSpanY = 50.0f;
		g_aGrade[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGrade[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGrade[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	}
}