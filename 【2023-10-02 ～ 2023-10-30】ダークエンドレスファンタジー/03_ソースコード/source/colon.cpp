//************************************************
//
//�R��������[logo_title.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "colon.h"
#include "timer.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Colon = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Colon = NULL;	//���_�o�b�t�@�̃|�C���^
COLON g_aColon;	//�R�������

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Colon()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_COLON,
		&g_pTexture_Colon);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Colon,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Colon;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Colon->Lock(0, 0, (void**)&pVtx_Colon, 0);

	//���_���W�̏����ݒ�
	pVtx_Colon[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Colon[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Colon[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Colon[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Colon[0].rhw = 1.0f;
	pVtx_Colon[1].rhw = 1.0f;
	pVtx_Colon[2].rhw = 1.0f;
	pVtx_Colon[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Colon[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Colon[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Colon[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Colon[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Colon[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Colon[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Colon[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Colon[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Colon->Unlock();

	//�w�i�\���̂̏��̏������Q
	g_aColon.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aColon.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aColon.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aColon.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aColon.fRadius[nCnt] = 0.0f;
	}
	g_aColon.fLength = 0.0f;
	g_aColon.fAngle = 0.0f;

	//�w�i�\���̂ɏ���t�^
	SetInfo_Colon();

	//�ʒu�Ɋ�Â��|���S����W�J
	Update_Pos_Colon();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Colon(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Colon != NULL)
	{
		g_pTexture_Colon->Release();
		g_pTexture_Colon = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Colon != NULL)
	{
		g_pVtxBuff_Colon->Release();
		g_pVtxBuff_Colon = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Colon(void)
{

}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Colon(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Colon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Colon);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//�R�����\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Colon(void)
{
	TIMER* pTimer = GetInfo_TIMER();

	g_aColon.pos = pTimer[0].pos;
	g_aColon.pos.x += 100.0f;
	g_aColon.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aColon.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aColon.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aColon.fRadius[0] = 15.0f;
	g_aColon.fRadius[1] = 35.0f;
	g_aColon.fLength = sqrtf((g_aColon.fRadius[0] * g_aColon.fRadius[0]) + (g_aColon.fRadius[1] * g_aColon.fRadius[1]));
	g_aColon.fAngle = atan2f(g_aColon.fRadius[0] * 2.0f, g_aColon.fRadius[1] * 2.0f);
}

//************************************************
//�R�����̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Colon(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Colon;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Colon->Lock(0, 0, (void**)&pVtx_Colon, 0);

	pVtx_Colon[0].pos.x = g_aColon.pos.x + sinf(g_aColon.rot.z - (D3DX_PI - g_aColon.fAngle)) * g_aColon.fLength;
	pVtx_Colon[0].pos.y = g_aColon.pos.y + cosf(g_aColon.rot.z - (D3DX_PI - g_aColon.fAngle)) * g_aColon.fLength;
	pVtx_Colon[1].pos.x = g_aColon.pos.x + sinf(g_aColon.rot.z + (D3DX_PI - g_aColon.fAngle)) * g_aColon.fLength;
	pVtx_Colon[1].pos.y = g_aColon.pos.y + cosf(g_aColon.rot.z + (D3DX_PI - g_aColon.fAngle)) * g_aColon.fLength;
	pVtx_Colon[2].pos.x = g_aColon.pos.x + sinf(g_aColon.rot.z - g_aColon.fAngle) * g_aColon.fLength;
	pVtx_Colon[2].pos.y = g_aColon.pos.y + cosf(g_aColon.rot.z - g_aColon.fAngle) * g_aColon.fLength;
	pVtx_Colon[3].pos.x = g_aColon.pos.x + sinf(g_aColon.rot.z + g_aColon.fAngle) * g_aColon.fLength;
	pVtx_Colon[3].pos.y = g_aColon.pos.y + cosf(g_aColon.rot.z + g_aColon.fAngle) * g_aColon.fLength;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Colon->Unlock();
}

//************************************************
//�R�����\���̂̃A�h���X��n��
//************************************************
COLON* GetInfo_Colon(void)
{
	return &g_aColon;
}