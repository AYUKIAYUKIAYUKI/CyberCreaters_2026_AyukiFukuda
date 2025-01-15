//************************************************
//
//���j���[�t�F�[�h����[menu_fade.cpp]
//Author�F���c����
//
//************************************************
#include "fade.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Fade_Menu[AMOUNT_TEXTURE_FADE_MENU] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Fade_Menu = NULL;	//���_�o�b�t�@�̃|�C���^
FADE_MENU_OBJECT g_aFade_Menu[AMOUNT_POLYGON_FADE_MENU];	//���j���[�p�|���S���̏����i�[

//************************************************
//�����������֐�
//************************************************
void Init_Fade_Menu(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLACK_FADE_MENU,
		&g_pTexture_Fade_Menu[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_FADE_MENU,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Fade_Menu,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Fade_Menu;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Fade_Menu->Lock(0, 0, (void**)&pVtx_Fade_Menu, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FADE_MENU; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Fade_Menu[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Fade_Menu[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Fade_Menu[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Fade_Menu[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Fade_Menu[0].rhw = 1.0f;
		pVtx_Fade_Menu[1].rhw = 1.0f;
		pVtx_Fade_Menu[2].rhw = 1.0f;
		pVtx_Fade_Menu[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Fade_Menu[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Fade_Menu[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Fade_Menu[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Fade_Menu[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Fade_Menu[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Fade_Menu[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Fade_Menu[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Fade_Menu[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Fade_Menu += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Fade_Menu->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FADE_MENU; nCnt++)
	{
		g_aFade_Menu[nCnt].nStyle = 0;
		g_aFade_Menu[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFade_Menu[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFade_Menu[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFade_Menu[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aFade_Menu[nCnt].fLength = 0.0f;
		g_aFade_Menu[nCnt].fAngle = 0.0f;
	}

	//����̂ݒ��_��W�J
	Setinfo_Fade_Menu();
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Fade_Menu(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_FADE_MENU; nCnt++)
	{
		if (g_pTexture_Fade_Menu[nCnt] != NULL)
		{
			g_pTexture_Fade_Menu[nCnt]->Release();
			g_pTexture_Fade_Menu[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Fade_Menu != NULL)
	{
		g_pVtxBuff_Fade_Menu->Release();
		g_pVtxBuff_Fade_Menu = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Fade_Menu(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Fade_Menu;

	bool* pStart;
	pStart = Getinfo_Menu();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Fade_Menu->Lock(0, 0, (void**)&pVtx_Fade_Menu, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FADE_MENU; nCnt++)
	{
		//�ړ��A��]�𔽉f
		pVtx_Fade_Menu[0].pos.x = g_aFade_Menu[nCnt].pos.x + sinf(g_aFade_Menu[nCnt].rot.z - (D3DX_PI - g_aFade_Menu[nCnt].fAngle)) * g_aFade_Menu[nCnt].fLength;
		pVtx_Fade_Menu[0].pos.y = g_aFade_Menu[nCnt].pos.y + cosf(g_aFade_Menu[nCnt].rot.z - (D3DX_PI - g_aFade_Menu[nCnt].fAngle)) * g_aFade_Menu[nCnt].fLength;
		pVtx_Fade_Menu[1].pos.x = g_aFade_Menu[nCnt].pos.x + sinf(g_aFade_Menu[nCnt].rot.z + (D3DX_PI - g_aFade_Menu[nCnt].fAngle)) * g_aFade_Menu[nCnt].fLength;
		pVtx_Fade_Menu[1].pos.y = g_aFade_Menu[nCnt].pos.y + cosf(g_aFade_Menu[nCnt].rot.z + (D3DX_PI - g_aFade_Menu[nCnt].fAngle)) * g_aFade_Menu[nCnt].fLength;
		pVtx_Fade_Menu[2].pos.x = g_aFade_Menu[nCnt].pos.x + sinf(g_aFade_Menu[nCnt].rot.z - g_aFade_Menu[nCnt].fAngle) * g_aFade_Menu[nCnt].fLength;
		pVtx_Fade_Menu[2].pos.y = g_aFade_Menu[nCnt].pos.y + cosf(g_aFade_Menu[nCnt].rot.z - g_aFade_Menu[nCnt].fAngle) * g_aFade_Menu[nCnt].fLength;
		pVtx_Fade_Menu[3].pos.x = g_aFade_Menu[nCnt].pos.x + sinf(g_aFade_Menu[nCnt].rot.z + g_aFade_Menu[nCnt].fAngle) * g_aFade_Menu[nCnt].fLength;
		pVtx_Fade_Menu[3].pos.y = g_aFade_Menu[nCnt].pos.y + cosf(g_aFade_Menu[nCnt].rot.z + g_aFade_Menu[nCnt].fAngle) * g_aFade_Menu[nCnt].fLength;

		if (*pStart == false)
		{
			g_aFade_Menu[nCnt].col.a -= 0.05f;

			if (g_aFade_Menu[nCnt].col.a < 0.0f)
			{
				g_aFade_Menu[nCnt].col.a = 0.0f;
			}
		}
		else
		{
			g_aFade_Menu[nCnt].col.a += 0.1f;
		}

		pVtx_Fade_Menu[0].col = g_aFade_Menu[nCnt].col;
		pVtx_Fade_Menu[1].col = g_aFade_Menu[nCnt].col;
		pVtx_Fade_Menu[2].col = g_aFade_Menu[nCnt].col;
		pVtx_Fade_Menu[3].col = g_aFade_Menu[nCnt].col;

		pVtx_Fade_Menu += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Fade_Menu->Unlock();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Fade_Menu(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Fade_Menu, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_FADE_MENU; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Fade_Menu[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Fade_Menu(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FADE_MENU; nCnt++)
	{
		g_aFade_Menu[nCnt].nStyle = 0;
		g_aFade_Menu[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
		g_aFade_Menu[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFade_Menu[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFade_Menu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aFade_Menu[nCnt].fLength = sqrtf((990.0f * 990.0f) + (540.0f * 540.0f));
		g_aFade_Menu[nCnt].fAngle = atan2f(990.0f * 2.0f, 540.0f * 2.0f);
	}
}

//************************************************
//�|���S�����𑗂�֐�
//************************************************
float* Getinfo_Fade_Menu(void)
{
	return &g_aFade_Menu[0].col.a;
}