//************************************************
//
//�|�[�Y�J�[�\������[cursor_game.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "cursor_game.h"
#include "text_game.h"
#include "game.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Cursor_Game = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Cursor_Game = NULL;	//���_�o�b�t�@�̃|�C���^
CURSOR_GAME g_aCursor_Game;	//�|�[�Y�J�[�\�����

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Cursor_Game()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CURSOR_GAME_1,
		&g_pTexture_Cursor_Game);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Cursor_Game,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Cursor_Game;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Cursor_Game->Lock(0, 0, (void**)&pVtx_Cursor_Game, 0);

	//���_���W�̏����ݒ�
	pVtx_Cursor_Game[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Cursor_Game[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Cursor_Game[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Cursor_Game[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Cursor_Game[0].rhw = 1.0f;
	pVtx_Cursor_Game[1].rhw = 1.0f;
	pVtx_Cursor_Game[2].rhw = 1.0f;
	pVtx_Cursor_Game[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Cursor_Game[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Cursor_Game[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Cursor_Game[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Cursor_Game[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Cursor_Game[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Cursor_Game[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Cursor_Game[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Cursor_Game[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Cursor_Game->Unlock();

	//�w�i�\���̂̏��̏������Q
	g_aCursor_Game.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCursor_Game.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCursor_Game.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCursor_Game.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aCursor_Game.fRadius[nCnt] = 0.0f;
	}
	g_aCursor_Game.fLength = 0.0f;
	g_aCursor_Game.fAngle = 0.0f;

	//�w�i�\���̂ɏ���t�^
	SetInfo_Cursor_Game();

	//�ʒu�Ɋ�Â��|���S����W�J
	Update_Pos_Cursor_Game();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Cursor_Game(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Cursor_Game != NULL)
	{
		g_pTexture_Cursor_Game->Release();
		g_pTexture_Cursor_Game = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Cursor_Game != NULL)
	{
		g_pVtxBuff_Cursor_Game->Release();
		g_pVtxBuff_Cursor_Game = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Cursor_Game(void)
{
	int* pChoose = Getinfo_Choose_Pause_Menu();
	TEXT_GAME* pText_Game = GetInfo_Text_Game();

	g_aCursor_Game.pos.y = pText_Game[*pChoose].pos.y;

	Update_Pos_Cursor_Game();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Cursor_Game(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Cursor_Game, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Cursor_Game);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//�|�[�Y�J�[�\���\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Cursor_Game(void)
{
	TEXT_GAME* pText_Game = GetInfo_Text_Game();

	g_aCursor_Game.pos.x = 650.0f;
	g_aCursor_Game.pos.y = pText_Game[CONTINUE].pos.y;
	g_aCursor_Game.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCursor_Game.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aCursor_Game.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aCursor_Game.fRadius[0] = RADIUS_CURSOR_GAME_X;	//�w�i������
	g_aCursor_Game.fRadius[1] = RADIUS_CURSOR_GAME_Y;	//�w�i�c����
	g_aCursor_Game.fLength = sqrtf((g_aCursor_Game.fRadius[0] * g_aCursor_Game.fRadius[0]) + (g_aCursor_Game.fRadius[1] * g_aCursor_Game.fRadius[1]));
	g_aCursor_Game.fAngle = atan2f(g_aCursor_Game.fRadius[0] * 2.0f, g_aCursor_Game.fRadius[1] * 2.0f);
}

//************************************************
//�|�[�Y�J�[�\���̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Cursor_Game(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Cursor_Game;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Cursor_Game->Lock(0, 0, (void**)&pVtx_Cursor_Game, 0);

	pVtx_Cursor_Game[0].pos.x = g_aCursor_Game.pos.x + sinf(g_aCursor_Game.rot.z - (D3DX_PI - g_aCursor_Game.fAngle)) * g_aCursor_Game.fLength;
	pVtx_Cursor_Game[0].pos.y = g_aCursor_Game.pos.y + cosf(g_aCursor_Game.rot.z - (D3DX_PI - g_aCursor_Game.fAngle)) * g_aCursor_Game.fLength;
	pVtx_Cursor_Game[1].pos.x = g_aCursor_Game.pos.x + sinf(g_aCursor_Game.rot.z + (D3DX_PI - g_aCursor_Game.fAngle)) * g_aCursor_Game.fLength;
	pVtx_Cursor_Game[1].pos.y = g_aCursor_Game.pos.y + cosf(g_aCursor_Game.rot.z + (D3DX_PI - g_aCursor_Game.fAngle)) * g_aCursor_Game.fLength;
	pVtx_Cursor_Game[2].pos.x = g_aCursor_Game.pos.x + sinf(g_aCursor_Game.rot.z - g_aCursor_Game.fAngle) * g_aCursor_Game.fLength;
	pVtx_Cursor_Game[2].pos.y = g_aCursor_Game.pos.y + cosf(g_aCursor_Game.rot.z - g_aCursor_Game.fAngle) * g_aCursor_Game.fLength;
	pVtx_Cursor_Game[3].pos.x = g_aCursor_Game.pos.x + sinf(g_aCursor_Game.rot.z + g_aCursor_Game.fAngle) * g_aCursor_Game.fLength;
	pVtx_Cursor_Game[3].pos.y = g_aCursor_Game.pos.y + cosf(g_aCursor_Game.rot.z + g_aCursor_Game.fAngle) * g_aCursor_Game.fLength;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Cursor_Game->Unlock();
}

//************************************************
//�|�[�Y�J�[�\���\���̂̃A�h���X��n��
//************************************************
CURSOR_GAME* GetInfo_Cursor_Game(void)
{
	return &g_aCursor_Game;
}