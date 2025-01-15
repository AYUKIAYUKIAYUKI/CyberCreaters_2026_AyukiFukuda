//************************************************
//
//�|�[�Y�e�L�X�g����[text_game.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "text_game.h"
#include "game.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Text_Game[AMOUNT_TEX_TEXT_GAME] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Text_Game = NULL;	//���_�o�b�t�@�̃|�C���^
TEXT_GAME g_aText_Game[AMOUNT_POLYGON_TEXT_GAME];	//�|�[�Y�e�L�X�g���

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Text_Game()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_GAME_1,
		&g_pTexture_Text_Game[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_GAME_2,
		&g_pTexture_Text_Game[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TEXT_GAME_3,
		&g_pTexture_Text_Game[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TEXT_GAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Text_Game,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Text_Game;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Text_Game->Lock(0, 0, (void**)&pVtx_Text_Game, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_GAME; i++)
	{
		//���_���W�̏����ݒ�
		pVtx_Text_Game[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Game[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Game[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Text_Game[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Text_Game[0].rhw = 1.0f;
		pVtx_Text_Game[1].rhw = 1.0f;
		pVtx_Text_Game[2].rhw = 1.0f;
		pVtx_Text_Game[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Text_Game[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Game[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Game[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Text_Game[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Text_Game[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Text_Game[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Text_Game[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Text_Game[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Text_Game += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Text_Game->Unlock();

	//�w�i�\���̂̏��̏������Q
	for (int i = 0; i < AMOUNT_POLYGON_TEXT_GAME; i++)
	{
		g_aText_Game[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Game[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Game[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aText_Game[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aText_Game[i].fRadius[nCnt] = 0.0f;
		}
		g_aText_Game[i].fLength = 0.0f;
		g_aText_Game[i].fAngle = 0.0f;
	}

	//�w�i�\���̂ɏ���t�^
	SetInfo_Text_Game();

	//�ʒu�Ɋ�Â��|���S����W�J
	Update_Pos_Text_Game();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Text_Game(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < AMOUNT_TEX_TEXT_GAME; i++)
	{
		if (g_pTexture_Text_Game[i] != NULL)
		{
			g_pTexture_Text_Game[i]->Release();
			g_pTexture_Text_Game[i] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Text_Game != NULL)
	{
		g_pVtxBuff_Text_Game->Release();
		g_pVtxBuff_Text_Game = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Text_Game(void)
{
	Update_Col_Text_Game();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Text_Game(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Text_Game, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_GAME; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexture_Text_Game[i]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|�[�Y�e�L�X�g�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Text_Game(void)
{
	for (int i = 0; i < AMOUNT_POLYGON_TEXT_GAME; i++)
	{
		g_aText_Game[i].pos = D3DXVECTOR3(990.0f, 500.0f + (i * 150.0f), 0.0f);
		g_aText_Game[i].fRadius[0] = RADIUS_TEXT_GAME_X;	//�w�i������
		g_aText_Game[i].fRadius[1] = RADIUS_TEXT_GAME_Y;	//�w�i�c����
		g_aText_Game[i].fLength = sqrtf((g_aText_Game[i].fRadius[0] * g_aText_Game[i].fRadius[0]) + (g_aText_Game[i].fRadius[1] * g_aText_Game[i].fRadius[1]));
		g_aText_Game[i].fAngle = atan2f(g_aText_Game[i].fRadius[0] * 2.0f, g_aText_Game[i].fRadius[1] * 2.0f);
	}
}

//************************************************
//�|�[�Y�e�L�X�g�̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Text_Game(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Text_Game;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Text_Game->Lock(0, 0, (void**)&pVtx_Text_Game, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_GAME; i++)
	{
		pVtx_Text_Game[0].pos.x = g_aText_Game[i].pos.x + sinf(g_aText_Game[i].rot.z - (D3DX_PI - g_aText_Game[i].fAngle)) * g_aText_Game[i].fLength;
		pVtx_Text_Game[0].pos.y = g_aText_Game[i].pos.y + cosf(g_aText_Game[i].rot.z - (D3DX_PI - g_aText_Game[i].fAngle)) * g_aText_Game[i].fLength;
		pVtx_Text_Game[1].pos.x = g_aText_Game[i].pos.x + sinf(g_aText_Game[i].rot.z + (D3DX_PI - g_aText_Game[i].fAngle)) * g_aText_Game[i].fLength;
		pVtx_Text_Game[1].pos.y = g_aText_Game[i].pos.y + cosf(g_aText_Game[i].rot.z + (D3DX_PI - g_aText_Game[i].fAngle)) * g_aText_Game[i].fLength;
		pVtx_Text_Game[2].pos.x = g_aText_Game[i].pos.x + sinf(g_aText_Game[i].rot.z - g_aText_Game[i].fAngle) * g_aText_Game[i].fLength;
		pVtx_Text_Game[2].pos.y = g_aText_Game[i].pos.y + cosf(g_aText_Game[i].rot.z - g_aText_Game[i].fAngle) * g_aText_Game[i].fLength;
		pVtx_Text_Game[3].pos.x = g_aText_Game[i].pos.x + sinf(g_aText_Game[i].rot.z + g_aText_Game[i].fAngle) * g_aText_Game[i].fLength;
		pVtx_Text_Game[3].pos.y = g_aText_Game[i].pos.y + cosf(g_aText_Game[i].rot.z + g_aText_Game[i].fAngle) * g_aText_Game[i].fLength;

		pVtx_Text_Game += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Text_Game->Unlock();
}

//************************************************
//�e�L�X�g�̐F��ύX����֐�
//************************************************
void Update_Col_Text_Game(void)
{
	int* pChoose = Getinfo_Choose_Pause_Menu();

	//�I��ł���̂̐F��ύX����`��
	for (int i = 0; i < AMOUNT_POLYGON_TEXT_GAME; i++)
	{
		if (i != *pChoose)
		{
			g_aText_Game[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
		}
		else
		{
			g_aText_Game[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Text_Game;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Text_Game->Lock(0, 0, (void**)&pVtx_Text_Game, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TEXT_GAME; i++)
	{
		pVtx_Text_Game[0].col = g_aText_Game[i].col;
		pVtx_Text_Game[1].col = g_aText_Game[i].col;
		pVtx_Text_Game[2].col = g_aText_Game[i].col;
		pVtx_Text_Game[3].col = g_aText_Game[i].col;

		pVtx_Text_Game += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Text_Game->Unlock();
}

//************************************************
//�|�[�Y�e�L�X�g�\���̂̃A�h���X��n��
//************************************************
TEXT_GAME* GetInfo_Text_Game(void)
{
	return &g_aText_Game[0];
}