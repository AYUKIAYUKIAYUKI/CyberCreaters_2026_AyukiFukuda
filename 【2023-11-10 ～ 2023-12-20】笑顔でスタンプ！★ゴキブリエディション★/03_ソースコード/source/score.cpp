//************************************************
//
//�X�R�A����[score.cpp]	(���K�V�[)
//Author�F���c����
//
//************************************************
#include "score.h"

#include "input.h"
#include "sound.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Score[AMOUNT_TEXTURE_SCORE] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Score = NULL;	//���_�o�b�t�@�̃|�C���^
float g_fMoveX_Score = 0.0f;	//�|���S���ړ���
int g_nScore[AMOUNT_POLYGON_SCORE] = {};	//��ʕ\���p�U�蕪��
int g_nHoldScore = 0;	//�v�Z����Ƃ��X�R�A�̒l���؂�Ă���
int g_nNowScore = 0;	//���݂̃X�R�A
int g_nCntWaitScore = 0;	//�X�R�A�J�E���g
int g_nAnimeScore[AMOUNT_POLYGON_SCORE] = {};	//�A�j���[�V�����p�^���X�R�A�i�[
int g_nCntAnimeScore = 0;	//�A�j���[�V�����p�J�E���g
int g_nCntFinishAnimeScore = 0;	//�A�j���[�V�����I���J�E���g
bool g_bAddedScore = false;	//�X�R�A�ɉ��Z��������������
int g_nScore_Digit = 0;	//���������i�[

