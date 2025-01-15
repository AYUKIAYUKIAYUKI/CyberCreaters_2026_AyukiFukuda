//************************************************
//
//�E�B���h�E���j���[����[window_menu.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "window_menu.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Window_Menu = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Window_Menu = NULL;	//���_�o�b�t�@�̃|�C���^
WINDOW_MENU g_aWindow_Menu;	//�E�B���h�E���j���[���

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Window_Menu()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WINDOW_MENU,
		&g_pTexture_Window_Menu);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Window_Menu,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Window_Menu;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Window_Menu->Lock(0, 0, (void**)&pVtx_Window_Menu, 0);

	//���_���W�̏����ݒ�
	pVtx_Window_Menu[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Menu[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Menu[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Window_Menu[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Window_Menu[0].rhw = 1.0f;
	pVtx_Window_Menu[1].rhw = 1.0f;
	pVtx_Window_Menu[2].rhw = 1.0f;
	pVtx_Window_Menu[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Window_Menu[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Window_Menu[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Window_Menu[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Window_Menu[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Window_Menu[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Window_Menu[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Window_Menu[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Window_Menu[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Window_Menu->Unlock();

	//�E�B���h�E���j���[�\���̂̏��̏������Q
	g_aWindow_Menu.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Menu.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Menu.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Menu.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aWindow_Menu.fRadius[nCnt] = 0.0f;
		g_aWindow_Menu.fLength[nCnt] = 0.0f;
		g_aWindow_Menu.fAngle[nCnt] = 0.0f;
	}

	//�E�B���h�E���j���[�\���̂ɏ���t�^
	SetInfo_Window_Menu();

	//�ʒu�Ɋ�Â��|���S����W�J
	Update_Pos_Window_Menu();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Window_Menu(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Window_Menu != NULL)
	{
		g_pTexture_Window_Menu->Release();
		g_pTexture_Window_Menu = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Window_Menu != NULL)
	{
		g_pVtxBuff_Window_Menu->Release();
		g_pVtxBuff_Window_Menu = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Window_Menu(void)
{

}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Window_Menu(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Window_Menu, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Window_Menu);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//�E�B���h�E���j���[�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Window_Menu(void)
{
	g_aWindow_Menu.pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
	g_aWindow_Menu.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Menu.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aWindow_Menu.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aWindow_Menu.fRadius[0] = RADIUS_WINDOW_MENU_X;	//������
	g_aWindow_Menu.fRadius[1] = RADIUS_WINDOW_MENU_Y;	//�c����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aWindow_Menu.fLength[nCnt] = sqrtf((g_aWindow_Menu.fRadius[0] * g_aWindow_Menu.fRadius[0]) + (g_aWindow_Menu.fRadius[1] * g_aWindow_Menu.fRadius[1]));
		g_aWindow_Menu.fAngle[nCnt] = atan2f(g_aWindow_Menu.fRadius[0] * 2.0f, g_aWindow_Menu.fRadius[1] * 2.0f);
	}
}

//************************************************
//�E�B���h�E���j���[�̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Window_Menu(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Window_Menu;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Window_Menu->Lock(0, 0, (void**)&pVtx_Window_Menu, 0);

	pVtx_Window_Menu[0].pos.x = g_aWindow_Menu.pos.x + sinf(g_aWindow_Menu.rot.z - (D3DX_PI - g_aWindow_Menu.fAngle[0])) * g_aWindow_Menu.fLength[0];
	pVtx_Window_Menu[0].pos.y = g_aWindow_Menu.pos.y + cosf(g_aWindow_Menu.rot.z - (D3DX_PI - g_aWindow_Menu.fAngle[0])) * g_aWindow_Menu.fLength[0];
	pVtx_Window_Menu[1].pos.x = g_aWindow_Menu.pos.x + sinf(g_aWindow_Menu.rot.z + (D3DX_PI - g_aWindow_Menu.fAngle[0])) * g_aWindow_Menu.fLength[0];
	pVtx_Window_Menu[1].pos.y = g_aWindow_Menu.pos.y + cosf(g_aWindow_Menu.rot.z + (D3DX_PI - g_aWindow_Menu.fAngle[0])) * g_aWindow_Menu.fLength[0];
	pVtx_Window_Menu[2].pos.x = g_aWindow_Menu.pos.x + sinf(g_aWindow_Menu.rot.z - g_aWindow_Menu.fAngle[0]) * g_aWindow_Menu.fLength[0];
	pVtx_Window_Menu[2].pos.y = g_aWindow_Menu.pos.y + cosf(g_aWindow_Menu.rot.z - g_aWindow_Menu.fAngle[0]) * g_aWindow_Menu.fLength[0];
	pVtx_Window_Menu[3].pos.x = g_aWindow_Menu.pos.x + sinf(g_aWindow_Menu.rot.z + g_aWindow_Menu.fAngle[0]) * g_aWindow_Menu.fLength[0];
	pVtx_Window_Menu[3].pos.y = g_aWindow_Menu.pos.y + cosf(g_aWindow_Menu.rot.z + g_aWindow_Menu.fAngle[0]) * g_aWindow_Menu.fLength[0];

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Window_Menu->Unlock();
}

//************************************************
//�E�B���h�E���j���[�\���̂̃A�h���X��n��
//************************************************
WINDOW_MENU* GetInfo_Window_Menu(void)
{
	return &g_aWindow_Menu;
}