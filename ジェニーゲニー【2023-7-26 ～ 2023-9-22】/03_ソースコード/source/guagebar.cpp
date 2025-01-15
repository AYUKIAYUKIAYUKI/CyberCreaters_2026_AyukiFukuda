//************************************************
//
//�Q�[�W�o�[�\������[guagebar.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "guagebar.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_GuageBar = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_GuageBar = NULL;	//���_�o�b�t�@�̃|�C���^

//************************************************
//�|���S�������������֐�
//************************************************
void Init_GuageBar()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GUAGEBAR,
		&g_pTexture_GuageBar);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_GuageBar,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_GuageBar;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_GuageBar->Lock(0, 0, (void**)&pVtx_GuageBar, 0);

	//���_���W�̏����ݒ�
	pVtx_GuageBar[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_GuageBar[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_GuageBar[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_GuageBar[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_GuageBar[0].rhw = 1.0f;
	pVtx_GuageBar[1].rhw = 1.0f;
	pVtx_GuageBar[2].rhw = 1.0f;
	pVtx_GuageBar[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_GuageBar[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_GuageBar[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_GuageBar[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_GuageBar[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_GuageBar[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_GuageBar[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_GuageBar[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_GuageBar[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_GuageBar->Unlock();

	//����Ɉ�x�|���S����W�J����
	SetPos_Vtx_GuageBar();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_GuageBar(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_GuageBar != NULL)
	{
		g_pTexture_GuageBar->Release();
		g_pTexture_GuageBar = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_GuageBar != NULL)
	{
		g_pVtxBuff_GuageBar->Release();
		g_pVtxBuff_GuageBar = NULL;
	}
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_GuageBar(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_GuageBar, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_GuageBar);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//���_��W�J����֐�
//************************************************
void SetPos_Vtx_GuageBar(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_GuageBar;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_GuageBar->Lock(0, 0, (void**)&pVtx_GuageBar, 0);

	pVtx_GuageBar[0].pos = D3DXVECTOR3(POS_X_LEFT_GUAGEBAR, POS_Y_UP_GUAGEBAR, 0.0f);
	pVtx_GuageBar[1].pos = D3DXVECTOR3(POS_X_RIGHT_GUAGEBAR, POS_Y_UP_GUAGEBAR, 0.0f);
	pVtx_GuageBar[2].pos = D3DXVECTOR3(POS_X_LEFT_GUAGEBAR, POS_Y_DOWN_GUAGEBAR, 0.0f);
	pVtx_GuageBar[3].pos = D3DXVECTOR3(POS_X_RIGHT_GUAGEBAR, POS_Y_DOWN_GUAGEBAR, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_GuageBar->Unlock();
}