//************************************************
//
//�����L���O�ɃX�R�A���o��[ranking_score.cpp]
//Author�F���c����
//
//************************************************
#include "ranking_score.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Ranking_Score[AMOUNT_TEXTURE_RANKING_SCORE] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Ranking_Score = NULL;	//���_�o�b�t�@�̃|�C���^
RANKING_SCORE g_aRanking_Score[AMOUNT_POLYGON_RANKING_SCORE];	//�|���S���̏����i�[
READ_RANKING_SCORE g_aRead_Ranking_Score[6];
int g_nHold_Ranking_Score = 0;
int g_nView_Ranking_Score[AMOUNT_POLYGON_RANKING_SCORE][AMOUNT_POLYGON_RANKING_SCORE] = {};	//��ʕ\���p�U�蕪��
int g_nLastScore = 0;	//�Q�[���Ŋl�������X�R�A
char g_stringScore[6][256];

float g_fcolA = 0.0f;
bool g_bcol = false;

//************************************************
//�����������֐�
//************************************************
void Init_Ranking_Score(int nMode)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NUMBER_RANKING_SCORE,
		&g_pTexture_Ranking_Score[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_RANKING_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Ranking_Score,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Ranking_Score;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Ranking_Score->Lock(0, 0, (void**)&pVtx_Ranking_Score, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_SCORE; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Ranking_Score[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Score[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Score[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking_Score[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Ranking_Score[0].rhw = 1.0f;
		pVtx_Ranking_Score[1].rhw = 1.0f;
		pVtx_Ranking_Score[2].rhw = 1.0f;
		pVtx_Ranking_Score[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Ranking_Score[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Score[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Score[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Ranking_Score[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Ranking_Score[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Ranking_Score[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx_Ranking_Score[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Ranking_Score[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx_Ranking_Score += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Ranking_Score->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_SCORE; nCnt++)
	{
		g_aRanking_Score[nCnt].nStyle = 0;
		g_aRanking_Score[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Score[nCnt].fSpanX = 0.0f;
		g_aRanking_Score[nCnt].fSpanY = 0.0f;
		g_aRanking_Score[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Score[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking_Score[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aRanking_Score[nCnt].fLength = 0.0f;
		g_aRanking_Score[nCnt].fAngle = 0.0f;
		g_aRanking_Score[nCnt].fSPD_X = 0.0f;
		g_aRanking_Score[nCnt].colA = 0.0f;
	}

	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		g_aRead_Ranking_Score[nCnt].lfScore = 0;
		g_aRead_Ranking_Score[nCnt].nDigit = 0;
		
		for (int nWORD = 0; nWORD < 256; nWORD++)
		{
			g_stringScore[nCnt][nWORD] = {};
		}
	}

	g_nHold_Ranking_Score = 0;

	for (int nCnt1 = 0; nCnt1 < AMOUNT_POLYGON_RANKING_SCORE; nCnt1++)
	{
		for (int nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_RANKING_SCORE; nCnt2++)
		{
			g_nView_Ranking_Score[nCnt1][nCnt2] = 0;
		}
	}

	g_nLastScore = 0;

	g_fcolA = 1.0f;

	g_bcol = false;

	//�X�R�A�Ǎ���
	Readinfo_Ranking_Score();

	//�L�^���ꂽ�X�R�A�Ƃ̔�r
	if (nMode == 1)
	{
		SetNewinfo_Ranking();
	}

	//������x�̎��O����ݒ�
	Setinfo_Ranking_Score();

	SetTex_Ranking_Score(nMode);
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Ranking_Score(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_RANKING_SCORE; nCnt++)
	{
		if (g_pTexture_Ranking_Score[nCnt] != NULL)
		{
			g_pTexture_Ranking_Score[nCnt]->Release();
			g_pTexture_Ranking_Score[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Ranking_Score != NULL)
	{
		g_pVtxBuff_Ranking_Score->Release();
		g_pVtxBuff_Ranking_Score = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Ranking_Score(void)
{
	////���_���ւ̃|�C���^
	//VERTEX_2D* pVtx_Ranking_Score;

	////���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	//g_pVtxBuff_Ranking_Score->Lock(0, 0, (void**)&pVtx_Ranking_Score, 0);

	//for (int nRow = 0; nRow < 5; nRow++)
	//{
	//	if (g_aRead_Ranking_Score[nRow].lfScore == g_nLastScore)
	//	{
	//		for (int nCnt = 0; nCnt < g_aRead_Ranking_Score[nRow].nDigit; nCnt++)
	//		{
	//			if (g_fcolA > 0.0f && !g_bcol)
	//			{
	//				g_fcolA -= 0.01f;
	//			}
	//			else if (!g_bcol)
	//			{
	//				g_bcol = true;
	//			}

	//			if (g_fcolA < 1.0f && g_bcol)
	//			{
	//				g_fcolA += 0.01f;
	//			}
	//			else if (g_bcol)
	//			{
	//				g_bcol = false;
	//			}

	//			//�U�蕪�����x�[�X�Ƀe�N�X�`�����W��ύX
	//			pVtx_Ranking_Score[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcolA);
	//			pVtx_Ranking_Score[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcolA);
	//			pVtx_Ranking_Score[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcolA);
	//			pVtx_Ranking_Score[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcolA);

	//			pVtx_Ranking_Score += AMOUNT_VTX;
	//		}
	//	}
	//	else
	//	{
	//		for (int nCnt = 0; nCnt < g_aRead_Ranking_Score[nRow].nDigit; nCnt++)
	//		{
	//			pVtx_Ranking_Score += AMOUNT_VTX;
	//		}
	//	}
	//}

	////���_�o�b�t�@���A�����b�N����
	//g_pVtxBuff_Ranking_Score->Unlock();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Ranking_Score(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Ranking_Score, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_SCORE; nCnt++)
	{
		if (g_aRanking_Score[nCnt].nStyle == 0)
		{
			pDevice->SetTexture(0, g_pTexture_Ranking_Score[0]);
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�X�R�A�Ǎ��݊֐�
//************************************************
void Readinfo_Ranking_Score(void)
{
	int nRow = 0;

	//�t�@�C���|�C���^��錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen(FILE_SET_RANKING, "r");

	//�t�@�C�����J����
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf\n", &g_aRead_Ranking_Score[nRow].lfScore) != EOF)
		{
			nRow++;
		}

		fclose(pFile);
	}
}

//************************************************
//���݂̃X�R�A�Ƃ��Ɣ�ׂ�֐�
//************************************************
void SetNewinfo_Ranking(void)
{
	int* pHoldLastScore;
	pHoldLastScore = Getinfo_HoldLastScore();

	//���݂̃X�R�A���擾
	g_nLastScore = *pHoldLastScore;

	////������X�R�A���L�^����Ă�����̂Ɠ����������ꍇ
	//if ((int)g_aRead_Ranking_Score[nCnt].lfScore != g_nLastScore)
	//{
	//	//�ǂ����悤��
	//}

	//�v�Z�p�Ɏ�����X�R�A�l�𕡐�
	int nCopyLastScore = g_nLastScore;

	//�����̃X�R�A�召���ׂ�
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		if ((int)g_aRead_Ranking_Score[nCnt].lfScore < nCopyLastScore)
		{
			//�ߋ��̒Ⴂ�L�^��ێ����A
			int nHold = (int)g_aRead_Ranking_Score[nCnt].lfScore;

			//������L�^���R�s�[
			g_aRead_Ranking_Score[nCnt].lfScore = nCopyLastScore;

			//�Ⴂ���̋L�^���g���Ĕ�r���J��Ԃ�
			nCopyLastScore = nHold;
		}

		//���o���p�ɕ�����ɕϊ�
		sprintf(&g_stringScore[nCnt][0], "%lf", g_aRead_Ranking_Score[nCnt].lfScore);
	}

	//��r���I�������A�X�R�A���t�@�C���ɏ��o��
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen(FILE_SET_RANKING, "w");

	//�J����
	if (pFile != NULL)
	{
		//������
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			fprintf(pFile, "%s\n", &g_stringScore[nCnt][0]);
		}

		//�t�@�C������
		fclose(pFile);
	}
}

//************************************************
//�X�R�A�\���p�����֐�
//************************************************
void SetTex_Ranking_Score(int nMode)
{
	//�z�[���h���v�Z����
	for (int nRow = 0; nRow < AMOUNT_SET_RANKING_SCORE; nRow++)
	{
		//�v�Z�p�ɁA�X�R�A���擾
		g_nHold_Ranking_Score = (int)g_aRead_Ranking_Score[nRow].lfScore;

		for (int nLine = 0; nLine < AMOUNT_POLYGON_RANKING_SCORE; nLine++)
		{
			//���l��U�蕪����
			g_nView_Ranking_Score[nRow][nLine] = g_nHold_Ranking_Score % 10;

			//�ʂ�������
			g_nHold_Ranking_Score *= 0.1;

			//�������擾
			g_aRead_Ranking_Score[nRow].nDigit++;

			//�ʂ̉����悤���Ȃ��Ȃ炱���ŏI��
			if (g_nHold_Ranking_Score < 0.5)
			{
				break;
			}
		}
	}

	//������X�R�A���擾
	g_nHold_Ranking_Score = g_nLastScore;

	for (int nLine = 0; nLine < AMOUNT_POLYGON_RANKING_SCORE; nLine++)
	{
		//���l��U�蕪����
		g_nView_Ranking_Score[5][nLine] = g_nHold_Ranking_Score % 10;

		//�ʂ�������
		g_nHold_Ranking_Score *= 0.1;

		//�������擾
		g_aRead_Ranking_Score[5].nDigit++;

		//�ʂ̉����悤���Ȃ��Ȃ炱���ŏI��
		if (g_nHold_Ranking_Score < 0.5)
		{
			break;
		}
	}

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Ranking_Score;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Ranking_Score->Lock(0, 0, (void**)&pVtx_Ranking_Score, 0);

	for (int nRow = 0; nRow < AMOUNT_SET_RANKING_SCORE; nRow++)
	{
		for (int nCnt = 0; nCnt < g_aRead_Ranking_Score[nRow].nDigit; nCnt++)
		{
			//���W���w��
			switch (nRow)
			{
			case 0:

				g_aRanking_Score[nCnt].pos = D3DXVECTOR3(1540.0f - (125.0f * nCnt), 235.0f, 0.0f);

				g_aRanking_Score[nCnt].fSpanX = 75.0f;
				g_aRanking_Score[nCnt].fSpanY = 75.0f;
				g_aRanking_Score[nCnt].fLength = sqrtf((g_aRanking_Score[nCnt].fSpanX * g_aRanking_Score[nCnt].fSpanX) + (g_aRanking_Score[nCnt].fSpanY * g_aRanking_Score[nCnt].fSpanY));
				g_aRanking_Score[nCnt].fAngle = atan2f(g_aRanking_Score[nCnt].fSpanX * 2.0f, g_aRanking_Score[nCnt].fSpanY * 2.0f);

				break;

			case 1:

				g_aRanking_Score[nCnt].pos = D3DXVECTOR3(850.0f - (80.0f * nCnt), 525.0f, 0.0f);

				g_aRanking_Score[nCnt].fSpanX = 50.0f;
				g_aRanking_Score[nCnt].fSpanY = 50.0f;
				g_aRanking_Score[nCnt].fLength = sqrtf((g_aRanking_Score[nCnt].fSpanX * g_aRanking_Score[nCnt].fSpanX) + (g_aRanking_Score[nCnt].fSpanY * g_aRanking_Score[nCnt].fSpanY));
				g_aRanking_Score[nCnt].fAngle = atan2f(g_aRanking_Score[nCnt].fSpanX * 2.0f, g_aRanking_Score[nCnt].fSpanY * 2.0f);

				break;

			case 2:

				g_aRanking_Score[nCnt].pos = D3DXVECTOR3(1850.0f - (80.0f * nCnt), 525.0f, 0.0f);

				g_aRanking_Score[nCnt].fSpanX = 50.0f;
				g_aRanking_Score[nCnt].fSpanY = 50.0f;
				g_aRanking_Score[nCnt].fLength = sqrtf((g_aRanking_Score[nCnt].fSpanX * g_aRanking_Score[nCnt].fSpanX) + (g_aRanking_Score[nCnt].fSpanY * g_aRanking_Score[nCnt].fSpanY));
				g_aRanking_Score[nCnt].fAngle = atan2f(g_aRanking_Score[nCnt].fSpanX * 2.0f, g_aRanking_Score[nCnt].fSpanY * 2.0f);

				break;

			case 3:

				g_aRanking_Score[nCnt].pos = D3DXVECTOR3(830.0f - (70.0f * nCnt), 725.0f, 0.0f);

				g_aRanking_Score[nCnt].fSpanX = 40.0f;
				g_aRanking_Score[nCnt].fSpanY = 40.0f;
				g_aRanking_Score[nCnt].fLength = sqrtf((g_aRanking_Score[nCnt].fSpanX * g_aRanking_Score[nCnt].fSpanX) + (g_aRanking_Score[nCnt].fSpanY * g_aRanking_Score[nCnt].fSpanY));
				g_aRanking_Score[nCnt].fAngle = atan2f(g_aRanking_Score[nCnt].fSpanX * 2.0f, g_aRanking_Score[nCnt].fSpanY * 2.0f);

				break;

			case 4:

				g_aRanking_Score[nCnt].pos = D3DXVECTOR3(1830.0f - (70.0f * nCnt), 725.0f, 0.0f);

				g_aRanking_Score[nCnt].fSpanX = 40.0f;
				g_aRanking_Score[nCnt].fSpanY = 40.0f;
				g_aRanking_Score[nCnt].fLength = sqrtf((g_aRanking_Score[nCnt].fSpanX * g_aRanking_Score[nCnt].fSpanX) + (g_aRanking_Score[nCnt].fSpanY * g_aRanking_Score[nCnt].fSpanY));
				g_aRanking_Score[nCnt].fAngle = atan2f(g_aRanking_Score[nCnt].fSpanX * 2.0f, g_aRanking_Score[nCnt].fSpanY * 2.0f);

				break;
			}

			//�ړ��A��]�𔽉f
			pVtx_Ranking_Score[0].pos.x = g_aRanking_Score[nCnt].pos.x + sinf(g_aRanking_Score[nCnt].rot.z - (D3DX_PI - g_aRanking_Score[nCnt].fAngle)) * g_aRanking_Score[nCnt].fLength;
			pVtx_Ranking_Score[0].pos.y = g_aRanking_Score[nCnt].pos.y + cosf(g_aRanking_Score[nCnt].rot.z - (D3DX_PI - g_aRanking_Score[nCnt].fAngle)) * g_aRanking_Score[nCnt].fLength;
			pVtx_Ranking_Score[1].pos.x = g_aRanking_Score[nCnt].pos.x + sinf(g_aRanking_Score[nCnt].rot.z + (D3DX_PI - g_aRanking_Score[nCnt].fAngle)) * g_aRanking_Score[nCnt].fLength;
			pVtx_Ranking_Score[1].pos.y = g_aRanking_Score[nCnt].pos.y + cosf(g_aRanking_Score[nCnt].rot.z + (D3DX_PI - g_aRanking_Score[nCnt].fAngle)) * g_aRanking_Score[nCnt].fLength;
			pVtx_Ranking_Score[2].pos.x = g_aRanking_Score[nCnt].pos.x + sinf(g_aRanking_Score[nCnt].rot.z - g_aRanking_Score[nCnt].fAngle) * g_aRanking_Score[nCnt].fLength;
			pVtx_Ranking_Score[2].pos.y = g_aRanking_Score[nCnt].pos.y + cosf(g_aRanking_Score[nCnt].rot.z - g_aRanking_Score[nCnt].fAngle) * g_aRanking_Score[nCnt].fLength;
			pVtx_Ranking_Score[3].pos.x = g_aRanking_Score[nCnt].pos.x + sinf(g_aRanking_Score[nCnt].rot.z + g_aRanking_Score[nCnt].fAngle) * g_aRanking_Score[nCnt].fLength;
			pVtx_Ranking_Score[3].pos.y = g_aRanking_Score[nCnt].pos.y + cosf(g_aRanking_Score[nCnt].rot.z + g_aRanking_Score[nCnt].fAngle) * g_aRanking_Score[nCnt].fLength;

			//�U�蕪�����x�[�X�Ƀe�N�X�`�����W��ύX
			pVtx_Ranking_Score[0].tex.x = 0.1f * g_nView_Ranking_Score[nRow][nCnt];
			pVtx_Ranking_Score[1].tex.x = 0.1f * (g_nView_Ranking_Score[nRow][nCnt] + 1);
			pVtx_Ranking_Score[2].tex.x = 0.1f * g_nView_Ranking_Score[nRow][nCnt];
			pVtx_Ranking_Score[3].tex.x = 0.1f * (g_nView_Ranking_Score[nRow][nCnt] + 1);

			pVtx_Ranking_Score += AMOUNT_VTX;
		}
	}

	if (nMode == 1)
	{
		for (int nCnt = 0; nCnt < g_aRead_Ranking_Score[5].nDigit; nCnt++)
		{
			g_aRanking_Score[5].pos = D3DXVECTOR3(1100.0f - (80.0f * nCnt), 925.0f, 0.0f);

			g_aRanking_Score[5].fSpanX = 50.0f;
			g_aRanking_Score[5].fSpanY = 50.0f;
			g_aRanking_Score[5].fLength = sqrtf((g_aRanking_Score[5].fSpanX * g_aRanking_Score[5].fSpanX) + (g_aRanking_Score[5].fSpanY * g_aRanking_Score[5].fSpanY));
			g_aRanking_Score[5].fAngle = atan2f(g_aRanking_Score[5].fSpanX * 2.0f, g_aRanking_Score[5].fSpanY * 2.0f);

			//�ړ��A��]�𔽉f
			pVtx_Ranking_Score[0].pos.x = g_aRanking_Score[5].pos.x + sinf(g_aRanking_Score[5].rot.z - (D3DX_PI - g_aRanking_Score[5].fAngle)) * g_aRanking_Score[5].fLength;
			pVtx_Ranking_Score[0].pos.y = g_aRanking_Score[5].pos.y + cosf(g_aRanking_Score[5].rot.z - (D3DX_PI - g_aRanking_Score[5].fAngle)) * g_aRanking_Score[5].fLength;
			pVtx_Ranking_Score[1].pos.x = g_aRanking_Score[5].pos.x + sinf(g_aRanking_Score[5].rot.z + (D3DX_PI - g_aRanking_Score[5].fAngle)) * g_aRanking_Score[5].fLength;
			pVtx_Ranking_Score[1].pos.y = g_aRanking_Score[5].pos.y + cosf(g_aRanking_Score[5].rot.z + (D3DX_PI - g_aRanking_Score[5].fAngle)) * g_aRanking_Score[5].fLength;
			pVtx_Ranking_Score[2].pos.x = g_aRanking_Score[5].pos.x + sinf(g_aRanking_Score[5].rot.z - g_aRanking_Score[5].fAngle) * g_aRanking_Score[5].fLength;
			pVtx_Ranking_Score[2].pos.y = g_aRanking_Score[5].pos.y + cosf(g_aRanking_Score[5].rot.z - g_aRanking_Score[5].fAngle) * g_aRanking_Score[5].fLength;
			pVtx_Ranking_Score[3].pos.x = g_aRanking_Score[5].pos.x + sinf(g_aRanking_Score[5].rot.z + g_aRanking_Score[5].fAngle) * g_aRanking_Score[5].fLength;
			pVtx_Ranking_Score[3].pos.y = g_aRanking_Score[5].pos.y + cosf(g_aRanking_Score[5].rot.z + g_aRanking_Score[5].fAngle) * g_aRanking_Score[5].fLength;

			//�U�蕪�����x�[�X�Ƀe�N�X�`�����W��ύX
			pVtx_Ranking_Score[0].tex.x = 0.1f * g_nView_Ranking_Score[5][nCnt];
			pVtx_Ranking_Score[1].tex.x = 0.1f * (g_nView_Ranking_Score[5][nCnt] + 1);
			pVtx_Ranking_Score[2].tex.x = 0.1f * g_nView_Ranking_Score[5][nCnt];
			pVtx_Ranking_Score[3].tex.x = 0.1f * (g_nView_Ranking_Score[5][nCnt] + 1);

			pVtx_Ranking_Score += AMOUNT_VTX;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Ranking_Score->Unlock();
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Ranking_Score(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING_SCORE; nCnt++)
	{
		g_aRanking_Score[nCnt].nStyle = nCnt;
		g_aRanking_Score[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRanking_Score[nCnt].fSPD_X = 1.0f;
		g_aRanking_Score[nCnt].colA = 0.01f;
	}
}