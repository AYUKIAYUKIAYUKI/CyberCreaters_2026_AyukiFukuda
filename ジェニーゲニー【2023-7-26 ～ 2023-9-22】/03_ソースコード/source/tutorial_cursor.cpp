//************************************************
//
//���j���[�̃J�[�\������[tutorial_cursor.cpp]
//Author�F���c����
//
//************************************************
#include "input.h"
#include "sound.h"
#include "tutorial_cursor.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Tutorial_Cursor[AMOUNT_TEXTURE_TUTORIAL_CURSOR] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Tutorial_Cursor = NULL;	//���_�o�b�t�@�̃|�C���^
TUTORIAL_CURSOR g_aTutorial_Cursor[AMOUNT_POLYGON_TUTORIAL_CURSOR];	//�J�[�\���p�|���S���̏����i�[
int g_nChoosing_Tutorial_Cursor = 0;	//������I��ł�
float g_fRotateSPD_Tutorial_Cursor = 0.0f;

//************************************************
//�����������֐�
//************************************************
void Init_Tutorial_Cursor(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TUTORIAL_CURSOR,
		&g_pTexture_Tutorial_Cursor[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TUTORIAL_CURSOR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Tutorial_Cursor,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Tutorial_Cursor;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Tutorial_Cursor->Lock(0, 0, (void**)&pVtx_Tutorial_Cursor, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_CURSOR; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Tutorial_Cursor[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Cursor[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Cursor[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial_Cursor[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Tutorial_Cursor[0].rhw = 1.0f;
		pVtx_Tutorial_Cursor[1].rhw = 1.0f;
		pVtx_Tutorial_Cursor[2].rhw = 1.0f;
		pVtx_Tutorial_Cursor[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Tutorial_Cursor[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Cursor[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Cursor[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Tutorial_Cursor[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Tutorial_Cursor[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Tutorial_Cursor[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Tutorial_Cursor[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Tutorial_Cursor[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Tutorial_Cursor += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Tutorial_Cursor->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_CURSOR; nCnt++)
	{
		g_aTutorial_Cursor[nCnt].nStyle = 0;
		g_aTutorial_Cursor[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].fSpanX = 0.0f;
		g_aTutorial_Cursor[nCnt].fSpanY = 0.0f;
		g_aTutorial_Cursor[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].fLength = 0.0f;
		g_aTutorial_Cursor[nCnt].fAngle = 0.0f;
		g_aTutorial_Cursor[nCnt].nCntStop = 0;
		g_aTutorial_Cursor[nCnt].bTurn = false;
		g_aTutorial_Cursor[nCnt].colA = 0.0f;
	}

	//���I��ł���̏�����
	g_nChoosing_Tutorial_Cursor = 0;

	g_fRotateSPD_Tutorial_Cursor = -0.001f;

	//����̂ݒ��_��W�J
	Setinfo_Tutorial_Cursor();
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Tutorial_Cursor(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_TUTORIAL_CURSOR; nCnt++)
	{
		if (g_pTexture_Tutorial_Cursor[nCnt] != NULL)
		{
			g_pTexture_Tutorial_Cursor[nCnt]->Release();
			g_pTexture_Tutorial_Cursor[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Tutorial_Cursor != NULL)
	{
		g_pVtxBuff_Tutorial_Cursor->Release();
		g_pVtxBuff_Tutorial_Cursor = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Tutorial_Cursor(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Tutorial_Cursor;

	bool* pStart;
	pStart = Getinfo_Menu();

	bool* pPopup;
	pPopup = Getinfo_Tutorial_Menu();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Tutorial_Cursor->Lock(0, 0, (void**)&pVtx_Tutorial_Cursor, 0);

	if (*pStart == false && *pPopup == true)
	{
		if (GetKeyboardTrigger(DIK_LEFT) == true || GetJoypadTrigger(JOYKEY_LEFT) == true)
		{
			if (g_nChoosing_Tutorial_Cursor > 0)
			{
				g_nChoosing_Tutorial_Cursor--;

				//���ʉ���炷
				PlaySound(SOUND_LABEL_SE_SELECT1);
			}
		}
		else if (GetKeyboardTrigger(DIK_RIGHT) == true || GetJoypadTrigger(JOYKEY_RIGHT) == true)
		{
			if (g_nChoosing_Tutorial_Cursor < 1)
			{
				g_nChoosing_Tutorial_Cursor++;

				//���ʉ���炷
				PlaySound(SOUND_LABEL_SE_SELECT1);
			}
		}
	}

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_CURSOR; nCnt++)
	{
		if (g_aTutorial_Cursor[nCnt].colA < 1.0f)
		{
			g_aTutorial_Cursor[nCnt].colA *= 1.1f;
		}
		else
		{
			g_aTutorial_Cursor[nCnt].colA = 1.0;
		}

		g_aTutorial_Cursor[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aTutorial_Cursor[nCnt].colA);

		if (g_nChoosing_Tutorial_Cursor == 0)
		{
			if (g_aTutorial_Cursor[nCnt].pos.x > 1020.0f)
			{
				if (g_aTutorial_Cursor[nCnt].move.x < 50.0f)
				{
					g_aTutorial_Cursor[nCnt].move.x += 20.0f;
				}
			}
			else
			{
				if (g_aTutorial_Cursor[nCnt].move.x > 0.0f)
				{
					g_aTutorial_Cursor[nCnt].move.x -= 10.0f;
				}
			}

			g_aTutorial_Cursor[nCnt].pos.x -= g_aTutorial_Cursor[nCnt].move.x;
		}
		else
		{
			if (g_aTutorial_Cursor[nCnt].pos.x < 1250.0f)
			{
				if (g_aTutorial_Cursor[nCnt].move.x < 50.0f)
				{
					g_aTutorial_Cursor[nCnt].move.x += 20.0f;
				}
			}
			else
			{
				if (g_aTutorial_Cursor[nCnt].move.x > 0.0f)
				{
					g_aTutorial_Cursor[nCnt].move.x -= 10.0f;
				}
			}

			g_aTutorial_Cursor[nCnt].pos.x += g_aTutorial_Cursor[nCnt].move.x;
		}

		//�ړ��𔽉f
		pVtx_Tutorial_Cursor[0].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z - (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[0].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z - (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[1].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z + (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[1].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z + (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[2].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z - g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[2].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z - g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[3].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z + g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[3].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z + g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;

		pVtx_Tutorial_Cursor[0].col = g_aTutorial_Cursor[nCnt].col;
		pVtx_Tutorial_Cursor[1].col = g_aTutorial_Cursor[nCnt].col;
		pVtx_Tutorial_Cursor[2].col = g_aTutorial_Cursor[nCnt].col;
		pVtx_Tutorial_Cursor[3].col = g_aTutorial_Cursor[nCnt].col;

		pVtx_Tutorial_Cursor += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Tutorial_Cursor->Unlock();

	//���肮��A�j���[�V����
	Animation_Tutorial_Cursor();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Tutorial_Cursor(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Tutorial_Cursor, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_CURSOR; nCnt++)
	{
		switch (g_aTutorial_Cursor[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Tutorial_Cursor[0]);

			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Tutorial_Cursor(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_CURSOR; nCnt++)
	{
		g_aTutorial_Cursor[nCnt].nStyle = nCnt;
		g_aTutorial_Cursor[nCnt].pos = D3DXVECTOR3(750.0f + 120.0f, 600.0f + 125.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].fSpanX = 50.0f;
		g_aTutorial_Cursor[nCnt].fSpanY = 50.0f;
		g_aTutorial_Cursor[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		g_aTutorial_Cursor[nCnt].fLength = sqrtf((g_aTutorial_Cursor[nCnt].fSpanX * g_aTutorial_Cursor[nCnt].fSpanX) + (g_aTutorial_Cursor[nCnt].fSpanY * g_aTutorial_Cursor[nCnt].fSpanY));
		g_aTutorial_Cursor[nCnt].fAngle = atan2f(g_aTutorial_Cursor[nCnt].fSpanX * 2.0f, g_aTutorial_Cursor[nCnt].fSpanX * 2.0f);
		g_aTutorial_Cursor[nCnt].nCntStop = 0;
		g_aTutorial_Cursor[nCnt].bTurn = false;
		g_aTutorial_Cursor[nCnt].colA = 0.01f;
	}
}

//************************************************
//���肮��A�j���[�V�����֐�
//************************************************
void Animation_Tutorial_Cursor(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Tutorial_Cursor;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Tutorial_Cursor->Lock(0, 0, (void**)&pVtx_Tutorial_Cursor, 0);

	//��]�̔��f
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_CURSOR; nCnt++)
	{
		if (g_aTutorial_Cursor[nCnt].rot.z > -0.6f && !g_aTutorial_Cursor[nCnt].bTurn)
		{
			g_fRotateSPD_Tutorial_Cursor *= 1.1f;

			g_aTutorial_Cursor[nCnt].rot.z += g_fRotateSPD_Tutorial_Cursor;
		}
		else
		{
			g_aTutorial_Cursor[nCnt].bTurn = true;

			g_aTutorial_Cursor[nCnt].nCntStop++;

			if (g_aTutorial_Cursor[nCnt].nCntStop > 9)
			{
				g_aTutorial_Cursor[nCnt].rot.z += 0.075f;

				if (g_aTutorial_Cursor[nCnt].rot.z >= 0.0f)
				{
					g_aTutorial_Cursor[nCnt].nCntStop = 0;

					g_aTutorial_Cursor[nCnt].rot.z = 0.0f;

					g_aTutorial_Cursor[nCnt].bTurn = false;

					g_fRotateSPD_Tutorial_Cursor = -0.001f;
				}
			}
		}

		pVtx_Tutorial_Cursor[0].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z - (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[0].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z - (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[1].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z + (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[1].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z + (D3DX_PI - g_aTutorial_Cursor[nCnt].fAngle)) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[2].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z - g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[2].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z - g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[3].pos.x = g_aTutorial_Cursor[nCnt].pos.x + sinf(g_aTutorial_Cursor[nCnt].rot.z + g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;
		pVtx_Tutorial_Cursor[3].pos.y = g_aTutorial_Cursor[nCnt].pos.y + cosf(g_aTutorial_Cursor[nCnt].rot.z + g_aTutorial_Cursor[nCnt].fAngle) * g_aTutorial_Cursor[nCnt].fLength;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Tutorial_Cursor->Unlock();
}

//************************************************
//�I���󋵂������n���֐�
//************************************************
int* Getinfo_Choose_YesNo(void)
{
	return &g_nChoosing_Tutorial_Cursor;
}