//************************************************
//
//�X�R�A(�����L���O)����[score.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "score_ranking.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Score_Ranking = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Score_Ranking = NULL;	//���_�o�b�t�@�̃|�C���^
SCORE_RANKING g_aScore_Ranking[AMOUNT_POLYGON_SCORE_RANKING];	//�X�R�A�\���p
int g_nScore_Ranking[SCORE_RANKING_STYLE_MAX];	//�X�R�A

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Score_Ranking(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SCORE_RANKING,
		&g_pTexture_Score_Ranking);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_SCORE_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Score_Ranking,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Score_Ranking;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Score_Ranking->Lock(0, 0, (void**)&pVtx_Score_Ranking, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE_RANKING; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Score_Ranking[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score_Ranking[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score_Ranking[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score_Ranking[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Score_Ranking[0].rhw = 1.0f;
		pVtx_Score_Ranking[1].rhw = 1.0f;
		pVtx_Score_Ranking[2].rhw = 1.0f;
		pVtx_Score_Ranking[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Score_Ranking[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score_Ranking[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score_Ranking[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score_Ranking[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Score_Ranking[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Score_Ranking[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Score_Ranking[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Score_Ranking[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Score_Ranking += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Score_Ranking->Unlock();

	//�X�R�A�\���̃N���A
	for (int i = 0; i < AMOUNT_POLYGON_SCORE_RANKING; i++)
	{
		g_aScore_Ranking[i].nStyle = 0;
		g_aScore_Ranking[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Ranking[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Ranking[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Ranking[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aScore_Ranking[i].nCntTex = 0;
		g_aScore_Ranking[i].nCntPattern = 0;
		for (int ii = 0; ii < AMOUNT_POLYGON_SCORE_RANKING; ii++)
		{
			g_aScore_Ranking[i].fTexSpan[ii] = 0.0f;
			g_aScore_Ranking[i].fRadius[ii] = 0.0f;
			g_aScore_Ranking[i].fLength[ii] = 0.0f;
			g_aScore_Ranking[i].fAngle[ii] = 0.0f;
		}
	}

	//�X�R�A�N���A
	for (int i = 0; i < SCORE_RANKING_STYLE_MAX; i++)
	{
		g_nScore_Ranking[i] = 0;
	}

	//�X�R�A�\���p�Ƀf�[�^���Z�b�g
	SetInfo_Score_Ranking();

	//�X�R�A�f�[�^���擾
	ReadInfo_Score_Ranking();

	//�W�J
	Update_Pos_Score_Ranking();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Score_Ranking(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Score_Ranking != NULL)
	{
		g_pTexture_Score_Ranking->Release();
		g_pTexture_Score_Ranking = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Score_Ranking != NULL)
	{
		g_pVtxBuff_Score_Ranking->Release();
		g_pVtxBuff_Score_Ranking = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Score_Ranking(void)
{

}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Score_Ranking(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Score_Ranking, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE_RANKING; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexture_Score_Ranking);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�X�R�A�\���p�Ƀf�[�^��t�^����֐�
//************************************************
void SetInfo_Score_Ranking(void)
{
	for (int i = 0; i < AMOUNT_POLYGON_SCORE_RANKING; i++)
	{
		i >= 8 ? g_aScore_Ranking[i].nStyle = SCORE_RANKING_LAST : g_aScore_Ranking[i].nStyle = SCORE_RANKING_HIGH;

		switch (g_aScore_Ranking[i].nStyle)
		{
		case SCORE_RANKING_HIGH:
			g_aScore_Ranking[i].pos = D3DXVECTOR3(1125.0f + (100.0f * i), 275.0f, 0.0f);
			g_aScore_Ranking[i].fRadius[0] = 50.0f;
			g_aScore_Ranking[i].fRadius[1] = 90.0f;
			break;
		case SCORE_RANKING_LAST:
			g_aScore_Ranking[i].pos = D3DXVECTOR3(1125.0f + (100.0f * (i - 8)), 600.0f, 0.0f);
			g_aScore_Ranking[i].fRadius[0] = 50.0f;
			g_aScore_Ranking[i].fRadius[1] = 90.0f;
			break;
		}
		g_aScore_Ranking[i].fTexSpan[0] = 0.0f;
		g_aScore_Ranking[i].fTexSpan[1] = 0.1f;
		g_aScore_Ranking[i].fLength[0] = sqrtf((g_aScore_Ranking[i].fRadius[0] * g_aScore_Ranking[i].fRadius[0]) + (g_aScore_Ranking[i].fRadius[1] * g_aScore_Ranking[i].fRadius[1]));
		g_aScore_Ranking[i].fLength[1] = g_aScore_Ranking[i].fLength[0];
		g_aScore_Ranking[i].fAngle[0] = atan2f(g_aScore_Ranking[i].fRadius[0] * 2.0f, g_aScore_Ranking[i].fRadius[1] * 2.0f);
		g_aScore_Ranking[i].fAngle[1] = g_aScore_Ranking[i].fAngle[0];
	}
}

//************************************************
//�X�R�A�ɉߋ��̃f�[�^��t�^����֐�
//************************************************
void ReadInfo_Score_Ranking(void)
{
	FILE* pFile;
	pFile = fopen("data\\txt\\ranking.txt", "r");

	if (pFile != NULL)
	{
		for (int i = 0; i < SCORE_RANKING_STYLE_MAX; i++)
		{
			fscanf(pFile, "%d", &g_nScore_Ranking[i]);
		}

		//�t�@�C�������
		fclose(pFile);
	}
}

//************************************************
//�X�R�A�\���p�Ƀo�[�e�b�N�X���X�V�֐�
//************************************************
void Update_Pos_Score_Ranking(void)
{
	//�e�N�X�`�����X�V
	Update_Tex_Score_Ranking();

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Score_Ranking;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Score_Ranking->Lock(0, 0, (void**)&pVtx_Score_Ranking, 0);

	for (int i = 0; i < AMOUNT_POLYGON_SCORE_RANKING; i++)
	{
		pVtx_Score_Ranking[0].pos.x = g_aScore_Ranking[i].pos.x + sinf(g_aScore_Ranking[i].rot.z - (D3DX_PI - g_aScore_Ranking[i].fAngle[0])) * g_aScore_Ranking[i].fLength[0];
		pVtx_Score_Ranking[0].pos.y = g_aScore_Ranking[i].pos.y + cosf(g_aScore_Ranking[i].rot.z - (D3DX_PI - g_aScore_Ranking[i].fAngle[0])) * g_aScore_Ranking[i].fLength[0];
		pVtx_Score_Ranking[1].pos.x = g_aScore_Ranking[i].pos.x + sinf(g_aScore_Ranking[i].rot.z + (D3DX_PI - g_aScore_Ranking[i].fAngle[0])) * g_aScore_Ranking[i].fLength[0];
		pVtx_Score_Ranking[1].pos.y = g_aScore_Ranking[i].pos.y + cosf(g_aScore_Ranking[i].rot.z + (D3DX_PI - g_aScore_Ranking[i].fAngle[0])) * g_aScore_Ranking[i].fLength[0];
		pVtx_Score_Ranking[2].pos.x = g_aScore_Ranking[i].pos.x + sinf(g_aScore_Ranking[i].rot.z - g_aScore_Ranking[i].fAngle[1]) * g_aScore_Ranking[i].fLength[1];
		pVtx_Score_Ranking[2].pos.y = g_aScore_Ranking[i].pos.y + cosf(g_aScore_Ranking[i].rot.z - g_aScore_Ranking[i].fAngle[1]) * g_aScore_Ranking[i].fLength[1];
		pVtx_Score_Ranking[3].pos.x = g_aScore_Ranking[i].pos.x + sinf(g_aScore_Ranking[i].rot.z + g_aScore_Ranking[i].fAngle[1]) * g_aScore_Ranking[i].fLength[1];
		pVtx_Score_Ranking[3].pos.y = g_aScore_Ranking[i].pos.y + cosf(g_aScore_Ranking[i].rot.z + g_aScore_Ranking[i].fAngle[1]) * g_aScore_Ranking[i].fLength[1];

		pVtx_Score_Ranking += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Score_Ranking->Unlock();
}

//************************************************
//�X�R�A�\���p�Ƀe�N�X�`�����X�V�֐�
//************************************************
void Update_Tex_Score_Ranking(void)
{
	//�e�N�X�`���̕����X�R�A����Z�o
	Calc_Tex_Score_Ranking();

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Score_Ranking;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Score_Ranking->Lock(0, 0, (void**)&pVtx_Score_Ranking, 0);

	for (int i = 0; i < AMOUNT_POLYGON_SCORE_RANKING; i++)
	{
		pVtx_Score_Ranking[0].tex = D3DXVECTOR2(g_aScore_Ranking[i].fTexSpan[0], 0.0f);
		pVtx_Score_Ranking[1].tex = D3DXVECTOR2(g_aScore_Ranking[i].fTexSpan[1], 0.0f);
		pVtx_Score_Ranking[2].tex = D3DXVECTOR2(g_aScore_Ranking[i].fTexSpan[0], 1.0f);
		pVtx_Score_Ranking[3].tex = D3DXVECTOR2(g_aScore_Ranking[i].fTexSpan[1], 1.0f);

		pVtx_Score_Ranking += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Score_Ranking->Unlock();
}

//************************************************
//�X�R�A����Ƀe�N�X�`�������v�Z�֐�
//************************************************
void Calc_Tex_Score_Ranking(void)
{
	//�X�R�A���擾
	int nHold[SCORE_RANKING_STYLE_MAX];
	for (int i = 0; i < SCORE_RANKING_STYLE_MAX; i++)
	{
		nHold[i] = g_nScore_Ranking[i];
	}

	//�v�Z����
	for (int i = 0; i < AMOUNT_POLYGON_SCORE_RANKING; i++)
	{
		if (i < 8)
		{
			//1�̈ʂ̐��l�𔲂��o��
			int nNumber = nHold[SCORE_RANKING_HIGH] % 10;

			//�����o���������畝���Z�b�g
			g_aScore_Ranking[(8 - 1) - i].fTexSpan[0] = 0.0f + (0.1f * nNumber);
			g_aScore_Ranking[(8 - 1) - i].fTexSpan[1] = 0.1f + (0.1f * nNumber);

			//�X�R�A�̌������炷
			nHold[SCORE_RANKING_HIGH] /= 10;
		}
		else
		{
			//1�̈ʂ̐��l�𔲂��o��
			int nNumber = nHold[SCORE_RANKING_LAST] % 10;

			//�����o���������畝���Z�b�g
			g_aScore_Ranking[(AMOUNT_POLYGON_SCORE_RANKING - 1) - (i - 8)].fTexSpan[0] = 0.0f + (0.1f * nNumber);
			g_aScore_Ranking[(AMOUNT_POLYGON_SCORE_RANKING - 1) - (i - 8)].fTexSpan[1] = 0.1f + (0.1f * nNumber);

			//�X�R�A�̌������炷
			nHold[SCORE_RANKING_LAST] /= 10;
		}
	}
}


//************************************************
//�X�R�A�\���p�̃A�h���X���擾����֐�
//************************************************
SCORE_RANKING* GetInfo_Score_Ranking(void)
{
	return &g_aScore_Ranking[0];
}