/* �ǉ� */
static const float g_AdjustX = 0.0f;
static const float g_AdjustY = 15.0f;

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Score(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLACK_SCORE,
		&g_pTexture_Score[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NUMBER_SCORE,
		&g_pTexture_Score[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SYMBOL_SCORE,
		&g_pTexture_Score[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Score,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Score;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Score->Lock(0, 0, (void**)&pVtx_Score, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Score[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Score[0].rhw = 1.0f;
		pVtx_Score[1].rhw = 1.0f;
		pVtx_Score[2].rhw = 1.0f;
		pVtx_Score[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Score[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Score[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Score[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Score[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Score[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Score += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Score->Unlock();

	//�ړ��ʂ����Z�b�g
	g_fMoveX_Score = 0.0f;

	//�U�蕪�������Z�b�g
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE; nCnt++)
	{
		g_nScore[nCnt] = 0;
	}

	//�ێ������Z�b�g
	g_nHoldScore = 0;

	//���݂̃X�R�A�����Z�b�g
	g_nNowScore = 0;

	//�X�R�A�J�E���g
	g_nCntWaitScore = 0;

	//�^���X�R�A���Z�b�g
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE; nCnt++)
	{
		g_nAnimeScore[nCnt] = 0;
	}

	//�A�j���[�V�����p�J�E���g
	g_nCntAnimeScore = 0;

	//�A�j���[�V�����I���J�E���g
	g_nCntFinishAnimeScore = 0;

	//���Z����𖳂���
	g_bAddedScore = false;

	//���������i�[
	g_nScore_Digit = 0;

	//���_�̓W�J
	SetPos_Vtx_Score();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Score(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_SCORE; nCnt++)
	{
		if (g_pTexture_Score[nCnt] != NULL)
		{
			g_pTexture_Score[nCnt]->Release();
			g_pTexture_Score[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Score != NULL)
	{
		g_pVtxBuff_Score->Release();
		g_pVtxBuff_Score = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Score(void)
{
	//���Z�t���O�̗����Ă���Ƃ��̂݉��
	if (g_bAddedScore)
	{
		Calc_Score();

		if (g_nCntFinishAnimeScore < 5)
		{
			g_nCntAnimeScore++;

			if (g_nCntAnimeScore > 2)
			{
				//�����A�j���[�V����
				Animation_Score();

				g_nCntAnimeScore = 0;

				g_nCntFinishAnimeScore++;
			}
		}
		else
		{
			//�Ō�ɐ��m�Ȓl����ׂ�
			ReSetPos_Vtx_Score();

			//�v�Z�I��
			g_bAddedScore = false;

			g_nCntFinishAnimeScore = 0;
		}
	}
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Score(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Score, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE; nCnt++)
	{
		if (nCnt == 0)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexture_Score[0]);
		}
		else if (nCnt >= 1 && nCnt <= 6)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexture_Score[1]);
		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexture_Score[2]);
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�X�R�A�z�u�p�����֐�
//************************************************
void SetPos_Vtx_Score(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Score;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Score->Lock(0, 0, (void**)&pVtx_Score, 0);

	//�����_��K���Ȉʒu��
	pVtx_Score[0].pos = D3DXVECTOR3(385.0f + g_AdjustX, 20.0f + g_AdjustY, 0.0f);
	pVtx_Score[1].pos = D3DXVECTOR3(700.0f + g_AdjustX, 20.0f + g_AdjustY, 0.0f);
	pVtx_Score[2].pos = D3DXVECTOR3(360.0f + g_AdjustX, 100.0f + g_AdjustY, 0.0f);
	pVtx_Score[3].pos = D3DXVECTOR3(675.0f + g_AdjustX, 100.0f + g_AdjustY, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx_Score[0].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx_Score[1].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx_Score[2].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx_Score[3].col = D3DCOLOR_RGBA(255, 255, 255, 150);

	//������
	pVtx_Score += AMOUNT_VTX;

	//�ŏ���1���̂ݕ\��(�Ȃ����̌�̏����̂��ߍŌ�̃|���S����\��)
	for (int nCnt = 0; nCnt < AMOUNT_USING_POLYGON_NUMBER_SCORE; nCnt++)
	{
		if (nCnt == AMOUNT_USING_POLYGON_NUMBER_SCORE - 1)
		{
			//�X�R�A��1���\��(���l�F�n�_470, ���_575, �I�_680, ��210, ������60)
			pVtx_Score[0].pos = D3DXVECTOR3(535.0f + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[1].pos = D3DXVECTOR3(595.0f + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[2].pos = D3DXVECTOR3(535.0f + g_AdjustX, 80.0f + g_AdjustY, 0.0f);
			pVtx_Score[3].pos = D3DXVECTOR3(595.0f + g_AdjustX, 80.0f + g_AdjustY, 0.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx_Score[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_Score[1].tex = D3DXVECTOR2(TEX_U_RIGHT_SCORE, 0.0f);
			pVtx_Score[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx_Score[3].tex = D3DXVECTOR2(TEX_U_RIGHT_SCORE, 1.0f);
		}

		//�|���S�����_�͕ύX��������
		pVtx_Score += AMOUNT_VTX;
	}

	//�V���{�������̕ӂɔz�u
	pVtx_Score[0].pos = D3DXVECTOR3(405.0f + g_AdjustX, 30.0f + g_AdjustY, 0.0f);
	pVtx_Score[1].pos = D3DXVECTOR3(445.0f + g_AdjustX, 30.0f + g_AdjustY, 0.0f);
	pVtx_Score[2].pos = D3DXVECTOR3(405.0f + g_AdjustX, 90.0f + g_AdjustY, 0.0f);
	pVtx_Score[3].pos = D3DXVECTOR3(445.0f + g_AdjustX, 90.0f + g_AdjustY, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Score->Unlock();
}

//************************************************
//�X�R�A�v�Z�\���p�����֐�
//************************************************
void Calc_Score(void)
{
	//����
	int nScore_Digit = 0;

	//�I�[�o�[�t���[�h�~
	g_nNowScore >= AMOUNT_MAX_SCORE ? g_nNowScore = AMOUNT_MAX_SCORE : g_nNowScore;

	//�v�Z�p�ɁA���̃X�R�A���擾
	g_nHoldScore = g_nNowScore;

	//�z�[���h���v�Z����
	for (int nCnt = 0; nCnt < AMOUNT_USING_POLYGON_NUMBER_SCORE; nCnt++)
	{
		//�z���AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt�Ԗڂ�1�̈ʂ̐��l��U�蕪����
		g_nScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt] = g_nHoldScore % 10;

		//�ʂ�������
		g_nHoldScore /= 10;

		//�������擾
		nScore_Digit++;

		//�ʂ̉����悤���Ȃ��Ȃ炱���ŏI��
		if (g_nHoldScore < 0.5)
		{
			break;
		}
	}

	//��������n��
	g_nScore_Digit = nScore_Digit;
}

//************************************************
//�X�R�A�𑝂₷�p�����֐�
//************************************************
void Add_Score(int Add)
{
	//���Z�J�n�̔�����o��
	g_bAddedScore = true;

	//�������X�R�A��������
	g_nNowScore += Add;

	//�X�R�A���Z���͌v�Z���ł��A�j���J�E���g�����Z�b�g
	g_nCntFinishAnimeScore = 0;

	//�����Ă�����v�Z
	Calc_Score();
}

//************************************************
//�A�j���[�V���������֐�
//************************************************
void Animation_Score(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Timer;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Score->Lock(0, 0, (void**)&pVtx_Timer, 0);

	pVtx_Timer += AMOUNT_VTX * AMOUNT_USING_POLYGON_NUMBER_SCORE;

	//�^���X�R�A���Z�b�g
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SCORE; nCnt++)
	{
		g_nAnimeScore[nCnt] = 0;
	}

	int nDecreaseDigit = 0;
	g_nScore_Digit == 3 ?
		nDecreaseDigit = 1 :
		nDecreaseDigit = 2;

	for (int nCnt = 0; nCnt < g_nScore_Digit - nDecreaseDigit; nCnt++)
	{
		g_nAnimeScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt] = rand() % 10;

		//�U�蕪�����x�[�X�Ƀe�N�X�`�����W��ύX
		pVtx_Timer[0].tex.x = MOVE_SPAN_TEX_SCORE * g_nAnimeScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt];
		pVtx_Timer[1].tex.x = MOVE_SPAN_TEX_SCORE * (g_nAnimeScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt] + 1);
		pVtx_Timer[2].tex.x = MOVE_SPAN_TEX_SCORE * g_nAnimeScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt];
		pVtx_Timer[3].tex.x = MOVE_SPAN_TEX_SCORE * (g_nAnimeScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt] + 1);

		pVtx_Timer -= AMOUNT_VTX;
	}
}

//************************************************
//�|���S���ēW�J�����֐�
//************************************************
void ReSetPos_Vtx_Score(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Score;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Score->Lock(0, 0, (void**)&pVtx_Score, 0);

	//�|�C���^�𐔎��̍Ō��
	pVtx_Score += AMOUNT_VTX * AMOUNT_USING_POLYGON_NUMBER_SCORE;

	g_fMoveX_Score = 0;

	//�擾������������
	for (int nCnt = 0; nCnt < g_nScore_Digit; nCnt++)
	{
		//���݃X�R�A�̌����ɉ����ă|���S������ׂ�
		switch (g_nScore_Digit)
		{
		case 1:

			pVtx_Score[0].pos = D3DXVECTOR3(535.0f + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[1].pos = D3DXVECTOR3(595.0f + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[2].pos = D3DXVECTOR3(535.0f + g_AdjustX, 80.0f + g_AdjustY, 0.0f);
			pVtx_Score[3].pos = D3DXVECTOR3(595.0f + g_AdjustX, 80.0f + g_AdjustY, 0.0f);

			break;

		case 2:

			pVtx_Score[0].pos = D3DXVECTOR3(550.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[1].pos = D3DXVECTOR3(610.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[2].pos = D3DXVECTOR3(550.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);
			pVtx_Score[3].pos = D3DXVECTOR3(610.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);

			break;

		case 3:

			pVtx_Score[0].pos = D3DXVECTOR3(565.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[1].pos = D3DXVECTOR3(625.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[2].pos = D3DXVECTOR3(565.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);
			pVtx_Score[3].pos = D3DXVECTOR3(625.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);

			break;

		case 4:

			pVtx_Score[0].pos = D3DXVECTOR3(580.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[1].pos = D3DXVECTOR3(640.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[2].pos = D3DXVECTOR3(580.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);
			pVtx_Score[3].pos = D3DXVECTOR3(640.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);

			break;

		case 5:

			pVtx_Score[0].pos = D3DXVECTOR3(595.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[1].pos = D3DXVECTOR3(655.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[2].pos = D3DXVECTOR3(595.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);
			pVtx_Score[3].pos = D3DXVECTOR3(655.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);

			break;

		case 6:

			pVtx_Score[0].pos = D3DXVECTOR3(610.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[1].pos = D3DXVECTOR3(670.0f - g_fMoveX_Score + g_AdjustX, 40.0f + g_AdjustY, 0.0f);
			pVtx_Score[2].pos = D3DXVECTOR3(610.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);
			pVtx_Score[3].pos = D3DXVECTOR3(670.0f - g_fMoveX_Score + g_AdjustX, 80.0f + g_AdjustY, 0.0f);

			break;
		}

		g_fMoveX_Score += DISTANCESPAN_POLYGON_SCORE;

		//�U�蕪�����x�[�X�Ƀe�N�X�`�����W��ύX
		pVtx_Score[0].tex.x = MOVE_SPAN_TEX_SCORE * g_nScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt];
		pVtx_Score[1].tex.x = MOVE_SPAN_TEX_SCORE * (g_nScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt] + 1);
		pVtx_Score[2].tex.x = MOVE_SPAN_TEX_SCORE * g_nScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt];
		pVtx_Score[3].tex.x = MOVE_SPAN_TEX_SCORE * (g_nScore[AMOUNT_USING_POLYGON_NUMBER_SCORE - nCnt] + 1);

		pVtx_Score -= AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Score->Unlock();
}

//*************************************
//�X�R�A�L�^
//*************************************
void SaveScore(void)
{
	int nScoreInfo[3];

	FILE* pFile;

	//���̎��Ƃ����X�R�A��������
	if (fopen_s(&pFile, "data\\txt\\lastrank.txt", "w") == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			fprintf(pFile, "%d\n", g_nNowScore);
		}

		fclose(pFile);
	}

	if (fopen_s(&pFile, "data\\txt\\rank.txt", "r") == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			fscanf_s(pFile, "%d", &nScoreInfo[i]);
		}

		fclose(pFile);
	}

	int nScore[4] =
	{
		nScoreInfo[0],
		nScoreInfo[1],
		nScoreInfo[2],
		g_nNowScore,
	};

	int nScoreWrite[3];
	int nHold = 0;

	//�\�[�g
	for (int i = 0; i < 4; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			if (nScore[i] < nScore[j])
			{
				nHold = nScore[i];
				nScore[i] = nScore[j];
				nScore[j] = nHold;
			}
		}
	}

	//���בւ�
	for (int i = 0; i < 3; i++)
	{
		nScoreWrite[i] = nScore[i];
	}

	//������
	if (fopen_s(&pFile, "data\\txt\\rank.txt", "w") == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			fprintf(pFile, "%d\n", nScoreWrite[i]);
		}

		fclose(pFile);
	}
}