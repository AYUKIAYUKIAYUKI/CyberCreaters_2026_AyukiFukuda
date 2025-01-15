//************************************************
//
//�|�[�Y��ʃJ�[�\������[pause_cursor.cpp]
//Author�F���c����
//
//************************************************
#include "input.h"
#include "sound.h"
#include "pause_cursor.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Pause_Cursor[AMOUNT_TEXTURE_PAUSE_CURSOR] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Pause_Cursor = NULL;	//���_�o�b�t�@�̃|�C���^
PAUSE_CURSOR g_aPause_Cursor[AMOUNT_POLYGON_PAUSE_CURSOR];	//�J�[�\���p�|���S���̏����i�[
int g_nChoosing_Pause_Cursor = 0;	//������I��ł�
float g_fRotateSPD_Pause_Cursor = 0.0f;
int g_nLine = 0;
int g_nRow = 0;

//************************************************
//�����������֐�
//************************************************
void Init_Pause_Cursor(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PAUSE_CURSOR,
		&g_pTexture_Pause_Cursor[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_PAUSE_CURSOR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Pause_Cursor,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Pause_Cursor;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Pause_Cursor->Lock(0, 0, (void**)&pVtx_Pause_Cursor, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_CURSOR; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Pause_Cursor[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Pause_Cursor[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Pause_Cursor[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Pause_Cursor[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Pause_Cursor[0].rhw = 1.0f;
		pVtx_Pause_Cursor[1].rhw = 1.0f;
		pVtx_Pause_Cursor[2].rhw = 1.0f;
		pVtx_Pause_Cursor[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Pause_Cursor[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Pause_Cursor[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Pause_Cursor[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Pause_Cursor[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Pause_Cursor[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Pause_Cursor[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Pause_Cursor[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Pause_Cursor[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Pause_Cursor += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Pause_Cursor->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_CURSOR; nCnt++)
	{
		g_aPause_Cursor[nCnt].nStyle = 0;
		g_aPause_Cursor[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Cursor[nCnt].fSpanX = 0.0f;
		g_aPause_Cursor[nCnt].fSpanY = 0.0f;
		g_aPause_Cursor[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Cursor[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Cursor[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aPause_Cursor[nCnt].fLength = 0.0f;
		g_aPause_Cursor[nCnt].fAngle = 0.0f;
		g_aPause_Cursor[nCnt].nCntStop = 0;
		g_aPause_Cursor[nCnt].bTurn = false;
		g_aPause_Cursor[nCnt].colA = 0.0f;
	}

	//���I��ł���̏�����
	g_nChoosing_Pause_Cursor = 0;

	g_fRotateSPD_Pause_Cursor = -0.001f;

	g_nLine = 0;
	g_nRow = 0;

	//����̂ݒ��_��W�J
	Setinfo_Pause_Cursor();
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Pause_Cursor(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_PAUSE_CURSOR; nCnt++)
	{
		if (g_pTexture_Pause_Cursor[nCnt] != NULL)
		{
			g_pTexture_Pause_Cursor[nCnt]->Release();
			g_pTexture_Pause_Cursor[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Pause_Cursor != NULL)
	{
		g_pVtxBuff_Pause_Cursor->Release();
		g_pVtxBuff_Pause_Cursor = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Pause_Cursor(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Pause_Cursor;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Pause_Cursor->Lock(0, 0, (void**)&pVtx_Pause_Cursor, 0);

	if (GetKeyboardTrigger(DIK_LEFT) == true || GetJoypadTrigger(JOYKEY_LEFT) == true)
	{
		if (g_nLine > 0)
		{
			g_nLine--;

			//���ʉ���炷
			PlaySound(SOUND_LABEL_SE_SELECT1);
		}
	}
	else if (GetKeyboardTrigger(DIK_RIGHT) == true || GetJoypadTrigger(JOYKEY_RIGHT) == true)
	{
		if (g_nLine < 1)
		{
			g_nLine++;

			//���ʉ���炷
			PlaySound(SOUND_LABEL_SE_SELECT1);
		}
	}

	if (GetKeyboardTrigger(DIK_UP) == true || GetJoypadTrigger(JOYKEY_UP) == true)
	{
		if (g_nRow > 0)
		{
			g_nRow--;

			//���ʉ���炷
			PlaySound(SOUND_LABEL_SE_SELECT1);
		}
	}
	else if (GetKeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true)
	{
		if (g_nRow < 1)
		{
			g_nRow++;

			//���ʉ���炷
			PlaySound(SOUND_LABEL_SE_SELECT1);
		}
	}

	if (g_nLine == 0 && g_nRow == 0)
	{
		g_nChoosing_Pause_Cursor = 0;
	}
	else if (g_nLine == 1 && g_nRow == 0)
	{
		g_nChoosing_Pause_Cursor = 1;
	}
	else if (g_nLine == 0 && g_nRow == 1)
	{
		g_nChoosing_Pause_Cursor = 2;
	}
	else if (g_nLine == 1 && g_nRow == 1)
	{
		g_nChoosing_Pause_Cursor = 3;
	}

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_CURSOR; nCnt++)
	{
		if (g_aPause_Cursor[nCnt].colA < 1.0f)
		{
			g_aPause_Cursor[nCnt].colA *= 1.2f;
		}
		else
		{
			g_aPause_Cursor[nCnt].colA = 1.0;
		}

		g_aPause_Cursor[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aPause_Cursor[nCnt].colA);

		if (g_nLine == 0)
		{
			if (g_aPause_Cursor[nCnt].pos.x > 1100.0f)
			{
				if (g_aPause_Cursor[nCnt].move.x < 50.0f)
				{
					g_aPause_Cursor[nCnt].move.x += 20.0f;
				}
			}
			else
			{
				if (g_aPause_Cursor[nCnt].move.x > 0.0f)
				{
					g_aPause_Cursor[nCnt].move.x -= 10.0f;
				}
			}

			g_aPause_Cursor[nCnt].pos.x -= g_aPause_Cursor[nCnt].move.x;
		}
		else
		{
			if (g_aPause_Cursor[nCnt].pos.x < 1350.0f)
			{
				if (g_aPause_Cursor[nCnt].move.x < 50.0f)
				{
					g_aPause_Cursor[nCnt].move.x += 20.0f;
				}
			}
			else
			{
				if (g_aPause_Cursor[nCnt].move.x > 0.0f)
				{
					g_aPause_Cursor[nCnt].move.x -= 10.0f;
				}
			}

			g_aPause_Cursor[nCnt].pos.x += g_aPause_Cursor[nCnt].move.x;
		}

		if (g_nRow == 0)
		{
			if (g_aPause_Cursor[nCnt].pos.y > 650.0f)
			{
				if (g_aPause_Cursor[nCnt].move.y < 30.0f)
				{
					g_aPause_Cursor[nCnt].move.y += 20.0f;
				}
			}
			else
			{
				if (g_aPause_Cursor[nCnt].move.y > 0.0f)
				{
					g_aPause_Cursor[nCnt].move.y -= 10.0f;
				}
			}

			g_aPause_Cursor[nCnt].pos.y -= g_aPause_Cursor[nCnt].move.y;
		}
		else
		{
			if (g_aPause_Cursor[nCnt].pos.y < 670.0f)
			{
				if (g_aPause_Cursor[nCnt].move.y < 30.0f)
				{
					g_aPause_Cursor[nCnt].move.y += 20.0f;
				}
			}
			else
			{
				if (g_aPause_Cursor[nCnt].move.y > 0.0f)
				{
					g_aPause_Cursor[nCnt].move.y -= 10.0f;
				}
			}

			g_aPause_Cursor[nCnt].pos.y += g_aPause_Cursor[nCnt].move.y;
		}

		//�ړ��𔽉f
		pVtx_Pause_Cursor[0].pos.x = g_aPause_Cursor[nCnt].pos.x + sinf(g_aPause_Cursor[nCnt].rot.z - (D3DX_PI - g_aPause_Cursor[nCnt].fAngle)) * g_aPause_Cursor[nCnt].fLength;
		pVtx_Pause_Cursor[0].pos.y = g_aPause_Cursor[nCnt].pos.y + cosf(g_aPause_Cursor[nCnt].rot.z - (D3DX_PI - g_aPause_Cursor[nCnt].fAngle)) * g_aPause_Cursor[nCnt].fLength;
		pVtx_Pause_Cursor[1].pos.x = g_aPause_Cursor[nCnt].pos.x + sinf(g_aPause_Cursor[nCnt].rot.z + (D3DX_PI - g_aPause_Cursor[nCnt].fAngle)) * g_aPause_Cursor[nCnt].fLength;
		pVtx_Pause_Cursor[1].pos.y = g_aPause_Cursor[nCnt].pos.y + cosf(g_aPause_Cursor[nCnt].rot.z + (D3DX_PI - g_aPause_Cursor[nCnt].fAngle)) * g_aPause_Cursor[nCnt].fLength;
		pVtx_Pause_Cursor[2].pos.x = g_aPause_Cursor[nCnt].pos.x + sinf(g_aPause_Cursor[nCnt].rot.z - g_aPause_Cursor[nCnt].fAngle) * g_aPause_Cursor[nCnt].fLength;
		pVtx_Pause_Cursor[2].pos.y = g_aPause_Cursor[nCnt].pos.y + cosf(g_aPause_Cursor[nCnt].rot.z - g_aPause_Cursor[nCnt].fAngle) * g_aPause_Cursor[nCnt].fLength;
		pVtx_Pause_Cursor[3].pos.x = g_aPause_Cursor[nCnt].pos.x + sinf(g_aPause_Cursor[nCnt].rot.z + g_aPause_Cursor[nCnt].fAngle) * g_aPause_Cursor[nCnt].fLength;
		pVtx_Pause_Cursor[3].pos.y = g_aPause_Cursor[nCnt].pos.y + cosf(g_aPause_Cursor[nCnt].rot.z + g_aPause_Cursor[nCnt].fAngle) * g_aPause_Cursor[nCnt].fLength;

		pVtx_Pause_Cursor[0].col = g_aPause_Cursor[nCnt].col;
		pVtx_Pause_Cursor[1].col = g_aPause_Cursor[nCnt].col;
		pVtx_Pause_Cursor[2].col = g_aPause_Cursor[nCnt].col;
		pVtx_Pause_Cursor[3].col = g_aPause_Cursor[nCnt].col;

		pVtx_Pause_Cursor += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Pause_Cursor->Unlock();

	//���肮��A�j���[�V����
	Animation_Pause_Cursor();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Pause_Cursor(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Pause_Cursor, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_CURSOR; nCnt++)
	{
		switch (g_aPause_Cursor[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Pause_Cursor[0]);

			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Pause_Cursor(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_CURSOR; nCnt++)
	{
		g_aPause_Cursor[nCnt].nStyle = nCnt;
		g_aPause_Cursor[nCnt].pos = D3DXVECTOR3(700.0f + 250.0f, 400.0f + 160.0f, 0.0f);
		g_aPause_Cursor[nCnt].fSpanX = 40.0f;
		g_aPause_Cursor[nCnt].fSpanY = 40.0f;
		g_aPause_Cursor[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Cursor[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPause_Cursor[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		g_aPause_Cursor[nCnt].fLength = sqrtf((g_aPause_Cursor[nCnt].fSpanX * g_aPause_Cursor[nCnt].fSpanX) + (g_aPause_Cursor[nCnt].fSpanY * g_aPause_Cursor[nCnt].fSpanY));
		g_aPause_Cursor[nCnt].fAngle = atan2f(g_aPause_Cursor[nCnt].fSpanX * 2.0f, g_aPause_Cursor[nCnt].fSpanX * 2.0f);
		g_aPause_Cursor[nCnt].nCntStop = 0;
		g_aPause_Cursor[nCnt].bTurn = false;
		g_aPause_Cursor[nCnt].colA = 0.01f;
	}
}

//************************************************
//���肮��A�j���[�V�����֐�
//************************************************
void Animation_Pause_Cursor(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Pause_Cursor;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Pause_Cursor->Lock(0, 0, (void**)&pVtx_Pause_Cursor, 0);

	//��]�̔��f
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PAUSE_CURSOR; nCnt++)
	{
		if (g_aPause_Cursor[nCnt].rot.z > -0.6f && !g_aPause_Cursor[nCnt].bTurn)
		{
			g_fRotateSPD_Pause_Cursor *= 1.1f;

			g_aPause_Cursor[nCnt].rot.z += g_fRotateSPD_Pause_Cursor;
		}
		else
		{
			g_aPause_Cursor[nCnt].bTurn = true;

			g_aPause_Cursor[nCnt].nCntStop++;

			if (g_aPause_Cursor[nCnt].nCntStop > 9)
			{
				g_aPause_Cursor[nCnt].rot.z += 0.075f;

				if (g_aPause_Cursor[nCnt].rot.z >= 0.0f)
				{
					g_aPause_Cursor[nCnt].nCntStop = 0;

					g_aPause_Cursor[nCnt].rot.z = 0.0f;

					g_aPause_Cursor[nCnt].bTurn = false;

					g_fRotateSPD_Pause_Cursor = -0.001f;
				}
			}
		}

		pVtx_Pause_Cursor[0].pos.x = g_aPause_Cursor[nCnt].pos.x + sinf(g_aPause_Cursor[nCnt].rot.z - (D3DX_PI - g_aPause_Cursor[nCnt].fAngle)) * g_aPause_Cursor[nCnt].fLength;
		pVtx_Pause_Cursor[0].pos.y = g_aPause_Cursor[nCnt].pos.y + cosf(g_aPause_Cursor[nCnt].rot.z - (D3DX_PI - g_aPause_Cursor[nCnt].fAngle)) * g_aPause_Cursor[nCnt].fLength;
		pVtx_Pause_Cursor[1].pos.x = g_aPause_Cursor[nCnt].pos.x + sinf(g_aPause_Cursor[nCnt].rot.z + (D3DX_PI - g_aPause_Cursor[nCnt].fAngle)) * g_aPause_Cursor[nCnt].fLength;
		pVtx_Pause_Cursor[1].pos.y = g_aPause_Cursor[nCnt].pos.y + cosf(g_aPause_Cursor[nCnt].rot.z + (D3DX_PI - g_aPause_Cursor[nCnt].fAngle)) * g_aPause_Cursor[nCnt].fLength;
		pVtx_Pause_Cursor[2].pos.x = g_aPause_Cursor[nCnt].pos.x + sinf(g_aPause_Cursor[nCnt].rot.z - g_aPause_Cursor[nCnt].fAngle) * g_aPause_Cursor[nCnt].fLength;
		pVtx_Pause_Cursor[2].pos.y = g_aPause_Cursor[nCnt].pos.y + cosf(g_aPause_Cursor[nCnt].rot.z - g_aPause_Cursor[nCnt].fAngle) * g_aPause_Cursor[nCnt].fLength;
		pVtx_Pause_Cursor[3].pos.x = g_aPause_Cursor[nCnt].pos.x + sinf(g_aPause_Cursor[nCnt].rot.z + g_aPause_Cursor[nCnt].fAngle) * g_aPause_Cursor[nCnt].fLength;
		pVtx_Pause_Cursor[3].pos.y = g_aPause_Cursor[nCnt].pos.y + cosf(g_aPause_Cursor[nCnt].rot.z + g_aPause_Cursor[nCnt].fAngle) * g_aPause_Cursor[nCnt].fLength;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Pause_Cursor->Unlock();
}

//************************************************
//�I���󋵂������n���֐�
//************************************************
int* Getinfo_Choose_Pause(void)
{
	return &g_nChoosing_Pause_Cursor;
}