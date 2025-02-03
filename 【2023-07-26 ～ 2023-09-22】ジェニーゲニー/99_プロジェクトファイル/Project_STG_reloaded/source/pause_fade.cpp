//************************************************
//
//�|�[�Y�t�F�[�h����[pause_fade.cpp]
//Author�F���c����
//
//************************************************
#include "pause.h"
#include "pause_fade.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Pause_Fade[AMOUNT_TEXTURE_PAUSE_FADE] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Pause_Fade = NULL;	//���_�o�b�t�@�̃|�C���^
PAUSE_FADE g_aPause_Fade[AMOUNT_POLYGON_PAUSE_FADE];	//�|���S���̏����i�[

//************************************************
//�����������֐�
//************************************************
void Init_Pause_Fade(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLACK_PAUSE_FADE,
		&g_pTexture_Pause_Fade[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_PAUSE_FADE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Pause_Fade,
		NULL);

	////���_���ւ̃|�C���^
	//VERTEX_2D* pVtx_Pause_Fade;

	////���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	//g_pVtxBuff_Pause_Fade->Lock(0, 0, (void**)&pVtx_Pause_Fade, 0);

	////�����ݒ�
	//for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_FADE; nCnt++)
	//{
	//	//���_���W�̏����ݒ�
	//	pVtx_Pause_Fade[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	pVtx_Pause_Fade[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	pVtx_Pause_Fade[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	pVtx_Pause_Fade[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	//������̊g�嗦(?)�̏����ݒ�
	//	pVtx_Pause_Fade[0].rhw = 1.0f;
	//	pVtx_Pause_Fade[1].rhw = 1.0f;
	//	pVtx_Pause_Fade[2].rhw = 1.0f;
	//	pVtx_Pause_Fade[3].rhw = 1.0f;

	//	//���_�J���[�̏����ݒ�
	//	pVtx_Pause_Fade[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	pVtx_Pause_Fade[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	pVtx_Pause_Fade[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//	pVtx_Pause_Fade[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//	//�e�N�X�`�����W�̏����ݒ�
	//	pVtx_Pause_Fade[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx_Pause_Fade[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx_Pause_Fade[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx_Pause_Fade[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//	pVtx_Pause_Fade += AMOUNT_VTX;
	//}

	////���_�o�b�t�@���A�����b�N����
	//g_pVtxBuff_Pause_Fade->Unlock();

	////�����ݒ�
	//for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_FADE; nCnt++)
	//{
	//	g_aPause_Fade[nCnt].nStyle = 0;
	//	g_aPause_Fade[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_aPause_Fade[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_aPause_Fade[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//	g_aPause_Fade[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	//	g_aPause_Fade[nCnt].fLength = 0.0f;
	//	g_aPause_Fade[nCnt].fAngle = 0.0f;
	//}

	//����̂ݒ��_��W�J
	Setinfo_Pause_Fade();
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Pause_Fade(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_PAUSE_FADE; nCnt++)
	{
		if (g_pTexture_Pause_Fade[nCnt] != NULL)
		{
			g_pTexture_Pause_Fade[nCnt]->Release();
			g_pTexture_Pause_Fade[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Pause_Fade != NULL)
	{
		g_pVtxBuff_Pause_Fade->Release();
		g_pVtxBuff_Pause_Fade = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Pause_Fade(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Pause_Fade;

	bool* pStart_M;
	pStart_M = Getinfo_Return_Pause();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Pause_Fade->Lock(0, 0, (void**)&pVtx_Pause_Fade, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_FADE; nCnt++)
	{
		//�ړ��A��]�𔽉f
		pVtx_Pause_Fade[0].pos.x = g_aPause_Fade[nCnt].pos.x + sinf(g_aPause_Fade[nCnt].rot.z - (D3DX_PI - g_aPause_Fade[nCnt].fAngle)) * g_aPause_Fade[nCnt].fLength;
		pVtx_Pause_Fade[0].pos.y = g_aPause_Fade[nCnt].pos.y + cosf(g_aPause_Fade[nCnt].rot.z - (D3DX_PI - g_aPause_Fade[nCnt].fAngle)) * g_aPause_Fade[nCnt].fLength;
		pVtx_Pause_Fade[1].pos.x = g_aPause_Fade[nCnt].pos.x + sinf(g_aPause_Fade[nCnt].rot.z + (D3DX_PI - g_aPause_Fade[nCnt].fAngle)) * g_aPause_Fade[nCnt].fLength;
		pVtx_Pause_Fade[1].pos.y = g_aPause_Fade[nCnt].pos.y + cosf(g_aPause_Fade[nCnt].rot.z + (D3DX_PI - g_aPause_Fade[nCnt].fAngle)) * g_aPause_Fade[nCnt].fLength;
		pVtx_Pause_Fade[2].pos.x = g_aPause_Fade[nCnt].pos.x + sinf(g_aPause_Fade[nCnt].rot.z - g_aPause_Fade[nCnt].fAngle) * g_aPause_Fade[nCnt].fLength;
		pVtx_Pause_Fade[2].pos.y = g_aPause_Fade[nCnt].pos.y + cosf(g_aPause_Fade[nCnt].rot.z - g_aPause_Fade[nCnt].fAngle) * g_aPause_Fade[nCnt].fLength;
		pVtx_Pause_Fade[3].pos.x = g_aPause_Fade[nCnt].pos.x + sinf(g_aPause_Fade[nCnt].rot.z + g_aPause_Fade[nCnt].fAngle) * g_aPause_Fade[nCnt].fLength;
		pVtx_Pause_Fade[3].pos.y = g_aPause_Fade[nCnt].pos.y + cosf(g_aPause_Fade[nCnt].rot.z + g_aPause_Fade[nCnt].fAngle) * g_aPause_Fade[nCnt].fLength;

		if (*pStart_M == false)
		{
			g_aPause_Fade[nCnt].col.a -= 0.05f;

			if (g_aPause_Fade[nCnt].col.a < 0.0f)
			{
				g_aPause_Fade[nCnt].col.a = 0.0f;
			}
		}
		else
		{
			g_aPause_Fade[nCnt].col.a += 0.1f;
		}

		pVtx_Pause_Fade[0].col = g_aPause_Fade[nCnt].col;
		pVtx_Pause_Fade[1].col = g_aPause_Fade[nCnt].col;
		pVtx_Pause_Fade[2].col = g_aPause_Fade[nCnt].col;
		pVtx_Pause_Fade[3].col = g_aPause_Fade[nCnt].col;

		pVtx_Pause_Fade += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Pause_Fade->Unlock();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Pause_Fade(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Pause_Fade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_PAUSE_FADE; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Pause_Fade[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Pause_Fade(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_FADE; nCnt++)
	{
		g_aPause_Fade[nCnt].nStyle = 0;
		g_aPause_Fade[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
		g_aPause_Fade[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Fade[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Fade[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPause_Fade[nCnt].fLength = sqrtf((990.0f * 990.0f) + (540.0f * 540.0f));
		g_aPause_Fade[nCnt].fAngle = atan2f(990.0f * 2.0f, 540.0f * 2.0f);
	}
}

//************************************************
//�|���S�����𑗂�֐�
//************************************************
float* Getinfo_Pause_Fade(void)
{
	return &g_aPause_Fade[0].col.a;
}