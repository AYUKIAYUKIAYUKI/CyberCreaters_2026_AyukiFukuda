//************************************************
//
//�|�[�Y[pause.cpp]
//Author�F���c����
//
//************************************************
#include "pause.h"

#include "game.h"

#include "fade.h"
#include "input.h"
#include "sound.h"

#include "player.h"

//�|�[�Y�p
typedef enum
{
	TexWindow = 0,
	TexContinue,
	TexRetry,
	TexRetire,
	TexArrow,
	TexMax,
}TexType;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePause[TexMax] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;	//���_�o�b�t�@�̃|�C���^
Pause g_aPause[TexMax];	//���
int g_nChoosePause = TexContinue;

//************************************************
//�|�[�Y����
//************************************************
void InitPause(void)
{
	g_nChoosePause = TexContinue;

	//�\���̂̏��̏������Q
	for (int i = 0; i < TexMax; i++)
	{
		g_aPause[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aPause[i].sizeX = 0.0f;
		g_aPause[i].sizeY = 0.0f;
		g_aPause[i].F = 1.0f;	//�ėp
	}

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	const char* pFileName[TexMax] =
	{
		"data\\texture\\pause.png",
		"data\\texture\\continue.png",
		"data\\texture\\retry.png",
		"data\\texture\\retire.png",
		"data\\texture\\arrow.png",
	};

	for (int i = 0; i < TexMax; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTexturePause[i]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * TexMax,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++)
	{
		//���_���W�̏����ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	//����t�^
	SetInfoPause();

	//�W�J
	SetSizePause();
}

//************************************************
//�|�[�Y�I�������֐�
//************************************************
void UninitPause(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < TexMax; i++)
	{
		if (g_pTexturePause[i] != NULL)
		{
			g_pTexturePause[i]->Release();
			g_pTexturePause[i] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//************************************************
//�|�[�Y�X�V
//************************************************
void UpdatePause(void)
{
	//�|�[�Y���p
	bool* pPause = GetInfoPause();

	//�t�F�[�h���p
	FADE* pFade = GetInfoFade();

	if (GetKeyboardTrigger(DIK_W) || GetJoypadTrigger(JOYKEY_UP))
	{
		g_nChoosePause > TexContinue ? g_nChoosePause-- : g_nChoosePause = TexRetire;
		PlaySound(SOUND_LABEL_CHOOSE);
	}
	else if (GetKeyboardTrigger(DIK_S) || GetJoypadTrigger(JOYKEY_DOWN))
	{
		g_nChoosePause < TexRetire ? g_nChoosePause++ : g_nChoosePause = TexContinue;
		PlaySound(SOUND_LABEL_CHOOSE);
	}

	//if (GetJoypadTrigger(JOYKEY_START))
	//{
	//	*pPause = false;
	//	g_nChoosePause = TexContinue;
	//}

	if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_B))
	{
		switch(g_nChoosePause)
		{
		case TexContinue:
			*pPause = false;
			break;

		case TexRetry:
			//�t�F�[�h�A�E�g�J�n
			pFade->bFadeIn = false;
			pFade->bFadeOut = true;
			break;

		case TexRetire:
			//�t�F�[�h�A�E�g�J�n
			pFade->bFadeIn = false;
			pFade->bFadeOut = true;
			break;
		}
		PlaySound(SOUND_LABEL_DEFINE);
	}

	//�W�J
	SetSizePause();

	//�F�ύX
	UpdateColPause();
}

//************************************************
//�|�[�Y�W�J
//************************************************
void SetSizePause(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		if (i == TexArrow)
		{
			g_aPause[i].pos =
			{
				g_aPause[g_nChoosePause].pos.x - 220.0f,
				g_aPause[g_nChoosePause].pos.y,
				g_aPause[g_nChoosePause].pos.z,
			};
		}

		//���_���W�̐ݒ�
		pVtx[0].pos =
		{
			g_aPause[i].pos.x - g_aPause[i].sizeX,
			g_aPause[i].pos.y - g_aPause[i].sizeY,
			0.0f
		};

		pVtx[1].pos =
		{
			g_aPause[i].pos.x + g_aPause[i].sizeX,
			g_aPause[i].pos.y - g_aPause[i].sizeY,
			0.0f
		};

		pVtx[2].pos =
		{
			g_aPause[i].pos.x - g_aPause[i].sizeX,
			g_aPause[i].pos.y + g_aPause[i].sizeY,
			0.0f
		};

		pVtx[3].pos =
		{
			g_aPause[i].pos.x + g_aPause[i].sizeX,
			g_aPause[i].pos.y + g_aPause[i].sizeY,
			0.0f
		};
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}

//************************************************
//�|�[�Y�F�ύX
//************************************************
void UpdateColPause(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		//���ɂȂ�
		if (i == g_nChoosePause)
		{
			g_aPause[i].col.r = 0.0f;
			g_aPause[i].col.b = 0.0f;
		}
		else
		{
			g_aPause[i].col.r = 1.0f;
			g_aPause[i].col.b = 1.0f;
		}
		
		pVtx[0].col = g_aPause[i].col;
		pVtx[1].col = g_aPause[i].col;
		pVtx[2].col = g_aPause[i].col;
		pVtx[3].col = g_aPause[i].col;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}

//************************************************
//�|�[�Y�`��
//************************************************
void DrawPause(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TexMax; i++)
	{
		pDevice->SetTexture(0, g_pTexturePause[i]);

		//�|�[�Y�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfoPause(void)
{
	for (int i = 0; i < TexMax; i++)
	{
		g_aPause[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPause[i].F = 1.0f;	//�ėp

		if (i == TexWindow)
		{
			g_aPause[i].pos = D3DXVECTOR3((float)SCREEN_HALFWIDTH, (float)SCREEN_HALFHEIGHT, 0.0f);
			g_aPause[i].sizeX = (float)SCREEN_HALFWIDTH;
			g_aPause[i].sizeY = (float)SCREEN_HALFHEIGHT;
		}
		else if (i == TexArrow)
		{
			g_aPause[i].sizeX = 55.0f;
			g_aPause[i].sizeY = 55.0f;
		}
		else
		{
			g_aPause[i].pos = D3DXVECTOR3(850.0f, 350.0f + (i * 125.0f), 0.0f);
			g_aPause[i].sizeX = 175.0f;
			g_aPause[i].sizeY = 55.0f;
		}
	}
}

//************************************
//�|�[�Y�I�����擾
//************************************
MODE GetInfoChoosePause(void)
{
	int nChoose = 0;

	switch (g_nChoosePause)
	{
	case TexRetry:
		nChoose = MODE_GAME;
		break;

	case TexRetire:
		nChoose = MODE_TITLE;
		break;
	}

	return (MODE)nChoose;
}