//************************************************
//
//�O�i����(�N�\�R�[�h����)[fg.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "fg.h"
#include "timer.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_FG[AMOUNT_TEXTURE_FG] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_FG = NULL;	//���_�o�b�t�@�̃|�C���^
FG_OBJECT g_aObject[AMOUNT_POLYGON_FG];	//�O�i�|���S���p���\����
float g_fLength_Object[2] = {};	//�Ίp�������i�[
float g_fAngle_Object[2] = {};	//�p�x�����i�[
int g_nStartingSet_Ivy = 0;	//�J��������ʓ��Ƀc�^��u������

//************************************************
//�|���S�������������֐�
//************************************************
void Init_FG(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_IVY_1,
		&g_pTexture_FG[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_IVY_2,
		&g_pTexture_FG[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_IVY_3,
		&g_pTexture_FG[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_FG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_FG,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_FG;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_FG->Lock(0, 0, (void**)&pVtx_FG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FG; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_FG[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_FG[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_FG[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_FG[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_FG[0].rhw = 1.0f;
		pVtx_FG[1].rhw = 1.0f;
		pVtx_FG[2].rhw = 1.0f;
		pVtx_FG[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_FG[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_FG[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_FG[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_FG[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_FG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_FG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_FG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_FG[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_FG += AMOUNT_VTX;
	}

	//�O�i�p�|���S��������
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FG; nCnt++)
	{
		g_aObject[nCnt].nStyle = 0;
		g_aObject[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCnt].bUse = false;
		g_aObject[nCnt].nCntSpawn = 0;
		g_aObject[nCnt].fLength = 0.0f;
		g_aObject[nCnt].fAngle = 0.0f;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_FG->Unlock();

	g_nStartingSet_Ivy = 0;

	//�K�v�Ȓl�̌v�Z����x����
	SetSpan_FG();

	//�K�v�ȏ���ݒ肷��
	Setinfo_Vtx_FG();

	////�ݒ肵���������ƂɃ|���S����W�J���Ă���
	//Update_FG();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_FG(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_FG; nCnt++)
	{
		if (g_pTexture_FG[nCnt] != NULL)
		{
			g_pTexture_FG[nCnt]->Release();
			g_pTexture_FG[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_FG != NULL)
	{
		g_pVtxBuff_FG->Release();
		g_pVtxBuff_FG = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_FG(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_FG;

	//�^�C�}�[���̃|�C���^
	bool* pInversion;
	bool* pReInversion;

	//���]���̎擾
	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_FG->Lock(0, 0, (void**)&pVtx_FG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FG; nCnt++)
	{
		if (!g_aObject[nCnt].bUse)
		{
			if (g_aObject[nCnt].nCntSpawn > 0)
			{
				g_aObject[nCnt].nCntSpawn--;
			}
			else
			{
				g_aObject[nCnt].bUse = true;
			}
		}
		else
		{
			//�ړ�
			g_aObject[nCnt].pos.x += g_aObject[nCnt].move.x;
			g_aObject[nCnt].pos.y += g_aObject[nCnt].move.y;

			//���]���肪�o�Ă���Ƃ�
			if (*pInversion == true &&
				g_aObject[nCnt].move.x <= 8.0f &&
				*pReInversion == false)
			{
				g_aObject[nCnt].move.x += 0.1f;
			}
			else if (*pInversion == true &&
				g_aObject[nCnt].move.x >= -12.0f &&
				*pReInversion == true)
			{
				g_aObject[nCnt].move.x -= 0.1f;
			}

			if (g_aObject[nCnt].pos.x < -1000.0f ||
				g_aObject[nCnt].pos.x > 3000.0f)
			{
				Disappear_FG(nCnt);
			}

			//�ړ��A��]�𔽉f
			pVtx_FG[0].pos.x = g_aObject[nCnt].pos.x + sinf(g_aObject[nCnt].rot.z - (D3DX_PI - g_aObject[nCnt].fAngle)) * g_aObject[nCnt].fLength;
			pVtx_FG[0].pos.y = g_aObject[nCnt].pos.y + cosf(g_aObject[nCnt].rot.z - (D3DX_PI - g_aObject[nCnt].fAngle)) * g_aObject[nCnt].fLength;
			pVtx_FG[1].pos.x = g_aObject[nCnt].pos.x + sinf(g_aObject[nCnt].rot.z + (D3DX_PI - g_aObject[nCnt].fAngle)) * g_aObject[nCnt].fLength;
			pVtx_FG[1].pos.y = g_aObject[nCnt].pos.y + cosf(g_aObject[nCnt].rot.z + (D3DX_PI - g_aObject[nCnt].fAngle)) * g_aObject[nCnt].fLength;
			pVtx_FG[2].pos.x = g_aObject[nCnt].pos.x + sinf(g_aObject[nCnt].rot.z - g_aObject[nCnt].fAngle) * g_aObject[nCnt].fLength;
			pVtx_FG[2].pos.y = g_aObject[nCnt].pos.y + cosf(g_aObject[nCnt].rot.z - g_aObject[nCnt].fAngle) * g_aObject[nCnt].fLength;
			pVtx_FG[3].pos.x = g_aObject[nCnt].pos.x + sinf(g_aObject[nCnt].rot.z + g_aObject[nCnt].fAngle) * g_aObject[nCnt].fLength;
			pVtx_FG[3].pos.y = g_aObject[nCnt].pos.y + cosf(g_aObject[nCnt].rot.z + g_aObject[nCnt].fAngle) * g_aObject[nCnt].fLength;
		}

		pVtx_FG += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_FG->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_FG(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_FG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FG; nCnt++)
	{
		switch (g_aObject[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_FG[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_FG[1]);

			break;

		case 2:

			pDevice->SetTexture(0, g_pTexture_FG[2]);

			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�K�v�Ȓl���v�Z����֐�
//***********************************************
void SetSpan_FG(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			g_fLength_Object[nCnt] = sqrtf((HALFSPAN_X_IVY * HALFSPAN_X_IVY) +
				(HALFSPAN_Y_IVY * HALFSPAN_Y_IVY)) * 0.5f;

			g_fAngle_Object[nCnt] = atan2f(HALFSPAN_X_IVY * 2.0f, HALFSPAN_X_IVY * 2.0f);

			break;

		case 1:

			g_fLength_Object[nCnt] = sqrtf((HALFSPAN_X_LONGIVY * HALFSPAN_X_LONGIVY) +
				(HALFSPAN_Y_LONGIVY * HALFSPAN_Y_LONGIVY)) * 0.5f;

			g_fAngle_Object[nCnt] = atan2f(HALFSPAN_X_LONGIVY * 2.0f, HALFSPAN_Y_LONGIVY * 2.0f);

			break;
		}
	}
}

//************************************************
//�|���S������ݒ�֐�
//************************************************
void Setinfo_Vtx_FG(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_FG;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_FG->Lock(0, 0, (void**)&pVtx_FG, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_FG; nCnt++)
	{
		g_nStartingSet_Ivy++;

		//�����_���Ɏ�ނ�ݒ�
		int nRandomStyle = (int)rand() % 5;

		if (nRandomStyle == 1 || nRandomStyle == 2)
		{
			g_aObject[nCnt].nStyle = 1;
		}
		else if (nRandomStyle == 3 || nRandomStyle == 4)
		{
			g_aObject[nCnt].nStyle = 2;
		}
		else
		{
			g_aObject[nCnt].nStyle = 0;
		}

		g_aObject[nCnt].move = D3DXVECTOR3(-6.0f, 0.0f, 0.0f);
		g_aObject[nCnt].bUse = false;

		if (g_nStartingSet_Ivy >= 5)
		{
			g_aObject[nCnt].nCntSpawn = 90 * (nCnt - 5);
		}

		int nRandom = (int)rand() % 2;

		if (nRandom == 0)
		{
			pVtx_FG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_FG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx_FG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx_FG[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		//���]
		else
		{
			pVtx_FG[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx_FG[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_FG[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx_FG[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		}

		if (g_nStartingSet_Ivy < 5)
		{
			g_aObject[nCnt].nCntSpawn = 0;

			if (g_aObject[nCnt].nStyle == 0)
			{
				g_aObject[nCnt].pos = D3DXVECTOR3(2200.0f - (396.0f * (g_nStartingSet_Ivy + 1)), 20.0f, 0.0f);
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.25f);
				g_aObject[nCnt].fLength = g_fLength_Object[0];
				g_aObject[nCnt].fAngle = g_fAngle_Object[0];
			}
			else if (g_aObject[nCnt].nStyle == 1)
			{
				g_aObject[nCnt].pos = D3DXVECTOR3(2500.0f - (396.0f * (g_nStartingSet_Ivy + 1)), 20.0f, 0.0f);

				if (nRandom == 0)
				{
					g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, -0.1f);
				}
				else
				{
					g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.1f);
				}

				g_aObject[nCnt].fLength = g_fLength_Object[1];
				g_aObject[nCnt].fAngle = g_fAngle_Object[1];
			}
			else if (g_aObject[nCnt].nStyle == 2)
			{
				g_aObject[nCnt].pos = D3DXVECTOR3(2500.0f - (396.0f * (g_nStartingSet_Ivy + 1)), 30.0f, 0.0f);
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aObject[nCnt].fLength = g_fLength_Object[1];
				g_aObject[nCnt].fAngle = g_fAngle_Object[1];
			}
		}
		else
		{
			if (g_aObject[nCnt].nStyle == 0)
			{
				g_aObject[nCnt].pos = D3DXVECTOR3(2200.0f, 20.0f, 0.0f);
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.25f);
				g_aObject[nCnt].fLength = g_fLength_Object[0];
				g_aObject[nCnt].fAngle = g_fAngle_Object[0];
			}
			else if (g_aObject[nCnt].nStyle == 1)
			{
				g_aObject[nCnt].pos = D3DXVECTOR3(2500.0f, 20.0f, 0.0f);

				if (nRandom == 0)
				{
					g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, -0.1f);
				}
				else
				{
					g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.1f);
				}

				g_aObject[nCnt].fLength = g_fLength_Object[1];
				g_aObject[nCnt].fAngle = g_fAngle_Object[1];
			}
			else if (g_aObject[nCnt].nStyle == 2)
			{
				g_aObject[nCnt].pos = D3DXVECTOR3(2500.0f, 30.0f, 0.0f);
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aObject[nCnt].fLength = g_fLength_Object[1];
				g_aObject[nCnt].fAngle = g_fAngle_Object[1];
			}
		}

		pVtx_FG += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_FG->Unlock();
}

//************************************************
//�|���S���̏����Đݒ肷��֐�
//***********************************************
void Disappear_FG(int nCnt)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_FG;

	//�^�C�}�[���̃|�C���^
	bool* pInversion;
	bool* pReInversion;

	//���]���̎擾
	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_FG->Lock(0, 0, (void**)&pVtx_FG, 0);

	pVtx_FG += AMOUNT_VTX * nCnt;

	//�����_���Ƀc�^�̎�ނ��Č���
	int nRandomStyle = (int)rand() % 5;

	if (nRandomStyle == 1 || nRandomStyle == 2)
	{
		g_aObject[nCnt].nStyle = 1;
	}
	else if (nRandomStyle == 3 || nRandomStyle == 4)
	{
		g_aObject[nCnt].nStyle = 2;
	}
	else
	{
		g_aObject[nCnt].nStyle = 0;
	}

	int nRandom = (int)rand() % 2;

	if (nRandom == 0)
	{
		pVtx_FG[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_FG[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_FG[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_FG[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//���]
	else
	{
		pVtx_FG[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_FG[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_FG[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx_FG[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	}

	//�����_���ɏo�Ă���ʒu���Č���
	if (*pInversion == false || *pReInversion == true)
	{
		if (g_aObject[nCnt].nStyle == 0)
		{
			g_aObject[nCnt].pos = D3DXVECTOR3(2200.0f, 20.0f, 0.0f);
			g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.25f);
			g_aObject[nCnt].fLength = g_fLength_Object[0];
			g_aObject[nCnt].fAngle = g_fAngle_Object[0];
		}
		else if (g_aObject[nCnt].nStyle == 1)
		{
			g_aObject[nCnt].pos = D3DXVECTOR3(2500.0f, 20.0f, 0.0f);

			if (nRandom == 0)
			{
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, -0.1f);
			}
			else
			{
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.1f);
			}

			g_aObject[nCnt].fLength = g_fLength_Object[1];
			g_aObject[nCnt].fAngle = g_fAngle_Object[1];
		}
		else if (g_aObject[nCnt].nStyle == 2)
		{
			g_aObject[nCnt].pos = D3DXVECTOR3(2500.0f, 30.0f, 0.0f);
			g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aObject[nCnt].fLength = g_fLength_Object[1];
			g_aObject[nCnt].fAngle = g_fAngle_Object[1];
		}
	}
	else
	{
		if (g_aObject[nCnt].nStyle == 0)
		{
			g_aObject[nCnt].pos = D3DXVECTOR3(-200.0f, 20.0f, 0.0f);
			g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.25f);
			g_aObject[nCnt].fLength = g_fLength_Object[0];
			g_aObject[nCnt].fAngle = g_fAngle_Object[0];
		}
		else if (g_aObject[nCnt].nStyle == 1)
		{
			g_aObject[nCnt].pos = D3DXVECTOR3(-500.0f, 20.0f, 0.0f);

			if (nRandom == 0)
			{
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, -0.1f);
			}
			else
			{
				g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.1f);
			}

			g_aObject[nCnt].fLength = g_fLength_Object[1];
			g_aObject[nCnt].fAngle = g_fAngle_Object[1];
		}
		else if (g_aObject[nCnt].nStyle == 2)
		{
			g_aObject[nCnt].pos = D3DXVECTOR3(-500.0f, 30.0f, 0.0f);
			g_aObject[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aObject[nCnt].fLength = g_fLength_Object[1];
			g_aObject[nCnt].fAngle = g_fAngle_Object[1];
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_FG->Unlock();
}