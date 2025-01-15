//************************************************
//
//�����L���O[ranking.cpp]
//Author�F���c����
//
//************************************************
#include "input.h"
#include "sound.h"
#include "ranking.h"
#include "ranking_back.h"
#include "ranking_black.h"
#include "ranking_fade.h"
#include "ranking_score.h"
#include "ranking_th.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Ranking = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Ranking = NULL;	//���_�o�b�t�@�̃|�C���^
RANKING g_aRanking[AMOUNT_POLYGON_RANKING];
bool g_bStart_R = false;

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Ranking(int nMode)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RANKING_BG,
		&g_pTexture_Ranking);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Ranking,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Ranking;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Ranking->Lock(0, 0, (void**)&pVtx_Ranking, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Ranking[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Ranking[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Ranking[0].rhw = 1.0f;
		pVtx_Ranking[1].rhw = 1.0f;
		pVtx_Ranking[2].rhw = 1.0f;
		pVtx_Ranking[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Ranking[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Ranking[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Ranking[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Ranking[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Ranking[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Ranking[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Ranking[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Ranking[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Ranking += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Ranking->Unlock();

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING; nCnt++)
	{
		g_aRanking[nCnt].nStyle = 0;
		g_aRanking[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRanking[nCnt].fLength = 0.0f;
		g_aRanking[nCnt].fAngle = 0.0f;
	}

	g_bStart_R = false;

	Setinfo_Ranking();

	//���̂ق���
	Init_Ranking_Back();
	Init_Ranking_Black(nMode);
	Init_Ranking_Fade();
	Init_Ranking_Score(nMode);
	Init_Ranking_TH(nMode);
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Ranking(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Ranking != NULL)
	{
		g_pTexture_Ranking->Release();
		g_pTexture_Ranking = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Ranking != NULL)
	{
		g_pVtxBuff_Ranking->Release();
		g_pVtxBuff_Ranking = NULL;
	}

	//���̂ق���
	Uninit_Ranking_Back();
	Uninit_Ranking_Black();
	Uninit_Ranking_Fade();
	Uninit_Ranking_Score();
	Uninit_Ranking_TH();
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Ranking(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Ranking;

	float* pFade_R;
	pFade_R = Getinfo_Ranking_Fade();

	if (!g_bStart_R)
	{
		//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
		g_pVtxBuff_Ranking->Lock(0, 0, (void**)&pVtx_Ranking, 0);

		for (int nCnt = 0; nCnt < AMOUNT_POLYGON_MENU; nCnt++)
		{
			//�ړ��A��]�𔽉f
			pVtx_Ranking[0].pos.x = g_aRanking[nCnt].pos.x + sinf(g_aRanking[nCnt].rot.z - (D3DX_PI - g_aRanking[nCnt].fAngle)) * g_aRanking[nCnt].fLength;
			pVtx_Ranking[0].pos.y = g_aRanking[nCnt].pos.y + cosf(g_aRanking[nCnt].rot.z - (D3DX_PI - g_aRanking[nCnt].fAngle)) * g_aRanking[nCnt].fLength;
			pVtx_Ranking[1].pos.x = g_aRanking[nCnt].pos.x + sinf(g_aRanking[nCnt].rot.z + (D3DX_PI - g_aRanking[nCnt].fAngle)) * g_aRanking[nCnt].fLength;
			pVtx_Ranking[1].pos.y = g_aRanking[nCnt].pos.y + cosf(g_aRanking[nCnt].rot.z + (D3DX_PI - g_aRanking[nCnt].fAngle)) * g_aRanking[nCnt].fLength;
			pVtx_Ranking[2].pos.x = g_aRanking[nCnt].pos.x + sinf(g_aRanking[nCnt].rot.z - g_aRanking[nCnt].fAngle) * g_aRanking[nCnt].fLength;
			pVtx_Ranking[2].pos.y = g_aRanking[nCnt].pos.y + cosf(g_aRanking[nCnt].rot.z - g_aRanking[nCnt].fAngle) * g_aRanking[nCnt].fLength;
			pVtx_Ranking[3].pos.x = g_aRanking[nCnt].pos.x + sinf(g_aRanking[nCnt].rot.z + g_aRanking[nCnt].fAngle) * g_aRanking[nCnt].fLength;
			pVtx_Ranking[3].pos.y = g_aRanking[nCnt].pos.y + cosf(g_aRanking[nCnt].rot.z + g_aRanking[nCnt].fAngle) * g_aRanking[nCnt].fLength;

			pVtx_Ranking[0].col = g_aRanking[nCnt].col;
			pVtx_Ranking[1].col = g_aRanking[nCnt].col;
			pVtx_Ranking[2].col = g_aRanking[nCnt].col;
			pVtx_Ranking[3].col = g_aRanking[nCnt].col;

			pVtx_Ranking += AMOUNT_VTX;
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuff_Ranking->Unlock();

		if (GetKeyboardTrigger(DIK_A) == true || GetJoypadTrigger(JOYKEY_A) == true &&
			!g_bStart_R)
		{
			//���ʉ���炷
			PlaySound(SOUND_LABEL_SE_SELECT2);

			g_bStart_R = true;
		}
	}

	//���̂ق���
	Update_Ranking_Back();
	Update_Ranking_Black();
	Update_Ranking_Fade();
	Update_Ranking_Score();
	Update_Ranking_TH();

	if (g_bStart_R)
	{
		if (*pFade_R > 1.1f)
		{
			Setinfo_Mode(MODE_MENU);	//���j���[��
		}
	}
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Ranking(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Ranking, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Ranking);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//���̂ق���
	Draw_Ranking_Back();
	Draw_Ranking_Black();
	Draw_Ranking_Score();
	Draw_Ranking_TH();
	Draw_Ranking_Fade();
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Ranking(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_RANKING; nCnt++)
	{
		g_aRanking[nCnt].nStyle = 0;
		g_aRanking[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
		g_aRanking[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRanking[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aRanking[nCnt].fLength = sqrtf((990.0f * 990.0f) + (540.0f * 540.0f));
		g_aRanking[nCnt].fAngle = atan2f(990.0f * 2.0f, 540.0f * 2.0f);
	}
}

//************************************************
//�J�n���𑗂�֐�
//************************************************
bool* Getinfo_Ranking(void)
{
	return &g_bStart_R;
}