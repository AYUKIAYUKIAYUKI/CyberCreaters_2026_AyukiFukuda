//************************************************
//
//���ǂ�[ranking_back.cpp]
//Author�F���c����
//
//************************************************
#include "ranking_back.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Ranking_Back[AMOUNT_TEXTURE_RANKING_BACK] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Ranking_Back = NULL;	//���_�o�b�t�@�̃|�C���^
RANKING_BACK g_aRanking_Back[AMOUNT_POLYGON_RANKING_BACK];	//�J�[�\���p�|���S���̏����i�[
int g_nCnt = 0;

//************************************************
//�����������֐�
//************************************************
void Init_Ranking_Back(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_BACK,
		&g_pTexture_Ranking_Back[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_RANKING_BACK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Ranking_Back,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Ranking_Back;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Ranking_Back->Lock(0, 0, (void**)&pVtx_Ranking_Back, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BACK; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Ranking_Back[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Back[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Back[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Back[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Ranking_Back[0].rhw = 1.0f;
		pVtx_Ranking_Back[1].rhw = 1.0f;
		pVtx_Ranking_Back[2].rhw = 1.0f;
		pVtx_Ranking_Back[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Ranking_Back[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Back[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Back[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Back[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Ranking_Back[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Ranking_Back[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Ranking_Back[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Ranking_Back[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Ranking_Back += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Ranking_Back->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BACK; nCnt++)
	{
		g_aRanking_Back[nCnt].nStyle = 0;
		g_aRanking_Back[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Back[nCnt].fSpanX = 0.0f;
		g_aRanking_Back[nCnt].fSpanY = 0.0f;
		g_aRanking_Back[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Back[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Back[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aRanking_Back[nCnt].fLength = 0.0f;
		g_aRanking_Back[nCnt].fAngle = 0.0f;
		g_aRanking_Back[nCnt].fSPD_X = 0.0f;
		g_aRanking_Back[nCnt].colA = 0.0f;
	}

	g_nCnt = 0;

	//����̂ݒ��_��W�J
	Setinfo_Ranking_Back();
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Ranking_Back(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_RANKING_BACK; nCnt++)
	{
		if (g_pTexture_Ranking_Back[nCnt] != NULL)
		{
			g_pTexture_Ranking_Back[nCnt]->Release();
			g_pTexture_Ranking_Back[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Ranking_Back != NULL)
	{
		g_pVtxBuff_Ranking_Back->Release();
		g_pVtxBuff_Ranking_Back = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Ranking_Back(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Ranking_Back;

	bool* pStart_R;
	pStart_R = Getinfo_Ranking();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Ranking_Back->Lock(0, 0, (void**)&pVtx_Ranking_Back, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BACK; nCnt++)
	{
		//�ړ��Ȃǔ��f
		pVtx_Ranking_Back[0].pos.x = g_aRanking_Back[nCnt].pos.x + sinf(g_aRanking_Back[nCnt].rot.z - (D3DX_PI - g_aRanking_Back[nCnt].fAngle)) * g_aRanking_Back[nCnt].fLength;
		pVtx_Ranking_Back[0].pos.y = g_aRanking_Back[nCnt].pos.y + cosf(g_aRanking_Back[nCnt].rot.z - (D3DX_PI - g_aRanking_Back[nCnt].fAngle)) * g_aRanking_Back[nCnt].fLength;
		pVtx_Ranking_Back[1].pos.x = g_aRanking_Back[nCnt].pos.x + sinf(g_aRanking_Back[nCnt].rot.z + (D3DX_PI - g_aRanking_Back[nCnt].fAngle)) * g_aRanking_Back[nCnt].fLength;
		pVtx_Ranking_Back[1].pos.y = g_aRanking_Back[nCnt].pos.y + cosf(g_aRanking_Back[nCnt].rot.z + (D3DX_PI - g_aRanking_Back[nCnt].fAngle)) * g_aRanking_Back[nCnt].fLength;
		pVtx_Ranking_Back[2].pos.x = g_aRanking_Back[nCnt].pos.x + sinf(g_aRanking_Back[nCnt].rot.z - g_aRanking_Back[nCnt].fAngle) * g_aRanking_Back[nCnt].fLength;
		pVtx_Ranking_Back[2].pos.y = g_aRanking_Back[nCnt].pos.y + cosf(g_aRanking_Back[nCnt].rot.z - g_aRanking_Back[nCnt].fAngle) * g_aRanking_Back[nCnt].fLength;
		pVtx_Ranking_Back[3].pos.x = g_aRanking_Back[nCnt].pos.x + sinf(g_aRanking_Back[nCnt].rot.z + g_aRanking_Back[nCnt].fAngle) * g_aRanking_Back[nCnt].fLength;
		pVtx_Ranking_Back[3].pos.y = g_aRanking_Back[nCnt].pos.y + cosf(g_aRanking_Back[nCnt].rot.z + g_aRanking_Back[nCnt].fAngle) * g_aRanking_Back[nCnt].fLength;

		if (*pStart_R == true && g_nCnt < 5)
		{
			g_nCnt++;

			g_aRanking_Back[nCnt].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		}
		else
		{
			g_aRanking_Back[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		pVtx_Ranking_Back[0].col = g_aRanking_Back[nCnt].col;
		pVtx_Ranking_Back[1].col = g_aRanking_Back[nCnt].col;
		pVtx_Ranking_Back[2].col = g_aRanking_Back[nCnt].col;
		pVtx_Ranking_Back[3].col = g_aRanking_Back[nCnt].col;

		pVtx_Ranking_Back += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Ranking_Back->Unlock();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Ranking_Back(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Ranking_Back, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BACK; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Ranking_Back[0]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Ranking_Back(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_BACK; nCnt++)
	{
		g_aRanking_Back[nCnt].nStyle = nCnt;
		g_aRanking_Back[nCnt].pos = D3DXVECTOR3(1650.0f, 1000.0f, 0.0f);
		g_aRanking_Back[nCnt].fSpanX = 300.0f;
		g_aRanking_Back[nCnt].fSpanY = 50.0f;
		g_aRanking_Back[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Back[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Back[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRanking_Back[nCnt].fLength = sqrtf((g_aRanking_Back[nCnt].fSpanX * g_aRanking_Back[nCnt].fSpanX) + (g_aRanking_Back[nCnt].fSpanY * g_aRanking_Back[nCnt].fSpanY));
		g_aRanking_Back[nCnt].fAngle = atan2f(g_aRanking_Back[nCnt].fSpanX * 2.0f, g_aRanking_Back[nCnt].fSpanY * 2.0f);
		g_aRanking_Back[nCnt].fSPD_X = 1.0f;
		g_aRanking_Back[nCnt].colA = 0.01f;
	}
}