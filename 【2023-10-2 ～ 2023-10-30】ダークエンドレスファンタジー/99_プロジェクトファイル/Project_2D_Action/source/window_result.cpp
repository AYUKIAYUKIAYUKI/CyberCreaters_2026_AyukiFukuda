//************************************************
//
//�E�B���h�E���U���g����[window_menu.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "result.h"
#include "window_result.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Window_Result[AMOUNT_TEX_WINDOW_RESULT] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Window_Result = NULL;	//���_�o�b�t�@�̃|�C���^
WINDOW_RESULT g_aWindow_Result;	//�E�B���h�E���U���g���

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Window_Result()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WINDOW_RESULT1,
		&g_pTexture_Window_Result[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WINDOW_RESULT2
		,
		&g_pTexture_Window_Result[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Window_Result,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Window_Result;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Window_Result->Lock(0, 0, (void**)&pVtx_Window_Result, 0);

	//���_���W�̏����ݒ�
	pVtx_Window_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Window_Result[0].rhw = 1.0f;
	pVtx_Window_Result[1].rhw = 1.0f;
	pVtx_Window_Result[2].rhw = 1.0f;
	pVtx_Window_Result[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Window_Result[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Window_Result[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Window_Result[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Window_Result[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Window_Result[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Window_Result[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Window_Result[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Window_Result[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Window_Result->Unlock();

	//�E�B���h�E���U���g�\���̂̏��̏������Q
	g_aWindow_Result.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Result.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Result.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Result.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aWindow_Result.fRadius[nCnt] = 0.0f;
		g_aWindow_Result.fLength[nCnt] = 0.0f;
		g_aWindow_Result.fAngle[nCnt] = 0.0f;
	}

	//�E�B���h�E���U���g�\���̂ɏ���t�^
	SetInfo_Window_Result();

	//�ʒu�Ɋ�Â��|���S����W�J
	Update_Pos_Window_Result();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Window_Result(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < AMOUNT_TEX_WINDOW_RESULT; i++)
	{
		if (g_pTexture_Window_Result[i] != NULL)
		{
			g_pTexture_Window_Result[i]->Release();
			g_pTexture_Window_Result[i] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Window_Result != NULL)
	{
		g_pVtxBuff_Window_Result->Release();
		g_pVtxBuff_Window_Result = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Window_Result(void)
{

}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Window_Result(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Window_Result, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	bool* pCLEAR = GetInfo_CLEAR();

	//�e�N�X�`���̐ݒ�
	if (*pCLEAR)
	{
		pDevice->SetTexture(0, g_pTexture_Window_Result[0]);
	}
	else
	{
		pDevice->SetTexture(0, g_pTexture_Window_Result[1]);
	}

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//�E�B���h�E���U���g�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Window_Result(void)
{
	g_aWindow_Result.pos = D3DXVECTOR3(990.0f, 290.0f, 0.0f);
	g_aWindow_Result.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Result.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Result.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aWindow_Result.fRadius[0] = RADIUS_WINDOW_RESULT_X;	//������
	g_aWindow_Result.fRadius[1] = RADIUS_WINDOW_RESULT_Y;	//�c����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aWindow_Result.fLength[nCnt] = sqrtf((g_aWindow_Result.fRadius[0] * g_aWindow_Result.fRadius[0]) + (g_aWindow_Result.fRadius[1] * g_aWindow_Result.fRadius[1]));
		g_aWindow_Result.fAngle[nCnt] = atan2f(g_aWindow_Result.fRadius[0] * 2.0f, g_aWindow_Result.fRadius[1] * 2.0f);
	}
}

//************************************************
//�E�B���h�E���U���g�̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Window_Result(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Window_Result;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Window_Result->Lock(0, 0, (void**)&pVtx_Window_Result, 0);

	pVtx_Window_Result[0].pos.x = g_aWindow_Result.pos.x + sinf(g_aWindow_Result.rot.z - (D3DX_PI - g_aWindow_Result.fAngle[0])) * g_aWindow_Result.fLength[0];
	pVtx_Window_Result[0].pos.y = g_aWindow_Result.pos.y + cosf(g_aWindow_Result.rot.z - (D3DX_PI - g_aWindow_Result.fAngle[0])) * g_aWindow_Result.fLength[0];
	pVtx_Window_Result[1].pos.x = g_aWindow_Result.pos.x + sinf(g_aWindow_Result.rot.z + (D3DX_PI - g_aWindow_Result.fAngle[0])) * g_aWindow_Result.fLength[0];
	pVtx_Window_Result[1].pos.y = g_aWindow_Result.pos.y + cosf(g_aWindow_Result.rot.z + (D3DX_PI - g_aWindow_Result.fAngle[0])) * g_aWindow_Result.fLength[0];
	pVtx_Window_Result[2].pos.x = g_aWindow_Result.pos.x + sinf(g_aWindow_Result.rot.z - g_aWindow_Result.fAngle[0]) * g_aWindow_Result.fLength[0];
	pVtx_Window_Result[2].pos.y = g_aWindow_Result.pos.y + cosf(g_aWindow_Result.rot.z - g_aWindow_Result.fAngle[0]) * g_aWindow_Result.fLength[0];
	pVtx_Window_Result[3].pos.x = g_aWindow_Result.pos.x + sinf(g_aWindow_Result.rot.z + g_aWindow_Result.fAngle[0]) * g_aWindow_Result.fLength[0];
	pVtx_Window_Result[3].pos.y = g_aWindow_Result.pos.y + cosf(g_aWindow_Result.rot.z + g_aWindow_Result.fAngle[0]) * g_aWindow_Result.fLength[0];

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Window_Result->Unlock();
}

//************************************************
//�E�B���h�E���U���g�\���̂̃A�h���X��n��
//************************************************
WINDOW_RESULT* GetInfo_Window_Result(void)
{
	return &g_aWindow_Result;
}