//************************************************
//
//�|�[�Y���(�r��n)[pause.cpp]
//Author�F���c����
//
//************************************************
#include "input.h"
#include "sound.h"
#include "game.h"
#include "pause.h"
#include "pause_cursor.h"
#include "pause_fade.h"
#include "pause_select.h"
#include "pause_window.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Pause = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Pause = NULL;	//���_�o�b�t�@�̃|�C���^
bool g_bPause_Return = false;

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Pause(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WHITE_PAUSE,
		&g_pTexture_Pause);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Pause,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Pause;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Pause->Lock(0, 0, (void**)&pVtx_Pause, 0);

	//���_���W�̏����ݒ�
	pVtx_Pause[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Pause[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx_Pause[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx_Pause[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Pause[0].rhw = 1.0f;
	pVtx_Pause[1].rhw = 1.0f;
	pVtx_Pause[2].rhw = 1.0f;
	pVtx_Pause[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Pause[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx_Pause[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx_Pause[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx_Pause[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Pause[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Pause[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Pause[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Pause[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Pause->Unlock();

	g_bPause_Return = false;

	//���̂ق���
	Init_Pause_Cursor();
	Init_Pause_Fade();
	Init_Pause_Select();
	Init_Pause_Window();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Pause(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Pause != NULL)
	{
		g_pTexture_Pause->Release();
		g_pTexture_Pause = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Pause != NULL)
	{
		g_pVtxBuff_Pause->Release();
		g_pVtxBuff_Pause = NULL;
	}

	//���̂ق���
	Uninit_Pause_Cursor();
	Uninit_Pause_Fade();
	Uninit_Pause_Select();
	Uninit_Pause_Window();
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Pause(void)
{
	//�|�[�Y����
	bool* pStop;
	pStop = Getinfo_Pause();

	int* pChoose_Pause;
	pChoose_Pause = Getinfo_Choose_Pause();

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true &&
		!g_bPause_Return)
	{
		//���ʉ���炷
		PlaySound(SOUND_LABEL_SE_SELECT2);

		g_bPause_Return = true;
	}

	//���̂ق���
	Update_Pause_Cursor();
	Update_Pause_Fade();
	Update_Pause_Select();
	Update_Pause_Window();

	if (g_bPause_Return)
	{
		float* pFade_Menu;
		pFade_Menu = Getinfo_Pause_Fade();

		switch (*pChoose_Pause)
		{
		case 0:

			*pStop = false;	//��������

			g_bPause_Return = false;

			Uninit_Pause_Cursor();
			Uninit_Pause_Fade();
			Uninit_Pause_Select();
			Uninit_Pause_Window();

			Init_Pause_Cursor();
			Init_Pause_Fade();
			Init_Pause_Select();
			Init_Pause_Window();

			break;

		case 1:

			if (*pFade_Menu >= 1.1f)
			{
				Setinfo_Mode(MODE_GAME);	//���g���C
			}

			break;

		case 2:

			if (*pFade_Menu >= 1.1f)
			{
				Setinfo_Mode(MODE_MENU);	//���j���[�ɐݒ�
			}

			break;

		case 3:

			if (*pFade_Menu >= 1.1f)
			{
				Setinfo_Mode(MODE_TITLE);	//�^�C�g���ɐݒ�
			}

			break;
		}
	}
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Pause(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Pause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Pause);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);

	//���̂ق���
	Draw_Pause_Window();
	Draw_Pause_Cursor();
	Draw_Pause_Select();
	Draw_Pause_Fade();
}

//************************************************
//���j���[������𑗂�֐�
//************************************************
bool* Getinfo_Return_Pause(void)
{
	return &g_bPause_Return;
}