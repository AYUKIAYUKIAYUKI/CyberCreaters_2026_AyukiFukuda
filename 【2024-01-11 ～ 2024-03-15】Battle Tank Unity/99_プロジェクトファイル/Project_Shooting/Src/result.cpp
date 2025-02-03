//===============================================================================
//
//		���U���g���(��ʑJ�ڊm�F�p)(result.cpp)
//								����F���n�O��
// 
//===============================================================================
#include "result.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "stdio.h"
#include "game.h"
#include "player_count.h"
#include "sound.h"
#define MAX_NUMBER_STR	8										//�X�R�A����
#define MAX_SCORE_STR	2										//�\������X�R�A�O���[�v�̐�
#define RESULT_USE_POLY	(MAX_NUMBER_STR * MAX_SCORE_STR)		//��L��̏�Z(�X�R�A�̕`�擙�Ŏg����)
#define RESULT_USE_TEX	3										//���U���gUI�p�̃e�N�X�`����
#define SCORETEX_SIZE_X	120.0f
#define SCORETEX_SIZE_Y	175.0f


typedef enum
{
	RESULT_SCORE_SET = 0,
	RESULT_SERECT_SET,
	RESULT_MAX
}RESULT_SETC;

enum
{
	RESULT_TEX_GAMECLEAR = 0,
	RESULT_TEX_NOWSCORE,
	RESULT_TEX_HIGHSCORE,
};

//�e�N�X�`����
static const char* ResultTex[RESULT_USE_TEX]
{
	"data\\TEXTURE\\result\\result_Gameclear.png",		//������I
	"data\\TEXTURE\\result\\nowscore.png",				//����̃X�R�A
	"data\\TEXTURE\\result\\highscore.png",				//�ō��X�R�A
};

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fHeight;
	float fWidth;
	float fAngle;
	float fLength;
	int Type;
}RESULT_POLY;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fHeight;
	float fWidth;
	float fAngle;
	float fLength;
}RESULT_SCORE;

