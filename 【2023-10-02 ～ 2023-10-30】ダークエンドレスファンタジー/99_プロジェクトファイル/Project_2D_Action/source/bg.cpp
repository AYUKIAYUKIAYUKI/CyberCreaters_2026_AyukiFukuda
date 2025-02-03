//************************************************
//
//�w�i����[bg.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "bg.h"
#include "player.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_BG[AMOUNT_TEX_BG] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_BG = NULL;	//���_�o�b�t�@�̃|�C���^
BG g_aBG[AMOUNT_POLYGON_BG];	//�w�i���
static float g_F = 0.0f;	//�ėp��������
int g_Mode;

//************************************************
//�|���S�������������֐�
//************************************************
void Init_BG(int nMode)
{
	g_Mode = nMode;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_1,
		&g_pTexture_BG[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_2,
		&g_pTexture_BG[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_3,
		&g_pTexture_BG[2]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_4,
		&g_pTexture_BG[3]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_5,
		&g_pTexture_BG[4]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_6,
		&g_pTexture_BG[5]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_7,
		&g_pTexture_BG[6]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_8,
		&g_pTexture_BG[7]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_9,
		&g_pTexture_BG[8]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BG_10,
		&g_pTexture_BG[9]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_BG,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_BG;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_BG->Lock(0, 0, (void**)&pVtx_BG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_BG[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_BG[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_BG[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_BG[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_BG[0].rhw = 1.0f;
		pVtx_BG[1].rhw = 1.0f;
		pVtx_BG[2].rhw = 1.0f;
		pVtx_BG[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		switch (nMode)
		{
		case BG_TYPE_TITLE:
			pVtx_BG[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
			pVtx_BG[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
			pVtx_BG[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
			pVtx_BG[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
			break;
		case BG_TYPE_GAME:
			pVtx_BG[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx_BG[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx_BG[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx_BG[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_BG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_BG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_BG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_BG[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_BG += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_BG->Unlock();

	//�w�i�\���̂̏��̏������Q
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		g_aBG[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBG[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBG[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBG[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aBG[nCnt].fRadius[nCnt2] = 0.0f;
			g_aBG[nCnt].fTex[nCnt2] = 0.0f;
		}
		g_aBG[nCnt].fLength = 0.0f;
		g_aBG[nCnt].fAngle = 0.0f;
		g_aBG[nCnt].nLayer = 0;
	}

	g_F = 0.01f;

	//�w�i�\���̂ɏ���t�^
	SetInfo_BG();

	//�ʒu�Ɋ�Â��|���S����W�J
	Update_Pos_BG();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_BG(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEX_BG; nCnt++)
	{
		if (g_pTexture_BG[nCnt] != NULL)
		{
			g_pTexture_BG[nCnt]->Release();
			g_pTexture_BG[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_BG != NULL)
	{
		g_pVtxBuff_BG->Release();
		g_pVtxBuff_BG = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_BG(void)
{
	//�N���͓���
	Update_Pos_BG();

	//�F�ύX
	if(g_Mode == BG_TYPE_GAME)
	{
		Update_Col_BG();
	}

	//�e�N�X�`���A�j���[�V����
	Update_Tex_BG();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_BG(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_BG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		//if (nCnt >= AMOUNT_TEX_BG)
		//{
		//	pDevice->SetTexture(0, g_pTexture_BG[9]);
		//}
		//else
		//{
			pDevice->SetTexture(0, g_pTexture_BG[nCnt]);
		//}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�w�i�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_BG(void)
{
	int nCntLayer = 0;
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		if (nCnt < AMOUNT_TEX_BG - 1)
		{
			switch (nCnt)
			{
			case 2:
				nCntLayer++;
				break;
			case 3:
				nCntLayer++;
				break;
			case 5:
				nCntLayer++;
				break;
			case 6:
				nCntLayer++;
				break;
			case 7:
				nCntLayer++;
				break;
			}
			g_aBG[nCnt].pos = D3DXVECTOR3(SCREEN_HALFWIDTH, SCREEN_HALFHEIGHT, 0.0f);
			g_aBG[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_aBG[nCnt].fRadius[0] = RADIUS_BG_X;	//�w�i������
			g_aBG[nCnt].fRadius[1] = RADIUS_BG_Y;	//�w�i�c����
			g_aBG[nCnt].fLength = sqrtf((g_aBG[nCnt].fRadius[0] * g_aBG[nCnt].fRadius[0]) + (g_aBG[nCnt].fRadius[1] * g_aBG[nCnt].fRadius[1]));
			g_aBG[nCnt].fAngle = atan2f(g_aBG[nCnt].fRadius[0] * 2.0f, g_aBG[nCnt].fRadius[1] * 2.0f);
			g_aBG[nCnt].nLayer = nCntLayer;
			g_aBG[nCnt].fTex[0] = 0.0f;
			g_aBG[nCnt].fTex[1] = 2.0f;
		}
		////�N���ɂ͕ʂ̃f�[�^��ݒ肷��
		//else
		//{
		//	//�o���ʒu��ړ��ʂ̓����_���Ɍ��܂�
		//	g_aBG[nCnt].pos = D3DXVECTOR3(SCREEN_HALFWIDTH, 200, 0.0f);
		//	g_aBG[nCnt].move = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		//	g_aBG[nCnt].fRadius[0] = RADIUS_CLOUD_X;	//�N��������
		//	g_aBG[nCnt].fRadius[1] = RADIUS_CLOUD_Y;	//�N���c����
		//	g_aBG[nCnt].fLength = sqrtf((g_aBG[nCnt].fRadius[0] * g_aBG[nCnt].fRadius[0]) + (g_aBG[nCnt].fRadius[1] * g_aBG[nCnt].fRadius[1]));
		//	g_aBG[nCnt].fAngle = atan2f(g_aBG[nCnt].fRadius[0] * 2.0f, g_aBG[nCnt].fRadius[1] * 2.0f);
		//	g_aBG[nCnt].fTex[0] = 0.0f;
		//	g_aBG[nCnt].fTex[1] = 1.0f;
		//}
	}
}

//************************************************
//�w�i�̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_BG(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_BG;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_BG->Lock(0, 0, (void**)&pVtx_BG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		//�N���͓���
		g_aBG[nCnt].pos += g_aBG[nCnt].move;

		pVtx_BG[0].pos.x = g_aBG[nCnt].pos.x + sinf(g_aBG[nCnt].rot.z - (D3DX_PI - g_aBG[nCnt].fAngle)) * g_aBG[nCnt].fLength;
		pVtx_BG[0].pos.y = g_aBG[nCnt].pos.y + cosf(g_aBG[nCnt].rot.z - (D3DX_PI - g_aBG[nCnt].fAngle)) * g_aBG[nCnt].fLength;
		pVtx_BG[1].pos.x = g_aBG[nCnt].pos.x + sinf(g_aBG[nCnt].rot.z + (D3DX_PI - g_aBG[nCnt].fAngle)) * g_aBG[nCnt].fLength;
		pVtx_BG[1].pos.y = g_aBG[nCnt].pos.y + cosf(g_aBG[nCnt].rot.z + (D3DX_PI - g_aBG[nCnt].fAngle)) * g_aBG[nCnt].fLength;
		pVtx_BG[2].pos.x = g_aBG[nCnt].pos.x + sinf(g_aBG[nCnt].rot.z - g_aBG[nCnt].fAngle) * g_aBG[nCnt].fLength;
		pVtx_BG[2].pos.y = g_aBG[nCnt].pos.y + cosf(g_aBG[nCnt].rot.z - g_aBG[nCnt].fAngle) * g_aBG[nCnt].fLength;
		pVtx_BG[3].pos.x = g_aBG[nCnt].pos.x + sinf(g_aBG[nCnt].rot.z + g_aBG[nCnt].fAngle) * g_aBG[nCnt].fLength;
		pVtx_BG[3].pos.y = g_aBG[nCnt].pos.y + cosf(g_aBG[nCnt].rot.z + g_aBG[nCnt].fAngle) * g_aBG[nCnt].fLength;

		pVtx_BG += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_BG->Unlock();
}

//************************************************
//�w�i�̐F��ύX����֐�
//************************************************
void Update_Col_BG(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_BG;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_BG->Lock(0, 0, (void**)&pVtx_BG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		if (nCnt == 4)
		{
			g_aBG[nCnt].col.a -= g_F;

			pVtx_BG[0].col = g_aBG[nCnt].col;
			pVtx_BG[1].col = g_aBG[nCnt].col;
			pVtx_BG[2].col = g_aBG[nCnt].col;
			pVtx_BG[3].col = g_aBG[nCnt].col;
		}

		//����
		if (g_aBG[nCnt].col.a < 0.0f || g_aBG[nCnt].col.a > 1.0f)
		{
			g_F *= -1.0f;
		}

		pVtx_BG += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_BG->Unlock();
}

//************************************************
//�w�i�̃e�N�X�`���𓮂����֐�
//************************************************
void Update_Tex_BG(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_BG;

	PLAYER* pPlayer = GetInfo_Player();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_BG->Lock(0, 0, (void**)&pVtx_BG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BG; nCnt++)
	{
		if (g_aBG[nCnt].nLayer == 2)
		{
			for (int nCntLR = 0; nCntLR < 2; nCntLR++)
			{
				g_aBG[nCnt].fTex[nCntLR] += pPlayer->move.x * 0.0005f;
			}
		}

		switch (g_aBG[nCnt].nLayer)
		{
		case 5:
			for (int nCntLR = 0; nCntLR < 2; nCntLR++)
			{
				g_aBG[nCnt].fTex[nCntLR] += 0.0002f;
				g_aBG[nCnt].fTex[nCntLR] += pPlayer->move.x * 0.0002f;
			}
		case 4:
			for (int nCntLR = 0; nCntLR < 2; nCntLR++)
			{
				g_aBG[nCnt].fTex[nCntLR] += 0.0002f;
				g_aBG[nCnt].fTex[nCntLR] += pPlayer->move.x * 0.0002f;
			}
		case 3:
			for (int nCntLR = 0; nCntLR < 2; nCntLR++)
			{
				g_aBG[nCnt].fTex[nCntLR] += 0.0002f;
				g_aBG[nCnt].fTex[nCntLR] += pPlayer->move.x * 0.0002f;
			}
		case 1:
			for (int nCntLR = 0; nCntLR < 2; nCntLR++)
			{
				g_aBG[nCnt].fTex[nCntLR] += 0.0002f;
				g_aBG[nCnt].fTex[nCntLR] += pPlayer->move.x * 0.0002f;
			}
			break;
		}

		pVtx_BG[0].tex = D3DXVECTOR2(g_aBG[nCnt].fTex[0], 0.0f);
		pVtx_BG[1].tex = D3DXVECTOR2(g_aBG[nCnt].fTex[1], 0.0f);
		pVtx_BG[2].tex = D3DXVECTOR2(g_aBG[nCnt].fTex[0], 1.0f);
		pVtx_BG[3].tex = D3DXVECTOR2(g_aBG[nCnt].fTex[1], 1.0f);

		pVtx_BG += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_BG->Unlock();
}

//************************************************
//�w�i�\���̂̃A�h���X��n��
//************************************************
BG* GetInfo_BG(void)
{
	return &g_aBG[0];
}