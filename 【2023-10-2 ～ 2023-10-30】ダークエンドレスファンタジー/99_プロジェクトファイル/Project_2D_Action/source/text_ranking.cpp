//************************************************
//
//�����L���O�e�L�X�g����[text_title.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "score_ranking.h"
#include "text_ranking.h"
#include "title.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Text_Ranking[AMOUNT_TEX_TEXT_RANKING] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Text_Ranking = NULL;	//���_�o�b�t�@�̃|�C���^
TEXT_RANKING g_aText_Ranking[AMOUNT_POLYGON_TEXT_RANKING];	//�����L���O�e�L�X�g���

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Text_Ranking()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_RANKING_1,
		&g_pTexture_Text_Ranking[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_RANKING_2,
		&g_pTexture_Text_Ranking[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TEXT_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Text_Ranking,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Text_Ranking;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Text_Ranking->Lock(0, 0, (void**)&pVtx_Text_Ranking, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_RANKING; i++)
	{
		//���_���W�̏����ݒ�
		pVtx_Text_Ranking[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Ranking[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Ranking[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Ranking[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Text_Ranking[0].rhw = 1.0f;
		pVtx_Text_Ranking[1].rhw = 1.0f;
		pVtx_Text_Ranking[2].rhw = 1.0f;
		pVtx_Text_Ranking[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Text_Ranking[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Ranking[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Ranking[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Ranking[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Text_Ranking[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Text_Ranking[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Text_Ranking[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Text_Ranking[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Text_Ranking += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Text_Ranking->Unlock();

	//�w�i�\���̂̏��̏������Q
	for (int i = 0; i < AMOUNT_POLYGON_TEXT_RANKING; i++)
	{
		g_aText_Ranking[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Ranking[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Ranking[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Ranking[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aText_Ranking[i].fRadius[nCnt] = 0.0f;
		}
		g_aText_Ranking[i].fLength = 0.0f;
		g_aText_Ranking[i].fAngle = 0.0f;
	}

	//�w�i�\���̂ɏ���t�^
	SetInfo_Text_Ranking();

	//�ʒu�Ɋ�Â��|���S����W�J
	Update_Pos_Text_Ranking();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Text_Ranking(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < AMOUNT_TEX_TEXT_RANKING; i++)
	{
		if (g_pTexture_Text_Ranking[i] != NULL)
		{
			g_pTexture_Text_Ranking[i]->Release();
			g_pTexture_Text_Ranking[i] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Text_Ranking != NULL)
	{
		g_pVtxBuff_Text_Ranking->Release();
		g_pVtxBuff_Text_Ranking = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Text_Ranking(void)
{

}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Text_Ranking(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Text_Ranking, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_RANKING; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexture_Text_Ranking[i]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�����L���O�e�L�X�g�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Text_Ranking(void)
{
	SCORE_RANKING* pSCORE_RANKING = GetInfo_Score_Ranking();

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_RANKING; i++)
	{
		g_aText_Ranking[i].pos = pSCORE_RANKING[i * 8].pos;
		g_aText_Ranking[i].pos.x -= 525.0f;
		g_aText_Ranking[i].pos.y -= 10.0f;
		g_aText_Ranking[i].fRadius[0] = RADIUS_TEXT_RANKING_X;	//�w�i������
		g_aText_Ranking[i].fRadius[1] = RADIUS_TEXT_RANKING_Y;	//�w�i�c����
		g_aText_Ranking[i].fLength = sqrtf((g_aText_Ranking[i].fRadius[0] * g_aText_Ranking[i].fRadius[0]) + (g_aText_Ranking[i].fRadius[1] * g_aText_Ranking[i].fRadius[1]));
		g_aText_Ranking[i].fAngle = atan2f(g_aText_Ranking[i].fRadius[0] * 2.0f, g_aText_Ranking[i].fRadius[1] * 2.0f);
	}
}

//************************************************
//�����L���O�e�L�X�g�̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Text_Ranking(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Text_Ranking;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Text_Ranking->Lock(0, 0, (void**)&pVtx_Text_Ranking, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_RANKING; i++)
	{
		pVtx_Text_Ranking[0].pos.x = g_aText_Ranking[i].pos.x + sinf(g_aText_Ranking[i].rot.z - (D3DX_PI - g_aText_Ranking[i].fAngle)) * g_aText_Ranking[i].fLength;
		pVtx_Text_Ranking[0].pos.y = g_aText_Ranking[i].pos.y + cosf(g_aText_Ranking[i].rot.z - (D3DX_PI - g_aText_Ranking[i].fAngle)) * g_aText_Ranking[i].fLength;
		pVtx_Text_Ranking[1].pos.x = g_aText_Ranking[i].pos.x + sinf(g_aText_Ranking[i].rot.z + (D3DX_PI - g_aText_Ranking[i].fAngle)) * g_aText_Ranking[i].fLength;
		pVtx_Text_Ranking[1].pos.y = g_aText_Ranking[i].pos.y + cosf(g_aText_Ranking[i].rot.z + (D3DX_PI - g_aText_Ranking[i].fAngle)) * g_aText_Ranking[i].fLength;
		pVtx_Text_Ranking[2].pos.x = g_aText_Ranking[i].pos.x + sinf(g_aText_Ranking[i].rot.z - g_aText_Ranking[i].fAngle) * g_aText_Ranking[i].fLength;
		pVtx_Text_Ranking[2].pos.y = g_aText_Ranking[i].pos.y + cosf(g_aText_Ranking[i].rot.z - g_aText_Ranking[i].fAngle) * g_aText_Ranking[i].fLength;
		pVtx_Text_Ranking[3].pos.x = g_aText_Ranking[i].pos.x + sinf(g_aText_Ranking[i].rot.z + g_aText_Ranking[i].fAngle) * g_aText_Ranking[i].fLength;
		pVtx_Text_Ranking[3].pos.y = g_aText_Ranking[i].pos.y + cosf(g_aText_Ranking[i].rot.z + g_aText_Ranking[i].fAngle) * g_aText_Ranking[i].fLength;

		pVtx_Text_Ranking += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Text_Ranking->Unlock();
}

//************************************************
//�����L���O�e�L�X�g�\���̂̃A�h���X��n��
//************************************************
TEXT_RANKING* GetInfo_Text_Ranking(void)
{
	return &g_aText_Ranking[0];
}