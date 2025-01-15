//************************************************
//
//���C�t�\�L(int nLife�Ƃ�������̈����v�C��)[life.cpp]
//Author�F���c����
//
//************************************************
#include "input.h"
#include "main.h"
#include "sound.h"
#include "life.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Life = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Life = NULL;	//���_�o�b�t�@�̃|�C���^
float g_fTexU_Life = 0.0f;				//���C�t�e�N�X�`���p
float g_fTexV_Life = TEX_V_DOWN_LIFE;	//����

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Life(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_HEARTS_LIFE,
		&g_pTexture_Life);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Life,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Life;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Life->Lock(0, 0, (void**)&pVtx_Life, 0);

	//���_���W�̏����ݒ�
	pVtx_Life[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Life[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Life[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Life[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Life[0].rhw = 1.0f;
	pVtx_Life[1].rhw = 1.0f;
	pVtx_Life[2].rhw = 1.0f;
	pVtx_Life[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Life[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Life[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Life[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Life[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Life[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Life[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Life[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Life[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Life->Unlock();

	//���C�t�e�N�X�`���p�ϐ�������
	g_fTexU_Life = 0.0f;
	g_fTexV_Life = TEX_V_DOWN_LIFE;

	//����Ɉ�x�|���S����W�J����
	SetPos_Vtx_Life();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Life(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Life != NULL)
	{
		g_pTexture_Life->Release();
		g_pTexture_Life = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Life != NULL)
	{
		g_pVtxBuff_Life->Release();
		g_pVtxBuff_Life = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�(��e��񕜎�)
//************************************************
void Update_Life(int nLife)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Life;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Life->Lock(0, 0, (void**)&pVtx_Life, 0);

	//���C�t���ɍ��킹�ăe�N�X�`���ω�
	switch (nLife)
	{
	case AMOUNT_LIFE_0:

		g_fTexU_Life = MOVE_SPAN_TEX_LIFE * 5;
		g_fTexV_Life = MOVE_SPAN_TEX_LIFE * 5 + TEX_V_DOWN_LIFE;

		break;

	case AMOUNT_LIFE_1:

		g_fTexU_Life = MOVE_SPAN_TEX_LIFE * 4;
		g_fTexV_Life = MOVE_SPAN_TEX_LIFE * 4 + TEX_V_DOWN_LIFE;

		break;

	case AMOUNT_LIFE_2:

		g_fTexU_Life = MOVE_SPAN_TEX_LIFE * 3;
		g_fTexV_Life = MOVE_SPAN_TEX_LIFE * 3 + TEX_V_DOWN_LIFE;

		break;

	case AMOUNT_LIFE_3:

		g_fTexU_Life = MOVE_SPAN_TEX_LIFE * 2;
		g_fTexV_Life = MOVE_SPAN_TEX_LIFE * 2 + TEX_V_DOWN_LIFE;

		break;

	case AMOUNT_LIFE_4:

		g_fTexU_Life = MOVE_SPAN_TEX_LIFE;
		g_fTexV_Life = MOVE_SPAN_TEX_LIFE + TEX_V_DOWN_LIFE;

		break;

	case AMOUNT_LIFE_MAX:

		g_fTexU_Life = 0.0f;
		g_fTexV_Life = TEX_V_DOWN_LIFE;

		break;
	}

	//�e�N�X�`�����W�̐ݒ�
	pVtx_Life[0].tex = D3DXVECTOR2(0.0f, g_fTexU_Life);
	pVtx_Life[1].tex = D3DXVECTOR2(1.0f, g_fTexU_Life);
	pVtx_Life[2].tex = D3DXVECTOR2(0.0f, g_fTexV_Life);
	pVtx_Life[3].tex = D3DXVECTOR2(1.0f, g_fTexV_Life);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Life->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Life(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Life, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Life);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//���_��W�J����֐�
//************************************************
void SetPos_Vtx_Life(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Life;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Life->Lock(0, 0, (void**)&pVtx_Life, 0);

	pVtx_Life[0].pos = D3DXVECTOR3(POS_X_LEFT_LIFE, POS_Y_UP_LIFE, 0.0f);
	pVtx_Life[1].pos = D3DXVECTOR3(POS_X_RIGHT_LIFE, POS_Y_UP_LIFE, 0.0f);
	pVtx_Life[2].pos = D3DXVECTOR3(POS_X_LEFT_LIFE, POS_Y_DOWN_LIFE, 0.0f);
	pVtx_Life[3].pos = D3DXVECTOR3(POS_X_RIGHT_LIFE, POS_Y_DOWN_LIFE, 0.0f);

	pVtx_Life[0].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx_Life[1].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx_Life[2].col = D3DCOLOR_RGBA(255, 255, 255, 200);
	pVtx_Life[3].col = D3DCOLOR_RGBA(255, 255, 255, 200);

	pVtx_Life[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Life[1].tex = D3DXVECTOR2(TEX_U_RIGHT_LIFE, 0.0f);
	pVtx_Life[2].tex = D3DXVECTOR2(0.0f, TEX_V_DOWN_LIFE);
	pVtx_Life[3].tex = D3DXVECTOR2(TEX_U_RIGHT_LIFE, TEX_V_DOWN_LIFE);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Life->Unlock();
}