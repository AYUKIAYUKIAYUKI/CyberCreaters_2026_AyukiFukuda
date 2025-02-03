//************************************************
//
//�X�R�A(���U���g)����[score_result.cpp]
//Author�F���c����
//
//************************************************
#include "score_result.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Score_Result[AMOUNT_TEXTURE_SCORE_RESULT] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Score_Result = NULL;	//���_�o�b�t�@�̃|�C���^
float g_fMoveX_Score_Result = 0.0f;	//�|���S���ړ���
int g_aFileData_Score[5]= {};	//�t�@�C������f�[�^���i�[
int g_nAnimeScore_Result[AMOUNT_POLYGON_SCORE_RESULT] = {};	//�A�j���[�V�����p�^���X�R�A�i�[
SCORE_RESULT g_aScore_Result[AMOUNT_POLYGON_SCORE_RESULT];	//

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Score_Result(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NUMBER_SCORE_RESULT,
		&g_pTexture_Score_Result[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_SCORE_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Score_Result,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Score_Result;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Score_Result->Lock(0, 0, (void**)&pVtx_Score_Result, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE_RESULT; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Score_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Score_Result[0].rhw = 1.0f;
		pVtx_Score_Result[1].rhw = 1.0f;
		pVtx_Score_Result[2].rhw = 1.0f;
		pVtx_Score_Result[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Score_Result[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score_Result[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score_Result[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score_Result[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Score_Result[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Score_Result[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Score_Result[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Score_Result[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Score_Result += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Score_Result->Unlock();

	//�ړ��ʂ����Z�b�g
	g_fMoveX_Score_Result = 0.0f;

	//�t�@�C���i�[�p������
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		g_aFileData_Score[nCnt] = 0;
	}

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE_RESULT; nCnt++)
	{
		g_nAnimeScore_Result[nCnt] = 0;

		g_aScore_Result[nCnt].nStyle = 0;
		g_aScore_Result[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Result[nCnt].fSpanX = 0.0f;
		g_aScore_Result[nCnt].fSpanY = 0.0f;
		g_aScore_Result[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Result[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Result[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//���̓ǂݎ��
	Setinfo_Score_Result();

	//���_�̓W�J
	SetPos_Vtx_Score_Result();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Score_Result(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_SCORE_RESULT; nCnt++)
	{
		if (g_pTexture_Score_Result[nCnt] != NULL)
		{
			g_pTexture_Score_Result[nCnt]->Release();
			g_pTexture_Score_Result[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Score_Result != NULL)
	{
		g_pVtxBuff_Score_Result->Release();
		g_pVtxBuff_Score_Result = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Score_Result(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Score_Result;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Score_Result->Lock(0, 0, (void**)&pVtx_Score_Result, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE_RESULT; nCnt++)
	{
		//�ړ��A��]�𔽉f
		pVtx_Score_Result[0].pos.x = g_aScore_Result[nCnt].pos.x - g_aScore_Result[nCnt].fSpanX;
		pVtx_Score_Result[0].pos.y = g_aScore_Result[nCnt].pos.y - g_aScore_Result[nCnt].fSpanY;
		pVtx_Score_Result[1].pos.x = g_aScore_Result[nCnt].pos.x + g_aScore_Result[nCnt].fSpanX;
		pVtx_Score_Result[1].pos.y = g_aScore_Result[nCnt].pos.y - g_aScore_Result[nCnt].fSpanY;
		pVtx_Score_Result[2].pos.x = g_aScore_Result[nCnt].pos.x - g_aScore_Result[nCnt].fSpanX;
		pVtx_Score_Result[2].pos.y = g_aScore_Result[nCnt].pos.y + g_aScore_Result[nCnt].fSpanY;
		pVtx_Score_Result[3].pos.x = g_aScore_Result[nCnt].pos.x + g_aScore_Result[nCnt].fSpanX;
		pVtx_Score_Result[3].pos.y = g_aScore_Result[nCnt].pos.y + g_aScore_Result[nCnt].fSpanY;

		pVtx_Score_Result[0].col = g_aScore_Result[nCnt].col;
		pVtx_Score_Result[1].col = g_aScore_Result[nCnt].col;
		pVtx_Score_Result[2].col = g_aScore_Result[nCnt].col;
		pVtx_Score_Result[3].col = g_aScore_Result[nCnt].col;

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Score_Result[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_nAnimeScore_Result[nCnt]), 0.0f);
		pVtx_Score_Result[1].tex = D3DXVECTOR2(TEX_U_RIGHT_SCORE_RESULT + (0.1f * g_nAnimeScore_Result[nCnt]), 0.0f);
		pVtx_Score_Result[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_nAnimeScore_Result[nCnt]), 1.0f);
		pVtx_Score_Result[3].tex = D3DXVECTOR2(TEX_U_RIGHT_SCORE_RESULT + (0.1f * g_nAnimeScore_Result[nCnt]), 1.0f);

		pVtx_Score_Result += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Score_Result->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Score_Result(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Score_Result, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE_RESULT; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		switch (g_aScore_Result[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Score_Result[0]);

			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�X�R�A���ǂݎ�菈���֐�
//************************************************
void Setinfo_Score_Result(void)
{
	//�t�@�C���|�C���^��錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen("data\\txt\\rank.txt", "r");

	//�t�@�C�����J����
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			fscanf(pFile, "%d", &g_aFileData_Score[nCnt]);
		}

		fclose(pFile);
	}

	//�ǂݎ��X�R�A�f�[�^����
	for (int nCnt1 = 0; nCnt1 < 5; nCnt1++)
	{
		//�z�[���h���v�Z����
		for (int nCnt2 = 0 + (6 * nCnt1); nCnt2 < 30; nCnt2++)
		{
			g_nAnimeScore_Result[nCnt2] = g_aFileData_Score[nCnt1] % 10;

			//�ʂ�������
			g_aFileData_Score[nCnt1] *= 0.1;

			//�ʂ̉����悤���Ȃ��Ȃ炱���ŏI��
			if (g_aFileData_Score[nCnt1] < 0.5)
			{
				break;
			}
		}
	}
}

//************************************************
//�X�R�A�z�u�p�����֐�
//************************************************
void SetPos_Vtx_Score_Result(void)
{
	int nCntDigit = 0;
	int nLine = 0;

	for (int nCnt = 0; nCnt < 30; nCnt++)
	{
		g_aScore_Result[nCnt].nStyle = 0;
		g_aScore_Result[nCnt].pos = D3DXVECTOR3(900.0f - (50.0f * nCntDigit), 300.0f + (150.0f * nLine), 0.0f);
		g_aScore_Result[nCnt].fSpanX = 30.0f;
		g_aScore_Result[nCnt].fSpanY = 37.5f;
		g_aScore_Result[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Result[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore_Result[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		nCntDigit++;

		if (nCntDigit > 5)
		{
			nCntDigit = 0;
			nLine++;
		}
	}
}