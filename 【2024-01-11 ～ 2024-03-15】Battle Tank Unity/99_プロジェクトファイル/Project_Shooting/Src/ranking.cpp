//========================
//
//�����L���O����:ranking.cpp
//Authar:KuramaeSatoshi
// 
//========================
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "sound.h"
#include <assert.h>
#include "player_count.h"
#include "game.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;		//���_�o�b�t�@�ւ̃|�C���^
RankScore g_aRankScore[MAX_RANK][MAX_DIGIT];		//�����L���O�X�R�A���([�����N��][����])
int g_nRankUpdate = -1;								//�X�V�����NNo.
int g_nTimerRanking;								//�_�������鎞��
int g_NumPlayer_RANK = JOIN_VERIFY;	//�v���C�l���i�[

//�w�i�����p�̃O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureRank_BG[NUM_RANK_UITEX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank_BG = NULL;
//=======================================================================
//�����L���O�̏���������
//=======================================================================
void InitRanking(void)
{
	PlaySound(SOUND_LABEL_RESULT_RANKING_BGM);
	InitRanking_BG();
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank = 0; //�����J�E���g����(����)
	int nDataRank = 0;	//�����J�E���g����(����)

	g_NumPlayer_RANK = 0;	// �Q���l���̏�����

	//�v���C�l���̎擾
	g_NumPlayer_RANK = ReturnSelectPlayerCount() + 1;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\result\\Number001.png", &g_pTextureRank);


	//�����L���O�̏��̏�����
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nDataRank = 0; nDataRank < MAX_DIGIT; nDataRank++)
		{
			g_aRankScore[nCntRank][nDataRank].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�X�R�A�̈ʒu�̏�����
			g_aRankScore[nCntRank][nDataRank].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 360.0f - 80.0f * nDataRank, 100.0f + 210 * nCntRank, 0.0f);
			g_aRankScore[nCntRank][nDataRank].nScore = 0;                       //�g�p���Ă��Ȃ����
			g_aRankScore[nCntRank][nDataRank].nScorePos = 0;					//�e�N�X�`���̈ʒu
			g_aRankScore[nCntRank][nDataRank].bRight = false;					//�_�������邩�ǂ���
		}
	}

	g_nTimerRanking = 0;	//�_�������鎞��

//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANK * MAX_DIGIT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRank, NULL);

	//���_���̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);


	for (nCntRank = 0; nCntRank < MAX_RANK * MAX_DIGIT; nCntRank++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}


	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffRank->Unlock();

	SetRanking(*GetInfoScore());

	//�t�F�[�h�C������
	SetFade(FADE_IN, MODE_MAX);//�t�F�[�h�C�����͓�ڂ̈������������̂łȂ�ł�����

}

//=======================================================================
//�����L���O�̏I������
//=======================================================================
void UninitRanking(void)
{
	StopSound();
	UninitRanking_BG();
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}
}

//=======================================================================
//�����L���O�̍X�V����
//=======================================================================
void UpdateRanking(void)
{
	UpdateRanking_BG();
	g_nTimerRanking++;	//�����L���O��_�������鎞�Ԃ̍X�V

	//���_���̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	int nCntRank = 0;
	int nCntDigit = 0;	//����

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A, 0))
	{//ENTER�L�[�������ꂽ or A�{�^���������ꂽ

		//���[�h�ݒ�(�Q�[����ʂɈڍs)
		SetFade(FADE_OUT, MODE_TITLE);
	}

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			pVtx[0].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x - MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y - MAX_RANKHEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x + MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y - MAX_RANKHEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x - MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y + MAX_RANKHEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aRankScore[nCntRank][nCntDigit].pos.x + MAX_RANKWIDTH, g_aRankScore[nCntRank][nCntDigit].pos.y + MAX_RANKHEIGHT, 0.0f);



			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx += 4;
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffRank->Unlock();
}

//=======================================================================
//�����L���O�̕`�揈��
//=======================================================================
void DrawRanking(void)
{
	DrawRanking_BG();
	LPDIRECT3DDEVICE9 pDevice;
	int nCntRank;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRank = 0; nCntRank < MAX_RANK * MAX_DIGIT; nCntRank++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRank);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRank * 4, 2);
	}
}


//=======================================================================
//�����L���O�̃��Z�b�g����
//=======================================================================
void ResetRanking(void)
{
	int nCntRank; //�����J�E���g����(����)
	int nCntDigit;	//�����J�E���g����(����)

	//�����L���O�̏��̏�����
	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			g_aRankScore[nCntRank][nCntDigit].nScore = 0;                       //�g�p���Ă��Ȃ����
		}
	}

}

