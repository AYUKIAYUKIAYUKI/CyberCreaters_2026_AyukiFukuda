//************************************************
//
//���U���g�e�L�X�g����[logo_title.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "score.h"
#include "text_result.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Text_Result = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Text_Result = NULL;	//���_�o�b�t�@�̃|�C���^
TEXT_RESULT g_aText_Result;	//���U���g�e�L�X�g���

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Text_Result()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_RESULT,
		&g_pTexture_Text_Result);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Text_Result,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Text_Result;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Text_Result->Lock(0, 0, (void**)&pVtx_Text_Result, 0);

	//���_���W�̏����ݒ�
	pVtx_Text_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Text_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Text_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Text_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Text_Result[0].rhw = 1.0f;
	pVtx_Text_Result[1].rhw = 1.0f;
	pVtx_Text_Result[2].rhw = 1.0f;
	pVtx_Text_Result[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Text_Result[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Text_Result[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Text_Result[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Text_Result[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Text_Result[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Text_Result[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Text_Result[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Text_Result[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Text_Result->Unlock();

	//�w�i�\���̂̏��̏������Q
	g_aText_Result.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aText_Result.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aText_Result.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aText_Result.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aText_Result.fRadius[nCnt] = 0.0f;
	}
	g_aText_Result.fLength = 0.0f;
	g_aText_Result.fAngle = 0.0f;

	//�w�i�\���̂ɏ���t�^
	SetInfo_Text_Result();

	//�ʒu�Ɋ�Â��|���S����W�J
	Update_Pos_Text_Result();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Text_Result(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Text_Result != NULL)
	{
		g_pTexture_Text_Result->Release();
		g_pTexture_Text_Result = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Text_Result != NULL)
	{
		g_pVtxBuff_Text_Result->Release();
		g_pVtxBuff_Text_Result = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Text_Result(void)
{

}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Text_Result(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Text_Result, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Text_Result);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//���U���g�e�L�X�g�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Text_Result(void)
{
	SCORE* pSCORE = GetInfo_SCORE();

	g_aText_Result.pos = pSCORE->pos;
	g_aText_Result.pos.x -= 425.0f;
	g_aText_Result.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aText_Result.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aText_Result.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aText_Result.fRadius[0] = 350.0f;
	g_aText_Result.fRadius[1] = 100.0f;
	g_aText_Result.fLength = sqrtf((g_aText_Result.fRadius[0] * g_aText_Result.fRadius[0]) + (g_aText_Result.fRadius[1] * g_aText_Result.fRadius[1]));
	g_aText_Result.fAngle = atan2f(g_aText_Result.fRadius[0] * 2.0f, g_aText_Result.fRadius[1] * 2.0f);
}

//************************************************
//���U���g�e�L�X�g�̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Text_Result(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Text_Result;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Text_Result->Lock(0, 0, (void**)&pVtx_Text_Result, 0);

	pVtx_Text_Result[0].pos.x = g_aText_Result.pos.x + sinf(g_aText_Result.rot.z - (D3DX_PI - g_aText_Result.fAngle)) * g_aText_Result.fLength;
	pVtx_Text_Result[0].pos.y = g_aText_Result.pos.y + cosf(g_aText_Result.rot.z - (D3DX_PI - g_aText_Result.fAngle)) * g_aText_Result.fLength;
	pVtx_Text_Result[1].pos.x = g_aText_Result.pos.x + sinf(g_aText_Result.rot.z + (D3DX_PI - g_aText_Result.fAngle)) * g_aText_Result.fLength;
	pVtx_Text_Result[1].pos.y = g_aText_Result.pos.y + cosf(g_aText_Result.rot.z + (D3DX_PI - g_aText_Result.fAngle)) * g_aText_Result.fLength;
	pVtx_Text_Result[2].pos.x = g_aText_Result.pos.x + sinf(g_aText_Result.rot.z - g_aText_Result.fAngle) * g_aText_Result.fLength;
	pVtx_Text_Result[2].pos.y = g_aText_Result.pos.y + cosf(g_aText_Result.rot.z - g_aText_Result.fAngle) * g_aText_Result.fLength;
	pVtx_Text_Result[3].pos.x = g_aText_Result.pos.x + sinf(g_aText_Result.rot.z + g_aText_Result.fAngle) * g_aText_Result.fLength;
	pVtx_Text_Result[3].pos.y = g_aText_Result.pos.y + cosf(g_aText_Result.rot.z + g_aText_Result.fAngle) * g_aText_Result.fLength;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Text_Result->Unlock();
}

//************************************************
//���U���g�e�L�X�g�\���̂̃A�h���X��n��
//************************************************
TEXT_RESULT* GetInfo_Text_Result(void)
{
	return &g_aText_Result;
}