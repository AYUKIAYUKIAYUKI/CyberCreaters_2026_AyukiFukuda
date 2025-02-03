//************************************************
//
//���j���[�̃J�[�\������[cursor.cpp]
//Author�F���c����
//
//************************************************
#include "input.h"
#include "sound.h"
#include "cursorh.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Cursor[AMOUNT_TEXTURE_CURSOR] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Cursor = NULL;	//���_�o�b�t�@�̃|�C���^
CURSOR g_aCursor[AMOUNT_POLYGON_CURSOR];	//�J�[�\���p�|���S���̏����i�[
int g_nChoosing = 0;	//������I��ł�
float g_fRotateSPD = 0.0f;

//************************************************
//�����������֐�
//************************************************
void Init_Cursor(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CURSOR,
		&g_pTexture_Cursor[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_CURSOR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Cursor,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Cursor;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Cursor->Lock(0, 0, (void**)&pVtx_Cursor, 0);

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_CURSOR; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Cursor[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Cursor[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Cursor[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Cursor[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Cursor[0].rhw = 1.0f;
		pVtx_Cursor[1].rhw = 1.0f;
		pVtx_Cursor[2].rhw = 1.0f;
		pVtx_Cursor[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Cursor[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Cursor[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Cursor[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Cursor[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Cursor[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Cursor[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Cursor[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Cursor[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Cursor += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Cursor->Unlock();

	//�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_CURSOR; nCnt++)
	{
		g_aCursor[nCnt].nStyle = 0;
		g_aCursor[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCursor[nCnt].fSpanX = 0.0f;
		g_aCursor[nCnt].fSpanY = 0.0f;
		g_aCursor[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCursor[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCursor[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aCursor[nCnt].fLength = 0.0f;
		g_aCursor[nCnt].fAngle = 0.0f;
		g_aCursor[nCnt].nCntStop = 0;
		g_aCursor[nCnt].bTurn = false;
	}

	//���I��ł���̏�����
	g_nChoosing = 0;

	g_fRotateSPD = -0.001f;

	//����̂ݒ��_��W�J
	Setinfo_Cursor();
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Cursor(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_CURSOR; nCnt++)
	{
		if (g_pTexture_Cursor[nCnt] != NULL)
		{
			g_pTexture_Cursor[nCnt]->Release();
			g_pTexture_Cursor[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Cursor != NULL)
	{
		g_pVtxBuff_Cursor->Release();
		g_pVtxBuff_Cursor = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Cursor(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Cursor;

	bool* pStart;
	pStart = Getinfo_Menu();

	bool* pPopup;
	pPopup = Getinfo_Tutorial_Menu();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Cursor->Lock(0, 0, (void**)&pVtx_Cursor, 0);

	if (*pStart == false && *pPopup == false)
	{
		if (GetKeyboardTrigger(DIK_LEFT) == true || GetJoypadTrigger(JOYKEY_LEFT) == true)
		{
			if (g_nChoosing > 0)
			{
				g_nChoosing--;

				//���ʉ���炷
				PlaySound(SOUND_LABEL_SE_SELECT1);
			}
		}
		else if (GetKeyboardTrigger(DIK_RIGHT) == true || GetJoypadTrigger(JOYKEY_RIGHT) == true)
		{
			if (g_nChoosing < 1)
			{
				g_nChoosing++;

				//���ʉ���炷
				PlaySound(SOUND_LABEL_SE_SELECT1);
			}
		}
	}

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_CURSOR; nCnt++)
	{
		if (g_nChoosing == 0)
		{
			//g_aCursor[nCnt].pos = D3DXVECTOR3(820.0f, 760.0f, 0.0f);

			if (g_aCursor[nCnt].pos.x > 1035.0f)
			{
				if (g_aCursor[nCnt].move.x < 50.0f)
				{
					g_aCursor[nCnt].move.x += 20.0f;
				}
			}
			else
			{
				if (g_aCursor[nCnt].move.x > 0.0f)
				{
					g_aCursor[nCnt].move.x -= 10.0f;
				}
			}

			g_aCursor[nCnt].pos.x -= g_aCursor[nCnt].move.x;
		}
		else
		{
			//g_aCursor[nCnt].pos = D3DXVECTOR3(1830.0f, 760.0f, 0.0f);

			if (g_aCursor[nCnt].pos.x < 1615.0f)
			{
				if (g_aCursor[nCnt].move.x < 50.0f)
				{
					g_aCursor[nCnt].move.x += 20.0f;
				}
			}
			else
			{
				if (g_aCursor[nCnt].move.x > 0.0f)
				{
					g_aCursor[nCnt].move.x -= 10.0f;
				}
			}

			g_aCursor[nCnt].pos.x += g_aCursor[nCnt].move.x;
		}

		//�ړ��𔽉f
		pVtx_Cursor[0].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z - (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[0].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z - (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[1].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z + (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[1].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z + (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[2].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z - g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[2].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z - g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[3].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z + g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[3].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z + g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;

		pVtx_Cursor[0].col = g_aCursor[nCnt].col;
		pVtx_Cursor[1].col = g_aCursor[nCnt].col;
		pVtx_Cursor[2].col = g_aCursor[nCnt].col;
		pVtx_Cursor[3].col = g_aCursor[nCnt].col;

		pVtx_Cursor += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Cursor->Unlock();

	//���肮��A�j���[�V����
	Animation_Cursor();
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Cursor(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Cursor, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_CURSOR; nCnt++)
	{
		switch (g_aCursor[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Cursor[0]);

			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Cursor(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_CURSOR; nCnt++)
	{
		g_aCursor[nCnt].nStyle = nCnt;
		g_aCursor[nCnt].pos = D3DXVECTOR3(570.0f + 295.0f, 650.0f + 285.0f, 0.0f);
		g_aCursor[nCnt].fSpanX = 50.0f;
		g_aCursor[nCnt].fSpanY = 50.0f;
		g_aCursor[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCursor[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCursor[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aCursor[nCnt].fLength = sqrtf((g_aCursor[nCnt].fSpanX * g_aCursor[nCnt].fSpanX) + (g_aCursor[nCnt].fSpanY * g_aCursor[nCnt].fSpanY));
		g_aCursor[nCnt].fAngle = atan2f(g_aCursor[nCnt].fSpanX * 2.0f, g_aCursor[nCnt].fSpanX * 2.0f);
		g_aCursor[nCnt].nCntStop = 0;
		g_aCursor[nCnt].bTurn = false;
	}
}

//************************************************
//���肮��A�j���[�V�����֐�
//************************************************
void Animation_Cursor(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Cursor;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Cursor->Lock(0, 0, (void**)&pVtx_Cursor, 0);

	//��]�̔��f
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_CURSOR; nCnt++)
	{
		if (g_aCursor[nCnt].rot.z > -0.6f && !g_aCursor[nCnt].bTurn)
		{
			g_fRotateSPD *= 1.1f;

			g_aCursor[nCnt].rot.z += g_fRotateSPD;
		}
		else
		{
			g_aCursor[nCnt].bTurn = true;
			
			g_aCursor[nCnt].nCntStop++;
		
			if (g_aCursor[nCnt].nCntStop > 9)
			{
				g_aCursor[nCnt].rot.z += 0.075f;

				if (g_aCursor[nCnt].rot.z >= 0.0f)
				{
					g_aCursor[nCnt].nCntStop = 0;

					g_aCursor[nCnt].rot.z = 0.0f;

					g_aCursor[nCnt].bTurn = false;

					g_fRotateSPD = -0.001f;
				}
			}
		}

		pVtx_Cursor[0].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z - (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[0].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z - (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[1].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z + (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[1].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z + (D3DX_PI - g_aCursor[nCnt].fAngle)) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[2].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z - g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[2].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z - g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[3].pos.x = g_aCursor[nCnt].pos.x + sinf(g_aCursor[nCnt].rot.z + g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;
		pVtx_Cursor[3].pos.y = g_aCursor[nCnt].pos.y + cosf(g_aCursor[nCnt].rot.z + g_aCursor[nCnt].fAngle) * g_aCursor[nCnt].fLength;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Cursor->Unlock();
}

//************************************************
//�I���󋵂������n���֐�
//************************************************
int* Getinfo_Choose(void)
{
	return &g_nChoosing;
}