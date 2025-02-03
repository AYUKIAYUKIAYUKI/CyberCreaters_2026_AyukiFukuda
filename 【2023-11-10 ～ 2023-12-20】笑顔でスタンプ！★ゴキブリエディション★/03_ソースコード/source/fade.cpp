//************************************************
//
//�t�F�[�h����[fade.cpp]
//Author�F���c����
//
//************************************************
#include "fade.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Fade = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Fade = NULL;	//���_�o�b�t�@�̃|�C���^
FADE g_aFade;	//�t�F�[�h���

//************************************************
//�|���S�������������֐�
//************************************************
void InitFade()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_FADE,
		&g_pTexture_Fade);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Fade,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Fade;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Fade->Lock(0, 0, (void**)&pVtx_Fade, 0);

	//���_���W�̏����ݒ�
	pVtx_Fade[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Fade[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Fade[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Fade[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Fade[0].rhw = 1.0f;
	pVtx_Fade[1].rhw = 1.0f;
	pVtx_Fade[2].rhw = 1.0f;
	pVtx_Fade[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Fade[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Fade[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Fade[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Fade[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Fade[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Fade[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Fade[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Fade[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Fade->Unlock();

	//�t�F�[�h�\���̂̏��̏������Q
	g_aFade.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aFade.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aFade.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aFade.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aFade.fRadius[nCnt] = 0.0f;
	}
	g_aFade.fLength = 0.0f;
	g_aFade.fAngle = 0.0f;
	g_aFade.bFadeIn = false;
	g_aFade.bFadeOut = false;

	//�t�F�[�h�\���̂ɏ���t�^
	SetInfoFade();

	//�ʒu�Ɋ�Â��|���S����W�J
	UpdatePosFade();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void UninitFade(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Fade != NULL)
	{
		g_pTexture_Fade->Release();
		g_pTexture_Fade = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Fade != NULL)
	{
		g_pVtxBuff_Fade->Release();
		g_pVtxBuff_Fade = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void UpdateFade(void)
{
	if (g_aFade.bFadeIn)
	{
		if (g_aFade.col.a > -0.1f)
		{
			UpdateColFade();
		}
	}
	else if (g_aFade.bFadeOut)
	{
		if (g_aFade.col.a < 1.1f)
		{
			UpdateColFade();
		}
	}
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void DrawFade(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Fade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Fade);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//�t�F�[�h�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfoFade(void)
{
	g_aFade.pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
	g_aFade.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aFade.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aFade.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aFade.fRadius[0] = RADIUS_FADE_X;	//�t�F�[�h������
	g_aFade.fRadius[1] = RADIUS_FADE_Y;	//�t�F�[�h�c����
	g_aFade.fLength = sqrtf((g_aFade.fRadius[0] * g_aFade.fRadius[0]) + (g_aFade.fRadius[1] * g_aFade.fRadius[1]));
	g_aFade.fAngle = atan2f(g_aFade.fRadius[0] * 2.0f, g_aFade.fRadius[1] * 2.0f);
}

//************************************************
//�t�F�[�h�̈ʒu��ݒ肷��֐�
//************************************************
void UpdatePosFade(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Fade;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Fade->Lock(0, 0, (void**)&pVtx_Fade, 0);

	pVtx_Fade[0].pos.x = g_aFade.pos.x + sinf(g_aFade.rot.z - (D3DX_PI - g_aFade.fAngle)) * g_aFade.fLength;
	pVtx_Fade[0].pos.y = g_aFade.pos.y + cosf(g_aFade.rot.z - (D3DX_PI - g_aFade.fAngle)) * g_aFade.fLength;
	pVtx_Fade[1].pos.x = g_aFade.pos.x + sinf(g_aFade.rot.z + (D3DX_PI - g_aFade.fAngle)) * g_aFade.fLength;
	pVtx_Fade[1].pos.y = g_aFade.pos.y + cosf(g_aFade.rot.z + (D3DX_PI - g_aFade.fAngle)) * g_aFade.fLength;
	pVtx_Fade[2].pos.x = g_aFade.pos.x + sinf(g_aFade.rot.z - g_aFade.fAngle) * g_aFade.fLength;
	pVtx_Fade[2].pos.y = g_aFade.pos.y + cosf(g_aFade.rot.z - g_aFade.fAngle) * g_aFade.fLength;
	pVtx_Fade[3].pos.x = g_aFade.pos.x + sinf(g_aFade.rot.z + g_aFade.fAngle) * g_aFade.fLength;
	pVtx_Fade[3].pos.y = g_aFade.pos.y + cosf(g_aFade.rot.z + g_aFade.fAngle) * g_aFade.fLength;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Fade->Unlock();
}

//************************************************
//�t�F�[�h�̐F��ݒ肷��֐�
//************************************************
void UpdateColFade(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Fade;

	if (g_aFade.bFadeIn)
	{
		g_aFade.col.a -= SPD_CHANGE_COL_FADE;
	}
	else if (g_aFade.bFadeOut)
	{
		g_aFade.col.a += SPD_CHANGE_COL_FADE;
	}

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Fade->Lock(0, 0, (void**)&pVtx_Fade, 0);

	//�F�𔽉f
	pVtx_Fade[0].col = g_aFade.col;
	pVtx_Fade[1].col = g_aFade.col;
	pVtx_Fade[2].col = g_aFade.col;
	pVtx_Fade[3].col = g_aFade.col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Fade->Unlock();
}

//************************************************
//�t�F�[�h�\���̂̃A�h���X��n��
//************************************************
FADE* GetInfoFade(void)
{
	return &g_aFade;
}