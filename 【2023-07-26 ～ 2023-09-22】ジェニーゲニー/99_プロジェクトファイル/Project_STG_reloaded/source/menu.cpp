//************************************************
//
//���j���[�\������[menu.cpp]
//Author�F���c����
//
//************************************************
#include "input.h"
#include "sound.h"
#include "menu.h"
#include "cursorh.h"
#include "fade.h"
#include "select_mode.h"
#include "square.h"
#include "text_mode.h"
#include "tutorial_cursor.h"
#include "tutorial_select.h"
#include "tutorial_window.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Menu[AMOUNT_TEXTURE_MENU] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Menu = NULL;	//���_�o�b�t�@�̃|�C���^
MENU_OBJECT g_aMenu[AMOUNT_POLYGON_MENU];	//���j���[�p�|���S���̏����i�[
bool g_bPopup = false;
bool g_bStart = false;

//************************************************
//�����������֐�
//************************************************
void Init_Menu(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WHITE_MENU,
		&g_pTexture_Menu[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_MENU,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Menu,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Menu;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Menu->Lock(0, 0, (void**)&pVtx_Menu, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_MENU; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Menu[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Menu[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Menu[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Menu[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Menu[0].rhw = 1.0f;
		pVtx_Menu[1].rhw = 1.0f;
		pVtx_Menu[2].rhw = 1.0f;
		pVtx_Menu[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Menu[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Menu[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Menu[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Menu[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Menu[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Menu[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Menu[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Menu[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Menu += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Menu->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_MENU; nCnt++)
	{
		g_aMenu[nCnt].nStyle = 0;
		g_aMenu[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMenu[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMenu[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMenu[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aMenu[nCnt].fLength = 0.0f;
		g_aMenu[nCnt].fAngle = 0.0f;
	}

	//����̂ݒ��_��W�J
	Setinfo_Menu();

	//���̂ق���
	Init_Cursor();
	Init_Fade_Menu();
	Init_Select_Mode();
	Init_Square();
	Init_Text_Mode();
	Init_Tutorial_Cursor();
	Init_Tutorial_Select();
	Init_Tutorial_Window();

	g_bPopup = false;
	g_bStart = false;
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Menu(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_MENU; nCnt++)
	{
		if (g_pTexture_Menu[nCnt] != NULL)
		{
			g_pTexture_Menu[nCnt]->Release();
			g_pTexture_Menu[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Menu != NULL)
	{
		g_pVtxBuff_Menu->Release();
		g_pVtxBuff_Menu = NULL;
	}

	//���̂ق���
	Uninit_Cursor();
	Uninit_Fade_Menu();
	Uninit_Select_Mode();
	Uninit_Square();
	Uninit_Text_Mode();
	Uninit_Tutorial_Cursor();
	Uninit_Tutorial_Select();
	Uninit_Tutorial_Window();
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Menu(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Menu;

	//�I��ł���̂ւ̃|�C���^
	int* pChoose;
	pChoose = Getinfo_Choose();
	int* pChoose_YesNo;
	pChoose_YesNo = Getinfo_Choose_YesNo();

	float* pFade;
	pFade = Getinfo_Fade_Menu();

	if (!g_bPopup)
	{
		//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
		g_pVtxBuff_Menu->Lock(0, 0, (void**)&pVtx_Menu, 0);

		for (int nCnt = 0; nCnt < AMOUNT_POLYGON_MENU; nCnt++)
		{
			//�ړ��A��]�𔽉f
			pVtx_Menu[0].pos.x = g_aMenu[nCnt].pos.x + sinf(g_aMenu[nCnt].rot.z - (D3DX_PI - g_aMenu[nCnt].fAngle)) * g_aMenu[nCnt].fLength;
			pVtx_Menu[0].pos.y = g_aMenu[nCnt].pos.y + cosf(g_aMenu[nCnt].rot.z - (D3DX_PI - g_aMenu[nCnt].fAngle)) * g_aMenu[nCnt].fLength;
			pVtx_Menu[1].pos.x = g_aMenu[nCnt].pos.x + sinf(g_aMenu[nCnt].rot.z + (D3DX_PI - g_aMenu[nCnt].fAngle)) * g_aMenu[nCnt].fLength;
			pVtx_Menu[1].pos.y = g_aMenu[nCnt].pos.y + cosf(g_aMenu[nCnt].rot.z + (D3DX_PI - g_aMenu[nCnt].fAngle)) * g_aMenu[nCnt].fLength;
			pVtx_Menu[2].pos.x = g_aMenu[nCnt].pos.x + sinf(g_aMenu[nCnt].rot.z - g_aMenu[nCnt].fAngle) * g_aMenu[nCnt].fLength;
			pVtx_Menu[2].pos.y = g_aMenu[nCnt].pos.y + cosf(g_aMenu[nCnt].rot.z - g_aMenu[nCnt].fAngle) * g_aMenu[nCnt].fLength;
			pVtx_Menu[3].pos.x = g_aMenu[nCnt].pos.x + sinf(g_aMenu[nCnt].rot.z + g_aMenu[nCnt].fAngle) * g_aMenu[nCnt].fLength;
			pVtx_Menu[3].pos.y = g_aMenu[nCnt].pos.y + cosf(g_aMenu[nCnt].rot.z + g_aMenu[nCnt].fAngle) * g_aMenu[nCnt].fLength;

			//�I��ł���̂ɉ����Ĕw�i�F�ύX
			if (*pChoose == 0)
			{
				//g_aMenu[nCnt].col = D3DXCOLOR(1.0f, 0.85f, 0.5f, 1.0f);

				if (g_aMenu[nCnt].col.r < 1.0f)
				{
					g_aMenu[nCnt].col.r += 0.025f;
				}

				if (g_aMenu[nCnt].col.g < 1.0f)
				{
					g_aMenu[nCnt].col.g += 0.025f;
				}

				if (g_aMenu[nCnt].col.b > 0.5f)
				{
					g_aMenu[nCnt].col.b -= 0.025f;
				}
			}
			else
			{
				//g_aMenu[nCnt].col = D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f);

				if (g_aMenu[nCnt].col.r > 0.7f)
				{
					g_aMenu[nCnt].col.r -= 0.025f;
				}

				if (g_aMenu[nCnt].col.g > 0.7f)
				{
					g_aMenu[nCnt].col.g -= 0.025f;
				}

				if (g_aMenu[nCnt].col.b < 1.0f)
				{
					g_aMenu[nCnt].col.b += 0.025f;
				}
			}

			pVtx_Menu[2].col = g_aMenu[nCnt].col;
			pVtx_Menu[3].col = g_aMenu[nCnt].col;

			pVtx_Menu += AMOUNT_VTX;
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuff_Menu->Unlock();

		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true
			|| GetJoypadTrigger(JOYKEY_A) == true && g_bPopup == false && g_bStart == false)
		{
			//���ʉ���炷
			PlaySound(SOUND_LABEL_SE_SELECT2);

			if (*pChoose == 0)
			{
				g_bPopup = true;
			}
			else
			{
				g_bStart = true;
			}
		}
	}
	else if (g_bPopup && !g_bStart)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true
			|| GetJoypadTrigger(JOYKEY_A) == true && g_bPopup == true && g_bStart == false)
		{
			//���ʉ���炷
			PlaySound(SOUND_LABEL_SE_SELECT2);

			g_bStart = true;
		}

		Update_Tutorial_Cursor();
		Update_Tutorial_Select();
		Update_Tutorial_Window();
	}

	if (g_bPopup && g_bStart)
	{
		Update_Tutorial_Cursor();
		Update_Tutorial_Select();
		Update_Tutorial_Window();
	}

	//���̂ق���
	Update_Cursor();
	Update_Fade_Menu();
	Update_Select_Mode();
	Update_Square();
	Update_Text_Mode();

	if (g_bStart)
	{
		if (*pFade > 1.1f)
		{
			if (*pChoose == 0)
			{
				if (*pChoose_YesNo == 0)
				{
					Setinfo_Mode(MODE_TUTORIAL);	//�`���[�g���A�����[�h��
				}
				else
				{
					Setinfo_Mode(MODE_GAME);	//�Q�[�����[�h��
				}
			}
			else
			{
				Setinfo_Mode(MODE_RANKING);	//�����L���O���[�h��
			}
		}
	}
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Menu(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Menu, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_MENU; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Menu[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//���̂ق���(���C���[����)
	Draw_Square();
	Draw_Cursor();
	Draw_Select_Mode();
	Draw_Text_Mode();

	Draw_Tutorial_Window();
	Draw_Tutorial_Cursor();
	Draw_Tutorial_Select();

	Draw_Fade_Menu();
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Menu(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_MENU; nCnt++)
	{
		g_aMenu[nCnt].nStyle = 0;
		g_aMenu[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
		g_aMenu[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMenu[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aMenu[nCnt].fLength = sqrtf((990.0f * 990.0f) + (540.0f * 540.0f));
		g_aMenu[nCnt].fAngle = atan2f(990.0f * 2.0f, 540.0f * 2.0f);
	}
}

//************************************************
//�`���[�g���A�����𑗂�֐�
//************************************************
bool* Getinfo_Tutorial_Menu(void)
{
	return &g_bPopup;
}

//************************************************
//�J�n���𑗂�֐�
//************************************************
bool* Getinfo_Menu(void)
{
	return &g_bStart;
}