//************************************************
//
//�Q�[�W�\������[guage.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "guage.h"
#include "player.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Guage = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Guage = NULL;	//���_�o�b�t�@�̃|�C���^

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Guage()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GUAGE,
		&g_pTexture_Guage);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Guage,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Guage;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Guage->Lock(0, 0, (void**)&pVtx_Guage, 0);

	//���_���W�̏����ݒ�
	pVtx_Guage[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Guage[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Guage[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Guage[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Guage[0].rhw = 1.0f;
	pVtx_Guage[1].rhw = 1.0f;
	pVtx_Guage[2].rhw = 1.0f;
	pVtx_Guage[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Guage[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Guage[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Guage[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Guage[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Guage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Guage[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Guage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Guage[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Guage->Unlock();

	//����Ɉ�x�|���S����W�J����
	SetPos_Vtx_Guage();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Guage(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Guage != NULL)
	{
		g_pTexture_Guage->Release();
		g_pTexture_Guage = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Guage != NULL)
	{
		g_pVtxBuff_Guage->Release();
		g_pVtxBuff_Guage = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Guage(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Guage;

	//�v���C���[���ւ̃|�C���^
	PLAYER* pPlayer;

	//�v���C���[���̎擾
	pPlayer = Getinfo_Player();	//�v���C���[���n�̐擪�A�h���X����������

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Guage->Lock(0, 0, (void**)&pVtx_Guage, 0);

	//�L���p�ʓ�����̃Q�[�W���ʂ��Z�o
	float fNowCapacityPolygon = (pPlayer->nCapacity - AMOUNT_CAPACITY_PLAYER) * DIVIDE_POLYGON_GUAGE;	//�|���S���̒������L���p�̗ʁ��W��
	float fNowCapacityTexture = (pPlayer->nCapacity - AMOUNT_CAPACITY_PLAYER) * DIVIDE_TEXTURE_GUAGE;	//�e�N�X�`���̒������L���p�̗ʁ��W��

	//�|���S���L�k
	pVtx_Guage[0].pos = D3DXVECTOR3(POS_X_LEFT_GUAGE, POS_Y_UP_GUAGE, 0.0f);
	pVtx_Guage[1].pos = D3DXVECTOR3(POS_X_RIGHT_GUAGE + fNowCapacityPolygon, POS_Y_UP_GUAGE, 0.0f);
	pVtx_Guage[2].pos = D3DXVECTOR3(POS_X_LEFT_GUAGE, POS_Y_DOWN_GUAGE, 0.0f);
	pVtx_Guage[3].pos = D3DXVECTOR3(POS_X_RIGHT_GUAGE + fNowCapacityPolygon, POS_Y_DOWN_GUAGE, 0.0f);

	//�e�N�X�`���L�k
	pVtx_Guage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Guage[1].tex = D3DXVECTOR2(1.0f + fNowCapacityTexture, 0.0f);
	pVtx_Guage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Guage[3].tex = D3DXVECTOR2(1.0f + fNowCapacityTexture, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Guage->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Guage(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Guage, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Guage);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//���_��W�J����֐�
//************************************************
void SetPos_Vtx_Guage(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Guage;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Guage->Lock(0, 0, (void**)&pVtx_Guage, 0);

	pVtx_Guage[0].pos = D3DXVECTOR3(POS_X_LEFT_GUAGE, POS_Y_UP_GUAGE, 0.0f);
	pVtx_Guage[1].pos = D3DXVECTOR3(POS_X_RIGHT_GUAGE, POS_Y_UP_GUAGE, 0.0f);
	pVtx_Guage[2].pos = D3DXVECTOR3(POS_X_LEFT_GUAGE, POS_Y_DOWN_GUAGE, 0.0f);
	pVtx_Guage[3].pos = D3DXVECTOR3(POS_X_RIGHT_GUAGE, POS_Y_DOWN_GUAGE, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Guage->Unlock();
}