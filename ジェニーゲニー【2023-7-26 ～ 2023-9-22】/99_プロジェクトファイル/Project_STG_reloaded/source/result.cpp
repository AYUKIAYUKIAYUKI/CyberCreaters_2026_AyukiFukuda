//************************************************
//
//���U���g�\������(�r��n)[result.cpp]
//Author�F���c����
//
//************************************************
#include "../header/input.h"
#include "../header/sound.h"
#include "../header/player.h"
#include "../header/result.h"

//�}�N����`
#define MAX_RESULT	(10)		//�|���S����
#define TEXAMT_RESULT	(10)	//�Ǎ��݃e�N�X�`����

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Result[TEXAMT_RESULT] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Result = NULL;			//���_�o�b�t�@�̃|�C���^
int g_cursor_result = 0;									//�^�C�g���p�̃J�[�\��
/*�J�[�\���A�j���[�V�����p*/
float g_ANIMcursorL_r = 600.0f;
float g_ANIMcursorR_r = 700.0f;
bool g_bTurn_cursor_r = false;
/*�F�ύX�p*/
bool bStartFadein_Result = true;	//�t�F�[�h�C���̋���
bool bStartFadeout_Result = false;	//�t�F�[�h�A�E�g�̋���
int g_A_Result = 0;				//�����x�̒���

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Result(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEX_1_RESULT,
		&g_pTexture_Result[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEX_2_RESULT,
		&g_pTexture_Result[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEX_3_RESULT,
		&g_pTexture_Result[2]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEX_4_RESULT,
		&g_pTexture_Result[3]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEX_5_RESULT,
		&g_pTexture_Result[4]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEX_6_RESULT,
		&g_pTexture_Result[5]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEX_7_RESULT,
		&g_pTexture_Result[6]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEX_8_RESULT,
		&g_pTexture_Result[7]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEX_9_RESULT,
		&g_pTexture_Result[8]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEX_10_RESULT,
		&g_pTexture_Result[9]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMT_PLG_RESULT * TEXAMT_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Result,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Result;

	//�v���C���[���ւ̃|�C���^
	PLAYER* pPlayer;

	//�v���C���[���̎擾
	pPlayer = Getinfo_Player();	//�v���C���[���n�̐擪�A�h���X����������

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Result->Lock(0, 0, (void**)&pVtx_Result, 0);

	bStartFadein_Result = true;
	bStartFadeout_Result = false;
	g_A_Result = 255;

	//�����ʒu�ݒ�
	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			//�Q�[���N���A
			if (pPlayer->nLife > 0)
			{
				pVtx_Result[0].pos = D3DXVECTOR3(250.0f, 100.0f, 0.0f);
				pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 250.0f, 100.0f, 0.0f);
				pVtx_Result[2].pos = D3DXVECTOR3(250.0f, 400.0f, 0.0f);
				pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 250.0f, 400.0f, 0.0f);
			}

			break;

		case 1:

			//�Q�[���I�[�o�[
			if (pPlayer->nLife <= 0)
			{
				pVtx_Result[0].pos = D3DXVECTOR3(250.0f, 100.0f, 0.0f);
				pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 250.0f, 100.0f, 0.0f);
				pVtx_Result[2].pos = D3DXVECTOR3(250.0f, 400.0f, 0.0f);
				pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 250.0f, 400.0f, 0.0f);
			}

			break;

		case 2:

			//���j���[�D�F
			pVtx_Result[0].pos = D3DXVECTOR3(800.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 800.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(800.0f, SCREEN_HEIGHT - 400.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 800.0f, SCREEN_HEIGHT - 400.0f, 0.0f);

			break;

		case 3:

			//���j���[���F
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 4:

			//���g���C�D�F
			pVtx_Result[0].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);

			break;

		case 5:

			//���g���C���F
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 6:

			//�I���D�F
			pVtx_Result[0].pos = D3DXVECTOR3(850.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(850.0f, SCREEN_HEIGHT - 100.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 100.0f, 0.0f);

			break;

		case 7:

			//�I�����F
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 8:

			//�J�[�\��
			pVtx_Result[0].pos = D3DXVECTOR3(600.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(700.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(600.0f, SCREEN_HEIGHT - 400.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(700.0f, SCREEN_HEIGHT - 400.0f, 0.0f);

			break;

		case 9:

			//�u���b�N�x�[�X
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

			break;
		}

		//rhw�̐ݒ�
		pVtx_Result[0].rhw = 1.0f;
		pVtx_Result[1].rhw = 1.0f;
		pVtx_Result[2].rhw = 1.0f;
		pVtx_Result[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		if (nCnt != 9)
		{
			pVtx_Result[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx_Result[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx_Result[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx_Result[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else
		{
			pVtx_Result[0].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
			pVtx_Result[1].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
			pVtx_Result[2].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
			pVtx_Result[3].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx_Result[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Result[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Result[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Result[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�|�C���^�����炷
		pVtx_Result += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Result->Unlock();

	g_cursor_result = 0;
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Result(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < TEXAMT_RESULT; nCnt++)
	{
		if (g_pTexture_Result[nCnt] != NULL)
		{
			g_pTexture_Result[nCnt]->Release();
			g_pTexture_Result[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Result != NULL)
	{
		g_pVtxBuff_Result->Release();
		g_pVtxBuff_Result = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Result(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Result;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Result->Lock(0, 0, (void**)&pVtx_Result, 0);

	//�t�F�[�h�C��
	if (bStartFadein_Result == true)
	{
		g_A_Result -= 10;

		if (g_A_Result <= 0)
		{
			bStartFadein_Result = false;

			g_A_Result = 0;
		}

		pVtx_Result += 4 * 9;

		pVtx_Result[0].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
		pVtx_Result[1].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
		pVtx_Result[2].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
		pVtx_Result[3].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
	}

	//�t�F�[�h�C����A���R�I���\
	if (bStartFadeout_Result == false && bStartFadein_Result == false)
	{
		if (GetKeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP) == true
			&& g_cursor_result > 0)
		{
			//�J�[�\�����
			g_cursor_result--;

			//���ʉ���炷
			PlaySound(SOUND_LABEL_SE_SELECT1);
		}
		else if (GetKeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true
			&& g_cursor_result < 2)
		{
			//�J�[�\������
			g_cursor_result++;

			//���ʉ���炷
			PlaySound(SOUND_LABEL_SE_SELECT1);
		}

		//�J�[�\���A�j���[�V����(�펞)
		Setcursor_Anim_R();

		switch (g_cursor_result)
		{
		case 0:

			//MENU��I��
			Setcursor_MENU();

			break;

		case 1:

			//RETRY��I��
			Setcursor_RETRY_R();

			break;

		case 2:

			//EXIT��I��
			Setcursor_EXIT_R();

			break;
		}
	}

	//���肳�ꂽ
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true
		&& bStartFadeout_Result == false)
	{
		//���ʉ���炷
		PlaySound(SOUND_LABEL_SE_SELECT2);

		bStartFadeout_Result = true;
	}

	if (bStartFadeout_Result == true)
	{
		//�t�F�[�h�J�n
		g_A_Result += 10;

		pVtx_Result += 4 * 9;

		pVtx_Result[0].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
		pVtx_Result[1].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
		pVtx_Result[2].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);
		pVtx_Result[3].col = D3DCOLOR_RGBA(255, 255, 255, g_A_Result);

		if (g_A_Result >= 255)
		{
			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuff_Result->Unlock();

			switch (g_cursor_result)
			{
			case 0:

				Setinfo_Mode(MODE_MENU);	//���j���[���[�h��

				break;

			case 1:

				Setinfo_Mode(MODE_GAME);	//�Q�[�����[�h��

				break;

			case 2:

				//�I������ϐ��A�h���X�p�̃|�C���^
				bool* pExit;

				//�A�h���X����
				pExit = Getinfo_End();

				*pExit = true;	//�Q�[���I��

				break;
			}
		}
	}
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Result(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Result, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < TEXAMT_RESULT; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Result[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, AMT_TRI_RESULT);
	}
}

//************************************************
//�J�[�\��MENU�I��������
//************************************************
void Setcursor_MENU(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Result;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Result->Lock(0, 0, (void**)&pVtx_Result, 0);

	//�J�[�\���p�Ƀ|���S���ݒ�
	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		switch (nCnt)
		{
		case 2:

			//���j���[�D�F
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 3:

			//���j���[���F
			pVtx_Result[0].pos = D3DXVECTOR3(800.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 800.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(800.0f, SCREEN_HEIGHT - 400.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 800.0f, SCREEN_HEIGHT - 400.0f, 0.0f);

			break;

		case 4:

			//���g���C�D�F
			pVtx_Result[0].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);

			break;

		case 5:

			//���g���C���F
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 8:

			//�J�[�\��
			pVtx_Result[0].pos = D3DXVECTOR3(g_ANIMcursorL_r, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(g_ANIMcursorR_r, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(g_ANIMcursorL_r, SCREEN_HEIGHT - 400.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(g_ANIMcursorR_r, SCREEN_HEIGHT - 400.0f, 0.0f);

			break;
		}

		//�|�C���^�����炷
		pVtx_Result += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Result->Unlock();
}

//************************************************
//�J�[�\��RETRY�I��������
//************************************************
void Setcursor_RETRY_R(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Result;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Result->Lock(0, 0, (void**)&pVtx_Result, 0);

	//�J�[�\���p�Ƀ|���S���ݒ�
	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		switch (nCnt)
		{
		case 2:

			//���j���[�D�F
			pVtx_Result[0].pos = D3DXVECTOR3(800.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 800.0f, SCREEN_HEIGHT - 500.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(800.0f, SCREEN_HEIGHT - 400.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 800.0f, SCREEN_HEIGHT - 400.0f, 0.0f);

			break;

		case 3:

			//���j���[���F
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 4:

			//���g���C�D�F
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 5:

			//���g���C���F
			pVtx_Result[0].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);

			break;

		case 6:

			//�I���D�F
			pVtx_Result[0].pos = D3DXVECTOR3(850.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(850.0f, SCREEN_HEIGHT - 100.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 100.0f, 0.0f);

			break;

		case 7:

			//�I�����F
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 8:

			//�J�[�\��
			pVtx_Result[0].pos = D3DXVECTOR3(g_ANIMcursorL_r, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(g_ANIMcursorR_r, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(g_ANIMcursorL_r, SCREEN_HEIGHT - 250.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(g_ANIMcursorR_r, SCREEN_HEIGHT - 250.0f, 0.0f);

			break;
		}

		//�|�C���^�����炷
		pVtx_Result += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Result->Unlock();
}

//************************************************
//�J�[�\��EXIT�I��������
//************************************************
void Setcursor_EXIT_R(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Result;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Result->Lock(0, 0, (void**)&pVtx_Result, 0);

	//�J�[�\���p�Ƀ|���S���ݒ�
	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		switch (nCnt)
		{
		case 4:

			//���g���C�D�F
			pVtx_Result[0].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 350.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 775.0f, SCREEN_HEIGHT - 250.0f, 0.0f);

			break;

		case 5:

			//���g���C���F
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 6:

			//�I���D�F
			pVtx_Result[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;

		case 7:

			//�I�����F
			pVtx_Result[0].pos = D3DXVECTOR3(850.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(850.0f, SCREEN_HEIGHT - 100.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 850.0f, SCREEN_HEIGHT - 100.0f, 0.0f);

			break;

		case 8:

			//�J�[�\��
			pVtx_Result[0].pos = D3DXVECTOR3(g_ANIMcursorL_r, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[1].pos = D3DXVECTOR3(g_ANIMcursorR_r, SCREEN_HEIGHT - 200.0f, 0.0f);
			pVtx_Result[2].pos = D3DXVECTOR3(g_ANIMcursorL_r, SCREEN_HEIGHT - 100.0f, 0.0f);
			pVtx_Result[3].pos = D3DXVECTOR3(g_ANIMcursorR_r, SCREEN_HEIGHT - 100.0f, 0.0f);

			break;
		}

		//�|�C���^�����炷
		pVtx_Result += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Result->Unlock();
}

//************************************************
//�J�[�\���A�j���[�V��������
//************************************************
void Setcursor_Anim_R(void)
{
	if (g_ANIMcursorL_r < 600.0f + 10.0f && g_bTurn_cursor_r == false)
	{
		g_ANIMcursorL_r += 1.0f;
		g_ANIMcursorR_r += 1.0f;
	}
	else
	{
		g_bTurn_cursor_r = true;
	}

	if (g_ANIMcursorL_r > 600.0f - 10.0f && g_bTurn_cursor_r == true)
	{
		g_ANIMcursorL_r -= 1.0f;
		g_ANIMcursorR_r -= 1.0f;
	}
	else
	{
		g_bTurn_cursor_r = false;
	}
}