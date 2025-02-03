//************************************************
//
//���j���[�̎l�p�\������[square.cpp]
//Author�F���c����
//
//************************************************
#include "square.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Square[AMOUNT_TEXTURE_SQUARE] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Square = NULL;	//���_�o�b�t�@�̃|�C���^
SQUARE g_aSuquare[AMOUNT_POLYGON_SQUARE];	//���j���[�p�|���S���̏����i�[

//************************************************
//�����������֐�
//************************************************
void Init_Square(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SUQUARE_SMALL,
		&g_pTexture_Square[0]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SUQUARE_MIDDLE,
		&g_pTexture_Square[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_SQUARE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Square,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Square;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Square->Lock(0, 0, (void**)&pVtx_Square, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SQUARE; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Square[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Square[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Square[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Square[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Square[0].rhw = 1.0f;
		pVtx_Square[1].rhw = 1.0f;
		pVtx_Square[2].rhw = 1.0f;
		pVtx_Square[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Square[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Square[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Square[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Square[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Square[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Square[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Square[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Square[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Square += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Square->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SQUARE; nCnt++)
	{
		g_aSuquare[nCnt].nStyle = 0;
		g_aSuquare[nCnt].nRute = 0;
		g_aSuquare[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSuquare[nCnt].fSpan = 0.0f;
		g_aSuquare[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSuquare[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSuquare[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aSuquare[nCnt].nCntSpawn = 0;
	}

	//����̂ݒ��_��W�J
	Setinfo_Square();
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Square(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_SQUARE; nCnt++)
	{
		if (g_pTexture_Square[nCnt] != NULL)
		{
			g_pTexture_Square[nCnt]->Release();
			g_pTexture_Square[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Square != NULL)
	{
		g_pVtxBuff_Square->Release();
		g_pVtxBuff_Square = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Square(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Square;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Square->Lock(0, 0, (void**)&pVtx_Square, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SQUARE; nCnt++)
	{
		if (g_aSuquare[nCnt].nCntSpawn > 0)
		{
			g_aSuquare[nCnt].nCntSpawn--;
		}
		else
		{
			//�ړ�
			g_aSuquare[nCnt].pos += g_aSuquare[nCnt].move;

			//�ǂ����s������
			if (g_aSuquare[nCnt].pos.y <= -500.0f ||
				g_aSuquare[nCnt].pos.y >= 1580.0f ||
				g_aSuquare[nCnt].pos.x <= -500.0f ||
				g_aSuquare[nCnt].pos.x >= 2480.0f)
			{
				Disappear_Square(nCnt);
			}

			//�ړ��A��]�𔽉f
			pVtx_Square[0].pos.x = g_aSuquare[nCnt].pos.x - g_aSuquare[nCnt].fSpan;
			pVtx_Square[0].pos.y = g_aSuquare[nCnt].pos.y - g_aSuquare[nCnt].fSpan;
			pVtx_Square[1].pos.x = g_aSuquare[nCnt].pos.x + g_aSuquare[nCnt].fSpan;
			pVtx_Square[1].pos.y = g_aSuquare[nCnt].pos.y - g_aSuquare[nCnt].fSpan;
			pVtx_Square[2].pos.x = g_aSuquare[nCnt].pos.x - g_aSuquare[nCnt].fSpan;
			pVtx_Square[2].pos.y = g_aSuquare[nCnt].pos.y + g_aSuquare[nCnt].fSpan;
			pVtx_Square[3].pos.x = g_aSuquare[nCnt].pos.x + g_aSuquare[nCnt].fSpan;
			pVtx_Square[3].pos.y = g_aSuquare[nCnt].pos.y + g_aSuquare[nCnt].fSpan;

			pVtx_Square[0].col = g_aSuquare[nCnt].col;
			pVtx_Square[1].col = g_aSuquare[nCnt].col;
			pVtx_Square[2].col = g_aSuquare[nCnt].col;
			pVtx_Square[3].col = g_aSuquare[nCnt].col;
		}

		pVtx_Square += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Square->Unlock();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Square(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Square, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SQUARE; nCnt++)
	{
		switch (g_aSuquare[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Square[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_Square[1]);

			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Square(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SQUARE; nCnt++)
	{
		//�����_���ɑ召������
		g_aSuquare[nCnt].nStyle = rand() % 2;
		
		//�����_���ɋO����ݒ�
		g_aSuquare[nCnt].nRute = (int)rand() % 4;

		//�O���ɍ��킹�Ăɏo���ʒu�������_���ɁA�ړ��ʂ͋K��l�ɐݒ�
		int nRandom = 0;
		switch (g_aSuquare[nCnt].nRute)
		{
			//��
		case 0:

			nRandom = rand() % 1980;

			g_aSuquare[nCnt].pos = D3DXVECTOR3((1.0f * nRandom), 1380.0f, 0.0f);
			g_aSuquare[nCnt].move = D3DXVECTOR3(0.0f, -3.0f, 0.0f);

			break;

			//��
		case 1:

			nRandom = rand() % 1980;

			g_aSuquare[nCnt].pos = D3DXVECTOR3((1.0f * nRandom), -300.0f, 0.0f);
			g_aSuquare[nCnt].move = D3DXVECTOR3(0.0f, 3.0f, 0.0f);

			break;

			//��
		case 2:

			nRandom = rand() % 1080;

			g_aSuquare[nCnt].pos = D3DXVECTOR3(2280.0f, (1.0f * nRandom), 0.0f);
			g_aSuquare[nCnt].move = D3DXVECTOR3(-3.0f, 0.0f, 0.0f);

			break;

			//��
		case 3:

			nRandom = rand() % 1080;

			g_aSuquare[nCnt].pos = D3DXVECTOR3(-300.0f, (1.0f * nRandom), 0.0f);
			g_aSuquare[nCnt].move = D3DXVECTOR3(3.0f, 0.0f, 0.0f);

			break;
		}

		if (g_aSuquare[nCnt].nStyle == 0)
		{
			g_aSuquare[nCnt].fSpan = HALFSPAN_SMALL_SQUARE;
		}
		else
		{
			g_aSuquare[nCnt].fSpan = HALFSPAN_MIDDLE_SQUARE;
		}

		g_aSuquare[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSuquare[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		g_aSuquare[nCnt].nCntSpawn = (60 * nCnt);
	}
}

//************************************************
//�|���S�������Đݒ肷��֐�
//************************************************
void Disappear_Square(int nCnt)
{
	//�����_���ɑ召���Č���
	g_aSuquare[nCnt].nStyle = rand() % 2;

	//�����_���ɋO�����Đݒ�
	g_aSuquare[nCnt].nRute = (int)rand() % 4;

	//�O���ɍ��킹�Ăɏo���ʒu�������_���ɁA�ړ��ʂ͋K��l�ɍĐݒ�
	int nRandom = 0;
	switch (g_aSuquare[nCnt].nRute)
	{
		//��
	case 0:

		nRandom = rand() % 1980;

		g_aSuquare[nCnt].pos = D3DXVECTOR3((1.0f * nRandom), 1380.0f, 0.0f);
		g_aSuquare[nCnt].move = D3DXVECTOR3(0.0f, -3.0f, 0.0f);

		break;

		//��
	case 1:

		nRandom = rand() % 1980;

		g_aSuquare[nCnt].pos = D3DXVECTOR3((1.0f * nRandom), -300.0f, 0.0f);
		g_aSuquare[nCnt].move = D3DXVECTOR3(0.0f, 3.0f, 0.0f);

		break;

		//��
	case 2:

		nRandom = rand() % 1080;

		g_aSuquare[nCnt].pos = D3DXVECTOR3(2280.0f, (1.0f * nRandom), 0.0f);
		g_aSuquare[nCnt].move = D3DXVECTOR3(-3.0f, 0.0f, 0.0f);

		break;

		//��
	case 3:

		nRandom = rand() % 1080;

		g_aSuquare[nCnt].pos = D3DXVECTOR3(-300.0f, (1.0f * nRandom), 0.0f);
		g_aSuquare[nCnt].move = D3DXVECTOR3(3.0f, 0.0f, 0.0f);

		break;
	}

	if (g_aSuquare[nCnt].nStyle == 0)
	{
		g_aSuquare[nCnt].fSpan = HALFSPAN_SMALL_SQUARE;
	}
	else
	{
		g_aSuquare[nCnt].fSpan = HALFSPAN_MIDDLE_SQUARE;
	}
}