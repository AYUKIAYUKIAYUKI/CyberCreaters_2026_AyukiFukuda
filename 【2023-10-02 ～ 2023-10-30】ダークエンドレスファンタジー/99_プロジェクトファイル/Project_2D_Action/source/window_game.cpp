//************************************************
//
//�|�[�Y�E�B���h�E����[window_game.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "window_game.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Window_Game[AMOUNT_TEX_WINDOW_GAME] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Window_Game = NULL;	//���_�o�b�t�@�̃|�C���^
WINDOW_GAME g_aWindow_Game[AMOUNT_POLYGON_WINDOW_GAME];	//�|�[�Y�E�B���h�E���

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Window_Game(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WHTITE_PAUSE,
		&g_pTexture_Window_Game[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WINDOW_GAME,
		&g_pTexture_Window_Game[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_PAUSE,
		&g_pTexture_Window_Game[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_WINDOW_GAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Window_Game,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Window_Game;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Window_Game->Lock(0, 0, (void**)&pVtx_Window_Game, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_WINDOW_GAME; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Window_Game[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Window_Game[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Window_Game[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Window_Game[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Window_Game[0].rhw = 1.0f;
		pVtx_Window_Game[1].rhw = 1.0f;
		pVtx_Window_Game[2].rhw = 1.0f;
		pVtx_Window_Game[3].rhw = 1.0f;

		switch (nCnt)
		{
		case 0:
			pVtx_Window_Game[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			pVtx_Window_Game[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			pVtx_Window_Game[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			pVtx_Window_Game[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			break;
		default:
			pVtx_Window_Game[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx_Window_Game[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx_Window_Game[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx_Window_Game[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Window_Game[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Window_Game[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Window_Game[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Window_Game[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Window_Game += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Window_Game->Unlock();

	//�|�[�Y�E�B���h�E�\���̂̏��̏������Q
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_WINDOW_GAME; nCnt++)
	{
		g_aWindow_Game[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWindow_Game[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWindow_Game[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWindow_Game[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aWindow_Game[nCnt].fRadius[nCnt2] = 0.0f;
		}
		g_aWindow_Game[nCnt].fLength = 0.0f;
		g_aWindow_Game[nCnt].fAngle = 0.0f;
	}

	//�|�[�Y�E�B���h�E�\���̂ɏ���t�^
	SetInfo_Window_Game();

	//�ʒu�Ɋ�Â��|���S����W�J
	Update_Pos_Window_Game();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Window_Game(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEX_WINDOW_GAME; nCnt++)
	{
		if (g_pTexture_Window_Game[nCnt] != NULL)
		{
			g_pTexture_Window_Game[nCnt]->Release();
			g_pTexture_Window_Game[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Window_Game != NULL)
	{
		g_pVtxBuff_Window_Game->Release();
		g_pVtxBuff_Window_Game = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Window_Game(void)
{

}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Window_Game(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Window_Game, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_WINDOW_GAME; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Window_Game[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|�[�Y�E�B���h�E�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Window_Game(void)
{
	int nCntLayer = 0;
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_WINDOW_GAME; nCnt++)
	{
		g_aWindow_Game[nCnt].pos = D3DXVECTOR3(SCREEN_HALFWIDTH, SCREEN_HALFHEIGHT, 0.0f);
		switch (nCnt)
		{
		case 0:
			g_aWindow_Game[nCnt].fRadius[0] = SCREEN_HALFWIDTH;	//�|�[�Y�E�B���h�E������
			g_aWindow_Game[nCnt].fRadius[1] = SCREEN_HALFHEIGHT;	//�|�[�Y�E�B���h�E�c����
			break;
		case 1:
			g_aWindow_Game[nCnt].fRadius[0] = 600.0f;
			g_aWindow_Game[nCnt].fRadius[1] = 500.0f;
			break;
		case 2:
			g_aWindow_Game[nCnt].pos = D3DXVECTOR3(SCREEN_HALFWIDTH, 250.0f, 0.0f);
			g_aWindow_Game[nCnt].fRadius[0] = RADIUS_TEXT_PAUSE_X;
			g_aWindow_Game[nCnt].fRadius[1] = RADIUS_TEXT_PAUSE_Y;
			break;
		}
		g_aWindow_Game[nCnt].fLength = sqrtf((g_aWindow_Game[nCnt].fRadius[0] * g_aWindow_Game[nCnt].fRadius[0]) + (g_aWindow_Game[nCnt].fRadius[1] * g_aWindow_Game[nCnt].fRadius[1]));
		g_aWindow_Game[nCnt].fAngle = atan2f(g_aWindow_Game[nCnt].fRadius[0] * 2.0f, g_aWindow_Game[nCnt].fRadius[1] * 2.0f);
	}
}

//************************************************
//�|�[�Y�E�B���h�E�̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Window_Game(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Window_Game;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Window_Game->Lock(0, 0, (void**)&pVtx_Window_Game, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_WINDOW_GAME; nCnt++)
	{
		//�N���͓���
		g_aWindow_Game[nCnt].pos += g_aWindow_Game[nCnt].move;

		pVtx_Window_Game[0].pos.x = g_aWindow_Game[nCnt].pos.x + sinf(g_aWindow_Game[nCnt].rot.z - (D3DX_PI - g_aWindow_Game[nCnt].fAngle)) * g_aWindow_Game[nCnt].fLength;
		pVtx_Window_Game[0].pos.y = g_aWindow_Game[nCnt].pos.y + cosf(g_aWindow_Game[nCnt].rot.z - (D3DX_PI - g_aWindow_Game[nCnt].fAngle)) * g_aWindow_Game[nCnt].fLength;
		pVtx_Window_Game[1].pos.x = g_aWindow_Game[nCnt].pos.x + sinf(g_aWindow_Game[nCnt].rot.z + (D3DX_PI - g_aWindow_Game[nCnt].fAngle)) * g_aWindow_Game[nCnt].fLength;
		pVtx_Window_Game[1].pos.y = g_aWindow_Game[nCnt].pos.y + cosf(g_aWindow_Game[nCnt].rot.z + (D3DX_PI - g_aWindow_Game[nCnt].fAngle)) * g_aWindow_Game[nCnt].fLength;
		pVtx_Window_Game[2].pos.x = g_aWindow_Game[nCnt].pos.x + sinf(g_aWindow_Game[nCnt].rot.z - g_aWindow_Game[nCnt].fAngle) * g_aWindow_Game[nCnt].fLength;
		pVtx_Window_Game[2].pos.y = g_aWindow_Game[nCnt].pos.y + cosf(g_aWindow_Game[nCnt].rot.z - g_aWindow_Game[nCnt].fAngle) * g_aWindow_Game[nCnt].fLength;
		pVtx_Window_Game[3].pos.x = g_aWindow_Game[nCnt].pos.x + sinf(g_aWindow_Game[nCnt].rot.z + g_aWindow_Game[nCnt].fAngle) * g_aWindow_Game[nCnt].fLength;
		pVtx_Window_Game[3].pos.y = g_aWindow_Game[nCnt].pos.y + cosf(g_aWindow_Game[nCnt].rot.z + g_aWindow_Game[nCnt].fAngle) * g_aWindow_Game[nCnt].fLength;

		pVtx_Window_Game += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Window_Game->Unlock();
}

//************************************************
//�|�[�Y�E�B���h�E�\���̂̃A�h���X��n��
//************************************************
WINDOW_GAME* GetInfo_Window_Game(void)
{
	return &g_aWindow_Game[0];
}