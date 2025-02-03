//************************************************
//
//�`���[�g���A���f�U�C��[tutorialdesign.cpp]
//Author�F���c����
//
//************************************************
#include "tutorialdesign.h"

#include "fade.h"
#include "input.h"
#include "sound.h"

#include "player.h"

//�`���[�g���A���f�U�C���p
typedef enum
{
	Tex0 = 0,
	Tex1,
	Tex2,
	Tex3,
	Tex4,
	TexMax
}TexType;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTutorialDesign[TexMax] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialDesign = NULL;	//���_�o�b�t�@�̃|�C���^
TutorialDesign g_aTutorialDesign[TexMax];	//���
int g_nScenario = 0;	//�`���[�g���A���̐i�x
int g_nChangeCT = 0;	//�i�x�ύX���̕ϑJ�ɏ����x��
bool g_bSpawn = false;	//�N�����ǂ���
bool g_bStamp = false;	//�E����

//************************************************
//�`���[�g���A���f�U�C������
//************************************************
void InitTutorialDesign(void)
{
	//�\���̂̏��̏������Q
	for (int i = 0; i < TexMax; i++)
	{
		g_aTutorialDesign[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorialDesign[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorialDesign[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorialDesign[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aTutorialDesign[i].sizeX = 0.0f;
		g_aTutorialDesign[i].sizeY = 0.0f;
		g_aTutorialDesign[i].F = 1.0f;	//�ėp
	}

	//�i�x
	g_nScenario = Tex0;

	//�x��
	g_nChangeCT = 0;

	g_bSpawn = false;
	g_bStamp = false;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	const char* pFileName[TexMax] =
	{
		"data\\texture\\tutorial00.png",
		"data\\texture\\tutorial01.png",
		"data\\texture\\tutorial02.png",
		"data\\texture\\tutorial03.png",
		"data\\texture\\tutorial04.png",
	};

	for (int i = 0; i < TexMax; i++)
	{
		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureTutorialDesign[i]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * TexMax,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialDesign,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffTutorialDesign->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTutorialDesign->Unlock();

	//����t�^
	SetInfoTutorialDesign();

	//�W�J
	SetSizeTutorialDesign();
}

//************************************************
//�`���[�g���A���f�U�C���I�������֐�
//************************************************
void UninitTutorialDesign(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < TexMax; i++)
	{
		if (g_pTextureTutorialDesign[i] != NULL)
		{
			g_pTextureTutorialDesign[i]->Release();
			g_pTextureTutorialDesign[i] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTutorialDesign != NULL)
	{
		g_pVtxBuffTutorialDesign->Release();
		g_pVtxBuffTutorialDesign = NULL;
	}
}

//************************************************
//�`���[�g���A���f�U�C���X�V
//************************************************
void UpdateTutorialDesign(void)
{
	//�t�F�[�h���p
	FADE* pFade = GetInfoFade();

	//Player* pPlayer = GetInfoPlayer();

	if (g_nChangeCT > 0)
	{
		g_nChangeCT--;

		if (g_nChangeCT <= 0)
		{
			g_nScenario++;
		}
	}

	//�W�J
	SetSizeTutorialDesign();

	//�F�ύX
	//UpdateColTutorialDesign();

	if (g_nChangeCT <= 0)
	{
		switch (g_nScenario)
		{
		case Tex0:
			//if (pPlayer->pos != pPlayer->posOld)
			if (GetKeyboardTrigger(DIK_W) || GetKeyboardTrigger(DIK_A) || GetKeyboardTrigger(DIK_S) || GetKeyboardTrigger(DIK_D) || GetJoyStickL())
			{
				g_nChangeCT += 40;
			}
			break;
		case Tex1:
			if (GetKeyboardTrigger(DIK_UP) || GetKeyboardTrigger(DIK_LEFT) || GetKeyboardTrigger(DIK_RIGHT) || GetKeyboardTrigger(DIK_DOWN) || GetJoyStickR())
			{
				g_nChangeCT += 40;
				g_bSpawn = true;
			}
			break;
		case Tex2:
			if (GetKeyboardTrigger(DIK_SPACE) || GetTriggerTriggerButtonR())
			{
				g_nChangeCT += 40;
				g_bStamp = false;
			}
			break;
		case Tex3:
			if (g_bStamp && g_nChangeCT <= 0)
			{
				g_nChangeCT += 40;
			}
			break;
		case Tex4:
			if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_START))
			{
				//�t�F�[�h�A�E�g�J�n
				pFade->bFadeIn = false;
				pFade->bFadeOut = true;

				PlaySound(SOUND_LABEL_DEFINE);
			}
		}
	}
}

//************************************************
//�`���[�g���A���f�U�C���W�J
//************************************************
void SetSizeTutorialDesign(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffTutorialDesign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		if (g_nScenario == i)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos =
			{
				g_aTutorialDesign[i].pos.x - g_aTutorialDesign[i].sizeX,
				g_aTutorialDesign[i].pos.y - g_aTutorialDesign[i].sizeY,
				0.0f
			};

			pVtx[1].pos =
			{
				g_aTutorialDesign[i].pos.x + g_aTutorialDesign[i].sizeX,
				g_aTutorialDesign[i].pos.y - g_aTutorialDesign[i].sizeY,
				0.0f
			};

			pVtx[2].pos =
			{
				g_aTutorialDesign[i].pos.x - g_aTutorialDesign[i].sizeX,
				g_aTutorialDesign[i].pos.y + g_aTutorialDesign[i].sizeY,
				0.0f
			};

			pVtx[3].pos =
			{
				g_aTutorialDesign[i].pos.x + g_aTutorialDesign[i].sizeX,
				g_aTutorialDesign[i].pos.y + g_aTutorialDesign[i].sizeY,
				0.0f
			};
		}
		else
		{
			pVtx[0].pos = {};
			pVtx[1].pos = {};
			pVtx[2].pos = {};
			pVtx[3].pos = {};
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorialDesign->Unlock();
}

//************************************************
//�`���[�g���A���f�U�C���F�ύX
//************************************************
void UpdateColTutorialDesign(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffTutorialDesign->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TexMax; i++, pVtx += AMOUNT_VTX)
	{
		//���ɂȂ�
		pVtx[0].col = g_aTutorialDesign[i].col;
		pVtx[1].col = g_aTutorialDesign[i].col;
		pVtx[2].col = g_aTutorialDesign[i].col;
		pVtx[3].col = g_aTutorialDesign[i].col;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorialDesign->Unlock();
}

//************************************************
//�`���[�g���A���f�U�C���`��
//************************************************
void DrawTutorialDesign(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialDesign, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TexMax; i++)
	{
		pDevice->SetTexture(0, g_pTextureTutorialDesign[i]);

		//�`���[�g���A���f�U�C���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfoTutorialDesign(void)
{
	for (int i = 0; i < TexMax; i++)
	{
		g_aTutorialDesign[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorialDesign[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorialDesign[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTutorialDesign[i].F = 1.0f;	//�ėp

		g_aTutorialDesign[i].pos = D3DXVECTOR3((float)SCREEN_HALFWIDTH, (float)SCREEN_HALFHEIGHT, 0.0f);
		g_aTutorialDesign[i].sizeX = (float)SCREEN_HALFWIDTH;
		g_aTutorialDesign[i].sizeY = (float)SCREEN_HALFHEIGHT;
	}
}

//************************************************
//�G���킭���ǂ�������
//************************************************
bool* GetInfoSpawnEnemy(void)
{
	return &g_bSpawn;
}

//************************************************
//�G���Ԃ���������
//************************************************
bool* GetInfoStampEnemy(void)
{
	return &g_bStamp;
}