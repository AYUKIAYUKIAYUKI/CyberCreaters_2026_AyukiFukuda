//************************************************
//
//�Ñ�����[press_any.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "press_any.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Press_Any[AMOUNT_TEX_PRESS_ANY] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Press_Any = NULL;	//���_�o�b�t�@�̃|�C���^
PRESS_ANY g_aPress_Any;	//�Ñ����
static float g_F;	//�ėp��������

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Press_Any(int nMode)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PRESS_ANY_MENU,
		&g_pTexture_Press_Any[PRESS_TYPE_MENU]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PRESS_ANY_RESULT,
		&g_pTexture_Press_Any[PRESS_TYPE_RESULT]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Press_Any,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Press_Any;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Press_Any->Lock(0, 0, (void**)&pVtx_Press_Any, 0);

	//���_���W�̏����ݒ�
	pVtx_Press_Any[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Press_Any[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Press_Any[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Press_Any[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Press_Any[0].rhw = 1.0f;
	pVtx_Press_Any[1].rhw = 1.0f;
	pVtx_Press_Any[2].rhw = 1.0f;
	pVtx_Press_Any[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Press_Any[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Press_Any[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Press_Any[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Press_Any[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Press_Any[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Press_Any[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Press_Any[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Press_Any[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Press_Any->Unlock();

	//�w�i�\���̂̏��̏������Q
	g_aPress_Any.nType = nMode;
	g_aPress_Any.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPress_Any.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPress_Any.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPress_Any.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aPress_Any.fRadius[nCnt] = 0.0f;
	}
	g_aPress_Any.fLength = 0.0f;
	g_aPress_Any.fAngle = 0.0f;

	g_F = 0.01f;

	//�w�i�\���̂ɏ���t�^
	SetInfo_Press_Any();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Press_Any(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEX_PRESS_ANY; nCnt++)
	{
		if (g_pTexture_Press_Any[nCnt] != NULL)
		{
			g_pTexture_Press_Any[nCnt]->Release();
			g_pTexture_Press_Any[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Press_Any != NULL)
	{
		g_pVtxBuff_Press_Any->Release();
		g_pVtxBuff_Press_Any = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Press_Any(void)
{
	//�W�J
	Update_Pos_Press_Any();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Press_Any(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Press_Any, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	switch (g_aPress_Any.nType)
	{
	case PRESS_TYPE_MENU:
		pDevice->SetTexture(0, g_pTexture_Press_Any[PRESS_TYPE_MENU]);
		break;
	case PRESS_TYPE_RESULT:
		pDevice->SetTexture(0, g_pTexture_Press_Any[PRESS_TYPE_RESULT]);
		break;
	}

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//�Ñ��\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Press_Any(void)
{
	g_aPress_Any.pos = D3DXVECTOR3(990.0f, 900.0f, 0.0f);
	g_aPress_Any.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPress_Any.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPress_Any.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aPress_Any.fRadius[0] = 400.0f;
	g_aPress_Any.fRadius[1] = 100.0f;
	g_aPress_Any.fLength = sqrtf((g_aPress_Any.fRadius[0] * g_aPress_Any.fRadius[0]) + (g_aPress_Any.fRadius[1] * g_aPress_Any.fRadius[1]));
	g_aPress_Any.fAngle = atan2f(g_aPress_Any.fRadius[0] * 2.0f, g_aPress_Any.fRadius[1] * 2.0f);
}

//************************************************
//�Ñ��̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Press_Any(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Press_Any;

	//�F�ύX
	Update_Col_Press_Any();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Press_Any->Lock(0, 0, (void**)&pVtx_Press_Any, 0);

	pVtx_Press_Any[0].pos.x = g_aPress_Any.pos.x + sinf(g_aPress_Any.rot.z - (D3DX_PI - g_aPress_Any.fAngle)) * g_aPress_Any.fLength;
	pVtx_Press_Any[0].pos.y = g_aPress_Any.pos.y + cosf(g_aPress_Any.rot.z - (D3DX_PI - g_aPress_Any.fAngle)) * g_aPress_Any.fLength;
	pVtx_Press_Any[1].pos.x = g_aPress_Any.pos.x + sinf(g_aPress_Any.rot.z + (D3DX_PI - g_aPress_Any.fAngle)) * g_aPress_Any.fLength;
	pVtx_Press_Any[1].pos.y = g_aPress_Any.pos.y + cosf(g_aPress_Any.rot.z + (D3DX_PI - g_aPress_Any.fAngle)) * g_aPress_Any.fLength;
	pVtx_Press_Any[2].pos.x = g_aPress_Any.pos.x + sinf(g_aPress_Any.rot.z - g_aPress_Any.fAngle) * g_aPress_Any.fLength;
	pVtx_Press_Any[2].pos.y = g_aPress_Any.pos.y + cosf(g_aPress_Any.rot.z - g_aPress_Any.fAngle) * g_aPress_Any.fLength;
	pVtx_Press_Any[3].pos.x = g_aPress_Any.pos.x + sinf(g_aPress_Any.rot.z + g_aPress_Any.fAngle) * g_aPress_Any.fLength;
	pVtx_Press_Any[3].pos.y = g_aPress_Any.pos.y + cosf(g_aPress_Any.rot.z + g_aPress_Any.fAngle) * g_aPress_Any.fLength;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Press_Any->Unlock();
}

//************************************************
//�Ñ��̐F��ύX����֐�
//************************************************
void Update_Col_Press_Any(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Press_Any;

	g_aPress_Any.col.a -= g_F;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Press_Any->Lock(0, 0, (void**)&pVtx_Press_Any, 0);

	pVtx_Press_Any[0].col = g_aPress_Any.col;
	pVtx_Press_Any[1].col = g_aPress_Any.col;
	pVtx_Press_Any[2].col = g_aPress_Any.col;
	pVtx_Press_Any[3].col = g_aPress_Any.col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Press_Any->Unlock();

	//����
	if (g_aPress_Any.col.a < 0.0f || g_aPress_Any.col.a > 1.0f)
	{
		g_F *= -1.0f;
	}
}

//************************************************
//�Ñ��\���̂̃A�h���X��n��
//************************************************
PRESS_ANY* GetInfo_Press_Any(void)
{
	return &g_aPress_Any;
}