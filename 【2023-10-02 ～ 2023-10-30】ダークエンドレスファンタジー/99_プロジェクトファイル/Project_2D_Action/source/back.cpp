//************************************************
//
//UI�̌��̏���[back.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "back.h"
#include "score.h"
#include "timer.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Back = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Back = NULL;	//���_�o�b�t�@�̃|�C���^
BACK g_aBack[AMOUNT_POLYGON_BACK];	//UI�̌��̏��

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Back()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BACK,
		&g_pTexture_Back);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BACK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Back,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Back;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Back->Lock(0, 0, (void**)&pVtx_Back, 0);

	for (int i = 0; i < AMOUNT_POLYGON_BACK; i++)
	{
		//���_���W�̏����ݒ�
		pVtx_Back[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Back[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Back[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Back[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Back[0].rhw = 1.0f;
		pVtx_Back[1].rhw = 1.0f;
		pVtx_Back[2].rhw = 1.0f;
		pVtx_Back[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Back[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		pVtx_Back[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		pVtx_Back[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		pVtx_Back[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Back[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Back[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Back[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Back[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Back += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Back->Unlock();

	//UI�̌��̍\���̂̏��̏������Q
	for (int i = 0; i < AMOUNT_POLYGON_BACK; i++)
	{
		g_aBack[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBack[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBack[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBack[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aBack[i].fRadius[nCnt] = 0.0f;
		}
		g_aBack[i].fLength = 0.0f;
		g_aBack[i].fAngle = 0.0f;
	}

	//UI�̌��̍\���̂ɏ���t�^
	SetInfo_Back();

	//�W�J
	Update_Pos_Back();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Back(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Back != NULL)
	{
		g_pTexture_Back->Release();
		g_pTexture_Back = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Back != NULL)
	{
		g_pVtxBuff_Back->Release();
		g_pVtxBuff_Back = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Back(void)
{

}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Back(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Back, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int i = 0; i < AMOUNT_POLYGON_BACK; i++)
	{
		pDevice->SetTexture(0, g_pTexture_Back);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//UI�̌��̍\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Back(void)
{
	SCORE* pScore = GetInfo_SCORE();
	TIMER* pTimer = GetInfo_TIMER();

	for (int i = 0; i < AMOUNT_POLYGON_BACK; i++)
	{
		switch (i)
		{
		case 0:
			g_aBack[i].pos = pScore[0].pos;
			g_aBack[i].fRadius[0] = 430.0f;
			break;
		case 1:
			g_aBack[i].pos = pTimer[0].pos;
			g_aBack[i].fRadius[0] = 240.0f;
			break;
		}
		g_aBack[i].fRadius[1] = 55.0f;
	}
}

//************************************************
//UI�̌��̂̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Back(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Back;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Back->Lock(0, 0, (void**)&pVtx_Back, 0);

	for (int i = 0; i < AMOUNT_POLYGON_BACK; i++)
	{
		pVtx_Back[0].pos.x = g_aBack[i].pos.x - 40.0f;
		pVtx_Back[0].pos.y = g_aBack[i].pos.y - g_aBack[i].fRadius[1];
		pVtx_Back[1].pos.x = g_aBack[i].pos.x + g_aBack[i].fRadius[0] + 15.0f;
		pVtx_Back[1].pos.y = g_aBack[i].pos.y - g_aBack[i].fRadius[1];
		pVtx_Back[2].pos.x = g_aBack[i].pos.x - 55.0f;
		pVtx_Back[2].pos.y = g_aBack[i].pos.y + g_aBack[i].fRadius[1];
		pVtx_Back[3].pos.x = g_aBack[i].pos.x + g_aBack[i].fRadius[0];
		pVtx_Back[3].pos.y = g_aBack[i].pos.y + g_aBack[i].fRadius[1];

		pVtx_Back += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Back->Unlock();
}

//************************************************
//UI�̌��̂̍\���̂̃A�h���X��n��
//************************************************
BACK* GetInfo_Back(void)
{
	return &g_aBack[0];
}