//=======================================================================
//�����L���O�̃Z�b�g����
//=======================================================================
void SetRanking(int nScore)
{
	//���_���̃|�C���^
	VERTEX_2D* pVtx;

	FILE* pFile = NULL;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	int nCnt = 0;
	int nCntRank = 0;
	int nCntDigit = 0;	//����

	int nCntData = 0;	//�v�f1�̏��
	int nAddRank = 0;	//����̃X�R�A
	int nCopyData = 0;	//�f�[�^�̎󂯎M
	bool bFlag = false;	//���点��t���O
	bool SkipFlag = false;	//�����N���ɓ����X�R�A������ꍇ�������΂��t���O
	int nData[MAX_RANK];	//���łɃ����N�C�����Ă�X�R�A	
	int nDataRank[MAX_RANK];	//�f�[�^��ۑ�����p
	int nDataSave[MAX_RANK];	//�����N�C�������X�R�A�̕ۑ�(���בւ�����)


	pFile = fopen("data\\TXT\\SCORE\\Ranking.txt", "r");



	if (pFile != NULL)
	{
		for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			fscanf(pFile, "%d", &nData[nCntRank]);	//�X�R�A���t�@�C������ǂݍ���

			nDataRank[nCntRank] = nData[nCntRank];	//�ۑ�����

			nDataSave[nCntRank] = 0;	//������
		}

		nAddRank = nScore;	//����̃X�R�A��������
	}

	fclose(pFile);

	for (int i = 0; i < MAX_RANK; i++)
	{
		if (nAddRank == nData[i])
		{
			SkipFlag = true;
		}
	}

	if (nAddRank >= nData[MAX_RANK - 1] && SkipFlag == false)
	{//����5�ʂ�茻�݂̃X�R�A������������
		nData[MAX_RANK - 1] = nAddRank;//5�ʂɌ��݂̃X�R�A����
	}

	for (nCntData = 0; nCntData <= MAX_RANK - 1; nCntData++)//�v�f1�Ɨv�f2���r����
	{
		for (nCntRank = nCntData + 1; nCntRank < MAX_RANK; nCntRank++)
		{
			if (nData[nCntData] < nData[nCntRank])
			{
				nCopyData = nData[nCntData];	//�󂯎M�ɗv�f1����
				nData[nCntData] = nData[nCntRank];	//�v�f1�ɗv�f2����
				nData[nCntRank] = nCopyData;		//���l�����ւ���
			}
		}
	}


	pFile = fopen("data\\TXT\\SCORE\\Ranking.txt", "w");



	if (pFile != NULL)
	{
		for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fprintf(pFile, "%d\n", nData[nCnt]);	//���בւ������̂����߂ĕۑ�����
		}
	}

	fclose(pFile);



	for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		nDataSave[nCnt] = nData[nCnt];	//�X�R�A�̑��
	}

	for (nCnt = 0; nCnt < MAX_RANK; nCnt++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			g_aRankScore[nCnt][nCntDigit].nScorePos = nData[nCnt] % 10;
			nData[nCnt] = nData[nCnt] / 10;
		}
	}

	for (nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (nCntDigit = 0; nCntDigit < MAX_DIGIT; nCntDigit++)
		{
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aRankScore[nCntRank][nCntDigit].nScorePos), 1.0f);

			pVtx += 4;
		}


	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffRank->Unlock();
}

//=====================================================
//
//�����L���O��ʂ̔w�i����
//
//=====================================================

//����������
void InitRanking_BG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\Ranking.png", &g_pTextureRank_BG[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\texture\\ranking_ui.png", &g_pTextureRank_BG[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_RANK_UITEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRank_BG, NULL);

	VERTEX_2D* pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRank_BG->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < NUM_RANK_UITEX; i++)
	{
		if (i == 0)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		}
		if (i == 1)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(500.0f, 10.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(650.0f, 10.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(500.0f, 1010.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(650.0f, 1010.0f, 0.0f);

		}

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRank_BG->Unlock();
}

//�I������
void UninitRanking_BG(void)
{
	for (int i = 0; i < NUM_RANK_UITEX; i++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureRank_BG[i] != NULL)
		{
			g_pTextureRank_BG[i]->Release();
			g_pTextureRank_BG[i] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRank_BG != NULL)
	{
		g_pVtxBuffRank_BG->Release();
		g_pVtxBuffRank_BG = NULL;
	}
}

//�X�V����(���ɓ����Ȃ�)
void UpdateRanking_BG(void)
{

}

//�`�揈��
void DrawRanking_BG(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank_BG, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < NUM_RANK_UITEX; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRank_BG[i]);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}

}