typedef struct
{
	int nScore;
	D3DXVECTOR3 pos;
	RESULT_SCORE Number[MAX_NUMBER_STR];
}SCORE_OFFSET;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResult[RESULT_USE_TEX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
//�����e�N�X�`���p
LPDIRECT3DTEXTURE9 g_pTextureResultNumber = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultNumber = NULL;

RESULT_POLY g_ResultStr[RESULT_USE_TEX];
SCORE_OFFSET g_ResultScore[MAX_SCORE_STR];

void InitResultScore(void);
void UninitResultScore(void);
void UpdateResultScore(void);
void DrawResultScore(void);
void SetResultScore(void);
void SetPosResultScore(int Num,D3DXVECTOR3 pos);
void EditResultData(void);

//===============================================================================
//���U���g�̏���������
//===============================================================================
void InitResult(void)
{
	PlaySound(SOUND_LABEL_RESULT_RANKING_BGM);
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	for (int i = 0; i < RESULT_USE_TEX; i++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			ResultTex[i],
			&g_pTextureResult[i]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RESULT_USE_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	for (int i = 0; i < RESULT_USE_TEX; i++)
	{
		switch (i)
		{
		case RESULT_TEX_GAMECLEAR:
			g_ResultStr[i].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0);
			g_ResultStr[i].fWidth = SCREEN_WIDTH;
			g_ResultStr[i].fHeight = SCREEN_HEIGHT;
			g_ResultStr[i].Type = i;
			break;
		case RESULT_TEX_NOWSCORE:
			g_ResultStr[i].pos = D3DXVECTOR3(500.0f, 500.0f, 0);
			g_ResultStr[i].fWidth  = 750;
			g_ResultStr[i].fHeight = 250;
			g_ResultStr[i].Type = i;
			break;
		case RESULT_TEX_HIGHSCORE:
			g_ResultStr[i].pos = D3DXVECTOR3(600.0f, 700.0f, 0);
			g_ResultStr[i].fWidth  = 750;
			g_ResultStr[i].fHeight = 250;
			g_ResultStr[i].Type = i;
			break;
		}
		g_ResultStr[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�ꉞ������
		g_ResultStr[i].fAngle = atan2f(g_ResultStr[i].fWidth, g_ResultStr[i].fHeight);
		g_ResultStr[i].fLength = sqrtf(g_ResultStr[i].fWidth * g_ResultStr[i].fWidth + g_ResultStr[i].fHeight * g_ResultStr[i].fHeight) / 2;
	}

	VERTEX_2D* pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int n = 0; n < RESULT_USE_TEX; n++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = g_ResultStr[n].pos.x + sinf(g_ResultStr[n].rot.z - (D3DX_PI - g_ResultStr[n].fAngle)) * g_ResultStr[n].fLength;
		pVtx[0].pos.y = g_ResultStr[n].pos.y + cosf(g_ResultStr[n].rot.z - (D3DX_PI - g_ResultStr[n].fAngle)) * g_ResultStr[n].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_ResultStr[n].pos.x + sinf(g_ResultStr[n].rot.z + (D3DX_PI - g_ResultStr[n].fAngle)) * g_ResultStr[n].fLength;
		pVtx[1].pos.y = g_ResultStr[n].pos.y + cosf(g_ResultStr[n].rot.z + (D3DX_PI - g_ResultStr[n].fAngle)) * g_ResultStr[n].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_ResultStr[n].pos.x + sinf(g_ResultStr[n].rot.z - g_ResultStr[n].fAngle) * g_ResultStr[n].fLength;
		pVtx[2].pos.y = g_ResultStr[n].pos.y + cosf(g_ResultStr[n].rot.z - g_ResultStr[n].fAngle) * g_ResultStr[n].fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_ResultStr[n].pos.x + sinf(g_ResultStr[n].rot.z + g_ResultStr[n].fAngle) * g_ResultStr[n].fLength;
		pVtx[3].pos.y = g_ResultStr[n].pos.y + cosf(g_ResultStr[n].rot.z + g_ResultStr[n].fAngle) * g_ResultStr[n].fLength;
		pVtx[3].pos.z = 0.0f;

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffResult->Unlock();	

	InitResultScore();

	EditResultData();

	SetResultScore();

	SetPosResultScore(0, {1650.0f,500.0f,0.0f});
	SetPosResultScore(1, {1650.0f,700.0f,0.0f});

	//�t�F�[�h�C������
	SetFade(FADE_IN, MODE_MAX);//�t�F�[�h�C�����͓�ڂ̈������������̂łȂ�ł�����
}

//===============================================================================
//���U���g�̏I������
//===============================================================================
void UninitResult(void)
{
	StopSound();
	for (int i = 0; i < RESULT_USE_TEX; i++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureResult[i] != NULL)
		{					
			g_pTextureResult[i]->Release();
			g_pTextureResult[i] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
	UninitResultScore();
}


//===============================================================================
//���U���g�̍X�V����
//===============================================================================
void UpdateResult(void)
{
	UpdateResultScore();
	if (GetJoypadTrigger(JOYKEY_A,0) == true || GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//�t�F�[�h�A�E�g����
		SetFade(FADE_OUT, MODE_TITLE);//��ڂɈڍs��
	}
}


//===============================================================================
//���U���g�̕`�揈��
//===============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int i = 0; i < RESULT_USE_TEX; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[g_ResultStr[i].Type]);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * i,
			2);
	}
	DrawResultScore();
}

