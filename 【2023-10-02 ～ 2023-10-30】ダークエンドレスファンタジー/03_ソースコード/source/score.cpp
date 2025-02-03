//************************************************
//
//�X�R�A����[score.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "input.h"
#include "score.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Score = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Score = NULL;	//���_�o�b�t�@�̃|�C���^
SCORE g_aScore[AMOUNT_POLYGON_SCORE];	//�X�R�A�\���p
int g_nScore[SCORE_STYLE_MAX];	//�X�R�A
int g_nScore_Digit;	//����
int g_nAnimeCnt;

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Score(int nMode)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SCORE,
		&g_pTexture_Score);

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

	//�X�R�A�\���̃N���A
	for (int i = 0; i < AMOUNT_POLYGON_SCORE; i++)
	{
		g_aScore[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aScore[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aScore[i].nCntTex = 0;
		g_aScore[i].nCntPattern = 0;
		for (int ii = 0; ii < AMOUNT_POLYGON_SCORE; ii++)
		{
			g_aScore[i].fTexSpan[ii] = 0.0f;
			g_aScore[i].fRadius[ii] = 0.0f;
			g_aScore[i].fLength[ii] = 0.0f;
			g_aScore[i].fAngle[ii] = 0.0f;
		}
	}

	//�X�R�A�N���A
	if (nMode != SCORE_TYPE_RESULT)
	{
		for (int i = 0; i < SCORE_STYLE_MAX; i++)
		{
			g_nScore[i] = 0;
		}
	}

	g_nScore_Digit = 0;

	g_nAnimeCnt = 0;

	//�X�R�A�\���p�Ƀf�[�^���Z�b�g
	SetInfo_Score(nMode);
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Score(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Score != NULL)
	{
		g_pTexture_Score->Release();
		g_pTexture_Score = NULL;
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
	/*�L�����̂Ŗ���*/
	//���l�̕ϓ������m���ăA�j���[�V����
	//if (g_nAnimeCnt > 0)
	//{
	//	g_nAnimeCnt--;
	//	Animation_Score();
	//	Update_Tex_Score();
	//}
	//else
	//{
	//	g_nScore_Digit = 0;

		//�I�[�o�[�t���[�h�~
		g_nScore[SCORE_NEW] >= AMOUNT_MAX_SCORE ? g_nScore[SCORE_NEW] = AMOUNT_MAX_SCORE : 0;

		//�W�J
		Update_Pos_Score();
	//}
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
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexture_Score);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�X�R�A�\���p�Ƀf�[�^��t�^����֐�
//************************************************
void SetInfo_Score(int nMode)
{
	for (int i = 0; i < AMOUNT_POLYGON_SCORE; i++)
	{
		switch (nMode)
		{
		case SCORE_TYPE_GAME:
			g_aScore[i].pos = D3DXVECTOR3(1500.0f + (55.0f * i), 100.0f, 0.0f);
			g_aScore[i].fRadius[0] = 25.0f;
			g_aScore[i].fRadius[1] = 45.0f;
			break;
		case SCORE_TYPE_RESULT:
			g_aScore[i].pos = D3DXVECTOR3(1000.0f + (100.0f * i), 625.0f, 0.0f);
			g_aScore[i].fRadius[0] = 50.0f;
			g_aScore[i].fRadius[1] = 90.0f;
			break;
		}
		g_aScore[i].fTexSpan[0] = 0.0f;
		g_aScore[i].fTexSpan[1] = 0.1f;
		g_aScore[i].fLength[0] = sqrtf((g_aScore[i].fRadius[0] * g_aScore[i].fRadius[0]) + (g_aScore[i].fRadius[1] * g_aScore[i].fRadius[1]));
		g_aScore[i].fLength[1] = g_aScore[i].fLength[0];
		g_aScore[i].fAngle[0] = atan2f(g_aScore[i].fRadius[0] * 2.0f, g_aScore[i].fRadius[1] * 2.0f);
		g_aScore[i].fAngle[1] = g_aScore[i].fAngle[0];
	}
}

//************************************************
//�X�R�A�\���p�Ƀo�[�e�b�N�X���X�V�֐�
//************************************************
void Update_Pos_Score(void)
{
	//�e�N�X�`�����X�V
	Update_Tex_Score();

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Score;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Score->Lock(0, 0, (void**)&pVtx_Score, 0);

	for (int i = 0; i < AMOUNT_POLYGON_SCORE; i++)
	{
		pVtx_Score[0].pos.x = g_aScore[i].pos.x + sinf(g_aScore[i].rot.z - (D3DX_PI - g_aScore[i].fAngle[0])) * g_aScore[i].fLength[0];
		pVtx_Score[0].pos.y = g_aScore[i].pos.y + cosf(g_aScore[i].rot.z - (D3DX_PI - g_aScore[i].fAngle[0])) * g_aScore[i].fLength[0];
		pVtx_Score[1].pos.x = g_aScore[i].pos.x + sinf(g_aScore[i].rot.z + (D3DX_PI - g_aScore[i].fAngle[0])) * g_aScore[i].fLength[0];
		pVtx_Score[1].pos.y = g_aScore[i].pos.y + cosf(g_aScore[i].rot.z + (D3DX_PI - g_aScore[i].fAngle[0])) * g_aScore[i].fLength[0];
		pVtx_Score[2].pos.x = g_aScore[i].pos.x + sinf(g_aScore[i].rot.z - g_aScore[i].fAngle[1]) * g_aScore[i].fLength[1];
		pVtx_Score[2].pos.y = g_aScore[i].pos.y + cosf(g_aScore[i].rot.z - g_aScore[i].fAngle[1]) * g_aScore[i].fLength[1];
		pVtx_Score[3].pos.x = g_aScore[i].pos.x + sinf(g_aScore[i].rot.z + g_aScore[i].fAngle[1]) * g_aScore[i].fLength[1];
		pVtx_Score[3].pos.y = g_aScore[i].pos.y + cosf(g_aScore[i].rot.z + g_aScore[i].fAngle[1]) * g_aScore[i].fLength[1];

		pVtx_Score += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Score->Unlock();
}

//************************************************
//�X�R�A�\���p�Ƀe�N�X�`�����X�V�֐�
//************************************************
void Update_Tex_Score(void)
{
	//�e�N�X�`���̕����X�R�A����Z�o
	//if (g_nAnimeCnt <= 0)
	//{
		Calc_Tex_Score();
	//}

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Score;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Score->Lock(0, 0, (void**)&pVtx_Score, 0);

	for (int i = 0; i < AMOUNT_POLYGON_SCORE; i++)
	{
		pVtx_Score[0].tex = D3DXVECTOR2(g_aScore[i].fTexSpan[0], 0.0f);
		pVtx_Score[1].tex = D3DXVECTOR2(g_aScore[i].fTexSpan[1], 0.0f);
		pVtx_Score[2].tex = D3DXVECTOR2(g_aScore[i].fTexSpan[0], 1.0f);
		pVtx_Score[3].tex = D3DXVECTOR2(g_aScore[i].fTexSpan[1], 1.0f);

		pVtx_Score += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Score->Unlock();
}

//************************************************
//�X�R�A����Ƀe�N�X�`�������v�Z�֐�
//************************************************
void Calc_Tex_Score(void)
{
	//�X�R�A���擾
	int nHold = g_nScore[SCORE_NEW];

	//�v�Z����
	for (int i = 0; i < AMOUNT_POLYGON_SCORE; i++)
	{
		//1�̈ʂ̐��l�𔲂��o��
		int nNumber = nHold % 10;

		//�����o���������畝���Z�b�g
		g_aScore[(AMOUNT_POLYGON_SCORE - 1) - i].fTexSpan[0] = 0.0f + (0.1f * nNumber);
		g_aScore[(AMOUNT_POLYGON_SCORE - 1) - i].fTexSpan[1] = 0.1f + (0.1f * nNumber);

		//�X�R�A�̌������炷
		nHold /= 10;

		//�������擾
		if (i > 0)
		{
			g_nScore_Digit++;
		}

		//�ʂ̉����悤���Ȃ��Ȃ炱���ŏI��
		if (nHold < 0.5)
		{
			break;
		}
	}
}

//************************************************
//������
//************************************************
void Animation_Score(void)
{
	//��������
	for (int i = 0; i < g_nScore_Digit; i++)
	{
		//�K���ɐ��l�����o��
		int nNumber = rand() % 10;

		//�����o���������畝���Z�b�g
		g_aScore[(AMOUNT_POLYGON_SCORE - 1) - i].fTexSpan[0] = 0.0f + (0.1f * nNumber);
		g_aScore[(AMOUNT_POLYGON_SCORE - 1) - i].fTexSpan[1] = 0.1f + (0.1f * nNumber);
	}
}

//************************************************
//�X�R�A�\���p�̃A�h���X��n��
//************************************************
SCORE* GetInfo_SCORE(void)
{
	return &g_aScore[0];
}

//************************************************
//�X�R�A�̃A�h���X��n��
//************************************************
int* GetInfo_Score(void)
{
	return &g_nScore[0];
}

//************************************************
//�A�j���[�V����
//************************************************
int* GetInfo_S_A_CT(void)
{
	return &g_nAnimeCnt;
}