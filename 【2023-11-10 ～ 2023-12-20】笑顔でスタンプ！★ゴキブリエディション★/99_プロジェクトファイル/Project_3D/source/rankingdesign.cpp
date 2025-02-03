//************************************************
//
//�����L���O�f�U�C��[rankingdesign.cpp]
//Author�F���c����
//
//************************************************
#include "rankingdesign.h"

#include "debugproc.h"
#include "fade.h"
#include "input.h"

#define AMOUNT_NUM (24)	//�g���鐔���̍ő吔

//�f�U�C���e�N�X�`������
typedef enum
{
	TexLogo = 0,
	Tex1st,
	Tex2nd,
	Tex3rd,
	TexNow,
	TexLast,
	TexMax
}TexType;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureRankingDesign[TexMax] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankingScore = NULL;	//�����e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingDesign = NULL;	//���_�o�b�t�@�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingScore = NULL;	//�������_�o�b�t�@�̃|�C���^
RankingDesign g_aRankingDesign[TexMax];	//���
RankingDesign g_aRankingScore[AMOUNT_NUM];	//���

int g_nScoreInfo[3];	//�L�^
int g_nLastScore = 0;
int g_nLastMode = 0;	//�ȑO�̃��[�h

//************************************************
//�����L���O�f�U�C������
//************************************************
void InitRankingDesign(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < 3; i++)
	{
		g_nScoreInfo[i]= 0;
	}

	//�f�U�C�����Q
	//**************************************************************************

	//�f�U�C�����̏������Q
	for (int i = 0; i < TexMax; i++)
	{
		g_aRankingDesign[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingDesign[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingDesign[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingDesign[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aRankingDesign[i].sizeX = 0.0f;
		g_aRankingDesign[i].sizeY = 0.0f;
		g_aRankingDesign[i].F = 1.0f;	//�ėp
	}

	//�f�U�C���e�N�X�`���̓Ǎ���
	const char* pFileName[TexMax] =
	{
		"data\\texture\\roachrank.png",
		"data\\texture\\1st.png",
		"data\\texture\\2nd.png",
		"data\\texture\\3rd.png",
		"data\\texture\\nowscore.png",
		"data\\texture\\lastscore.png",
	};


	for (int i = 0; i < TexMax; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureRankingDesign[i]);
	}

	//�f�U�C�����_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * TexMax,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingDesign,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffRankingDesign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		//���_���W�̏����ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingDesign->Unlock();

	//�������Q
	//**************************************************************************

	//�������̏������Q
	for (int i = 0; i < AMOUNT_NUM; i++)
	{
		g_aRankingScore[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingScore[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingScore[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingScore[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aRankingScore[i].sizeX = 0.0f;
		g_aRankingScore[i].sizeY = 0.0f;
		g_aRankingScore[i].F = 1.0f;	//�ėp
	}

	//�����e�N�X�`���̓ǂݍ���
	const char* pScoreTexture =
	{
		"data\\texture\\NUM.png",
	};

	for (int i = 0; i < AMOUNT_NUM; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			pScoreTexture,
			&g_pTextureRankingScore);
	}

	//�������_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankingScore,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtxNum;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtxNum, 0);

	for (int i = 0; i < AMOUNT_NUM; i++, pVtxNum += AMOUNT_VTX)
	{
		//���_���W�̏����ݒ�
		pVtxNum[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtxNum[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtxNum[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtxNum[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtxNum[0].rhw = 1.0f;
		pVtxNum[1].rhw = 1.0f;
		pVtxNum[2].rhw = 1.0f;
		pVtxNum[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtxNum[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtxNum[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtxNum[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtxNum[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtxNum[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtxNum[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtxNum[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtxNum[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingScore->Unlock();

	//����t�^
	SetInfoRankingDesign();

	//�L�^��ǂݍ���
	ReadScoreInfo();

	//�W�J
	SetSizeRankingDesign();
}

//************************************************
//�Ō�ɗV��ł����[�h�����߂邽��
//************************************************
int* ChangeLastMode(void)
{
	return &g_nLastMode;
}

//************************************************
//�����L���O�f�U�C���I�������֐�
//************************************************
void UninitRankingDesign(void)
{
	//�f�U�C���Q
	//**************************************************************************

	//�f�U�C���e�N�X�`���̔j��
	for (int i = 0; i < TexMax; i++)
	{
		if (g_pTextureRankingDesign[i] != NULL)
		{
			g_pTextureRankingDesign[i]->Release();
			g_pTextureRankingDesign[i] = NULL;
		}
	}

	//�f�U�C�����_�o�b�t�@�̔j��
	if (g_pVtxBuffRankingDesign != NULL)
	{
		g_pVtxBuffRankingDesign->Release();
		g_pVtxBuffRankingDesign = NULL;
	}

	//�����Q
	//**************************************************************************

	//�����e�N�X�`���̔j��
	if (g_pTextureRankingScore != NULL)
	{
		g_pTextureRankingScore->Release();
		g_pTextureRankingScore = NULL;
	}

	//�������_�o�b�t�@�̔j��
	if (g_pVtxBuffRankingScore != NULL)
	{
		g_pVtxBuffRankingScore->Release();
		g_pVtxBuffRankingScore = NULL;
	}
}

//************************************************
//�����L���O�f�U�C���X�V
//************************************************
void UpdateRankingDesign(void)
{
	PrintDebugProc("%f %f %f\n", g_aRankingDesign[TexNow].pos.x, g_aRankingDesign[TexNow].pos.y, g_aRankingDesign[TexNow].pos.z);
	PrintDebugProc("%f %f %f\n", g_aRankingDesign[TexLast].pos.x, g_aRankingDesign[TexLast].pos.y, g_aRankingDesign[TexLast].pos.z);

	for (int i = 16; i < AMOUNT_NUM; i++)
	{
		PrintDebugProc("����%d : %f %f %f\n", i + 1, g_aRankingScore[i].pos.x, g_aRankingScore[i].pos.y, g_aRankingScore[i].pos.z);
	}
}

//************************************************
//�����L���O�f�U�C���W�J
//************************************************
void SetSizeRankingDesign(void)
{
	//�f�U�C��
	//**************************************************************************

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffRankingDesign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		//���_���W�̏����ݒ�
		pVtx[0].pos =
		{
			g_aRankingDesign[i].pos.x - g_aRankingDesign[i].sizeX,
			g_aRankingDesign[i].pos.y - g_aRankingDesign[i].sizeY,
			0.0f
		};

		pVtx[1].pos =
		{
			g_aRankingDesign[i].pos.x + g_aRankingDesign[i].sizeX,
			g_aRankingDesign[i].pos.y - g_aRankingDesign[i].sizeY,
			0.0f
		};

		pVtx[2].pos =
		{
			g_aRankingDesign[i].pos.x - g_aRankingDesign[i].sizeX,
			g_aRankingDesign[i].pos.y + g_aRankingDesign[i].sizeY,
			0.0f
		};

		pVtx[3].pos =
		{
			g_aRankingDesign[i].pos.x + g_aRankingDesign[i].sizeX,
			g_aRankingDesign[i].pos.y + g_aRankingDesign[i].sizeY,
			0.0f
		};
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingDesign->Unlock();

	//�X�R�A
	//**************************************************************************

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtxNum;

	//�^���X�R�A�p��
	int nCopyScoreInfo[3];

	for (int i = 0; i < 3; i++)
	{
		nCopyScoreInfo[i] = g_nScoreInfo[i];
	}

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffRankingScore->Lock(0, 0, (void**)&pVtxNum, 0);

	for (int i = 0, j = 0; i < AMOUNT_NUM; i++, pVtxNum += AMOUNT_VTX)
	{
		if (i < 6)
		{
			j = 0;
		}
		else if (i >= 6 && i < 12)
		{
			j = 1;
		}
		else if (i >= 12 && i < 18)
		{
			j = 2;
		}
		else if (i == 18)
		{
			nCopyScoreInfo[j] = g_nLastScore;
		}

		//���_���W�̏����ݒ�
		pVtxNum[0].pos =
		{
			g_aRankingScore[i].pos.x - g_aRankingScore[i].sizeX,
			g_aRankingScore[i].pos.y - g_aRankingScore[i].sizeY,
			0.0f
		};

		pVtxNum[1].pos =
		{
			g_aRankingScore[i].pos.x + g_aRankingScore[i].sizeX,
			g_aRankingScore[i].pos.y - g_aRankingScore[i].sizeY,
			0.0f
		};

		pVtxNum[2].pos =
		{
			g_aRankingScore[i].pos.x - g_aRankingScore[i].sizeX,
			g_aRankingScore[i].pos.y + g_aRankingScore[i].sizeY,
			0.0f
		};

		pVtxNum[3].pos =
		{
			g_aRankingScore[i].pos.x + g_aRankingScore[i].sizeX,
			g_aRankingScore[i].pos.y + g_aRankingScore[i].sizeY,
			0.0f
		};

		//�v�Z�p�ɐ��l�𕪗�
		int Value = nCopyScoreInfo[j];

		//�Е��͏�]�Z
		int Span = Value % 10;

		//�Е��͌������炷
		nCopyScoreInfo[j] /= 10;

		//�U�蕪�����x�[�X�Ƀe�N�X�`�����W��ύX
		pVtxNum[0].tex.x = 0.1f * Span;
		pVtxNum[1].tex.x = 0.1f * (Span + 1);
		pVtxNum[2].tex.x = 0.1f * Span;
		pVtxNum[3].tex.x = 0.1f * (Span + 1);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankingScore->Unlock();
}

//************************************************
//�����L���O�f�U�C���`��
//************************************************
void DrawRankingDesign(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//�f�U�C��
	//**************************************************************************

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankingDesign, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TexMax; i++)
	{
		pDevice->SetTexture(0, g_pTextureRankingDesign[i]);

		//�����L���O�f�U�C���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//����
	//**************************************************************************

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankingScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�����L���O�f�U�C���̕`��
	for (int i = 0; i < AMOUNT_NUM; i++)
	{
		//�e�N�X�`���̕`��
		pDevice->SetTexture(0, g_pTextureRankingScore);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfoRankingDesign(void)
{
	//�f�U�C��
	for (int i = 0; i < TexMax; i++)
	{
		if (i == TexLogo)
		{
			g_aRankingDesign[i].pos = D3DXVECTOR3((float)SCREEN_HALFWIDTH, (float)SCREEN_HALFHEIGHT, 0.0f);
			g_aRankingDesign[i].sizeX = (float)SCREEN_HALFWIDTH;
			g_aRankingDesign[i].sizeY = (float)SCREEN_HALFHEIGHT;
		}
		else
		{
			g_aRankingDesign[i].pos = D3DXVECTOR3(650.0f, 150.0f + (i * 200.0f), 0.0f);
			g_aRankingDesign[i].sizeX = 175.0f;
			g_aRankingDesign[i].sizeY = 100.0f;
		}

		if (g_nLastMode == MODE_GAME)
		{
			if (i == TexNow)
			{
				g_aRankingDesign[i].pos = D3DXVECTOR3(700.0f, 950.0f, 0.0f);
				g_aRankingDesign[i].sizeX = 400.0f;
				g_aRankingDesign[i].sizeY = 100.0f;
			}
			else if (i == TexLast)
			{
				g_aRankingDesign[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aRankingDesign[i].sizeX = 0.0f;
				g_aRankingDesign[i].sizeY = 0.0f;
			}
		}
		else if (g_nLastMode == MODE_TITLE)
		{
			if (i == TexNow)
			{
				g_aRankingDesign[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aRankingDesign[i].sizeX = 0.0f;
				g_aRankingDesign[i].sizeY = 0.0f;
			}
			else if (i == TexLast)
			{
				g_aRankingDesign[i].pos = D3DXVECTOR3(700.0f, 950.0f, 0.0f);
				g_aRankingDesign[i].sizeX = 400.0f;
				g_aRankingDesign[i].sizeY = 100.0f;
			}
		}

		g_aRankingDesign[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingDesign[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingDesign[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRankingDesign[i].F = 1.0f;	//�ėp
	}

	//����
	for (int i = 0; i < AMOUNT_NUM; i++)
	{
		if (i < 6)
		{
			g_aRankingScore[i].pos = D3DXVECTOR3((g_aRankingDesign[Tex1st].pos.x + 800.0f) + (i * -100.0f), g_aRankingDesign[Tex1st].pos.y, 0.0f);
		}
		else if (i >= 6 && i < 12)
		{
			g_aRankingScore[i].pos = D3DXVECTOR3((g_aRankingDesign[Tex2nd].pos.x + 800.0f) + ((i - 6) * -100.0f), g_aRankingDesign[Tex2nd].pos.y, 0.0f);
		}
		else if (i >= 12 && i < 18)
		{
			g_aRankingScore[i].pos = D3DXVECTOR3((g_aRankingDesign[Tex3rd].pos.x + 800.0f) + ((i - 12) * -100.0f), g_aRankingDesign[Tex3rd].pos.y, 0.0f);
		}
		else if (i >= 18 && i < 24)
		{
			if (g_nLastMode == MODE_TITLE)
			{
				g_aRankingScore[i].pos = D3DXVECTOR3((g_aRankingDesign[TexLast].pos.x + 1200.0f) + ((i - 16) * -100.0f), g_aRankingDesign[TexLast].pos.y, 0.0f);
			}
			else
			{
				g_aRankingScore[i].pos = D3DXVECTOR3((g_aRankingDesign[TexNow].pos.x + 1200.0f) + ((i - 16) * -100.0f), g_aRankingDesign[TexNow].pos.y, 0.0f);
			}
		}
		g_aRankingScore[i].sizeX = (float)100.0f;
		g_aRankingScore[i].sizeY = (float)80.0f;
		g_aRankingScore[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingScore[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRankingScore[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRankingScore[i].F = 1.0f;	//�ėp
	}
}

//************************************************
//�ߋ��̃X�R�A�̋L�^��ǂݍ���
//************************************************
void ReadScoreInfo(void)
{
	FILE* pFile;

	if (fopen_s(&pFile, "data\\txt\\rank.txt", "r") == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			fscanf_s(pFile, "%d", &g_nScoreInfo[i]);
		}

		fclose(pFile);
	}

	if (fopen_s(&pFile, "data\\txt\\lastrank.txt", "r") == 0)
	{

		fscanf_s(pFile, "%d", &g_nLastScore);

		fclose(pFile);
	}
}