//===============================================================================
//���U���g�̃X�R�A����������
//===============================================================================
void InitResultScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\result\\Number001.png",	
		&g_pTextureResultNumber);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RESULT_USE_POLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultNumber,
		NULL);

	for (int i = 0; i < MAX_SCORE_STR; i++)
	{
		g_ResultScore[i].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0);
		g_ResultScore[i].nScore = 0;
		for (int j = 0; j < MAX_NUMBER_STR; j++)
		{
			g_ResultScore[i].Number[j].rot = { 0.0f,0.0f,0.0f };
			g_ResultScore[i].Number[j].fWidth  = SCORETEX_SIZE_X;
			g_ResultScore[i].Number[j].fHeight = SCORETEX_SIZE_Y;
			g_ResultScore[i].Number[j].fAngle  = atan2f(g_ResultScore[i].Number[j].fWidth,g_ResultScore[i].Number[j].fHeight);
			g_ResultScore[i].Number[j].fLength = sqrtf(g_ResultScore[i].Number[j].fWidth *g_ResultScore[i].Number[j].fWidth + g_ResultScore[i].Number[j].fHeight * g_ResultScore[i].Number[j].fHeight) / 2;
			g_ResultScore[i].Number[j].pos = { g_ResultScore[i].pos.x - g_ResultScore[i].Number[j].fWidth * 0.5f, g_ResultScore[i].pos.y,g_ResultScore[i].pos.z };
		}
	}
	VERTEX_2D* pVtx;	//���_���̃|�C���^
	
	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	g_pVtxBuffResultNumber->Lock(0, 0, (void**)&pVtx, 0);

	for (int n = 0; n < MAX_SCORE_STR; n++)
	{
		for (int m = 0; m < MAX_NUMBER_STR; m++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z - (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[0].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z - (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z + (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[1].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z + (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z - g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[2].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z - g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z + g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[3].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z + g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[3].pos.z = 0.0f;

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffResultNumber->Unlock();

}

//===============================================================================
//���U���g�̃X�R�A�I������
//===============================================================================
void UninitResultScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureResultNumber != NULL)
	{
		g_pTextureResultNumber->Release();
		g_pTextureResultNumber = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResultNumber != NULL)
	{
		g_pVtxBuffResultNumber->Release();
		g_pVtxBuffResultNumber = NULL;
	}
}

//===============================================================================
//���U���g�̃X�R�A�X�V����
//===============================================================================
void UpdateResultScore(void)
{
	VERTEX_2D* pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	g_pVtxBuffResultNumber->Lock(0, 0, (void**)&pVtx, 0);

	for (int n = 0; n < MAX_SCORE_STR; n++)
	{
		for (int m = 0; m < MAX_NUMBER_STR; m++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z - (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[0].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z - (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z + (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[1].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z + (D3DX_PI - g_ResultScore[n].Number[m].fAngle)) * g_ResultScore[n].Number[m].fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z - g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[2].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z - g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_ResultScore[n].Number[m].pos.x + sinf(g_ResultScore[n].Number[m].rot.z + g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[3].pos.y = g_ResultScore[n].Number[m].pos.y + cosf(g_ResultScore[n].Number[m].rot.z + g_ResultScore[n].Number[m].fAngle) * g_ResultScore[n].Number[m].fLength;
			pVtx[3].pos.z = 0.0f;

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



			pVtx += 4;
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffResultNumber->Unlock();
}

//===============================================================================
//���U���g�̕`�揈��
//===============================================================================
void DrawResultScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultNumber, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int i = 0; i < RESULT_USE_POLY; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResultNumber);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * i,
			2);
	}
}

//===============================================================================
//���U���g�̃X�R�A�𔽉f���鏈��
//===============================================================================
void SetResultScore(void)
{
	int PosTex[2][8];
	
	int nScore[2];
	for (int i = 0; i < MAX_SCORE_STR; i++)
	{
		int nType = 1;
		nScore[i] = g_ResultScore[i].nScore;
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			nType *= 10;
			PosTex[i][nCnt] = (nScore[i] % nType * 10) / nType;
		}
	}

	VERTEX_2D* pVtx;
	g_pVtxBuffResultNumber->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < MAX_SCORE_STR; i++)
	{
		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.1f * (PosTex[i][nCnt] + 1) - 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f * (PosTex[i][nCnt] + 1), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.1f * (PosTex[i][nCnt] + 1) - 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f * (PosTex[i][nCnt] + 1), 1.0f);

			pVtx += 4;
		}
	}
	g_pVtxBuffResultNumber->Unlock();
}

//===============================================================================
//���U���g�̃X�R�A���W�ݒ菈��
//===============================================================================
void SetPosResultScore(int Num, D3DXVECTOR3 pos)
{
	int i = Num;
	g_ResultScore[i].pos = pos;
	for (int j = 0; j < MAX_NUMBER_STR; j++)
	{
		g_ResultScore[i].Number[j].rot = { 0.0f,0.0f,0.0f };
		g_ResultScore[i].Number[j].fWidth = SCORETEX_SIZE_X;
		g_ResultScore[i].Number[j].fHeight = SCORETEX_SIZE_Y;
		g_ResultScore[i].Number[j].fAngle = atan2f(g_ResultScore[i].Number[j].fWidth, g_ResultScore[i].Number[j].fHeight);
		g_ResultScore[i].Number[j].fLength = sqrtf(g_ResultScore[i].Number[j].fWidth * g_ResultScore[i].Number[j].fWidth + g_ResultScore[i].Number[j].fHeight * g_ResultScore[i].Number[j].fHeight) / 2;
		g_ResultScore[i].Number[j].pos = D3DXVECTOR3((g_ResultScore[i].pos.x - g_ResultScore[i].Number[j].fWidth* 0.75f * j), g_ResultScore[i].pos.y,g_ResultScore[i].pos.z);
	}
}

//===============================================================================
//���U���g�̃X�R�A�f�[�^�̎擾����
//===============================================================================
void EditResultData(void)
{
	int *Score = GetInfoScore();
	g_ResultScore[0].nScore = *Score;

	FILE* pFile;
	pFile = fopen("data\\TXT\\SCORE\\Ranking.txt", "r");
	if (pFile != NULL)
	{	
		fscanf(pFile, "%d", &g_ResultScore[1].nScore);
		fclose(pFile);

	}
	else
	{
		return;
	}
}